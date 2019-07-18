/**
 * \file quantity.hpp
 *
 * \brief   Run-time dimensional analysis and unit/quantity manipulation and conversion.
 * \author  Michael S. Kenniston, adaptation for runtime by Martin Moene
 * \date    12 July 2012
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

#ifndef PHYS_UNITS_QUANTITY_HPP_INCLUDED
#define PHYS_UNITS_QUANTITY_HPP_INCLUDED

#include <cmath>        // for pow()
#include <algorithm>
#include <functional>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <typeinfo>
#include <vector>

/**
 * number of SI base dimensions (7).
 */
#define PHYS_UNITS_QUANTITY_UNIT_BASE_COUNT 7

/**
 * number of extension dimensions (see note).
 *
 * Note: PHYS_UNITS_QUANTITY_UNIT_EXT_COUNT cannot be changed without
 * also changing:
 * - dimensions extra_x0_d( 7, 1 );... (this file)
 * - PHYS_UNITS_DEFINE_UNIT( x0 )... (this file)
 * - inline quantity define_unit() (io_output.hpp)
 */
#define PHYS_UNITS_QUANTITY_UNIT_EXT_COUNT 10

#if defined( __GNUC__ )
# define PHYS_UNITS_COMPILER_IS_GNUC
#elif defined( __MWERKS__ )
# define PHYS_UNITS_COMPILER_IS_MWERKS
#elif defined( _MSC_VER )
# define PHYS_UNITS_COMPILER_IS_MSVC
# if ( _MSC_VER >= 1200 ) && ( _MSC_VER < 1300 )
#  define PHYS_UNITS_COMPILER_IS_MSVC6
# endif
# if ( _MSC_VER >= 1600 ) && ( _MSC_VER < 1700 )
#  define PHYS_UNITS_COMPILER_IS_MSVC2010
# endif
#endif

#ifdef PHYS_UNITS_COMPILER_IS_MSVC
// for MSVC, 4248 = invalid access to "private" - must be treated as an error
// for MSVC, 4786 = truncated names in debugger - ignore
# pragma warning( error:4248; disable:4786 )
#endif

/**
 * \def TYPENAME_TYPE_K
 * handle differences in compiler support for use of typename as a type qualifier
 * within template function bodies (Wilson, ICPP 16-7 Unsupported Keywords).
 */
#ifndef TYPENAME_TYPE_K
# ifdef PHYS_UNITS_COMPILER_IS_MSVC6
#  define TYPENAME_TYPE_K
# else
#  define TYPENAME_TYPE_K typename
# endif
#endif

#if defined( PHYS_UNITS_COMPILER_IS_MSVC ) || defined( PHYS_UNITS_COMPILER_IS_MWERKS )
# define PHYS_UNITS_NO_PASCAL_IDENTIFIER
#endif

#ifdef PHYS_UNITS_NO_PASCAL_IDENTIFIER
/*
 * Some compilers use "pascal" as a keyword.
 * Note that defining a macro "pascal()" with zero arguments
 * will not interfere with the use of "pascal" as a keyword,
 * since the macro will be expanded only when followed by "()".
 */
# undef pascal
# define pascal() pascal_()
#endif

/**
 * preprocessor concatenate macro.
 */
#define PHYS_UNITS_CONCATENATE(s1, s2)  PHYS_UNITS_CONCATENATE_DIRECT(s1, s2)

/**
 * preprocessor concatenate helper macro.
 */
#define PHYS_UNITS_CONCATENATE_DIRECT(s1, s2)  s1##s2

/**
 * dimension of macro.
 *
 * Note: if not using signed at the computation of prefix_end below,
 * VC2010 -Wall issues a warning about unsigned and addition overflow.
 * Hence the cast to signed int here.
 */
#define PHYS_UNITS_DIMENSION_OF(x) ( static_cast<int>( sizeof(x) / sizeof( 0[(x)] ) ) )

/**
 * Note: I use an outer namespace rt.
 *
 * I'd prefer an inner namespace rt, however that prevents users to e.g.:
 * - using namespace phys::units::io;
 * - using namespace phys::units::io::eng
 *
 * Instead they would have to write:
 * - using namespace phys::units::rt::io;
 * - using namespace phys::units::rt::io::eng
 *
 * Which defeates the hiding of namespace rt.
 *
 * Hopefully there'll be no collision with namespace rt of another library.
 */
