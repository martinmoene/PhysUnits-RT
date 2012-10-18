/*
 * TestPrefix.cpp
 *
 * Created by Martin on 13 October 2012.
 * Copyright 2012 Universiteit Leiden. All rights reserved.
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

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

TEST_CASE( "prefix/metric", "The standard SI prefixes" )
{
    REQUIRE( to_string( 1e-24 * yotta() ) == "1" );
    REQUIRE( to_string( 1e-21 * zetta() ) == "1" );
    REQUIRE( to_string( 1e-18 * exa() ) == "1" );
    REQUIRE( to_string( 1e-15 * peta() ) == "1" );
    REQUIRE( to_string( 1e-12 * tera() ) == "1" );
    REQUIRE( to_string( 1e-9 * giga() ) == "1" );
    REQUIRE( to_string( 1e-6 * mega() ) == "1" );
    REQUIRE( to_string( 1e-3 * kilo() ) == "1" );
    REQUIRE( to_string( 1e-2 * hecto() ) == "1" );
    REQUIRE( to_string( 1e-1 * deka() ) == "1" );
    REQUIRE( to_string( 1e-1 * deca() ) == "1" );
    REQUIRE( to_string( 1e1 * deci() ) == "1" );
    REQUIRE( to_string( 1e2 * centi() ) == "1" );
    REQUIRE( to_string( 1e3 * milli() ) == "1" );
    REQUIRE( to_string( 1e6 * micro() ) == "1" );
    REQUIRE( to_string( 1e9 * nano() ) == "1" );
    REQUIRE( to_string( 1e12 * pico() ) == "1" );
    REQUIRE( to_string( 1e15 * femto() ) == "1" );
    REQUIRE( to_string( 1e18 * atto() ) == "1" );
    REQUIRE( to_string( 1e21 * zepto() ) == "1" );
    REQUIRE( to_string( 1e24 * yocto() ) == "1" );
}

TEST_CASE( "prefix/binary", "Binary prefixes, pending adoption" )
{
    REQUIRE( to_string( kibi() ) == "1024" );
    REQUIRE( to_string( mebi() / kibi() ) == "1024" );
    REQUIRE( to_string( gibi() / mebi() ) == "1024" );
    REQUIRE( to_string( tebi() / gibi() ) == "1024" );
    REQUIRE( to_string( pebi() / tebi() ) == "1024" );
    REQUIRE( to_string( exbi() / pebi() ) == "1024" );
    REQUIRE( to_string( zebi() / exbi() ) == "1024" );
    REQUIRE( to_string( yobi() / zebi() ) == "1024" );
}

/*
 * end of file
 */
