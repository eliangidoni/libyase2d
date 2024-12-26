// Time-stamp: <2009-04-06 03:21:16 geg>
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


#include <level.hpp>

Level::Level()
{
        for (unsigned int i=0;i<18;i++)
                filled_count[i]=0;
        curr_block = NULL;
}




void Level::init ()
{
        Sprite *s;
        vector<Sprite*> q;
        Block*b;

        s = new Sprite(DATADIR "/sprites/background.png");
        s->add_clip_rect(0,540,480,0,0);
        register_sprite (s);

        lose_dialog = new Sprite(DATADIR "/sprites/lose.png",true);
        pause_dialog = new Sprite(DATADIR "/sprites/pause.png",true);
        quit_dialog = new Sprite(DATADIR "/sprites/quitmenu.png",true);
        ready_dialog = new Sprite(DATADIR "/sprites/ready.png",true);

        lose_dialog->add_clip_rect(0, 138, 31, 0, 0);
        pause_dialog->add_clip_rect(0, 91, 31, 0, 0);
        quit_dialog->add_clip_rect(0, 301, 34, 0, 0);
        ready_dialog->add_clip_rect(0, 134, 32, 0, 0);

        register_sprite (ready_dialog,2);

        pause_dialog->set_x (200);
        pause_dialog->set_y (200);
        quit_dialog->set_x (150);
        quit_dialog->set_y (200);
        ready_dialog->set_x (200);
        ready_dialog->set_y (200);
        lose_dialog->set_x (200);
        lose_dialog->set_y (200);

        b = new Block();
        q=b->get_squares();
        for (unsigned int i=0; i<q.size();i++)
                register_sprite(q[i],1);
        curr_block = b;

        next_block = new Block();
        next_block->next_position();
        q=next_block->get_squares();
        for (unsigned int i=0; i<q.size();i++)
                register_sprite(q[i],1);

        time = 0;
        curr_limit = 1000;
        trans_time = 0;
        score = 0;
        lines = 0;
        show_quit = false;
        show_pause = false;
        show_ready = true;
        show_gameover = false;
        showed_blanks = false;
        
        player = "";
        int x=390;
        for (unsigned int i=0; i<player.size();i++)
        {
                s = new Font (player[i], x, 410);
                x+=12;
                register_sprite(s,1);
        }

        x=414;
        for (unsigned int i=0;i<6;i++)
        {
                score_s[i] = new Number (0,x,324);
                register_sprite (score_s[i],1);
                lines_s[i] = new Number (0,x,283);
                register_sprite (lines_s[i],1);
                time_s[i] = new Number (0,x,239);
                register_sprite (time_s[i],1);
                x+=12;
        }

        Sound::load_effect (0, DATADIR "/sounds/line.ogg");
        Sound::load_effect (1, DATADIR "/sounds/fall.ogg");
        Sound::load_effect (2, DATADIR "/sounds/blank.ogg");
        Sound::volume_effect (1, 10);
        Sound::volume_effect (0, 30);
        Sound::volume_effect (2, 30);

}


