/**
 * \file io_input.hpp
 *
 * \brief   IO for run-time quantity library.
 * \author  Martin Moene
 * \date    5 October 2012
 * \since   1.0
 *
 * This code is provided as-is, with no warrantee of correctness.
 * Copyright 2012 Universiteit Leiden. All rights reserved.
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

/**
\class rt::phys::units::quantity_parser
\verbatim

Syntax (EBNF)

  nv-expression = [numerical-value] term

     expression = [value] term

           term = factor { (" "|"."|"/") factor } .

         factor = prefixed-unit [power]
                | "(" expression ")" .

  prefixed-unit = [prefix] unit

numerical-value = floating-point-number

          value = floating-point-number

          power = signed-integral-number

         prefix = "y".."Y"

           unit = ["!"] ("m"|"kg"|"s"|"A"|"K"|"mol"|"cd"...)     See note 1
                |  "1"                                           See note 2

Note 1: "!" is the default escape character for newly defined units.
Note 2: "1" as factor is used for reciprocal units; it must be followed by "/"

Examples
  1 m, 1 m2, 1 m/s, 1 m/s2, 1 (4 cm)2, 33 Hz, 33 1/s,
  !foo , ffoo (or f!foo) (extension units)

For more information on SI units, see:
  Ambler Thompson and Barry N. Taylor.
  Guide for the Use of the International System of Units (SI).
  NIST Special Publication 811 2008 Edition.
  http://physics.nist.gov/cuu/pdf/sp811.pdf

\endverbatim
*/

#ifndef PHYS_UNITS_IO_INPUT_HPP_INCLUDED
#define PHYS_UNITS_IO_INPUT_HPP_INCLUDED

#include "phys/units/quantity.hpp"
#include "phys/units/io_output.hpp"

#include <iostream>

namespace rt { namespace phys { namespace units {

/**
 * parsing error.
 */
class quantity_parser_error : public quantity_error
{
public:
    quantity_parser_error( std::string const msg, std::string const text, int const position )
    : quantity_error( msg )
    , text( text )
    , position( position ) {}

    // corect for  g++ error: looser throw specifier:
    ~quantity_parser_error() throw() {}

    std::string input_text() const { return text; }
    int input_position() const { return position; }

    std::string const text;
    int const position;
};

namespace detail {

/// char-string convertion shim.
inline std::string to_string( char x )
{
    return std::string( 1, x );
}

/// string-real convertion shim.
inline double to_real( std::string const text )
{
    return strtod( text.c_str(), 0 );
}

/// long-string convertion shim.
inline std::string to_string( long const x, int const base = 10 )
{
    char buf[65] = "";

    return _ltoa( x, buf, base );
}

/// int-string convertion shim.
inline std::string to_string( int const x, int const base = 10 )
{
    return to_string( static_cast<long>(x), base );
}

/// default strip set for strip(), strip_left(), strip_right().
inline char const* const default_strip_set()
{
    return " \t\n";
}

/// string with characters in set removed from front of input text.
inline std::string strip_left( std::string text, const std::string set = detail::default_strip_set() )
{
    text.erase( 0, text.find_first_not_of( set ) );
    return text;
}

/// string with characters in set removed from rear of input text.
inline std::string strip_right( std::string text, const std::string set = detail::default_strip_set() )
{
    text.erase( text.find_last_not_of( set ) + 1 );
    return text;
}

/// string with characters in set removed from front and rear of input text.
inline std::string strip( std::string const text, const std::string set = detail::default_strip_set() )
{
    return strip_left( strip_right( text, set ), set );
}

} // namespace detail

/**
 * parse "1 m", "1.2km", "330m/s" "9.8m/s2" "3 kV.A" "3.2 kOhm"
 */
class quantity_parser
{
public:
    /**
     * the representation type.
     */
    typedef quantity::value_type value_type;

    /**
     * constructor
     */
    quantity_parser()
    : debug_flag( false )
    , ext_units( false )
    , dimless_quantities( false )
    , end_char( '#' )
    , escape_char( '!' )
    , current_char()
    , current_pos( 0 )
    , num_value( value_type(1) )
    , pfx_factor( value_type(1) )
    {
    }

    /**
     * desstructor
     */
    ~quantity_parser()
    {
        if ( debug_flag )
        {
            std::cout << debug_text() << std::endl;
        }
    }

