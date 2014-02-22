// -*-c++-*-

/*!
    \file main_data.cpp
    \brief main data class Source File.
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

#include <QtGui>

#include "main_data.h"

#include "options.h"

#ifdef HAVE_LIBZ
#include <rcg/gzfstream.h>
#endif
#include <rcg/parser.h>

#include <fstream>
#include <iostream>
#include <cmath>

#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#ifdef HAVE_WINDOWS_H
#include <windows.h>
#endif

namespace {

inline
float
quantize( const float & val,
          const float & prec )
{
    return rintf( val / prec ) * prec;
}

}

/*-------------------------------------------------------------------*/
/*!

*/
MainData::MainData()
{
 clear();
}

/*-------------------------------------------------------------------*/
/*!

*/
MainData::~MainData()
{
}

/*-------------------------------------------------------------------*/
/*!

*/
void
MainData::clear()
{
    M_index = 0;
    M_disp_holder.clear();
    updateFocus();
}

/*-------------------------------------------------------------------*/
/*!
  \todo multi-threaded
*/
bool
MainData::openRCG( const QString & file_path,
                   QWidget *  )
{
#ifdef HAVE_LIBZ
    rcss::gzifstream fin( file_path.toAscii() );
#else
    std::ifstream fin( file_path.toAscii() );
#endif

    if ( ! fin )
    {
        std::cerr << "failed to open the rcg file. [" << file_path.toStdString() << "]"
                  << std::endl;
        return false;
    }

    clear();

    QTime timer;
    timer.start();

    rcss::rcg::Parser parser( M_disp_holder );
    int count = 0;
    while (  parser.parse( fin ) )
    {
        ++count;
    }

    std::cerr << "parsing elapsed " << timer.elapsed() << " [ms]" << std::endl;

    if ( ! fin.eof() )
    {
        std::cerr << "failed to parse the rcg file [" << file_path.toStdString() << "]."
                  << std::endl;
        fin.close();
        return false;
    }

    fin.close();

    std::cerr << "opened rcg file [" << file_path.toStdString()
              << "]. data size = "
              << M_disp_holder.size()
              << std::endl;

    Options::instance().setGameLogFile( file_path.toStdString() );

    M_index = 0;
    updateFocus();

    return true;
}

/*-------------------------------------------------------------------*/
/*!

*/
bool
MainData::setIndexFirst()
{
    M_index = 0;
    updateFocus();

    return ( ! M_disp_holder.empty() );
}

/*-------------------------------------------------------------------*/
/*!

*/
bool
MainData::setIndexLast()
{
    if ( M_disp_holder.size() == 0)
    {
        M_index = 0;
        updateFocus();

        return false;
    }

    M_index = M_disp_holder.size() - 1;
    updateFocus();

    return true;
}

/*-------------------------------------------------------------------*/
/*!

*/
bool
MainData::setIndexStepBack()
{
    if ( 0 < M_index )
    {
        --M_index;
        updateFocus();

        return true;
    }
    else
    {
            return false;
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
bool
MainData::setIndexStepForward()
{
    if ( M_index < dispHolder().size() - 1 )
    {
        ++M_index;
        updateFocus();

        return true;
    }
    else
    {
        {
            return false;
        }
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
bool
MainData::setIndex( const int index )
{
    if ( static_cast< int >( M_index ) == index )
    {
        return false;
    }

    if ( index < 0 )
    {
        return false;
    }

    std::size_t idx = static_cast< std::size_t >( index );

    if ( idx >= dispHolder().size() )
    {
        return false;
    }

    M_index = idx;
    updateFocus();

    return true;
}

/*-------------------------------------------------------------------*/
/*!

*/
bool
MainData::setCycle( const int cycle )
{

    std::size_t index = cycle;

    if ( index == M_index )
    {
        return false;
    }

    M_index = index;
    updateFocus();

    return true;
}

void
MainData::updateFocus()
{
    const int current_time = index();

    const DispHolder & holder = dispHolder();
    std::map< int, std::pair<double, double> >::const_iterator p = holder.focusMap().find( current_time );

    if ( p != holder.focusMap().end() ) {
        double x = p->second.first;
        double y = p->second.second;

        std::map< int, std::pair<double, double> >::const_iterator q = holder.scaleMap().find( current_time );
        if (q != holder.scaleMap().end()) {
            double scale_x = q->second.first;
            double scale_y = q->second.second;

            x *= scale_x;
            y *= scale_y;
        }

        Options::instance().setFocusPointReal(x, y);
    }
}
