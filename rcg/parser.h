// -*-c++-*-

/*!
  \file rcgparser.h
  \brief Class for parsing rcg files
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

#ifndef RCSSLOGPLAYER_RCG_PARSER_H
#define RCSSLOGPLAYER_RCG_PARSER_H

#include <rcg/types.h>

#include <iosfwd>
#include <string>

namespace rcss {
namespace rcg {

class Handler;

/*!
  class Parser
  \brief rcg parser
 */
class Parser {
private:

    //! reference to the data handler instance
    Handler & M_handler;

    int M_line_count; //!< total number of parsed line. This variable is used only for v4+ log.
    int M_time; //!< current time

    // not used
    Parser();
    Parser( const Parser & );
    Parser & operator=( const Parser & );

public:
    /*!
      \brief construct parser object with data handler class
      \param handler reference to the handler class instance
     */
    explicit
    Parser( Handler & handler );

    /*!
      \brief destructor
     */
    ~Parser()
      { }

    /*!
      \brief analyze rcg data from input stream
      \param is reference to the imput stream
      \return true if successfuly parsed.
     */
    bool parse( std::istream & is );

private:

    // version 4
    //

    bool parseLine( std::istream & is );
public:
    bool parseLine( const int n_line,
                    const std::string & line );

private:
    bool parseDrawLine( const int n_line,
                        const std::string & line );

    bool parseScaleLine( const int n_line,
                        const std::string & line );

    bool parseFocusLine( const int n_line,
                        const std::string & line );
    //
    // common
    //

    bool strmErr( std::istream & is );

};

}
}

#endif
