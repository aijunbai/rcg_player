// -*-c++-*-

/*!
  \file field_canvas.cpp
  \brief main field canvas class Source File.
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
#include <sstream>
#include <iomanip>

#include "field_canvas.h"

#include "field_painter.h"
#include "draw_info_painter.h"

// model
#include "main_data.h"
#include "options.h"

#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

/*-------------------------------------------------------------------*/
/*!

*/
FieldCanvas::FieldCanvas( MainData & main_data )
    :
#ifdef USE_GLWIDGET
    QGLWidget( QGLFormat( QGL::SampleBuffers ) ),
#endif
    M_main_data( main_data ),
    M_normal_menu( static_cast< QMenu * >( 0 ) ),
    M_system_menu( static_cast< QMenu * >( 0 ) ),
    M_measure_line_pen( QColor( 0, 255, 255 ), 0, Qt::SolidLine ),
    M_measure_mark_pen( QColor( 255, 0, 0 ), 0, Qt::SolidLine ),
    M_measure_font_pen( QColor( 255, 191, 191 ), 0, Qt::SolidLine ),
    M_measure_font_pen2( QColor( 224, 224, 192 ), 0, Qt::SolidLine ),
    M_measure_font( "6x13bold", 9 )
    , M_current_time( 0 )
{
    this->setMouseTracking( true ); // need for the MouseMoveEvent
    this->setFocusPolicy( Qt::WheelFocus );

    readSettings();

    createPainters();
}

/*-------------------------------------------------------------------*/
/*!

*/
FieldCanvas::~FieldCanvas()
{
    writeSettings();
}

/*-------------------------------------------------------------------*/
/*!

*/
void
FieldCanvas::readSettings()
{
#ifndef Q_WS_WIN
    QSettings settings( QDir::homePath() + "/.rcg",
                        QSettings::IniFormat );
#else
    QSettings settings( QDir::currentPath() + "/rcg.ini",
                        QSettings::IniFormat );
#endif

    settings.beginGroup( "FieldCanvas" );

    QVariant val;

    val = settings.value( "measure_line_pen" );
    if ( val.isValid() ) M_measure_line_pen.setColor( val.toString() );

    val = settings.value( "measure_mark_pen" );
    if ( val.isValid() ) M_measure_mark_pen.setColor( val.toString() );

    val = settings.value( "measure_font_pen" );
    if ( val.isValid() ) M_measure_font_pen.setColor( val.toString() );

    val = settings.value( "measure_font_pen2" );
    if ( val.isValid() ) M_measure_font_pen2.setColor( val.toString() );

    val = settings.value( "measure_font" );
    if ( val.isValid() ) M_measure_font.fromString( val.toString() );

    settings.endGroup();
}

/*-------------------------------------------------------------------*/
/*!

*/
void
FieldCanvas::writeSettings()
{
#ifndef Q_WS_WIN
    QSettings settings( QDir::homePath() + "/.rcg",
                        QSettings::IniFormat );
#else
    QSettings settings( QDir::currentPath() + "/rcg.ini",
                        QSettings::IniFormat );
#endif

    settings.beginGroup( "FieldCanvas" );

    settings.setValue( "measure_line_pen", M_measure_line_pen.color().name() );
    settings.setValue( "measure_mark_pen", M_measure_mark_pen.color().name() );
    settings.setValue( "measure_font_pen", M_measure_font_pen.color().name() );
    settings.setValue( "measure_font_pen2", M_measure_font_pen2.color().name() );
    settings.setValue( "measure_font", M_measure_font.toString() );

    settings.endGroup();
}

/*-------------------------------------------------------------------*/
/*!

*/
void
FieldCanvas::createPainters()
{
    M_painters.clear();

    M_field_painter = boost::shared_ptr< FieldPainter >( new FieldPainter( M_main_data ) );

    M_painters.push_back( boost::shared_ptr< PainterInterface >
                          ( new DrawInfoPainter( M_main_data ) ) );
}

/*-------------------------------------------------------------------*/
/*!

*/
void
FieldCanvas::setNormalMenu( QMenu * menu )
{
    if ( M_normal_menu )
    {
        delete M_normal_menu;
        M_normal_menu = static_cast< QMenu * >( 0 );
    }

    M_normal_menu = menu;
}

/*-------------------------------------------------------------------*/
/*!

*/
void
FieldCanvas::setSystemMenu( QMenu * menu )
{
    if ( M_system_menu )
    {
        delete M_system_menu;
        M_system_menu = static_cast< QMenu * >( 0 );
    }

    M_system_menu = menu;
}

