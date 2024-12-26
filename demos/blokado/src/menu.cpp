// Time-stamp: <2009-04-06 03:21:35 geg>
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


#include <menu.hpp>


//
// Selection class
///
Selection::Selection (int tot, int dist)
{
        items=tot;
        pointdist=dist;
}


Selection::~Selection ()
{
}


Action Selection::update(vector<bool>& keys, Mouse& mouse,
                         unsigned int delta)
{
        Action action;

        if (keys[KEY_DOWN]&& curr_sel<items)
        {
                pointer->move(Sprite::DOWN, pointdist);
                curr_sel++;
        }
        else if (keys[KEY_UP] && curr_sel>1)
        {
                pointer->move(Sprite::UP, pointdist);
                curr_sel--;
        }

        if (keys[KEY_RETURN])
                return handle_selection (curr_sel);

        return action;
}


//
// Entry class
///
Entry::Entry (int point_x, int point_y, int char_limit)
{
        limit = char_limit;
        px = point_x; 
        py = point_y;
        orig_px = px;
        orig_py = py;
}


Entry::~Entry ()
{
}


Action Entry::update(vector<bool>& keys, Mouse& mouse, unsigned int delta)
{
        Action action;
        Sprite * s;
        char c;
        int idx;
        if (keys[KEY_BACKSPACE] && curr_text.size()>0)
        {
                unregister_sprite (letters.top());
                letters.pop();
                px-=12;
                underscore->move(Sprite::LEFT,12);
                curr_text.erase(curr_text.end()-1);
        }

        if (curr_text.size() < limit)
        {
                for (int i=KEY_a; i<=KEY_z;i++)
                {
                        idx = i-KEY_a;
                        if (keys[i])
                        {
                                c = 65 + idx;
                                curr_text += c;
                                s = new Font (c,px,py);
                                letters.push(s);
                                register_sprite (s);
                                px+=12;
                                underscore->move(Sprite::RIGHT,12);
                        }
                }
        }

        if (keys[KEY_RETURN] && curr_text.size() > 0)
        {
                string tmp = curr_text;
                curr_text.erase();
                while (!letters.empty()){
                        unregister_sprite(letters.top());
                        letters.pop();
                }
                px = orig_px;
                py = orig_py;
                underscore->set_x(px);
                underscore->set_y(py);

                return handle_text(tmp);
        }
        if (keys[KEY_ESCAPE])
        {
                curr_text.erase();
                while (!letters.empty()){
                        unregister_sprite(letters.top());
                        letters.pop();
                }
                px = orig_px;
                py = orig_py;
                underscore->set_x(px);
                underscore->set_y(py);
                return handle_cancel();
        }

        return action;
}


//
// Main_menu class
///
Main_menu::~Main_menu ()
{
}

void Main_menu::init ()
{
        pointer = new Pointer(180,95);
        back = new Sprite(DATADIR "/sprites/main.png");
        back->add_clip_rect(0,540,480,0,0);
        register_sprite (pointer,1);
        register_sprite (back,0);
        curr_sel=1;

        scenarios[NAME_MENU]->init();
        scenarios[SCORE_MENU]->init();

        Sound::load_music (1, DATADIR "/sounds/level.ogg");
        Sound::load_music (0, DATADIR "/sounds/menu.ogg");
        Sound::play_music (0,-1,2000);
}


Action Main_menu::handle_selection(int selected)
{
        Action action;
        switch (selected)
        {
                case 1:
                        action.next(NAME_MENU);
                        break;
                case 2:
                        action.next(SCORE_MENU);
                        break;
                case 3:
                        action.stop();
                        break;
        }
        pointer->set_x(180);
        pointer->set_y(95);
        curr_sel=1;

        return action;
}

//
// Score_menu class
///

Score_menu::~Score_menu ()
{
}


Action Score_menu::update(vector<bool>& keys, Mouse& mouse,
                          unsigned int delta)
{
        Action action;

        if (keys[KEY_RETURN] || keys[KEY_SPACE] || keys[KEY_ESCAPE])
                action.next(MAIN_MENU);
        return action;
}


