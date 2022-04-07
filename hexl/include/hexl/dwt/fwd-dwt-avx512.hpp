// Copyright (C) 2020-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "hexl/dwt/dwt.hpp"

namespace intel {
namespace hexl {

#ifdef HEXL_HAS_AVX512DQ

/// @brief AVX512 implementation of the forward DWT
/// @param[out] result_cmplx_intrlvd Output data. Overwritten with DWT output.
/// Result is a vector of double with interleaved real and imaginary numbers.
/// @param[in] operand_cmplx_intrlvd Input data. A vector of double with
/// interleaved real and imaginary numbers.
/// @param[in] roots_of_unity_cmplx_intrlvd Powers of 2n'th root of unity. In
/// bit-reversed order.
/// @param[in] n Size of the transform, i.e. the polynomial degree. Must be a
/// power of two.
/// @param[in] scale Scale applied to output values
void Forward_DWT_ToBitReverseAVX512(double* result_cmplx_intrlvd,
                                    const double* operand_cmplx_intrlvd,
                                    const double* roots_of_unity_cmplx_intrlvd,
                                    const uint64_t n,
                                    const double* scale = nullptr,
                                    uint64_t recursion_depth = 0,
                                    uint64_t recursion_half = 0);

/// @brief Construct floating-point values from CRT-composed polynomial with
/// integer coefficients in AVX512.
/// @param[out] res_cmplx_intrlvd Stores the result
/// @param[in] plain Plaintext
/// @param[in] threshold Upper half threshold with respect to the total
/// coefficient modulus
/// @param[in] decryption_modulus Product of all primes in the coefficient
/// modulus
/// @param[in] inv_scale Scale applied to output values
/// @param[in] mod_size Size of coefficient modulus parameter
/// @param[in] coeff_count Degree of the polynomial modulus parameter
void BuildFloatingPointsAVX512(double* res_cmplx_intrlvd, const uint64_t* plain,
                               const uint64_t* threshold,
                               const uint64_t* decryption_modulus,
                               const double inv_scale, const size_t mod_size,
                               const size_t coeff_count);

#endif  // HEXL_HAS_AVX512DQ

}  // namespace hexl
}  // namespace intel
