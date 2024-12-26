// Time-stamp: <2009-03-30 03:39:23 geg>
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

#include <paddle.hpp>


Paddle::Paddle()
        : Sprite(DATADIR "/sprites/block.png", 255,0,255)
{
        add_clip_rect (0,84,14,4,28);
}


void Paddle::move (Sprite::Direction dir)
{
        Sprite::Direction opp=NONE;

        Sprite::move (dir, 3);
        switch (dir)
        {
                case RIGHT:
                        opp = LEFT;
                        break;
                case LEFT:
                        opp = RIGHT;
                        break;
                default:
                        break;
        }

        if (collide_screen (640,480) != Sprite::SCR_NONE)
                while (collide_screen (640,480) != Sprite::SCR_NONE)
                        Sprite::move(opp,1);
}


Paddle::~Paddle()
{
}
