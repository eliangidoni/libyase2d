bin_PROGRAMS = blokado

blokado_SOURCES = main.cpp main.hpp \
	          menu.cpp menu.hpp \
	          blokado.cpp blokado.hpp \
	          level.cpp level.hpp \
	          block.cpp block.hpp defines.hpp

AM_CPPFLAGS = -DDATADIR=\"$(pkgdatadir)\" -DHOMEDIR=\"$(HOME)\"
AM_LDFLAGS = -lyase2d
AM_CXXFLAGS = -Wall -W -pedantic