Action Level::update(vector<bool>& keys, Mouse& mouse,
                     unsigned int delta)
{
        Action action;
        vector<Sprite*> out,in;

        if (show_ready)
        {
                action.delay(500, ready_dialog);
                show_ready = false;
        }
        else if (show_gameover)
        {
                trans_time += delta;
                if (trans_time >= 2000)
                {
                        save_score();
                        action.next(SCORE_MENU);
                        Sound::halt_music();
                        Sound::play_music (0,-1, 2000);

                        return action;
                }

        }
        else if (show_quit)
        {
                if (keys[KEY_y])
                {
                        remove_foreground();
                        save_score();
                        action.next(SCORE_MENU);
                        Sound::halt_music();
                        Sound::play_music (0,-1, 2000);

                        return action;
                }
                if (keys[KEY_n])
                {
                        show_quit = false;
                        unregister_sprite (quit_dialog);
                        remove_foreground();
                }
        }
        else if (show_pause)
        {
                if (keys[KEY_p])
                {
                        show_pause = false;
                        unregister_sprite (pause_dialog);
                        remove_foreground();
                }
        }
        else
        {
                if (showed_blanks)
                {
                        clean_and_next();
                        showed_blanks = false;
                        Sound::play_effect (0);
                }

                if (keys[KEY_ESCAPE])
                {
                        show_quit = true;
                        register_sprite (quit_dialog,2);
                        put_foreground(40,40,20,80,2);
                        return action;

                }

                if (keys[KEY_p])
                {
                        show_pause = true;
                        register_sprite (pause_dialog,2);
                        put_foreground(40,40,20,80,2);
                        return action;
                }

                trans_time += delta;

                if (keys[KEY_DOWN])
                {
                        out=curr_block->get_out_squares();
                        in=curr_block->get_squares();
                        curr_block->move_down(dead_squares);
                        update_squares (in, out);
                }
                if (keys[KEY_UP])
                {
                        out=curr_block->get_out_squares();
                        in=curr_block->get_squares();
                        curr_block->rotate(dead_squares);
                        update_squares (in,out);
                }
                if (keys[KEY_LEFT])
                        curr_block->move_left(dead_squares);
                if (keys[KEY_RIGHT])
                        curr_block->move_right(dead_squares);


                if (keys[KEY_SPACE])
                {
                        out=curr_block->get_out_squares();
                        in=curr_block->get_squares();
                        curr_block->move_bottom(dead_squares);
                        update_squares (in,out);
                        kill_current();
                        Sound::play_effect(1);
                }
                else if (trans_time >= curr_limit)
                {
                        out=curr_block->get_out_squares();
                        in=curr_block->get_squares();

                        if (curr_block->move_down(dead_squares))
                        {

                                kill_current();
                                Sound::play_effect(1);
                        }
                        else
                        {
                                update_squares (in,out);
                        }
                        trans_time = 0;
                        time++;
                }

                if (showed_blanks)
                {
                        action.delay(1000);
                        trans_time = 0;
                        Sound::play_effect (2);
                }

                update_info();
        }

        return action;
}


void Level::update_squares (vector<Sprite*>& in,vector<Sprite*>& out)
{
        vector<Sprite*> q;
        vector<Sprite*>::iterator itr;

        q=curr_block->get_squares();
        for (unsigned int i=0; i<out.size();i++)
        {
                itr = find (q.begin(),q.end(), out[i]);
                if (itr != q.end())
                        register_sprite(out[i],1);
        }
        q=curr_block->get_out_squares();
        for (unsigned int i=0; i<q.size();i++)
        {
                itr = find (in.begin(),in.end(), q[i]);
                if (itr != in.end())
                        unregister_sprite(q[i]);
        }

}

void Level::kill_current ()
{
        vector<Sprite*>::iterator it;
        Sprite * b;
        Block::Lines l;
        vector<Sprite*> q;

        q = curr_block->get_squares();
        l = curr_block->get_lines();
        for (unsigned int i=0; i<q.size(); i++)
        {
                dead_squares.push_back (q[i]);
                filled_count[l.square[i]]++;
                squares_by_line[l.square[i]].push_back(q[i]);
        }

        if (filled_count[0] > 0)
        {
                show_gameover = true;
                register_sprite (lose_dialog,2);
                return;
        }

        for (int i=17; i>=0; i--)
        {
                if (filled_count[i]==11)
                {
                        it = squares_by_line[i].begin();
                        while (it != squares_by_line[i].end())
                        {
                                b = Block::blank_square();
                                b->set_x((*it)->get_x());
                                b->set_y((*it)->get_y());
                                blanks.push_back (b);
                                register_sprite(b,3);
                                it++;
                        }
                        showed_blanks = true;
                }
        }

        if (!showed_blanks)
        {
                delete curr_block;
                curr_block = next_block;
                curr_block->play_position();
                q=curr_block->get_out_squares();
                for (unsigned int i=0; i<q.size();i++)
                        unregister_sprite(q[i]);

                next_block = new Block();
                next_block->next_position();
                q=next_block->get_squares();
                for (unsigned int i=0; i<q.size();i++)
                        register_sprite(q[i],1);

        }
}


