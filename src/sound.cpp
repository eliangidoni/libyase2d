// Time-stamp: <2009-03-29 19:33:36 geg>
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
#include <sound.hpp>


namespace Yase2D
{

        map<int, Mix_Chunk*> Sound::effects;
        map<int, Mix_Music*> Sound::musics;


        void Sound::init ()
        {
                if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) < 0)
                {
                        cerr << "SDL_mixer error: " << Mix_GetError() << '\n';
                        exit(1);
                }
        }


        void Sound::finish ()
        {
                map<int, Mix_Chunk*>::iterator cit;
                map<int, Mix_Music*>::iterator mit;

                for (cit = effects.begin(); cit != effects.end(); cit++)
                        Mix_FreeChunk (cit->second);
                effects.clear();

                for (mit = musics.begin(); mit != musics.end(); mit++)
                        Mix_FreeMusic (mit->second);
                musics.clear();

                Mix_CloseAudio();
        }


        void Sound::load_music (int mid, string file)
        {
                Mix_Music *music;

                if (musics.count(mid) == 0)
                {
                        music = Mix_LoadMUS(file.c_str());
                        if(music == NULL) 
                        {
                                cerr << "Mix_LoadMUS error: "<< Mix_GetError() << '\n';
                                exit (1);
                        }
                        musics[mid] = music;
                }
        }


        void Sound::unload_music (int mid)
        {
                Mix_FreeMusic (musics[mid]);
                musics.erase(mid);
        }


        void Sound::play_music (int mid, int loop, int faid_ms)
        {
                if (faid_ms >= 0)
                        Mix_FadeInMusic (musics[mid], loop, faid_ms);
                else
                        Mix_PlayMusic (musics[mid], loop);
        }


        void Sound::volume_music (int vol)
        {
                Mix_VolumeMusic (vol);
        }


        void Sound::volume_effect (int eid, int vol)
        {
                Mix_VolumeChunk (effects[eid], vol);
        }


        void Sound::pause_music ()
        {
                Mix_PauseMusic ();
        }


        void Sound::resume_music ()
        {
                Mix_ResumeMusic ();
        }


        void Sound::halt_music (int faid_ms)
        {
                if (faid_ms >= 0)
                        Mix_FadeOutMusic (faid_ms);
                else
                        Mix_HaltMusic ();
        }


        void Sound::load_effect (int eid, string file)
        {
                Mix_Chunk * chunk;
                if (effects.count (eid) == 0)
                {
                        chunk = Mix_LoadWAV (file.c_str());
                        if (chunk == NULL)
                        {
                                cerr << "Mix_LoadWAV error: " << Mix_GetError() << '\n';
                                exit(1);
                        }
                        effects[eid] = chunk;
                }
        }


        void Sound::unload_effect (int eid)
        {
                Mix_FreeChunk (effects[eid]);
                effects.erase(eid);
        }


        int Sound::play_effect (int eid, int loop)
        {
                int channel;
                channel = Mix_PlayChannel (-1, effects[eid], loop);
                return channel;
        }
}
