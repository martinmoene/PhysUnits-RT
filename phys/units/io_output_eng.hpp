/**
 * \file io_output_eng.hpp
 *
 * \brief   Engineering IO for run-time quantity library.
 * \author  Jukka Korpela, David Hoerl, Martin Moene
 * \date    18 April 2012
 * \since   1.0
 *
 * This code is provided as-is, with no warrantee of correctness.
 * Copyright 2012 Universiteit Leiden. All rights reserved.
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef PHYS_UNITS_IO_OUTPUT_ENG_HPP_INCLUDED
#define PHYS_UNITS_IO_OUTPUT_ENG_HPP_INCLUDED

#include "phys/units/io_output.hpp"

#include <iomanip>
#include <limits>

/*
 * Note: micro, µ, may not work everywhere, so you can define a glyph yourself:
 */
#ifndef PHYS_UNITS_MICRO_GLYPH
# define PHYS_UNITS_MICRO_GLYPH "µ"
#endif

namespace rt { namespace phys { namespace units {

namespace detail {

/**
 * format quantity in engineering units.
 * code derived from http://www.cs.tut.fi/~jkorpela/c/eng.html, by Jukka Korpela.
 */
class eng_format
{
public:
   typedef dimensions dimension_type;
   typedef Rep value_type;

   eng_format( quantity const & q, int const digits = 6, bool const showpos = false )
   : m_magnitude()
   , m_unit()
   , m_fixed( false )
   , m_showpos( showpos )
   {
      construct( q, digits );
   }

   std::string magnitude() const
   {
      return m_magnitude;
   }

   std::string unit() const
   {
      return m_unit;
   }

   std::string repr() const
   {
      return magnitude() + " " + unit();
   }

private:
   /*
    * Note that here x is always positive, no need to round symmetrically:
    */
   static int lrint( value_type const x )
   {
      return static_cast<int>( x + std::numeric_limits<value_type>::epsilon() );
   }

   /*
    * single symbol, not being kg and prefix is within range:
    */
   static bool fits_eng_notation( quantity const & q, int const expof10, int const prefix_start, int const prefix_end )
   {
      return q.dimension() != mass_d
          && has_unit_name( q.dimension() )
          && prefix_start <= expof10 && expof10 <= prefix_end;
   }

   void construct( quantity const & q, int digits )
   {
      static char const * prefix[] =
      {
         "y", "z", "a", "f", "p", "n", PHYS_UNITS_MICRO_GLYPH, "m", "",
         "k", "M", "G", "T", "P", "E", "Z", "Y"
      };

      // from "y" to "Y":
      const int prefix_start = -24;
      const int prefix_end   = prefix_start + 3 * ( PHYS_UNITS_DIMENSION_OF( prefix ) -1 );

      const char * sign = "";

      value_type value = q.value();

//       assert( isnormal( value ) ); // could also return NULL

      if( value < 0.0 )
      {
         sign  = "-";
         value = -value;
      }
      else if ( m_showpos )
      {
         sign = "+";
      }
      else
      {
         sign = "";
      }

      /*
       * correctly round to desired number of digits:
       */
      int expof10 = lrint( floor( log10( value ) ) );
      value      *= pow( 10.0, digits - 1 - expof10 );

      /*
       * contrary to VC2010 documentation, it seems that
       *   long double modf( long double, long double* )
       * isn't available; same for GCC 4.5.2.
       */
      double display = 0.0;
      value_type fract = modf( value, &display );

      if ( fract >= 0.5 )
      {
         display += 1.0;
      }

      value = display * pow( 10.0, expof10 - digits + 1 );

      if ( expof10 > 0 )
      {
         expof10 = ( expof10 / 3 ) * 3;
      }
      else
      {
         expof10 = ( ( -expof10 + 3 ) / 3 ) * (-3);
      }

      value *= pow( 10.0, -expof10 );

      if (value >= 1000.0)
      {
         value   /= 1000.0;
         expof10 += 3;
      }
      else if (value >= 100.0)
      {
         digits -= 2;
      }
      else if ( value >= 10.0 )
      {
         digits -= 1;
      }

      if ( fits_eng_notation( q, expof10, prefix_start, prefix_end ) )
      {
         std::ostringstream os;

         if ( m_fixed )
         {
            os << sign << std::fixed << std::setprecision(digits-1) << value;
         }
         else
         {
            os << sign << value;
         }

         m_magnitude = os.str();

         m_unit = std::string( prefix[ ( expof10 - prefix_start ) / 3] );
      }
      else
      {
         std::ostringstream os;

         if ( m_fixed )
         {
            os << sign << std::fixed << std::setprecision(digits-1) << value << "e" << expof10;
         }
         else
         {
            os << sign << value << "e" << expof10;
         }
         m_magnitude = os.str();
      }

      m_unit += to_unit_symbol( q );
   }

private:
   std::string m_magnitude;
   std::string m_unit;
   bool m_fixed;
   bool m_showpos;
};

} // namespace detail {

/** \name Quantity, convert quantity elements to text in engineering format */
/// @{

/**
 * convert the magnitude of given quantity to string as "{magnitude}".
 */
inline std::string
to_eng_magnitude( quantity const & q, int const digits = 6, bool const showpos = false )
{
   return detail::eng_format( q, digits, showpos ).magnitude();
}

/**
 * convert the dimension of given quantity to string as "{prefix}{symbol}".
 */
inline std::string
to_eng_unit( quantity const & q )
{
   return detail::eng_format( q ).unit();
}

/**
 * convert given quantity to string as "{magnitude} ' ' {prefix}{symbol}".
 */
inline std::string
to_eng_string( quantity const & q, int const digits = 6, bool const showpos = false )
{
   return detail::eng_format( q, digits, showpos ).repr();
}

/// @}

namespace io {
namespace eng {

/**
 * convert given quantity to string as "{magnitude} ' ' {prefix}{symbol}".
 */
inline std::string
to_string( quantity const & q, int const digits = 6, bool const showpos = false )
{
   return to_eng_string( q, digits, showpos );
}

/**
 * stream quantity to stream as "{magnitude} ' ' {prefix}{symbol}".
 */
inline std::ostream & operator<<( std::ostream & os, quantity const & q )
{
   return os << to_string( q );
}

} // namespace eng
} // namespace io

}}} // namespace units { namespace phys { namespace rt {

#endif // PHYS_UNITS_IO_OUTPUT_ENG_HPP_INCLUDED

/*
 * end of file
 */

