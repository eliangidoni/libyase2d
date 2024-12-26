// Time-stamp: <2009-04-05 22:05:17 geg>
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
        cur_level = 0;
}


void Level::init ()
{

        back = new Sprite(DATADIR "/sprites/back.jpg");
        back->add_clip_rect(0,640,480,0,0);
        register_sprite (back);

        int x=450;
        for (int i=2; i>=0;i--)
        {
                lives_s[i] = new Sprite (DATADIR "/sprites/life.png",
                                         false,255,0,255);
                lives_s[i]->add_clip_rect(0, 50, 10, 0, 0);
                lives_s[i]->set_x (x);
                lives_s[i]->set_y (425);
                x+=60;
                register_sprite (lives_s[i],1);
        }

        lose_dialog = new Sprite(DATADIR "/sprites/lose.png",true);
        win_dialog = new Sprite(DATADIR "/sprites/win.png",true);
        pause_dialog = new Sprite(DATADIR "/sprites/pause.png",true);
        quit_dialog = new Sprite(DATADIR "/sprites/quitmenu.png",true);
        ready_dialog = new Sprite(DATADIR "/sprites/ready.png",true);


        lose_dialog->add_clip_rect(0, 138, 31, 0, 0);
        win_dialog->add_clip_rect(0, 206, 20, 0, 0);
        pause_dialog->add_clip_rect(0, 91, 31, 0, 0);
        quit_dialog->add_clip_rect(0, 301, 34, 0, 0);
        ready_dialog->add_clip_rect(0, 134, 32, 0, 0);

        pause_dialog->set_x (270);
        pause_dialog->set_y (200);
        win_dialog->set_x (250);
        win_dialog->set_y (200);
        quit_dialog->set_x (200);
        quit_dialog->set_y (200);
        ready_dialog->set_x (250);
        ready_dialog->set_y (200);
        lose_dialog->set_x (250);
        lose_dialog->set_y (200);

        left_blocks=0;
        lives = 3;
        trans_time = 0;
        score = 0;
        show_quit = false;
        show_win = false;
        show_pause = false;
        show_ready = true;
        show_gameover = false;
        playing = false;

        ball = new Ball;
        paddle = new Paddle;


        register_sprite (ball, 1);
        register_sprite (paddle, 1);

        player = "";

        x=350;
        for (int i=0;i<6;i++)
        {
                score_s[i] = new Number (0,x,455);
                register_sprite (score_s[i],1);
                x+=12;
        }

        stringstream lev;
        string levstr;
        lev.width (2);
        lev.fill('0');
        lev << cur_level;
        levstr = lev.str();
        x=560;
        for (int i=0;i<2;i++)
        {
                level_s[i] = new Number (levstr[i]-48, x,455);
                register_sprite (level_s[i],0);
                x+=12;
        }

        load_next_level ();
}


