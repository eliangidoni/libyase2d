// Time-stamp: <2009-03-29 19:38:06 geg>
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


#ifndef _BLOCK_HPP
#define _BLOCK_HPP

#include <yase2d.hpp>

using namespace Yase2D;

class Block
{
public:
        struct Lines {int square[4];};
        Block ();
        ~Block(){}

        Sprite::Screen collide_screen ();
        bool collide_neighbors (vector<Sprite*>& neighbors);

        void next_position();
        void play_position();

        void rotate (vector<Sprite*>& neighbors);
        void move_bottom(vector<Sprite*>& neighbors);
        bool move_down(vector<Sprite*>& neighbors);
        bool move_up(vector<Sprite*>& neighbors);
        void move_left(vector<Sprite*>& neighbors);
        void move_right(vector<Sprite*>& neighbors);

        // return line occupied by each square starting at '0'.
        Lines get_lines ();

        vector<Sprite*> get_squares();
        vector<Sprite*> get_out_squares();

        static Sprite * blank_square ();

protected:
        Sprite * squares[4];
        int center_x,center_y, type;

        static bool seeded;
        static int positions[7][10];
};







#endif // _BLOCK_HPP
