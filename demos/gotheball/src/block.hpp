// Time-stamp: <2009-03-29 19:41:20 geg>
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

#ifndef _BLOCK_HPP
#define _BLOCK_HPP

#include <yase2d.hpp>

using namespace Yase2D;
class Block : public Sprite
{
public:
        enum Type {SOFT=1, NORMAL, HARD, UNBREAKABLE};

        Block();
        ~Block();

        void set_type (Type t);
        Type get_type ();
protected:
        Type type;

};

#endif // _BLOCK_HPP
