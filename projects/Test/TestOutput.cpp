/*
 * TestOutput.cpp
 *
 * Created by Martin on 17 October 2012.
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

TEST_CASE( "output/convert", "Quantity output conversions" )
{
}

TEST_CASE( "output/exception", "Quantity output exceptions" )
{
    REQUIRE_THROWS_AS( prefix( "x" ), prefix_error );
    REQUIRE_THROWS_AS(   unit( "x" ), unit_error );
    REQUIRE_NOTHROW  (   unit( "x", extend() ) );
}

/*
 * end of file
 */
