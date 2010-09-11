// -*-c++-*-

/*!
  \file parser.cpp
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "parser.h"

#include "handler.h"

#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cstdio>

#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#ifdef HAVE_WINDOWS_H
#include <windows.h>
#endif

#include <boost/lexical_cast.hpp>



typedef std::map< std::string, int * > IntMap;
typedef std::map< std::string, double * > DoubleMap;
typedef std::map< std::string, bool * > BoolMap;
typedef std::map< std::string, std::string * > StringMap;

namespace {

std::string
clean_string( std::string str )
{
    if( str.empty() )
    {
        return str;
    }

    if ( *str.begin() == '\'' )
    {
        if( *str.rbegin() == '\''  )
        {
            str = str.substr( 1, str.length() - 2 );
        }
        else
        {
            return str;
        }

        // replace escape character
        for ( std::string::size_type escape_pos = str.find( "\\'" );
              escape_pos != std::string::npos;
              escape_pos = str.find( "\\'" ) )
        {
            // replace "\'" with "'"
            str.replace( escape_pos, 2, "'" );
        }
    }
    else if ( *str.begin() == '"' )
    {
        if ( *str.rbegin() == '"'  )
        {
            str = str.substr( 1, str.length() - 2 );
        }
        else
        {
            return str;
        }

        // replace escape character
        for( std::string::size_type escape_pos = str.find( "\\\"" );
             escape_pos != std::string::npos;
             escape_pos = str.find( "\\\"" ) )
        {
            // replace "\"" with """
            str.replace( escape_pos, 2, "\"" );
        }
    }

    return str;
}


bool
parse_param_line( const int n_line,
                  const std::string & line,
                  IntMap & int_map,
                  DoubleMap & double_map,
                  BoolMap & bool_map,
                  StringMap & string_map )
{
    int n_read = 0;

    char message_name[32];
    if ( std::sscanf( line.c_str(), " ( %31s %n ", message_name, &n_read ) != 1 )
    {
        std::cerr << ":error: failed to the parse message id."
                  << std::endl;
        return false;
    }

    for ( std::string::size_type pos = line.find_first_of( '(', n_read );
          pos != std::string::npos;
          pos = line.find_first_of( '(', pos ) )
    {
        std::string::size_type end_pos = line.find_first_of( ' ', pos );
        if ( end_pos == std::string::npos )
        {
            std::cerr << n_line << ":error: failed to find parameter name."
                      << std::endl;
            return false;
        }
        pos += 1;

        const std::string name_str( line, pos, end_pos - pos );

        pos = end_pos;

        // search end paren or double quatation
        end_pos = line.find_first_of( ")\"", end_pos ); //"
        if ( end_pos == std::string::npos )
        {
            std::cerr << n_line << ":error: failed to parse parameter value for ["
                      << name_str << "] "
                      << std::endl;
            return false;
        }

        // found quated value
        if ( line[end_pos] == '\"' )
        {
            pos = end_pos;
            end_pos = line.find_first_of( '\"', end_pos + 1 ); //"
            if ( end_pos == std::string::npos )
            {
                std::cerr << n_line << ":error: ailed to parse the quated value for ["
                          << name_str << "] "
                          << std::endl;
                return false;
            }
            end_pos += 1; // skip double quatation
        }
        else
        {
            pos += 1; // skip white space
        }

        std::string value_str( line, pos, end_pos - pos );
        pos = end_pos;


        //
        // check parameter maps
        //
        try
        {
            IntMap::iterator int_it = int_map.find( name_str );
            if ( int_it != int_map.end() )
            {
                *(int_it->second) = boost::lexical_cast< int >( value_str );
                continue;
            }

            DoubleMap::iterator double_it = double_map.find( name_str );
            if ( double_it != double_map.end() )
            {
                *(double_it->second) = boost::lexical_cast< double >( value_str );
                continue;
            }

            BoolMap::iterator bool_it = bool_map.find( name_str );
            if ( bool_it != bool_map.end() )
            {
                *(bool_it->second) = !( value_str == "0"
                                        || value_str == "false"
                                        || value_str == "off" );
                continue;
            }

            StringMap::iterator string_it = string_map.find( name_str );
            if ( string_it != string_map.end() )
            {
                *(string_it->second) = clean_string( value_str );
                continue;
            }


            std::cerr << n_line << ": warning: " << message_name
                      << " unsupported parameter=(" << name_str
                      << ' ' << value_str << ")"
                      << std::endl;
        }
        catch ( boost::bad_lexical_cast & e )
        {
            std::cerr << e.what() << '\n'
                      << " param_name=" << name_str
                      << " value=" << value_str
                      << std::endl;
        }
    }

    return true;
}

}


namespace rcss {
namespace rcg {

Parser::Parser( Handler & handler )
    : M_handler( handler )
    , M_line_count( 0 )
    , M_time( 0 )
{

}


bool
Parser::parse( std::istream & is )
{
    // check stream status
    if ( ! is.good() )
    {
        return strmErr( is );
    }

    // parse data
    return parseLine( is );
}

bool
Parser::strmErr( std::istream & is )
{
    if ( is.eof() )
    {
        M_handler.handleEOF();
        return false;
    }

    return false;
}


bool
Parser::parseLine( std::istream & is )
{
    std::string line;

    if ( std::getline( is, line ) )
    {
        ++M_line_count;
        if ( line.empty() )
        {
            return true;
        }

        parseLine( M_line_count, line );
        return true;
    }

    if ( ! is.eof() )
    {
        std::cerr << M_line_count << ": error: "
                  << "Failed to get line."
                  << std::endl;
    }

    return true;
}


bool
Parser::parseLine( const int n_line,
                   const std::string & line )
{
    if ( line.compare( 0, 6, "(draw " ) == 0 )
    {
        parseDrawLine( n_line, line );
    }

    return true;
}

bool
Parser::parseDrawLine( const int n_line,
                       const std::string & line )
{
    // ( draw <time> (clear))
    // ( draw <time> (point <x> <y> "<color>"))
    // ( draw <time> (circle <x> <y> <radius> "<color>"))
    // ( draw <time> (line <sx> <sy> <ex> <ey> "<color>"))

    const char * buf = line.c_str();

    int n_read = 0;

    // parse time

    int time = 0;
    if ( std::sscanf( buf, " ( draw %d %n ",
                      &time, &n_read ) != 1 )
    {
        std::cerr << n_line << ": error: "
                  << "Illegal time info \"" << line << "\""
                  << std::endl;
        return false;
    }
    buf += n_read;

    M_time = time;

    // parse object

    if ( ! std::strncmp( buf, "(point ", 7 ) )
    {
        float x, y;
        char col[64];
        if ( std::sscanf( buf,
                          " (point %f %f \"%63[^\"]\" %n ",
                          &x, &y, col, &n_read ) != 3 )
        {
            std::cerr << n_line << ": error: "
                      << "Illegal draw point info \"" << line << "\""
                      << std::endl;
            return false;
        }

        buf += n_read;
        char *p = const_cast<char*>(std::strstr(buf, ")"));
		*p = '\0';

        M_handler.handleDrawPointInfo( M_time, PointInfoT( x, y, col, buf) );
    }
    else if ( ! std::strncmp( buf, "(circle ", 8 ) )
    {
        float x, y, r;
        char col[64];
        if ( std::sscanf( buf,
                          " (circle %f %f %f \"%63[^\"]\" ) ",
                          &x, &y, &r, col ) != 4 )
        {
            std::cerr << n_line << ": error: "
                      << "Illegal draw circle info \"" << line << "\""
                      << std::endl;
            return false;
        }

        M_handler.handleDrawCircleInfo( M_time, CircleInfoT( x, y, r, col ) );
    }
    else if ( ! std::strncmp( buf, "(line ", 6 ) )
    {
        float x1, y1, x2, y2;
        char col[64];

        if ( std::sscanf( buf,
                          " (line %f %f %f %f \"%63[^\"]\" ) ",
                          &x1, &y1, &x2, &y2, col ) != 5 )
        {
            std::cerr << n_line << ": error: "
                      << "Illegal draw line info \"" << line << "\""
                      << std::endl;
            return false;
        }

        M_handler.handleDrawLineInfo( M_time, LineInfoT( x1, y1, x2, y2, col ) );
    }
    else if ( ! std::strncmp( buf, "(clear)", 7 ) )
    {
        M_handler.handleDrawClear( M_time );
    }
    else
    {
        std::cerr << n_line << ": error: "
                  << "Illegal draw info \"" << line << "\""
                  << std::endl;
        return false;
    }

    return true;
}

}
}
