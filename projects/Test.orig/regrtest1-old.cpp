//
//  regrtest1.cpp - regression test for Quantity library
//

//  Copyright (c) 2001 by Michael S. Kenniston.  The most recent
//  version will be available at www.xnet.com/~msk/quantity.  Permission is granted
//  to use this code without restriction so long as this copyright
//  notice appears in all source files.

//  This code is provided as-is, with no warrantee of correctness.

//  This program tests all the features of the Quantity Library.
//  It sends a report of each test, and a summary of all test results,
//  to stdout.

#define CUJ_QUANTITY_REP_TYPE long double

#include "cuj/quantity/quantity.hpp"
#include "cuj/quantity/quantity_io.hpp"
#include "cuj/quantity/other_units.hpp"
#include "cuj/quantity/physical_constants.hpp"

#include "user_example.hpp"

#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iomanip>
#ifndef BOOST_NO_STRINGSTREAM
    #include <sstream>
#else
    #include <strstream>
    typedef ostrstream ostringstream;
#endif

// We pull in the whole std namespace to make sure there are no conflicts,
// since users are very likely to do the same thing.

using namespace std;

// It may be bad form to pull in an entire namespace, but in this case
// there is no reason not to, since this is a regression test which
// deliberately makes a special point of touching every single identifier
// in the library.

using namespace cuj::quantity;

// === Reporting Routines ===

int pass_count = 0;
int fail_count = 0;

void report_impl( int line_number, const char * name, std::string actual, std::string expected )
{
    if( actual == expected )
    {
        cout << "  pass line " << setw( 4 ) << line_number << " (" << name
            << "): " << actual << "\n";
        ++pass_count;
    }
    else
    {
        cout << "* FAIL line " << setw( 4 ) << line_number << " (" << name
            << ")\n";
        cout << "                 expected: \"" << expected << "\"\n";
        cout << "                 actual:   \"" << actual   << "\"\n";
        ++fail_count;
    }
}

// REPORT is defined as a macro so it can include the line number automatically.
// The block that allocates the ostringstream is included in the macro, instead
// of putting it in a templated version of report_impl, in order to avoid blowing
// compiler heap limits.

#define REPORT( name, expr, expected ) \
{ \
    ostringstream os_; \
    os_.setf( ios::fixed, ios::floatfield ); \
    os_ << setprecision( 6 ) << ( expr ); \
    report_impl( __LINE__, name, os_.str(), expected ); \
}

void report_summary()
{
    cout << "\n";
    cout << "Total passes:   " << setw( 4 ) << pass_count << "\n";
    cout << "Total failures: " << setw( 4 ) << fail_count << "\n\n";
}

// === Testing Routines ===

void check_base_units()
{
    REPORT( "meter", meter(), "1.000000 m" );
    REPORT( "metre", metre(), "1.000000 m" );
    REPORT( "kilogram", kilogram(), "1.000000 kg" );
    REPORT( "second", second(), "1.000000 s" );
    REPORT( "ampere", ampere(), "1.000000 A" );
    REPORT( "kelvin", kelvin(), "1.000000 K" );
    REPORT( "mole", mole(), "1.000000 mol" );
    REPORT( "candela", candela(), "1.000000 cd" );
}

