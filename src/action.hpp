// Time-stamp: <2009-03-29 19:32:21 geg>
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
        class Action
        {
        public:
                typedef void (* Action_cb_sprite) (Sprite*);

                Action();

                // Framework needed
                void reset();
                unsigned int get_delay ();
                vector<Sprite*>& get_sprites();
                bool should_delay();
                bool should_stop ();
                bool should_unregister ();
                bool has_next ();
                int get_next ();
                int key_repetition ();


                // for the user
                void delay(unsigned int ms);
                void delay(unsigned int ms, Sprite * s, bool unregister=true);
                void delay(unsigned int ms, vector<Sprite*>& s, bool unregister=true);
                void next (int scenario);
                void enable_key_repetition (int ms=0);
                void stop();

        protected:
                vector<Sprite*> sprites;
                bool do_stop, unreg_sprites;
                unsigned int do_delay;
                int next_scenario,rep_key_ms;
        };
}
