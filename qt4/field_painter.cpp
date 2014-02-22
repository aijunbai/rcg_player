// -*-c++-*-

/*!
  \file field_painter.cpp
  \brief field painter class Source File.
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

#include <QtGui>

#include "field_painter.h"

#include "field_canvas.h"
#include "main_data.h"
#include "options.h"

#include <iostream>

/*-------------------------------------------------------------------*/
/*!

 */
FieldPainter::FieldPainter( const MainData & main_data )
    : M_main_data( main_data )
    , M_field_brush( QColor( 31, 160, 31 ), Qt::SolidPattern )
    , M_line_pen( QColor( 0xaa, 0xaa, 0xaa ),1, Qt::SolidLine )
{
    readSettings();
}

/*-------------------------------------------------------------------*/
/*!

 */
FieldPainter::~FieldPainter()
{
    writeSettings();
}

/*-------------------------------------------------------------------*/
/*!

 */
void
FieldPainter::readSettings()
{
#ifndef Q_WS_WIN
    QSettings settings( QDir::homePath() + "/.rcg",
                        QSettings::IniFormat );
#else
    QSettings settings( QDir::currentPath() + "/rcg.ini",
                        QSettings::IniFormat );
#endif

    settings.beginGroup( "FieldPainter" );

    QVariant val;

    val = settings.value( "field_brush" );
    if ( val.isValid() ) M_field_brush.setColor( val.toString() );

    val = settings.value( "line_pen" );
    if ( val.isValid() ) M_line_pen.setColor( val.toString() );

    settings.endGroup();
}

/*-------------------------------------------------------------------*/
/*!

 */
void
FieldPainter::writeSettings()
{
#ifndef Q_WS_WIN
    QSettings settings( QDir::homePath() + "/.rcg",
                        QSettings::IniFormat );
#else
    QSettings settings( QDir::currentPath() + "/rcg.ini",
                        QSettings::IniFormat );
#endif

    settings.beginGroup( "FieldPainter" );

    settings.setValue( "field_brush", M_field_brush.color().name() );
    settings.setValue( "line_pen", M_line_pen.color().name() );

    settings.endGroup();
}

/*-------------------------------------------------------------------*/
/*!

 */
void
FieldPainter::draw( QPainter & painter )
{
    if ( Options::instance().minimumMode() )
    {
        painter.fillRect( painter.window(),
                          Qt::black );
        return;
    }

    if ( Options::instance().antiAliasing() )
    {
        painter.setRenderHint( QPainter::Antialiasing, false );
    }

    drawBackGround( painter );
    drawLines( painter );
    if ( Options::instance().gridStep() > 0.0 )
    {
        drawGrid( painter );
    }

    if ( Options::instance().antiAliasing() )
    {
        painter.setRenderHint( QPainter::Antialiasing );
    }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
FieldPainter::drawBackGround( QPainter & painter ) const
{
    // fill the whole region
    painter.fillRect( painter.window(),
                      M_field_brush );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
FieldPainter::drawLines( QPainter & painter ) const
{
    // set paint styles
    painter.setPen( M_line_pen );
    painter.setBrush( Qt::NoBrush );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
FieldPainter::drawGrid( QPainter & painter ) const
{
    const Options & opt = Options::instance();

    const double grid_step = opt.gridStep();
    const int istep = opt.scale( grid_step );
    if ( istep <= 2 )
    {
        return;
    }

    const QFontMetrics metrics = painter.fontMetrics();
    const int text_step_x = ( opt.showGridCoord()
                              ? metrics.width( QObject::tr( "-00.000" ) )
                              : 100000 );
    const int text_step_y = ( opt.showGridCoord()
                              ? metrics.ascent()
                              : 100000 );

    const QRect win = painter.window();

    const int max_ix = win.right();
    const int min_ix = win.left();
    const int max_iy = win.bottom();
    const int min_iy = win.top();
    const double max_x = opt.fieldX( max_ix );
    const double min_x = opt.fieldX( min_ix );
    const double max_y = opt.fieldY( max_iy );
    const double min_y = opt.fieldY( min_iy );

    const int coord_x_print_y = min_iy + metrics.ascent();
    //     std::cerr << "drawGrid  min_x = " << min_x
    //               << "  max_x = " << max_x
    //               << "  min_y = " << min_y
    //               << "  max_y = " << max_y
    //               << std::endl;

    painter.setPen( M_line_pen );
    painter.setBrush( Qt::NoBrush );

    QString text;

    double x = 0.0;
    while ( x < max_x )
    {
        int ix = opt.screenX( x );
        if ( istep > text_step_x )
        {
            text.sprintf( "%.3f", x );
            painter.drawText( ix, coord_x_print_y , text );
        }
        painter.drawLine( ix, max_iy, ix, min_iy );
        x += grid_step;
    }

    x = -grid_step;
    while ( min_x < x )
    {
        int ix = opt.screenX( x );
        if ( istep > text_step_x )
        {
            text.sprintf( "%.3f", x );
            painter.drawText( ix, coord_x_print_y, text );
        }
        painter.drawLine( ix, max_iy, ix, min_iy );
        x -= grid_step;
    }


    double y = 0.0;
    while ( y < max_y )
    {
        int iy = opt.screenY( y );
        if ( istep > text_step_y )
        {
            text.sprintf( "%.3f", y );
            painter.drawText( min_ix, iy, text );
        }
        painter.drawLine( max_ix, iy, min_ix, iy );
        y += grid_step;
    }

    y = -grid_step;
    while ( min_y < y )
    {
        int iy = opt.screenY( y );
        if ( istep > text_step_y )
        {
            text.sprintf( "%.3f", y );
            painter.drawText( min_ix, iy, text );
        }
        painter.drawLine( max_ix, iy, min_ix, iy );
        y -= grid_step;
    }
}
