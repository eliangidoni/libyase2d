// Time-stamp: <2009-04-27 11:58:42 geg>
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


#ifndef _CHARACTER_HPP
#define _CHARACTER_HPP

#include <yase2d.hpp>

#include <menu.hpp>

using namespace Yase2D;
class Character : public Sprite
{
public:
        Character(string s);
        void set_dest (int x, int y);
        void check_collision (vector<Sprite*> n);
protected:
        int cur_state,gun,cur_dir,delay,tx,ty,origx,origy;
        vector<Sprite*> neighbors;
        map<int, pair<int, int> > states[2];
        float xp,yp;
        Vector dir;
};

class Rms : public Character
{
public:
        Rms();
        void update (unsigned int dt);
protected:
};

class Bill : public Character
{
public:
        Bill();
        void update (unsigned int dt);
protected:
};


#endif // _CHARACTER_HPP
