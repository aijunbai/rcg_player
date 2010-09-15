// -*-c++-*-

/*!
  \file config_dialog.h
  \brief Config Dialog class Header File.
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

#ifndef RCSSLOGPLAYER_CONFIG_DIALOG_H
#define RCSSLOGPLAYER_CONFIG_DIALOG_H

#include <QDialog>

class QPushButton;
class QCheckBox;
class QCloseEvent;
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;
class QSlider;
class QSpinBox;
class QTabWidget;

class MainData;

class ConfigDialog
    : public QDialog {

    Q_OBJECT

private:

    const MainData & M_main_data;

    QTabWidget * M_tab_widget;

    // zoom control
    QSlider * M_scale_slider;
    QLineEdit * M_scale_text;

    // canvas size control
    QLineEdit * M_canvas_width_text;
    QLineEdit * M_canvas_height_text;

    // misc options
    QCheckBox * M_anti_aliasing_cb;

    QCheckBox * M_show_draw_info_cb;

    QSlider * M_grid_step_slider;
    QLineEdit * M_grid_step_text;
    QCheckBox * M_show_grid_coord_cb;

public:

    ConfigDialog( QWidget * parent,
                  const MainData & main_data );
    ~ConfigDialog();
private:

    void createWidgets();

    QWidget * createZoomControls();
    QWidget * createCanvasSizeControls();
    QWidget * createShowControls();
    QWidget * createFieldStyleControls();
    QWidget * createMiscControls();
    QWidget * createGridStepControls();


protected:

    void showEvent( QShowEvent * event );


private slots:

    // just update this dialog contents
    // no emit
    void updateAll();

    //-----------------------

    // connect to itself
    // emit configured()
    void slideFieldScale( int value );
    void editFieldScale( const QString & );

    void clickShowDrawInfo( bool checked );

    void clickShowGridCoord( bool checked );
    void slideGridStep( int value );
    void editGridStep( const QString & text );

    void clickAntiAliasing( bool checked );

    void setFocusPoint( const QPoint & point );

public slots:

    // just update this dialog contents
    // no emit
    void updateFieldScale();

    // connect to other objects
    // emit configured()
    void zoomIn();
    void zoomOut();
    void unzoom();

    void applyCanvasSize();

    void toggleShowDrawInfo();

signals:

    void configured();
    void canvasResized( const QSize & size );
};

#endif
