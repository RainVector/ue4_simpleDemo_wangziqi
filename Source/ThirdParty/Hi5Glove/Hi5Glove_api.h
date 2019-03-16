
#ifndef HI5GLOVE_API_H
#define HI5GLOVE_API_H

#ifdef HI5GLOVE_STATIC_DEFINE
#  define HI5GLOVE_API
#  define HI5GLOVE_NO_EXPORT
#else
#  ifndef HI5GLOVE_API
#    ifdef Hi5Glove_EXPORTS
        /* We are building this library */
#      define HI5GLOVE_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define HI5GLOVE_API __declspec(dllimport)
#    endif
#  endif

#  ifndef HI5GLOVE_NO_EXPORT
#    define HI5GLOVE_NO_EXPORT 
#  endif
#endif

#ifndef HI5GLOVE_DEPRECATED
#  define HI5GLOVE_DEPRECATED __declspec(deprecated)
#endif

#ifndef HI5GLOVE_DEPRECATED_EXPORT
#  define HI5GLOVE_DEPRECATED_EXPORT HI5GLOVE_API HI5GLOVE_DEPRECATED
#endif

#ifndef HI5GLOVE_DEPRECATED_NO_EXPORT
#  define HI5GLOVE_DEPRECATED_NO_EXPORT HI5GLOVE_NO_EXPORT HI5GLOVE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef HI5GLOVE_NO_DEPRECATED
#    define HI5GLOVE_NO_DEPRECATED
#  endif
#endif

#endif
