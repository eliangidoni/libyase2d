# Copyright (C) 2009 Elian Gidoni <geg@gnu.org>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

AC_INIT([Yase2d], [trunk], [geg@gnu.org], [libyase2d])
AC_PREREQ([2.61])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

AC_PROG_CXX

AC_PROG_LIBTOOL

AC_CANONICAL_HOST
canonical_host=$host

# check for sdl
AM_PATH_SDL([1.2.11],, [AC_MSG_ERROR([couldn't find the SDL library.])])

# check for sdl image
AC_CHECK_HEADER([SDL/SDL_image.h],,
                AC_MSG_ERROR([couldn't find the SDL Image library.]))
AC_CHECK_LIB([SDL_image], [IMG_Load],,
             AC_MSG_ERROR([couldn't find the SDL Image library.]))

# check for sdl mixer
AC_CHECK_HEADER([SDL/SDL_mixer.h],,
                AC_MSG_ERROR([couldn't find the SDL Mixer library.]))
AC_CHECK_LIB([SDL_mixer], [Mix_OpenAudio],,
             AC_MSG_ERROR([couldn't find the SDL Mixer library.]))

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
