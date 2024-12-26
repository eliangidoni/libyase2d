// Time-stamp: <2009-03-30 03:29:32 geg>
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

        class Game
        {
        public:
                Game();
                virtual ~Game();

                void set_resolution (int width, int height, bool fs);

                void add_scene (int id, Scene * s, int nwidth=0, int nheight=0,
                                int fs=-1);

                void load_scene (int id);

                void draw (SDL_Surface * scr);

                bool update(vector<bool>& keys,Mouse& mouse,unsigned int delta);

                virtual void init() = 0;


        protected:
                unsigned int delay_time;
                int width, height;
                Scene * cur_scene;
                map<int, Scene*> scenes;
                Action action;
                bool fullscreen;

                void manage_delay (unsigned int delta);
                void change_scene ();
        };

}        
