/*
 * TestComparison.cpp
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

TEST_CASE( "quantity/operator/comparison", "Quantity comparison operators" )
{
    quantity neg2( -2 * watt() );
    quantity neg1( -1 * watt() );
    quantity z( 0 * watt() );
    quantity pos1( 1 * watt() );
    quantity pos2( 2 * watt() );

    REQUIRE( ( neg1 == neg1 ) == true );
    REQUIRE( ( neg1 != neg1 ) == false );
    REQUIRE( ( neg1 <= neg1 ) == true );
    REQUIRE( ( neg1 >= neg1 ) == true );
    REQUIRE( ( neg1 <  neg1 ) == false );
    REQUIRE( ( neg1 >  neg1 ) == false );

    REQUIRE( ( z == z ) == true );
    REQUIRE( ( z != z ) == false );
    REQUIRE( ( z <= z ) == true );
    REQUIRE( ( z >= z ) == true );
    REQUIRE( ( z <  z ) == false );
    REQUIRE( ( z >  z ) == false );

    REQUIRE( ( pos1 == pos1 ) == true );
    REQUIRE( ( pos1 != pos1 ) == false );
    REQUIRE( ( pos1 <= pos1 ) == true );
    REQUIRE( ( pos1 >= pos1 ) == true );
    REQUIRE( ( pos1 <  pos1 ) == false );
    REQUIRE( ( pos1 >  pos1 ) == false );

    REQUIRE( ( z == neg1 ) == false );
    REQUIRE( ( z != neg1 ) == true );
    REQUIRE( ( z <= neg1 ) == false );
    REQUIRE( ( z >= neg1 ) == true );
    REQUIRE( ( z <  neg1 ) == false );
    REQUIRE( ( z >  neg1 ) == true );

    REQUIRE( ( z == pos1 ) == false );
    REQUIRE( ( z != pos1 ) == true );
    REQUIRE( ( z <= pos1 ) == true );
    REQUIRE( ( z >= pos1 ) == false );
    REQUIRE( ( z <  pos1 ) == true );
    REQUIRE( ( z >  pos1 ) == false );

    REQUIRE( ( neg1 == z ) == false );
    REQUIRE( ( neg1 != z ) == true );
    REQUIRE( ( neg1 <= z ) == true );
    REQUIRE( ( neg1 >= z ) == false );
    REQUIRE( ( neg1 <  z ) == true );
    REQUIRE( ( neg1 >  z ) == false );

    REQUIRE( ( pos1 == z ) == false );
    REQUIRE( ( pos1 != z ) == true );
    REQUIRE( ( pos1 <= z ) == false );
    REQUIRE( ( pos1 >= z ) == true );
    REQUIRE( ( pos1 <  z ) == false );
    REQUIRE( ( pos1 >  z ) == true );

    REQUIRE( ( neg1 == neg2 ) == false );
    REQUIRE( ( neg1 != neg2 ) == true );
    REQUIRE( ( neg1 <= neg2 ) == false );
    REQUIRE( ( neg1 >= neg2 ) == true );
    REQUIRE( ( neg1 <  neg2 ) == false );
    REQUIRE( ( neg1 >  neg2 ) == true );

    REQUIRE( ( neg2 == neg1 ) == false );
    REQUIRE( ( neg2 != neg1 ) == true );
    REQUIRE( ( neg2 <= neg1 ) == true );
    REQUIRE( ( neg2 >= neg1 ) == false );
    REQUIRE( ( neg2 <  neg1 ) == true );
    REQUIRE( ( neg2 >  neg1 ) == false );

    REQUIRE( ( neg1 == pos1 ) == false );
    REQUIRE( ( neg1 != pos1 ) == true );
    REQUIRE( ( neg1 <= pos1 ) == true );
    REQUIRE( ( neg1 >= pos1 ) == false );
    REQUIRE( ( neg1 <  pos1 ) == true );
    REQUIRE( ( neg1 >  pos1 ) == false );

    REQUIRE( ( pos1 == neg1 ) == false );
    REQUIRE( ( pos1 != neg1 ) == true );
    REQUIRE( ( pos1 <= neg1 ) == false );
    REQUIRE( ( pos1 >= neg1 ) == true );
    REQUIRE( ( pos1 <  neg1 ) == false );
    REQUIRE( ( pos1 >  neg1 ) == true );

    REQUIRE( ( pos1 == pos2 ) == false );
    REQUIRE( ( pos1 != pos2 ) == true );
    REQUIRE( ( pos1 <= pos2 ) == true );
    REQUIRE( ( pos1 >= pos2 ) == false );
    REQUIRE( ( pos1 <  pos2 ) == true );
    REQUIRE( ( pos1 >  pos2 ) == false );

    REQUIRE( ( pos2 == pos1 ) == false );
    REQUIRE( ( pos2 != pos1 ) == true );
    REQUIRE( ( pos2 <= pos1 ) == false );
    REQUIRE( ( pos2 >= pos1 ) == true );
    REQUIRE( ( pos2 <  pos1 ) == false );
    REQUIRE( ( pos2 >  pos1 ) == true );
}

/*
 * end of file
 */
