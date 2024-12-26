// Time-stamp: <2009-04-27 12:24:53 geg>
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


#include <bullet.hpp>


Bullet::Bullet()
        : Sprite (DATADIR "/sprites/bullets.png", false, 0,255,0)
{
        add_clip_rect (0, 4,8, 1, 1);
        add_clip_rect (1, 2,2, 6, 1);
        set_rect_id (1);
        time =0;
}


void Bullet::set_dir (int tx, int ty)
{
        dir.set_x(tx-get_x());
        dir.set_y(ty-get_y());
        dir.normalize();
        x = get_x();
        y = get_y();
}


void Bullet::update (unsigned int dt)
{
        x += dir.get_x();
        y += dir.get_y();
        set_x(x);
        set_y(y);
        time += dt;
}


bool Bullet::is_dead ()
{
        if (time > 1000)
                return true;
        return false;
}

Bullet::~Bullet()
{
}
