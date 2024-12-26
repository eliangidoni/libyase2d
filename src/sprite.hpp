// Time-stamp: <2009-08-11 11:50:20 geg>
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

        class Sprite
        {
        public:
                enum Direction {UP, DOWN, RIGHT, LEFT, NONE};
                enum Collision {CIRCULAR, RECTANGULAR};
                enum Screen {SCR_TOP, SCR_BOTTOM, SCR_LEFT, SCR_RIGHT, SCR_NONE,
                             SCR_TOPLEFT, SCR_TOPRIGHT, SCR_BOTLEFT, SCR_BOTRIGHT};

                Sprite (int width, int height, int r, int g, int b, int alpha);
                Sprite(string file, bool alpha=false,
                       int rk=-1, int gk=-1, int bk=-1);
                virtual ~Sprite();

                // user defined behavior.
                virtual void update (unsigned int dt);

                // blit the sprite on screen.
                void draw (SDL_Surface * screen);

                // set x position in screen.
                void set_x (int x);

                // set y position in screen.
                void set_y (int y);

                int get_x ();

                int get_y ();

                int get_left ();
                int get_top ();
                int get_bottom ();
                int get_right ();
                int get_height ();
                int get_width ();
                bool is_walkable ();

                void set_walkable(bool v);
                // set id for sprite.
                void set_id (int sid);

                // get id for sprite.
                int get_id ();

                // set rectangle id for sprite.
                void set_rect_id (int rid);

                // get rectangle id for sprite.
                int get_rect_id ();

                // set collision type.
                void set_collision (Collision type);

                // move sprite to dir by steps pixels.
                void move (Direction dir, unsigned int steps);

                // add new pixmap rectangle for the sprite set 'curr_rect' to 'id'.
                void add_clip_rect(int id, int width, int height, int x, int y);

                // returns colliding screen zone.
                Screen collide_screen (int width, int height, int origx=0, int origy=0);

                // returns true if collides, false otherwise.
                bool collide_neighbor (Sprite * neighbor,int threshold=0);

                // returns colliding neighbors.
                vector<Sprite*> collide_neighbors(vector<Sprite*>& neighbors,
                                                  int threshold=0);

        protected:
                Collision col_type;
                int curr_rect, id,top,left,right,bottom, width, height;
                map<int, SDL_Rect> pixmap_rects;
                SDL_Surface * pixmap;
                string img_file;
                bool walkable;
                bool collide_rect (Sprite *neighbor, int threshold);
                bool collide_circ (Sprite *neighbor);

                // map for surface caching.
                static map<string, pair<SDL_Surface*,int> > surfaces;

                static SDL_Surface *load_pixmap (string img_file, bool alpha,
                                                 int rk,int gk,int bk);
        
        };

}
