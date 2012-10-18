/**
 * \file io_output.hpp
 *
 * \brief   IO for run-time quantity library.
 * \author  Michael S. Kenniston, expanded and adapted for run-time use by Martin Moene
 * \date    July 2001, 20 february 2012
 * \since   1.0
 *
 * This code is provided as-is, with no warrantee of correctness.
 * Copyright 2012 Universiteit Leiden. All rights reserved.
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

/*
 * Based on quantity.hpp, rev 0.4 as of 2001-07-16 by Michael S. Kenniston.
 *
 * Copyright (c) 2001 by Michael S. Kenniston.  For the most
 * recent version check www.xnet.com/~msk/quantity.  Permission is granted
 * to use this code without restriction so long as this copyright
 * notice appears in all source files.
 *
 * This code is provided as-is, with no warrantee of correctness.
 *
 * Unless otherwise specified, the definitions of all units in this
 * file are from NIST Special Publication 811, found online at
 * http://physics.nist.gov/Document/sp811.pdf, or from other NIST
 * web pages.
 */

#ifndef PHYS_UNITS_IO_OUTPUT_HPP_INCLUDED
#define PHYS_UNITS_IO_OUTPUT_HPP_INCLUDED

#include "phys/units/quantity.hpp"

#include <iosfwd>
#include <iterator>
#include <map>
#include <string>
#include <sstream>
#include <string>
#include <assert.h>

namespace rt { namespace phys { namespace units {

/**
 * prefix error, for example when prefix is unrecognized.
 */
struct prefix_error : public quantity_error
{
    prefix_error( std::string const text )
    : quantity_error( text ) {}
};

/**
 * unit error, for example when extension table is full.
 */
struct unit_error : public quantity_error
{
    unit_error( std::string const text )
    : quantity_error( text ) {}
};

/**
 * safe bool (base) type: yes, or no.
 */
struct yesno
{
    typedef void ( yesno::*bool_type )() const;

    explicit yesno( bool const v = false ) : value(v) {};

    operator bool_type() const { return value ? &yesno::yes : 0; }

private:
    bool const value;

