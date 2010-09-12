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
    ,  M_focus_point( 0.0, 0.0 )
      , M_field_center(0, 0)
{
    readSettings();
}

/*-------------------------------------------------------------------*/
/*!

 */
Options::~Options()
{
    writeSettings();
}

void
Options::setFocusPoint( const int screen_x,
                                const int screen_y )
{
    M_focus_point.setX( fieldX( screen_x ) );
    M_focus_point.setY( fieldY( screen_y ) );
}


void
Options::readSettings()
{
#ifndef Q_WS_WIN
    QSettings settings( QDir::homePath() + "/.rcg",
                        QSettings::IniFormat );
#else
    QSettings settings( QDir::currentPath() + "/rcg.ini",
                        QSettings::IniFormat );
#endif

    settings.beginGroup( "Global" );

    QVariant val;

    val = settings.value( "timer_interval" );
    if ( val.isValid() ) M_timer_interval = val.toInt();

    val = settings.value( "window_width" );
    if ( val.isValid() ) M_window_width = val.toInt();

    val = settings.value( "window_height" );
    if ( val.isValid() ) M_window_height = val.toInt();

    val = settings.value( "maximize" );
    if ( val.isValid() ) M_maximize = val.toBool();

    val = settings.value( "full_screen" );
    if ( val.isValid() ) M_full_screen = val.toBool();

    val = settings.value( "hide_menu_bar" );
    if ( val.isValid() ) M_hide_menu_bar = val.toBool();

    val = settings.value( "hide_tool_bar" );
    if ( val.isValid() ) M_hide_tool_bar = val.toBool();

    val = settings.value( "hide_status_bar" );
    if ( val.isValid() ) M_hide_status_bar = val.toBool();

    val = settings.value( "anti_aliasing" );
    if ( val.isValid() ) M_anti_aliasing = val.toBool();

    val = settings.value( "show_draw_info" );
    if ( val.isValid() ) M_show_draw_info = val.toBool();

    val = settings.value( "show_grid_coord", M_show_grid_coord );
    if ( val.isValid() ) M_show_grid_coord = val.toBool();

    val = settings.value( "grid_step", M_grid_step );
    if ( val.isValid() ) M_grid_step = val.toDouble();

    settings.endGroup();
}

/*-----------------------------------------------------------------*/
/*!

 */
void
Options::writeSettings()
{
#ifndef Q_WS_WIN
    QSettings settings( QDir::homePath() + "/.rcg",
                        QSettings::IniFormat );
#else
    QSettings settings( QDir::currentPath() + "/rcg.ini",
                        QSettings::IniFormat );
#endif

    settings.beginGroup( "Global" );

     settings.setValue( "canvas_width", M_canvas_width );
     settings.setValue( "canvas_height", M_canvas_height );
     settings.setValue( "hide_menu_bar", M_hide_menu_bar );
    settings.setValue( "anti_aliasing", M_anti_aliasing );
    settings.setValue( "show_draw_info", M_show_draw_info );
    settings.setValue( "show_grid_coord", M_show_grid_coord );
    settings.setValue( "grid_step", M_grid_step );

    settings.endGroup();
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
    if ( M_zoomed || focusPoint().x() != 0.0
                     || focusPoint().y() != 0.0 )
    {
        M_zoomed = false;
        M_focus_point.setX( 0.0 );
        M_focus_point.setY( 0.0 );

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

        if ( ! zoomed() )
        {
            M_field_scale = MIN_FIELD_SCALE;
            M_field_scale = rint( M_field_scale * 100.0 ) / 100.0;
        }
    }

     M_field_center.setX( canvas_width/2 - scale( focusPoint().x() ) );
     M_field_center.setY( canvas_height/2 - scale( focusPoint().y() ) );

}

/*-------------------------------------------------------------------*/
/*!

 */
/*-------------------------------------------------------------------*/
/*!

 */



