// Time-stamp: <2009-04-27 12:23:59 geg>
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
        c = new Rms;
        set_size(32,32,21,25);
        set_view (0,0,640,480);
        Engine::set_key_repetition(100);
        load_next_level();
        Scene::register_sprite (c,2);
}


Action Level::update(vector<bool>& keys, Mouse& mouse,
                     unsigned int delta)
{
        Action action;
                
        if (keys[KEY_LEFT])
                set_camera_x(get_camera_x()-1);
        if (keys[KEY_RIGHT])
                set_camera_x(get_camera_x()+1);
        if (keys[KEY_UP])
                set_camera_y(get_camera_y()-1);
        if (keys[KEY_DOWN])
                set_camera_y(get_camera_y()+1);
	if (keys[KEY_ESCAPE])
		action.stop();
        if (mouse[LEFT])
        {
                c->set_dest (mouse[XPOS],mouse[YPOS]);

                if (640 - mouse[XPOS] < 80)
                        set_camera_x(get_camera_x()+32);
                if (640 - mouse[XPOS] > 580)
                        set_camera_x(get_camera_x()-32);

                if (480 - mouse[YPOS] < 80)
                        set_camera_y(get_camera_y()+32);
                if (480 - mouse[YPOS] > 400)
                        set_camera_y(get_camera_y()-32);
        }
        if (mouse[RIGHT])
        {
                Bullet * b = new Bullet;
                b->set_x(c->get_x()+16);
                b->set_y(c->get_y()+16);
                b->set_dir(mouse[XPOS],mouse[YPOS]);
                Scene::register_sprite (b, 2);
                bullets.push_back(b);
        }

        c->update(delta);
        c->check_collision(collide_sprites(c,1));
        update_bullets (delta);
        return action;
}


void Level::update_bullets (unsigned int dt)
{
        vector<Bullet*>::iterator itr;
        for (itr=bullets.begin (); itr != bullets.end(); itr++)
        {
                (*itr)->update(dt);
                if ((*itr)->is_dead ())
                {
                        unregister_sprite (*itr);
                        delete *itr;
                        bullets.erase(itr);
                        itr--;
                }
        }
}


bool Level::load_next_level ()
{
        stringstream lev;
        ifstream file;
        Terrain * b;
        string levelstr,levstr;

        cur_level++;

        levelstr = DATADIR "/level";
        levelstr += cur_level+48;
        levelstr += ".map";

        file.open (levelstr.c_str());
        if (!file.is_open())
                return false;

        for (int i=0; i<25; i++)
                for (int j=0; j<21;j++)
                        file >> level[i][j];
        file.close();
        int n=0;
        for (int i=0; i<25; i++)
        {
                for (int j=0; j<21;j++)
                {
                        if (level[i][j] > 0)
                        {
                                b = new Terrain;
                                b->set_type (level[i][j]);
                                b->set_id (n++);
                                register_sprite (b, j,i,1);
                        }
                }
        }
        return true;
}