    void yes() const {}
};

struct yes: yesno { yes() : yesno(true ){} };    ///< yes, true
struct no : yesno {  no() : yesno(false){} };    ///< no, false

/// do extend
struct extend : yesno { extend( bool const v=true ) : yesno(v){} };
/// do \e not extend
struct no_extend : extend { no_extend() : extend(false){} };

/// accept dimensionless quantities.
struct dimensionless : yesno { dimensionless( bool const v=true ) : yesno(v){} };
/// do not accept dimensionless quantities.
struct non_dimensionless : dimensionless { non_dimensionless() : dimensionless(false){} };

/// use name for unit, if available.
struct name_symbol : yesno { name_symbol( bool const v=true ) : yesno(v){} };
/// express unit in base dimensions.
struct base_symbols : name_symbol { base_symbols() : name_symbol(false){} };

inline Rep
prefix( std::string const prefix );

inline quantity
unit( std::string const text, extend extunits = no_extend() );

namespace detail {

/// prefix factor delivering function type.
typedef Rep (*prefix_function_t)();

/**
 * return factor for given prefix.
 */
inline prefix_function_t
prefix_function( std::string const prefix )
{
    struct entry
    {
        char const * name; prefix_function_t func;
    }
    table[] =
    {
        { "m", milli },
        { "k", kilo  },
        { "u", micro },
        { "M", mega  },
        { "n", nano  },
        { "G", giga  },
        { "p", pico },
        { "T", tera  },
        { "f", femto },
        { "P", peta  },
        { "a", atto  },
        { "E", exa   },
        { "z", zepto },
        { "Z", zetta },
        { "y", yocto },
        { "Y", yotta },
        { "h", hecto },
        { "da",deka  },
        { "d", deci  },
        { "c", centi },
        {  0 , 0     },
    };

    entry * p = table;
    for ( ; p->name; ++p )
    {
        if ( prefix == p->name )
        {
            return p->func;
        }
    }
    return 0;
}

typedef quantity (*unit_function_t)();                  ///< unit quantity delivering function type
typedef std::map<dimensions, std::string> unitnamemap;  ///< unit name map type
typedef std::map<std::string, unit_function_t> unitmap; ///< unit delivering function map type

/**
 * create map with predefined unit names
 */
inline unitnamemap
predefined_unit_names()
{
    typedef std::pair<dimensions, char const *> entry;

    entry table[] =
    {
        // SI base units
        entry( length_d, "m" ),
        entry( mass_d, "kg"),
        entry( time_interval_d, "s" ),
        entry( electric_current_d, "A" ),
        entry( thermodynamic_temperature_d, "K" ),
        entry( amount_of_substance_d, "mol"),
        entry( luminous_intensity_d, "cd"),

        // SI coherent derived units with special names and symbols
        entry( frequency_d, "Hz"),
        entry( force_d, "N" ),
        entry( pressure_d, "Pa"),
        entry( energy_d, "J" ),
        entry( power_d, "W" ),
        entry( electric_charge_d, "C" ),
        entry( electric_potential_d, "V" ),
        entry( capacitance_d, "F" ),
        entry( electric_resistance_d, "Ohm" ),
        entry( electric_conductance_d, "S" ),
        entry( magnetic_flux_d, "Wb" ),
        entry( magnetic_flux_density_d, "T" ),
        entry( inductance_d, "H" ),
        //    entry( thermodynamic_temperature_d, "'C" ), // same as K
        entry( luminous_flux_d, "lm" ),
        entry( illuminance_d, "lx" ),
        entry( activity_of_a_nuclide_d, "Bq" ),   // same as Hz
        //    entry( absorbed_dose_d, "Gy" ),           // same as Sv
        entry( dose_equivalent_d, "Sv" ),
        //    entry( "kat",(unit_function_t) katal ),

        // compound dimensions:
        entry( quotient( length_d, time_interval_d), "m/s" ),
        entry( quotient( electric_potential_d, time_interval_d), "V/s" ),

        // extension dimensions:
        entry( extra_x0_d, "x0" ),
        entry( extra_x1_d, "x1" ),
        entry( extra_x2_d, "x2" ),
        entry( extra_x3_d, "x3" ),
        entry( extra_x4_d, "x4" ),
        entry( extra_x5_d, "x5" ),
        entry( extra_x6_d, "x6" ),
        entry( extra_x7_d, "x7" ),
        entry( extra_x8_d, "x8" ),
        entry( extra_x9_d, "x9" ),
    };

    unitnamemap m;

    std::copy(
        table, table + PHYS_UNITS_DIMENSION_OF(table),
        std::inserter( m, m.begin() )
    );

    return m;
}

/**
 * create map with predefined unit delivering functions.
 */
inline unitmap
predefined_units()
{
    typedef std::pair<char const *, unit_function_t> entry;

    entry table[] =
    {
        // SI base units
        entry( "m" , (unit_function_t) meter ),
        entry( "kg", (unit_function_t) kilogram ),
        entry( "s" , (unit_function_t) second ),
        entry( "A" , (unit_function_t) ampere ),
        entry( "K" , (unit_function_t) kelvin ),
        entry( "mol",(unit_function_t) mole ),
        entry( "cd", (unit_function_t) candela ),

        // SI coherent derived units with special names and symbols
        entry( "g" , (unit_function_t) gram ),
        entry( "Hz", (unit_function_t) hertz ),
        entry( "N" , (unit_function_t) newton ),
#ifdef PHYS_UNITS_NO_PASCAL_IDENTIFIER
        entry( "Pa", (unit_function_t) pascal_ ),
#else
        entry( "Pa", (unit_function_t) pascal ),
#endif
        entry( "J" , (unit_function_t) joule ),
        entry( "W" , (unit_function_t) watt ),
        entry( "C" , (unit_function_t) coulomb ),
        entry( "J" , (unit_function_t) joule ),
        entry( "V" , (unit_function_t) volt ),
        entry( "F" , (unit_function_t) farad ),
        entry( "Ohm",(unit_function_t) ohm ),
        entry( "S" , (unit_function_t) siemens ),
        entry( "Wb", (unit_function_t) weber ),
        entry( "T" , (unit_function_t) tesla ),
        entry( "H" , (unit_function_t) henry ),
        entry( "'C", (unit_function_t) degree_celsius ),
        entry( "lm", (unit_function_t) lumen ),
        entry( "lx", (unit_function_t) lux ),
        entry( "Bq", (unit_function_t) becquerel ),
        entry( "Gy", (unit_function_t) gray ),
        entry( "Sv", (unit_function_t) sievert ),
        //    entry( "kat",(unit_function_t) katal ),

        // SI accepted units
        entry( "d"  , (unit_function_t) day ),
        entry( "min", (unit_function_t) minute ),
        entry( "h"  , (unit_function_t) hour ),
        entry( "l"  , (unit_function_t) liter ),
    };

    unitmap m;

    std::copy(
        table, table + PHYS_UNITS_DIMENSION_OF(table),
        std::inserter( m, m.begin() )
    );

    return m;
}

/**
 * the map with predefined unit names
 */
inline unitnamemap &
get_nmap()
{
    static unitnamemap m = predefined_unit_names();
    return m;
}

/**
 * the map with predefined unit delivering functions.
 */
inline unitmap &
get_umap()
{
    static unitmap m = predefined_units();
    return m;
}

/**
 * the map with extension unit delivering functions.
 */
inline unitmap &
get_xmap()
{
    static unitmap m;
    return m;
}

/**
 * define a unit name for given dimension.
 */
inline void
define_unit_name( dimensions const & d, std::string const name )
{
    detail::get_nmap()[d] = name;
}

/**
 * define a unit name for dimension of given quantity.
 */
inline void
define_unit_name( quantity const & q, std::string const name )
{
    define_unit_name( q.dimension(), name );
}

/**
 * append the given unit name to the given map (used for extension units);
 * throws unit_error when table of 10 items is full.
 */
inline quantity
define_unit( unitmap & m, std::string const name )
{
    unit_function_t table[] =
    {
        quantity_x0,
        quantity_x1,
        quantity_x2,
        quantity_x3,
        quantity_x4,
        quantity_x5,
        quantity_x6,
        quantity_x7,
        quantity_x8,
        quantity_x9,
    };

    assert( PHYS_UNITS_QUANTITY_UNIT_EXT_COUNT == PHYS_UNITS_DIMENSION_OF( table ) );

    const int index = m.size();

    if ( index >= PHYS_UNITS_DIMENSION_OF( table ) )
    {
        throw unit_error( "quantity: dimension extension table full, while trying to add '" + name + "'" );
    }

    m[name] = table[index];

    define_unit_name( table[index](), name );

    return unit( name );
}

} // namespace detail {

/** \name Prefix, check and create */
/// @{

/**
 * true if given prefix exists.
 */
inline bool
has_prefix( std::string const prefix )
{
    return 0 != detail::prefix_function( prefix );
}

/**
 * factor for given prefix; throws prefix_error for invalid prefixes.
 */
inline quantity::value_type
prefix( std::string const prefix )
{
    typedef quantity::value_type (*unit_function_t)();

    if ( unit_function_t f = detail::prefix_function( prefix ) )
    {
        return f();
    }

    throw prefix_error( "quantity: unrecognized prefix '" + prefix + "'" );
}

/// @}
/** \name Units, check and create */
/// @{

/**
 * true if unit name exists for given dimension.
 */
inline bool
has_unit_name( dimensions const & d )
{
    return detail::get_nmap().end() != detail::get_nmap().find( d );
}

/**
 * true if unit name exists for dimension of given quantity.
 */
inline bool
has_unit_name( quantity const & q )
{
    return has_unit_name( q.dimension() );
}

/**
 * return quantity of 1 [unit] for given unit, optionally defining
 * unrecognized units as extension first (see \ref extend, no_extend);
 * throws unit_error if unit is not found.
 */
inline quantity
unit( std::string const text, extend extunits /* = no_extend() */ )
{
    detail::unitmap & xmap = detail::get_xmap();
    detail::unitmap & umap = detail::get_umap();

    // predefined:
    {
        const detail::unitmap::iterator pos = umap.find(text);

        if ( pos != umap.end() )
        {
            return (*pos).second();
        }
    }
    // extension:
    {
        const detail::unitmap::iterator pos = xmap.find(text);

        if ( pos != xmap.end() )
        {
            return (*pos).second();
        }
    }

    if ( extunits )
    {
        return detail::define_unit( xmap, text );
    }

    throw unit_error( "quantity: undefined unit '" + text + "'" );
}

/// @}

namespace detail {

/**
 * unit name for given dimension.
 */
inline std::string
unit_name( dimensions const & d )
{
    return detail::get_nmap()[d];
}

/**
 * unit name for dimension of given quantity.
 */
inline std::string
unit_name( quantity const & q )
{
    return unit_name( q.dimension() );
}

/**
 * Provide SI units-and-exponents in as close to NIST-specified format
 * as possible with plain ascii.
 */
struct unit_info
{
    dimensions m_dim;

