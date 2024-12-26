// Time-stamp: <2009-03-29 19:32:15 geg>
//
// Copyright (C) 2009 Elian Gidoni <geg@gnu.org>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

namespace Yase2D
{

        enum Button {
                LEFT,
                MIDDLE,
                RIGHT,
                WHEELUP,
                WHEELDOWN,
                XPOS,
                YPOS,
                XREL,
                YREL,
                PRESSED_X,
                PRESSED_Y,
                RELEASED_X,
                RELEASED_Y,
                MOVED
        };

        typedef map<int, int> Mouse;
}