void check_types()
{
    REPORT( "absorbed_dose_d", quantity< absorbed_dose_d >::zero(), "0.000000 m+2 s-2" );
    REPORT( "absorbed_dose_rate_d", quantity< absorbed_dose_rate_d >::zero(), "0.000000 m+2 s-3" );
    REPORT( "acceleration_d", quantity< acceleration_d >::zero(), "0.000000 m s-2" );
    REPORT( "activity_of_a_nuclide_d", quantity< activity_of_a_nuclide_d >::zero(), "0.000000 s-1" );
    REPORT( "angular_velocity_d", quantity< angular_velocity_d >::zero(), "0.000000 s-1" );
    REPORT( "angular_acceleration_d", quantity< angular_acceleration_d >::zero(), "0.000000 s-2" );
    REPORT( "area_d", quantity< area_d >::zero(), "0.000000 m+2" );
    REPORT( "capacitance_d", quantity< capacitance_d >::zero(), "0.000000 m-2 kg-1 s+4 A+2" );
    REPORT( "concentration_d", quantity< concentration_d >::zero(), "0.000000 m-3 mol" );
    REPORT( "current_density_d", quantity< current_density_d >::zero(), "0.000000 m-2 A" );
    REPORT( "dose_equivalent_d", quantity< dose_equivalent_d >::zero(), "0.000000 m+2 s-2" );
    REPORT( "dynamic_viscosity_d", quantity< dynamic_viscosity_d >::zero(), "0.000000 m-1 kg s-1" );
    REPORT( "electric_charge_d", quantity< electric_charge_d >::zero(), "0.000000 s A" );
    REPORT( "electric_charge_density_d", quantity< electric_charge_density_d >::zero(), "0.000000 m-3 s A" );
    REPORT( "electric_conductance_d", quantity< electric_conductance_d >::zero(), "0.000000 m-2 kg-1 s+3 A+2" );
    REPORT( "electric_field_strenth_d", quantity< electric_field_strenth_d >::zero(), "0.000000 m kg s-3 A-1" );
    REPORT( "electric_flux_density_d", quantity< electric_flux_density_d >::zero(), "0.000000 m-2 s A" );
    REPORT( "electric_potential_d", quantity< electric_potential_d >::zero(), "0.000000 m+2 kg s-3 A-1" );
    REPORT( "electric_resistance_d", quantity< electric_resistance_d >::zero(), "0.000000 m+2 kg s-3 A-2" );
    REPORT( "energy_d", quantity< energy_d >::zero(), "0.000000 m+2 kg s-2" );
    REPORT( "energy_density_d", quantity< energy_density_d >::zero(), "0.000000 m-1 kg s-2" );
    REPORT( "exposure_d", quantity< exposure_d >::zero(), "0.000000 kg-1 s A" );
    REPORT( "force_d", quantity< force_d >::zero(), "0.000000 m kg s-2" );
    REPORT( "frequency_d", quantity< frequency_d >::zero(), "0.000000 s-1" );
    REPORT( "heat_capacity_d", quantity< heat_capacity_d >::zero(), "0.000000 m+2 kg s-2 K-1" );
    REPORT( "heat_density_d", quantity< heat_density_d >::zero(), "0.000000 kg s-2" );
    REPORT( "heat_density_flow_rate_d", quantity< heat_density_flow_rate_d >::zero(), "0.000000 kg s-3" );
    REPORT( "heat_flow_rate_d", quantity< heat_flow_rate_d >::zero(), "0.000000 m+2 kg s-3" );
    REPORT( "heat_flux_density_d", quantity< heat_flux_density_d >::zero(), "0.000000 kg s-3" );
    REPORT( "heat_transfer_coefficient_d", quantity< heat_transfer_coefficient_d >::zero(), "0.000000 kg s-3 K-1" );
    REPORT( "illuminance_d", quantity< illuminance_d >::zero(), "0.000000 m-2 cd" );
    REPORT( "inductance_d", quantity< inductance_d >::zero(), "0.000000 m+2 kg s-2 A-2" );
    REPORT( "irradiance_d", quantity< irradiance_d >::zero(), "0.000000 kg s-3" );
    REPORT( "kinematic_viscosity_d", quantity< kinematic_viscosity_d >::zero(), "0.000000 m+2 s-1" );
    REPORT( "luminance_d", quantity< luminance_d >::zero(), "0.000000 m-2 cd" );
    REPORT( "luminous_flux_d", quantity< luminous_flux_d >::zero(), "0.000000 cd" );
    REPORT( "magnetic_field_strength_d", quantity< magnetic_field_strength_d >::zero(), "0.000000 m-1 A" );
    REPORT( "magnetic_flux_d", quantity< magnetic_flux_d >::zero(), "0.000000 m+2 kg s-2 A-1" );
    REPORT( "magnetic_flux_density_d", quantity< magnetic_flux_density_d >::zero(), "0.000000 kg s-2 A-1" );
    REPORT( "magnetic_permeability_d", quantity< magnetic_permeability_d >::zero(), "0.000000 m kg s-2 A-2" );
    REPORT( "mass_density_d", quantity< mass_density_d >::zero(), "0.000000 m-3 kg" );
    REPORT( "mass_flow_rate_d", quantity< mass_flow_rate_d >::zero(), "0.000000 kg s-1" );
    REPORT( "molar_energy_d", quantity< molar_energy_d >::zero(), "0.000000 m+2 kg s-2 mol-1" );
    REPORT( "molar_entropy_d", quantity< molar_entropy_d >::zero(), "0.000000 m+2 kg s-2 A-1 mol-1" );
    REPORT( "moment_of_force_d", quantity< moment_of_force_d >::zero(), "0.000000 m+2 kg s-2" );
    REPORT( "permittivity_d", quantity< permittivity_d >::zero(), "0.000000 m-3 kg-1 s+4 A+2" );
    REPORT( "power_d", quantity< power_d >::zero(), "0.000000 m+2 kg s-3" );
    REPORT( "pressure_d", quantity< pressure_d >::zero(), "0.000000 m-1 kg s-2" );
    REPORT( "radiance_d", quantity< radiance_d >::zero(), "0.000000 kg s-3" );
    REPORT( "radiant_intensity_d", quantity< radiant_intensity_d >::zero(), "0.000000 m+2 kg s-3" );
    REPORT( "specific_volume_d", quantity< specific_volume_d >::zero(), "0.000000 m+3 kg-1" );
    REPORT( "speed_d", quantity< speed_d >::zero(), "0.000000 m s-1" );
    REPORT( "specific_energy_d", quantity< specific_energy_d >::zero(), "0.000000 m+2 s-2" );
    REPORT( "specific_heat_capacity_d", quantity< specific_heat_capacity_d >::zero(), "0.000000 m+2 s-2 K-1" );
    REPORT( "specific_volume_d", quantity< specific_volume_d >::zero(), "0.000000 m+3 kg-1" );
    REPORT( "substance_permeability_d", quantity< substance_permeability_d >::zero(), "0.000000 m-1 s" );
    REPORT( "surface_tension_d", quantity< surface_tension_d >::zero(), "0.000000 kg s-2" );
    REPORT( "thermal_conductivity_d", quantity< thermal_conductivity_d >::zero(), "0.000000 m kg s-3 K-1" );
    REPORT( "thermal_diffusivity_d", quantity< thermal_diffusivity_d >::zero(), "0.000000 m+2 s-1" );
    REPORT( "thermal_insulance_d", quantity< thermal_insulance_d >::zero(), "0.000000 kg-1 s+3 K" );
    REPORT( "thermal_resistance_d", quantity< thermal_resistance_d >::zero(), "0.000000 m-2 kg-1 s+3 K" );
    REPORT( "thermal_resistivity_d", quantity< thermal_resistivity_d >::zero(), "0.000000 m-1 kg-1 s+3 K" );
    REPORT( "torque_d", quantity< torque_d >::zero(), "0.000000 m+2 kg s-2" );
    REPORT( "volume_d", quantity< volume_d >::zero(), "0.000000 m+3" );
    REPORT( "volume_flow_rate_d", quantity< volume_flow_rate_d >::zero(), "0.000000 m+3 s-1" );
    REPORT( "wave_number_d", quantity< wave_number_d >::zero(), "0.000000 m-1" );
}