bool
Options::parseCmdLine( int argc,
                       char ** argv )
{
#ifdef HAVE_BOOST_PROGRAM_OPTIONS
    namespace po = boost::program_options;

    std::string geometry;
//     std::string canvas_size;

    po::options_description visibles( "Allowed options:" );

    visibles.add_options()
        ( "help,h",
          "print this message." )
        ( "version,v",
          "print version information." )
        // logplayer options
        ( "minimum-mode",
          po::bool_switch( &M_minimum_mode )->default_value( M_minimum_mode ),
          "start logplayer with minimum mode." )
        ( "timer-interval",
          po::value< int >( &M_timer_interval )->default_value( DEFAULT_TIMER_INTERVAL ),
          "set the logplayer timer interval." )
        // window options
        ( "geometry",
          po::value< std::string >( &geometry )->default_value( "" ),
          "specifies the window geometry ([WxH][+X+Y]). e.g. --geometry=1024x768+1+1" )
//         ( "canvas-size",
//           po::value< std::string >( &canvas_size )->default_value( "" ),
//           "specifies the canvas size(WxH). e.g. --canvas-size=1024x768" )
        ( "maximize",
          po::bool_switch( &M_maximize )->default_value( M_maximize ),
          "start with a maximized window." )
        ( "full-screen",
          po::bool_switch( &M_full_screen )->default_value( M_full_screen ),
          "start with a full screen window." )
        ( "hide-menu-bar",
          po::bool_switch( &M_hide_menu_bar )->default_value( M_hide_menu_bar ),
          "start without a menu bar." )
        ( "hide-tool-bar",
          po::bool_switch( &M_hide_tool_bar )->default_value( M_hide_tool_bar ),
          "start without a tool bar." )
        ( "hide-status-bar",
          po::bool_switch( &M_hide_status_bar )->default_value( M_hide_status_bar ),
          "start without a status bar." )
        // view options
        ( "anti-aliasing",
          po::value< bool >( &M_anti_aliasing )->default_value( true, "on" ),
          "show anti-aliased objects." )
        ( "show-draw-info",
          po::value< bool >( &M_show_draw_info )->default_value( true, "on" ),
          "show team draw information." )
        ( "show-grid-coord",
          po::value< bool >( &M_show_grid_coord )->default_value( false, "off" ),
          "show grid line coordinate value." )
        ( "grid-step",
          po::value< double >( &M_grid_step )->default_value( 0.0, "0.0" ),
          "set a grid step size." )
        ;

    po::options_description invisibles( "Invisibles" );
    invisibles.add_options()
        ( "game-log-file",
          po::value< std::string >( &M_game_log_file )->default_value( "" ),
          "set the path to Game Log file(.rcg) to be opened.")
        ;

    po::positional_options_description pdesc;
    pdesc.add( "game-log-file", 1 );

    po::options_description all_desc( "All options:" );
    all_desc.add( visibles ).add( invisibles );


    bool help = false;
    bool version = false;
    try
    {
        po::variables_map vm;
        po::command_line_parser parser( argc, argv );
        parser.options( all_desc ).positional( pdesc );
        po::store( parser.run(), vm );
        po::notify( vm );

        help = vm.count( "help" );
        version = vm.count( "version" );
    }
    catch ( std::exception & e )
    {
        std::cerr << e.what() << std::endl;
        help = true;
    }

    if ( version )
    {
        std::cout << PACKAGE_NAME << " Version " << VERSION
                  << std::endl;
        if ( ! help )
        {
            return false;
        }
    }

    if ( help )
    {
        std::cout << "Usage: " << PACKAGE_NAME
                  << " [options ... ] [<GameLogFile>]\n";
        std::cout << visibles << std::endl;
        return false;
    }

    if ( M_timer_interval < 0 )
    {
        std::cerr << "Illegal timer interval " << M_timer_interval
                  << ". set default value." << std::endl;
        M_timer_interval = DEFAULT_TIMER_INTERVAL;
    }

    if ( M_timer_interval < 5 )
    {
        std::cerr << "Too small timer interval " << M_timer_interval
                  << ".  replaced by 5." << std::endl;
        M_timer_interval = 5;
    }

    if ( M_timer_interval > 5000 )
    {
        std::cerr << "Too huge timer interval " << M_timer_interval
                  << ".  replaced by 5000." << std::endl;
        M_timer_interval = 5000;
    }

    if ( ! geometry.empty() )
    {
        int w = -1, h = -1;
        int x = -1, y = -1;

        int num = std::sscanf( geometry.c_str(),
                               " %d x %d %d %d " ,
                               &w, &h, &x, &y );
        //std::cerr << "geometry = " << geometry
        //          << "  param_num=" << num
        //          << " width=" << w << " height=" << h
        //          << " x=" << x << " y=" << y
        //          << std::endl;
        if ( num == 4 || num == 2 )
        {
            if ( w <= 0 || h <= 0 )
            {
                std::cerr << "Illegal window size [" << geometry
                          << "]" << std::endl;
            }
            else
            {
                M_window_width = w;
                M_window_height = h;
                M_window_x = x;
                M_window_y = y;
            }
        }
        else if ( std::sscanf( geometry.c_str(),
                               " %d %d " ,
                               &x, &y ) == 2 )
        {
            //std::cerr << "only pos = "
            //          << " x=" << x
            //          << " y=" << y
            //          << std::endl;
            M_window_x = x;
            M_window_y = y;
        }
        else
        {
            std::cerr << "Illegal geometry format [" << geometry
                      << "]" << std::endl;
        }
    }

//     if ( ! canvas_size.empty() )
//     {
//         int w = -1, h = -1;
//         if ( std::sscanf( canvas_size.c_str(),
//                           " %d x %d ",
//                           &w, &h ) == 2
//              && w > 1
//              && h > 1 )
//         {
//             M_canvas_width = w;
//             M_canvas_height = h;
//         }
//         else
//         {
//             std::cerr << "Illegal canvas size format [" << canvas_size
//                       << "]" << std::endl;
//         }
//     }
#endif
    return true;
}
