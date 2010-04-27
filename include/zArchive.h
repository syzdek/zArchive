/*
 *  zArchive
 *  Copyright (C) 2010 Bindle Binaries
 *
 *  @BINDLE_BINARIES_LICENSE_START@
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110 USA
 *
 *  @BINDLE_BINARIES_LICENSE_END@
 */
/**
 *  @file lib/zArchive.h defines API for libzArchive.la
 */
#ifndef _ZARCHIVE_H
#define _ZARCHIVE_H 1

//////////////
//          //
//  Macros  //
//          //
//////////////

/*
 * The macros "BEGIN_C_DECLS" and "END_C_DECLS" are taken verbatim
 * from section 7.1 of the Libtool 1.5.14 manual.
 */
/* BEGIN_C_DECLS should be used at the beginning of your declarations,
   so that C++ compilers don't mangle their names. Use END_C_DECLS at
   the end of C declarations. */
#undef BEGIN_C_DECLS
#undef END_C_DECLS
#if defined(__cplusplus) || defined(c_plusplus)
#   define BEGIN_C_DECLS  extern "C" {    ///< exports as C functions
#   define END_C_DECLS    }               ///< exports as C functions
#else
#   define BEGIN_C_DECLS  /* empty */     ///< exports as C functions
#   define END_C_DECLS    /* empty */     ///< exports as C functions
#endif


/*
 * The macro "PARAMS" is taken verbatim from section 7.1 of the
 * Libtool 1.5.14 manual.
 */
/* PARAMS is a macro used to wrap function prototypes, so that
   compilers that don't understand ANSI C prototypes still work,
   and ANSI C compilers can issue warnings about type mismatches. */
#undef PARAMS
#if defined (__STDC__) || defined (_AIX) \
        || (defined (__mips) && defined (_SYSTYPE_SVR4)) \
        || defined(WIN32) || defined (__cplusplus)
# define PARAMS(protos) protos   ///< wraps function arguments in order to support ANSI C
#else
# define PARAMS(protos) ()       ///< wraps function arguments in order to support ANSI C
#endif


/*
 * The following macro is taken verbatim from section 5.40 of the GCC
 * 4.0.2 manual.
 */
#if __STDC_VERSION__ < 199901L
# if __GNUC__ >= 2
# define __func__ __FUNCTION__
# else
# define __func__ "<unknown>"
# endif
#endif


// Exports function type
#ifdef WIN32
#   ifdef ZARCHIVE_LIBS_DYNAMIC
#      define ZARCHIVE_F(type)   extern __declspec(dllexport) type   ///< used for library calls
#      define ZARCHIVE_V(type)   extern __declspec(dllexport) type   ///< used for library calls
#   else
#      define ZARCHIVE_F(type)   extern __declspec(dllimport) type   ///< used for library calls
#      define ZARCHIVE_V(type)   extern __declspec(dllimport) type   ///< used for library calls
#   endif
#else
#   ifdef ZARCHIVE_LIBS_DYNAMIC
#      define ZARCHIVE_F(type)   type                                ///< used for library calls
#      define ZARCHIVE_V(type)   type                                ///< used for library calls
#   else
#      define ZARCHIVE_F(type)   extern type                         ///< used for library calls
#      define ZARCHIVE_V(type)   extern type                         ///< used for library calls
#   endif
#endif


///////////////
//           //
//  Headers  //
//           //
///////////////

#include <inttypes.h>
#include <sys/types.h>


/////////////////
//             //
//  Datatypes  //
//             //
/////////////////

/// internal libzArchive.la state data
typedef struct zarchive_data zArchive;


/////////////////
//             //
//  Structs    //
//             //
/////////////////

/// internal libzArchive.la state data
struct zarchive_data
{
   size_t   count_files;   ///< number of files in archive
};


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
BEGIN_C_DECLS

// frees memory from zArchive
ZARCHIVE_F(void) zarchive_free PARAMS((zArchive * zd));

// initializes memory for zArchive
ZARCHIVE_F(zArchive *) zarchive_init PARAMS((void));

// resets the state of the zArchive
ZARCHIVE_F(void) zarchive_reset PARAMS((zArchive * zd));

END_C_DECLS
#endif /* end of header file */
