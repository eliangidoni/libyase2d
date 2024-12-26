bin_PROGRAMS = gotheball

gotheball_SOURCES = main.cpp main.hpp \
                    menu.hpp menu.cpp \
                    gotheball.hpp gotheball.cpp \
                    level.hpp level.cpp \
                    paddle.hpp paddle.cpp \
                    block.hpp block.cpp \
                    ball.hpp ball.cpp \
                    defines.hpp 


AM_CPPFLAGS = -DDATADIR=\"$(pkgdatadir)\" -DHOMEDIR=\"$(HOME)\"
AM_LDFLAGS = -lyase2d
AM_CXXFLAGS = -Wall -W -pedantic