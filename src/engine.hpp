// Time-stamp: <2009-08-11 10:11:14 geg>
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

namespace Yase2D
{
        class Engine
        {
        public:
                enum Animation {FRAME_BASED, TIME_BASED};

                Engine();
                ~Engine();

                void set_resolution (int width, int height, int color_depth,
                                     bool fs=false);
                void set_animation (Animation type);
                void set_fps (unsigned int fps);
                void enable_sound ();
                void hide_mouse_pointer ();

                // run engine using game.
                void run (Game *game, string name);

                // Framework needed.
                static unsigned int update_interval ();
                static void resize_screen (int width, int height, bool fs);
                static void set_key_repetition (int ms);
                static void show_mouse();
                static void hide_mouse();
                static void grab_input();
                static void release_input();
        protected:
                // animation attrs
                static unsigned int update_int;
                unsigned int fps,max_cycles;
                Animation anim_type;

                // graphic attrs
                static SDL_Surface * screen;
                static int resy, resx, depth;
                bool fullscreen;

                // game attrs
                Game * cur_game;

                // input attrs
                Mouse mouse;
                static bool rep_keys;
                vector<bool> keys;
                bool mouse_hidden;

                // sound attrs
                bool with_sound;

                // engine procs
                void init_mouse ();
                void toggle_mouse_button (int button);
                void game_input (bool*running);
                void frame_loop ();
                void time_loop ();
                Key get_engine_key (SDLKey k);

                // default frame rate.
                static const unsigned int FRAME_RATE = 30;
                // maximum frame rate (for time-based).
                static const unsigned int MAX_FRAME_RATE = FRAME_RATE;
                // minimum frame rate (for time-based).
                static const unsigned int MIN_FRAME_RATE = 20;
                // max cycles per frame (for time-based).
                static const unsigned int MAX_CYCLES_PER_FRAME = MAX_FRAME_RATE/MIN_FRAME_RATE;
                // default update interval in ms.
                static const unsigned int UPDATE_INTERVAL = (1000 / FRAME_RATE);
        };
}
