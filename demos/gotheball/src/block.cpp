// Time-stamp: <2009-04-05 22:07:31 geg>
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

#include <block.hpp>

Block::Block()
        : Sprite(DATADIR "/sprites/block.png", false,255,0,255)
{
        add_clip_rect (1,40,20,4,4);
        add_clip_rect (2,40,20,48,4);
        add_clip_rect (3,40,20,92,4);
        add_clip_rect (4,40,20,136,4);
}


Block::~Block()
{
}


void Block::set_type (Type t)
{
        type = t;
        switch (type)
        {
                case SOFT:
                        set_rect_id (1);
                        break;
                case NORMAL:
                        set_rect_id (2);
                        break;
                case HARD:
                        set_rect_id (4);
                        break;
                case UNBREAKABLE:
                        set_rect_id (3);
                        break;
        }
}


Block::Type Block::get_type ()
{
        return type;
}