    /**
     * convert given string to quantity.
     */
    quantity parse( std::string text )
    {
        try
        {
            return parseInput( text );
        }
        catch ( quantity_error const & e )
        {
            throw quantity_parser_error(
                "quantity: parsing unit '" + text + "': " + e.what(),
                    input_text(), input_position() );
        }
    }

    /**
     * the numerical value, the v in v km/h.
     */
    value_type numerical_value() const
    {
        return num_value;
    }

    /**
     * the prefix factor, the k in v km/h.
     */
    value_type prefix_factor() const
    {
        return pfx_factor;
    }

    /**
     * the stripped input text.
     */
    std::string input_text() const
    {
        return text.substr( 0, text.size() - 1 );
    }

    /**
     * the collected debug text.
     */
    std::string debug_text() const
    {
        return oss.str();
    }

    /**
     * the current scanner position in the text.
     */
    int input_position() const
    {
        return current_pos;
    }

    /**
     * set or clear debug flag.
     */
    quantity_parser & debug( bool on )
    {
        debug_flag = on;
        return *this;
    }

    /**
     * set unit escape character; for example to specify extended unit foo, use !foo;
     * '!' is the (default) escape character to prevent interpreting femto oo.
     */
    quantity_parser & escape( char chr )
    {
        escape_char = chr;
        return *this;
    }

    /**
     * enable or disable unit extending.
     */
    quantity_parser & extend( bool on )
    {
        ext_units = on;
        return *this;
    }

    /**
     * enable or disable accepting dimensionless quantities.
     */
    quantity_parser & dimensionless( bool on )
    {
        dimless_quantities = on;
        return *this;
    }

private:
    /*
     * prepare input and debug streams, parse expression and return result.
     */
    quantity parseInput( std::string const text_ )
    {
        oss << "parse(): '" << text_ << "'" << std::endl;

        initialize( text_ );

        advance();

        quantity const q( parseNumValueExpression() );

        if ( ! accept( end_char ) )
        {
            throw quantity_parser_error(
                std::string() + "garbage at position " +
                    detail::to_string( current_pos ) + ": '" + currentStr() + "'",
                        input_text(), input_position() );
        }

        pfx_factor = (q / numerical_value() ).value();

        return q;
    }

    /*
     * nv-expression = [numerical-value] term .
     */
    quantity parseNumValueExpression()
    {
        oss << "parseNumValueExpression(): '" << current() << "'" << std::endl;

        num_value = parseNumericalValue();

        return num_value * parseTerm();
    }

    /*
     * expression = [value] term .
     */
    quantity parseExpression()
    {
        oss << "parseExpression(): '" << current() << "'" << std::endl;

        // Note order: keep as separate statements:

        value_type const value( parseNumericalValue() );

        return value * parseTerm();
    }

    /*
     * [value].
     */
    value_type parseNumericalValue()
    {
        oss << "parseNumericalValue(): char: '" << current() << "'" << std::endl;

        value_type value = 1.0;

        skip_whitespace();

        if ( isReal( current() ) )
        {
            value = scanReal();
        }

        skip_whitespace();

        oss << "parseNumericalValue() text: " << text << ", magnitude: " << value << std::endl;

        return value;
    }

    /*
     * term = factor { (" "|"."|"/") factor } .
     */
    quantity parseTerm()
    {
        quantity lhs( parseFactor() );

        int solidus_count = 0;

        while ( isOperator( current() ) )
        {
            if ( isOperator( ahead() ) )
            {
                throw quantity_parser_error(
                    std::string() + "consecutive operators at position " +
                        detail::to_string( input_position() ) + ": '" + currentStr() + "' and '" + aheadStr() + "'",
                            input_text(), input_position() );
            }

            switch( current() )
            {
                case ' ': case '.':
                    oss << "parseTerm(): '" << current() << "'" << std::endl;
                    solidus_count = 0;
                    advance();
                    lhs *= parseFactor();
                    break;

                case '/':
                    oss << "parseTerm(): '" << current() << "'" << std::endl;
                    if ( ++solidus_count > 1 )
                    {
                        throw quantity_parser_error(
                            std::string() + "repetition of solidus at position " +
                                detail::to_string( current_pos ) + ": use parenthesis to avoid ambiguity",
                                    input_text(), input_position() );
                    }
                    advance();
                    lhs /= parseFactor();
                    break;
            }
        }

        return lhs;
    }

