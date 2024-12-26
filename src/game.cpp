// Time-stamp: <2009-03-30 03:29:16 geg>
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

#include <common.hpp>
#include <mouse.hpp>
#include <keymap.hpp>
#include <sprite.hpp>
#include <action.hpp>
#include <scene.hpp>
#include <game.hpp>
#include <engine.hpp>

namespace Yase2D
{

        Game::Game()
        {
                cur_scene = NULL;
                delay_time = 0;
        }


        Game::~Game()
        {
                map<int, Scene*>::iterator it;

                for (it=scenes.begin(); it!=scenes.end();it++)
                {
                        delete it->second;
                }
        }


        void Game::add_scene (int id, Scene * s, int nwidth, int nheight, int fs)
        {
                int w=width,h=height;

                scenes[id] = s;
                cur_scene = s;

                if (nwidth != 0)
                        w = nwidth;
                if (nheight != 0)
                        h = nheight;
                if (fs != -1)
                        cur_scene->set_resolution(w,h,fs);
                else
                        cur_scene->set_resolution(w,h,fullscreen);
        }


        void Game::load_scene (int id)
        {
                map<int, Scene*>::iterator it;

                for (it=scenes.begin(); it!=scenes.end();it++)
                        it->second->set_scenes(scenes);

                cur_scene = scenes[id];
                cur_scene->init();
        }


        void Game::set_resolution (int width, int height, bool fs)
        {
                this->width = width;
                this->height = height;
                this->fullscreen = fs;
        }


        void Game::draw (SDL_Surface * scr)
        {
                cur_scene->draw(scr);
        }


        bool Game::update(vector<bool>& keys, Mouse& mouse, unsigned int delta)
        {
                if (action.should_delay())
                {
                        delay_time--;
                        manage_delay (delta);
                }
                else
                {
                        action = cur_scene->update(keys,mouse,delta);
                        if (action.should_stop())
                                return false;

                        if (action.should_delay())
                        {
                                delay_time=action.get_delay()/Engine::update_interval();
                                cur_scene->sprites_in_delay(action);
                                manage_delay(delta);
                        }
                        else if (action.has_next())
                        {
                                change_scene();
                        }
                }

                return true;
        }


        void Game::manage_delay (unsigned int delta)
        {
                if (delay_time == 0)
                {
                        cur_scene->clean_in_delay (action);
                        if (action.has_next())
                                change_scene();
                        action.reset();
                }
                else
                {
                        cur_scene->update_in_delay (delta);
                }
        }


        void Game::change_scene ()
        {
                cur_scene = scenes[action.get_next()];
                Engine::resize_screen (cur_scene->get_resx(), cur_scene->get_resy(),
                                       cur_scene->get_fs());
                Engine::set_key_repetition (action.key_repetition());
        }
}
