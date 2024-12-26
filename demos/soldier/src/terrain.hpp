// Time-stamp: <2009-04-24 12:57:12 geg>
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


#ifndef _TERRAIN_HPP
#define _TERRAIN_HPP

#include <yase2d.hpp>
#include <level.hpp>
#include <menu.hpp>

using namespace Yase2D;
class Terrain : public Sprite
{
public:

        Terrain();
        ~Terrain();

        void set_type (int type);

protected:
        
};

#endif // _TERRAIN_HPP
