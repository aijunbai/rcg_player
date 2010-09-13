// -*-c++-*-

/*!
  \file view_holder.h
  \brief view data holder class Header File.
*/

/*
 *Copyright:

 Copyright (C) The RoboCup Soccer Server Maintenance Group.
 Hidehisa AKIYAMA

 This code is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2, or (at your option)
 any later version.

 This code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this code; see the file COPYING.	If not, write to
 the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

 *EndCopyright:
 */

/////////////////////////////////////////////////////////////////////

#ifndef RCSSLOGPLAYER_DISP_HOLDER_H
#define RCSSLOGPLAYER_DISP_HOLDER_H


#include <rcg/types.h>
#include <rcg/handler.h>

#include <boost/shared_ptr.hpp>

#include <map>
#include <vector>
#include <iostream>

class DispHolder
    : public rcss::rcg::Handler {
private:

    std::multimap< int, rcss::rcg::PointInfoT > M_point_map;
    std::multimap< int, rcss::rcg::LineInfoT > M_line_map;
    std::multimap< int, rcss::rcg::CircleInfoT > M_circle_map;

    std::map < int, std::pair<double, double> > M_scale_map;
    std::map < int, std::pair<double, double> > M_focus_map;

    unsigned int M_size;

    // not used
    DispHolder( const DispHolder & );
    const DispHolder & operator=( const DispHolder & );
public:

    DispHolder();
    ~DispHolder();

    void clear();

    unsigned int size() const {
        return M_size;
    }

    bool empty() {
        return size() == 0;
    }

    const
    std::multimap< int, rcss::rcg::PointInfoT > & pointMap() const
      {
          return M_point_map;
      }

    const
    std::multimap< int, rcss::rcg::CircleInfoT > & circleMap() const
      {
          return M_circle_map;
      }

    const
    std::multimap< int, rcss::rcg::LineInfoT > & lineMap() const
      {
          return M_line_map;
      }

    const
    std::map< int, std::pair<double, double> > & scaleMap() const
      {
          return M_scale_map;
      }

    const
    std::map< int, std::pair<double, double> > & focusMap() const
      {
          return M_focus_map;
      }

private:
    virtual
    void doHandleDrawClear( const int );
    virtual
    void doHandleDrawPointInfo( const int,
                                const rcss::rcg::PointInfoT & );
    virtual
    void doHandleDrawLineInfo( const int,
                               const rcss::rcg::LineInfoT & );
    virtual
    void doHandleDrawCircleInfo( const int,
                                 const rcss::rcg::CircleInfoT & );

    virtual
    void doHandleScaleInfo(const int, const double, const double);

    virtual
    void doHandleFocusInfo(const int, const double, const double);

    virtual
    void doHandleEOF();
};

#endif
