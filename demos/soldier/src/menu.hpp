// Time-stamp: <2009-03-29 19:41:33 geg>
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


#ifndef _MENU_HPP
#define _MENU_HPP

#include <yase2d.hpp>
#include <defines.hpp>

using namespace Yase2D;
// FIXME: agregar splash de presentacion.
class Selection : public Scene
{
public:
        Selection (int tot, int dist);
        ~Selection ();
        Action update(vector<bool>& keys, Mouse& mouse,
                      unsigned int delta);
        virtual Action handle_selection (int selected) = 0;

protected:
        Sprite *pointer, *back;
        int curr_sel, items, pointdist;
};


class Entry : public Scene
{
public:
        Entry (int point_x, int point_y, int char_limit=10);
        ~Entry ();

        Action update(vector<bool>& keys, Mouse& mouse,
                      unsigned int delta);
        virtual Action handle_text (string text) = 0;
        virtual Action handle_cancel () = 0;

protected:
        Sprite * underscore, *back;
        string curr_text;
        unsigned int limit, px,py,orig_px,orig_py;
        stack<Sprite*> letters;
};


class Main_menu : public Selection
{
public:
        Main_menu () : Selection (3, 45) {}
        ~Main_menu ();
        Action handle_selection(int selected);
        void init ();

protected:
        
};


class Score_menu : public Scene
{
public:
        Score_menu (){}
        ~Score_menu ();
        Action update(vector<bool>& keys, Mouse& mouse,
                      unsigned int delta);
        void init ();
        void send_data (map<string,string>  data);

protected:
        Sprite *back;
        vector<pair<int, string> > scores_vec;
        vector<Sprite*> fonts;
};


class Name_menu : public Entry
{
public:
        Name_menu ();
        ~Name_menu ();
        Action handle_text (string text);
        Action handle_cancel ();
        void init ();
protected:
};


class Font : public Sprite
{
public:
        Font (char c, int x, int y);
protected:
};


class Number : public Sprite
{
public:
        Number (int c, int x, int y);
protected:
};


class Pointer : public Sprite
{
public:
        Pointer (int x, int y);
};


class Underscore : public Sprite
{
public:
        Underscore (int x, int y);
};

#endif // _MENU_HPP
