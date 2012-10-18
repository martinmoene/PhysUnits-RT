/**
 * \file demo.cpp
 *
 * \brief   test driver for quantity library.
 * \author  Michael S. Kenniston, Martin Moene
 * \date    20 February 2012
 * \since   0.4
 *
 * Copyright (c) 2001 by Michael S. Kenniston.  For the most
 * recent version check www.xnet.com/~msk/quantity.  Permission is granted
 * to use this code without restriction so long as this copyright
 * notice appears in all source files.
 *
 * This code is provided as-is, with no warrantee of correctness.
 *
 * This program demonstrates simple use of the "quantity" library,
 * which allows compile-time type-safety for the dimensionality
 * (meter vs. kilogram) and units (meter vs. foot) of variables
 * representing physical quantity.
 */

#define PHYS_UNITS_REP_TYPE long double
#define PHYS_UNITS_MICRO_GLYPH "u"

#include "phys/units/quantity.hpp"              // required
#include "phys/units/io_output.hpp"             // required for operator<<
#include "phys/units/io_output_eng.hpp"         // operator<< and unit names and symbols

#include "phys/units/other_units.hpp"           // optional
#include "phys/units/physical_constants.hpp"    // optional

#include "user_example.hpp"                     // roll-your-own

#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

#ifndef PHYS_UNITS_COMPILER_IS_MSVC6

using phys::units::ampere;
using phys::units::area_d;
using phys::units::becquerel;
using phys::units::c;
using phys::units::candela;
using phys::units::coulomb;
using phys::units::cube;
using phys::units::degree_celsius;
using phys::units::dimensions;
using phys::units::electric_potential_d;
using phys::units::farad;
using phys::units::force_d;
using phys::units::fortnight;
using phys::units::frequency_d;
using phys::units::furlong;
using phys::units::gray;
using phys::units::henry;
using phys::units::hertz;
using phys::units::hour;
using phys::units::joule;
using phys::units::kelvin;
using phys::units::kilo;
using phys::units::kilogram;
using phys::units::length_d;
using phys::units::lumen;
using phys::units::lux;
using phys::units::mass_d;
using phys::units::mega;
using phys::units::meter;
using phys::units::micro;
using phys::units::mile;
using phys::units::milli;
using phys::units::mole;
using phys::units::nano;
using phys::units::newton;
using phys::units::nth_power;
using phys::units::nth_root;
using phys::units::ohm;
using phys::units::pascal;
using phys::units::power_d;
using phys::units::quantity;
using phys::units::radian;
using phys::units::second;
using phys::units::siemens;
using phys::units::sievert;
using phys::units::speed_d;
using phys::units::sqrt;
using phys::units::square;
using phys::units::steradian;
using phys::units::tera;
using phys::units::tesla;
using phys::units::time_interval_d;
using phys::units::volt;
using phys::units::volume_d;
using phys::units::watt;
using phys::units::weber;

#else
using namespace phys::units;
#endif

using hyperspace::scotty;
using hyperspace::warp_factor_d;

using namespace std;

