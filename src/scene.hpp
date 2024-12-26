// Time-stamp: <2009-04-26 14:29:19 geg>
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
        class Scene
        {
        public:
                Scene();
                virtual ~Scene();

                // framework needed
                void set_resolution (int w, int h, bool fs);
                int get_resx ();
                int get_resy ();
                bool get_fs ();
                void set_scenes (map<int, Scene*> n);
                virtual void draw (SDL_Surface * scr);

                void sprites_in_delay (Action action);
                void update_in_delay (unsigned int delta);
                void clean_in_delay (Action action);

                // for the user
                void put_foreground (int r, int g, int b, int alpha, int depth);
                void remove_foreground ();
                void register_sprite (Sprite * obj, int depth=0);
                void unregister_sprite (Sprite *obj);
                void unregister_all ();

                virtual void send_data (map<string,string> data);
                virtual void init ();
                virtual void finish ();
                virtual Action update(vector<bool>& keys, Mouse& mouse,
                                      unsigned int delta);

        protected:
                bool fullscreen;
                int width, height;
                Sprite * front_s;
                vector<Sprite*> sprites_for_delay;
                map<int, Scene*> scenarios;
                map<int, vector<Sprite*>*> sprites_by_depth;
        };

        class Tile_scene : public Scene
        {
        public:
                Tile_scene ();
                virtual ~Tile_scene();

                void set_size (int tw, int th, int cols, int rows);
                void set_view (int x, int y, int width, int height);
                void set_camera_x (int x);
                void set_camera_y (int y);

                bool leftmost_side ();
                bool rightmost_side ();
                bool top_side ();
                bool bottom_side ();

                // TODO: we should not assume that sprite 's' is of tile width.
                vector<Sprite*> collide_sprites (Sprite * s, int depth,int th=0);
                Sprite * get_tile (int x, int y, int depth=0);
                int get_camera_x ();
                int get_camera_y ();
                void register_sprite (Sprite * obj, int x, int y,
                                      int depth=0);
                void register_background (Sprite * obj);
                void unregister_sprite (Sprite *obj);
                void unregister_all ();
                void draw (SDL_Surface * scr);

        protected:
                int camera_x, camera_y, tile_width,tile_height,
                        map_width,map_height,tiles_per_col,tiles_per_row;
                SDL_Rect view;
                vector<vector<vector<Sprite*>* >* > sprites;
                Sprite * background;

                void draw_tiles (SDL_Surface *scr, int i, int j);
        };
}
