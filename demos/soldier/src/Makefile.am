bin_PROGRAMS = soldier

soldier_SOURCES = main.cpp main.hpp \
                    menu.hpp menu.cpp \
                    terrain.hpp terrain.cpp \
                    bullet.hpp bullet.cpp \
                    character.hpp character.cpp \
                    soldier.hpp soldier.cpp \
                    level.hpp level.cpp \
                    defines.hpp 


AM_CPPFLAGS = -DDATADIR=\"$(pkgdatadir)\" -DHOMEDIR=\"$(HOME)\"
AM_LDFLAGS = -lyase2d
AM_CXXFLAGS = -Wall -W -pedantic