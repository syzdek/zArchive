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
 *  @file lib/zArchive_memory.c functions for querying information about the library 
 */
#define _ZARCHIVE_LIB_ZARCHIVE_MEMORY_C 1
#include "libzArchive_memory.h"

///////////////
//           //
//  Headers  //
//           //
///////////////

#include "libzArchive.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>


/////////////////
//             //
//  Functions  //
//             //
/////////////////

/// frees memory from zArchive
/// @param[in]  zd     pointer to archive state
void zarchive_free(zArchive * zd)
{
   free(zd);
   return;
}


/// initializes memory for zArchive
zArchive * zarchive_init(void)
{
   zArchive * zd;

   if (!(zd = malloc(sizeof(zArchive))))
   {
      errno = ENOMEM;
      return(NULL);
   };
   memset(zd, 0, sizeof(zArchive));

   return(zd);
}


/// resets the state of the zArchive
/// @param[in]  zd     pointer to archive state
void zarchive_reset(zArchive * zd)
{
   memset(zd, 0, sizeof(zArchive));
   return;
}

/* end of source code */