void check_derived_units()
{
    REPORT( "radian", radian(), "1.000000" );
    REPORT( "steradian", steradian(), "1.000000" );
    REPORT( "hertz", hertz(), "1.000000 s-1" );
    REPORT( "newton", newton(), "1.000000 m kg s-2" );
    REPORT( "pascal", pascal(), "1.000000 m-1 kg s-2" );
    REPORT( "joule", joule(), "1.000000 m+2 kg s-2" );
    REPORT( "watt", watt(), "1.000000 m+2 kg s-3" );
    REPORT( "coulomb", coulomb(), "1.000000 s A" );
    REPORT( "volt", volt(), "1.000000 m+2 kg s-3 A-1" );
    REPORT( "farad", farad(), "1.000000 m-2 kg-1 s+4 A+2" );
    REPORT( "ohm", ohm(), "1.000000 m+2 kg s-3 A-2" );
    REPORT( "siemens", siemens(), "1.000000 m-2 kg-1 s+3 A+2" );
    REPORT( "weber", weber(), "1.000000 m+2 kg s-2 A-1" );
    REPORT( "tesla", tesla(), "1.000000 kg s-2 A-1" );
    REPORT( "henry", henry(), "1.000000 m+2 kg s-2 A-2" );
    REPORT( "degree_celsius", degree_celsius(), "1.000000 K" );
    REPORT( "lumen", lumen(), "1.000000 cd" );
    REPORT( "lux", lux(), "1.000000 m-2 cd" );
    REPORT( "becquerel", becquerel(), "1.000000 s-1" );
    REPORT( "gray", gray(), "1.000000 m+2 s-2" );
    REPORT( "sievert", sievert(), "1.000000 m+2 s-2" );
}

void check_prefixes()
{
    REPORT( "yotta", 1e-24 * yotta(), "1.000000" );
    REPORT( "zetta", 1e-21 * zetta(), "1.000000" );
    REPORT( "exa", 1e-18 * exa(), "1.000000" );
    REPORT( "peta", 1e-15 * peta(), "1.000000" );
    REPORT( "tera", 1e-12 * tera(), "1.000000" );
    REPORT( "giga", 1e-9 * giga(), "1.000000" );
    REPORT( "mega", 1e-6 * mega(), "1.000000" );
    REPORT( "kilo", 1e-3 * kilo(), "1.000000" );
    REPORT( "hecto", 1e-2 * hecto(), "1.000000" );
    REPORT( "deka", 1e-1 * deka(), "1.000000" );
    REPORT( "deca", 1e-1 * deca(), "1.000000" );
    REPORT( "deci", 1e1 * deci(), "1.000000" );
    REPORT( "centi", 1e2 * centi(), "1.000000" );
    REPORT( "milli", 1e3 * milli(), "1.000000" );
    REPORT( "micro", 1e6 * micro(), "1.000000" );
    REPORT( "nano", 1e9 * nano(), "1.000000" );
    REPORT( "pico", 1e12 * pico(), "1.000000" );
    REPORT( "femto", 1e15 * femto(), "1.000000" );
    REPORT( "atto", 1e18 * atto(), "1.000000" );
    REPORT( "zepto", 1e21 * zepto(), "1.000000" );
    REPORT( "yocto", 1e24 * yocto(), "1.000000" );
}

void check_approved_units()
{
    REPORT( "angstrom", 1e+10 * angstrom(), "1.000000 m" );
    REPORT( "are", are(), "100.000000 m+2" );
    REPORT( "bar", 1e-5 * bar(), "1.000000 m-1 kg s-2" );
    REPORT( "barn", 1e+28 * barn(), "1.000000 m+2" );
    REPORT( "curie", 1e-10 * curie(), "3.700000 s-1" );
    REPORT( "day", day(), "86400.000000 s" );
    REPORT( "degree_angle", 1e+2 * degree_angle(), "1.745329" );
    REPORT( "gal", 1e+2 * gal(), "1.000000 m s-2" );
    REPORT( "hectare", 1e-4 * hectare(), "1.000000 m+2" );
    REPORT( "hour", hour(), "3600.000000 s" );
    REPORT( "knot", 1e+1 * knot(), "5.144444 m s-1" );
    REPORT( "liter", 1e+3 * liter(), "1.000000 m+3" );
    REPORT( "litre", 1e+3 * litre(), "1.000000 m+3" );
    REPORT( "minute", minute(), "60.000000 s" );
    REPORT( "minute_angle", 1e+4 * minute_angle(), "2.908882" );
    REPORT( "mile_nautical", 1e-3 * mile_nautical(), "1.852000 m" );
    REPORT( "rad", 1e+2 * rad(), "1.000000 m+2 s-2" );
    REPORT( "rem", 1e+2 * rem(), "1.000000 m+2 s-2" );
    REPORT( "roentgen", 1e+4 * roentgen(), "2.580000 kg-1 s A" );
    REPORT( "second_angle", 1e+6 * second_angle(), "4.848137" );
    REPORT( "ton_metric", ton_metric(), "1000.000000 kg" );
    REPORT( "tonne", tonne(), "1000.000000 kg" );
}

