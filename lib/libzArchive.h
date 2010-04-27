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
 *  @file lib/libzArchive.h internal directives for libzArchive.la
 */
#ifndef _ZARCHIVE_LIB_ZARCHIVE_H
#define _ZARCHIVE_LIB_ZARCHIVE_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <zArchive.h>

#include <inttypes.h>
#include <sys/types.h>


///////////////////
//               //
//  Definitions  //
//               //
///////////////////

#ifndef ZARCHIVE_LIBS_DYNAMIC
#define ZARCHIVE_LIBS_DYNAMIC 1
#endif

#ifndef PACKAGE_TARNAME
#define PACKAGE_TARNAME "zArchive"
#endif


///////////////////
//               //
//  i18l Support //
//               //
///////////////////

#ifdef HAVE_GETTEXT
#   include <gettext.h>
#   include <libintl.h>
#   define _(String) gettext (String)
#   define gettext_noop(String) String
#   define N_(String) gettext_noop (String)
#else
#   define _(String) (String)
#   define N_(String) String
#   define textdomain(Domain)
#   define bindtextdomain(Package, Directory)
#endif


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

#endif /* end of header file */