void Score_menu::init ()
{
        string name, score;
        char c;
        int x, y=84, count=0;
        Sprite * font;
        ifstream in (HOMEDIR "/.blokado-scores");

        scores_vec.clear();
        while (in.good() && count<10)
        {
                name.erase();
                score.erase();

                in.get(c);
                while (c >= 'A' && c <= 'Z' && in.good())
                {
                        name += c;
                        in.get(c);
                }
                if (c==',')
                {
                        in.get(c);
                        while (c >= '0' && c <= '9' && in.good())
                        {
                                score += c;
                                in.get(c);
                        }
                }

                if (name.size()>0 && score.size()>0)
                {
                        stringstream ss(score);
                        int tmp;
                        ss >> tmp;
                        scores_vec.push_back (make_pair(tmp, name));
                        x=182;
                        for (unsigned int i=0; i<name.size();i++)
                        {
                                font = new Font (name[i], x, y);
                                register_sprite(font,1);
                                fonts.push_back(font);
                                x+=15;
                        }
                        x=362;
                        for (unsigned int i=0; i<score.size();i++)
                        {
                                int num = score[i] - '0';
                                font = new Number (num, x, y);
                                register_sprite(font,1);
                                fonts.push_back(font);
                                x+=15;
                        }
                        y+=41;
                        count++;
                }
        }

        back = new Sprite(DATADIR "/sprites/scores.png");
        back->add_clip_rect(0,540,480,0,0);
        register_sprite (back,0);
}


void Score_menu::send_data (map<string,string>  data)
{
        stringstream ss(data["score"]);
        int tmp;
        ofstream f;
        vector<pair<int, string> >::reverse_iterator it;

        ss >> tmp;
        scores_vec.push_back (make_pair(tmp,data["name"]));

        sort(scores_vec.begin(),scores_vec.end());

        f.open(HOMEDIR "/.blokado-scores");
        for (it=scores_vec.rbegin();it!=scores_vec.rend();it++)
                f<<it->second<<','<<it->first<<"\n";

        f.close();

        while (!fonts.empty())
        {
                unregister_sprite(fonts.back());
                fonts.pop_back();
        }

        init();
}


//
// Name_menu class
///
Name_menu::Name_menu () :
        Entry (220, 150)
{
}


Name_menu::~Name_menu ()
{
}

void Name_menu::init ()
{
        underscore = new Underscore(220,155);
        back = new Sprite(DATADIR "/sprites/name.png");
        back->add_clip_rect(0,540,480,0,0);
        register_sprite (underscore,1);
        register_sprite (back,0);
}


Action Name_menu::handle_text (string text)
{
        Action action;
        map<string,string> m;

        m["name"] = text;
        scenarios[LEVEL]->send_data(m);
        scenarios[LEVEL]->init();
        Sound::halt_music();
        Sound::play_music (1,-1, 2000);
        action.next(LEVEL);
        
        return action;
}



Action Name_menu::handle_cancel ()
{
        Action action;

        action.next(MAIN_MENU);
        return action;
}


Font::Font (char c, int x, int y)
        : Sprite (DATADIR "/sprites/fonts.png",true)
{
        add_clip_rect (0, 10, 16, 10*(c-65), 2);
        set_x (x);
        set_y (y);      
}


Number::Number (int c, int x, int y)
        : Sprite (DATADIR "/sprites/numbers.png",true)
{
        add_clip_rect (0, 10, 15, 10*c, 1);
        set_x (x);
        set_y (y);      
}


Pointer::Pointer(int x, int y)
        : Sprite(DATADIR "/sprites/pointer.png",true)
{
        add_clip_rect (0, 24, 35, 0, 0);
        set_x (x);
        set_y (y);
}


Underscore::Underscore (int x, int y)
        : Sprite(DATADIR "/sprites/underscore.png",255,255,255)
{
        add_clip_rect (0, 21,20,0,0);
        set_x (x);
        set_y (y);

}
