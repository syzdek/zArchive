#
#   zArchive
#   Copyright (C) 2010 Bindle Binaries
#
#   @BINDLE_BINARIES_LICENSE_START@
#
#   This library is free software; you can redistribute it and/or
#   modify it under the terms of the GNU Lesser General Public
#   License as published by the Free Software Foundation; either
#   version 2.1 of the License, or (at your option) any later version.
#
#   This library is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public
#   License along with this library; if not, write to the Free Software
#   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110 USA
#
#   @BINDLE_BINARIES_LICENSE_END@
#
#   Makefile.am - automate compiling on a unix platform
#

# Sub directories
SUBDIRS					=
DIST_SUBDIRS				=


# Global flags
AM_LIBS					=
AM_LDFLAGS				=
AM_CFLAGS				= -O2 -W -Wall -Werror $(CFLAGS_WARNINGS)
AM_CXXFLAGS				= -O2 -W -Wall -Werror
AM_OBJCFLAGS				= -O2 -W -Wall -Werror
AM_CPPFLAGS				= -O2 -W -Wall -Werror -DHAVE_COMMON_H=1 -I$(top_builddir)/include -I$(top_srcdir)/include
ACLOCAL_AMFLAGS				= -I m4
DEFS					= -DLOCALEDIR="\"$(localedir)\"" @DEFS@


# automake targets
bin_PROGRAMS				= src/zArchive
include_HEADERS				=
lib_LTLIBRARIES				= lib/libzArchive.la
noinst_PROGRAMS				=
noinst_HEADERS				=
man_MANS				=


# macros for lib/libotadm.la
lib_libzArchive_la_DEPENDENCIES		= Makefile lib/libzArchive.sym
lib_libzArchive_la_CFLAGS		= $(AM_CFLAGS)
lib_libzArchive_la_LIBADD		= $(AM_LIBS)
lib_libzArchive_la_LDFLAGS		= -rpath '$(libdir)' \
					  -version-info $(LIB_VERSION_INFO) \
					  $(AM_LDFLAGS)
					  -export-symbols $(srcdir)/lib/libzArchive.sym
lib_libzArchive_la_SOURCES		= include/zArchive.h \
					  lib/libzArchive.h \
					  lib/libzArchive_memory.c \
					  lib/libzArchive_misc.c


# macros for src/zArchive
src_zArchive_DEPENDENCIES		= $(lib_LTLIBRARIES) Makefile
src_zArchive_CPPFLAGS			= -DPROGRAM_NAME="\"zArchive\"" $(AM_CPPFLAGS)
src_zArchive_LDADD			= $(AM_LDADD) lib/libzArchive.la
src_zArchive_SOURCES			= $(noinst_HEADERS) \
					  src/common.h \
					  src/zArchive.c


# lists
BUILT_SOURCES				=
TESTS					=
XFAIL_TESTS				=
EXTRA_DIST				= build-aux/LicenseHeader.txt \
					  build-aux/config.rpath \
					  lib/libzArchive.sym \
					  $(srcdir)/zArchive.xcodeproj/project.pbxproj
CLEANFILES				= \
					  $(builddir)/a.out   $(srcdir)/a.out \
					  $(builddir)/*/a.out $(srcdir)/*/a.out \
					  config.h.in~ $(srcdir)/config.h.in~ \
					  $(man_MANS) \
					  @PACKAGE_TARNAME@-*.tar.* \
					  @PACKAGE_TARNAME@-*.zip


# substitution routine
do_subst = sed \
	-e 's,[@]SHELL[@],@SHELL@,g' \
	-e 's,[@]PACKAGE_VERSION[@],@PACKAGE_VERSION@,g' \
	-e 's![@]PACKAGE_NAME[@]!@PACKAGE_NAME@!g' \
	-e 's,[@]PACKAGE_TARNAME[@],@PACKAGE_TARNAME@,g' \
	-e 's,[@]PACKAGE_BUGREPORT[@],@PACKAGE_BUGREPORT@,g' \
	-e 's|[@]PACKAGE_COPYRIGHT[@]|@PACKAGE_COPYRIGHT@|g' \
	-e 's,[@]LIB_VERSION_CURRENT[@],@LIB_VERSION_CURRENT@,g' \
	-e 's,[@]LIB_VERSION_REVISION[@],@LIB_VERSION_REVISION@,g' \
	-e 's,[@]LIB_VERSION_AGE[@],@LIB_VERSION_AGE@,g' \
	-e 's,[@]LIB_VERSION_INFO[@],@LIB_VERSION_INFO@,g' \
	-e 's,[@]LIB_RELEASE_INFO[@],@LIB_RELEASE_INFO@,g' \
	-e 's,[@]RELEASE_MONTH[@],@RELEASE_MONTH@,g'
do_subst_fn = \
		echo "do_subst < ${@}.in > ${@}"; \
		mkdir -p `dirname ${@}` || exit 1; \
		${do_subst} < $(srcdir)/${@}.in > ${@} || exit 1; \
		chmod 0755 ${@}
do_subst_dt = \
		echo "do_subst < ${@}.in > ${@}"; \
		mkdir -p `dirname ${@}` || exit 1; \
		${do_subst} < $(srcdir)/${@}.in > ${@} || exit 1; \
		chmod 0644 ${@}


# custom targets


# local targets
install-exec-local:

install-data-local: 

uninstall-local:

distclean-local:
	rm -fR $(srcdir)/autom4te.cache
	rm -fR $(srcdir)/doc/html

# end of automake file
