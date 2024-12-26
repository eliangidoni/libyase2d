// Time-stamp: <2009-04-06 02:53:01 geg>
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
        class Vector
        {
        public:
                Vector (float nx=0, float ny=0);
                Vector (const Vector& v);

                Vector operator+ (const Vector& v);
                Vector operator- (const Vector& v);
                Vector operator* (float v);
                Vector operator/ (float v);
                Vector& operator= (const Vector& v);
                Vector& operator+= (const Vector& v);
                Vector& operator-= (const Vector& v);
                Vector& operator*= (float v);
                Vector& operator/= (float v);

                void set_x (float nx);
                void set_y (float ny);
                float get_x ();
                float get_y ();
                void negate_x ();
                void negate_y ();

                float dot_product (const Vector& v);
                float perp_dot_product (const Vector& v);
                float length () const;
                void nullify ();
                void normalize ();
                void rotate (float degrees);

                // Returns: positive if v is above this vector. negative if
                // v is below this vector, 0 if they have the same angle.
                float angle (const Vector& v=Vector(0,0));

        protected:
                float x,y;
        };
}
