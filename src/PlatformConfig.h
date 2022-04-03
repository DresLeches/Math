#pragma once

// operating system platform
#if defined(_WIN32) || defined(_WIN64)
    #define MSFT
#elif defined (__APPLE__)
    #define APPLE
#elif defined(__unix__) || defined (__linux__)
    #define UNIX
#endif

// check arch
#if defined (__arm__) || defined (__arm) || defined (_M_ARM) || defined (__ARM_ARCH)
    #define ARM
#else
    #if defined (__x86_64) || defined (__x86_64__) || defined (_M_X64)
        #define X64
    #else
        #define X32
    #endif
#endif

// if check which simd version is supported
#if defined (X64)
    #define SIMD_SSE
#elif defined (ARM)
    #define SIMD_NEON
#else
    // not supported
#endif
