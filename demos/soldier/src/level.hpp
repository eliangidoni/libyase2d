// Time-stamp: <2009-04-27 11:58:46 geg>
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


#ifndef _LEVEL_HPP
#define _LEVEL_HPP

#include <yase2d.hpp>

#include <terrain.hpp>
#include <character.hpp>
#include <bullet.hpp>
#include <defines.hpp>
#include <menu.hpp>


using namespace Yase2D;

class Level : public Tile_scene
{
public:
        Level();
        void init();

        Action update(vector<bool>& keys, Mouse& mouse,
                      unsigned int delta);

protected:
        string player;
        int level[25][21], cur_level;
        Character* c;
        vector<Bullet*> bullets;

        bool load_next_level();
        void save_score ();
        void update_bullets (unsigned int dt);
};


#endif // _LEVEL_HPP
