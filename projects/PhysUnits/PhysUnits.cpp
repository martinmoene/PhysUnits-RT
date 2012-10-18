/**
 * \file PhysUnits.cpp
 *
 * \brief   Console program to play with units.
 * \author  Martin Moene
 * \date    16 September 2012
 *
 * Copyright 2012 Universiteit Leiden. All rights reserved.
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

// g++ -Wall -O2 -I../ -I%BOOST_INCLUDE% -o PhysUnits.exe PhysUnits.cpp && PhysUnits "1.23 m" "330 m/s" "9.8 m/s2"
// cl -nologo -W3 -EHsc -D_CRT_SECURE_NO_WARNINGS -I../ -I%BOOST_INCLUDE% PhysUnits.cpp && PhysUnits "1.23 m" "330 m/s" "9.8 m/s2"

#define PHYS_UNITS_MICRO_GLYPH "u"

#include "phys/units/io.hpp"
#include "phys/units/quantity.hpp"

#include <iostream>
#include <cstring>

#ifdef PHYS_UNITS_COMPILER_IS_MSVC
# include <io.h>
#else
# include <stdio.h>
# include <unistd.h>
#endif

char const * const version_text =
    "1.4 (12 October 2012)";

char const * const copyright_text =
    "Copyright 2012, Universiteit Leiden";

char const * const freesoftware_text =
    "This is free software, based on work by Michael S. Kenniston\n"
    "and distributed under the Boost Software License version 1.0.";

inline const std::string to_string( const long x, const int base = 10 )
{
   char buf[65];
   return _ltoa( x, buf, base );
}

/**
 * return compiler name, version.
 */
std::string compiler_name()
{
#if defined( _MSC_VER )
    return "MSVC " + to_string(_MSC_VER / 100 - 6) + "." + to_string(_MSC_VER % 100) ;
#elif defined( __GNUC__ )
    return "GCC " + to_string(__GNUC__) + "." + to_string(__GNUC_MINOR__) + "." + to_string(__GNUC_PATCHLEVEL__) ;
#endif
    return "Unknown";
}

/**
 * print version text, return EXIT_SUCCESS.
 */
int version( std::string const progname )
{
    std::cout <<
        progname << " " << version_text << " " << compiler_name() << "\n" <<
        copyright_text  << "\n" <<
        freesoftware_text <<  std::endl;
    return EXIT_SUCCESS;
}

/**
 * print help text, return EXIT_SUCCESS.
 */
int usage( std::string const progname )
{
    std::cout <<
        "\nUsage: " << progname << " [option...] [--] [-] [\"expression\"...]" <<
        "\n"
        "\nParse the unit expressions given on the commandline or read from standard"
        "\ninput and present each resulting quantity in engineering notation and as"
        "\nunit expressed in the seven SI base units."
        "\n"
        "\nOptions"
        "\n      -h, --help: this help."
        "\n   -d, --dimless: accept dimensionless quantities."
        "\n  -e, --escape=c: define escape character for extended units [!]."
        "\n    -x, --extend: define units when first encountered [no extend]."
        "\n         --debug: report debug info [no debug]."
        "\n       --version: report version of program."
        "\n              --: end option section."
        "\n               -: read from standard input."
        "\n"
        "\nOption --escape implies option --extend."
        "\n"
        "\nExamples"
        "\n  " << progname << " \"42 km\" \"1 dm3\" \"2 (3.14 mm)2\""
        "\n  " << progname << " \"330 m/s\" \"9.8 m/s2\" \"9.8 m.s-2\" \"9.8 m s-2\""
        "\n  " << progname << " \"3 kHz\" \"3 1/s\" \"3 kV.A\" \"2.2 kOhm\""
        "\n  " << progname << " --extend \"3 Foo\" \"4 !foo\" \"ffoo\" \"f!foo\" \"J2/ffoo\""
        "\n"
        "\nSyntax (EBNF)"
        "\n     expression = [magnitude] factor { (\" \"|\".\"|\"/\") factor } ."
        "\n"
        "\n         factor = prefixed-unit [power]"
        "\n                | \"(\" expression \")\" ."
        "\n"
        "\n  prefixed-unit = [prefix] unit"
        "\n"
        "\n      magnitude = floating-point-number"
        "\n"
        "\n          power = signed-integral-number"
        "\n"
        "\n         prefix = \"y\"..\"Y\""
        "\n"
        "\n           unit = [\"!\"] (\"m\"|\"kg\"|\"s\"|\"A\"|\"K\"|\"mol\"|\"cd\"...)"
        "\n                |  \"1\""
        "\n"
        "\nNote 1: \"!\" is the default escape character for newly defined units."
        "\nNote 2: \"1\" is used for reciprocal units; it must be followed by \"/\"."
        "\n"
        "\nFor more information on SI units, see:"
        "\n  Ambler Thompson and Barry N. Taylor."
        "\n  Guide for the Use of the International System of Units (SI)."
        "\n  NIST Special Publication 811 2008 Edition."
        "\n  http://physics.nist.gov/cuu/pdf/sp811.pdf"

    << std::endl;

    return EXIT_SUCCESS;
}

/**
 * print error messag and return EXIT_FAILURE.
 */
int error( std::string msg )
{
    std::cerr << "Error: " << msg << std::endl;
    return EXIT_FAILURE;
}

/**
 * check for and return single character from option argument.
 */
