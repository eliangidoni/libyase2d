// Time-stamp: <2009-04-21 22:51:01 geg>
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


#include <main.hpp>

int main ()
{
        Game *b=new Soldier;
        Engine e;
        e.set_resolution(640,480,16,false);
        e.set_fps (100);
        e.enable_sound ();
        e.run(b,"Go the ball");
}