/*-------------------------------------------------------------------*/
/*!

*/
void
FieldCanvas::paintEvent( QPaintEvent * )
{
    QPixmap pixmap(width(), height());
    QPainter painter( &pixmap );

    if ( Options::instance().antiAliasing() )
    {
         painter.setRenderHint( QPainter::Antialiasing );
    }

    draw( painter );

    // draw mouse measure

    if ( M_mouse_state[2].isDragged() )
    {
        drawMouseMeasure( painter );
    }

    painter.setPen(QPen(Qt::black, 5.0));
    painter.drawRect(0, 0, width(), height());

    const int current_time = M_main_data.index();

    std::stringstream ss2;
    ss2 << "/home/baj/Documents/Publications/AAAI-15/MOT/depth/frame_" << setw(4) << setfill('0') << current_time << ".png";
    QPixmap pixmap2(QString::fromStdString(ss2.str()));

    QPixmap pixmap3(width() * 2.0, height());
    QPainter painter3( &pixmap3 );

    painter3.drawPixmap(QPointF(0, 0), pixmap2);
    painter3.drawPixmap(QPointF(width(), 0), pixmap);

    std::stringstream ss;
    ss << "/tmp/baj/frame_" << setw(4) << setfill('0') << current_time << ".png";

    pixmap3.save(QString::fromStdString(ss.str()), "PNG");

    QPainter painter2( this );
    painter2.drawPixmap(QPointF(0, 0), pixmap);
}

/*-------------------------------------------------------------------*/
/*!

*/
bool
FieldCanvas::event( QEvent * event)
{
    if (event->type() == QEvent::ToolTip)
    {
    }
    return QWidget::event(event);
}

