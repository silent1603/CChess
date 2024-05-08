#pragma once
#include "base_config.h"
//platform check
#if defined(_MSC_VER) || defined(_MSC_FULL_VER)
#   define COMPILER_MSVC 1
#   if defined(_WIN32) || defined(_WIN64)
#       define OS_WINDOWS 1
#   else
#       error missing OS detection
#   endif
#   if defined(_M_AMD64)
#       define ARCH_X64 1
#   elif defined(_M_I86)
#       define ARCH_X86 1
#   elif defined(_M_ARM)
#       define ARCH_ARM 1
#   else
#       error missing ARCH detection
#   endif
#elif defined(__clang__)
#   define COMPILER_CLANG 1 
#   if defined(_WIN32)
#       define OS_WINDOWS 1
#   elif defined(__gnu_linux__) || define(__linux__)
#       define OS_LINUX 1
#   elif defined(__ANDROID__)
#       define OS_ANDROID 1
#   elif define(__APPLE__) && defined(__MACH__)
#       define OS_MAC 1
#   elif define(__unix__)
#       define OS_UNIX 1
#   else
#       error missing OS detection
#   endif
#   if defined(__amd64__)
#       define ARCH_X64 1
#   elif defined(__i386__)
#       define ARCH_X86 1
#   elif defined(__arm__)
#       define ARCH_ARM 1
#   elif defined(__aarch64__)
#       define ARCH_ARM64 1
#   else
#       error missing ARCH detection
#   endif
#elif defined(__GNUC__)
#   define COMPILER_GCC 1
#   if defined(_WIN32)
#       define OS_WINDOWS 1
#   elif defined(__gnu_linux__)
#       define OS_LINUX 1
#   elif define(__unix__)
#       define OS_UNIX 1
#   else
#       error missing OS detection
#   endif
#   if defined(__amd64__)
#       define ARCH_X64 1
#   elif defined(__i386__)
#       define ARCH_X86 1
#   elif defined(__arm__)
#       define ARCH_ARM 1
#   elif defined(__aarch64__)
#       define ARCH_ARM64 1
#   else
#       error missing ARCH detection
#   endif
#else
#   error no context cracking for this complier
#endif

#if !defined(COMPILER_MSVC)
#   define  COMPILER_MSVC 0
#endif

#if !defined(COMPILER_CLANG)
#   define  COMPILER_CLANG 0
#endif

#if !defined(COMPILER_GCC)
#   define  COMPILER_GCC 0
#endif

#if !defined(OS_WINDOWS)
#   define OS_WINDOWS 0
#endif

#if !defined(OS_LINUX)
#   define  OS_LINUX 0
#endif

#if !defined(OS_ANDROID)
#   define  OS_ANDROID 0
#endif

#if !defined(OS_MAC)
#   define  OS_MAC 0
#endif

#if !defined(OS_UNIX)
#define OS_UNIX 0
#endif

#if !defined(ARCH_X64)
#   define  ARCH_X64 0
#endif

#if !defined(ARCH_X86)
#   define  ARCH_X86 0
#endif

#if !defined(ARCH_ARM)
#   define  ARCH_ARM 0
#endif

#if !defined(ARCH_ARM64)
#   define  ARCH_ARM64 0
#endif

#if OS_WINDOWS
#   if USE_LIBC_MALLOC == 0
#   define USE_LIBC_WIN32_VIRTUALALLOC 1
#   endif

#ifndef UNICODE
#define UNICODE
#endif

#define  WIN32_LEAN_AND_MEAN
#define	 WIN32_EXTRA_LEAN
#include <Windows.h>
#include <atlconv.h>
#else

    #   if USE_LIBC_MALLOC == 0
    #   define USE_LINUX_MMAP 1
    #   endif

    #if defined(_POSIX_VERSION)
    #include <aio.h>
    #include <arpa/inet.h>
    #include <assert.h>
    #include <complex.h>
    #include <cpio.h>
    #include <ctype.h>
    #include <dirent.h>
    #include <dlfcn.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <fenv.h>
    #include <fmtmsg.h>
    #include <fnmatch.h>
    #include <ftw.h>
    #include <glob.h>
    #include <grp.h>
    #include <iconv.h>
    #include <inttypes.h>
    #include <langinfo.h>
    #include <libgen.h>
    #include <locale.h>
    #include <math.h>
    #include <monetary.h>
    #include <mqueue.h>
    #include <ndbm.h>
    #include <net/if.h>
    #include <netdb.h>
    #include <netinet/in.h>
    #include <netinet/tcp.h>
    #include <nl_types.h>
    #include <poll.h>
    #include <pthread.h>
    #include <pwd.h>
    #include <regex.h>
    #include <sched.h>
    #include <search.h>
    #include <semaphore.h>
    #include <setjmp.h>
    #include <signal.h>
    #include <spawn.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <strings.h>
    #include <stropts.h>
    #include <sys/ipc.h>
    #include <sys/mman.h>
    #include <sys/msg.h>
    #include <sys/resource.h>
    #include <sys/select.h>
    #include <sys/sem.h>
    #include <sys/shm.h>
    #include <sys/socket.h>
    #include <sys/stat.h>
    #include <sys/statvfs.h>
    #include <sys/time.h>
    #include <sys/times.h>
    #include <sys/types.h>
    #include <sys/uio.h>
    #include <sys/un.h>
    #include <sys/utsname.h>
    #include <sys/wait.h>
    #include <syslog.h>
    #include <tar.h>
    #include <termios.h>
    #include <tgmath.h>
    #include <time.h>
    #include <trace.h>
    #include <ulimit.h>
    #include <unistd.h>
    #include <utime.h>
    #include <utmpx.h>
    #include <wchar.h>
    #include <wctype.h>
    #include <wordexp.h>
    #endif

    #if OS_MAC
        #include <TargetConditionals.h>
        #if TARGET_IPHONE_SIMULATOR
             // iOS, tvOS, or watchOS Simulator
        #elif TARGET_OS_MACCATALYST
            // Mac's Catalyst (ports iOS API into Mac, like UIKit).
        #elif TARGET_OS_IPHONE
            // iOS, tvOS, or watchOS device
        #elif TARGET_OS_MAC
            // Other kinds of Apple platforms
        #else
            #   error "Unknown Apple platform"
        #endif  
    #endif
#endif
// C  freestanding
#include <float.h>
#include <iso646.h>
#include <limits.h>
#include <stdalign.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdnoreturn.h>
#include <assert.h>

#if USE_LIBC_MALLOC == 1
#include <iostream>
#include <string>
#endif


typedef int8_t S8;
typedef int16_t S16;
typedef int32_t S32;
typedef int64_t S64;
typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef float F32;
typedef double F64;

#define MFunctionWrap(S) do { S } while(0)

#if !defined(MAssertBreak)
#define MAssertBreak (*(int*)0  = 0)
#endif

#if ENABLE_ASSERT
    #define MAssert(c) MFunctionWrap( if(!(c)){MAssertBreak();})
#else
    #define MAssert(c)
#endif

#define MStringify_(S) #S
#define MStringify(S) MStringify_(S)
#define MGlue_(A,B) A##B
#define MGlue(A,B) MGlue_(A,B)

#define MArrayCount(a) (sizeof(a)/sizeof(*(a)))
#define IntFromPtr(p) (unsigned long long)((char*)p -(char*)0)
#define PtrFromInt(n) (void*) ((char*)0 + (n))

#define global static
#define local static
#define function static

#if OS_WINDOWS
    #define INV_HANDLE(x)       (((x) == NULL) || ((x) == INVALID_HANDLE_VALUE))
#endif