void check_other_units()
{
    REPORT( "abampere", abampere(), "10.000000 A" );
    REPORT( "abcoulomb", abcoulomb(), "10.000000 s A" );
    REPORT( "abfarad", 1e-9 * abfarad(), "1.000000 m-2 kg-1 s+4 A+2" );
    REPORT( "abhenry", 1e+9 * abhenry(), "1.000000 m+2 kg s-2 A-2" );
    REPORT( "abmho", 1e-9 * abmho(), "1.000000 m-2 kg-1 s+3 A+2" );
    REPORT( "abohm", 1e+9 * abohm(), "1.000000 m+2 kg s-3 A-2" );
    REPORT( "abvolt", 1e+8 * abvolt(), "1.000000 m+2 kg s-3 A-1" );
    REPORT( "acre", 1e-3 * acre(), "4.046873 m+2" );
    REPORT( "acre_foot", 1e-3 * acre_foot(), "1.233489 m+3" );
    REPORT( "astronomical_unit", 1e-11 * astronomical_unit(), "1.495979 m" );
    REPORT( "atmosphere_std", 1e-5 * atmosphere_std(), "1.013250 m-1 kg s-2" );
    REPORT( "atmosphere_tech", 1e-4 * atmosphere_tech(), "9.806650 m-1 kg s-2" );
    REPORT( "barrel", 1e+1 * barrel(), "1.589873 m+3" );
    REPORT( "biot", 1e-1 * biot(), "1.000000 A" );
    REPORT( "btu", 1e-3 * btu(), "1.055870 m+2 kg s-2" );
    REPORT( "btu_it", 1e-3 * btu_it(), "1.055056 m+2 kg s-2" );
    REPORT( "btu_th", 1e-3 * btu_th(), "1.054350 m+2 kg s-2" );
    REPORT( "btu_39F", 1e-3 * btu_39F(), "1.059670 m+2 kg s-2" );
    REPORT( "btu_59F", 1e-3 * btu_59F(), "1.054800 m+2 kg s-2" );
    REPORT( "btu_60F", 1e-3 * btu_60F(), "1.054680 m+2 kg s-2" );
    REPORT( "bushel", 1e+2 * bushel(), "3.523907 m+3" );
    REPORT( "calorie", calorie(), "4.190020 m+2 kg s-2" );
    REPORT( "calorie_it", calorie_it(), "4.186800 m+2 kg s-2" );
    REPORT( "calorie_th", calorie_th(), "4.184000 m+2 kg s-2" );
    REPORT( "calorie_15C", calorie_15C(), "4.185800 m+2 kg s-2" );
    REPORT( "calorie_20C", calorie_20C(), "4.181900 m+2 kg s-2" );
    REPORT( "carat_metric", 1e+4 * carat_metric(), "2.000000 kg" );
    REPORT( "chain", 1e-1 * chain(), "2.011684 m" );
    REPORT( "clo", 1e+1 * clo(), "1.550000 kg-1 s+3 K" );
    REPORT( "cm_mercury", 1e-3 * cm_mercury(), "1.333224 m-1 kg s-2" );
    REPORT( "cord", cord(), "3.624556 m+3" );
    REPORT( "cup", 1e+4 * cup(), "2.365882 m+3" );
    REPORT( "darcy", 1e+13 * darcy(), "9.869233 m+2" );
    REPORT( "day_sidereal", 1e-4 * day_sidereal(), "8.616409 s" );
    REPORT( "debye", 1e+30 * debye(), "3.335641 m s A" );
    REPORT( "degree_fahrenheit", 1e+1 * degree_fahrenheit(), "5.555556 K" );
    REPORT( "degree_rankine", 1e+1 * degree_rankine(), "5.555556 K" );
    REPORT( "denier", 1e+7 * denier(), "1.111111 m-1 kg" );
    REPORT( "dyne", 1e+5 * dyne(), "1.000000 m kg s-2" );
    REPORT( "erg", 1e+7 * erg(), "1.000000 m+2 kg s-2" );
    REPORT( "faraday", 1e-4 * faraday(), "9.648531 s A" );
    REPORT( "fathom", fathom(), "1.828804 m" );
    REPORT( "fermi", 1e+15 * fermi(), "1.000000 m" );
    REPORT( "foot", 1e+1 * foot(), "3.048000 m" );
    REPORT( "foot_pound_force", foot_pound_force(), "1.355818 m+2 kg s-2" );
    REPORT( "foot_poundal", 1e+2 * foot_poundal(), "4.214011 m+2 kg s-2" );
    REPORT( "foot_us_survey", 1e+1 * foot_us_survey(), "3.048006 m" );
    REPORT( "footcandle", 1e-1 * footcandle(), "1.076391 m-2 cd" );
    REPORT( "footlambert", footlambert(), "3.426259 m-2 cd" );
    REPORT( "fortnight", 1e-6 * fortnight(), "1.209600 s" );
    REPORT( "franklin", 1e+10 * franklin(), "3.335641 s A" );
    REPORT( "furlong", 1e-2 * furlong(), "2.011680 m" );
    REPORT( "gallon_imperial", 1e+3 * gallon_imperial(), "4.546090 m+3" );
    REPORT( "gallon_us", 1e+3 * gallon_us(), "3.785412 m+3" );
    REPORT( "gamma", 1e+9 * gamma(), "1.000000 kg s-2 A-1" );
    REPORT( "gamma_mass", 1e+9 * gamma_mass(), "1.000000 kg" );
    REPORT( "gauss", 1e+4 * gauss(), "1.000000 kg s-2 A-1" );
    REPORT( "gilbert", 1e+1 * gilbert(), "7.957747 A" );
    REPORT( "gill_imperial", 1e+4 * gill_imperial(), "1.420653 m+3" );
    REPORT( "gill_us", 1e+4 * gill_us(), "1.182941 m+3" );
    REPORT( "gon", 1e+2 * gon(), "1.570796" );
    REPORT( "grain", 1e+5 * grain(), "6.479891 kg" );
    REPORT( "horsepower", 1e-2 * horsepower(), "7.456999 m+2 kg s-3" );
    REPORT( "horsepower_boiler", 1e-3 * horsepower_boiler(), "9.809500 m+2 kg s-3" );
    REPORT( "horespower_electric", 1e-2 * horsepower_electric(), "7.460000 m+2 kg s-3" );
    REPORT( "horsepower_metric", 1e-2 * horsepower_metric(), "7.354988 m+2 kg s-3" );
    REPORT( "horsepower_uk", 1e-2 * horsepower_uk(), "7.457000 m+2 kg s-3" );
    REPORT( "horsepower_water", 1e-2 * horsepower_water(), "7.460430 m+2 kg s-3" );
    REPORT( "hour_sidereal", 1e-3 * hour_sidereal(), "3.590170 s" );
    REPORT( "hundredweight_long", 1e-1 * hundredweight_long(), "5.080235 kg" );
    REPORT( "hundredweight_short", 1e-1 * hundredweight_short(), "4.535924 kg" );
    REPORT( "inch", 1e+2 * inch(), "2.540000 m" );
    REPORT( "inches_mercury", 1e-3 * inches_mercury(), "3.386389 m-1 kg s-2" );
    REPORT( "kayser", 1e-2 * kayser(), "1.000000 m-1" );
    REPORT( "kilogram_force", kilogram_force(), "9.806650 m kg s-2" );
    REPORT( "kilopond", kilopond(), "9.806650 m kg s-2" );
    REPORT( "kip", 1e-3 * kip(), "4.448222 m kg s-2" );
    REPORT( "lambda_volume", 1e+9 * lambda_volume(), "1.000000 m+3" );
    REPORT( "lambert", 1e-3 * lambert(), "3.183099 m-2 cd" );
    REPORT( "langley", 1e-4 * langley(), "4.184000 kg s-2" );
    REPORT( "light_year", 1e-15 * light_year(), "9.460730 m" );
    REPORT( "maxwell", 1e+8 * maxwell(), "1.000000 m+2 kg s-2 A-1" );
    REPORT( "mho", mho(), "1.000000 m-2 kg-1 s+3 A+2" );
    REPORT( "micron", 1e+6 * micron(), "1.000000 m" );
    REPORT( "mil", 1e+5 * mil(), "2.540000 m" );
    REPORT( "mil_angle", 1e+4 * mil_angle(), "9.817477" );
    REPORT( "mil_circular", 1e+10 * mil_circular(), "5.067075 m+2" );
    REPORT( "mile", 1e-3 * mile(), "1.609344 m" );
    REPORT( "mile_us_survey", 1e-3 * mile_us_survey(), "1.609347 m" );
    REPORT( "minute_sidereal", 1e-1 * minute_sidereal(), "5.983617 s" );
    REPORT( "oersted", 1e-1 * oersted(), "7.957747 m-1 A" );
    REPORT( "ounce_avdp", 1e+2 * ounce_avdp(), "2.834952 kg" );
    REPORT( "ounce_fluid_imperial", 1e+5 * ounce_fluid_imperial(), "2.841306 m+3" );
    REPORT( "ounce_fluid_us", 1e+5 * ounce_fluid_us(), "2.957353 m+3" );
    REPORT( "ounce_force", 1e+1 * ounce_force(), "2.780139 m kg s-2" );
    REPORT( "ounce_troy", 1e+2 * ounce_troy(), "3.110348 kg" );
    REPORT( "parsec", 1e-16 * parsec(), "3.085678 m" );
    REPORT( "peck", 1e+3 * peck(), "8.809768 m+3" );
    REPORT( "pennyweight", 1e+3 * pennyweight(), "1.555174 kg" );
    REPORT( "perm_0C", 1e+11 * perm_0C(), "5.721350 m-1 s" );
    REPORT( "perm_23C", 1e+11 * perm_23C(), "5.745250 m-1 s" );
    REPORT( "phot", 1e-4 * phot(), "1.000000 m-2 cd" );
    REPORT( "pica_computer", 1e+3 * pica_computer(), "4.233333 m" );
    REPORT( "pica_printers", 1e+3 * pica_printers(), "4.217518 m" );
    REPORT( "pint_dry", 1e+4 * pint_dry(), "5.506105 m+3" );
    REPORT( "pint_liquid", 1e+4 * pint_liquid(), "4.731765 m+3" );
    REPORT( "point_computer", 1e+4 * point_computer(), "3.527778 m" );
    REPORT( "point_printers", 1e+4 * point_printers(), "3.514598 m" );
    REPORT( "poise", 1e+1 * poise(), "1.000000 m-1 kg s-1" );
    REPORT( "pound_avdp", 1e+1 * pound_avdp(), "4.535924 kg" );
    REPORT( "pound_force", pound_force(), "4.448222 m kg s-2" );
    REPORT( "pound_troy", 1e+1 * pound_troy(), "3.732417 kg" );
    REPORT( "poundal", 1e+1 * poundal(), "1.382550 m kg s-2" );
    REPORT( "psi", 1e-3 * psi(), "6.894757 m-1 kg s-2" );
    REPORT( "quad", 1e-18 * quad(), "1.055056 m+2 kg s-2" );
    REPORT( "quart_dry", 1e+3 * quart_dry(), "1.101221 m+3" );
    REPORT( "quart_liquid", 1e+4 * quart_liquid(), "9.463529 m+3" );
    REPORT( "revolution", revolution(), "6.283185" );
    REPORT( "rhe", 1e-1 * rhe(), "1.000000 m kg-1 s" );
    REPORT( "rod", rod(), "5.029210 m" );
    REPORT( "rpm", 1e+1 * rpm(), "1.047198 s-1" );
    REPORT( "second_sidereal", 1e+1 * second_sidereal(), "9.972696 s" );
    REPORT( "shake", 1e+8 * shake(), "1.000000 s" );
    REPORT( "slug", 1e-1 * slug(), "1.459390 kg" );
    REPORT( "statampere", 1e+10 * statampere(), "3.335641 A" );
    REPORT( "statcoulomb", 1e+10 * statcoulomb(), "3.335641 s A" );
    REPORT( "statfarad", 1e+12 * statfarad(), "1.112650 m-2 kg-1 s+4 A+2" );
    REPORT( "stathenry", 1e-11 * stathenry(), "8.987552 m+2 kg s-2 A-2" );
    REPORT( "statmho", 1e+12 * statmho(), "1.112650 m-2 kg-1 s+3 A+2" );
    REPORT( "statohm", 1e-11 * statohm(), "8.987552 m+2 kg s-3 A-2" );
    REPORT( "statvolt", 1e-2 * statvolt(), "2.997925 m+2 kg s-3 A-1" );
    REPORT( "stere", stere(), "1.000000 m+3" );
    REPORT( "stilb", 1e-4 * stilb(), "1.000000 m-2 cd" );
    REPORT( "stokes", 1e+4 * stokes(), "1.000000 m+2 s-1" );
    REPORT( "tablespoon", 1e+5 * tablespoon(), "1.478676 m+3" );
    REPORT( "teaspoon", 1e+6 * teaspoon(), "4.928922 m+3" );
    REPORT( "tex", 1e+6 * tex(), "1.000000 m-1 kg" );
    REPORT( "therm_ec", 1e-8 * therm_ec(), "1.055060 m+2 kg s-2" );
    REPORT( "therm_us", 1e-8 * therm_us(), "1.054804 m+2 kg s-2" );
    REPORT( "ton_assay", 1e+2 * ton_assay(), "2.916667 kg" );
    REPORT( "ton_force", 1e-3 * ton_force(), "8.896443 m kg s-2" );
    REPORT( "ton_long", 1e-3 * ton_long(), "1.016047 kg" );
    REPORT( "ton_refrigeration", 1e-3 * ton_refrigeration(), "3.516853 m+2 kg s-3" );
    REPORT( "ton_register", ton_register(), "2.831685 m+3" );
    REPORT( "ton_short", 1e-2 * ton_short(), "9.071847 kg" );
    REPORT( "ton_tnt", 1e-9 * ton_tnt(), "4.184000 m+2 kg s-2" );
    REPORT( "torr", 1e-2 * torr(), "1.333224 m-1 kg s-2" );
    REPORT( "unit_pole", 1e+7 * unit_pole(), "1.256637 m+2 kg s-2 A-1" );
    REPORT( "week", 1e-5 * week(), "6.048000 s" );
    REPORT( "x_unit", 1e+13 * x_unit(), "1.002000 m" );
    REPORT( "yard", 1e+1 * yard(), "9.144000 m" );
    REPORT( "year_sideral", 1e-7 * year_sidereal(), "3.155815 s" );
    REPORT( "year_std", 1e-7 * year_std(), "3.153600 s" );
    REPORT( "year_tropical", 1e-7 * year_tropical(), "3.155693 s" );
}

