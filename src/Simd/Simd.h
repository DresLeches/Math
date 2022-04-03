#pragma once
#include "Defines.h"
#include "PlatformConfig.h"


#if defined SIMD_SSE
    #if defined (MSFT)
        #include <immintrin.h>
    #elif defined (UNIX)
        #include <immintrin.h>
    #endif
#endif

// supported up to sse 4.2

#if defined (SIMD_SSE)
    #define Simd_t __m128
    #define ISimd_t __m128i

    // add
    #define SimdAdd32(a, b) _mm_add_ps(a, b)
    #define ISimdAdd32(a, b) _mm_add_epi32(a, b)

    // subtract
    #define SimdSub32(a, b) _mm_sub_ps(a, b)
    #define ISimdSub32(a, b) _mm_sub_epi32(a, b)

    // multiply
    #define SimdMul32(a, b) _mm_mul_ps(a, b)
    #define ISimdMul32(a, b) _mm_mul_epi32(a, b)

    // divide
    #define SimdDiv32(a, b) _mm_div_ps(a, b)
    #define ISimdDiv32(a, b) _mm_div_epi32(a, b)

    // rsqrt
    #define SimdRSqrt32(a) _mm_rsqrt_ps(a)

    // shuffle
    #define SimdSetShuffleRev(a, b, c, d) _MM_SHUFFLE(d, c, b, a)
    #define SimdShuffle32(a, b, shf) _mm_shuffle_ps(a, b, shf)
    #define ISimdShuffle32(a, b, shf) _mm_shuffle_epi32(a, b, shf)

    // splat
    #define SimdSplatX(a) _mm_shuffle_ps(a, a, _MM_SHUFFLE(0, 0, 0, 0))
    #define SimdSplatY(a) _mm_shuffle_ps(a, a, _MM_SHUFFLE(1, 1, 1, 1))
    #define SimdSplatZ(a) _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 2, 2, 2))
    #define SimdSplatW(a) _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 3, 3, 3))

    // min
    #define SimdMin32(a, b) _mm_min_ps(a, b)
    #define ISimdMin3(a, b) _mm_min_epi32(a, b)

    // max
    #define SimdMax32(a, b) _mm_max_ps(a, b)
    #define ISimdMax32(a, b) _mm_max_epi32(a, b)

    // floor / ceil
    #define SimdFloor32(a) _mm_floor_ps(a)
    #define SimdCeil32(a) _mm_ceil_ps(a)

    // bitwise op
    #define SimdBitwiseOr(a, b) _mm_or_ps(a, b)
    #define SimdBitwiseAnd(a, b) _mm_and_ps(a, b)
    #define SimdBitwiseXor(a, b) _mm_xor_ps(a, b)
    
    // set / load / store
    #define SimdSet32(a, b, c, d) _mm_set_ps(a, b, c, d)
    #define SimdSet32(v) _mm_set_ps(v, v, v, v)
    #define ISimdSet32(a, b, c, d) _mm_set_epi32(a, b, c, d)
    #define ISimdSet32(v) _mm_set_epi32(v, v, v, v)
    #define SimdLoad32(data) _mm_load_ps(data)      // must be 16-byte aligned
    #define SimdStore32(data, dst) _mm_store_ps(data, dst)
    
#else
    
#endif


