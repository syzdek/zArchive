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
typedef struct zarchive zArchive;

/// zArchive central directory file header
typedef struct zarchive_central_file zArchiveCentralFile;

/// zArchive central directory file header
typedef struct zarchive_disk zArchiveDisk;

/// zArchive local file header
typedef struct zarchive_local_file zArchiveLocalFile;


/////////////////
//             //
//  Structs    //
//             //
/////////////////

/// internal libzArchive.la state data
struct zarchive
{
   size_t flags;                ///< zArchive option flags
   size_t numOfDisks;           ///< number of disks in archive
   size_t numOfFiles;           ///< number of central directory file headers
   zArchiveCentralFile * files; ///< array of central directory file headers
   zArchiveDisk * disks;        ///< array of ZIP disks
};


/// zArchive end of central directory record
struct zarchive_disk
{
   // Zip end of central directory record
   size_t sig;                    ///< End of central directory signature = 0x06054b50
   size_t thisDiskNumber;         ///< Number of this disk
   size_t dirStartDisk;           ///< Disk where central directory starts
   size_t dirDiskRecordCount;     ///< Number of central directory records on this disk
   size_t totalDirRecords;        ///< Total number of central directory records
   size_t dirSize;                ///< Size of central directory (bytes)
   size_t dirOffset;              ///< Offset of start of central directory, relative to start of archive
   size_t commentLen;             ///< ZIP file comment length (n)
   size_t localCount;             ///< number of local files
   size_t centralCount;           ///< number of central directory records
   char                * comment;      ///< ZIP file comment
   zArchiveLocalFile   * localFiles;   ///< array of local files
   zArchiveCentralFile * centralFiles; ///< array of central directory records
};


/// zArchive central directory file header
struct zarchive_central_file
{
   size_t    sig;               ///< Central directory file header signature = 0x02014b50
   size_t    version;           ///< Version made by
   size_t    minVersion;        ///< Version needed to extract (minimum)
   size_t    flags;             ///< General purpose bit flag
   size_t    compressionMethod; ///< Compression method
   size_t    modTime;           ///< File last modification time
   size_t    modDate;           ///< File last modification date
   size_t    crc32;             ///< CRC-32
   size_t    compressSize;      ///< Compressed size
   size_t    uncompressSize;    ///< Uncompressed size
   size_t    nameLen;           ///< File name length (n)
   size_t    extraLen;          ///< Extra field length (m)
   size_t    commentLen;        ///< File comment length (k)
   size_t    diskNum;           ///< Disk number where file starts
   size_t    internalAttrs;     ///< Internal file attributes
   size_t    externalAttrs;     ///< External file attributes
   off_t     offset;            ///< Relative offset of local file header
   char    * name;              ///< File name
   char    * extra;             ///< Extra field
   char    * comment;           ///< File comment
};


/// zArchive local file header
struct zarchive_local_file
{
   size_t    sig;                 ///< Central directory file header signature = 0x02014b50
   size_t    version;             ///< Version made by
   size_t    minVersion;          ///< Version needed to extract (minimum)
   size_t    flags;               ///< General purpose bit flag
   size_t    compressionMethod;   ///< Compression method
   size_t    modTime;             ///< File last modification time
   size_t    modDate;             ///< File last modification date
   size_t    crc32;               ///< CRC-32
   size_t    compressSize;        ///< Compressed size
   size_t    uncompressSize;      ///< Uncompressed size
   size_t    nameLen;             ///< File name length (n)
   size_t    extraLen;            ///< Extra field length (m)
   char    * name;                ///< File name
   char    * extra;               ///< Extra field
   uint8_t * data;                ///< compressed data
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
