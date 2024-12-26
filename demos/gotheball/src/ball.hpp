// Time-stamp: <2009-04-01 01:42:06 geg>
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

#ifndef _BALL_HPP
#define _BALL_HPP

#include <yase2d.hpp>

using namespace Yase2D;
class Ball : public Sprite
{
public:
        Ball ();
        ~Ball ();

        void update (unsigned int dt);

        void block_dir (Sprite * neighbor);
        void paddle_dir (Sprite * neighbor);
        void screen_dir (Sprite::Screen scr);

        void set_x(int x);
        void set_y(int y);

        void play ();
        void stop ();
        void sticky ();

protected:
        bool moving, is_sticky, seeded;
        Vector speed, position;
        float x,y;

        void set_rand_dir();
};

#endif // _BALL_HPP
