/**
 * \file other_units.hpp
 *
 * \brief   Other units for run-time quantity library.
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
 *
 * This file contains the definitions of units that are *NOT* approved
 * for use with SI, as specified by SP811.  These units should not
 * be used with any new work.  However, they may be needed for
 * handling and converting legacy data.
 */

#ifndef PHYS_UNITS_OTHER_UNITS_HPP_INCLUDED
#define PHYS_UNITS_OTHER_UNITS_HPP_INCLUDED

#include "phys/units/quantity.hpp"

namespace rt { namespace phys { namespace units {

/** \name Other units. */
/// @{
inline quantity abampere()          { return Rep( 1e+1L ) * ampere(); }
inline quantity abcoulomb()         { return Rep( 1e+1L ) * coulomb(); }
inline quantity abfarad()           { return Rep( 1e+9L ) * farad(); }
inline quantity abhenry()           { return Rep( 1e-9L ) * henry(); }
inline quantity abmho()             { return Rep( 1e+9L ) * siemens(); }
inline quantity abohm()             { return Rep( 1e-9L ) * ohm(); }
inline quantity abvolt()            { return Rep( 1e-8L ) * volt(); }
inline quantity acre()              { return Rep( 4.046873e+3L ) * square( meter() ); }
inline quantity acre_foot()         { return Rep( 1.233489e+3L ) * cube( meter() ); }
inline quantity astronomical_unit() { return Rep( 1.495979e+11L ) * meter(); }
inline quantity atmosphere_std()    { return Rep( 1.01325e+5L ) * pascal(); }
inline quantity atmosphere_tech()   { return Rep( 9.80665e+4L ) * pascal(); }

inline quantity barrel()            { return Rep( 1.589873e-1L ) * cube( meter() ); }
inline quantity biot()              { return Rep( 1e+1L ) * ampere(); }
inline quantity btu()               { return Rep( 1.05587e+3L ) * joule(); }
inline quantity btu_it()            { return Rep( 1.055056e+3L ) * joule(); }
inline quantity btu_th()            { return Rep( 1.054350e+3L ) * joule(); }
inline quantity btu_39F()           { return Rep( 1.05967e+3L ) * joule(); }
inline quantity btu_59F()           { return Rep( 1.05480e+3L ) * joule(); }
inline quantity btu_60F()           { return Rep( 1.05468e+3L ) * joule(); }
inline quantity bushel()            { return Rep( 3.523907e-2L ) * cube( meter() ); }

inline quantity calorie()           { return Rep( 4.19002L ) * joule(); }
inline quantity calorie_it()        { return Rep( 4.1868L ) * joule(); }
inline quantity calorie_th()        { return Rep( 4.184L ) * joule(); }
inline quantity calorie_15C()       { return Rep( 4.18580L ) * joule(); }
inline quantity calorie_20C()       { return Rep( 4.18190L ) * joule(); }
inline quantity carat_metric()      { return Rep( 2e-4L ) * kilogram(); }
inline quantity chain()             { return Rep( 2.011684e+1L ) * meter(); }
inline quantity clo()               { return Rep( 1.55e-1L ) * square( meter() ) * kelvin() / watt(); }
inline quantity cm_mercury()        { return Rep( 1.333224e+3L ) * pascal(); }
inline quantity cord()              { return Rep( 3.624556L ) * cube( meter() ); }
inline quantity cup()               { return Rep( 2.365882e-4L ) * cube( meter() ); }

inline quantity darcy()             { return Rep( 9.869233e-13L ) * square( meter() ); }
inline quantity day_sidereal()      { return Rep( 8.616409e+4L ) * second(); }
inline quantity debye()             { return Rep( 3.335641e-30L ) * coulomb() * meter(); }
inline quantity degree_fahrenheit() {return Rep( 5.555556e-1L ) * kelvin(); }
inline quantity degree_rankine()    { return Rep( 5.555556e-1L ) * kelvin(); }
inline quantity denier()            { return Rep( 1.111111e-7L ) * kilogram() / meter(); }
inline quantity dyne()              { return Rep( 1e-5L ) * newton(); }

inline quantity erg()               { return Rep( 1e-7L ) * joule(); }

inline quantity faraday()           { return Rep( 9.648531e+4L ) * coulomb(); }
inline quantity fathom()            { return Rep( 1.828804L ) * meter(); }
inline quantity fermi()             { return Rep( 1e-15L ) * meter(); }
inline quantity foot()              { return Rep( 3.048e-1L ) * meter(); }
inline quantity foot_pound_force()  { return Rep( 1.355818L ) * joule(); }
inline quantity foot_poundal()      { return Rep( 4.214011e-2L ) * joule(); }
inline quantity foot_us_survey()    { return Rep( 3.048006e-1L ) * meter(); }
inline quantity footcandle()        { return Rep( 1.076391e+1L ) * lux(); }
inline quantity footlambert()       { return Rep( 3.426259L ) * candela() / square( meter() ); }
inline quantity fortnight()         { return Rep( 14 ) * day(); } // from OED
inline quantity franklin()          { return Rep( 3.335641e-10L ) * coulomb(); }
inline quantity furlong()           { return Rep( 2.01168e+2L ) * meter(); } // from OED

inline quantity gallon_imperial()   { return Rep( 4.54609e-3L ) * cube( meter() ); }
inline quantity gallon_us()         { return Rep( 3.785412e-3L ) * cube( meter() ); }
inline quantity gamma()             { return Rep( 1e-9L ) * tesla(); }
inline quantity gamma_mass()        { return Rep( 1e-9L ) * kilogram(); }
inline quantity gauss()             { return Rep( 1e-4L ) * tesla(); }
inline quantity gilbert()           { return Rep( 7.957747e-1L ) * ampere(); }
inline quantity gill_imperial()     { return Rep( 1.420653e-4L ) * cube( meter() ); }
inline quantity gill_us()           { return Rep( 1.182941e-4L ) * cube( meter() ); }
inline Rep      gon()               { return Rep( 9e-1L ) * degree_angle(); }
inline quantity grain()             { return Rep( 6.479891e-5L ) * kilogram(); }

inline quantity horsepower()          { return Rep( 7.456999e+2L ) * watt(); }
inline quantity horsepower_boiler()   { return Rep( 9.80950e+3L ) * watt(); }
inline quantity horsepower_electric() {return Rep( 7.46e+2L ) * watt(); }
inline quantity horsepower_metric()   { return Rep( 7.354988e+2L ) * watt(); }
inline quantity horsepower_uk()       { return Rep( 7.4570e+2L ) * watt(); }
inline quantity horsepower_water()    { return Rep( 7.46043e+2L ) * watt(); }
inline quantity hour_sidereal()       { return Rep( 3.590170e+3L ) * second(); }
inline quantity hundredweight_long()  { return Rep( 5.080235e+1L ) * kilogram(); }
inline quantity hundredweight_short() { return Rep( 4.535924e+1L ) * kilogram(); }

inline quantity inch()              { return Rep( 2.54e-2L ) * meter(); }
inline quantity inches_mercury()    { return Rep( 3.386389e+3L ) * pascal(); }

inline quantity kayser()            { return Rep( 1e+2 ) / meter(); }
inline quantity kilogram_force()    { return Rep( 9.80665 ) * newton(); }
inline quantity kilopond()          { return Rep( 9.80665 ) * newton(); }
inline quantity kip()               { return Rep( 4.448222e+3L ) * newton(); }

inline quantity lambda_volume()     { return Rep( 1e-9L ) * cube( meter() ); }
inline quantity lambert()           { return Rep( 3.183099e+3L ) * candela() / square( meter() ); }
inline quantity langley()           { return Rep( 4.184e+4L ) * joule() / square( meter() ); }
inline quantity light_year()        { return Rep( 9.46073e+15L ) * meter(); }

inline quantity maxwell()           { return Rep( 1e-8L ) * weber(); }
inline quantity mho()               { return siemens(); }
inline quantity micron()            { return micro() * meter(); }
inline quantity mil()               { return Rep( 2.54e-5L ) * meter(); }
inline Rep      mil_angle()         { return Rep( 5.625e-2L ) * degree_angle(); }
inline quantity mil_circular()      { return Rep( 5.067075e-10L ) * square( meter() ); }
inline quantity mile()              { return Rep( 1.609344e+3L ) * meter(); }
inline quantity mile_us_survey()    { return Rep( 1.609347e+3L ) * meter(); }
inline quantity minute_sidereal()   { return Rep( 5.983617e+1L ) * second(); }

inline quantity oersted()           { return Rep( 7.957747e+1L ) * ampere() / meter(); }
inline quantity ounce_avdp()        { return Rep( 2.834952e-2L ) * kilogram(); }
inline quantity ounce_fluid_imperial(){return Rep( 2.841306e-5L ) * cube( meter() ); }
inline quantity ounce_fluid_us()    { return Rep( 2.957353e-5L ) * cube( meter() ); }
inline quantity ounce_force()       { return Rep( 2.780139e-1L ) * newton(); }
inline quantity ounce_troy()        { return Rep( 3.110348e-2L ) * kilogram(); }

inline quantity parsec()            { return Rep( 3.085678e+16L ) * meter(); }
inline quantity peck()              { return Rep( 8.809768e-3L ) * cube( meter() ); }
inline quantity pennyweight()       { return Rep( 1.555174e-3L ) * kilogram(); }
inline quantity perm_0C()           { return Rep( 5.72135e-11L ) * kilogram() / pascal() / second() / square( meter() ); }
inline quantity perm_23C()          { return Rep( 5.74525e-11L ) * kilogram() / pascal() / second() / square( meter() ); }
inline quantity phot()              { return Rep( 1e+4L ) * lux(); }
inline quantity pica_computer()     { return Rep( 4.233333e-3L ) * meter(); }
inline quantity pica_printers()     { return Rep( 4.217518e-3L ) * meter(); }
inline quantity pint_dry()          { return Rep( 5.506105e-4L ) * cube( meter() ); }
inline quantity pint_liquid()       { return Rep( 4.731765e-4L ) * cube( meter() ); }
inline quantity point_computer()    { return Rep( 3.527778e-4L ) * meter(); }
inline quantity point_printers()    { return Rep( 3.514598e-4L ) * meter(); }
inline quantity poise()             { return Rep( 1e-1L ) * pascal() * second(); }
inline quantity pound_avdp()        { return Rep( 4.5359237e-1L ) * kilogram(); }
inline quantity pound_force()       { return Rep( 4.448222L ) * newton(); }
inline quantity pound_troy()        { return Rep( 3.732417e-1L ) * kilogram(); }
inline quantity poundal()           { return Rep( 1.382550e-1L ) * newton(); }
inline quantity psi()               { return Rep( 6.894757e+3L ) * pascal(); }

inline quantity quad()              { return Rep( 1e+15L ) * btu_it(); }
inline quantity quart_dry()         { return Rep( 1.101221e-3L ) * cube( meter() ); }
inline quantity quart_liquid()      { return Rep( 9.463529e-4L ) * cube( meter() ); }

inline Rep      revolution()        { return Rep( 2 ) * pi(); }
inline quantity rhe()               { return Rep( 1e+1L ) / pascal() / second(); }
inline quantity rod()               { return Rep( 5.029210L ) * meter(); }
inline quantity rpm()               { return Rep( 1.047198e-1L ) / second(); }

inline quantity second_sidereal()   { return Rep( 9.972696e-1L ) * second(); }
inline quantity shake()             { return Rep( 1e-8L ) * second(); }
inline quantity slug()              { return Rep( 1.459390e+1L ) * kilogram(); }
inline quantity statampere()        { return Rep( 3.335641e-10L ) * ampere(); }
inline quantity statcoulomb()       { return Rep( 3.335641e-10L ) * coulomb(); }
inline quantity statfarad()         { return Rep( 1.112650e-12L ) * farad(); }
inline quantity stathenry()         { return Rep( 8.987552e+11L ) * henry(); }
inline quantity statmho()           { return Rep( 1.112650e-12L ) * siemens(); }
inline quantity statohm()           { return Rep( 8.987552e+11L ) * ohm(); }
inline quantity statvolt()          { return Rep( 2.997925e+2L ) * volt(); }
inline quantity stere()             { return cube( meter() ); }
inline quantity stilb()             { return Rep( 1e+4L ) * candela() / square( meter() ); }
inline quantity stokes()            { return Rep( 1e-4L ) * square( meter() ) / second(); }

inline quantity tablespoon()        { return Rep( 1.478676e-5L ) * cube( meter() ); }
inline quantity teaspoon()          { return Rep( 4.928922e-6L ) * cube( meter() ); }
inline quantity tex()               { return Rep( 1e-6L ) * kilogram() / meter(); }
inline quantity therm_ec()          { return Rep( 1.05506e+8L ) * joule(); }
inline quantity therm_us()          { return Rep( 1.054804e+8L ) * joule(); }
inline quantity ton_assay()         { return Rep( 2.916667e-2L ) * kilogram(); }
inline quantity ton_force()         { return Rep( 8.896443e+3L ) * newton(); }
inline quantity ton_long()          { return Rep( 1.016047e+3L ) * kilogram(); }
inline quantity ton_refrigeration() { return Rep( 3.516853e+3L ) * watt(); }
inline quantity ton_register()      { return Rep( 2.831685L ) * cube( meter() ); }
inline quantity ton_short()         { return Rep( 9.071847e+2L ) * kilogram(); }
inline quantity ton_tnt()           { return Rep( 4.184e+9L ) * joule(); }
inline quantity torr()              { return Rep( 1.333224e+2L ) * pascal(); }

inline quantity unit_pole()         { return Rep( 1.256637e-7L ) * weber(); }

inline quantity week()              { return Rep( 604800L ) * second(); } // 7 days

inline quantity x_unit()            { return Rep( 1.002e-13L ) * meter(); }

inline quantity yard()              { return Rep( 9.144e-1L ) * meter(); }
inline quantity year_sidereal()     { return Rep( 3.155815e+7L ) * second(); }
inline quantity year_std()          { return Rep( 3.1536e+7L ) * second(); } // 365 days
inline quantity year_tropical()     { return Rep( 3.155693e+7L ) * second(); }
/// @}

}}} // namespace rt { namespace phys { namespace units {

#endif // PHYS_UNITS_OTHER_UNITS_HPP_INCLUDED

/*
 * end of file
 */
