// Time-stamp: <2009-08-11 10:10:56 geg>
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
#include <keymap.hpp>
#include <mouse.hpp>
#include <sound.hpp>
#include <sprite.hpp>
#include <action.hpp>
#include <scene.hpp>
#include <game.hpp>
#include <engine.hpp>

namespace Yase2D
{
        SDL_Surface * Engine::screen;
        int Engine::resy, Engine::resx, Engine::depth;
        bool Engine::rep_keys;
        unsigned int Engine::update_int;

        Engine::Engine()
                : keys(323,false)
        {
                fps = FRAME_RATE;
                update_int = UPDATE_INTERVAL;
                max_cycles = MAX_CYCLES_PER_FRAME;
                anim_type = FRAME_BASED;
                resx=640;
                resy=480;
                screen = NULL;
                depth=16;
                cur_game=NULL;
                with_sound = false;
                rep_keys = false;
                mouse_hidden = false;
                fullscreen = false;
        }


        Engine::~Engine()
        {
                // nothing yet.
        }


        void Engine::set_resolution (int width, int height, int color_depth, bool fs)
        {
                fullscreen = fs;
                resx = width;
                resy = height;
                depth = color_depth;
        }


        void Engine::set_animation (Animation type)
        {
                anim_type = type;
        }


        void Engine::set_fps (unsigned int f)
        {
                fps = f;
                update_int = 1000/fps;
                max_cycles = fps / MIN_FRAME_RATE;
        }


        unsigned int Engine::update_interval ()
        {
                return update_int;
        }


        void Engine::enable_sound ()
        {
                with_sound = true;
        }


        void Engine::run (Game *game, string name)
        {
                Uint32 flags = SDL_INIT_VIDEO | SDL_INIT_TIMER;

                if (with_sound)
                        flags |= SDL_INIT_AUDIO;

                if((SDL_Init(flags)==-1))
                { 
                        cerr << "Could not initialize SDL: " << SDL_GetError() << '\n';
                        exit(1);
                }
                cerr << "Initialized SDL.\n";

                flags = SDL_SWSURFACE;
                if (fullscreen)
                        flags |= SDL_FULLSCREEN;
                screen = SDL_SetVideoMode(resx,resy,depth,flags);
                if (!screen)
                {
                        cerr << "SDL_SetVideoMode error: " << SDL_GetError() << '\n';
                        exit(1);
                }

                if (with_sound)
                {
                        Sound::init();
                        cerr << "Initialized SDL_mixer.\n";
                }

                SDL_WM_SetCaption (name.c_str(), name.c_str());

                init_mouse ();
                if (mouse_hidden)
                        SDL_ShowCursor(SDL_DISABLE);

                // let's play !!
                cur_game = game;
                cur_game->set_resolution(resx,resy, fullscreen);
                if (anim_type == FRAME_BASED)
                        frame_loop();
                else
                        time_loop();

                // Clean up
                if (with_sound)
                        Sound::finish();
                SDL_Quit();

        }


        void Engine::resize_screen (int width, int height, bool fs)
        {
                resx = width;
                resy = height;
                if (fs)
                        screen = SDL_SetVideoMode(resx,resy,depth,
                                                  SDL_FULLSCREEN|SDL_SWSURFACE);
                else
                        screen = SDL_SetVideoMode(resx,resy,depth,
                                                  SDL_SWSURFACE);
                if (!screen)
                {
                        cerr << "SDL_SetVideoMode error: " << SDL_GetError() << '\n';
                        exit(1);
                }

        }


        void Engine::time_loop ()
        {
                unsigned int currtime=0, prevtime=0, remainder=0,iterations=0;
                bool running=true;

                cur_game->init();
                cur_game->draw (screen);

                prevtime=SDL_GetTicks();
                while (running)
                {
                        currtime = SDL_GetTicks ();
                        iterations = ((currtime+remainder)-prevtime);
                        prevtime = currtime;

                        if (iterations > max_cycles*update_int)
                                iterations = max_cycles*update_int;

                        while (iterations >= update_int)
                        {
                                iterations -= update_int;
                                game_input (&running);
                                running &= cur_game->update(keys,mouse,
                                                            update_int);
                                if (!rep_keys)
                                        fill(keys.begin(),keys.end(),false);
                        }
                        remainder = iterations;
                        cur_game->draw(screen);

                        // give the CPU a break.
                        SDL_Delay (1); 
                }
        }


