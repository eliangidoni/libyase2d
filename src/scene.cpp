// Time-stamp: <2009-04-26 13:45:25 geg>
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
#include <sprite.hpp>
#include <action.hpp>
#include <scene.hpp>

namespace Yase2D
{

        Scene::Scene()
        {
                front_s = NULL;
        }


        Scene::~Scene()
        {
                map<int, vector<Sprite*>*>::iterator itr;

                for (itr=sprites_by_depth.begin(); itr!=sprites_by_depth.end();itr++)
                        delete itr->second;
        }


        void Scene::set_scenes (map<int, Scene*> n)
        {
                scenarios = n;
        }


        void Scene::register_sprite (Sprite *obj, int depth)
        {
                if (sprites_by_depth.count(depth) == 0)
                        sprites_by_depth[depth] = new vector<Sprite*>;
                sprites_by_depth[depth]->push_back(obj);              
        }


        void Scene::unregister_all ()
        {
                map<int, vector<Sprite*>*>::iterator it;
                for(it=sprites_by_depth.begin();it!=sprites_by_depth.end();it++)
                        it->second->clear();
        }

        void Scene::unregister_sprite (Sprite *obj)
        {
                map<int, vector<Sprite*>*>::iterator it;
                vector<Sprite*>::iterator it2;
        
                for(it=sprites_by_depth.begin();it!=sprites_by_depth.end();it++)
                {
                        it2 = find (it->second->begin(),it->second->end(),obj);
                        if (it2 != it->second->end())
                        {
                                it->second->erase(it2);
                                break;
                        }
                }
        }


        int Scene::get_resx()
        {
                return width;
        }


        int Scene::get_resy()
        {
                return height;
        }

        bool Scene::get_fs ()
        {
                return fullscreen;
        }

        void Scene::set_resolution (int w, int h, bool fs)
        {
                fullscreen = fs;
                height = h;
                width = w;
        }


        void Scene::draw (SDL_Surface * scr)
        {
                map<int, vector<Sprite*>*>::iterator itr;
                vector<Sprite*>::iterator itr2;

                // draw sprites in depth order.
                for (itr=sprites_by_depth.begin(); itr!=sprites_by_depth.end();itr++)
                        for (itr2=itr->second->begin();itr2!=itr->second->end();itr2++)
                                (*itr2)->draw(scr);
                SDL_Flip(scr);
        }


        void Scene::put_foreground (int r, int g, int b, int alpha, int depth)
        {
                if (front_s == NULL)
                {
                        front_s = new Sprite(width, height,r,g,b,alpha);
                        front_s->add_clip_rect (0,width,height,0,0);
                        register_sprite (front_s, depth);
                }
        }


        void Scene::remove_foreground ()
        {
                unregister_sprite (front_s);
                front_s = NULL;
        }


        void Scene::send_data (map<string, string> data)
        {
                // user defined.
        }


        void Scene::init ()
        {
                // user defined.
        }

        void Scene::finish ()
        {
                // user defined.
        }


        Action Scene::update(vector<bool>& keys, Mouse& mouse, unsigned int delta)
        {
                // user defined.
                return Action();
        }


        void Scene::sprites_in_delay (Action action)
        {
                sprites_for_delay = action.get_sprites();
        }


        void Scene::update_in_delay (unsigned int delta)
        {
                for (unsigned int i=0; i<sprites_for_delay.size(); i++)
                        sprites_for_delay[i]->update(delta);
        }


        void Scene::clean_in_delay (Action action)
        {
                if (action.should_unregister())
                {
                        for (unsigned int i=0; i<sprites_for_delay.size(); i++)
                                unregister_sprite (sprites_for_delay[i]);
                }
        }

        //
        // Tile scene class
        ///

        Tile_scene::Tile_scene ()
        {
                camera_x=0;
                camera_y=0;
                view.w = 0;
                view.h = 0;
                view.x = 0;
                view.y = 0;
                tiles_per_col = 0;
                tiles_per_row = 0;
                tile_height = 0;
                tile_width = 0;
                map_height = 0;
                map_width = 0;
                background = NULL;
        }

        Tile_scene::~Tile_scene()
        {
                for (int i=0; i < tiles_per_col; i++)
                {
                        for (int j=0; j < tiles_per_row; j++)
                                delete sprites[i]->at(j);
                        delete sprites[i];
                }
        }


        bool Tile_scene::leftmost_side ()
        {
                if (camera_x == 0)
                        return true;
                return false;              
        }
        
        bool Tile_scene::rightmost_side ()
        {
                if (camera_x+view.w == map_width)
                        return true;
                return false;
        }
        
        bool Tile_scene::top_side ()
        {
                if (camera_y == 0)
                        return true;
                return false;
        }
        
        bool Tile_scene::bottom_side ()
        {
                if (camera_y+view.h == map_height)
                        return true;
                return false;
        }



