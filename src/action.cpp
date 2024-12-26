// Time-stamp: <2009-03-29 19:33:27 geg>
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
#include <sprite.hpp>
#include <action.hpp>

namespace Yase2D
{

        Action::Action()
        {
                reset();
        }


        void Action::reset ()
        {
                unreg_sprites = true;
                next_scenario = -1;
                do_delay = 0;
                rep_key_ms = -1;
                do_stop = false;
                sprites.clear();
        }


        unsigned int Action::get_delay ()
        {
                return do_delay;
        }


        bool Action::should_delay()
        {
                if (do_delay > 0)
                        return true;
                return false;
        }


        int Action::key_repetition ()
        {
                return rep_key_ms;
        }


        bool Action::should_stop ()
        {
                return do_stop;
        }

        bool Action::should_unregister ()
        {
                return unreg_sprites;
        }


        bool Action::has_next ()
        {
                if (next_scenario >= 0)
                        return true;
                return false;
        }


        int Action::get_next ()
        {
                return next_scenario;
        }


        void Action::delay(unsigned int ms)
        {
                do_delay = ms;
        }


        void Action::delay(unsigned int ms, Sprite * s, bool unregister)
        {
                do_delay = ms;
                sprites.push_back (s);
                unreg_sprites = unregister;
        }


        void Action::delay(unsigned int ms, vector<Sprite*>& s, bool unregister)
        {
                do_delay = ms;
                sprites = s;
                unreg_sprites = unregister;
        }


        void Action::next (int scenario)
        {
                next_scenario = scenario;
        }


        void Action::stop()
        {
                do_stop = true;
        }


        void Action::enable_key_repetition (int ms)
        {
                rep_key_ms = ms;
        }


        vector<Sprite*>& Action::get_sprites()
        {
                return sprites;
        }
}