        void Engine::frame_loop ()
        {
                unsigned int currtime=0, prevtime=0, deltatime=0;
                bool running=true;
                int frames=0;

                cur_game->init();
                cur_game->draw (screen);

                prevtime=SDL_GetTicks();
                // debug vars
                int f=SDL_GetTicks(),s=0;
                while (running)
                {
                        // s = s + (SDL_GetTicks() - f);
                        // f = SDL_GetTicks();
                        // if (s > 1000)
                        // {
                        //         cout<<frames<<'\n';
                        //         frames=0;
                        //         s=0;
                        // }
                        // frames++;

                        game_input (&running);
                        running &= cur_game->update(keys,mouse,
                                                    deltatime);
                        if (!rep_keys)
                                fill(keys.begin(),keys.end(),false);
                        cur_game->draw(screen);

                        currtime = SDL_GetTicks();
                        deltatime = currtime - prevtime;
                        prevtime = currtime;
                        if (deltatime < update_int)
                        {
                                SDL_Delay(update_int-deltatime);
                                prevtime += (update_int-deltatime);
                                deltatime += (update_int-deltatime);
                        }
                }

        }


        void Engine::set_key_repetition (int ms)
        {
                if (ms < 0)
                {
                        rep_keys = false;
                        SDL_EnableKeyRepeat(0,0);
                }
                else if (ms == 0)
                {
                        rep_keys = true;
                        SDL_EnableKeyRepeat(0,0);
                }
                else
                {
                        rep_keys = false;
                        SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,ms);
                }
        }


        void Engine::game_input (bool *running)
        {
                SDL_Event event;
                // poll _all_ events in queue.
                mouse[MOVED] = 0;
                while (SDL_PollEvent(&event))
                {
                        switch (event.type)
                        {
                                case SDL_QUIT:
                                        *running=false;
                                        break;
                                case SDL_KEYDOWN:
                                        keys[event.key.keysym.sym]=true;
                                        break;
                                case SDL_KEYUP:
                                        if (rep_keys)
                                                keys[event.key.keysym.sym]=false;
                                        break;
                                case SDL_MOUSEMOTION:
                                        mouse[XPOS] = event.motion.x;
                                        mouse[YPOS] = event.motion.y;
                                        mouse[YREL] = event.motion.yrel;
                                        mouse[XREL] = event.motion.xrel;
                                        mouse[MOVED] = 1;
                                        break;
                                case SDL_MOUSEBUTTONDOWN:
                                        mouse[PRESSED_X] = event.button.x;
                                        mouse[PRESSED_Y] = event.button.y;
                                        toggle_mouse_button (event.button.button);
                                        break;
                                case SDL_MOUSEBUTTONUP:
                                        mouse[RELEASED_X] = event.button.x;
                                        mouse[RELEASED_Y] = event.button.y;
                                        toggle_mouse_button (event.button.button);
                                        break;
                        }
                }
        }


        void Engine::toggle_mouse_button (int button)
        {
                switch (button)
                {
                        case SDL_BUTTON_LEFT:
                                mouse[LEFT] = !mouse[LEFT];
                                break;
                        case SDL_BUTTON_RIGHT:
                                mouse[RIGHT] = !mouse[RIGHT];
                                break;
                        case SDL_BUTTON_MIDDLE:
                                mouse[MIDDLE] = !mouse[MIDDLE];
                                break;
                        case SDL_BUTTON_WHEELUP:
                                mouse[WHEELUP] = !mouse[WHEELUP];
                                break;
                        case SDL_BUTTON_WHEELDOWN:
                                mouse[WHEELDOWN] = !mouse[WHEELDOWN];
                                break;
                }
        }


        void Engine::init_mouse ()
        {
                mouse[LEFT]=0;
                mouse[MIDDLE]=0;
                mouse[RIGHT]=0;
                mouse[WHEELUP]=0;
                mouse[WHEELDOWN]=0;
                mouse[XPOS]=0;
                mouse[YPOS]=0;
                mouse[XREL]=0;
                mouse[YREL]=0;
                mouse[PRESSED_X]=0;
                mouse[PRESSED_Y]=0;
                mouse[RELEASED_X]=0;
                mouse[RELEASED_Y]=0;
                mouse[MOVED]=0;       
        }


        void Engine::hide_mouse_pointer ()
        {
                mouse_hidden = true;
        }


        void Engine::show_mouse ()
        {
                SDL_ShowCursor (SDL_ENABLE);
        }


        void Engine::hide_mouse ()
        {
                SDL_ShowCursor (SDL_DISABLE);
        }


        void Engine::grab_input ()
        {
                SDL_WM_GrabInput(SDL_GRAB_ON);
        }


        void Engine::release_input ()
        {
                SDL_WM_GrabInput(SDL_GRAB_OFF);
        }
}