namespace rt { namespace phys { namespace units {

#ifdef PHYS_UNITS_REP_TYPE
    typedef PHYS_UNITS_REP_TYPE Rep;
#else
    typedef double Rep;
#endif

/**
 * quantity error base class.
 */
struct quantity_error : public std::runtime_error
{
    quantity_error( std::string const text )
    : std::runtime_error( text )
    {
    }
};

/**
 * bad quantity cast error.
 */
struct bad_quantity_cast : public quantity_error
{
    bad_quantity_cast( std::string const text )
    : quantity_error( text )
    {
    }
};

/**
 * dimension error.
 */
struct dimension_error : public quantity_error
{
    dimension_error( std::string const text )
    : quantity_error( text )
    {
    }
};

/**
 * dimension representation.
 */
class dimensions
{
public:
    /**
     * the single dimension value type.
     */
    typedef signed char value_type;

    /**
     * default constructor.
     */
    dimensions()
    : d( 7 + PHYS_UNITS_QUANTITY_UNIT_EXT_COUNT )
    {
    }

    /**
     * constructor to set a specific unit.
     */
    explicit dimensions( int const n, int const v )
    : d( 7 + PHYS_UNITS_QUANTITY_UNIT_EXT_COUNT )
    {
        d[n] = static_cast<value_type>( v );
    }

    /**
     * constructor to set the 7 base SI units (units 4-7 default to 0).
     */
    dimensions(
        int const _1    , int const _2    , int const _3    ,
        int const _4 = 0, int const _5 = 0, int const _6 = 0, int const _7 = 0
    )
    : d( 7 + PHYS_UNITS_QUANTITY_UNIT_EXT_COUNT )
    {
        d[ 0] = static_cast<value_type>( _1 );
        d[ 1] = static_cast<value_type>( _2 );
        d[ 2] = static_cast<value_type>( _3 );

        d[ 3] = static_cast<value_type>( _4 );
        d[ 4] = static_cast<value_type>( _5 );
        d[ 5] = static_cast<value_type>( _6 );
        d[ 6] = static_cast<value_type>( _7 );
    }

    /**
     * constructor to copy a range of units from another quantity.
     */
    dimensions( dimensions const & other, int const from, int const to )
    : d( 7 + PHYS_UNITS_QUANTITY_UNIT_EXT_COUNT )
    {
        for ( int i = from; i < to; ++i )
        {
            d[i] = other.d[i];
        }
    }

    /**
     * true if all units are zero.
     */
    bool is_all_zero() const
    {
        return 0 == std::count_if( d.begin(), d.end(), is_non_zero );
    }

    /**
     * true if this is a base unit: only one unit is set.
     */
    bool is_base() const
    {
        return 1 == std::count_if( d.begin(), d.end(), is_non_zero );
    };

    /**
     * less-than.
     */
    bool operator<( dimensions const & o ) const
    {
        return d < o.d;
    }

    /**
     * equal to.
     */
    bool operator==( dimensions const & o ) const
    {
        return d == o.d;
    }

    /**
     * not equal to.
     */
    bool operator!=( dimensions const & o ) const
    {
        return !( *this == o );
    }

    /**
     * multiply this dimension by other.
     */
    dimensions & operator*=( dimensions const & o )
    {
        std::transform(
        d.begin(), d.end(),
        o.d.begin(),
        d.begin(),
        std::plus<value_type>() );
        return *this;
    }

    /**
     * divide this dimension by other.
     */
    dimensions & operator/=( dimensions const & o )
    {
        std::transform(
        d.begin(), d.end(),
        o.d.begin(),
        d.begin(),
        std::minus<value_type>() );
        return *this;
        }

    /**
     * the product of the dimensions.
     */
    dimensions product( dimensions const & o ) const
    {
        dimensions r( o );
        std::transform(
        d.begin(), d.end(),
        r.d.begin(),
        r.d.begin(),
        std::plus<value_type>() );
        return r;
    }

    /**
     * the quotient of the dimensions.
     */
    dimensions quotient( dimensions const & o ) const
    {
        dimensions r( o );
        std::transform(
        d.begin(), d.end(),
        r.d.begin(),
        r.d.begin(),
        std::minus<value_type>() );
        return r;
    }

