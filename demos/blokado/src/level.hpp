// Time-stamp: <2009-03-29 19:38:22 geg>
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

#include <defines.hpp>
#include <block.hpp>
#include <menu.hpp>

using namespace Yase2D;
// FIXME: add game level aceleration.
class Level : public Scene
{
public:
        Level();
        void init();
        void finish ();
        Action update(vector<bool>& keys, Mouse& mouse,
                      unsigned int delta);
        void send_data (map<string,string>  data);


protected:
        unsigned int time, score, lines, trans_time, curr_limit;
        string player;
        Sprite * time_s[6], *lines_s[6], *score_s[6],
                *quit_dialog,*pause_dialog, *ready_dialog,
                *lose_dialog;
        int filled_count[18];
        vector<Sprite*> squares_by_line[18], dead_squares, blanks;
        Block * curr_block,*next_block;
        bool show_quit, show_pause, show_ready, show_gameover, showed_blanks;

        void kill_current ();
        void clean_and_next ();
        void move_dead_down (int line);
        void update_info ();
        void save_score ();
        void update_squares (vector<Sprite*>& in,vector<Sprite*>& out);

};


#endif // _LEVEL_HPP