        vector<Sprite*> Tile_scene::collide_sprites (Sprite * s, int depth,
                                                     int th)
        {
                vector<Sprite*> bastards, unwalkable,colliders;
                int x,y, top,right,left,bottom;

                x = s->get_x()+get_camera_x();
                y = s->get_y()+get_camera_y();

                top = y - tile_width;
                bottom = y + tile_width;
                left = x - tile_width;
                right = x + tile_width;

                if (left > 0)
                {
                        bastards.push_back(get_tile(left,y,depth));
                        if (top > 0)
                                bastards.push_back(get_tile(left,top,depth));
                        if (bottom < get_camera_y()+view.h)
                                bastards.push_back(get_tile(left,bottom,depth));
                }
                if (right < get_camera_x()+view.w)
                {
                        bastards.push_back(get_tile(right,y,depth));
                        if (top > 0)
                                bastards.push_back(get_tile(right,top,depth));
                        if (bottom < get_camera_y()+view.h)
                                bastards.push_back(get_tile(right,bottom,depth));
                }
                if (top > 0)
                        bastards.push_back(get_tile(x,top,depth));
                if (bottom < get_camera_y()+view.h)
                        bastards.push_back(get_tile(x,bottom,depth));

                colliders = s->collide_neighbors (bastards, th);
                for (int i=0; i < colliders.size(); i++)
                        if (!colliders[i]->is_walkable())
                                unwalkable.push_back (colliders[i]);

                return unwalkable;
        }

        Sprite * Tile_scene::get_tile (int x, int y, int depth)
        {
                return sprites[y/tile_height]->at(x/tile_width)->at(depth);
        }

        void Tile_scene::set_size (int tw, int th, int cols, int rows)
        {
                vector<vector<Sprite*>* > *v;
                vector<Sprite*> * v2;
                tile_width = tw;
                tile_height = th;
                map_height = th*rows;
                map_width = tw*cols;
                tiles_per_col = rows;
                tiles_per_row = cols;

                for (int i=0; i < tiles_per_col; i++)
                {
                        v = new vector<vector<Sprite*>* >;
                        for (int j=0; j < tiles_per_row; j++)
                        {
                                v2 = new vector<Sprite*>(5);
                                for (int k=0; k<5; k++)
                                        v2->at(k) = NULL;
                                v->push_back (v2);
                                
                        }
                        sprites.push_back (v);
                }
        }

        void Tile_scene::set_view (int x, int y, int width, int height)
        {
                view.w = width;
                view.h = height;
                view.x = x;
                view.y = y;
        }

        void Tile_scene::set_camera_x (int x)
        {
                if (x >=0 && x+view.w <= map_width)
                        camera_x=x;
        }

        void Tile_scene::set_camera_y (int y)
        {
                if (y >=0 && y+view.h <= map_height)
                        camera_y=y;
        }
        
        int Tile_scene::get_camera_x ()
        {
                return camera_x;
        }

        int Tile_scene::get_camera_y ()
        {
                return camera_y;
        }

        void Tile_scene::register_background (Sprite * obj)
        {
                background = obj;
                background->set_x(view.x);
                background->set_y(view.y);
        }

        void Tile_scene::register_sprite (Sprite * obj, int x, int y,
                                          int depth)
        {
                if (depth > 4)
                        depth=4;
                sprites[y]->at(x)->at(depth) = obj;
        }

        void Tile_scene::unregister_all ()
        {
                Scene::unregister_all();
                for (int i =0 ; i<tiles_per_col; i++)
                        for (int j =0 ; j<tiles_per_row; j++)
                                sprites[i]->at(j)->clear();
        }

        void Tile_scene::unregister_sprite (Sprite *obj)
        {
                bool found=false;
                vector<Sprite*>::iterator itr;
                for (int i=0; i<tiles_per_col; i++)
                {
                        for (int j =0 ; j<tiles_per_row; j++)
                        {
                                itr = find (sprites[i]->at(j)->begin(),
                                            sprites[i]->at(j)->end(),
                                            obj);
                                if (itr != sprites[i]->at(j)->end())
                                {
                                        sprites[i]->at(j)->erase(itr);
                                        found=true;
                                        break;
                                }
                        }
                }
                if (!found)
                        Scene::unregister_sprite(obj);
        }

        void Tile_scene::draw_tiles (SDL_Surface *scr, int i, int j)
        {
                vector<Sprite*>::iterator itr;

                for (int k=0; k<5; k++)
                {
                        if (sprites[i]->at(j)->at(k) != NULL)
                        {
                                sprites[i]->at(j)->at(k)->
                                        set_x(j*tile_width-camera_x+view.x);
                                sprites[i]->at(j)->at(k)->
                                        set_y(i*tile_height-camera_y+view.y);
                                sprites[i]->at(j)->at(k)->draw(scr);
                        }
                }
                
        }

        void Tile_scene::draw (SDL_Surface * scr)
        {
                map<int, vector<Sprite*>*>::iterator itr;
                vector<Sprite*>::iterator itr2;
                int beg_x, beg_y, end_x, end_y;

                beg_x = camera_x/tile_width;
                beg_y = camera_y/tile_height;
                end_x = beg_x + view.w/tile_width;
                end_y = beg_y + view.h/tile_height;

                if (camera_x+view.w % tile_width != 0)
                        end_x++;
                if (camera_y+view.h % tile_height != 0)
                        end_y++;
         
                if (end_x >= tiles_per_row)
                        end_x = tiles_per_row;
                if (end_y >= tiles_per_col)
                        end_y = tiles_per_col;

                SDL_SetClipRect (scr, &view);
                if (background != NULL)
                        background->draw(scr);
                // now, draw tile sprites
                for (int i=beg_y; i<end_y; i++)
                        for (int j=beg_x; j<end_x; j++)
                                draw_tiles(scr, i,j);
                SDL_SetClipRect (scr, NULL);

                // draw sprites in depth order.
                for (itr=sprites_by_depth.begin(); itr!=sprites_by_depth.end();itr++)
                        for (itr2=itr->second->begin();itr2!=itr->second->end();itr2++)
                                (*itr2)->draw(scr);

                SDL_Flip(scr);
        }

}
