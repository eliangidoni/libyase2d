// Time-stamp: <2009-04-27 12:17:21 geg>
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


#include <character.hpp>


Character::Character(string s)
        : Sprite (s, false, 0,255,0)
{
        int x=1,y=1;
        add_clip_rect (1, 32,32, x, y);
        x+=33;
        add_clip_rect (2, 32,32, x, y);
        x+=33;
        add_clip_rect (3, 32,32, x, y);
        x+=33;
        add_clip_rect (4, 32,32, x, y);
        x+=33;
        add_clip_rect (5, 32,32, x, y);
        x+=33;
        add_clip_rect (6, 32,32, x, y);
        x+=33;
        add_clip_rect (7, 32,32, x, y);
        x+=33;
        add_clip_rect (8, 32,32, x, y);
        x+=33;
        add_clip_rect (9, 32,32, x, y);
        x+=33;
        add_clip_rect (10, 32,32, x, y);
        x+=33;

        y+=33;x=1;
        add_clip_rect (11, 32,32, x, y);
        x+=33;
        add_clip_rect (12, 32,32, x, y);
        x+=33;
        add_clip_rect (13, 32,32, x, y);
        x+=33;
        add_clip_rect (14, 32,32, x, y);
        x+=33;
        add_clip_rect (15, 32,32, x, y);
        x+=33;
        add_clip_rect (16, 32,32, x, y);
        x+=33;
        add_clip_rect (17, 32,32, x, y);
        x+=33;
        add_clip_rect (18, 32,32, x, y);
        x+=33;
        add_clip_rect (19, 32,32, x, y);
        x+=33;
        add_clip_rect (20, 32,32, x, y);

}


void Character::check_collision (vector<Sprite*> n)
{
        if (n.size() > 0)
        {
                set_x(origx);
                set_y(origy);
                xp = origx;
                yp = origy;
                tx = origx;
                ty = origy;
        }
}

void Character::set_dest (int x, int y)
{
        tx = x-16;
        ty = y-16;


        dir.set_x (tx-get_x());
        dir.set_y (ty-get_y());
        dir.normalize();
        float a= -dir.angle();

        if (a>45&&a<=135)
        {
                set_rect_id (states[gun][4].second);
                cur_state = states[gun][4].first;
        }
        else if (a<=-45 && a>=-135)
        {
                set_rect_id (states[gun][8].second);
                cur_state = states[gun][8].first;               
        }
        else if (a>135||a<-135)
        {
                set_rect_id (states[gun][10].second);
                cur_state = states[gun][10].first;
        }
        else
        {
                set_rect_id (states[gun][14].second);
                cur_state = states[gun][14].first;               
        }

}


Bill::Bill ()
        : Character (DATADIR "/sprites/bill.png")
{
        cur_state = 3;
        cur_dir = -1;
        gun = 0;
        delay = 0;

        // up
        states[0][1] = make_pair(2,10);
        states[0][2] = make_pair(3,9);
        states[0][3] = make_pair(4,8);
        states[0][4] = make_pair(1,9);
        // down
        states[0][5] = make_pair(6,2);
        states[0][6] = make_pair(7,3);
        states[0][7] = make_pair(8,1);
        states[0][8] = make_pair(5,3);
        // left
        states[0][9] = make_pair(10,5);
        states[0][10] = make_pair(9,4);
        // right
        states[0][13] = make_pair(14,7);
        states[0][14] = make_pair(13,6);

        set_rect_id(3);
}


void Bill::update (unsigned int dt)
{
}




Rms::Rms ()
        : Character (DATADIR "/sprites/rms.png")
{

        cur_dir = -1;
        gun = 0;
        delay = 0;
        xp=100,yp=100;
        tx=0,ty=0;

        // up
        states[0][1] = make_pair(2,10);
        states[0][2] = make_pair(3,9);
        states[0][3] = make_pair(4,8);
        states[0][4] = make_pair(1,9);
        // down
        states[0][5] = make_pair(6,2);
        states[0][6] = make_pair(7,3);
        states[0][7] = make_pair(8,1);
        states[0][8] = make_pair(5,3);
        // left
        states[0][9] = make_pair(10,5);
        states[0][10] = make_pair(9,4);
        // right
        states[0][13] = make_pair(14,7);
        states[0][14] = make_pair(13,6);

        cur_state = 5;
        set_rect_id(3);
        set_x(100);
        set_y(100);
        dir.set_x(0);
        dir.set_y(0);
}


void Rms::update (unsigned int dt)
{
        vector<Sprite*> cols;

        delay += dt;
        if (delay > 100 && tx != get_x() && ty != get_y())
        {
                delay = 0;
                set_rect_id (states[gun][cur_state].second);
                cur_state = states[gun][cur_state].first;
        }

        origx = get_x();
        origy = get_y();
        dir.set_x (tx-origx);
        dir.set_y (ty-origy);
        dir.normalize();       
        xp += dir.get_x();
        yp += dir.get_y();
        set_x (xp);
        set_y (yp);
}