void check_comparisons()
{
    quantity< power_d > neg2( -2 * watt() );
    quantity< power_d > neg1( -1 * watt() );
    quantity< power_d > z( 0 * watt() );
    quantity< power_d > pos1( 1 * watt() );
    quantity< power_d > pos2( 2 * watt() );

    REPORT( "-1 == -1", neg1 == neg1, "1" );
    REPORT( "-1 != -1", neg1 != neg1, "0" );
    REPORT( "-1 <= -1", neg1 <= neg1, "1" );
    REPORT( "-1 >= -1", neg1 >= neg1, "1" );
    REPORT( "-1 < -1", neg1 < neg1, "0" );
    REPORT( "-1 > -1", neg1 > neg1, "0" );

    REPORT( "0 == 0", z == z, "1" );
    REPORT( "0 != 0", z != z, "0" );
    REPORT( "0 <= 0", z <= z, "1" );
    REPORT( "0 >= 0", z >= z, "1" );
    REPORT( "0 < 0", z < z, "0" );
    REPORT( "0 > 0", z > z, "0" );

    REPORT( "1 == 1", pos1 == pos1, "1" );
    REPORT( "1 != 1", pos1 != pos1, "0" );
    REPORT( "1 <= 1", pos1 <= pos1, "1" );
    REPORT( "1 >= 1", pos1 >= pos1, "1" );
    REPORT( "1 < 1", pos1 < pos1, "0" );
    REPORT( "1 > 1", pos1 > pos1, "0" );

    REPORT( "0 == -1", z == neg1, "0" );
    REPORT( "0 != -1", z != neg1, "1" );
    REPORT( "0 <= -1", z <= neg1, "0" );
    REPORT( "0 >= -1", z >= neg1, "1" );
    REPORT( "0 < -1", z < neg1, "0" );
    REPORT( "0 > -1", z > neg1, "1" );

    REPORT( "0 == 1", z == pos1, "0" );
    REPORT( "0 != 1", z != pos1, "1" );
    REPORT( "0 <= 1", z <= pos1, "1" );
    REPORT( "0 >= 1", z >= pos1, "0" );
    REPORT( "0 < 1", z < pos1, "1" );
    REPORT( "0 > 1", z > pos1, "0" );

    REPORT( "-1 == 0", neg1 == z, "0" );
    REPORT( "-1 != 0", neg1 != z, "1" );
    REPORT( "-1 <= 0", neg1 <= z, "1" );
    REPORT( "-1 >= 0", neg1 >= z, "0" );
    REPORT( "-1 < 0", neg1 < z, "1" );
    REPORT( "-1 > 0", neg1 > z, "0" );

    REPORT( "1 == 0", pos1 == z, "0" );
    REPORT( "1 != 0", pos1 != z, "1" );
    REPORT( "1 <= 0", pos1 <= z, "0" );
    REPORT( "1 >= 0", pos1 >= z, "1" );
    REPORT( "1 < 0", pos1 < z, "0" );
    REPORT( "1 > 0", pos1 > z, "1" );

    REPORT( "-1 == -2", neg1 == neg2, "0" );
    REPORT( "-1 != -2", neg1 != neg2, "1" );
    REPORT( "-1 <= -2", neg1 <= neg2, "0" );
    REPORT( "-1 >= -2", neg1 >= neg2, "1" );
    REPORT( "-1 < -2", neg1 < neg2, "0" );
    REPORT( "-1 > -2", neg1 > neg2, "1" );

    REPORT( "-2 == -1", neg2 == neg1, "0" );
    REPORT( "-2 != -1", neg2 != neg1, "1" );
    REPORT( "-2 <= -1", neg2 <= neg1, "1" );
    REPORT( "-2 >= -1", neg2 >= neg1, "0" );
    REPORT( "-2 < -1", neg2 < neg1, "1" );
    REPORT( "-2 > -1", neg2 > neg1, "0" );

    REPORT( "-1 == 1", neg1 == pos1, "0" );
    REPORT( "-1 != 1", neg1 != pos1, "1" );
    REPORT( "-1 <= 1", neg1 <= pos1, "1" );
    REPORT( "-1 >= 1", neg1 >= pos1, "0" );
    REPORT( "-1 < 1", neg1 < pos1, "1" );
    REPORT( "-1 > 1", neg1 > pos1, "0" );

    REPORT( "1 == -1", pos1 == neg1, "0" );
    REPORT( "1 != -1", pos1 != neg1, "1" );
    REPORT( "1 <= -1", pos1 <= neg1, "0" );
    REPORT( "1 >= -1", pos1 >= neg1, "1" );
    REPORT( "1 < -1", pos1 < neg1, "0" );
    REPORT( "1 > -1", pos1 > neg1, "1" );

    REPORT( "1 == 2", pos1 == pos2, "0" );
    REPORT( "1 != 2", pos1 != pos2, "1" );
    REPORT( "1 <= 2", pos1 <= pos2, "1" );
    REPORT( "1 >= 2", pos1 >= pos2, "0" );
    REPORT( "1 < 2", pos1 < pos2, "1" );
    REPORT( "1 > 2", pos1 > pos2, "0" );

    REPORT( "2 == 1", pos2 == pos1, "0" );
    REPORT( "2 != 1", pos2 != pos1, "1" );
    REPORT( "2 <= 1", pos2 <= pos1, "0" );
    REPORT( "2 >= 1", pos2 >= pos1, "1" );
    REPORT( "2 < 1", pos2 < pos1, "0" );
    REPORT( "2 > 1", pos2 > pos1, "1" );
}