/*-------------------------------------------------------------------*/
/*!

*/
void
FieldCanvas::mouseDoubleClickEvent( QMouseEvent * event )
{
    this->unsetCursor();

    if ( event->button() == Qt::LeftButton )
    {
        emit focusChanged( event->pos() );
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
FieldCanvas::mousePressEvent( QMouseEvent * event )
{
    if ( event->button() == Qt::LeftButton )
    {
        M_mouse_state[0].pressed( event->pos() );
        if ( M_mouse_state[1].isMenuFailed() )
        {
            M_mouse_state[1].setMenuFailed( false );
        }

        if ( event->modifiers() == Qt::ControlModifier )
        {
            emit focusChanged( event->pos() );
        }
        else
        {
        }
    }
    else if ( event->button() == Qt::MidButton )
    {
        M_mouse_state[1].pressed( event->pos() );
        if ( M_mouse_state[1].isMenuFailed() )
        {
            M_mouse_state[1].setMenuFailed( false );
        }
    }
    else if ( event->button() == Qt::RightButton )
    {
        M_mouse_state[2].pressed( event->pos() );
        if ( M_mouse_state[2].isMenuFailed() )
        {
            M_mouse_state[2].setMenuFailed( false );
        }
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
FieldCanvas::mouseReleaseEvent( QMouseEvent * event )
{
    this->unsetCursor();

    if ( event->button() == Qt::LeftButton )
    {
        M_mouse_state[0].released();

        if ( M_mouse_state[0].isMenuFailed() )
        {
            M_mouse_state[0].setMenuFailed( false );
        }
        else if ( M_mouse_state[0].pressedPoint() == event->pos() )
        {
        }
        else
        {

        }
    }
    else if ( event->button() == Qt::MidButton )
    {
        M_mouse_state[1].released();
    }
    else if ( event->button() == Qt::RightButton )
    {
        M_mouse_state[2].released();

        if ( M_mouse_state[2].isMenuFailed() )
        {
            M_mouse_state[2].setMenuFailed( false );
        }
        else if ( M_mouse_state[2].pressedPoint() == event->pos() )
        {
            {
                if ( M_normal_menu
                     && ! M_normal_menu->exec( event->globalPos() ) )
                {
                    M_mouse_state[2].setMenuFailed( true );
                }
            }
        }
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
FieldCanvas::mouseMoveEvent( QMouseEvent * event )
{
    if ( this->cursor().shape() == Qt::BlankCursor )
    {
        this->unsetCursor();
    }

    if ( M_mouse_state[0].isDragged() )
    {
#if QT_VERSION >= 0x040200
        if ( this->cursor().shape() != Qt::ClosedHandCursor )
        {
            this->setCursor( QCursor( Qt::ClosedHandCursor ) );
        }
#else
        if ( this->cursor().shape() != Qt::SizeAllCursor )
        {
            this->setCursor( QCursor( Qt::SizeAllCursor ) );
        }
#endif

        int new_x = Options::instance().screenX( Options::instance().focusPoint().x() );
        int new_y = Options::instance().screenY( Options::instance().focusPoint().y() );
        new_x -= ( event->pos().x() - M_mouse_state[0].draggedPoint().x() );
        new_y -= ( event->pos().y() - M_mouse_state[0].draggedPoint().y() );
        emit focusChanged( QPoint( new_x, new_y ) );
    }

    for ( int i = 0; i < 3; ++i )
    {
        M_mouse_state[i].moved( event->pos() );
    }

    if ( M_mouse_state[2].isDragged() )
    {
        static QRect s_last_rect;

        if ( this->cursor().shape() != Qt::CrossCursor )
        {
            this->setCursor( QCursor( Qt::CrossCursor ) );
        }

        QRect new_rect
            = QRect( M_mouse_state[2].pressedPoint(),
                     M_mouse_state[2].draggedPoint() ).normalized();
        new_rect.adjust( -32, -32, 32, 32 );
        if ( new_rect.right() < M_mouse_state[2].draggedPoint().x() + 256 )
        {
            new_rect.setRight( M_mouse_state[2].draggedPoint().x() + 256 );
        }
        // draw mouse measure
        this->update( s_last_rect.unite( new_rect ) );
        s_last_rect = new_rect;
    }

    emit mouseMoved( event->pos() );
}

/*-------------------------------------------------------------------*/
/*!

*/
void
FieldCanvas::draw( QPainter & painter )
{
    updateFocus();
    // update field scale and related things
    Options::instance().updateFieldSize( this->width(), this->height() );

    M_field_painter->draw( painter );

    for ( std::vector< boost::shared_ptr< PainterInterface > >::iterator
              it = M_painters.begin();
          it != M_painters.end();
          ++it )
    {
        (*it)->draw( painter );
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
FieldCanvas::drawMouseMeasure( QPainter & painter )
{
    const Options & opt = Options::instance();

    QPoint start_point = M_mouse_state[2].pressedPoint();
    QPoint end_point = M_mouse_state[2].draggedPoint();

    // draw straight line
    painter.setPen( M_measure_line_pen );
    painter.setBrush( Qt::NoBrush );
    painter.drawLine( start_point, end_point );

    // draw mark
    painter.setPen( M_measure_mark_pen );
    painter.drawEllipse( start_point.x() - 2,
                         start_point.y() - 2,
                         4,
                         4 );
    painter.drawEllipse( end_point.x() - 2,
                         end_point.y() - 2,
                         4,
                         4 );

    // draw distance & angle text
    painter.setFont( M_measure_font );
    painter.setPen( M_measure_font_pen );

    char buf[64];

    // draw start point value
    QPointF start_real( opt.fieldX( start_point.x() ),
                        opt.fieldY( start_point.y() ) );
    snprintf( buf, 64,
              "(%.2f,%.2f)",
              start_real.x(),
              start_real.y() );
    painter.drawText( start_point,
                      QString::fromAscii( buf ) );

    if ( std::abs( start_point.x() - end_point.x() ) < 1
         && std::abs( start_point.y() - end_point.y() ) < 1 )
    {
        return;
    }

    // draw end point value
    QPointF end_real( opt.fieldX( end_point.x() ),
                      opt.fieldY( end_point.y() ) );
    snprintf( buf, 64,
              "(%.2f,%.2f)",
              end_real.x(),
              end_real.y() );
    painter.drawText( end_point.x(),
                      end_point.y(),
                      QString::fromAscii( buf ) );

    // draw relative coordinate value
    painter.setPen( M_measure_font_pen2 );

    QPointF rel( end_real - start_real );
    double r = std::sqrt( std::pow( rel.x(), 2.0 ) + std::pow( rel.y(), 2.0 ) );
    double th = ( rel.x() == 0.0 && rel.y() == 0.0
                   ? 0.0
                   : std::atan2( rel.y(), rel.x() ) * 180.0 / M_PI );

    snprintf( buf, 64,
              "rel(%.2f,%.2f) r%.2f th%.1f",
              rel.x(), rel.y(), r, th );

    int dist_add_y = ( end_point.y() > start_point.y()
                       ? + painter.fontMetrics().height()
                       : - painter.fontMetrics().height() );
    painter.drawText( end_point.x(),
                      end_point.y() + dist_add_y,
                      QString::fromAscii( buf ) );
}

void FieldCanvas::updateFocus()
{
    Options & opt = Options::instance();

    if (!opt.timer()->isActive()) return;
    if (M_mouse_state[0].isDragged()) return;

    opt.setFocusPoint();
}
