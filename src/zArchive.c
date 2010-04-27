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
 *  @file src/zArchive.c Utility for interacting with Zip files.
 */
/*
 *  Simple Build:
 *     gcc -W -Wall -O2 -c zArchive.c
 *     gcc -W -Wall -O2 -o zArchive   zArchive.o
 *
 *  GNU Libtool Build:
 *     libtool --mode=compile gcc -W -Wall -g -O2 -c zArchive.c
 *     libtool --mode=link    gcc -W -Wall -g -O2 -o zArchive zArchive.lo
 *
 *  GNU Libtool Install:
 *     libtool --mode=install install -c zArchive /usr/local/bin/zArchive
 *
 *  GNU Libtool Clean:
 *     libtool --mode=clean rm -f zArchive.lo zArchive
 */
#define _ZARCHIVE_SRC_ZARCHIVE_C 1

///////////////
//           //
//  Headers  //
//           //
///////////////

#ifdef HAVE_COMMON_H
#include "common.h"
#endif

#include <zArchive.h>

#include <stdio.h>
#include <getopt.h>
#include <errno.h>


///////////////////
//               //
//  Definitions  //
//               //
///////////////////

#ifndef PROGRAM_NAME
#define PROGRAM_NAME "zArchive"
#endif


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

// main statement
int main PARAMS((int argc, char * argv[]));

// displays usage
void zarchive_usage PARAMS((void));

// displays version information
void zarchive_version PARAMS((void));


/////////////////
//             //
//  Functions  //
//             //
/////////////////

/// main statement
/// @param[in]  argc  number of arguments passed to program
/// @param[in]  argv  array of arguments passed to program
int main(int argc, char * argv[])
{
   int           c;
   int           opt_index;
   zArchive    * zd;

   static char   short_opt[] = "hqvV";
   static struct option long_opt[] =
   {
      {"help",          no_argument, 0, 'h'},
      {"silent",        no_argument, 0, 'q'},
      {"quiet",         no_argument, 0, 'q'},
      {"verbose",       no_argument, 0, 'v'},
      {"version",       no_argument, 0, 'V'},
      {NULL,            0,           0, 0  }
   };

   opt_index          = 0;

   if (!(zd = zarchive_init()))
   {
      perror("zarchive_init()");
      return(1);
   };

   while((c = getopt_long(argc, argv, short_opt, long_opt, &opt_index)) != -1)
   {
      switch(c)
      {
         case -1:	/* no more arguments */
         case 0:	/* long options toggles */
            break;
         case 'h':
            zarchive_usage();
            zarchive_free(zd);
            return(0);
         case 'q':
            break;
         case 'V':
            zarchive_version();
            zarchive_free(zd);
            return(0);
         case 'v':
            break;
         case '?':
            fprintf(stderr, _("Try `%s --help' for more information.\n"), PROGRAM_NAME);
            return(1);
         default:
            fprintf(stderr, _("%s: unrecognized option `--%c'\n"
                  "Try `%s --help' for more information.\n"
               ),  PROGRAM_NAME, c, PROGRAM_NAME
            );
            zarchive_free(zd);
            return(1);
      };
   };

   zarchive_free(zd);

   return(0);
}


/// displays usage
void zarchive_usage(void)
{
   // TRANSLATORS: The following strings provide usage for command. These
   // strings are displayed if the program is passed `--help' on the command
   // line. The two strings referenced are: PROGRAM_NAME, and
   // PACKAGE_BUGREPORT
   printf(_("Usage: %s [OPTIONS]\n"
         "  -h, --help                print this help and exit\n"
         "  -q, --quiet, --silent     do not print messages\n"
         "  -v, --verbose             print verbose messages\n"
         "  -V, --version             print version number and exit\n"
         "\n"
         "Report bugs to <%s>.\n"
      ), PROGRAM_NAME, PACKAGE_BUGREPORT
   );
   return;
}


/// displays version information
void zarchive_version(void)
{
   // TRANSLATORS: The following strings provide version and copyright
   // information if the program is passed --version on the command line.
   // The three strings referenced are: PROGRAM_NAME, PACKAGE_NAME,
   // PACKAGE_VERSION.
   printf(_("%s (%s) %s\n"
         "Written by Bindle Binaries.\n"
         "\n"
         "%s\n"
         "This is free software; see the source for copying conditions.  There is NO\n"
         "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"
      ), PROGRAM_NAME, PACKAGE_NAME, PACKAGE_VERSION, PACKAGE_COPYRIGHT
   );
   return;
}

/* end of source file */