void check_arithmetic()
{
    // constructors

    quantity< area_d > a1;
    quantity< area_d > a2( meter() * meter() );
    REPORT( "ctor(quan)", a2, "1.000000 m+2" );

    // assignment

    a1 = 3 * meter() * meter();
    REPORT( "ctor(), assign", a1, "3.000000 m+2" );
    a2 = 4 * meter() * meter();
    REPORT( "assign", a2, "4.000000 m+2" );

    // addition

    a1 = 5 * meter() * meter();
    a2 = 6 * meter() * meter();
    a1 += a2;
    REPORT( "quan += quan", a1, "11.000000 m+2" );

    REPORT( "+ quan", a1, "11.000000 m+2" );

    REPORT( "quan + quan", a1 + a2, "17.000000 m+2" );

    // subtraction

    a1 = 9 * meter() * meter();
    a2 = 7 * meter() * meter();
    a1 -= a2;
    REPORT( "quan -= quan", a1, "2.000000 m+2" );

    REPORT( "- quan", -a1, "-2.000000 m+2" );

    REPORT( "quan - quan", a1 - a2, "-5.000000 m+2" );
    REPORT( "quan - quan", a2 - a1, "5.000000 m+2" );

    // multiplication

    quantity< speed_d > s1( 8 * meter() / second() );
    quantity< speed_d > s2( 20 * meter() / second() );
    quantity< time_interval_d > t( 5 * second() );
    quantity< length_d > len( 4 * meter() );

    s1 *= 2;
    REPORT( "quan *= num", s1, "16.000000 m s-1" );

    REPORT( "quan * quan", s1 * s2, "320.000000 m+2 s-2" );
    REPORT( "quan1 * quan2", s1 * len, "64.000000 m+2 s-1" );
    REPORT( "quan * num", s1 * 3, "48.000000 m s-1" );
    REPORT( "num * quan", 5 * s1, "80.000000 m s-1" );

    // division

    s2 /= 5;
    REPORT( "quan /= num", s2, "4.000000 m s-1" );

    REPORT( "quan / quan", s2 / s2, "1.000000" );
    REPORT( "quan1 / quan2", s2 / t, "0.800000 m s-2" );
    REPORT( "quan / num", s2 / 8, "0.500000 m s-1" );
    REPORT( "num / quan", 8 / s2, "2.000000 m-1 s" );
}