    /*
     * factor = prefixed-unit [power]
     *        | "(" expression ")" .
     */
    quantity parseFactor()
    {
        oss << "parseFactor(): '" << current() << "'" << std::endl;

        while ( accept( '(' ) )
        {
            quantity const q( parseExpression() );

            expect( ')' );

            return parsePower( q );
        }

        // accept dimensionless quantity?

        if ( dimless_quantities && ! isPrefixedUnit( current(), ahead() ) )
        {
            return number();
        }

        // Note order: keep as separate statements:

        value_type const prefix = parsePrefix();

        return parsePower( prefix * parseUnit() );
    }

    /*
     * prefix variations:
     * m - no prefix
     * km - normal prefix
     * kfoo - normal prefix
     * !foo - escape: skip prefix, interpret as unit
     * k!foo - allow redundant escape
     */
    value_type parsePrefix()
    {
        using namespace phys::units;

        oss << "parsePrefix(): current: '" << current() << "'" << std::endl;
        oss << "parsePrefix(): ahead: '" << ahead() << "'" << std::endl;

        std::string pfx = currentStr();

        if ( isEscape( current() ) )
        {
            // !foo
            return 1.0;
        }
        else if ( ! isUnit( ahead() ) )
        {
            // V#
            return 1.0;
        }
        else if ( current() == 'c' && 'd' == ahead() )
        {
            // cd
            return 1.0;
        }
        else if ( current() == 'k' && 'g' == ahead() )
        {
            // kg
            return 1.0;
        }
        else if ( current() == 'm' && 'o' == ahead() )
        {
            // mol?
            return 1.0;
        }
        else if ( current() == 'm' && 'i' == ahead() )
        {
            // min?
            return 1.0;
        }
        else if ( current() == 'P' && 'a' == ahead() )
        {
            // Pa
            return 1.0;
        }
        else if ( current() == 'G' && 'y' == ahead() )
        {
            // Gy
            return 1.0;
        }
        else if ( current() == 'd' && 'a' == ahead() )
        {
            // deka?
            advance();
            pfx += currentStr();
        }
        else if ( ! has_prefix( currentStr() ) )
        {
            // not a prefix
            return 1.0;
        }

        advance();

        return prefix( pfx );
    }

    /*
     * [unit], e.g. "m", "1" if followed by "/", {escape}{unit}.
     */
    quantity parseUnit()
    {
        oss << "parseUnit(): '" << current() << "'" << std::endl;

        /*
         * special case: 1/{unit}
         */
        if ( current() == '1' )
        {
            if ( ahead() != '/' )
            {
                throw quantity_parser_error(
                    std::string() + "expecting 1/u construct at position " +
                        detail::to_string( current_pos ) + ", got: '1" + (end_char==ahead() ? "[nothing]" : aheadStr()) + "'",
                            input_text(), input_position() );
            }

            accept( '1' );
            return number();
        }

        if ( ! isUnit( current(), ahead() ) )
        {
            throw quantity_parser_error(
                std::string() + "expecting unit at position " +
                    detail::to_string( current_pos ) + ", got: '" + (end_char==current() ? "[nothing]" : currentStr()) + "'",
                        input_text(), input_position() );
        }

        return unit( scanUnit(), rt::phys::units::extend( ext_units ) );
    }

    /*
     * quantity [power].
     */
    quantity parsePower( quantity const & q )
    {
        oss << "parsePower(): '" << current() << "'" << std::endl;

        if ( isInteger( current() ) )
        {
            return nth_power( q, static_cast<int>( scanInteger() ) );
        }

        return q;
    }

    bool isEscape( char x ) const
    {
        return x == escape_char;
    }

    bool isEnd( char x ) const
    {
        return x == end_char;
    }

    bool isUnit( char x ) const
    {
        return isEscape(x) || isalpha( x );
    }

    bool isUnit( char x, char y ) const
    {
        return   isalpha ( x )
            || ( isEscape( x ) && isalpha( y ) )
            || (   '\'' == x   &&   'C' == y );
    }

    bool isPrefixedUnit( char x, char y ) const
    {
        // special case for 1/{unit}
        return '1' == x || isUnit( x, y );
    }

    bool isReal( char x ) const
    {
        return isdigit( x ) || std::string::npos != std::string( ".eE+-").find_first_of( x );
    }

