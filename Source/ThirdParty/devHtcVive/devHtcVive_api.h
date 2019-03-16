
#ifndef DEVHTCVIVE_API_H
#define DEVHTCVIVE_API_H

#ifdef DEVHTCVIVE_STATIC_DEFINE
#  define DEVHTCVIVE_API
#  define DEVHTCVIVE_NO_EXPORT
#else
#  ifndef DEVHTCVIVE_API
#    ifdef devHtcVive_EXPORTS
        /* We are building this library */
#      define DEVHTCVIVE_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define DEVHTCVIVE_API __declspec(dllimport)
#    endif
#  endif

#  ifndef DEVHTCVIVE_NO_EXPORT
#    define DEVHTCVIVE_NO_EXPORT 
#  endif
#endif

#ifndef DEVHTCVIVE_DEPRECATED
#  define DEVHTCVIVE_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef DEVHTCVIVE_DEPRECATED_EXPORT
#  define DEVHTCVIVE_DEPRECATED_EXPORT DEVHTCVIVE_API DEVHTCVIVE_DEPRECATED
#endif

#ifndef DEVHTCVIVE_DEPRECATED_NO_EXPORT
#  define DEVHTCVIVE_DEPRECATED_NO_EXPORT DEVHTCVIVE_NO_EXPORT DEVHTCVIVE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef DEVHTCVIVE_NO_DEPRECATED
#    define DEVHTCVIVE_NO_DEPRECATED
#  endif
#endif

#endif
