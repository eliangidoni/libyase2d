// Time-stamp: <2009-04-06 03:19:16 geg>
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

#include <ball.hpp>

Ball::Ball ()
        : Sprite(DATADIR "/sprites/block.png", false,255,0,255)
{
        add_clip_rect (1, 14,14,198,4);
        add_clip_rect (0, 14,14,180,4);
        moving = false;
        x = 0;
        y = 0;
        is_sticky = false;
        seeded = false;
        set_rand_dir();
}


Ball::~Ball ()
{
}


void Ball::update (unsigned int dt)
{
        if (moving)
        {
                x += speed.get_x();
                y -= speed.get_y();
                Sprite::set_x ((int)x);
                Sprite::set_y ((int)y);
        }
}


void Ball::block_dir (Sprite * neighbor)
{
        int left2,top2,right2,bottom2;

        // restore position
        while (collide_neighbor(neighbor))
        {
                x -= speed.get_x();
                y += speed.get_y();
                Sprite::set_x ((int)x);
                Sprite::set_y ((int)y);
        }

        left2=neighbor->get_left();
        top2=neighbor->get_top();
        bottom2=neighbor->get_bottom();
        right2=neighbor->get_right();

        // collide left
        if (left <= left2 && right <= left2)
                speed.negate_x();
        // collide right
        else if (right2 <= left && right2 <= right)
                speed.negate_x();
        // collide top/bottom
        else
                speed.negate_y();
}


void Ball::paddle_dir (Sprite * neighbor)
{
        int factor;

        // restore position
        while (collide_neighbor(neighbor))
        {
                x -= speed.get_x();
                y += speed.get_y();
                Sprite::set_x ((int)x);
                Sprite::set_y ((int)y);
        }

        factor = neighbor->get_right() - left;
        speed.negate_y();
        speed.normalize();
        // right direction
        if (factor < 49)
                speed.rotate(-(49-factor));
        // left direction
        else if (factor > 49)
                speed.rotate((factor-49));

        if (speed.angle() < 30)
        {
                speed.nullify();
                speed.rotate(30);
        }else if (speed.angle() > 150){
                speed.nullify();
                speed.rotate(150);
        }
        speed*=2;

}


void Ball::screen_dir (Sprite::Screen scr)
{
        switch (scr)
        {
                case Sprite::SCR_TOP:
                case Sprite::SCR_BOTTOM:
                        speed.negate_y();
                        break;
                case Sprite::SCR_LEFT:
                case Sprite::SCR_RIGHT:
                        speed.negate_x();
                        break;
                case Sprite::SCR_BOTLEFT:
                case Sprite::SCR_TOPRIGHT:
                case Sprite::SCR_TOPLEFT:
                case Sprite::SCR_BOTRIGHT:
                        speed.negate_x();
                        speed.negate_y();
                        break;
        }
}


void Ball::play ()
{
        moving = true;
}


void Ball::sticky ()
{
        is_sticky = !is_sticky;
        if (is_sticky)
                set_rect_id (1);
        else
                set_rect_id (0);
}


void Ball::stop ()
{
        moving = false;
        set_rand_dir ();
}


void Ball::set_rand_dir ()
{
        if (!seeded)
        {
                srand(time(NULL));
                seeded=true;
        }
        speed.nullify();
        speed.rotate(rand()%120+30);
        speed *= 2;
}


void Ball::set_x(int x)
{
        Sprite::set_x(x);
        this->x = x;
}


void Ball::set_y(int y)
{
        Sprite::set_y(y);
        this->y = y;
}