    bool isInteger( char x ) const
    {
        return isdigit( x ) || std::string::npos != std::string( "+-").find_first_of( x );
    }

    bool isMultiplyingOperator( char x ) const
    {
        return x == ' ' || x == '.';
    }

    bool isDividingOperator( char x ) const
    {
        return x == '/';
    }

    bool isMultiplicativeOperator( char x ) const
    {
        return isMultiplyingOperator(x) || isDividingOperator(x);
    }

    bool isOperator( char x ) const
    {
        return isMultiplicativeOperator(x);
    }

    void initialize( std::string const & text_ )
    {
        current_pos = 0;
        current_char = ' ';

        text = detail::strip( text_ ) + detail::to_string( end_char );

        iss.clear();
        iss.str( text );
    }

    void skip_whitespace()
    {
        while ( isspace( current() ) )
        {
            advance();
        }
    }

    value_type scanReal()
    {
        oss << "scanReal(): '";

        std::string text;
        while ( isReal( current() ) )
        {
            oss << current();
            text.append( 1, current() );
            advance();
        }
        oss << "'\nscanReal(): text: " << text << std::endl;

        return detail::to_real( text );
    }

    value_type scanInteger()
    {
        oss << "scanInteger(): '";

        std::string text;
        while ( isInteger( current() ) )
        {
            oss << current();
            text.append( 1, current() );
            advance();
        }
        oss << "'" << std::endl;

        return detail::to_real( text );
    }

    std::string scanUnit()
    {
        oss << "scanUnit(): '";

        accept( escape_char );

        // \': special case for degree celsius ('C )

        std::string text;
        while ( '\'' == current() || isalpha( current() ) )
        {
            oss << current();
            text.append( 1, current() );
            advance();
        }
        oss << "'" << std::endl;

        return text;
    }

    bool accept( char chr )
    {
        if ( chr != current() )
        {
            return false;
        }
        advance();
        return true;
    }

    std::string currentStr() const
    {
        return detail::to_string( current() );
    }

    std::string aheadStr()
    {
        return detail::to_string( ahead() );
    }

    char current() const
    {
        return current_char;
    }

    char ahead()
    {
        if ( isEnd( current_char ) )
        {
            return end_char;
        }
        return iss.peek();
    }

    char advance( bool skipws = false )
    {
        if ( isEnd( current_char ) )
        {
            return current_char;
        }

        if ( skipws )
        {
            while ( ' ' == ( current_char = iss.get() ) )
            {
                ++current_pos;
            }
        }
        else
        {
            ++current_pos;
            current_char = iss.get();
        }
        return current();
    }

