// -*-c++-*-

/*!
  \file main_window.h
  \brief main application window class Header File.
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

#ifndef RCSSLOGPLAYER_MAIN_WINDOW_H
#define RCSSLOGPLAYER_MAIN_WINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QString>

#include "main_data.h"

class QAction;
class QActionGroup;
class QCloseEvent;
class QDragEnterEvent;
class QDropEvent;
class QLabel;
class QPoint;
class QResizeEvent;

class ConfigDialog;
class DetailDialog;
class FieldCanvas;
class LogPlayer;
class LogPlayerToolBar;
class LogSliderToolBar;
class PlayerTypeDialog;

class MainWindow
    : public QMainWindow {

    Q_OBJECT

private:

    MainData M_main_data;

    QString M_window_style;
    QString M_game_log_path; //!< file path to the last opened game log

    FieldCanvas * M_field_canvas;
    LogPlayer * M_log_player;
    LogPlayerToolBar * M_log_player_tool_bar;
    LogSliderToolBar * M_log_slider_tool_bar;
    ConfigDialog * M_config_dialog;

    QLabel * M_position_label;

    // file actions
    QAction * M_open_act;
    QAction * M_exit_act;

    // view actions
    QAction * M_toggle_menu_bar_act;
    QAction * M_toggle_tool_bar_act;
    QAction * M_toggle_status_bar_act;
    QAction * M_toggle_field_canvas_act;
    QAction * M_full_screen_act;
    QActionGroup * M_style_act_group;
    QAction * M_show_config_dialog_act;

    // help actions
    QAction * M_about_act;
    QAction * M_shortcut_keys_act;

    // not used
    MainWindow( const MainWindow & );
    const MainWindow & operator=( const MainWindow & );

public:

    MainWindow();
    ~MainWindow();

    void init();

private:

    void readSettings();
    void writeSettings();

    void createActions();
    void createActionsFile();
    void createActionsView();
    void createActionsHelp();

    void createMenus();
    void createMenuFile();
    void createMenuView();
    void createMenuHelp();

    void createToolBars();
    void createStatusBar();

    void createFieldCanvas();
    void createConfigDialog();

protected:

    // overrided method (virtual in super)
    void closeEvent( QCloseEvent * event );
    void resizeEvent( QResizeEvent * event );
    void wheelEvent( QWheelEvent * event );

    void dragEnterEvent( QDragEnterEvent * event );
    void dropEvent( QDropEvent * event );

private:

    void openRCG( const QString & file_path );
    void openOutputFile( const QString & file_path );

private slots:
    // file menu actions slots
    void openRCG();


    // view menu actions slots
    void toggleMenuBar();
    void toggleToolBar();
    void toggleStatusBar();
    void toggleFieldCanvas();
    void toggleFullScreen();
    void changeStyle( bool checked );
    void showConfigDialog();

    // help menu actions slots
    void about();
    void printShortcutKeys();

    void resizeCanvas( const QSize & size );

public slots:


    void updatePositionLabel( const QPoint & point );

signals:

    void viewUpdated();

};

#endif
