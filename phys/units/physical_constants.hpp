/**
 * \file physical_constants.hpp
 *
 * \brief   Physical constants for run-time quantity library.
 * \author  Michael S. Kenniston, adapted for run-time use by Martin Moene
 * \date    July 2001, 13 July 2012
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

#ifndef PHYS_UNITS_PHYSICAL_CONSTANTS_HPP_INCLUDED
#define PHYS_UNITS_PHYSICAL_CONSTANTS_HPP_INCLUDED

#include "phys/units/quantity.hpp"

namespace rt { namespace phys { namespace units {

/** \name Physical constants */
/// @{

// acceleration of free-fall, standard
inline quantity g_sub_n() { return Rep( 9.80665L ) * meter() / square( second() ); }

// Avogadro constant
inline quantity N_sub_A() { return mole() / mole() * // to help msvc
                                             Rep( 6.02214199e+23L ) / mole(); }
// electronvolt
inline quantity eV() { return Rep( 1.60217733e-19L ) * joule(); }

// elementary charge
inline quantity e() { return Rep( 1.602176462e-19L ) * coulomb(); }

// Planck constant
inline quantity h() { return Rep( 6.62606876e-34L ) * joule() * second(); }

// speed of light in a vacuum
inline quantity c() { return Rep( 299792458L ) * meter() / second(); }

// unified atomic mass unit
inline quantity u() { return Rep( 1.6605402e-27L ) * kilogram(); }

// etc.
/// @}

}}} // namespace rt { namespace phys { namespace units {

#endif // PHYS_UNITS_PHYSICAL_CONSTANTS_HPP_INCLUDED

/*
 * end of file
 */
