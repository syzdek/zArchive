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

#endif /* end of header file */
