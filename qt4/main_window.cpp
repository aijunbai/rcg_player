// -*-c++-*-

/*!
  \file main_window.cpp
  \brief main application window class Source File.
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

#include "main_window.h"

#include "config_dialog.h"
#include "field_canvas.h"
#include "log_player.h"
#include "log_player_tool_bar.h"
#include "log_slider_tool_bar.h"
#include "options.h"

#include <string>
#include <iostream>
#include <cstring>

#include "icons/rcss.xpm"

#include "icons/open.xpm"

#ifndef PACKAGE_NAME
#define PACKAGE_NAME "rcg"
#endif

#define USE_MONITOR_CLIENT

/*-------------------------------------------------------------------*/
/*!

 */
MainWindow::MainWindow()
    : M_window_style( "plastique" )
    , M_game_log_path()
    , M_log_player( new LogPlayer( M_main_data, this ) )
    , M_config_dialog( static_cast< ConfigDialog * >( 0 ) )
{
    readSettings();

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    // central widget
    createFieldCanvas();
    // control dialogs
    createConfigDialog();

    connect( M_field_canvas, SIGNAL( playerSelected( int ) ),
             M_config_dialog, SLOT( selectPlayer( int ) ) );
    connect( M_field_canvas, SIGNAL( focusChanged( const QPoint & ) ),
             M_config_dialog, SLOT( setFocusPoint( const QPoint & ) ) );

    connect( M_log_player, SIGNAL( updated() ),
             this, SIGNAL( viewUpdated() ) );
    connect( M_log_player, SIGNAL( updated() ),
             this, SLOT( outputCurrentData() ) );

    this->setWindowIcon( QIcon( QPixmap( rcss_xpm ) ) );
    this->setWindowTitle( tr( PACKAGE_NAME ) );

    this->setMinimumSize( 280, 220 );
    this->resize( Options::instance().windowWidth() > 0
                  ? Options::instance().windowWidth()
                  : 640,
                  Options::instance().windowHeight() > 0
                  ? Options::instance().windowHeight()
                  : 480 );
    this->move( Options::instance().windowX() >= 0
                ? Options::instance().windowX()
                : this->x(),
                Options::instance().windowY() >= 0
                ? Options::instance().windowY()
                : this->y() );

    // this->setWindowOpacity( 0.5 ); // window transparency

    this->setAcceptDrops( true );

    if ( Options::instance().hideToolBar() )
    {
        M_log_player_tool_bar->hide();
        M_log_slider_tool_bar->hide();
    }

    if ( Options::instance().hideStatusBar() )
    {
        this->statusBar()->hide();
    }

    if ( Options::instance().hideMenuBar() )
    {
        this->menuBar()->hide();
    }
}

/*-------------------------------------------------------------------*/
/*!

 */
