// -*-c++-*-

/*!
  \file config_dialog.cpp
  \brief Config Dialog class Source File.
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

#include "config_dialog.h"

#include "options.h"
#include "main_data.h"

#include <iostream>
#include <cassert>

/*-------------------------------------------------------------------*/
/*!

*/
ConfigDialog::ConfigDialog( QWidget * parent,
                            const MainData & main_data )
    : QDialog( parent )
    , M_main_data( main_data )
{
    this->setWindowTitle( tr( "Config" ) );

    createWidgets();
}

/*-------------------------------------------------------------------*/
/*!

*/
ConfigDialog::~ConfigDialog()
{
    //std::cerr << "delete ConfigDialog" << std::endl;
}

/*-------------------------------------------------------------------*/
/*!

*/
void
ConfigDialog::createWidgets()
{
    M_tab_widget = new QTabWidget();
    QVBoxLayout * top_layout = new QVBoxLayout();

    // canvas
    {
        QFrame * frame = new QFrame();
        QVBoxLayout * layout = new QVBoxLayout();
        layout->setSizeConstraint( QLayout::SetFixedSize );
        layout->setMargin( 4 );
        layout->setSpacing( 4 );

        layout->addWidget( createZoomControls(),
                           0, Qt::AlignLeft );
        layout->addWidget( createCanvasSizeControls(),
                           0, Qt::AlignLeft );
        layout->addWidget( createMiscControls(),
                           0, Qt::AlignLeft );

        frame->setLayout( layout );
        M_tab_widget->addTab( frame, tr( "Canvas" ) );
    }
    // show
    {
        QFrame * frame = new QFrame();
        QVBoxLayout * layout = new QVBoxLayout();
        layout->setSizeConstraint( QLayout::SetFixedSize );
        layout->setMargin( 4 );
        layout->setSpacing( 4 );

        layout->addWidget( createShowControls(),
                           0, Qt::AlignLeft );
        layout->addWidget( createGridStepControls(),
                           0, Qt::AlignLeft );

        frame->setLayout( layout );
        M_tab_widget->addTab( frame, tr( "Show" ) );
    }

    top_layout->addWidget( M_tab_widget );
    this->setLayout( top_layout );
}

/*-------------------------------------------------------------------*/
/*!

*/
QWidget *
ConfigDialog::createZoomControls()
{
    QGroupBox * group_box = new QGroupBox( tr( "Zoom" ) );

    QVBoxLayout * top_layout = new QVBoxLayout();
    top_layout->setSizeConstraint( QLayout::SetFixedSize );
    top_layout->setMargin( 1 );
    top_layout->setSpacing( 0 );

    const QFontMetrics metrics = this->fontMetrics();
    const int button_height = metrics.height() + 12;

    {
        QHBoxLayout * layout = new QHBoxLayout();
        layout->setSpacing( 0 );

        QPushButton * zoomin_button = new QPushButton( tr( "+" ) );
        zoomin_button->setMaximumSize( 48, button_height );
        connect( zoomin_button, SIGNAL( clicked() ),
                 this, SLOT( zoomIn() ) );
        layout->addWidget( zoomin_button );
        //
        QPushButton * zoomout_button = new QPushButton( tr( "-" ) );
        zoomout_button->setMaximumSize( 48, button_height );
        connect( zoomout_button, SIGNAL( clicked() ),
                 this, SLOT( zoomOut() ) );
        layout->addWidget( zoomout_button );
        //
        layout->addSpacing( 1 );
        layout->addStretch( 1 );
        //
        QPushButton * fit_button = new QPushButton( tr( "Fit" ) );
        fit_button->setMaximumSize( 60, button_height );
        connect( fit_button, SIGNAL( clicked() ),
                 this, SLOT( unzoom() ) );
        layout->addWidget( fit_button );

        top_layout->addLayout( layout );
    }

    {
        QHBoxLayout * layout = new QHBoxLayout();
        layout->setSpacing( 0 );

        layout->addWidget( new QLabel( tr( "Scale:" ) ) );

        layout->addSpacing( 2 );

        M_scale_slider = new QSlider( Qt::Horizontal );
        M_scale_slider->setRange( static_cast< int >( Options::MIN_FIELD_SCALE * 10.0 ),
                                  static_cast< int >( Options::MAX_FIELD_SCALE * 10.0 ) );
        M_scale_slider->setValue( 80 );
        M_scale_slider->setSingleStep( 1 );
        M_scale_slider->setPageStep( 1 ); // set the minimal increment/decrement step
        M_scale_slider->setMinimumSize( 250, 24 );
        connect( M_scale_slider, SIGNAL( sliderMoved( int ) ),
                 this, SLOT( slideFieldScale( int ) ) );
        layout->addWidget( M_scale_slider );

        layout->addSpacing( 2 );

        M_scale_text = new QLineEdit( tr( "0.0" ) );
        M_scale_text->setValidator( new QDoubleValidator( 0.0, 400.0, 3, M_scale_text ) );
        M_scale_text->setMaximumSize( 48, 24 );
        connect( M_scale_text, SIGNAL( textChanged( const QString & ) ),
                 this, SLOT( editFieldScale( const QString & ) ) );
        layout->addWidget( M_scale_text );

        top_layout->addLayout( layout );
    }


    group_box->setLayout( top_layout );
    return group_box;;
}

