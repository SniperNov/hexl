// Copyright (C) 2020 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#include <benchmark/benchmark.h>

#include <vector>

#include "eltwise/eltwise-sub-mod-avx512.hpp"
#include "eltwise/eltwise-sub-mod-internal.hpp"
#include "hexl/eltwise/eltwise-sub-mod.hpp"
#include "hexl/logging/logging.hpp"
#include "hexl/number-theory/number-theory.hpp"
#include "hexl/util/aligned-allocator.hpp"
#include "util/util-internal.hpp"

namespace intel {
namespace hexl {

// state[0] is the degree
static void BM_EltwiseVectorVectorSubModNative(
    benchmark::State& state) {  //  NOLINT
  size_t input_size = state.range(0);
  uint64_t modulus = 0xffffffffffc0001ULL;

  auto input1 = GenerateInsecureUniformIntRandomValues(input_size, 0, modulus);
  auto input2 = GenerateInsecureUniformIntRandomValues(input_size, 0, modulus);
  AlignedVector64<uint64_t> output(input_size, 0);

  for (auto _ : state) {
    EltwiseSubModNative(output.data(), input1.data(), input2.data(), input_size,
                        modulus);
  }
}

BENCHMARK(BM_EltwiseVectorVectorSubModNative)
    ->Unit(benchmark::kMicrosecond)
    ->Args({1024})
    ->Args({4096})
    ->Args({16384})
    ->Args({32768})
    ->Args({65536})
    ->Args({131072})
    ->Args({262144});

//=================================================================

#ifdef HEXL_HAS_AVX512DQ
// state[0] is the degree
static void BM_EltwiseVectorVectorSubModAVX512(
    benchmark::State& state) {  //  NOLINT
  size_t input_size = state.range(0);
  size_t modulus = 1152921504606877697;

  auto input1 = GenerateInsecureUniformIntRandomValues(input_size, 0, modulus);
  auto input2 = GenerateInsecureUniformIntRandomValues(input_size, 0, modulus);
  AlignedVector64<uint64_t> output(input_size, 0);

  for (auto _ : state) {
    EltwiseSubModAVX512(output.data(), input1.data(), input2.data(), input_size,
                        modulus);
  }
}

BENCHMARK(BM_EltwiseVectorVectorSubModAVX512)
    ->Unit(benchmark::kMicrosecond)
    ->Args({1024})
    ->Args({4096})
    ->Args({16384})
    ->Args({32768})
    ->Args({65536})
    ->Args({131072})
    ->Args({262144});
#endif

//=================================================================
// state[0] is the degree
static void BM_EltwiseVectorScalarSubModNative(
    benchmark::State& state) {  //  NOLINT
  size_t input_size = state.range(0);
  uint64_t modulus = 0xffffffffffc0001ULL;

  auto input1 = GenerateInsecureUniformIntRandomValues(input_size, 0, modulus);
  uint64_t input2 = GenerateInsecureUniformIntRandomValue(0, modulus);
  AlignedVector64<uint64_t> output(input_size, 0);

  for (auto _ : state) {
    EltwiseSubModNative(output.data(), input1.data(), input2, input_size,
                        modulus);
  }
}

BENCHMARK(BM_EltwiseVectorScalarSubModNative)
    ->Unit(benchmark::kMicrosecond)
    ->Args({1024})
    ->Args({4096})
    ->Args({16384})
    ->Args({32768})
    ->Args({65536})
    ->Args({131072})
    ->Args({262144});

//=================================================================

#ifdef HEXL_HAS_AVX512DQ
// state[0] is the degree
static void BM_EltwiseVectorScalarSubModAVX512(
    benchmark::State& state) {  //  NOLINT
  size_t input_size = state.range(0);
  size_t modulus = 1152921504606877697;

  auto input1 = GenerateInsecureUniformIntRandomValues(input_size, 0, modulus);
  uint64_t input2 = GenerateInsecureUniformIntRandomValue(0, modulus);
  AlignedVector64<uint64_t> output(input_size, 0);

  for (auto _ : state) {
    EltwiseSubModAVX512(output.data(), input1.data(), input2, input_size,
                        modulus);
  }
}

BENCHMARK(BM_EltwiseVectorScalarSubModAVX512)
    ->Unit(benchmark::kMicrosecond)
    ->Args({1024})
    ->Args({4096})
    ->Args({16384})
    ->Args({32768})
    ->Args({65536})
    ->Args({131072})
    ->Args({262144});
#endif

}  // namespace hexl
}  // namespace intel
