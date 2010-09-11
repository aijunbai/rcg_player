// -*-c++-*-

/*!
  \file options.cpp
  \brief application configuration class Source File.
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
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this code; see the file COPYING.  If not, write to
 the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

 *EndCopyright:
 */

/////////////////////////////////////////////////////////////////////

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <QSettings>
#include <QDir>

#include "options.h"

#ifdef HAVE_BOOST_PROGRAM_OPTIONS
#include <boost/program_options.hpp>
#endif

#include <iostream>
#include <cmath>
#include <cstdio>

#ifndef PACKAGE_NAME
#define PACKAGE_NAME "rcg"
#endif
#ifndef VERSION
#define VERSION "unknown-version"
#endif

#define USE_MONITOR_CLIENT

const double Options::PITCH_LENGTH = 105.0;
const double Options::PITCH_WIDTH = 68.0;
const double Options::PITCH_HALF_LENGTH = Options::PITCH_LENGTH * 0.5;
const double Options::PITCH_HALF_WIDTH = Options::PITCH_WIDTH * 0.5;
const double Options::PITCH_MARGIN = 5.0;

const double Options::MIN_FIELD_SCALE = 1.0;
const double Options::MAX_FIELD_SCALE = 400.0;
const double Options::ZOOM_RATIO = 1.5;
const int Options::DEFAULT_TIMER_INTERVAL = 100;

/*-------------------------------------------------------------------*/
/*!
  singleton interface
*/
Options &
Options::instance()
{
    static Options s_instance;
    return s_instance;
}

/*-------------------------------------------------------------------*/
/*!

 */
Options::Options()
    : M_minimum_mode( false )
    , M_game_log_file( "" )
    , M_timer_interval( Options::DEFAULT_TIMER_INTERVAL )
      // window options
    , M_window_x( -1 )
    , M_window_y( -1 )
    , M_window_width( -1 )
    , M_window_height( -1 )
    , M_maximize( false )
    , M_full_screen( false )
    , M_canvas_width( -1 )
    , M_canvas_height( -1 )
    , M_hide_menu_bar( false )
    , M_hide_tool_bar( false )
    , M_hide_status_bar( false )
      // view options
    , M_anti_aliasing( true )
    , M_show_draw_info( true )
{
}

/*-------------------------------------------------------------------*/
/*!

 */
Options::~Options()
{
}

/*!

 */
/*-------------------------------------------------------------------*/
/*!

 */
void
Options::setFieldScale( const double & value )
{
    if ( std::fabs( M_field_scale - value ) > 0.01 )
    {
        M_field_scale = std::max( MIN_FIELD_SCALE, std::min( value, MAX_FIELD_SCALE ) );
        M_zoomed = true;
    }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
Options::zoomIn()
{
    M_zoomed = true;
    M_field_scale *= ZOOM_RATIO;
    if ( M_field_scale > MAX_FIELD_SCALE )
    {
        M_field_scale = MAX_FIELD_SCALE;
    }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
Options::zoomOut()
{
    M_zoomed = true;
    M_field_scale /= ZOOM_RATIO;
    if ( M_field_scale < MIN_FIELD_SCALE )
    {
        M_field_scale = MIN_FIELD_SCALE;
    }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
Options::unzoom()
{
    if ( M_zoomed)
    {
        M_zoomed = false;

        int temp_width = M_canvas_width;
        M_canvas_width += 1;
        updateFieldSize( temp_width, M_canvas_height );
    }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
Options::updateFieldSize( const int canvas_width,
                          const int canvas_height )
{
    if ( M_canvas_width != canvas_width
         || M_canvas_height != canvas_height )
    {
        M_canvas_width = canvas_width;
        M_canvas_height = canvas_height;

        // adjust field scale to window size.
        if ( ! zoomed() )
        {
            double total_pitch_l = ( PITCH_LENGTH
                                     + PITCH_MARGIN * 2.0
                                     + 1.0 );
            double total_pitch_w = ( PITCH_WIDTH
                                     + PITCH_MARGIN * 2.0
                                     + 1.0 );

            M_field_scale = static_cast< double >( canvas_width ) / total_pitch_l;

            // automatically adjust a field scale
            if ( total_pitch_w * fieldScale() > canvas_height )
            {
                M_field_scale = static_cast< double >( canvas_height ) / total_pitch_w;
            }

            // check the scale threshold
            if ( fieldScale() < MIN_FIELD_SCALE )
            {
                M_field_scale = MIN_FIELD_SCALE;
            }

            M_field_scale = rint( M_field_scale * 100.0 ) / 100.0;
        }
    }

}

/*-------------------------------------------------------------------*/
/*!

 */
/*-------------------------------------------------------------------*/
/*!

 */
