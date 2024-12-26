// Time-stamp: <2009-03-29 19:32:35 geg>
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
        class Sound
        {
        public:
                static void init ();
                static void finish ();

                static void load_music (int mid, string file);
                static void unload_music (int mid);
                static void play_music (int mid, int loop=0, int faid_ms=-1);
                static void pause_music ();
                static void resume_music ();
                static void halt_music (int faid_ms=-1);
                static void volume_music (int vol);

                static void load_effect (int eid, string file);
                static void unload_effect (int eid);
                // returns the channel the effect is being played on or -1.
                static int play_effect (int eid, int loop=0);
                static void volume_effect (int eid, int vol);

        protected:
                static map<int, Mix_Chunk*> effects;
                static map<int, Mix_Music*> musics;
        };
}
