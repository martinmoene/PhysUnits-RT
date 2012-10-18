/*
 * TestInput.cpp
 *
 * Created by Martin on 16 October 2012.
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

TEST_CASE( "input/convert", "Quantity parser string to value conversions" )
{
    CAPTURE( magnitude( to_quantity( "2 (3 hm)2" ) ) );
    CAPTURE(     to_numerical_value( "2 (3 hm)2" )   );

    REQUIRE(     magnitude( to_quantity( "2 (3 m)" ) ) == 6 );
    REQUIRE(         to_numerical_value( "2 (3 m)" )   == 2 );
    REQUIRE( !!(                to_unit( "2 (3 m)" )   == 3 * meter() ) );

    REQUIRE( !!(            to_quantity( "45 km/h" )   == quantity( 45 * kilo() * meter() / hour() ) ) );
    REQUIRE( !!( dimension( to_quantity( "45 km/h" ) ) == quantity(      kilo() * meter() / hour() ).dimension() ) );

    REQUIRE(     magnitude( to_quantity( "45 km/h" ) ) == 12.5 );
    REQUIRE(         to_numerical_value( "45 km/h" )   == 45   );
    REQUIRE( !!(                to_unit( "45 km/h" )   == kilo() * meter() / hour() ) );
}

TEST_CASE( "input/exception", "Quantity parser exceptions" )
{
    REQUIRE_THROWS( to_quantity( "m/s/s" ) );

    INFO( "Expect garbage:" );
    REQUIRE_THROWS_AS( to_quantity( "(m)a"  ), quantity_parser_error );

    INFO( "Expect invalid prefix:" );
    REQUIRE_THROWS_AS( to_quantity( "xm"    ), quantity_parser_error );

    INFO( "Expect consecutive operators:" );
    REQUIRE_THROWS_AS( to_quantity( "m..m"  ), quantity_parser_error );

    INFO( "Expect repeated solidus:" );
    REQUIRE_THROWS_AS( to_quantity( "m/s/s" ), quantity_parser_error );

    INFO( "Expect expect 1/{unit}:" );
    REQUIRE_THROWS_AS( to_quantity( "7 1k"  ), quantity_parser_error );

    INFO( "Expect expect unit:" );
    REQUIRE_THROWS_AS( to_quantity( "3"     ), quantity_parser_error );

    INFO( "Expect expect ')':" );
    REQUIRE_THROWS_AS( to_quantity( "(3 m"  ), quantity_parser_error );
}

/*
 * end of file
 */