    /**
     * the reciprocal of this dimension.
     */
    dimensions reciprocal() const
    {
        dimensions r( *this );
        std::transform(
        r.d.begin(), r.d.end(),
        r.d.begin(),
        std::negate<value_type>() );
        return r;
    }

    /**
     * the integral power of this dimension.
     */
    dimensions power( int const N ) const
    {
        dimensions r( *this );
        std::transform(
        r.d.begin(), r.d.end(),
        r.d.begin(),
        std::bind2nd( std::multiplies<value_type>(), N ) );
        return r;
    }

    /**
     * the integral root of this dimension.
     */
    dimensions root( int const N ) const
    {
        if ( ! is_all_even_multiples( N ) )
        {
            throw dimension_error( "quantity: dimension should be even multiple" );
        }

        dimensions r( *this );
        std::transform(
        r.d.begin(), r.d.end(),
        r.d.begin(),
        std::bind2nd( std::divides<value_type>(), N ) );
        return r;
    }

    /**
    * true if this dimension consists of only even multiples.
    */
    bool is_all_even_multiples( int const N ) const
    {
        return 0 == std::count_if( d.begin(), d.end(),
        std::bind2nd( std::ptr_fun( &dimensions::is_non_even_multiple ), N ) );
    }

    /**
     * the dimension implementation type.
     */
    std::vector<value_type> d;

private:
    static bool is_non_zero( value_type const v )
    {
        return value_type(0) != v;
    }

    static bool is_non_even_multiple( value_type /*const*/ v, int /*const*/ N )
    {
        return value_type(0) != v % N;
    }
};

/** \name Dimension, operations */
/// @{

/**
 * dimension product.
 */
inline dimensions product( dimensions const & lhs, dimensions const & rhs )
{
    return lhs.product( rhs );
}

/**
 * dimension quotient.
 */
inline dimensions quotient( dimensions const & lhs, dimensions const & rhs )
{
    return lhs.quotient( rhs );
}

/**
 * reciprocal of dimension.
 */
inline dimensions reciprocal( dimensions const & lhs )
{
    return lhs.reciprocal();
}

/**
 * integral power of dimension.
 */
inline dimensions power( dimensions const & lhs, int const N )
{
    return lhs.power( N );
}

/**
 * integral root of dimension.
 */
inline dimensions root( dimensions const & lhs, int const N )
{
    return lhs.root( N );
}
/// @}

/** \name Dimension, conversion to text */
/// @{

/**
 * format dimension as string, for example "1,0,0,0,-1,\~".
 */
inline std::string to_string( dimensions const & d )
{
    std::ostringstream os;
    std::copy( d.d.begin(), d.d.end(), std::ostream_iterator<int>( os, ",") );
    return os.str();
}
/// @}

/**
 * incompatible dimensions error.
 */
struct incompatible_dimension_error : public dimension_error
{
    incompatible_dimension_error( std::string text, dimensions const & lhs, dimensions const & rhs )
    : dimension_error(
        (std::string("quantity: incompatible dimension in ") + text + ": lhs:" +
            to_string(lhs) + ", rhs:" + to_string(rhs) ).c_str() )
    {
    }
};

/**
 * quantity.
 */
class quantity
{
public:
    typedef dimensions dimension_type;   //< the dimension type.
    typedef Rep value_type;              //< the magnitude value type.

    /**
     * default constructor.
     */
    quantity()
    : m_dim( )
    , m_value( 0 )
    {
    }

    /**
     * initializing constructor.
     */
    explicit quantity( dimension_type dimensions, value_type val = 0 )
    : m_dim( dimensions )
    , m_value( val )
    {
    }

    /**
     * copy-assignment constructor.
     */
    quantity( quantity const & other )
    : m_dim( other.m_dim )
    , m_value( other.m_value )
    {
    }

    /**
     * assignment operator.
     */
    quantity operator=( quantity other )
    {
        check_dimension( other, "operator=" );
        other.swap( *this );
        return *this;
    }

    /**
     * swap with other.
     */
    void swap( quantity & other )
    {
        using std::swap;
        swap( m_dim, other.m_dim );
        swap( m_value, other.m_value );
    }

    /**
     * reference to internal value (non-const).
     */
    value_type & value( /* permit */ )
    {
        return m_value;
    }

    /**
     * internal value (const).
     */
    value_type value( /* permit */ ) const
    {
        return m_value;
    }

