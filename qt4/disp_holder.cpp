// -*-c++-*-

/*!
  \file disp_holder.cpp
  \brief display data holder class Source File.
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "disp_holder.h"

#include <rcg/parser.h>

#include <sstream>
#include <cmath>
#include <cstring>
#include <cstdio>

#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#ifdef HAVE_WINDOWS_H
#include <windows.h>
#endif

/*-------------------------------------------------------------------*/
/*!

 */
DispHolder::DispHolder()
    : M_log_version( 0 )
{

}

/*-------------------------------------------------------------------*/
/*!

 */
DispHolder::~DispHolder()
{

}

/*-------------------------------------------------------------------*/
/*!

 */
void
DispHolder::clear()
{
    M_point_map.clear();
    M_line_map.clear();
    M_circle_map.clear();
}

/*!

 */
void
DispHolder::doHandleDrawClear( const int time )
{
    M_point_map.erase( time );
    M_circle_map.erase( time );
    M_line_map.erase( time );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
DispHolder::doHandleDrawPointInfo( const int time,
                                   const rcss::rcg::PointInfoT & point )
{
    M_point_map.insert( std::pair< int, rcss::rcg::PointInfoT >( time, point ) );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
DispHolder::doHandleDrawCircleInfo( const int time,
                                    const rcss::rcg::CircleInfoT & circle )
{
    M_circle_map.insert( std::pair< int, rcss::rcg::CircleInfoT >( time, circle ) );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
DispHolder::doHandleDrawLineInfo( const int time,
                                  const rcss::rcg::LineInfoT & line )
{
    M_line_map.insert( std::pair< int, rcss::rcg::LineInfoT >( time, line ) );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
DispHolder::doHandleEOF()
{

}
