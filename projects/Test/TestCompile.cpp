/*
 * TestCompile.cpp
 *
 * Created by Martin on 13 October 2012.
 * Copyright 2012 Universiteit Leiden. All rights reserved.
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "catch.hpp"
#include "phys/units/quantity.hpp"

#ifdef PHYS_UNITS_IN_RT_NAMESPACE
using namespace rt::phys::units;
#else
using namespace phys::units;
#endif

void compile()
{
    meter();
    meter() + meter();
    meter() - meter();
    meter() * meter();
    meter() / meter();

    meter() == meter();
    meter() != meter();

    meter() <  meter();
    meter() <= meter();
    meter() >  meter();
    meter() >= meter();

    quantity m( meter() );
    m += meter();
    m -= meter();
    m *= meter();
    m /= meter();

    to_real( meter() / meter() );
    to_integer( meter() / meter() );

    product ( length_d, length_d );
    quotient( length_d, length_d );
    quotient( length_d, length_d );
    reciprocal( length_d );
    power   ( length_d, 2 );
    root    ( length_d, 2 );
}

/*
 * end of file
 */