void check_powers_and_roots()
{
    // general powers

    quantity< force_d > f1( 2 * newton() );

    REPORT( "nth_power<10>", nth_power< 10 >( f1 ), "1024.000000 m+10 kg+10 s-20" );
    REPORT( "nth_power<4>", nth_power< 4 >( f1 ), "16.000000 m+4 kg+4 s-8" );
    REPORT( "nth_power<3>", nth_power< 3 >( f1 ), "8.000000 m+3 kg+3 s-6" );
    REPORT( "nth_power<2>", nth_power< 2 >( f1 ), "4.000000 m+2 kg+2 s-4" );
    REPORT( "nth_power<1>", nth_power< 1 >( f1 ), "2.000000 m kg s-2" );
    REPORT( "nth_power<0>", nth_power< 0 >( f1 ), "1.000000" );
    REPORT( "nth_power<-1>", nth_power< -1 >( f1 ), "0.500000 m-1 kg-1 s+2" );
    REPORT( "nth_power<-2>", nth_power< -2 >( f1 ), "0.250000 m-2 kg-2 s+4" );

    // special powers

    REPORT( "square", square( f1 ), "4.000000 m+2 kg+2 s-4" );
    REPORT( "cube", cube( f1 ), "8.000000 m+3 kg+3 s-6" );

    // general roots

    quantity< dimensions< 4, 0, 0 > > hv( 10000 * meter() * meter() * meter() * meter() );

    REPORT( "nth_root<4>", nth_root< 4 >( hv ), "10.000000 m" );
    REPORT( "nth_root<2>", nth_root< 2 >( hv ), "100.000000 m+2" );
    REPORT( "nth_root<1>", nth_root< 1 >( hv ), "10000.000000 m+4" );
    REPORT( "nth_root<-1>", nth_root< -1 >( hv ), "0.000100 m-4" );
    REPORT( "nth_root<-2>", nth_root< -2 >( hv ), "0.010000 m-2" );
    REPORT( "nth_root<-4>", nth_root< -4 >( hv ), "0.100000 m-1" );

    // special roots

    REPORT( "sqrt", sqrt( hv ), "100.000000 m+2" );

    quantity< power_d > p1( 3 * watt() );
    quantity< power_d > p2( 4 * watt() );
    
    REPORT( "sqrt", sqrt( square( p1 ) + square( p2 ) ), "5.000000 m+2 kg s-3" );

    quantity< frequency_d > freq( 25 / second() );
    quantity< dimensions< 0, 0, -1, 2 > > thing( 9 * ampere() * ampere() / second() );

    REPORT( "sqrt", sqrt( freq * thing ), "15.000000 s-1 A" );
}