MainWindow::~MainWindow()
{
    writeSettings();
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::init()
{
    if ( Options::instance().minimumMode() )
    {
        Options::instance().toggleMinimumMode();
        toggleFieldCanvas();
    }

    if ( ! Options::instance().gameLogFile().empty() )
    {
        openRCG( QString::fromStdString( Options::instance().gameLogFile() ) );
    }

    if ( Options::instance().minimumMode() )
    {
        //
    }
    else if ( Options::instance().fullScreen() )
    {
        this->showFullScreen();
    }
    else if ( Options::instance().maximize() )
    {
        this->showMaximized();
    }
    else if ( Options::instance().canvasWidth() > 0
              && Options::instance().canvasHeight() > 0 )
    {
        resizeCanvas( QSize( Options::instance().canvasWidth(),
                             Options::instance().canvasHeight() ) );
    }

}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::readSettings()
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

    M_window_style = settings.value( "window_style", "plastique" ).toString();
    M_game_log_path = settings.value( "game_log_path", "" ).toString();

    settings.endGroup();
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::writeSettings()
{
#ifndef Q_WS_WIN
    QSettings settings( QDir::homePath() + "/.rcg",
                        QSettings::IniFormat );
#else
    QSettings settings( QDir::currentPath() + "/rcg.ini",
                        QSettings::IniFormat );
#endif

    settings.beginGroup( "Global" );

    settings.setValue( "window_style", M_window_style );
    settings.setValue( "game_log_path", M_game_log_path );

    if ( ! Options::instance().minimumMode() )
    {
        settings.setValue( "window_width", this->width() );
        settings.setValue( "window_height", this->height() );
        settings.setValue( "window_x", this->pos().x() );
        settings.setValue( "window_y", this->pos().y() );
        settings.setValue( "maximize", this->isMaximized() );
        settings.setValue( "full_screen", this->isFullScreen() );
        settings.setValue( "hide_menu_bar", this->menuBar()->isHidden() );
        settings.setValue( "hide_tool_bar", ( M_log_player_tool_bar->isHidden()
                                              && M_log_slider_tool_bar->isHidden() ) );
        settings.setValue( "hide_status_bar", this->statusBar()->isHidden() );
    }

    settings.endGroup();
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::createActions()
{
    createActionsFile();
    createActionsView();
    createActionsHelp();

}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::createActionsFile()
{
    M_open_act = new QAction( QIcon( QPixmap( open_xpm ) ),
                              tr( "&Open rcg file..." ), this );
#ifdef Q_WS_MAC
    M_open_act->setShortcut( Qt::META + Qt::Key_O );
#else
    M_open_act->setShortcut( Qt::CTRL + Qt::Key_O );
#endif
    M_open_act->setStatusTip( tr( "Open RoboCup Game Log file." ) );
    connect( M_open_act, SIGNAL( triggered() ),
             this, SLOT( openRCG() ) );
    this->addAction( M_open_act );
    //
    //
    //
    M_exit_act = new QAction( tr( "&Quit" ), this );
#ifdef Q_WS_MAC
    M_exit_act->setShortcut( Qt::META + Qt::Key_Q );
#else
    M_exit_act->setShortcut( Qt::CTRL + Qt::Key_Q );
#endif
    M_exit_act->setStatusTip( tr( "Exit the application." ) );
    connect( M_exit_act, SIGNAL( triggered() ),
             this, SLOT( close() ) );
    this->addAction( M_exit_act );
}

/*-------------------------------------------------------------------*/
/*!

 */
/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::createActionsView()
{
    M_toggle_menu_bar_act = new QAction( tr( "&Menu Bar" ), this );
#ifdef Q_WS_MAC
    M_toggle_menu_bar_act->setShortcut( Qt::META + Qt::Key_M );
#else
    M_toggle_menu_bar_act->setShortcut( Qt::CTRL + Qt::Key_M );
#endif
    M_toggle_menu_bar_act->setStatusTip( tr( "Show/Hide menu bar." ) );
    connect( M_toggle_menu_bar_act, SIGNAL( triggered() ),
             this, SLOT( toggleMenuBar() ) );
    this->addAction( M_toggle_menu_bar_act );
    //
    M_toggle_tool_bar_act = new QAction( tr( "&Tool Bar" ), this );
    M_toggle_tool_bar_act->setStatusTip( tr( "Show/Hide tool bar." ) );
    connect( M_toggle_tool_bar_act, SIGNAL( triggered() ),
             this, SLOT( toggleToolBar() ) );
    this->addAction( M_toggle_tool_bar_act );
    //
    M_toggle_status_bar_act = new QAction( tr( "&Status Bar" ), this );
    M_toggle_status_bar_act->setStatusTip( tr( "Show/Hide status bar." ) );
    connect( M_toggle_status_bar_act, SIGNAL( triggered() ),
             this, SLOT( toggleStatusBar() ) );
    this->addAction( M_toggle_status_bar_act );
    //
    M_toggle_field_canvas_act = new QAction( tr( "Minimum" ), this );
    M_toggle_field_canvas_act->setStatusTip( tr( "Show/Hide field." ) );
    connect( M_toggle_field_canvas_act, SIGNAL( triggered() ),
             this, SLOT( toggleFieldCanvas() ) );
    this->addAction( M_toggle_field_canvas_act );
    //
    M_full_screen_act = new QAction( tr( "&Full Screen" ), this );
    M_full_screen_act->setShortcut( tr( "F11" ) );
    //M_full_screen_act->setShortcut( tr( "Alt+Enter" ) );
    //M_full_screen_act->setShortcut( Qt::ALT + Qt::Key_Return );
    //M_full_screen_act->setShortcut( Qt::ALT + Qt::Key_Enter );
    M_full_screen_act->setStatusTip( tr( "Toggle full screen." ) );
    connect( M_full_screen_act, SIGNAL( triggered() ),
             this, SLOT( toggleFullScreen() ) );
    this->addAction( M_full_screen_act );
    //(void) new QShortcut( Qt::ALT + Qt::Key_Enter, this, SLOT( toggleFullScreen() ) );
    (void) new QShortcut( Qt::ALT + Qt::Key_Return,
                          this, SLOT( toggleFullScreen() ) );
    (void) new QShortcut( Qt::ALT + Qt::Key_Enter,
                          this, SLOT( toggleFullScreen() ) );
    //
    //

    // qt style menu group
    M_style_act_group = new QActionGroup( this );
    Q_FOREACH ( QString style_name, QStyleFactory::keys() )
    {
        QAction * subaction = new QAction( M_style_act_group );
        subaction->setText( style_name );
        subaction->setData( style_name );
        subaction->setCheckable( true );
        if ( style_name.toLower()
             == QApplication::style()->objectName().toLower() )
        {
            subaction->setChecked( true );
        }
        connect( subaction, SIGNAL( triggered( bool ) ),
                 this, SLOT( changeStyle( bool ) ) );
    }
    //
    M_show_config_dialog_act = new QAction( tr( "&Config" ), this );
#ifdef Q_WS_MAC
    M_show_config_dialog_act->setShortcut( tr( "Meta+V" ) );
#else
    M_show_config_dialog_act->setShortcut( tr( "Ctrl+V" ) );
#endif
    M_show_config_dialog_act->setStatusTip( tr( "Show config dialog." ) );
    connect( M_show_config_dialog_act, SIGNAL( triggered() ),
             this, SLOT( showConfigDialog() ) );
    this->addAction( M_show_config_dialog_act );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::createActionsHelp()
{
    M_about_act = new QAction( QIcon( QPixmap( rcss_xpm ) ),
                               tr( "&About" ), this );
    M_about_act->setStatusTip( tr( "Show the about dialog." ) );
    connect( M_about_act, SIGNAL( triggered() ), this, SLOT( about() ) );
    this->addAction( M_about_act );

    M_shortcut_keys_act = new QAction( tr( "Shortcut Keys" ), this );
    M_shortcut_keys_act->setStatusTip( tr( "Print available shortcut keys." ) );
    connect( M_shortcut_keys_act, SIGNAL( triggered() ),
             this, SLOT( printShortcutKeys() ) );
    this->addAction( M_shortcut_keys_act );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::createMenus()
{
    createMenuFile();
    createMenuView();
    createMenuHelp();
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::createMenuFile()
{
    QMenu * menu = menuBar()->addMenu( tr( "&File" ) );

    menu->addAction( M_open_act );

    menu->addSeparator();

    menu->addSeparator();
    menu->addAction( M_exit_act );
}

/*-------------------------------------------------------------------*/
/*!

 */

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::createMenuView()
{
    QMenu * menu = menuBar()->addMenu( tr( "&View" ) );

    menu->addAction( M_toggle_field_canvas_act );

    menu->addSeparator();

    menu->addAction( M_toggle_menu_bar_act );
    menu->addAction( M_toggle_tool_bar_act );
    menu->addAction( M_toggle_status_bar_act );

    menu->addSeparator();
    menu->addAction( M_full_screen_act );

    menu->addSeparator();

    menu->addSeparator();
    {
        QMenu * submenu = menu->addMenu( tr( "Qt &Style" ) );
        Q_FOREACH ( QAction * action, M_style_act_group->actions() )
        {
            submenu->addAction( action );
        }
    }
    menu->addAction( M_show_config_dialog_act );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::createMenuHelp()
{
    QMenu * menu = menuBar()->addMenu( tr( "&Help" ) );
    menu->addAction( M_about_act );
    menu->addAction( M_shortcut_keys_act );

    menu->addSeparator();
    menu->addAction( tr( "About Qt" ), qApp, SLOT( aboutQt() ) );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::createToolBars()
{
    M_log_player_tool_bar = new LogPlayerToolBar( M_log_player,
                                                  M_main_data,
                                                  this );
    connect( M_log_player_tool_bar, SIGNAL( recordToggled( bool ) ),
             this, SLOT( toggleRecord( bool ) ) );

    this->addToolBar( Qt::TopToolBarArea, M_log_player_tool_bar );

    //

    M_log_slider_tool_bar = new LogSliderToolBar( M_log_player,
                                                  M_main_data,
                                                  this );

    connect( this,  SIGNAL( viewUpdated() ),
             M_log_slider_tool_bar, SLOT( updateSlider() ) );

    this->addToolBar( Qt::TopToolBarArea, M_log_slider_tool_bar );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::createStatusBar()
{
    this->statusBar()->showMessage( tr( "Ready" ) );

    M_position_label = new QLabel( tr( "(0.0, 0.0)" ) );

    int min_width
        = M_position_label->fontMetrics().width(  tr( "(-60.0, -30.0)" ) )
        + 16;
    M_position_label->setMinimumWidth( min_width );
    M_position_label->setAlignment( Qt::AlignRight );

    this->statusBar()->addPermanentWidget( M_position_label );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::createFieldCanvas()
{
    M_field_canvas = new FieldCanvas( M_main_data );
    this->setCentralWidget( M_field_canvas );

    M_field_canvas->setFocus();

    connect( this, SIGNAL( viewUpdated() ),
             M_field_canvas, SLOT( update() ) );

    connect( M_field_canvas, SIGNAL( mouseMoved( const QPoint & ) ),
             this, SLOT( updatePositionLabel( const QPoint & ) ) );

    // create & set context menus
    {
        QMenu * menu = new QMenu( M_field_canvas );
        menu->addAction( M_open_act );

        M_field_canvas->setNormalMenu( menu );
    }
    {
        QMenu * menu = new QMenu( M_field_canvas );
        menu->addAction( M_open_act );

        M_field_canvas->setSystemMenu( menu );
    }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::createConfigDialog()
{
    if ( M_config_dialog )
    {
        return;
    }

    M_config_dialog = new ConfigDialog( this, M_main_data );

    M_config_dialog->hide();

    connect( M_config_dialog, SIGNAL( configured() ),
             this, SIGNAL( viewUpdated() ) );

    connect( M_config_dialog, SIGNAL( canvasResized( const QSize & ) ),
             this, SLOT( resizeCanvas( const QSize & ) ) );

    // register short cut keys
    {
        // z
        QAction * act = new QAction( tr( "ZoomIn" ), this );
        act->setShortcut( Qt::Key_Z );
        act->setStatusTip( tr( "Zoom in." ) );
        this->addAction( act );
        connect( act, SIGNAL( triggered() ),
                 M_config_dialog, SLOT( zoomIn() ) );
    }
    {
        // x
        QAction * act = new QAction( tr( "ZoomOut" ), this );
        act->setShortcut( Qt::Key_X );
        act->setStatusTip( tr( "Zoom out." ) );
        this->addAction( act );
        connect( act, SIGNAL( triggered() ),
                 M_config_dialog, SLOT( zoomOut() ) );
    }
    {
        // Ctrl + z
        QAction * act = new QAction( tr( "ZoomOut" ), this );
#ifdef Q_WS_MAC
        act->setShortcut( Qt::META + Qt::Key_Z );
#else
        act->setShortcut( Qt::CTRL + Qt::Key_Z );
#endif
        act->setStatusTip( tr( "Zoom out." ) );
        this->addAction( act );
        connect( act, SIGNAL( triggered() ),
                 M_config_dialog, SLOT( zoomOut() ) );
    }
    {
        // i
        QAction * act = new QAction( tr( "Fit Field Size" ), this );
        act->setShortcut( Qt::Key_I );
        act->setStatusTip( tr( "Fit field size to the screen." ) );
        this->addAction( act );
        connect( act, SIGNAL( triggered() ),
                 M_config_dialog, SLOT( unzoom() ) );
    }

}

/*-------------------------------------------------------------------*/
/*!

 */

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::closeEvent( QCloseEvent * event )
{
    event->ignore();

    qApp->quit();
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::resizeEvent( QResizeEvent * event )
{
    event->accept();

    if ( M_config_dialog
         && M_config_dialog->isVisible() )
    {
        M_config_dialog->updateFieldScale();
    }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::wheelEvent( QWheelEvent * event )
{
    if ( event->delta() < 0 )
    {
        M_log_player->stepForward();
    }
    else
    {
        M_log_player->stepBack();
    }

    event->accept();
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::dragEnterEvent( QDragEnterEvent * event )
{
    if ( event->mimeData()->hasFormat( "text/uri-list" ) )
    {
        event->acceptProposedAction();
    }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::dropEvent( QDropEvent * event )
{
    const QMimeData * mimedata = event->mimeData();

    QList< QUrl > urls = mimedata->urls();

    //     std::cerr << "urls size = " << urls.size() << std::endl;

    //     for ( int i = 0; i < urls.size() && i < 32; ++i )
    //     {
    //         std::cerr << "url " << i << ": "
    //                   << urls.at(i).path().toStdString()
    //                   << std::endl;
    //     }

    while ( ! urls.empty()
            && urls.back().isEmpty() )
    {
        urls.pop_back();
    }

    if ( urls.empty() )
    {
        QMessageBox::information( this,
                                  tr( "Information" ),
                                  tr( "Dropped data has no file path." ),
                                  QMessageBox::Ok, QMessageBox::NoButton );
    }
    else if ( urls.size() == 1 )
    {
        openRCG( urls.front().toLocalFile() );
    }
    else if ( urls.size() > 1 )
    {
        QMessageBox::critical( this,
                               tr( "Error" ),
                               tr( "Too many files are dropped." ),
                               QMessageBox::Ok, QMessageBox::NoButton );
    }

    event->acceptProposedAction();
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::openRCG()
{
#ifdef HAVE_LIBZ
    QString filter( tr( "Game Log files (*.rcg *.rcg.gz);;"
                        "All files (*)" ) );
#else
    QString filter( tr( "Game Log files (*.rcg);;"
                        "All files (*)" ) );
#endif
    if ( ! Options::instance().gameLogFile().empty() )
    {
        M_game_log_path = QString::fromStdString( Options::instance().gameLogFile() );
    }

    QString file_path = QFileDialog::getOpenFileName( this,
                                                      tr( "Choose a game log file to open" ),
                                                      M_game_log_path,
                                                      filter );

    if ( file_path.isEmpty() )
    {
        //std::cerr << "MainWindow::opneRCG() empty file path" << std::endl;
        return;
    }

    std::cerr << "open file = [" << file_path.toStdString() << ']' << std::endl;

    openRCG( file_path );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::openRCG( const QString & file_path )
{
    if ( ! QFile::exists( file_path ) )
    {
        std::cerr << "File [" << file_path.toStdString()
                  << "] does not exist."
                  << std::endl;
        return;
    }

    M_log_player->stop();
    M_log_player_tool_bar->checkRecord( false );
    M_log_player_tool_bar->enableRecord( false );

    if ( ! M_main_data.openRCG( file_path, this ) )
    {
        return;
    }

    if ( M_main_data.dispHolder().empty() )
    {
        return;
    }

    // update last opened file path
    QFileInfo file_info( file_path );
    M_game_log_path = file_info.absoluteFilePath();
    Options::instance().setGameLogFile( M_game_log_path.toStdString() );

    if ( M_config_dialog )
    {
        M_config_dialog->unzoom();
    }

    // set window title
    QString name = file_info.fileName();
    if ( name.length() > 128 )
    {
        name.replace( 125, name.length() - 125, tr( "..." ) );
    }
    this->setWindowTitle( name + tr( " - "PACKAGE_NAME ) );
    this->statusBar()->showMessage( name );


    emit viewUpdated();
}

/*-------------------------------------------------------------------*/
/*!

 */

/*-------------------------------------------------------------------*/
/*!

 */

/*-------------------------------------------------------------------*/
/*!

 */

/*-------------------------------------------------------------------*/
/*!

 */
/*-------------------------------------------------------------------*/
/*!

 */
/*-------------------------------------------------------------------*/
/*!

 */
/*-------------------------------------------------------------------*/
/*!

 */
/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::toggleMenuBar()
{
    this->menuBar()->setVisible( ! this->menuBar()->isVisible() );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::toggleToolBar()
{
    M_log_player_tool_bar->setVisible( ! M_log_player_tool_bar->isVisible() );
    M_log_slider_tool_bar->setVisible( ! M_log_slider_tool_bar->isVisible() );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::toggleStatusBar()
{
    this->statusBar()->setVisible( ! this->statusBar()->isVisible() );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::toggleFieldCanvas()
{
    static QSize s_old_canvas_size = M_field_canvas->size();

    Options::instance().toggleMinimumMode();

    const bool visible = ! Options::instance().minimumMode();
    M_position_label->setVisible( visible );
    if ( ! visible
         && M_config_dialog
         && M_config_dialog->isVisible() )
    {
        M_config_dialog->hide();
    }
    M_toggle_tool_bar_act->setEnabled( visible );
    M_toggle_status_bar_act->setEnabled( visible );
    M_full_screen_act->setEnabled( visible );
    M_show_config_dialog_act->setEnabled( visible );

    if ( Options::instance().minimumMode() )
    {
        s_old_canvas_size = M_field_canvas->size();

        QSize new_canvas_size( 280, 120 ); // for 3 lines

        QRect win_rect = this->geometry();

        this->setMinimumWidth( win_rect.width() - s_old_canvas_size.width() + new_canvas_size.width() );
        this->setMinimumHeight( win_rect.height() - s_old_canvas_size.height() + new_canvas_size.height() );

        // relocate toolbars
        this->addToolBar( Qt::TopToolBarArea, M_log_player_tool_bar );
        this->addToolBarBreak( Qt::TopToolBarArea );
        this->addToolBar( Qt::TopToolBarArea, M_log_slider_tool_bar );

        M_log_player_tool_bar->show();
        M_log_slider_tool_bar->show();

        M_log_player_tool_bar->setMovable( false );
        M_log_slider_tool_bar->setMovable( false );

#if QT_VERSION >= 0x040300
        M_log_player_tool_bar->setFloatable( false );
        M_log_slider_tool_bar->setFloatable( false );
#endif

        M_toggle_field_canvas_act->setText( tr( "Show Field" ) );

        resizeCanvas( new_canvas_size );
    }
    else
    {
        this->setMinimumWidth( 280 );
        this->setMinimumHeight( 220 );
        this->setMaximumSize( QWIDGETSIZE_MAX, QWIDGETSIZE_MAX );

#if QT_VERSION >= 0x040300
        this->removeToolBarBreak( M_log_slider_tool_bar );
#else
        this->addToolBar( Qt::TopToolBarArea, M_log_player_tool_bar );
        this->addToolBar( Qt::TopToolBarArea, M_log_slider_tool_bar );
#endif

        M_log_player_tool_bar->setMovable( true );
        M_log_slider_tool_bar->setMovable( true );
#if QT_VERSION >= 0x040300
        M_log_player_tool_bar->setFloatable( true );
        M_log_slider_tool_bar->setFloatable( true );
#endif

        M_toggle_field_canvas_act->setText( tr( "Minimum" ) );

        resizeCanvas( s_old_canvas_size );
    }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::toggleFullScreen()
{
    if ( this->isFullScreen() )
    {
        this->showNormal();
    }
    else
    {
        this->showFullScreen();
    }
}

/*-------------------------------------------------------------------*/
/*!

 */
/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::changeStyle( bool checked )
{
    if ( ! checked )
    {
        return;
    }

    QAction * action = qobject_cast< QAction * >( sender() );
    QStyle * style = QStyleFactory::create( action->data().toString() );
    Q_ASSERT( style );

    QApplication::setStyle( style );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::showConfigDialog()
{
    M_config_dialog->setVisible( ! M_config_dialog->isVisible() );

    if ( M_config_dialog->isVisible() )
    {
        M_config_dialog->setFixedSize( M_config_dialog->size() );
    }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::about()
{
    QString msg( tr( PACKAGE_NAME"-"VERSION"\n\n" ) );
    QMessageBox::about( this,
                        tr( "About "PACKAGE_NAME ),
                        msg );

    // from Qt 4.1 documents
    /*
      about() looks for a suitable icon in four locations:

      1. It prefers parent->icon() if that exists.
      2. If not, it tries the top-level widget containing parent.
      3. If that fails, it tries the active window.
      4. As a last resort it uses the Information icon.

      The about box has a single button labelled "OK".
    */
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::printShortcutKeys()
{
    QDialog dialog( this );
    QVBoxLayout * layout = new QVBoxLayout();

    QTableWidget * table_widget = new QTableWidget( &dialog );
    table_widget->insertColumn( 0 );
    table_widget->insertColumn( 1 );

    QStringList header;
    header.push_back( tr( "key" ) );
    header.push_back( tr( "action" ) );
    table_widget->setHorizontalHeaderLabels( header );

    table_widget->horizontalHeader()->setStretchLastSection( true );
    table_widget->horizontalHeader()->setResizeMode( QHeaderView::ResizeToContents );
    table_widget->verticalHeader()->hide();

    int row = 0;

    Q_FOREACH( QAction * act, this->actions() )
    {
        if ( ! act->shortcut().isEmpty() )
        {
            //std::cout << '[' << (*it)->shortcut().toString().toStdString() << "] "
            //          << QString( (*it)->text() ).remove( QChar( '&' ) ).toStdString()
            //    //<< ", " << (*it)->statusTip().toStdString()
            //          << '\n';
            table_widget->insertRow( row );
            table_widget->setItem ( row, 0, new QTableWidgetItem( act->shortcut().toString() ) );
            table_widget->setItem ( row, 1, new QTableWidgetItem( QString( act->statusTip() ).remove( QChar( '&' ) ) ) );
            ++row;
        }
    }

    table_widget->setSortingEnabled( true );
//     std::cout <<  "table row_count = " << table_widget->rowCount()
//               <<  "table col_count = " << table_widget->columnCount()
//               << std::endl;

    layout->addWidget( table_widget );
    dialog.setLayout( layout );
    if ( row > 0 )
    {
        dialog.exec();
    }
}

/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::resizeCanvas( const QSize & size )
{
    if ( centralWidget() )
    {
        if ( this->isMaximized()
             || this->isFullScreen() )
        {
            this->showNormal();
        }

        QRect rect = this->geometry();

        int width_diff = rect.width() - centralWidget()->width();
        int height_diff = rect.height() - centralWidget()->height();

        if ( width_diff + size.width() < this->minimumWidth() )
        {
            std::cerr << "Too small canvas width "
                      << size.width() << " "
                      << " minimum=" << this->minimumWidth()
                      << std::endl;
            return;
        }

        if ( height_diff + size.height() < this->minimumHeight() )
        {
            std::cerr << "Too small canvas height "
                      << size.height() << " "
                      << " minimum=" << this->minimumHeight()
                      << std::endl;
            return;
        }

        rect.setWidth( size.width() + width_diff );
        rect.setHeight( size.height() + height_diff );

        this->setGeometry( rect );
    }
}

/*-------------------------------------------------------------------*/
/*!

 */
/*-------------------------------------------------------------------*/
/*!

 */
void
MainWindow::updatePositionLabel( const QPoint & point )
{
    if ( M_position_label
         && M_field_canvas
         && statusBar()
         && statusBar()->isVisible() )
    {
        double x = Options::instance().fieldX( point.x() );
        double y = Options::instance().fieldY( point.y() );

        char buf[32];
        snprintf( buf, 32,
                  "(%.2f, %.2f)",
                  x, y );

        M_position_label->setText( QString::fromAscii( buf ) );
    }
}
