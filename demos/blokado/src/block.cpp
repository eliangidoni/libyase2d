// Time-stamp: <2009-03-30 03:37:52 geg>
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


#include <block.hpp>


Sprite * Block::blank_square ()
{
        Sprite *s = new Sprite(DATADIR "/sprites/squares.png");
        s->add_clip_rect (0,24,24,6,38);
        return s;
}


// initial block positions.
int Block::positions[7][10] =
{
        {6,8,0,-1,0,0,0,1,0,2},         // line
        {38,8,-1,-1,0,-1,0,0,-1,0},     // square
        {71,8,0,-1,0,0,-1,0,1,0},       // T
        {104,8,-1,-1,0,-1,0,0,1,0},     // inv S
        {137,8,-1,0,0,0,0,-1,1,-1},     // S
        {170,8,0,-1,0,0,0,1,-1,1},      // inv L
        {204,8,0,-1,0,0,0,1,1,1}        // L
};

bool Block::seeded = false;
Block::Block()
{
        int t;
        for (int i=0; i<4; i++)
                squares[i] = new Sprite(DATADIR "/sprites/squares.png");
        center_x = 141;
        center_y = 51;
        if (!seeded)
        {
                srand(time(NULL));
                seeded=true;
        }
        t = rand()%7;
        type=t;
        for (int i=0;i<4;i++)
                squares[i]->add_clip_rect (0, 24,24, positions[t][0],
                                             positions[t][1]);       
        for (int i=0,j=2; i<4; i++,j+=2){
                squares[i]->set_x (center_x+24*positions[t][j]);
                squares[i]->set_y (center_y+24*positions[t][j+1]);
        }
}



void Block::play_position ()
{
        center_x = 141;
        center_y = 51;
        int moves=2, t=type;
        for (int i=0,j=2; i<4; i++,j+=2){
                squares[i]->set_x (center_x+24*positions[t][j]);
                squares[i]->set_y (center_y+24*positions[t][j+1]);
        }

        switch (type)
        {
                case 0: // line
                        moves = 4;
                        break;
                case 5: // inv L
                case 6: // L
                        moves = 3;
                        break;
        }
        for (int i=0;i<4;i++)
                squares[i]->move (Sprite::UP, 24*moves);
        center_y-=24*moves;

}

void Block::next_position()
{
        center_x = 388;
        center_y = 128;
        int t=type;
        for (int i=0,j=2; i<4; i++,j+=2){
                squares[i]->set_x (center_x+24*positions[t][j]);
                squares[i]->set_y (center_y+24*positions[t][j+1]);
        }

}

void Block::move_bottom (vector<Sprite*>& neighbors)
{
        bool collided;
        collided = move_down(neighbors);
        while (!collided)
                collided = move_down(neighbors);
}

bool Block::move_down (vector<Sprite*>& neighbors)
{
        for (int i=0;i<4;i++){
                squares[i]->move (Sprite::DOWN, 24);
        }
        if (collide_screen () == Sprite::SCR_BOTTOM ||
            collide_screen () == Sprite::SCR_BOTLEFT ||
            collide_screen () == Sprite::SCR_BOTRIGHT ||
            collide_neighbors(neighbors))
        {
                for (int j=0;j<4;j++)
                        squares[j]->move (Sprite::UP, 24);
                return true;
        }
        else
                center_y+=24;
        return false;
}

bool Block::move_up (vector<Sprite*>& neighbors)
{
        for (int i=0;i<4;i++)
                squares[i]->move (Sprite::UP, 24);
        if (collide_screen () == Sprite::SCR_TOP ||
            collide_screen () == Sprite::SCR_TOPLEFT ||
            collide_screen () == Sprite::SCR_TOPRIGHT ||
            collide_neighbors(neighbors))
        {
                for (int j=0;j<4;j++)
                        squares[j]->move (Sprite::DOWN, 24);
                return true;
        }
        else
                center_y -=24;
        return false;
}

void Block::move_left (vector<Sprite*>& neighbors)
{

        for (int i=0;i<4;i++)
                squares[i]->move (Sprite::LEFT, 24);
        if (collide_screen () == Sprite::SCR_LEFT ||
            collide_screen () == Sprite::SCR_TOP || 
            collide_screen () == Sprite::SCR_BOTLEFT ||
            collide_screen () == Sprite::SCR_TOPLEFT ||
            collide_neighbors(neighbors))
        {
                for (int j=0;j<4;j++)
                        squares[j]->move (Sprite::RIGHT, 24);
        }
        else
                center_x-=24;

}

void Block::move_right (vector<Sprite*>& neighbors)
{

        for (int i=0;i<4;i++)
                squares[i]->move (Sprite::RIGHT, 24);
        if (collide_screen () == Sprite::SCR_RIGHT ||
            collide_screen () == Sprite::SCR_TOPRIGHT ||
            collide_screen () == Sprite::SCR_TOP ||
            collide_screen () == Sprite::SCR_BOTRIGHT ||
            collide_neighbors(neighbors))
        {
                for (int j=0;j<4;j++)
                        squares[j]->move (Sprite::LEFT, 24);
        }
        else
                center_x+=24;

}

vector<Sprite*> Block::get_squares ()
{
        vector<Sprite*> vec;
        for (int i=0; i<4; i++)
                if (squares[i]->get_y() >= 27)
                        vec.push_back(squares[i]);
        return vec;
}

vector<Sprite*> Block::get_out_squares ()
{
        vector<Sprite*> vec;
        for (int i=0; i<4; i++)
                if (squares[i]->get_y() < 27)
                        vec.push_back(squares[i]);
        return vec;
}


Sprite::Screen Block::collide_screen ()
{
        Sprite::Screen s;
        for (int i=0; i<4; i++)
        {
                s = squares[i]->collide_screen(286,434,20,26);
                if (s != Sprite::SCR_NONE)
                {
                        return s;
                }
        }
        return Sprite::SCR_NONE;
}


bool Block::collide_neighbors (vector<Sprite*>& neighbors)
{
        for (int i=0; i<4; i++)
                if (squares[i]->collide_neighbors(neighbors,1).size()>0)
                        return true;
        return false;
}


void Block::rotate (vector<Sprite*>& neighbors)
{
        int x,y,origx[4],origy[4];
        Sprite::Screen scr;
        if (type != 1)
        {
                for (int i=0; i<4; i++){
                        origx[i] = squares[i]->get_x();
                        origy[i] = squares[i]->get_y();
                }              
                for (int i=0;i<4;i++)
                {
                        x = origx[i] - center_x;
                        y = origy[i] - center_y;
                        squares[i]->set_x ((-y)+center_x);
                        squares[i]->set_y (x+center_y);

                        scr = squares[i]->collide_screen(286,434,20,26);
                        if ((scr!=Sprite::SCR_NONE && scr!=Sprite::SCR_TOP &&
                             scr!=Sprite::SCR_TOPLEFT &&
                             scr!=Sprite::SCR_TOPRIGHT) ||
                            squares[i]->collide_neighbors(neighbors,1).size()>0)
                        {
                                for (int j=0;j<4;j++){
                                        squares[j]->set_x(origx[j]);
                                        squares[j]->set_y(origy[j]);
                                }
                                return;
                        }
                }
        }
}


Block::Lines Block::get_lines ()
{
        Lines l;
        vector<Sprite*> vec = get_squares();
        for (unsigned int i=0;i<vec.size();i++)
                l.square[i] = vec[i]->get_y()/24 - 1;
        return l;
}