int main()
{
   {
#ifndef PHYS_UNITS_COMPILER_IS_MSVC6
    using phys::units::io::operator<<;
#else
    using namespace phys::units::io;
#endif

    cout << "Demonstration of quantity library." << endl;

    // Output of built-in units.

    cout << "meter = " << meter() << endl;
    cout << "kilogram = " << kilogram() << endl;
    cout << "second = " << second() << endl;
    cout << "ampere = " << ampere() << endl;
    cout << "kelvin = " << kelvin() << endl;
    cout << "mole = " << mole() << endl;
    cout << "candela = " << candela() << endl;

    cout << "+ quan: " << + meter() << endl;
    cout << "quan + quan: " << kilogram() + kilogram() << endl;
    quantity t( second() );
    t += second();

    cout << "- quan: " << - ampere() << endl;
    cout << "quan - quan: " << t - second() << endl;
    t -= second();

    quantity mass( kilogram() );
    cout << "num * quan: " << 3 * mass << endl;
    cout << "quan * num: " << mass * 4 << endl;
    mass *= 5;
    cout << "quan *= num: " << mass << endl;
    cout << "quan * quan: " << kilogram() * kelvin() << endl;

    quantity freq( hertz() );
    freq = 5 / second();

    // Mixed double and quantity arithmetic

    cout << meter() * 1.2f << " is the same as " << 1.2f * meter() << endl;

    cout << meter() / 2 << " is the reciprocal of " << 2 / meter() << endl;

    mass = 2 * kilogram();
    mass = 3 * kilogram();
    mass = kilogram() * 3.5;
    mass *= 4;
    mass = mass / 5;
    mass /= 6;
    cout << mass << endl;

    // quantity arithmetic

    quantity length( 4 * meter() );
    length = length + 5 * meter();
    length += 6 * meter();
    length = 7 * meter() - length;
    length -= 8 * meter();
    cout << length << endl;

    length = -length;
    quantity width( 1.2f * meter() );
    quantity height( 2.3f * meter() );
    quantity area( length * width );
    cout << "volume = " << height * area << endl;

    quantity speed = length / second();
    length = speed * second();

    // Relational operators;

    bool b;
    b = ( length == width );
    b = ( length != width );
    b = ( length >  width );
    b = ( length >= width );
    b = ( length <  width );
    b = ( length <= width );

    // Output of units with a range of exponents.

    cout << "kitchen sink = " << 123456789.0f
        * meter() * meter() * meter()
        * kilogram() * kilogram()
        * second()
        / kelvin()
        / mole() / mole()
        / candela() / candela() / candela() << endl;

    // Explicit unit conversion is required on input
    // (multiply by the desired unit).

    double d = 4.5; // could be read from input
    length = d * kilo() * meter();
    length = d * mile();

    // Implicit conversion to SI units is the default on output.

    cout << "1 mile = " << mile() << endl;

    // For explicit unit conversion on output, divide by the desired unit.

    cout << "1 kilometer = " << kilo() * meter() / mile() << " mile" << endl;

    // quantity operations can yield a double.

    double r = to_real( length / width );
    r = to_real( speed * ( second() / meter() ) );

    // Arrays and vectors of quantity are allowed.

   std::cout << "\n...Skipping vectors for now...\n" << std::endl;
#if 0
    quantity< force_d > forcearray[ 10 ];
    vector< quantity< power_d > > powervec;

    // Standard algorithms can be used on physical quantity.

    for( int i = 0; i < 10; i++ )
    {
        powervec.push_back( watt() * double( rand()) / RAND_MAX );
    }

    sort( powervec.begin(), powervec.end() );

    cout << "power vector = " << endl;
    vector< quantity >::iterator iter;
    for( iter = powervec.begin(); iter != powervec.end(); iter++ )
    {
        cout << "    " << *iter << endl;
    }

    phys::units::quantity sum( phys::units::quantity< power_d >::zero() );
    if ( sum == quantity< power_d >::zero() ) cout << "init correctly\n";
    sum = quantity< power_d >::zero();
    for( iter = powervec.begin(); iter != powervec.end(); iter++ )
    {
        sum += *iter;
    }
    cout << "sum = " << sum << endl;
    if( sum > quantity< power_d >::zero() ) cout << "sum is greater than zero\n";
#endif

    // Custom types and units can be defined and used.

    quantity full_power = 3.27 * mega() * scotty();
    cout << "full power = " << full_power << endl;

    // Misc stuff.

    cout << "60 cubic meters = " <<
        ( 3 * meter() ) * ( 4 * meter() ) * ( 5 * meter() ) << endl;

    length = 3 * meter();
    cout << "the side is " << length << "\n";
    area = length * length;
    area = square( length );
    cout << "the area is " << area << endl;
    quantity vol = cube( length );

    cout << "the side is " << nth_root( area, 2 ) << endl;
    cout << "the area is " << nth_power( length, 2 ) << endl;
    cout << "the volume is " << nth_power( length, 3 ) << endl;

    cout << "the sqrt of the area is " << sqrt( area ) << endl;
    cout << "the 3rd root of " << 1000 * meter() * meter() * meter() << " is " <<
        nth_root( 1000 * meter() * meter() * meter(), 3 ) << endl;

//    typedef dimensions< 4, 8, 12, 0, -4, -8, -12 > mongo_d;
//    const dimensions mongo_d( 4, 8, 12, 0, -4, -8, -12 );
    const dimensions mongo_d( 4, 8, 12, 0, -4, -8, -12 );
    quantity nothing( quantity( mongo_d, 0 ).zero() );
    cout << "mongo = " << nothing << endl;
    cout << "4th root of mongo = " << nth_root( nothing, 4 ) << endl;

    cout << "the speed of light in a vacuum is " << c() / ( tera() * furlong() / fortnight() ) <<
        " terafurlong / fortnight" << endl;

    cout << 456789 * kilo() * watt() * hour() << "\n";

    // unit names (added by Martin Moene, February 2012):

    cout <<
        "Unit symbols:\n" <<
        ampere() << "\n" <<
        becquerel() << "\n" <<
        candela() << "\n" <<
        coulomb() << "\n" <<
        degree_celsius() << "\n" <<
        farad() << "\n" <<
        gray() << "\n" <<
        henry() << "\n" <<
        hertz() << "\n" <<
        joule() << "\n" <<
        kelvin() << "\n" <<
        kilogram() << "\n" <<
        lumen() << "\n" <<
        lux() << "\n" <<
        meter() << "\n" <<
        newton() << "\n" <<
        ohm() << "\n" <<
        pascal() << "\n" <<
        radian() << "\n" <<
        second() << "\n" <<
        siemens() << "\n" <<
        sievert() << "\n" <<
        steradian() << "\n" <<
        tesla() << "\n" <<
        volt() << "\n" <<
        watt() << "\n" <<
        weber() << "\n" <<
        std::endl;
    }

    // engineering notation (added by Martin Moene, April 2012):
    {
#ifndef PHYS_UNITS_COMPILER_IS_MSVC6
    using phys::units::io::eng::operator<<;
#else
    using namespace phys::units::io::eng;
#endif

    cout <<
        "Engineering notation:\n" <<
        milli() * ampere() << "\n" <<
        milli() * becquerel() << "\n" <<
        kilo() * candela() << "\n" <<
        kilo() * coulomb() << "\n" <<
        milli() * degree_celsius() << "\n" <<
        nano() * farad() << "\n" <<
        milli() * gray() << "\n" <<
        milli() * henry() << "\n" <<
        kilo() * hertz() << "\n" <<
        kilo() * joule() << "\n" <<
        micro() * kelvin() << "\n" <<
        kilo() * kilogram() << "\n" <<
        kilo() * lumen() << "\n" <<
        kilo() * lux() << "\n" <<
        kilo() * meter() << "\n" <<
        kilo() * newton() << "\n" <<
        kilo() * ohm() << "\n" <<
        kilo() * pascal() << "\n" <<
        micro() * radian() << "\n" <<
        milli() * second() << "\n" <<
        milli() * siemens() << "\n" <<
        milli() * sievert() << "\n" <<
        kilo() * steradian() << "\n" <<
        milli() * tesla() << "\n" <<
        kilo() * volt() << "\n" <<
        kilo() * watt() << "\n" <<
        milli() * weber() << "\n" <<
        std::endl;
   }

    return 0;
}