int expect_character( char const * const option_str, char const * const value_str )
{
    if ( strlen( value_str ) != 1 )
    {
        exit( error( std::string() +
            "expecting single character for option '" + option_str + "', got '" + value_str + "'\n"
            "Try option --help for more information." ) );
    }
    return value_str[0];
}

/**
 * report text and quantity created from that.
 */
void report( std::string const argument, phys::units::quantity const q )
{
    using namespace phys::units;
    using phys::units::io::eng::operator<<;

    std::cout << "'" << argument  << "': " << q <<
        " [" << to_unit_symbol( q, base_symbols() ) << "]" << std::endl;
}

/**
 * true if stream represents a console.
 * \sa http://stackoverflow.com/questions/5156675/how-to-use-isatty-on-cout-or-can-i-assume-that-cout-file-descriptor-1
 */
bool isConsole( std::istream & is )
{
    return 0 != _isatty( _fileno( stdin ) );
}

/**
 * read a line of text.
 * VC6 doesn't handle end of line correctly with std::cin, hence a separate version.
 */
std::string readline()
{
#ifdef PHYS_UNITS_COMPILER_IS_MSVC6
    std::string text;

    do
    {
        if ( isConsole( std::cin ) )
        {
            std::cout << ">";
        }

        char buf[200];
        char * const p = fgets( buf, sizeof buf - 1, stdin );

        if ( NULL == p || feof( stdin ) )
        {
            return "exit";
        }

        text = p;
        text.erase( text.size() - 1 );
    }
    while ( text.size() <= 0 );

    return text;
#else
    std::cin.clear();
    std::string text;

    while( text.size() <= 0 )
    {
        if ( isConsole( std::cin ) )
        {
            std::cout << ">";
        }

        std::getline( std::cin, text );

        if ( std::cin.eof() )
        {
            return "exit";
        }
    }
    return text;
#endif
}

/**
 * interactive mode.
 */
void interactive( std::string const progname, phys::units::quantity_parser & parser )
{
    if ( isConsole( std::cin ) )
    {
        std::cout <<
            "\n" << progname << " " << version_text << " " << compiler_name() <<
            "\n"
            "\nCommands: help, exit (or Ctrl+Z)\n" << std::endl;
    }

    while ( true )
    {
        try
        {
            std::string expression = readline();

            if ( expression == "help" )
            {
                (void) usage( progname );
            }
            else if ( expression == "exit" )
            {
                return ;
            }
            else
            {
                report( expression, parser.parse( expression ) );
            }
        }
        catch( phys::units::quantity_parser_error const & e)
        {
            std::cout <<
               e.input_text() <<
               "\n" << std::string( e.input_position() - 1, ' ' ) << "^" <<
               "\nError: " << e.what() << std::endl;
        }
    }
}

/**
 * main program.
 */
int main( int argc, char *argv[] )
{
    try
    {
        char const * const progname = "PhysUnits" ; // argv[0];

        bool opt_debug = false;
        bool opt_extend = false;
        bool opt_dimless = false;
        char opt_escape = '!';

        // process options:

        while( *++argv && '-' == *argv[0] )
        {
            // argument such as: -a=1.23, --alpha=1.23, --trace
            char * const argument = argv[0];

            /*
             * separate option from (optional) value:
             *
             * Note value may always be accessed, but can yield an empty string ("")
             * if nothing was specified (e.g. as in --anoption ).
             */
            char *pos = strchr(argument, '=');
            if ( NULL != pos )
            {
                *pos++ = '\0';
            }
            else
            {
                // Point to end of string / empty string;
                // saves us allocating a seperate one.
                pos = (char *) "";
            }

            char const * const option = argument;   // e.g. -a or --alpha
            char const * const value  = pos;        // e.g. 1.23, or ""

            if ( strcmp( "--", option) == 0 )
            {
                ++argv;
                break;
            }
            else if ( strcmp( "-h", option) == 0 || strcmp( "--help", option ) == 0 )
            {
                return usage( progname );
            }
            else if ( strcmp( "-d", option) == 0 || strcmp( "--dimless", option ) == 0
                                                 || strcmp( "--dimensionless", option ) == 0 )
            {
                opt_dimless = true;
            }
            else if ( strcmp( "-e", option) == 0 || strcmp( "--escape", option ) == 0 )
            {
                opt_escape = expect_character( option, value );
                opt_extend = true;
            }
            else if ( strcmp( "-x", option) == 0 || strcmp( "--extend", option ) == 0 )
            {
                opt_extend = true;
            }
            else if ( strcmp( "--debug", option ) == 0 )
            {
                opt_debug = true;
            }
            else if ( strcmp( "--version", option ) == 0 )
            {
                return version( progname );
            }
            else
            {
                return error( std::string() +
                    "invalid option '" + option + "'.\n"
                    "Try option --help for more information." );
            }
        }

        // no arguments, show help:

        if ( 0 == *argv )
        {
            return usage( progname );
        }

        // process arguments:

        while ( *argv )
        {
            using namespace phys::units;

            std::string const argument( *argv++ );

            quantity_parser parser;

            parser.
                debug ( opt_debug  ).
                extend( opt_extend ).
                escape( opt_escape ).
                dimensionless( opt_dimless );

            if ( "-" == argument )
            {
                interactive( progname, parser );
            }
            else
            {
                report( argument, parser.parse( argument ) );
            }
        }
    }
    catch( std::exception const & e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS; // VC6
}

/*
 * end of file
 */
