#pragma once

#include "Engine/Core/Log.h"

#if defined(_MSC_VER)
#define ENGINE_DEBUG_BREAK() __debugbreak() // Windows / MSVC
#elif defined(__clang__) || defined(__GNUC__)
#define ENGINE_DEBUG_BREAK() __builtin_trap() // Linux / macOS / Clang / GCC
#else
#define ENGINE_DEBUG_BREAK()
#endif

#if defined(ENGINE_BUILD_SHARED)

inline void EngineAssertHandler(const char *expr, const char *message, const char *file, int line)
{
    std::cerr << "[ASSERT FAILED]\n"
              << "  Condition: " << expr << "\n"
              << "  Message:   " << message << "\n"
              << "  Location:  " << file << ":" << line << "\n\n";
}

#define FRISK_ASSERT(condition, message)                                                                               \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(condition))                                                                                              \
        {                                                                                                              \
            EngineAssertHandler(#condition, message, __FILE__, __LINE__);                                              \
            ENGINE_DEBUG_BREAK();                                                                                      \
        }                                                                                                              \
    } while (false)

#else
#define FRISK_ASSERT(condition, message) ((void)0)
#endif