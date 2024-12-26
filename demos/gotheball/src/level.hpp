// Time-stamp: <2009-03-29 19:41:28 geg>
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

#include <ball.hpp>
#include <block.hpp>
#include <paddle.hpp>
#include <defines.hpp>
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
        unsigned int score, trans_time, lives, left_blocks, cur_level;
        Ball * ball;
        Paddle *paddle;
        string player;
        Sprite * score_s[6], *level_s[2], *quit_dialog,*pause_dialog,
                *ready_dialog, *lose_dialog, *win_dialog, *back,*lives_s[3];
        vector<Sprite*> blocks;
        bool show_quit, show_pause, show_ready, show_gameover,show_win, playing;
        int level[16][16];

        bool load_next_level ();
        void update_info ();
        void manage_collisions ();
        void save_score ();
};


#endif // _LEVEL_HPP
