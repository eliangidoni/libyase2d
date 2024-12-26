// Time-stamp: <2009-08-11 11:50:54 geg>
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

namespace Yase2D
{

        map<string, pair<SDL_Surface*,int> > Sprite::surfaces;

        Sprite::Sprite (int width, int height, int r, int g, int b, int alpha)
        {
                pixmap = SDL_CreateRGBSurface(SDL_SWSURFACE,width,height,16,0,0,0,0);

                SDL_FillRect (pixmap, NULL, SDL_MapRGB(pixmap->format,r,g,b));
                SDL_SetAlpha (pixmap, SDL_SRCALPHA, alpha);
                pixmap = SDL_DisplayFormat (pixmap);
                if (!pixmap)
                {
                        cerr << "SDL_DisplayFormat(): " << SDL_GetError() << "\n";
                        exit (1);
                }

                col_type = RECTANGULAR;
                left = 0;
                top = 0;
                right = 0;
                bottom = 0;
                id = -1;
                walkable =true;
        }


        Sprite::Sprite(string file, bool alpha, int rk, int gk, int bk)
        {
                col_type = RECTANGULAR;
                img_file = file;
                pixmap = load_pixmap (file, alpha, rk,gk,bk);
                left = 0;
                top = 0;
                right = 0;
                bottom = 0;
                id = -1;
                walkable =true;
        }


        Sprite::~Sprite()
        {
                surfaces[img_file].second--;
                if (surfaces[img_file].second == 0)
                {
                        surfaces.erase(img_file);
                        SDL_FreeSurface (pixmap);
                }
        }


        SDL_Surface * Sprite::load_pixmap (string img_file, bool alpha,
                                           int rk, int gk, int bk)
        {

                SDL_Surface * pixmap,*tmp;

                if (surfaces.count(img_file) > 0)
                {
                        surfaces[img_file].second++;
                        return surfaces[img_file].first;
                }
                else
                {
                        pixmap = IMG_Load (img_file.c_str());
                        if (!pixmap)
                        {
                                cerr << "IMG_Load: " << IMG_GetError() << "\n";
                                exit (1);
                        }

                        if (rk>=0 && gk>=0 && bk>=0)
                                SDL_SetColorKey (pixmap, SDL_SRCCOLORKEY|SDL_RLEACCEL,
                                                 SDL_MapRGB(pixmap->format,rk,gk,bk));

                        // a _must_ optimization.
                        if (alpha)
                                tmp = SDL_DisplayFormatAlpha (pixmap);
                        else
                                tmp = SDL_DisplayFormat (pixmap);
                        SDL_FreeSurface(pixmap);
                        pixmap = tmp;

                        if (!pixmap)
                        {
                                cerr << "SDL_DisplayFormat(): " << SDL_GetError() << "\n";
                                exit (1);
                        }

                        surfaces[img_file] = make_pair(pixmap,1);
                }
                return pixmap;
        }


        void Sprite::draw (SDL_Surface * screen)
        {
                SDL_Rect rect;

                rect.x = left;
                rect.y = top;
                SDL_BlitSurface(pixmap, &pixmap_rects[curr_rect], screen, &rect);
        }


        void Sprite::set_x (int x)
        {
                left = x;
                right = left + pixmap_rects[curr_rect].w;
        }


        void Sprite::set_y (int y)
        {
                top = y;
                bottom = top + pixmap_rects[curr_rect].h;
        }

        int Sprite::get_x ()
        {
                return left;
        }


        int Sprite::get_y ()
        {
                return top;
        }


        int Sprite::get_left ()
        {
                return left;
        }


        int Sprite::get_top ()
        {
                return top;
        }


        int Sprite::get_right ()
        {
                return right;
        }


        int Sprite::get_bottom ()
        {
                return bottom;
        }

        int Sprite::get_height ()
        {
                return height;
        }

        int Sprite::get_width ()
        {
                return width;
        }


        void Sprite::set_id (int sid)
        {
                id = sid;
        }


        int Sprite::get_id ()
        {
                return id;
        }


        void Sprite::set_rect_id (int rid)
        {
                curr_rect = rid;
                right = left + pixmap_rects[rid].w;
                bottom = top + pixmap_rects[rid].h;
                width = pixmap_rects[rid].w;
                height = pixmap_rects[rid].h;
        }


