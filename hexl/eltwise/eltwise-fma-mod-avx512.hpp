// Copyright (C) 2020-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <immintrin.h>
#include <stdint.h>

#include "eltwise/eltwise-fma-mod-internal.hpp"
#include "hexl/number-theory/number-theory.hpp"
#include "hexl/util/check.hpp"
#include "util/avx512-util.hpp"

namespace intel {
namespace hexl {

#ifdef HEXL_HAS_AVX512DQ

/// uses Shoup's modular multiplication. See Algorithm 4 of
/// https://arxiv.org/pdf/2012.01968.pdf
template <int BitShift, int InputModFactor>
void EltwiseFMAModAVX512(uint64_t* result, const uint64_t* arg1, uint64_t arg2,
                         const uint64_t* arg3, uint64_t n, uint64_t modulus);
#endif

}  // namespace hexl
}  // namespace intel
