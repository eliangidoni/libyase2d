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

lib_LTLIBRARIES = libyase2d.la

libyase2d_la_SOURCES =  common.hpp keymap.hpp mouse.hpp \
			sprite.cpp sprite.hpp \
                        engine.cpp engine.hpp \
                        game.cpp game.hpp \
                        scene.cpp scene.hpp \
                        action.cpp action.hpp \
	                sound.cpp sound.hpp \
	                vector.cpp vector.hpp
#                        network.cpp

# iface version : rev : age
libyase2d_la_LDFLAGS = -version-info 0:1:0

include_HEADERS = yase2d.hpp

PUBLIC_HEADRS = common.hpp \
                vector.hpp \
                keymap.hpp \
                mouse.hpp \
                sound.hpp \
                sprite.hpp \
                action.hpp \
                scene.hpp \
                game.hpp \
                engine.hpp 
#                network.hpp

yase2d.hpp: $(PUBLIC_HEADRS)
	cat $(top_builddir)/gpl-header > $@
	echo "#ifndef _YASE2D_HPP" >> $@
	echo "#define _YASE2D_HPP" >> $@
	cat $^ >> $@
	echo "#endif // _YASE2D_HPP" >> $@

clean-local:
	rm -f $(srcdir)/yase2d.hpp

AM_LDFLAGS = $(SDL_LIBS)
AM_CXXFLAGS = -Wall -W -pedantic 
AM_CPPFLAGS = $(SDL_CFLAGS)
