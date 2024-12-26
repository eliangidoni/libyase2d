// Time-stamp: <2009-04-24 12:58:11 geg>
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


#include <terrain.hpp>


Terrain::Terrain()
        : Sprite (DATADIR "/sprites/terrain.png")
{
        int x=1,y=1;
        add_clip_rect (1, 32,32, x,y);
        x+=33;
        add_clip_rect (2, 32,32, x,y);
        x+=33;
        add_clip_rect (3, 32,32, x,y);
        x+=33;
        add_clip_rect (4, 32,32, x,y);
        x+=33;
        add_clip_rect (5, 32,32, x,y);
        x+=33;
        add_clip_rect (6, 32,32, x,y);
        x+=33;
        add_clip_rect (7, 32,32, x,y);
        x+=33;
        add_clip_rect (8, 32,32, x,y);

        x=1;y+=33;
        add_clip_rect (9, 32,32, x,y);
        x+=33;
        add_clip_rect (10, 32,32, x,y);
        x+=33;
        add_clip_rect (11, 32,32, x,y);
        x+=33;
        add_clip_rect (12, 32,32, x,y);
        x+=33;
        add_clip_rect (13, 32,32, x,y);
        x+=33;
        add_clip_rect (14, 32,32, x,y);
        x+=33;
        add_clip_rect (15, 32,32, x,y);
        x+=33;
        add_clip_rect (16, 32,32, x,y);

        x=1;y+=33;
        add_clip_rect (17, 32,32, x,y);
        x+=33;
        add_clip_rect (18, 32,32, x,y);
        x+=33;
        add_clip_rect (19, 32,32, x,y);
        x+=33;
        add_clip_rect (20, 32,32, x,y);
        x+=33;
        add_clip_rect (21, 32,32, x,y);
        x+=33;
        add_clip_rect (22, 32,32, x,y);
        x+=33;
        add_clip_rect (23, 32,32, x,y);
        x+=33;
        add_clip_rect (24, 32,32, x,y);

        x=1;y+=33;
        add_clip_rect (25, 32,32, x,y);
        x+=33;
        add_clip_rect (26, 32,32, x,y);
        x+=33;
        add_clip_rect (27, 32,32, x,y);
        x+=33;
        add_clip_rect (28, 32,32, x,y);
}


Terrain::~Terrain()
{
}


void Terrain::set_type(int type)
{
        if (type == 25)
                set_walkable(false);
        set_rect_id (type);
}
