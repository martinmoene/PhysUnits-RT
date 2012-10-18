/*
 * TestFunction.cpp
 *
 * Created by Martin on 13 October 2012.
 * Copyright 2012 Universiteit Leiden. All rights reserved.
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "TestUtil.hpp"

#include "catch.hpp"
#include "phys/units/io.hpp"
#include "phys/units/quantity.hpp"

#ifdef PHYS_UNITS_IN_RT_NAMESPACE
using namespace rt::phys::units;
using namespace rt::phys::units::io;
#else
using namespace phys::units;
using namespace phys::units::io;
#endif

TEST_CASE( "quantity/function/power", "Quantity power functions" )
{
    // general powers

    quantity f1( 2 * newton() );

    REQUIRE( b(nth_power( f1, 10 ) ) == "1024.000000 m+10 kg+10 s-20" );
    REQUIRE( b(nth_power( f1, 4 ) ) == "16.000000 m+4 kg+4 s-8" );
    REQUIRE( b(nth_power( f1, 3 ) ) == "8.000000 m+3 kg+3 s-6" );
    REQUIRE( b(nth_power( f1, 2 ) ) == "4.000000 m+2 kg+2 s-4" );
    REQUIRE( b(nth_power( f1, 1 ) ) == "2.000000 m kg s-2" );
    REQUIRE( b(nth_power( f1, 0 ) ) == "1.000000" );
    REQUIRE( b(nth_power( f1, -1 ) ) == "0.500000 m-1 kg-1 s+2" );
    REQUIRE( b(nth_power( f1, -2 ) ) == "0.250000 m-2 kg-2 s+4" );

    // special powers

    REQUIRE( b(square( f1 ) ) == "4.000000 m+2 kg+2 s-4" );
    REQUIRE( b(cube( f1 ) ) == "8.000000 m+3 kg+3 s-6" );
}

TEST_CASE( "quantity/function/root", "Quantity root functions" )
{
    // general roots

    quantity hv( 10000 * meter() * meter() * meter() * meter() );

    REQUIRE( b(nth_root( hv, 4 ) ) == "10.000000 m" );
    REQUIRE( b(nth_root( hv, 2 ) ) == "100.000000 m+2" );
    REQUIRE( b(nth_root( hv, 1 ) ) == "10000.000000 m+4" );
    REQUIRE( b(nth_root( hv, -1 ) ) == "0.000100 m-4" );
    REQUIRE( b(nth_root( hv, -2 ) ) == "0.010000 m-2" );
    REQUIRE( b(nth_root( hv, -4 ) ) == "0.100000 m-1" );

    // special roots

    REQUIRE( b(sqrt( hv ) ) == "100.000000 m+2" );

    quantity p1( 3 * watt() );
    quantity p2( 4 * watt() );

    REQUIRE( b(sqrt( square( p1 ) + square( p2 ) ) ) == "5.000000 m+2 kg s-3" );

    quantity freq( 25 / second() );
    quantity thing( 9 * ampere() * ampere() / second() );

    REQUIRE( b(sqrt( freq * thing ) ) == "15.000000 s-1 A" );
}

TEST_CASE( "quantity/function/various", "Quantity, various functions" )
{
    quantity m( meter() );
    // abs
    REQUIRE( b(abs(  m ) ) == "1.000000 m" );
    REQUIRE( b(abs( +m ) ) == "1.000000 m" );
    REQUIRE( b(abs( -m ) ) == "1.000000 m" );
}

TEST_CASE( "quantity/function/exception", "Quantity function exceptions" )
{
    INFO( "dimension powers must be even mutiples:" );
    REQUIRE_THROWS_AS( nth_root( meter() * meter() / second(), 2), dimension_error );

    INFO( "quantity must be dimensionless when used in cast (regardless destination):" );
    REQUIRE_THROWS_AS( quantity_cast<double>( meter() ), bad_quantity_cast );
}

/*
 * end of file
 */
