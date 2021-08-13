// Copyright (C) 2020-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#include <functional>
#include <vector>

#include "hexl/logging/logging.hpp"
#include "hexl/ntt/ntt.hpp"
#include "hexl/number-theory/number-theory.hpp"
#include "ntt/fwd-ntt-avx512.hpp"
#include "ntt/ntt-avx512-util.hpp"
#include "ntt/ntt-internal.hpp"
#include "util/avx512-util.hpp"

namespace intel {
namespace hexl {

#ifdef HEXL_HAS_AVX512DQ

/// @brief The Harvey butterfly: assume \p X, \p Y in [0, 4q), and return X', Y'
/// in [0, 4q) such that X', Y' = X + WY, X - WY (mod q).
/// @param[in,out] X Input representing 8 64-bit signed integers in SIMD form
/// @param[in,out] Y Input representing 8 64-bit signed integers in SIMD form
/// @param[in] W_op Input representing 8 64-bit signed integers in SIMD form
/// @param[in] W_precon Preconditioned \p W_op for BitShift-bit Barrett
/// reduction
/// @param[in] neg_modulus Negative modulus, i.e. (-q) represented as 8 64-bit
/// signed integers in SIMD form
/// @param[in] twice_modulus Twice the modulus, i.e. 2*q represented as 8 64-bit
/// signed integers in SIMD form
/// @param InputLessThanMod If true, assumes \p X, \p Y < \p qp. Otherwise,
/// assumes \p X, \p Y < 4*\p q
/// @details See Algorithm 4 of https://arxiv.org/pdf/1205.2926.pdf
template <int BitShift, bool InputLessThanMod>
void FwdButterfly(__m512i* X, __m512i* Y, __m512i W_op, __m512i W_precon,
                  __m512i neg_modulus, __m512i twice_modulus) {
  if (!InputLessThanMod) {
    *X = _mm512_hexl_small_mod_epu64(*X, twice_modulus);
  }

  __m512i T;
  if (BitShift == 32) {
    __m512i Q = _mm512_hexl_mullo_epi<64>(W_precon, *Y);
    Q = _mm512_srli_epi64(Q, 32);
    __m512i W_Y = _mm512_hexl_mullo_epi<64>(W_op, *Y);
    T = _mm512_hexl_mullo_add_lo_epi<64>(W_Y, Q, neg_modulus);
  } else if (BitShift == 52) {
    __m512i Q = _mm512_hexl_mulhi_epi<BitShift>(W_precon, *Y);
    __m512i W_Y = _mm512_hexl_mullo_epi<BitShift>(W_op, *Y);
    T = _mm512_hexl_mullo_add_lo_epi<BitShift>(W_Y, Q, neg_modulus);
  } else if (BitShift == 64) {
    // Perform approximate computation of Q, as described in page 7 of
    // https://arxiv.org/pdf/2003.04510.pdf
    __m512i Q = _mm512_hexl_mulhi_approx_epi<BitShift>(W_precon, *Y);
    __m512i W_Y = _mm512_hexl_mullo_epi<BitShift>(W_op, *Y);
    // Compute T in range [0, 4q)
    T = _mm512_hexl_mullo_add_lo_epi<BitShift>(W_Y, Q, neg_modulus);
    // Reduce T to range [0, 2q)
    T = _mm512_hexl_small_mod_epu64<2>(T, twice_modulus);
  } else {
    HEXL_CHECK(false, "Invalid BitShift " << BitShift);
  }

  __m512i twice_mod_minus_T = _mm512_sub_epi64(twice_modulus, T);
  *Y = _mm512_add_epi64(*X, twice_mod_minus_T);
  *X = _mm512_add_epi64(*X, T);
}

template <int BitShift>
void FwdT1(uint64_t* operand, __m512i v_neg_modulus, __m512i v_twice_mod,
           uint64_t m, const uint64_t* W_op, const uint64_t* W_precon) {
  const __m512i* v_W_op_pt = reinterpret_cast<const __m512i*>(W_op);
  const __m512i* v_W_precon_pt = reinterpret_cast<const __m512i*>(W_precon);
  size_t j1 = 0;

  // 8 | m guaranteed by n >= 16
  HEXL_LOOP_UNROLL_8
  for (size_t i = m / 8; i > 0; --i) {
    uint64_t* X = operand + j1;
    __m512i* v_X_pt = reinterpret_cast<__m512i*>(X);

    __m512i v_X;
    __m512i v_Y;
    LoadFwdInterleavedT1(X, &v_X, &v_Y);
    __m512i v_W_op = _mm512_loadu_si512(v_W_op_pt++);
    __m512i v_W_precon = _mm512_loadu_si512(v_W_precon_pt++);

    FwdButterfly<BitShift, false>(&v_X, &v_Y, v_W_op, v_W_precon, v_neg_modulus,
                                  v_twice_mod);
    WriteFwdInterleavedT1(v_X, v_Y, v_X_pt);

    j1 += 16;
  }
}

template <int BitShift>
void FwdT2(uint64_t* operand, __m512i v_neg_modulus, __m512i v_twice_mod,
           uint64_t m, const uint64_t* W_op, const uint64_t* W_precon) {
  const __m512i* v_W_op_pt = reinterpret_cast<const __m512i*>(W_op);
  const __m512i* v_W_precon_pt = reinterpret_cast<const __m512i*>(W_precon);

  size_t j1 = 0;
  // 4 | m guaranteed by n >= 16
  HEXL_LOOP_UNROLL_4
  for (size_t i = m / 4; i > 0; --i) {
    uint64_t* X = operand + j1;
    __m512i* v_X_pt = reinterpret_cast<__m512i*>(X);

    __m512i v_X;
    __m512i v_Y;
    LoadFwdInterleavedT2(X, &v_X, &v_Y);

    __m512i v_W_op = _mm512_loadu_si512(v_W_op_pt++);
    __m512i v_W_precon = _mm512_loadu_si512(v_W_precon_pt++);

    HEXL_CHECK(ExtractValues(v_W_op)[0] == ExtractValues(v_W_op)[1],
               "bad v_W_op " << ExtractValues(v_W_op));
    HEXL_CHECK(ExtractValues(v_W_precon)[0] == ExtractValues(v_W_precon)[1],
               "bad v_W_precon " << ExtractValues(v_W_precon));
    FwdButterfly<BitShift, false>(&v_X, &v_Y, v_W_op, v_W_precon, v_neg_modulus,
                                  v_twice_mod);

    _mm512_storeu_si512(v_X_pt++, v_X);
    _mm512_storeu_si512(v_X_pt, v_Y);

    j1 += 16;
  }
}

template <int BitShift>
void FwdT4(uint64_t* operand, __m512i v_neg_modulus, __m512i v_twice_mod,
           uint64_t m, const uint64_t* W_op, const uint64_t* W_precon) {
  size_t j1 = 0;
  const __m512i* v_W_op_pt = reinterpret_cast<const __m512i*>(W_op);
  const __m512i* v_W_precon_pt = reinterpret_cast<const __m512i*>(W_precon);

  // 2 | m guaranteed by n >= 16
  HEXL_LOOP_UNROLL_4
  for (size_t i = m / 2; i > 0; --i) {
    uint64_t* X = operand + j1;
    __m512i* v_X_pt = reinterpret_cast<__m512i*>(X);

    __m512i v_X;
    __m512i v_Y;
    LoadFwdInterleavedT4(X, &v_X, &v_Y);

    __m512i v_W_op = _mm512_loadu_si512(v_W_op_pt++);
    __m512i v_W_precon = _mm512_loadu_si512(v_W_precon_pt++);
    FwdButterfly<BitShift, false>(&v_X, &v_Y, v_W_op, v_W_precon, v_neg_modulus,
                                  v_twice_mod);

    _mm512_storeu_si512(v_X_pt++, v_X);
    _mm512_storeu_si512(v_X_pt, v_Y);

    j1 += 16;
  }
}

template <int BitShift, bool InputLessThanMod>
void FwdT8(uint64_t* operand, __m512i v_neg_modulus, __m512i v_twice_mod,
           uint64_t t, uint64_t m, const uint64_t* W_op,
           const uint64_t* W_precon) {
  size_t j1 = 0;

  HEXL_LOOP_UNROLL_4
  for (size_t i = 0; i < m; i++) {
    uint64_t* X = operand + j1;
    uint64_t* Y = X + t;

    __m512i v_W_op = _mm512_set1_epi64(static_cast<int64_t>(*W_op++));
    __m512i v_W_precon = _mm512_set1_epi64(static_cast<int64_t>(*W_precon++));

    __m512i* v_X_pt = reinterpret_cast<__m512i*>(X);
    __m512i* v_Y_pt = reinterpret_cast<__m512i*>(Y);

    // assume 8 | t
    for (size_t j = t / 8; j > 0; --j) {
      __m512i v_X = _mm512_loadu_si512(v_X_pt);
      __m512i v_Y = _mm512_loadu_si512(v_Y_pt);

      FwdButterfly<BitShift, InputLessThanMod>(&v_X, &v_Y, v_W_op, v_W_precon,
                                               v_neg_modulus, v_twice_mod);

      _mm512_storeu_si512(v_X_pt++, v_X);
      _mm512_storeu_si512(v_Y_pt++, v_Y);
    }
    j1 += (t << 1);
  }
}

/// @brief AVX512 implementation of the forward NTT
/// @param[in, out] operand Input data. Overwritten with NTT output
/// @param[in] n Size of the transfrom, i.e. the polynomial degree. Must be a
/// power of two.
/// @param[in] modulus Prime modulus. Must satisfy q == 1 mod 2n
/// @param[in] root_of_unity_powers Powers of 2n'th root of unity in F_q. In
/// bit-reversed order.
/// @param[in] precon_root_of_unity_powers Pre-conditioned Powers of 2n'th root
/// of unity in F_q. In bit-reversed order.
/// @param[in] input_mod_factor Upper bound for inputs; inputs must be in [0,
/// input_mod_factor * modulus)
/// @param[in] output_mod_factor Upper bound for result; result must be in [0,
/// output_mod_factor * modulus)
/// @param[in] recursion_depth Depth of recursive call
/// @param[in] recursion_half Helper for indexing roots of unity
/// @details The implementation is recursive. The base case is a breadth-first
/// NTT, where all the butterflies in a given stage are processed before any
/// butteflies in the next stage. The base case is small enough to fit in the
/// smallest cache. Larger NTTs are processed recursively in a depth-first
/// manner, such that an entire subtransform is completed before moving to the
/// next subtransform. This reduces the number of cache misses, improving
/// performance on larger transform sizes.
template <int BitShift>
void ForwardTransformToBitReverseAVX512(
    uint64_t* operand, uint64_t n, uint64_t modulus,
    const uint64_t* root_of_unity_powers,
    const uint64_t* precon_root_of_unity_powers, uint64_t input_mod_factor,
    uint64_t output_mod_factor, uint64_t recursion_depth,
    uint64_t recursion_half) {
  HEXL_CHECK(NTT::CheckArguments(n, modulus), "");
  HEXL_CHECK(modulus < MaximumValue(BitShift) / 4,
             "modulus " << modulus << " too large for BitShift " << BitShift
                        << " => maximum value " << MaximumValue(BitShift) / 4);
  HEXL_CHECK_BOUNDS(precon_root_of_unity_powers, n, MaximumValue(BitShift),
                    "precon_root_of_unity_powers too large");
  HEXL_CHECK_BOUNDS(operand, n, MaximumValue(BitShift), "operand too large");
  // Skip input bound checking for recursive steps
  HEXL_CHECK_BOUNDS(operand, (recursion_depth == 0) ? n : 0,
                    input_mod_factor * modulus,
                    "operand larger than input_mod_factor * modulus ("
                        << input_mod_factor << " * " << modulus << ")");
  HEXL_CHECK(n >= 16,
             "Don't support small transforms. Need n >= 16, got n = " << n);
  HEXL_CHECK(
      input_mod_factor == 1 || input_mod_factor == 2 || input_mod_factor == 4,
      "input_mod_factor must be 1, 2, or 4; got " << input_mod_factor);
  HEXL_CHECK(output_mod_factor == 1 || output_mod_factor == 4,
             "output_mod_factor must be 1 or 4; got " << output_mod_factor);

  uint64_t twice_mod = modulus << 1;

  __m512i v_modulus = _mm512_set1_epi64(static_cast<int64_t>(modulus));
  __m512i v_neg_modulus = _mm512_set1_epi64(-static_cast<int64_t>(modulus));
  __m512i v_twice_mod = _mm512_set1_epi64(static_cast<int64_t>(twice_mod));

  HEXL_VLOG(5, "root_of_unity_powers " << std::vector<uint64_t>(
                   root_of_unity_powers, root_of_unity_powers + n))
  HEXL_VLOG(5,
            "precon_root_of_unity_powers " << std::vector<uint64_t>(
                precon_root_of_unity_powers, precon_root_of_unity_powers + n));
  HEXL_VLOG(5, "operand " << std::vector<uint64_t>(operand, operand + n));

  static const size_t base_ntt_size = 1024;

  if (n <= base_ntt_size) {  // Perform breadth-first NTT
    size_t t = (n >> 1);
    size_t m = 1;
    size_t W_idx = (m << recursion_depth) + (recursion_half * m);
    // First iteration assumes input in [0,p)
    if (m < (n >> 3)) {
      const uint64_t* W_op = &root_of_unity_powers[W_idx];
      const uint64_t* W_precon = &precon_root_of_unity_powers[W_idx];

      if (input_mod_factor <= 2) {
        FwdT8<BitShift, true>(operand, v_neg_modulus, v_twice_mod, t, m, W_op,
                              W_precon);
      } else {
        FwdT8<BitShift, false>(operand, v_neg_modulus, v_twice_mod, t, m, W_op,
                               W_precon);
      }

      t >>= 1;
      m <<= 1;
      W_idx <<= 1;
    }
    for (; m < (n >> 3); m <<= 1) {
      const uint64_t* W_op = &root_of_unity_powers[W_idx];
      const uint64_t* W_precon = &precon_root_of_unity_powers[W_idx];
      FwdT8<BitShift, false>(operand, v_neg_modulus, v_twice_mod, t, m, W_op,
                             W_precon);
      t >>= 1;
      W_idx <<= 1;
    }

    // Do T=4, T=2, T=1 separately
    {
      // Correction step needed due to extra copies of roots of unity in the
      // AVX512 vectors loaded for FwdT2 and FwdT4
      auto compute_new_W_idx = [&](size_t idx) {
        // Originally, from root of unity vector index to loop:
        // [0, N/8) => FwdT8
        // [N/8, N/4) => FwdT4
        // [N/4, N/2) => FwdT2
        // [N/2, N) => FwdT1
        // The new mapping from AVX512 root of unity vector index to loop:
        // [0, N/8) => FwdT8
        // [N/8, 5N/8) => FwdT4
        // [5N/8, 9N/8) => FwdT2
        // [9N/8, 13N/8) => FwdT1
        size_t N = n << recursion_depth;

        // FwdT8 range
        if (idx <= N / 8) {
          return idx;
        }
        // FwdT4 range
        if (idx <= N / 4) {
          return (idx - N / 8) * 4 + (N / 8);
        }
        // FwdT2 range
        if (idx <= N / 2) {
          return (idx - N / 4) * 2 + (5 * N / 8);
        }
        // FwdT1 range
        return idx + (5 * N / 8);
      };

      size_t new_W_idx = compute_new_W_idx(W_idx);
      const uint64_t* W_op = &root_of_unity_powers[new_W_idx];
      const uint64_t* W_precon = &precon_root_of_unity_powers[new_W_idx];
      FwdT4<BitShift>(operand, v_neg_modulus, v_twice_mod, m, W_op, W_precon);

      m <<= 1;
      W_idx <<= 1;
      new_W_idx = compute_new_W_idx(W_idx);
      W_op = &root_of_unity_powers[new_W_idx];
      W_precon = &precon_root_of_unity_powers[new_W_idx];
      FwdT2<BitShift>(operand, v_neg_modulus, v_twice_mod, m, W_op, W_precon);

      m <<= 1;
      W_idx <<= 1;
      new_W_idx = compute_new_W_idx(W_idx);
      W_op = &root_of_unity_powers[new_W_idx];
      W_precon = &precon_root_of_unity_powers[new_W_idx];
      FwdT1<BitShift>(operand, v_neg_modulus, v_twice_mod, m, W_op, W_precon);
    }

    if (output_mod_factor == 1) {
      // n power of two at least 8 => n divisible by 8
      HEXL_CHECK(n % 8 == 0, "n " << n << " not a power of 2");
      __m512i* v_X_pt = reinterpret_cast<__m512i*>(operand);
      for (size_t i = 0; i < n; i += 8) {
        __m512i v_X = _mm512_loadu_si512(v_X_pt);

        // Reduce from [0, 4q) to [0, q)
        v_X = _mm512_hexl_small_mod_epu64(v_X, v_twice_mod);
        v_X = _mm512_hexl_small_mod_epu64(v_X, v_modulus);

        HEXL_CHECK_BOUNDS(ExtractValues(v_X).data(), 8, modulus,
                          "v_X exceeds bound " << modulus);

        _mm512_storeu_si512(v_X_pt, v_X);

        ++v_X_pt;
      }
    }
  } else {
    // Perform depth-first NTT via recursive call
    size_t t = (n >> 1);
    size_t W_idx = (1ULL << recursion_depth) + recursion_half;
    const uint64_t* W_op = &root_of_unity_powers[W_idx];
    const uint64_t* W_precon = &precon_root_of_unity_powers[W_idx];

    FwdT8<BitShift, false>(operand, v_neg_modulus, v_twice_mod, t, 1, W_op,
                           W_precon);

    ForwardTransformToBitReverseAVX512<BitShift>(
        operand, n / 2, modulus, root_of_unity_powers,
        precon_root_of_unity_powers, input_mod_factor, output_mod_factor,
        recursion_depth + 1, recursion_half * 2);

    ForwardTransformToBitReverseAVX512<BitShift>(
        &operand[n / 2], n / 2, modulus, root_of_unity_powers,
        precon_root_of_unity_powers, input_mod_factor, output_mod_factor,
        recursion_depth + 1, recursion_half * 2 + 1);
  }
}

#endif  // HEXL_HAS_AVX512DQ

}  // namespace hexl
}  // namespace intel