    void expect( char chr )
    {
        if ( chr != current() )
        {
            throw quantity_parser_error(
                "quantity: expecting '" + std::string(1,static_cast<char>(chr)) + "'",
                    input_text(), input_position() );
        }
        advance();
    }

private:
    bool debug_flag;            //< report debuging info
    bool ext_units;              //< define unrecognized units
    bool dimless_quantities;    //< accept dimensionless quantities
    char end_char;              //< character to mark end-of-input
    char escape_char;           //< unit escape character
    char current_char;          //< current scanner character
    int  current_pos;           //< current scanner character position
    std::string text;           //< input text
    std::istringstream iss;     //< input stream
    std::ostringstream oss;     //< debug output stream
    value_type num_value;       //< numerical value, e.g. the v in v km/h
    value_type pfx_factor;      //< prefix factor, e.g. the k in v km/h
};

/** \name Quantity, create from text */
/// @{

namespace detail {

/**
 * return a pair with quantity and the numerical value for given text;
 * optionally define not-yet-defined units (extunits),
 * optionally accept dimensionless quantities (dimless).
 */
inline std::pair<quantity, quantity::value_type>
make_quantity( std::string text, extend extunits, dimensionless dimless )
{
    /* use !! to prevent warning with VC6:
     * warning C4761: integral size mismatch in argument; conversion supplied
     */
    quantity_parser parser;
    parser.
        extend( !!extunits ).
        dimensionless( !!dimless );

    typedef quantity::value_type numvalue;

    quantity const & q = parser.parse( text );
    numvalue const & v = parser.numerical_value();

    return std::make_pair( q, v );
}

} // namespace detail {

/**
 * return quantity for given text;
 * optionally define not-yet-defined units (extunits),
 * optionally accept dimensionless quantities (dimless).
 */
inline quantity
to_quantity( std::string text, extend extunits, dimensionless dimless )
{
    return detail::make_quantity( text, extunits, dimless ).first;
}

/**
 * return quantity for given text;
 * no unit extension, no dimensionless quantities.
 */
inline quantity
to_quantity( std::string text )
{
    return to_quantity( text, no_extend(), non_dimensionless() );
}

/**
 * return quantity for given text;
 * allow unit extension per extunits, no dimensionless quantities.
 */
inline quantity
to_quantity( std::string text, extend extunits )
{
    return to_quantity( text, extunits, non_dimensionless() );
}

/**
 * return quantity for given text;
 * allow dimensionless quantities per dimless, no unit extension.
 */
inline quantity
to_quantity( std::string text, dimensionless dimless )
{
    return to_quantity( text, no_extend(), dimless );
}

/**
 * return quantity for given text;
 * allow unit extension per dimless, allow dimensionless quantities per extunits.
 */
inline quantity
to_quantity( std::string text, dimensionless dimless, extend extunits )
{
    return to_quantity( text, extunits, dimless );
}

/**
 * return unit (the km/h for 45 km/h) for given text;
 * optionally define not-yet-defined units (extunits),
 * optionally accept dimensionless quantities (dimless).
 */
inline quantity
to_unit( std::string text, extend extunits, dimensionless dimless )
{
    std::pair<quantity, quantity::value_type> qv( detail::make_quantity( text, extunits, dimless ) );

    return quantity( qv.first.dimension(), qv.first.value() / qv.second );
}

/**
 * return unit (the km/h for 45 km/h) for given text;
 * no unit extension, no dimensionless quantities.
 */
inline quantity
to_unit( std::string text )
{
    return to_unit( text, no_extend(), non_dimensionless() );
}

/**
 * return unit (the km/h for 45 km/h) for given text;
 * allow unit extension per extunits, no dimensionless quantities.
 */
inline quantity
to_unit( std::string text, extend extunits )
{
    return to_unit( text, extunits, non_dimensionless() );
}

/**
 * return unit (the km/h for 45 km/h) for given text;
 * allow dimensionless quantities per dimless, no unit extension.
 */
inline quantity
to_unit( std::string text, dimensionless dimless )
{
    return to_unit( text, no_extend(), dimless );
}

/**
 * return numerical value (the 45 for 45 km/h) for given text;
 * allow unit extension per dimless, allow dimensionless quantities per extunits.
 */
inline quantity
to_unit( std::string text, dimensionless dimless, extend extunits )
{
    return to_unit( text, extunits, dimless );
}

/**
 * return numerical value (the 45 for 45 km/h) for given text;
 * optionally define not-yet-defined units (extunits),
 * optionally accept dimensionless quantities (dimless).
 */
inline quantity::value_type
to_numerical_value( std::string text, extend extunits, dimensionless dimless )
{
    return detail::make_quantity( text, extunits, dimless ).second;
}

/**
 * return numerical value (the 45 for 45 km/h) for given text;
 * no unit extension, no dimensionless quantities.
 */
inline quantity::value_type
to_numerical_value( std::string text )
{
    return to_numerical_value( text, no_extend(), non_dimensionless() );
}

/**
 * return numerical value (the 45 for 45 km/h) for given text;
 * allow unit extension per extunits, no dimensionless quantities.
 */
inline quantity::value_type
to_numerical_value( std::string text, extend extunits )
{
    return to_numerical_value( text, extunits, non_dimensionless() );
}

/**
 * return numerical value (the 45 for 45 km/h) for given text;
 * allow dimensionless quantities per dimless, no unit extension.
 */
inline quantity::value_type
to_numerical_value( std::string text, dimensionless dimless )
{
    return to_numerical_value( text, no_extend(), dimless );
}

/**
 * return numerical value (the 45 for 45 km/h) for given text;
 * allow unit extension per dimless, allow dimensionless quantities per extunits.
 */
inline quantity::value_type
to_numerical_value( std::string text, dimensionless dimless, extend extunits )
{
    return to_numerical_value( text, extunits, dimless );
}

/// @}

}}} // namespace rt { namespace phys { namespace units {

#endif // PHYS_UNITS_IO_INPUT_HPP_INCLUDED

/*
 * end of file
 */