    /**
     * reference to internal dimension (non-const).
     */
    dimension_type & dimension( /* permit */ )
    {
        return m_dim;
    }

    /**
     * internal dimension (const).
     */
    dimension_type dimension( /* permit */ ) const
    {
        return m_dim;
    }

    /**
     * true if has same dimension as other.
     */
    bool same_dimension( quantity const & other ) const
    {
        return m_dim == other.m_dim;
    }

    /**
     * check for same dimension as other; throw incompatible_dimension_error if dimensions differ.
     */
    void check_dimension( quantity const & other, std::string text ) const
    {
        if ( ! same_dimension( other ) )
        {
            throw incompatible_dimension_error( text, m_dim, other.m_dim );
        }
    }

    /**
     * zero quantity with dimension of this quantity.
     */
    quantity zero() const
    {
        return quantity( m_dim, value_type( 0.0 ) );
    }

private:
    dimension_type m_dim;    ///< dimension
    value_type m_value;      ///< magnitude
};

/** \name Quantity, attributes */
/// @{

/**
 * the quantity's magnitude, for example 1000 for 1km; same as q.value().
 */
inline quantity::value_type
magnitude( quantity const & q )
{
    return q.value();
}

/**
 * the quantity's dimension; same as q.dimension().
 */
inline dimensions
dimension( quantity const & q )
{
    return q.dimension();
}
/// @}

/** \name Quantity, operators */
/// @{

/**
 * quan += quan
 */
inline quantity &
operator+=( quantity & lhs, quantity const & rhs )
{
    lhs.check_dimension( rhs, "operator+=" );
    lhs.value() += rhs.value();
    return lhs;
}

/**
 * + quan
 */
inline quantity
operator+( quantity const & rhs )
{
    return quantity( rhs.dimension(), + rhs.value( ) );
}


/**
 * quan + quan
 */
inline quantity
operator+( quantity const & lhs, quantity const & rhs )
{
    lhs.check_dimension( rhs, "operator+" );
    return quantity( lhs.dimension(), lhs.value() + rhs.value() );
}

/**
 * quan -= quan
 */
inline quantity &
operator-=( quantity & lhs, quantity const & rhs )
{
    lhs.check_dimension( rhs, "operator-=" );
    lhs.value() -= rhs.value();
    return lhs;
}

/**
 * \- quan
 */
inline quantity
operator-( quantity const & rhs )
{
    return quantity( rhs.dimension(), - rhs.value( ) );
}

/**
 * quan - quan
 */
inline quantity
operator-( quantity const & lhs, quantity const & rhs )
{
    lhs.check_dimension( rhs, "operator-" );
    return quantity( lhs.dimension(), lhs.value() - rhs.value() );
}

/**
 * quan *= n
 */
inline quantity &
operator*=( quantity & lhs, Rep rhs )
{
    lhs.value() *= rhs;
    return lhs;
}

/**
 * quan * n
 */
inline quantity
operator*( quantity const & lhs, Rep rhs )
{
    return quantity( lhs.dimension(), lhs.value() * rhs );
}

/**
 * n * quan
 */
inline quantity
operator*( Rep lhs, quantity const & rhs )
{
    return quantity( rhs.dimension(),  lhs * rhs.value() );
}

/**
 * quan *= quan
 */
inline quantity &
operator*=( quantity & lhs, quantity const & rhs )
{
    lhs.dimension() *= rhs.dimension();
    lhs.value() *= rhs.value();
    return lhs;
}

/**
 * quan * quan
 * define as member func VC6 if using quantity<> template.
 */
inline quantity
operator*( quantity const & lhs, quantity const & rhs )
{
    return quantity( product(lhs.dimension(), rhs.dimension()), lhs.value() * rhs.value() );
}

/**
 * quan /= n
 */
inline quantity &
operator/=( quantity & lhs, Rep rhs )
{
    lhs.value() /= rhs;
    return lhs;
}

/**
 * quan / n
 */
inline quantity
operator/( quantity const & lhs, Rep rhs )
{
    return quantity( lhs.dimension(), lhs.value() / rhs );
}

/**
 * n / quan
 */
inline quantity
operator/( Rep lhs, quantity const & rhs )
{
    return quantity( reciprocal( rhs.dimension() ), lhs / rhs.value() );
}

/**
 * quan /= quan
 */
inline quantity &
operator/=( quantity & lhs, quantity const & rhs )
{
    lhs.dimension() /= rhs.dimension();
    lhs.value() /= rhs.value();
    return lhs;
}

/**
 * quan / quan
 */
inline quantity
operator/( quantity const & lhs, quantity const & rhs )
{
    return quantity( quotient(lhs.dimension(), rhs.dimension()), lhs.value() / rhs.value() );
}

// Comparison operators

/**
 * equality.
 */
inline bool
operator==( quantity const & lhs, quantity const & rhs )
{
    lhs.check_dimension( rhs, "operator==" );
    return lhs.value() == rhs.value();
}

/**
 * inequality.
 */
inline bool
operator!=( quantity const & lhs, quantity const & rhs )
{
    lhs.check_dimension( rhs, "operator!=" );
    return lhs.value() != rhs.value();
}

/**
 * less-equal.
 */
inline bool
operator<=( quantity const & lhs, quantity const & rhs )
{
    lhs.check_dimension( rhs, "operator<=" );
    return lhs.value() <= rhs.value();
}

/**
 * greater-equal.
 */
inline bool
operator>=( quantity const & lhs, quantity const & rhs )
{
    lhs.check_dimension( rhs, "operator>=" );
    return lhs.value() >= rhs.value();
}

/**
 * less-than.
 */
inline bool
operator<( quantity const & lhs, quantity const & rhs )
{
    lhs.check_dimension( rhs, "operator<" );
    return lhs.value() < rhs.value();
}

/**
 * greater-than.
 */
inline bool
operator>( quantity const & lhs, quantity const & rhs )
{
    lhs.check_dimension( rhs, "operator>" );
    return lhs.value() > rhs.value();
}
/// @}

/** \name Quantity, functions */
/// @{

/**
 * return absolute value;
 * NTS: fabs() versus std::abs().
 */
inline quantity
abs( quantity const & arg )
{
    return quantity( arg.dimension(), fabs( arg.value() ) );
}

/**
 * N-th power.
 */
inline quantity
nth_power( quantity const & arg, int const N )
{
    return quantity( power( arg.dimension(), N ), pow( arg.value(), Rep( N ) ) );
}

// Low powers defined separately for efficiency.

/**
 * square.
 */
inline quantity
square( quantity const & arg )
{
    return arg * arg;
}

/**
 * cube.
 */
inline quantity
cube( quantity const & arg )
{
    return arg * arg * arg;
}

// General root

/**
 * n-th root.
 */
inline quantity
nth_root( quantity const & arg, int const N )
{
    return quantity( root( arg.dimension(), N ), pow( arg.value(), Rep( 1.0 ) / N ) );
}

// Low roots defined separately for convenience.

/**
 * square root.
 */
inline quantity
sqrt( quantity const & arg )
{
    return quantity( root( arg.dimension(), 2 ), pow( arg.value(), Rep( 1.0 ) / 2 ) );
}
/// @}

/** \name Base dimensions */
/// @{
const dimensions dimensionless_d;
const dimensions length_d( 0, 1 );
const dimensions mass_d( 1, 1 );
const dimensions time_interval_d( 2, 1 );
const dimensions electric_current_d( 3, 1 );
const dimensions thermodynamic_temperature_d( 4, 1 );
const dimensions amount_of_substance_d( 5, 1 );
const dimensions luminous_intensity_d( 6, 1 );
/// @}

/** \name Extension dimensions */
/// @{
const dimensions extra_x0_d( 7, 1 );
const dimensions extra_x1_d( 8, 1 );
const dimensions extra_x2_d( 9, 1 );
const dimensions extra_x3_d( 10, 1 );
const dimensions extra_x4_d( 11, 1 );
const dimensions extra_x5_d( 12, 1 );
const dimensions extra_x6_d( 13, 1 );
const dimensions extra_x7_d( 14, 1 );
const dimensions extra_x8_d( 15, 1 );
const dimensions extra_x9_d( 16, 1 );
/// @}

/** \name Quantity, conversion to numeric types */
/// @{

/**
 * return magnitude as requested type, throw bad_quantity_cast if quantity is not dimensionless.
 */
template <typename T>
inline T quantity_cast( quantity const & q )
{
    if ( dimensionless_d != q.dimension() )
    {
        throw bad_quantity_cast( std::string() +
            "cast quantity to '" + typeid(T).name() + "': quantity must be dimensionless" );
    }

    return static_cast<T>( q.value() );
}

/**
 * return magnitude as real; uses quantity_cast<>() and throws bad_quantity_cast if quantity is not dimensionless.
 */
inline double to_real( quantity const & q )
{
    return quantity_cast<double>( q );
}

/**
 * return magnitude as long integer; uses quantity_cast<>() and throws bad_quantity_cast if quantity is not dimensionless.
 */
inline long to_integer( quantity const & q )
{
    return quantity_cast<long>( q );
}
/// @}

/** \name Base units */
/// @{

inline quantity number()
{
    return quantity( dimensionless_d, 1.0 );
}

inline quantity meter()
{
    return quantity( length_d, 1.0 );
}

inline quantity kilogram()
{
    return quantity( mass_d , 1.0 );
}

inline quantity second()
{
    return quantity( time_interval_d , 1.0 );
}

inline quantity ampere()
{
    return quantity( electric_current_d , 1.0 );
}

inline quantity kelvin()
{
    return quantity( thermodynamic_temperature_d , 1.0 );
}

inline quantity mole()
{
    return quantity( amount_of_substance_d , 1.0 );
}

inline quantity candela()
{
    return quantity( luminous_intensity_d , 1.0 );
}

#define PHYS_UNITS_DEFINE_UNIT( u ) \
   inline quantity quantity_##u() \
   { \
      return quantity( PHYS_UNITS_CONCATENATE(PHYS_UNITS_CONCATENATE(extra_,u), _d ), 1.0 ); \
   } \

PHYS_UNITS_DEFINE_UNIT( x0 )
PHYS_UNITS_DEFINE_UNIT( x1 )
PHYS_UNITS_DEFINE_UNIT( x2 )
PHYS_UNITS_DEFINE_UNIT( x3 )
PHYS_UNITS_DEFINE_UNIT( x4 )
PHYS_UNITS_DEFINE_UNIT( x5 )
PHYS_UNITS_DEFINE_UNIT( x6 )
PHYS_UNITS_DEFINE_UNIT( x7 )
PHYS_UNITS_DEFINE_UNIT( x8 )
PHYS_UNITS_DEFINE_UNIT( x9 )
/// @}

/** \name The standard SI prefixes */
/// @{
inline Rep yotta()   { return Rep( 1e+24L ); }
inline Rep zetta()   { return Rep( 1e+21L ); }
inline Rep exa()     { return Rep( 1e+18L ); }
inline Rep peta()    { return Rep( 1e+15L ); }
inline Rep tera()    { return Rep( 1e+12L ); }
inline Rep giga()    { return Rep( 1e+9L ); }
inline Rep mega()    { return Rep( 1e+6L ); }
inline Rep kilo()    { return Rep( 1e+3L ); }
inline Rep hecto()   { return Rep( 1e+2L ); }
inline Rep deka()    { return Rep( 1e+1L ); }
inline Rep deci()    { return Rep( 1e-1L ); }
inline Rep centi()   { return Rep( 1e-2L ); }
inline Rep milli()   { return Rep( 1e-3L ); }
inline Rep micro()   { return Rep( 1e-6L ); }
inline Rep nano()    { return Rep( 1e-9L ); }
inline Rep pico()    { return Rep( 1e-12L ); }
inline Rep femto()   { return Rep( 1e-15L ); }
inline Rep atto()    { return Rep( 1e-18L ); }
inline Rep zepto()   { return Rep( 1e-21L ); }
inline Rep yocto()   { return Rep( 1e-24L ); }
/// @}

/** \name Binary prefixes, pending adoption */
/// @{
inline Rep kibi() { return Rep( 1024 ); }
inline Rep mebi() { return Rep( 1024 * kibi() ); }
inline Rep gibi() { return Rep( 1024 * mebi() ); }
inline Rep tebi() { return Rep( 1024 * gibi() ); }
inline Rep pebi() { return Rep( 1024 * tebi() ); }
inline Rep exbi() { return Rep( 1024 * pebi() ); }
inline Rep zebi() { return Rep( 1024 * exbi() ); }
inline Rep yobi() { return Rep( 1024 * zebi() ); }
/// @}

/** \name The rest of the standard dimensional types, as specified in SP811 */
/// @{
const dimensions absorbed_dose_d            ( 2, 0, -2 );
const dimensions absorbed_dose_rate_d       ( 2, 0, -3 );
const dimensions acceleration_d             ( 1, 0, -2 );
const dimensions activity_of_a_nuclide_d    ( 0, 0, -1 );
const dimensions angular_velocity_d         ( 0, 0, -1 );
const dimensions angular_acceleration_d     ( 0, 0, -2 );
const dimensions area_d                     ( 2, 0, 0 );
const dimensions capacitance_d              ( -2, -1, 4, 2 );
const dimensions concentration_d            ( -3, 0, 0, 0, 0, 1 );
const dimensions current_density_d          ( -2, 0, 0, 1 );
const dimensions dose_equivalent_d          ( 2, 0, -2 );
const dimensions dynamic_viscosity_d        ( -1, 1, -1 );
const dimensions electric_charge_d          ( 0, 0, 1, 1 );
const dimensions electric_charge_density_d  ( -3, 0, 1, 1 );
const dimensions electric_conductance_d     ( -2, -1, 3, 2 );
const dimensions electric_field_strenth_d   ( 1, 1, -3, -1 );
const dimensions electric_flux_density_d    ( -2, 0, 1, 1 );
const dimensions electric_potential_d       ( 2, 1, -3, -1 );
const dimensions electric_resistance_d      ( 2, 1, -3, -2 );
const dimensions energy_d                   ( 2, 1, -2 );
const dimensions energy_density_d           ( -1, 1, -2 );
const dimensions exposure_d                 ( 0, -1, 1, 1 );
const dimensions force_d                    ( 1, 1, -2 );
const dimensions frequency_d                ( 0, 0, -1 );
const dimensions heat_capacity_d            ( 2, 1, -2, 0, -1 );
const dimensions heat_density_d             ( 0, 1, -2 );
const dimensions heat_density_flow_rate_d   ( 0, 1, -3 );
const dimensions heat_flow_rate_d           ( 2, 1, -3 );
const dimensions heat_flux_density_d        ( 0, 1, -3 );
const dimensions heat_transfer_coefficient_d( 0, 1, -3, 0, -1 );
const dimensions illuminance_d              ( -2, 0, 0, 0, 0, 0, 1 );
const dimensions inductance_d               ( 2, 1, -2, -2 );
const dimensions irradiance_d               ( 0, 1, -3 );
const dimensions kinematic_viscosity_d      ( 2, 0, -1 );
const dimensions luminance_d                ( -2, 0, 0, 0, 0, 0, 1 );
const dimensions luminous_flux_d            ( 0, 0, 0, 0, 0, 0, 1 );
const dimensions magnetic_field_strength_d  ( -1, 0, 0, 1 );
const dimensions magnetic_flux_d            ( 2, 1, -2, -1 );
const dimensions magnetic_flux_density_d    ( 0, 1, -2, -1 );
const dimensions magnetic_permeability_d    ( 1, 1, -2, -2 );
const dimensions mass_density_d             ( -3, 1, 0 );
const dimensions mass_flow_rate_d           ( 0, 1, -1 );
const dimensions molar_energy_d             ( 2, 1, -2, 0, 0, -1 );
const dimensions molar_entropy_d            ( 2, 1, -2, -1, 0, -1 );
const dimensions moment_of_force_d          ( 2, 1, -2 );
const dimensions permittivity_d             ( -3, -1, 4, 2 );
const dimensions power_d                    ( 2, 1, -3 );
const dimensions pressure_d                 ( -1, 1, -2 );
const dimensions radiance_d                 ( 0, 1, -3 );
const dimensions radiant_intensity_d        ( 2, 1, -3 );
const dimensions speed_d                    ( 1, 0, -1 );
const dimensions specific_energy_d          ( 2, 0, -2 );
const dimensions specific_heat_capacity_d   ( 2, 0, -2, 0, -1 );
const dimensions specific_volume_d          ( 3, -1, 0 );
const dimensions substance_permeability_d   ( -1, 0, 1 );
const dimensions surface_tension_d          ( 0, 1, -2 );
const dimensions thermal_conductivity_d     ( 1, 1, -3, 0, -1 );
const dimensions thermal_diffusivity_d      ( 2, 0, -1 );
const dimensions thermal_insulance_d        ( 0, -1, 3, 0, 1 );
const dimensions thermal_resistance_d       ( -2, -1, 3, 0, 1 );
const dimensions thermal_resistivity_d      ( -1, -1, 3, 0, 1 );
const dimensions torque_d                   ( 2, 1, -2 );
const dimensions volume_d                   ( 3, 0, 0 );
const dimensions volume_flow_rate_d         ( 3, 0, -1 );
const dimensions wave_number_d              ( -1, 0, 0 );
/// @}

/** \name Handy values */
/// @{
inline Rep      pi()           { return Rep( 3.141592653589793238462L ); }
inline Rep      percent()      { return Rep( 1 ) / 100; }
/// @}

/** \name Not approved for use alone (needed for use with prefixes) */
/// @{
inline quantity gram()         { return kilogram() / 1000; }
/// @}

/** \name The derived SI units, as specified in SP811 */
/// @{
inline Rep      radian()       { return Rep( 1 ); }
inline Rep      steradian()    { return Rep( 1 ); }
inline quantity newton()       { return meter() * kilogram() / square( second() ); }
inline quantity pascal()       { return newton() / square( meter() ); }
inline quantity joule()        { return newton() * meter(); }
inline quantity watt()         { return joule() / second(); }
inline quantity coulomb()      { return second() * ampere(); }
inline quantity volt()         { return watt() / ampere(); }
inline quantity farad()        { return coulomb() / volt(); }
inline quantity ohm()          { return volt() / ampere(); }
inline quantity siemens()      { return ampere() / volt(); }
inline quantity weber()        { return volt() * second(); }
inline quantity tesla()        { return weber() / square( meter() ); }
inline quantity henry()        { return weber() / ampere(); }
inline quantity degree_celsius()   { return kelvin(); }
inline quantity lumen()        { return candela() * steradian(); }
inline quantity lux()          { return lumen() / meter() / meter(); }
inline quantity becquerel()    { return 1 / second(); }
inline quantity gray()         { return joule() / kilogram(); }
inline quantity sievert()      { return joule() / kilogram(); }
inline quantity hertz()        { return 1 / second(); }

// The rest of the units approved for use with SI, as specified in SP811.
// (However, use of these units is generally discouraged.)

inline quantity angstrom()     { return Rep( 1e-10L ) * meter(); }
inline quantity are()          { return Rep( 1e+2L ) * square( meter() ); }
inline quantity bar()          { return Rep( 1e+5L ) * pascal(); }
inline quantity barn()         { return Rep( 1e-28L ) * square( meter() ); }
inline quantity curie()        { return Rep( 3.7e+10L ) * becquerel(); }
inline quantity day()          { return Rep( 86400L ) * second(); }
inline Rep      degree_angle() { return pi() / 180; }
inline quantity gal()          { return Rep( 1e-2L ) * meter() / square( second() ); }
inline quantity hectare()      { return Rep( 1e+4L ) * square( meter() ); }
inline quantity hour()         { return Rep( 3600 ) * second(); }
inline quantity knot()         { return Rep( 1852 ) / 3600 * meter() / second(); }
inline quantity liter()        { return Rep( 1e-3L ) * cube( meter() ); }
inline quantity minute()       { return Rep( 60 ) * second(); }
inline Rep      minute_angle() { return pi() / 10800; }
inline quantity mile_nautical() { return Rep( 1852 ) * meter(); }
inline quantity rad()          { return Rep( 1e-2L ) * gray(); }
inline quantity rem()          { return Rep( 1e-2L ) * sievert(); }
inline quantity roentgen()     { return Rep( 2.58e-4L ) * coulomb() / kilogram(); }
inline Rep      second_angle() { return pi() / 648000L; }
inline quantity ton_metric()   { return Rep( 1e+3L ) * kilogram(); }

// Alternate (non-US) spellings:

inline quantity metre()        { return meter(); }
inline quantity litre()        { return liter(); }
inline Rep      deca()         { return deka(); }
inline quantity tonne()        { return ton_metric(); }
/// @}

}}} // namespace rt { namespace phys { namespace units {

#ifndef PHYS_UNITS_IN_RT_NAMESPACE
using namespace rt;
#endif

#endif // PHYS_UNITS_QUANTITY_HPP_INCLUDED

/*
 * end of file
 */
