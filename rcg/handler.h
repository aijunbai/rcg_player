// -*-c++-*-

/*!
  \file handler.h
  \brief Class for handring rcg data
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

#ifndef RCSSLOGPLAYER_HANDLER_H
#define RCSSLOGPLAYER_HANDLER_H

#include <rcg/types.h>

#include <string>

namespace rcss {
namespace rcg {

/*!
  class Handler
  \brief abstract rcg data handler
 */
class Handler {
protected:
    Handler()
      { }

public:

    virtual
    ~Handler()
      { }

private:
    friend class Parser;

    void handleDrawClear( const int time )
      {
          doHandleDrawClear( time );
      }

    void handleDrawPointInfo( const int time,
                              const PointInfoT & p )
      {
          doHandleDrawPointInfo( time, p );
      }

    void handleDrawCircleInfo( const int time,
                               const CircleInfoT & c )
      {
          doHandleDrawCircleInfo( time, c );
      }

    void handleDrawLineInfo( const int time,
                             const LineInfoT & l )
      {
          doHandleDrawLineInfo( time, l );
      }

    void handleScaleInfo( const int time, const double x, const double y)
    {
        doHandleScaleInfo(time, x, y);
    }

    void handleFocusInfo( const int time, const double x, const double y)
    {
        doHandleFocusInfo(time, x, y);
    }

    void handleEOF()
      {
          doHandleEOF();
      }

protected:
    virtual
    void doHandleDrawClear( const int ) = 0;

    virtual
    void doHandleDrawPointInfo( const int,
                                const PointInfoT & ) = 0;

    virtual
    void doHandleDrawCircleInfo( const int,
                                 const CircleInfoT & ) = 0;

    virtual
    void doHandleDrawLineInfo( const int,
                               const LineInfoT & ) = 0;

    virtual
    void doHandleScaleInfo(const int, const double, const double) = 0;

    virtual
    void doHandleFocusInfo(const int, const double, const double) = 0;

    virtual
    void doHandleEOF() = 0;

};

}
}

#endif
