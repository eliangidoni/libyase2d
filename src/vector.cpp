// Time-stamp: <2009-04-06 02:53:57 geg>
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
#include <vector.hpp>

namespace Yase2D
{

        Vector::Vector (float nx, float ny)
        {
                x = nx;
                y = ny;
        }

        Vector::Vector (const Vector& v)
        {
                x = v.x;
                y = v.y;
        }

        void Vector::set_x (float nx)
        {
                x = nx;
        }

        void Vector::set_y (float ny)
        {
                y = ny;
        }

        float Vector::get_x ()
        {
                return x;
        }

        float Vector::get_y ()
        {
                return y;
        }

        Vector Vector::operator+ (const Vector& v)
        {
                Vector nv;
                nv.x = x + v.x;
                nv.y = y + v.y;
                return nv;
        }

        Vector Vector::operator- (const Vector& v)
        {
                Vector nv;
                nv.x = x - v.x;
                nv.y = y - v.y;
                return nv;
        }

        Vector Vector::operator* (float v)
        {
                Vector nv;
                nv.x = x * v;
                nv.y = y * v;
                return nv;
        }

        Vector Vector::operator/ (float v)
        {
                Vector nv;
                if (v != 0)
                {
                        nv.x = x / v;
                        nv.y = y / v;
                }
                return nv;
        }


        Vector& Vector::operator= (const Vector& v)
        {
                if (&v != this)
                {
                        x = v.x;
                        y = v.y;
                }
                return *this;
        }

        Vector& Vector::operator+= (const Vector& v)
        {
                if (&v != this)
                {
                        x += v.x;
                        y += v.y;
                }
                return *this;

        }

        Vector& Vector::operator-= (const Vector& v)
        {
                if (&v != this)
                {
                        x -= v.x;
                        y -= v.y;
                }
                return *this;
        }

        Vector& Vector::operator*= (float v)
        {
                x *= v;
                y *= v;
                return *this;
        }

        Vector& Vector::operator/= (float v)
        {
                if (v != 0)
                {
                        x /= v;
                        y /= v;
                }
                return *this;
        }

        float Vector::dot_product (const Vector& v)
        {
                return (x*v.x + y*v.y);
        }

        // this is equivalent to the Z magnitude of the cross product
        // between two 2D vectors.
        float Vector::perp_dot_product (const Vector& v)
        {
                return (x*v.y - y*v.x);
        }

        float Vector::length () const
        {
                return sqrtf(x*x + y*y);
        }

        void Vector::nullify ()
        {
                x=0;
                y=0;
        }

        void Vector::normalize ()
        {
                float len = length();
                if (len != 0)
                {
                        x = x / len;
                        y = y / len;
                }
        }

        void Vector::rotate (float degrees)
        {
                float ang;
                ang = atan2f (y,x);
                ang = ang + (degrees * M_PI/180);
                x = cosf (ang);
                y = sinf (ang);
        }

        float Vector::angle (const Vector& v)
        {
                if (v.x == 0 && v.y == 0)
                {
                        Vector tmp=*this,v2=v;
                        v2.x=1;
                        return atan2f (v2.perp_dot_product(tmp),
                                       v2.dot_product(tmp)) *180/M_PI;
                }
                return atan2f (perp_dot_product(v),dot_product(v)) *180/M_PI;
        }

        void Vector::negate_x ()
        {
                x = -x;
        }

        void Vector::negate_y ()
        {
                y = -y;
        }
}
