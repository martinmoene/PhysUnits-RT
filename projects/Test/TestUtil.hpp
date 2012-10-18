/*
 * TestUtil.h
 *
 * Created by Martin on 13 October 2012.
 * Copyright 2012 Universiteit Leiden. All rights reserved.
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef TESTUTIL_H_INCLUDED
#define TESTUTIL_H_INCLUDED

#include "phys/units/io.hpp"
#include "phys/units/quantity.hpp"

#include <iomanip>
#include <sstream>
#include <string>

#ifdef PHYS_UNITS_IN_RT_NAMESPACE
using namespace rt::phys::units;
#else
using namespace phys::units;
#endif

inline std::string
s( Rep v )
{
    std::ostringstream os;
    os.setf( std::ios::fixed, std::ios::floatfield );
    os << std::setprecision(6) << v;
    return os.str();
}

inline std::string
s( quantity const & q, name_symbol const use = name_symbol() )
{
    std::ostringstream os;
    os.setf( std::ios::fixed, std::ios::floatfield );
    os << std::setprecision(6) << q.value();

    if ( q.dimension() != dimensionless_d )
    {
        os << " " << to_unit_symbol( q, use );
    }
    return os.str();
}

inline std::string
b( quantity const & q )
{
    return s( q, base_symbols() );
}

#endif // TESTUTIL_H_INCLUDED

/*
 *
 */