/*-------------------------------------------------------------------*/
/*!

*/
QWidget *
ConfigDialog::createCanvasSizeControls()
{
    QGroupBox * group_box = new QGroupBox( tr( "Canvas Size" ) );

    QHBoxLayout * layout = new QHBoxLayout();
    layout->setMargin( 1 );
    layout->setSpacing( 0 );

    layout->addWidget( new QLabel( tr( " Width:" ) ) );

    M_canvas_width_text = new QLineEdit( tr( "640" ) );
    M_canvas_width_text->setValidator( new QIntValidator( 100, 3000, M_canvas_width_text ) );
    M_canvas_width_text->setMaximumSize( 48, 24 );
    layout->addWidget( M_canvas_width_text );

    layout->addWidget( new QLabel( tr( " Height:" ) ) );

    M_canvas_height_text = new QLineEdit( tr( "480" ) );
    M_canvas_height_text->setValidator( new QIntValidator( 100, 3000, M_canvas_height_text ) );
    M_canvas_height_text->setMaximumSize( 48, 24 );
    layout->addWidget( M_canvas_height_text );

    layout->addSpacing( 12 );

    QPushButton * apply_canvas_size_btn = new QPushButton( tr( "apply" ) );
    apply_canvas_size_btn->setMaximumSize( 60, this->fontMetrics().height() + 12 );
    connect( apply_canvas_size_btn, SIGNAL( clicked() ),
             this, SLOT( applyCanvasSize() ) );
    layout->addWidget( apply_canvas_size_btn );

    group_box->setLayout( layout );
    return group_box;
}

QWidget *
ConfigDialog::createShowControls()
{
    QGroupBox * group_box = new QGroupBox( tr( "Show" ) );

    QVBoxLayout * top_layout = new QVBoxLayout();
    top_layout->setMargin( 1 );
    top_layout->setSpacing( 0 );

    group_box->setLayout( top_layout );
    return group_box;
}

/*-------------------------------------------------------------------*/
/*!

*/
QWidget *
ConfigDialog::createMiscControls()
{
    QGroupBox * group_box = new QGroupBox( tr( "Misc" ) );
    QVBoxLayout * top_layout = new QVBoxLayout();
    top_layout->setMargin( 1 );
    top_layout->setSpacing( 0 );

    //
    M_anti_aliasing_cb = new QCheckBox( tr( "Anti Aliasing" ) );
    M_anti_aliasing_cb->setChecked( Options::instance().antiAliasing() );
    connect( M_anti_aliasing_cb, SIGNAL( toggled( bool ) ),
             this, SLOT( clickAntiAliasing( bool ) ) );
    top_layout->addWidget( M_anti_aliasing_cb );

    group_box->setLayout( top_layout );
    return group_box;
}

/*-------------------------------------------------------------------*/
/*!

*/
QWidget *
ConfigDialog::createGridStepControls()
{
    QGroupBox * group_box = new QGroupBox( tr( "Grid Lines" ) );
    QVBoxLayout * top_layout = new QVBoxLayout();
    top_layout->setMargin( 1 );
    top_layout->setSpacing( 0 );

    M_show_grid_coord_cb = new QCheckBox( tr( "Grid Coordinate" ) );
    M_show_grid_coord_cb->setChecked( Options::instance().showGridCoord() );
    connect( M_show_grid_coord_cb, SIGNAL( toggled( bool ) ),
             this, SLOT( clickShowGridCoord( bool ) ) );
    top_layout->addWidget( M_show_grid_coord_cb );

    //
    QHBoxLayout * layout = new QHBoxLayout();
    //layout->setMargin( 0 );
    //layout->setSpacing( 0 );
    //
    layout->addWidget( new QLabel( tr( "Step:" ) ) );
    //
    M_grid_step_slider = new QSlider( Qt::Horizontal );
    M_grid_step_slider->setRange( 0, 1000 );
    M_grid_step_slider->setValue( static_cast< int >( rint( Options::instance().gridStep() * 10.0 ) ) );
    M_grid_step_slider->setSingleStep( 1 );
    M_grid_step_slider->setPageStep( 1 );
    M_grid_step_slider->setMinimumSize( 260, 24 );
    connect( M_grid_step_slider, SIGNAL( sliderMoved( int ) ),
             this, SLOT( slideGridStep( int ) ) );
    layout->addWidget( M_grid_step_slider );

    //
    M_grid_step_text = new QLineEdit( tr( " 0.0" )  );
    M_grid_step_text->setValidator( new QDoubleValidator( 0.0, 100.0, 3, M_grid_step_text ) );
    M_grid_step_text->setMaximumSize( 48, 24 );
    M_grid_step_text->setText( QString::number( rint( Options::instance().gridStep() / 0.001 ) * 0.001 ) );
    connect( M_grid_step_text, SIGNAL( textChanged( const QString & ) ),
             this, SLOT( editGridStep( const QString & ) ) );
    layout->addWidget( M_grid_step_text );

    top_layout->addLayout( layout );
    group_box->setLayout( top_layout );
    return group_box;
}