void Level::clean_and_next ()
{
        vector<Sprite*> q;
        bool repeat=true;

        vector<Sprite*>::iterator it;
        for (it = blanks.begin(); it!=blanks.end(); it++)
                unregister_sprite (*it);
        blanks.clear();

        while (repeat)
        {
                repeat=false;
                for (int i=17; i>=0; i--)
                {
                        if (filled_count[i]==11)
                        {
                                move_dead_down(i);
                                lines++;
                                if (lines%8 == 0 && curr_limit > 100)
                                        curr_limit -= 20;
                                score += lines;
                                repeat=true;
                                break;
                        }
                }
        }


        delete curr_block;
        curr_block = next_block;
        curr_block->play_position();
        q=curr_block->get_out_squares();
        for (unsigned int i=0; i<q.size();i++)
                unregister_sprite(q[i]);

        next_block = new Block();
        next_block->next_position();
        q=next_block->get_squares();
        for (unsigned int i=0; i<q.size();i++)
                register_sprite(q[i],1);
}


void Level::move_dead_down (int line)
{
        vector<Sprite*>::iterator it=squares_by_line[line].begin(), square;
        while (it != squares_by_line[line].end())
        {
                square = find (dead_squares.begin(),dead_squares.end(),*it);
                if (square != dead_squares.end())
                        dead_squares.erase(square);
                unregister_sprite(*it);
                delete *it;
                it++;
        }

        for (unsigned int i=line; i>0; i--)
        {
                squares_by_line[i] = squares_by_line[i-1];
                filled_count[i] = filled_count[i-1];
                it=squares_by_line[i].begin();
                while (it != squares_by_line[i].end())
                {
                        (*it)->move(Sprite::DOWN, 24);
                        it++;
                }
        }
}


void Level::update_info ()
{
        stringstream st,ss,sl;
        string timestr,linestr,scorestr;
        st.fill('0');
        st.width(6);
        ss.fill('0');
        ss.width(6);
        sl.fill('0');
        sl.width(6);

        st << time;
        timestr = st.str();
        ss << score;
        scorestr = ss.str();
        sl << lines;
        linestr = sl.str();
        int x=414;
        for (unsigned int i=0;i<6;i++)
        {
                unregister_sprite (score_s[i]);
                unregister_sprite (lines_s[i]);
                unregister_sprite (time_s[i]);
                delete score_s[i];
                delete time_s[i];
                delete lines_s[i];
                score_s[i] = new Number (scorestr[i]-48, x,324);
                lines_s[i] = new Number (linestr[i]-48, x,283);
                time_s[i] = new Number (timestr[i]-48, x,239);
                register_sprite (lines_s[i]);
                register_sprite (time_s[i]);
                register_sprite (score_s[i]);
                x+=12;
        }

}


void Level::finish ()
{
        vector<Sprite*>::iterator it;

        for (unsigned int i=0; i<6; i++)
        {
                delete time_s[i];
                delete score_s[i];
                delete lines_s[i];
        }
        unregister_all();
        dead_squares.clear();

        for (unsigned int i=0; i<18; i++)
        {
                squares_by_line[i].clear();
                filled_count[i] = 0;
        }
        delete curr_block;
        delete next_block;

}

void Level::send_data (map<string,string>  data)
{
        player = data["name"];
        Sprite * s;
        int x=390;
        for (unsigned int i=0; i<player.size();i++)
        {
                s = new Font (player[i], x, 410);
                x+=12;
                register_sprite(s,1);
        }

}


void Level::save_score ()
{
        stringstream s;
        s << score;
        map<string, string> m;
        m["name"] = player;
        s >> m["score"];
        scenarios[SCORE_MENU]->send_data(m);
        finish();
}
