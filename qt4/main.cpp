// -*-c++-*-

/*!
  \file main.cpp
  \brief main function source file
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <QApplication>
#include <QThread>

#include "main_window.h"
#include "options.h"

int
main( int argc,
      char ** argv )
{
    std::cout << PACKAGE"-"VERSION << "\n\n"
              << std::endl;

    QApplication app( argc, argv );

    if ( ! Options::instance().parseCmdLine( argc, argv ) )
    {
        return 1;
    }


    MainWindow win;
    win.show();
    win.init();

    return app.exec();
}