/*!

*/
void
ConfigDialog::showEvent( QShowEvent * event )
{
    updateAll();
    event->accept();
}

/*-------------------------------------------------------------------*/
/*!

*/
void
ConfigDialog::updateAll()
{
    const Options & opt = Options::instance();

    updateFieldScale();

    M_canvas_width_text->setText( QString::number( opt.canvasWidth() ) );
    M_canvas_height_text->setText( QString::number( opt.canvasHeight() ) );

    M_anti_aliasing_cb->setChecked( opt.antiAliasing() );

}

/*-------------------------------------------------------------------*/
/*!

*/
void
ConfigDialog::updateFieldScale()
{
    int iscale = static_cast< int >( rint( Options::instance().fieldScale() * 10.0 ) );
    if ( M_scale_slider->value() != iscale )
    {
        M_scale_slider->setValue( iscale );
    }

    char buf[16];
    snprintf( buf, 16, "%.2f", Options::instance().fieldScale() );
    M_scale_text->setText( QString::fromAscii( buf ) );
}

/*-------------------------------------------------------------------*/
/*!

*/
void
ConfigDialog::zoomIn()
{
    Options::instance().zoomIn();

    updateFieldScale();

    emit configured();
}

/*-------------------------------------------------------------------*/
/*!

*/
void
ConfigDialog::zoomOut()
{
    Options::instance().zoomOut();

    updateFieldScale();

    emit configured();
}

/*-------------------------------------------------------------------*/
/*!

*/
void
ConfigDialog::unzoom()
{
    Options::instance().unzoom();
    updateFieldScale();

    emit configured();
}

/*-------------------------------------------------------------------*/
/*!

*/
/*-------------------------------------------------------------------*/
/*!

*/
void
ConfigDialog::slideFieldScale( int value )
{
    double scale = value * 0.1;

    if ( std::fabs( scale - Options::instance().fieldScale() ) >= 0.01 )
    {
        M_scale_text->setText( QString::number( scale ) );
        Options::instance().setFieldScale( scale );

        emit configured();
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
ConfigDialog::editFieldScale( const QString & text )
{
    bool ok = true;
    double value = text.toDouble( &ok );

    if ( ok
         && std::fabs( value - Options::instance().fieldScale() ) >= 0.01 )
    {
        int ivalue = static_cast< int >( rint( value * 10.0 ) );
        M_scale_slider->setValue( ivalue );
        Options::instance().setFieldScale( value );

        emit configured();
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
ConfigDialog::applyCanvasSize()
{
    bool ok_w = true;
    bool ok_h = true;
    int width = M_canvas_width_text->text().toInt( & ok_w );
    int height = M_canvas_height_text->text().toInt( & ok_h );

    if ( ok_w
         && ok_h
         && width > 0
         && height > 0 )
    {
        emit canvasResized( QSize( width, height ) );
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
ConfigDialog::clickAntiAliasing( bool checked )
{
    if ( Options::instance().antiAliasing() != checked )
    {
        Options::instance().toggleAntiAliasing();

        emit configured();
    }
}


void
ConfigDialog::clickShowDrawInfo( bool checked )
{
    if ( Options::instance().showDrawInfo() != checked )
    {
        Options::instance().toggleShowDrawInfo();
        emit configured();
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
ConfigDialog::toggleShowDrawInfo()
{
    Options::instance().toggleShowDrawInfo();
    M_show_draw_info_cb->setChecked( Options::instance().showDrawInfo() );

    emit configured();
}

/*-------------------------------------------------------------------*/
/*!

*/
void
ConfigDialog::clickShowGridCoord( bool checked )
{
    if ( Options::instance().showGridCoord() != checked )
    {
        Options::instance().toggleShowGridCoord();
        emit configured();
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
ConfigDialog::slideGridStep( int value )
{
    M_grid_step_text->setText( QString::number( value * 0.1 ) );

    Options::instance().setGridStep( value * 0.1 );

    emit configured();
}

/*-------------------------------------------------------------------*/
/*!

*/
void
ConfigDialog::editGridStep( const QString & text )
{
    bool ok = true;
    double value = text.toDouble( & ok );

    if ( ok )
    {
        M_grid_step_slider->setValue( static_cast< int >( rint( value * 10.0 ) ) );
        Options::instance().setGridStep( rint( value / 0.001 ) * 0.001 );

        emit configured();
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
void
ConfigDialog::setFocusPoint( const QPoint & point )
{
    Options::instance().setFocusPoint( point.x(), point.y() );

    emit configured();
}

