// -*-c++-*-

/*!
  \file types.h
  \brief Type definitions for rcg data format.
*/

/*
 *Copyright:

 Copyright (C) The RoboCup Soccer Server Maintenance Group.
               Hidehisa AKIYAMA

 This code is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 *EndCopyright:
 */

/////////////////////////////////////////////////////////////////////

#ifndef RCSSLOGPLAYER_TYPES_H
#define RCSSLOGPLAYER_TYPES_H

#include <boost/cstdint.hpp>

#include <iosfwd>
#include <string>

namespace rcss {
namespace rcg {

typedef boost::int16_t Int16;
typedef boost::uint16_t UInt16;
typedef boost::int32_t Int32;
typedef boost::int32_t UInt32;

const double SHOWINFO_SCALE = 16.0;
const float SHOWINFO_SCALEF = 16.0f;
const double SHOWINFO_SCALE2 = 65536.0;
const float SHOWINFO_SCALE2F = 65536.0f;

const int REC_OLD_VERSION = 1;
const int REC_VERSION_2 = 2;
const int REC_VERSION_3 = 3;
const int REC_VERSION_4 = 4;
const int REC_VERSION_5 = 5;
const int DEFAULT_REC_VERSION = REC_VERSION_5;

/*!
  \enum DrawMode
  \brief draw data types
 */
enum DrawMode {
    DrawClear = 0,
    DrawPoint = 1,
    DrawCircle = 2,
    DrawLine = 3,
};


/*!
  \struct PointInfoT
  \brief point data for drawing
*/
struct PointInfoT {
    float x_;
    float y_;
    std::string color_;
    std::string comment_;
    std::string label_;

    PointInfoT( const float x,
                const float y,
                const char * color,
                const char * comment
              )
        : x_( x )
        , y_( y )
        , color_( color )
        , comment_(comment)
      {
        std::size_t pos;
        while ((pos = comment_.find('#')) != std::string::npos)
        {
            comment_.replace(pos, 1, 1, '\n');
        }
        if ((pos = comment_.find('@')) != std::string::npos)
        {
            label_.assign(comment_, pos+1, std::string::npos);
            comment_.erase(pos);
        }
      }
};

/*!
  \struct CircleInfoT
  \brief circle data for drawing
*/
struct CircleInfoT {
    float x_;
    float y_;
    float r_;
    std::string color_;

    CircleInfoT( const float x,
                 const float y,
                 const float r,
                 const char * color )
        : x_( x )
        , y_( y )
        , r_( r )
        , color_( color )
      { }
};

/*!
  \struct LineInfoT
  \brief line data for drawing
*/
struct LineInfoT {
    float x1_;
    float y1_;
    float x2_;
    float y2_;
    std::string color_;

    LineInfoT( const float x1,
               const float y1,
               const float x2,
               const float y2,
               const char * color )
        : x1_( x1 )
        , y1_( y1 )
        , x2_( x2 )
        , y2_( y2 )
        , color_( color )
      { }
};

}
}

#endif