Action Level::update(vector<bool>& keys, Mouse& mouse,
                     unsigned int delta)
{
        Action action;

        if (show_ready)
        {
                score=0;
                trans_time = 0;
                ball->set_x(318);
                ball->set_y(385);
                paddle->set_x(280);
                paddle->set_y(400);
                ball->stop();
                register_sprite (ready_dialog,2);
                action.delay(1000,ready_dialog);
                show_ready = false;
                playing=false;
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
        else if (show_gameover)
        {
                save_score();
                Sound::halt_music();
                Sound::play_music (0,-1, 2000);
                register_sprite (lose_dialog,2);
                action.delay(2000, lose_dialog);
                action.next(SCORE_MENU);
                return action;
        }
        else if (show_pause)
        {
                if (keys[KEY_SPACE] || keys[KEY_c])
                {
                        show_pause = false;
                        Engine::grab_input();
                        unregister_sprite (pause_dialog);
                        remove_foreground();
                }
        }
        else if (show_win)
        {
                remove_foreground();
                show_ready=true;
                show_win = false;
                if (!load_next_level ())
                {
                        save_score();
                        Sound::halt_music();
                        Sound::play_music (0,-1, 2000);
                        register_sprite (win_dialog,2);
                        action.delay(2000, win_dialog);
                        action.next(SCORE_MENU);
                }
                return action;
        }
        else
        {

                if (left_blocks==0)
                {
                        show_win = true;
                        register_sprite (win_dialog,2);
                        put_foreground(40,40,20,80,0);
                        action.delay(2000,win_dialog);
                        return action;
                }

                if (keys[KEY_ESCAPE])
                {
                        show_quit = true;
                        put_foreground(40,40,20,80,0);
                        register_sprite (quit_dialog,2);
                        return action;
                }
                if (keys[KEY_p])
                {
                        show_pause = true;
                        put_foreground(40,40,20,80,0);
                        register_sprite (pause_dialog,2);
                        Engine::release_input();
                        return action;
                }

                trans_time += delta;

                if (mouse[MOVED] && mouse[XPOS] <= 556)
                        paddle->set_x(mouse[XPOS]);
                if (keys[KEY_RIGHT])
                        paddle->move(Sprite::RIGHT);
                if (keys[KEY_LEFT])
                        paddle->move(Sprite::LEFT);
                if (keys[KEY_n]){
                        show_win=true;
                        return action;
                }
                
                if (!playing)
                {
                        ball->set_x(paddle->get_x()+38);
                        if ((keys[KEY_SPACE] || mouse[LEFT]))
                        {
                                playing=true;
                                ball->play();
                        }
                }

                ball->update(delta);
                if (ball->get_bottom() > paddle->get_bottom())
                {
                        lives--;
                        unregister_sprite (lives_s[lives]);
                        delete lives_s[lives];
                        if (lives == 0)
                                show_gameover=true;
                        else
                                show_ready=true;
                }
                else
                        manage_collisions ();
                update_info();
        }

        return action;
}


void Level::manage_collisions()
{
        vector<Sprite*> coll;
        Sprite::Screen scr;

        scr = ball->collide_screen(640,480);
        if (scr!=Sprite::SCR_NONE)
                ball->screen_dir (scr);


        coll = ball->collide_neighbors (blocks);
        if (coll.size()>0)
        {
                ball->block_dir (coll[0]);
                for (int i=0; i<coll.size();i++)
                {
                        score += 10+10000/(trans_time/1000);
                        unregister_sprite(coll[i]);
                        blocks.erase(find(blocks.begin(),blocks.end(),coll[i]));
                        delete coll[i];
                        left_blocks--;
                }
        }

        if (ball->collide_neighbor(paddle))
                ball->paddle_dir (paddle);
}


void Level::update_info ()
{
        stringstream ss;
        string scorestr;
        ss.fill('0');
        ss.width(6);

        ss << score;
        scorestr = ss.str();
        int x=350;
        for (int i=0;i<6;i++)
        {
                unregister_sprite (score_s[i]);
                delete score_s[i];
                score_s[i] = new Number (scorestr[i]-48, x,455);
                register_sprite (score_s[i],0);
                x+=12;
        }

}


void Level::finish ()
{
        vector<Sprite*>::iterator it;

        cur_level = 0;

        for (int i=0; i<6; i++)
                delete score_s[i];
        unregister_all();

        for (int i=0; i<lives;i++)
                delete lives_s[i];

        for (it=blocks.begin();it!=blocks.end();it++)
                delete (*it);

        blocks.clear();

        delete win_dialog;
        delete pause_dialog;
        delete quit_dialog;
        delete ready_dialog;
        delete ball;
        delete paddle;
        delete back;
}

void Level::send_data (map<string,string>  data)
{
        player = data["name"];
        Sprite * s;
        int x=112;
        for (unsigned int i=0; i<player.size();i++)
        {
                s = new Font (player[i], x, 455);
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
        Engine::release_input();
        finish();
}


bool Level::load_next_level ()
{
        stringstream lev;
        ifstream file;
        Block * b;
        string levelstr,levstr;

        cur_level++;

        levelstr = DATADIR "/level";
        levelstr += cur_level+48;
        levelstr += ".map";

        file.open (levelstr.c_str());
        if (!file.is_open())
                return false;

        for (int i=0; i<16; i++)
                for (int j=0; j<16;j++)
                        file >> level[i][j];
        file.close();

        for (int i=0; i<16; i++)
        {
                for (int j=0; j<16;j++)
                {
                        if (level[i][j] > 0)
                        {
                                b = new Block;
                                b->set_type ((Block::Type)level[i][j]);
                                b->set_x (j*40);
                                b->set_y (i*20);
                                register_sprite (b, 1);
                                blocks.push_back(b);
                                left_blocks++;
                        }
                }
        }

        lev.width (2);
        lev.fill('0');
        lev << cur_level;
        levstr = lev.str();
        int x=560;
        for (int i=0;i<2;i++)
        {
                unregister_sprite (level_s[i]);
                delete level_s[i];
                level_s[i] = new Number (levstr[i]-48, x,455);
                register_sprite (level_s[i],0);
                x+=12;
        }

        return true;
}