        int Sprite::get_rect_id ()
        {
                return curr_rect;
        }


        void Sprite::update (unsigned int dt)
        {
                // user defined.
        }


        void Sprite::add_clip_rect(int id, int width, int height, int x,
                                   int y)
        {
                SDL_Rect rect;

                rect.w = width;
                rect.h = height;
                rect.x = x;
                rect.y = y;

                pixmap_rects[id] = rect;
                set_rect_id(id);
        }


        void Sprite::move (Direction dir, unsigned int steps)
        {
                switch (dir)
                {
                        case UP:
                                top -= steps;
                                bottom = top + pixmap_rects[curr_rect].h;
                                break;
                        case DOWN:
                                top += steps;
                                bottom = top + pixmap_rects[curr_rect].h;
                                break;
                        case RIGHT:
                                left += steps;
                                right = left + pixmap_rects[curr_rect].w;
                                break;
                        case LEFT:
                                left -= steps;
                                right = left + pixmap_rects[curr_rect].w;
                                break;
                        default: // NONE direction
                                break;
                }
        }


        Sprite::Screen Sprite::collide_screen (int width,int height,int origx,int origy)
        {
                if (left <= origx)
                {
                        if (top <= origy)
                                return SCR_TOPLEFT;
                        if (bottom >= height+origy)
                                return SCR_BOTLEFT;
                        return SCR_LEFT;
                }
                if (right >= width+origx)
                {
                        if (top <= origy)
                                return SCR_TOPRIGHT;
                        if (bottom >= height+origy)
                                return SCR_BOTRIGHT;
                        return SCR_RIGHT;
                }
                if (top <= origy)
                        return SCR_TOP;
                if (bottom >= height+origy)
                        return SCR_BOTTOM;
                return SCR_NONE;
        }


        bool Sprite::collide_neighbor (Sprite * neighbor,int threshold)
        {
                bool collide=false;
                if (this != neighbor)
                {
                        if (neighbor->col_type == RECTANGULAR ||
                            this->col_type == RECTANGULAR)
                        {
                                if (collide_rect(neighbor,threshold))
                                        collide = true;
                        }
                        else
                        {
                                if (collide_circ(neighbor))
                                        collide = true;
                        }
                }
                return collide;
        }


        vector<Sprite*> Sprite::collide_neighbors (vector<Sprite*>& neighbors,
                                                   int threshold)
        {
                vector<Sprite*>::iterator neighbor;
                vector<Sprite*> bastards;
                for (neighbor=neighbors.begin(); neighbor!=neighbors.end(); neighbor++)
                {
                        if (this != (*neighbor))
                        {
                                if ((*neighbor)->col_type == RECTANGULAR ||
                                    this->col_type == RECTANGULAR)
                                {
                                        if (collide_rect(*neighbor,threshold))
                                                bastards.push_back((*neighbor));
                                }
                                else
                                {
                                        if (collide_circ(*neighbor))
                                                bastards.push_back((*neighbor));
                                }
                        }
                }

                return bastards;
        }


        bool Sprite::collide_rect (Sprite *neighbor, int threshold)
        {
                int left2,right2,top2,bottom2;

                left2=neighbor->left;
                top2=neighbor->top;
                right2=neighbor->right;
                bottom2=neighbor->bottom;

                if (((right-threshold >= left2 && left <= left2) ||
                     (left >= left2 && left <= right2-threshold)) &&
                    ((bottom-threshold >= top2 && top <= top2) ||
                     (top >= top2 && top <= bottom2-threshold)))
                {
                        return true;
                }

                return false;

        }


        bool Sprite::collide_circ (Sprite *neighbor)
        {
                int x1,y1,x2,y2,rad1,rad2;
                SDL_Rect r1, r2;

                r1 = pixmap_rects[curr_rect];
                rad1 = r1.w/2;
                x1 = left+rad1;
                y1 = top+rad1;

                r2 = neighbor->pixmap_rects[neighbor->curr_rect];
                rad2 = r2.w/2;
                x2=neighbor->left+rad2;
                y2=neighbor->top+rad2;

                if (DISTANCE(x1,y1,x2,y2)<= rad2+rad1)
                        return true;

                return false;        
        }


        void Sprite::set_walkable (bool v)
        {
                walkable = v;
        }

        bool Sprite::is_walkable ()
        {
                return walkable;
        }

}