void check_containers()
{
    // arrays are ok

    quantity< volume_d > varray[ 10 ];
    for( int i = 0; i < 10; i ++ )
        varray[ i ] = i * stere();

    REPORT( "array", varray[ 6 ], "6.000000 m+3" );

    // make sure quantity<> works with STL

    vector< quantity< power_d > > pvec;
    pvec.push_back( 3.3 * watt() );
    pvec.push_back( 5.5 * watt() );
    pvec.push_back( 4.4 * watt() );
    pvec.push_back( 6.6 * watt() );
    pvec.push_back( 2.2 * watt() );
    pvec.push_back( 1.1 * watt() );
    sort( pvec.begin(), pvec.end() );

    REPORT( "sort", pvec[ 0 ], "1.100000 m+2 kg s-3" );
    REPORT( "sort", pvec[ 4 ] / watt(), "5.500000" );

    vector< quantity< power_d > >::iterator pvi = pvec.begin();
    pvi++;

    REPORT( "iterator", *++pvi, "3.300000 m+2 kg s-3" );
}

void check_user_defined()
{
    // make sure user-defined types and units work

    quantity< hyperspace::warp_factor_d > full_power = 3270000L * hyperspace::scotty();
    ostringstream os;
    os.setf( ios::fixed, ios::floatfield );
    os << setprecision( 6 );
    os << full_power / ( mega() * hyperspace::scotty() ) << " MSc";

    REPORT( "hyperspace", os.str(), "3.270000 MSc" );
}


int main()
{
    cout << "\nRegression Test for Quantity Library\n\n";

    check_base_units();
    check_types();
    check_derived_units();
    check_prefixes();
    check_approved_units();
    check_other_units();
    check_comparisons();
    check_arithmetic();
    check_powers_and_roots();
    check_containers();
    check_user_defined();

    //quantity< dimensions< 0, 0, 0 > > foo;

    report_summary();

    return fail_count;
}
