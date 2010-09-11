// -*-c++-*-

/*!
  \file options.h
  \brief application setting variables.
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

#ifndef RCSSLOGPLAYER_OPTIONS_H
#define RCSSLOGPLAYER_OPTIONS_H

#include <QPoint>
#include <QPointF>

#include <rcg/types.h>

#include <string>
#include <cmath>

/*!
  \class Options
  \brief application setting holder singleton.
*/
class Options {
public:

    static const double PITCH_LENGTH;
    static const double PITCH_WIDTH;
    static const double PITCH_HALF_LENGTH;
    static const double PITCH_HALF_WIDTH;
    static const double PITCH_MARGIN;


    //! minimum field scale
    static const double MIN_FIELD_SCALE;
    //! maximum field scale
    static const double MAX_FIELD_SCALE;
    //! zoom rate factor
    static const double ZOOM_RATIO;
    //! default logplayer timer step (ms).
    static const int DEFAULT_TIMER_INTERVAL;

private:

    //
    // logplayer options
    //
    bool M_minimum_mode;
    std::string M_game_log_file; //!< game log file path to be opened
    std::string M_output_file;
    int M_timer_interval; //!< logplayer's timer interval. default 100[ms]

    //
    // window options
    //
    int M_window_x;
    int M_window_y;
    int M_window_width;
    int M_window_height;
    bool M_maximize;
    bool M_full_screen;

    int M_canvas_width;
    int M_canvas_height;

    bool M_hide_menu_bar;
    bool M_hide_tool_bar;
    bool M_hide_status_bar;

    //
    // view options
    //

    bool M_anti_aliasing;

    bool M_show_draw_info;

    double M_grid_step;
    bool M_show_grid_coord;

    // zoom
    double M_field_scale;
    bool M_zoomed;
    QPoint M_field_center; //!< field center point on the screen

    // focus
    QPointF M_focus_point; //!< real coordinates

    //! private access for singleton
    Options();

    //! noncopyable
    Options( const Options & );
    //! noncopyable
    Options & operator=( const Options & );

public:
    ~Options();

    static
    Options & instance();

    /*!
      \biref analyze command line options
    */

    //
    // logplayer options
    //

    bool minimumMode() const
      {
          return M_minimum_mode;
      }
    void toggleMinimumMode()
      {
          M_minimum_mode = ! M_minimum_mode;
      }

    const
    std::string & gameLogFile() const
      {
          return M_game_log_file;
      }
    void setGameLogFile( const std::string & path )
      {
          M_game_log_file = path;
      }

    const
    std::string & outputFile() const
      {
          return M_output_file;
      }

    int timerInterval() const
      {
          return M_timer_interval;
      }

    //
    // window option
    //

    int windowX() const
      {
          return M_window_x;
      }

    int windowY() const
      {
          return M_window_y;
      }

    int windowWidth() const
      {
          return M_window_width;
      }

    int windowHeight() const
      {
          return M_window_height;
      }

    bool maximize() const
      {
          return M_maximize;
      }

    bool fullScreen() const
      {
          return M_full_screen;
      }

    int canvasWidth() const
      {
          return M_canvas_width;
      }

    int canvasHeight() const
      {
          return M_canvas_height;
      }

    bool hideMenuBar() const
      {
          return M_hide_menu_bar;
      }

    bool hideToolBar() const
      {
          return M_hide_tool_bar;
      }

    bool hideStatusBar() const
      {
          return M_hide_status_bar;
      }

    //
    // view options
    //

    bool antiAliasing() const
      {
          return M_anti_aliasing;
      }
    void toggleAntiAliasing()
      {
          M_anti_aliasing = ! M_anti_aliasing;
      }

    bool showDrawInfo() const
      {
          return M_show_draw_info;
      }
    void toggleShowDrawInfo()
      {
          M_show_draw_info = ! M_show_draw_info;
      }

    const
    double & gridStep() const
      {
          return M_grid_step;
      }
    void setGridStep( const double & value )
      {
          M_grid_step = value;
      }

    bool showGridCoord() const
      {
          return M_show_grid_coord;
      }
    void toggleShowGridCoord()
      {
          M_show_grid_coord = ! M_show_grid_coord;
      }

    // field scale

    void updateFieldSize( const int canvas_width,
                          const int canvas_height );

    const
    double & fieldScale() const
      {
          return M_field_scale;
      }
    void setFieldScale( const double & value );

    bool zoomed() const
      {
          return M_zoomed;
      }
    void zoomIn();
    void zoomOut();
    void unzoom();

    const
    QPoint & fieldCenter() const
      {
          return M_field_center;
      }

    const
    QPointF & focusPoint() const
      {
          return M_focus_point;
      }
    void setFocusPoint( const int screen_x,
                        const int screen_y );
    void setFocusPointReal( const double & x,
                            const double & y )
      {
          M_focus_point.setX( x );
          M_focus_point.setY( y );
      }

    int scale( const double & len ) const
      {
          return static_cast< int >( ::rint( len * M_field_scale ) );
      }

    int screenX( const double & x ) const
      {
          return M_field_center.x() + scale( x );
      }

    int screenY( const double & y ) const
      {
          return M_field_center.y() + scale( y );
      }

    double fieldX( const int x ) const
      {
          return ( x - M_field_center.x() ) / M_field_scale;
      }

    double fieldY( const int y ) const
      {
          return ( y - M_field_center.y() ) / M_field_scale;
      }
};

#endif
