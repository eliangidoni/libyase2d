// Time-stamp: <2009-04-21 22:50:45 geg>
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


#include <soldier.hpp>


Soldier::Soldier()
{
}


Soldier::~Soldier()
{
}


void Soldier::init ()
{
        add_scene (LEVEL, new Level (), 640,480,false);
        load_scene (LEVEL);
}