    unit_info( dimensions d )
    : m_dim( d )
    {
    }

    /**
     * true if base dimension.
     */
    bool single() const
    {
        return m_dim.is_base();
    }

    /**
     * provide unit's name.
     */
    std::string name() const
    {
        return symbol();
    }

    /**
    * provide unit's symbol.
    */
    std::string symbol( name_symbol name_symbol = name_symbol() ) const
    {
        bool first = true;
        std::ostringstream os;

        const int base_cnt = PHYS_UNITS_QUANTITY_UNIT_BASE_COUNT;
        const dimensions base_dim = dimensions( m_dim, 0, base_cnt );

        if ( name_symbol && has_unit_name( base_dim ) )
        {
            emit_dim( os, detail::unit_name( base_dim ), 1, first );
        }
        else
        {
            for ( int i = 0; i < base_cnt; ++i )
            {
                emit_dim( os, detail::unit_name( dimensions(i,1) ), m_dim.d[i], first );
            }
        }

        for ( int i = base_cnt; i < PHYS_UNITS_QUANTITY_UNIT_EXT_COUNT; ++i )
        {
            emit_dim( os, detail::unit_name( dimensions(i,1) ), m_dim.d[i], first );
        }

        return os.str();
    }

    /**
     * emit a single unit.
     */
    void emit_dim( std::ostream & os, std::string const label, int const exp, bool & first ) const
    {
        if( exp == 0 )
            return;

        if ( first )
            first = false;
        else
            os << " ";

        os << label;

        if( exp > 1 )
            os << "+";

        if( exp != 1 )
            os << exp;
    }
};

} // namespace detail {

/** \name Quantity and dimension, conversion to text */
/// @{

/**
 * the unit's name.
 */
inline std::string
to_unit_name( dimensions const & d )
{
    return detail::unit_info( d ).name();
}

/**
 * the quantity's unit name.
 */
inline std::string
to_unit_name( quantity const & q )
{
    return to_unit_name( q.dimension() );
}

/**
 * the unit's symbol, or expressed in 7 SI base units (name_symbol = false).
 */
inline std::string
to_unit_symbol( dimensions const & d, name_symbol use = name_symbol() )
{
    return detail::unit_info( d ).symbol( use );
}

/**
 * the quantity's unit symbol, or expressed in 7 SI base units (name_symbol = false).
 */
inline std::string
to_unit_symbol( quantity const & q, name_symbol use = name_symbol() )
{
    return to_unit_symbol( q.dimension(), use );
}

/**
 * the unit's symbol expressed in 7 SI base units.
 */
inline std::string
to_base_unit_symbols( dimensions const & d )
{
    return detail::unit_info( d ).symbol( base_symbols() );
}

/**
 * the quantity's unit symbol expressed in 7 SI base units.
 */
inline std::string
to_base_unit_symbols( quantity const & q )
{
    return to_base_unit_symbols( q.dimension() );
}

/**
 * return given real value as string.
 */
inline std::string
to_string( long double const value )
{
    std::ostringstream os;
    os << value;
    return os.str();
}

/// @}

namespace io {

/**
 * convert given quantity to string as "{magnitude} ' ' {symbol}".
 */
inline std::string
to_string( quantity const & q, name_symbol use = name_symbol() )
{
    std::ostringstream os;
    os << q.value() << " " << to_unit_symbol( q, use );
    return os.str();
}

/**
 * stream quantity to stream as "{magnitude} ' ' {symbol}".
 */
inline std::ostream &
operator<<( std::ostream & os, quantity const & q )
{
    return os << q.value() << " " << to_unit_symbol( q );
}

} // namespace io

}}} // namespace rt { namespace phys { namespace units {

#endif // PHYS_UNITS_IO_OUTPUT_HPP_INCLUDED

/*
 * end of file
 */
