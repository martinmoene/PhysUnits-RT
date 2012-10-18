/*
 * TestUnit.cpp
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
#include "phys/units/other_units.hpp"

#ifdef PHYS_UNITS_IN_RT_NAMESPACE
using namespace rt::phys::units;
using namespace rt::phys::units::io;
#else
using namespace phys::units;
using namespace phys::units::io;
#endif

TEST_CASE( "unit/base", "Base units" )
{
    REQUIRE( s( meter() ) == "1.000000 m" );
    REQUIRE( s( metre() ) == "1.000000 m" );
    REQUIRE( s( kilogram() ) == "1.000000 kg" );
    REQUIRE( s( second() ) == "1.000000 s" );
    REQUIRE( s( ampere() ) == "1.000000 A" );
    REQUIRE( s( kelvin() ) == "1.000000 K" );
    REQUIRE( s( mole() ) == "1.000000 mol" );
    REQUIRE( s( candela() ) == "1.000000 cd" );
}

TEST_CASE( "unit/standard", "The rest of the standard dimensional types, as specified in SP811" )
{
    REQUIRE( b( quantity( absorbed_dose_d ).zero() ) == "0.000000 m+2 s-2" );
    REQUIRE( b( quantity( absorbed_dose_rate_d ).zero() ) == "0.000000 m+2 s-3" );
    REQUIRE( b( quantity( acceleration_d ).zero() ) == "0.000000 m s-2" );
    REQUIRE( b( quantity( activity_of_a_nuclide_d ).zero() ) == "0.000000 s-1" );
    REQUIRE( b( quantity( angular_velocity_d ).zero() ) == "0.000000 s-1" );
    REQUIRE( b( quantity( angular_acceleration_d ).zero() ) == "0.000000 s-2" );
    REQUIRE( b( quantity( area_d ).zero() ) == "0.000000 m+2" );
    REQUIRE( b( quantity( capacitance_d ).zero() ) == "0.000000 m-2 kg-1 s+4 A+2" );
    REQUIRE( b( quantity( concentration_d ).zero() ) == "0.000000 m-3 mol" );
    REQUIRE( b( quantity( current_density_d ).zero() ) == "0.000000 m-2 A" );
    REQUIRE( b( quantity( dose_equivalent_d ).zero() ) == "0.000000 m+2 s-2" );
    REQUIRE( b( quantity( dynamic_viscosity_d ).zero() ) == "0.000000 m-1 kg s-1" );
    REQUIRE( b( quantity( electric_charge_d ).zero() ) == "0.000000 s A" );
    REQUIRE( b( quantity( electric_charge_density_d ).zero() ) == "0.000000 m-3 s A" );
    REQUIRE( b( quantity( electric_conductance_d ).zero() ) == "0.000000 m-2 kg-1 s+3 A+2" );
    REQUIRE( b( quantity( electric_field_strenth_d ).zero() ) == "0.000000 m kg s-3 A-1" );
    REQUIRE( b( quantity( electric_flux_density_d ).zero() ) == "0.000000 m-2 s A" );
    REQUIRE( b( quantity( electric_potential_d ).zero() ) == "0.000000 m+2 kg s-3 A-1" );
    REQUIRE( b( quantity( electric_resistance_d ).zero() ) == "0.000000 m+2 kg s-3 A-2" );
    REQUIRE( b( quantity( energy_d ).zero() ) == "0.000000 m+2 kg s-2" );
    REQUIRE( b( quantity( energy_density_d ).zero() ) == "0.000000 m-1 kg s-2" );
    REQUIRE( b( quantity( exposure_d ).zero() ) == "0.000000 kg-1 s A" );
    REQUIRE( b( quantity( force_d ).zero() ) == "0.000000 m kg s-2" );
    REQUIRE( b( quantity( frequency_d ).zero() ) == "0.000000 s-1" );
    REQUIRE( b( quantity( heat_capacity_d ).zero() ) == "0.000000 m+2 kg s-2 K-1" );
    REQUIRE( b( quantity( heat_density_d ).zero() ) == "0.000000 kg s-2" );
    REQUIRE( b( quantity( heat_density_flow_rate_d ).zero() ) == "0.000000 kg s-3" );
    REQUIRE( b( quantity( heat_flow_rate_d ).zero() ) == "0.000000 m+2 kg s-3" );
    REQUIRE( b( quantity( heat_flux_density_d ).zero() ) == "0.000000 kg s-3" );
    REQUIRE( b( quantity( heat_transfer_coefficient_d ).zero() ) == "0.000000 kg s-3 K-1" );
    REQUIRE( b( quantity( illuminance_d ).zero() ) == "0.000000 m-2 cd" );
    REQUIRE( b( quantity( inductance_d ).zero() ) == "0.000000 m+2 kg s-2 A-2" );
    REQUIRE( b( quantity( irradiance_d ).zero() ) == "0.000000 kg s-3" );
    REQUIRE( b( quantity( kinematic_viscosity_d ).zero() ) == "0.000000 m+2 s-1" );
    REQUIRE( b( quantity( luminance_d ).zero() ) == "0.000000 m-2 cd" );
    REQUIRE( b( quantity( luminous_flux_d ).zero() ) == "0.000000 cd" );
    REQUIRE( b( quantity( magnetic_field_strength_d ).zero() ) == "0.000000 m-1 A" );
    REQUIRE( b( quantity( magnetic_flux_d ).zero() ) == "0.000000 m+2 kg s-2 A-1" );
    REQUIRE( b( quantity( magnetic_flux_density_d ).zero() ) == "0.000000 kg s-2 A-1" );
    REQUIRE( b( quantity( magnetic_permeability_d ).zero() ) == "0.000000 m kg s-2 A-2" );
    REQUIRE( b( quantity( mass_density_d ).zero() ) == "0.000000 m-3 kg" );
    REQUIRE( b( quantity( mass_flow_rate_d ).zero() ) == "0.000000 kg s-1" );
    REQUIRE( b( quantity( molar_energy_d ).zero() ) == "0.000000 m+2 kg s-2 mol-1" );
    REQUIRE( b( quantity( molar_entropy_d ).zero() ) == "0.000000 m+2 kg s-2 A-1 mol-1" );
    REQUIRE( b( quantity( moment_of_force_d ).zero() ) == "0.000000 m+2 kg s-2" );
    REQUIRE( b( quantity( permittivity_d ).zero() ) == "0.000000 m-3 kg-1 s+4 A+2" );
    REQUIRE( b( quantity( power_d ).zero() ) == "0.000000 m+2 kg s-3" );
    REQUIRE( b( quantity( pressure_d ).zero() ) == "0.000000 m-1 kg s-2" );
    REQUIRE( b( quantity( radiance_d ).zero() ) == "0.000000 kg s-3" );
    REQUIRE( b( quantity( radiant_intensity_d ).zero() ) == "0.000000 m+2 kg s-3" );
    REQUIRE( b( quantity( specific_volume_d ).zero() ) == "0.000000 m+3 kg-1" );
    REQUIRE( b( quantity( speed_d ).zero() ) == "0.000000 m s-1" );
    REQUIRE( b( quantity( specific_energy_d ).zero() ) == "0.000000 m+2 s-2" );
    REQUIRE( b( quantity( specific_heat_capacity_d ).zero() ) == "0.000000 m+2 s-2 K-1" );
    REQUIRE( b( quantity( specific_volume_d ).zero() ) == "0.000000 m+3 kg-1" );
    REQUIRE( b( quantity( substance_permeability_d ).zero() ) == "0.000000 m-1 s" );
    REQUIRE( b( quantity( surface_tension_d ).zero() ) == "0.000000 kg s-2" );
    REQUIRE( b( quantity( thermal_conductivity_d ).zero() ) == "0.000000 m kg s-3 K-1" );
    REQUIRE( b( quantity( thermal_diffusivity_d ).zero() ) == "0.000000 m+2 s-1" );
    REQUIRE( b( quantity( thermal_insulance_d ).zero() ) == "0.000000 kg-1 s+3 K" );
    REQUIRE( b( quantity( thermal_resistance_d ).zero() ) == "0.000000 m-2 kg-1 s+3 K" );
    REQUIRE( b( quantity( thermal_resistivity_d ).zero() ) == "0.000000 m-1 kg-1 s+3 K" );
    REQUIRE( b( quantity( torque_d ).zero() ) == "0.000000 m+2 kg s-2" );
    REQUIRE( b( quantity( volume_d ).zero() ) == "0.000000 m+3" );
    REQUIRE( b( quantity( volume_flow_rate_d ).zero() ) == "0.000000 m+3 s-1" );
    REQUIRE( b( quantity( wave_number_d ).zero() ) == "0.000000 m-1" );
}

TEST_CASE( "unit/derived", "The derived SI units, as specified in SP811" )
{
    REQUIRE( s( radian() ) == "1.000000" );
    REQUIRE( s( steradian() ) == "1.000000" );
    REQUIRE( b( hertz() ) == "1.000000 s-1" );
    REQUIRE( b( newton() ) == "1.000000 m kg s-2" );
    REQUIRE( b( pascal() ) == "1.000000 m-1 kg s-2" );
    REQUIRE( b( joule() ) == "1.000000 m+2 kg s-2" );
    REQUIRE( b( watt() ) == "1.000000 m+2 kg s-3" );
    REQUIRE( b( coulomb() ) == "1.000000 s A" );
    REQUIRE( b( volt() ) == "1.000000 m+2 kg s-3 A-1" );
    REQUIRE( b( farad() ) == "1.000000 m-2 kg-1 s+4 A+2" );
    REQUIRE( b( ohm() ) == "1.000000 m+2 kg s-3 A-2" );
    REQUIRE( b( siemens() ) == "1.000000 m-2 kg-1 s+3 A+2" );
    REQUIRE( b( weber() ) == "1.000000 m+2 kg s-2 A-1" );
    REQUIRE( b( tesla() ) == "1.000000 kg s-2 A-1" );
    REQUIRE( b( henry() ) == "1.000000 m+2 kg s-2 A-2" );
    REQUIRE( b( degree_celsius() ) == "1.000000 K" );
    REQUIRE( b( lumen() ) == "1.000000 cd" );
    REQUIRE( b( lux() ) == "1.000000 m-2 cd" );
    REQUIRE( b( becquerel() ) == "1.000000 s-1" );
    REQUIRE( b( gray() ) == "1.000000 m+2 s-2" );
    REQUIRE( b( sievert() ) == "1.000000 m+2 s-2" );
}

TEST_CASE( "unit/approved", "The rest of the units approved for use with SI, as specified in SP811" )
{
    REQUIRE( b( 1e+10 * angstrom() ) == "1.000000 m" );
    REQUIRE( b( are() ) == "100.000000 m+2" );
    REQUIRE( b( 1e-5 * bar() ) == "1.000000 m-1 kg s-2" );
    REQUIRE( b( 1e+28 * barn() ) == "1.000000 m+2" );
    REQUIRE( b( 1e-10 * curie() ) == "3.700000 s-1" );
    REQUIRE( b( day() ) == "86400.000000 s" );
    REQUIRE( s( 1e+2 * degree_angle() ) == "1.745329" );
    REQUIRE( b( 1e+2 * gal() ) == "1.000000 m s-2" );
    REQUIRE( b( 1e-4 * hectare() ) == "1.000000 m+2" );
    REQUIRE( b( hour() ) == "3600.000000 s" );
    REQUIRE( b( 1e+1 * knot() ) == "5.144444 m s-1" );
    REQUIRE( b( 1e+3 * liter() ) == "1.000000 m+3" );
    REQUIRE( b( 1e+3 * litre() ) == "1.000000 m+3" );
    REQUIRE( b( minute() ) == "60.000000 s" );
    REQUIRE( s( 1e+4 * minute_angle() ) == "2.908882" );
    REQUIRE( b( 1e-3 * mile_nautical() ) == "1.852000 m" );
    REQUIRE( b( 1e+2 * rad() ) == "1.000000 m+2 s-2" );
    REQUIRE( b( 1e+2 * rem() ) == "1.000000 m+2 s-2" );
    REQUIRE( b( 1e+4 * roentgen() ) == "2.580000 kg-1 s A" );
    REQUIRE( s( 1e+6 * second_angle() ) == "4.848137" );
    REQUIRE( b( ton_metric() ) == "1000.000000 kg" );
    REQUIRE( b( tonne() ) == "1000.000000 kg" );
}

/*
 * fatal error C1509: compiler limit : too many exception handler states in
 *   function 'TestCaseFunction_catch_internal_157'. simplify function
 */

TEST_CASE( "unit/other/part1", "Other units" )
{
    REQUIRE( b( abampere() ) == "10.000000 A" );
    REQUIRE( b( abcoulomb() ) == "10.000000 s A" );
    REQUIRE( b( 1e-9 * abfarad() ) == "1.000000 m-2 kg-1 s+4 A+2" );
    REQUIRE( b( 1e+9 * abhenry() ) == "1.000000 m+2 kg s-2 A-2" );
    REQUIRE( b( 1e-9 * abmho() ) == "1.000000 m-2 kg-1 s+3 A+2" );
    REQUIRE( b( 1e+9 * abohm() ) == "1.000000 m+2 kg s-3 A-2" );
    REQUIRE( b( 1e+8 * abvolt() ) == "1.000000 m+2 kg s-3 A-1" );
    REQUIRE( b( 1e-3 * acre() ) == "4.046873 m+2" );
    REQUIRE( b( 1e-3 * acre_foot() ) == "1.233489 m+3" );
    REQUIRE( b( 1e-11 * astronomical_unit() ) == "1.495979 m" );
    REQUIRE( b( 1e-5 * atmosphere_std() ) == "1.013250 m-1 kg s-2" );
    REQUIRE( b( 1e-4 * atmosphere_tech() ) == "9.806650 m-1 kg s-2" );
    REQUIRE( b( 1e+1 * barrel() ) == "1.589873 m+3" );
    REQUIRE( b( 1e-1 * biot() ) == "1.000000 A" );
    REQUIRE( b( 1e-3 * btu() ) == "1.055870 m+2 kg s-2" );
    REQUIRE( b( 1e-3 * btu_it() ) == "1.055056 m+2 kg s-2" );
    REQUIRE( b( 1e-3 * btu_th() ) == "1.054350 m+2 kg s-2" );
    REQUIRE( b( 1e-3 * btu_39F() ) == "1.059670 m+2 kg s-2" );
    REQUIRE( b( 1e-3 * btu_59F() ) == "1.054800 m+2 kg s-2" );
    REQUIRE( b( 1e-3 * btu_60F() ) == "1.054680 m+2 kg s-2" );
    REQUIRE( b( 1e+2 * bushel() ) == "3.523907 m+3" );
    REQUIRE( b( calorie() ) == "4.190020 m+2 kg s-2" );
    REQUIRE( b( calorie_it() ) == "4.186800 m+2 kg s-2" );
    REQUIRE( b( calorie_th() ) == "4.184000 m+2 kg s-2" );
    REQUIRE( b( calorie_15C() ) == "4.185800 m+2 kg s-2" );
    REQUIRE( b( calorie_20C() ) == "4.181900 m+2 kg s-2" );
    REQUIRE( b( 1e+4 * carat_metric() ) == "2.000000 kg" );
    REQUIRE( b( 1e-1 * chain() ) == "2.011684 m" );
    REQUIRE( b( 1e+1 * clo() ) == "1.550000 kg-1 s+3 K" );
    REQUIRE( b( 1e-3 * cm_mercury() ) == "1.333224 m-1 kg s-2" );
    REQUIRE( b( cord() ) == "3.624556 m+3" );
    REQUIRE( b( 1e+4 * cup() ) == "2.365882 m+3" );
    REQUIRE( b( 1e+13 * darcy() ) == "9.869233 m+2" );
    REQUIRE( b( 1e-4 * day_sidereal() ) == "8.616409 s" );
    REQUIRE( b( 1e+30 * debye() ) == "3.335641 m s A" );
    REQUIRE( b( 1e+1 * degree_fahrenheit() ) == "5.555556 K" );
    REQUIRE( b( 1e+1 * degree_rankine() ) == "5.555556 K" );
    REQUIRE( b( 1e+7 * denier() ) == "1.111111 m-1 kg" );
    REQUIRE( b( 1e+5 * dyne() ) == "1.000000 m kg s-2" );
    REQUIRE( b( 1e+7 * erg() ) == "1.000000 m+2 kg s-2" );
    REQUIRE( b( 1e-4 * faraday() ) == "9.648531 s A" );
    REQUIRE( b( fathom() ) == "1.828804 m" );
    REQUIRE( b( 1e+15 * fermi() ) == "1.000000 m" );
    REQUIRE( b( 1e+1 * foot() ) == "3.048000 m" );
    REQUIRE( b( foot_pound_force() ) == "1.355818 m+2 kg s-2" );
    REQUIRE( b( 1e+2 * foot_poundal() ) == "4.214011 m+2 kg s-2" );
    REQUIRE( b( 1e+1 * foot_us_survey() ) == "3.048006 m" );
    REQUIRE( b( 1e-1 * footcandle() ) == "1.076391 m-2 cd" );
    REQUIRE( b( footlambert() ) == "3.426259 m-2 cd" );
    REQUIRE( b( 1e-6 * fortnight() ) == "1.209600 s" );
    REQUIRE( b( 1e+10 * franklin() ) == "3.335641 s A" );
    REQUIRE( b( 1e-2 * furlong() ) == "2.011680 m" );
    REQUIRE( b( 1e+3 * gallon_imperial() ) == "4.546090 m+3" );
    REQUIRE( b( 1e+3 * gallon_us() ) == "3.785412 m+3" );
    REQUIRE( b( 1e+9 * gamma() ) == "1.000000 kg s-2 A-1" );
    REQUIRE( b( 1e+9 * gamma_mass() ) == "1.000000 kg" );
    REQUIRE( b( 1e+4 * gauss() ) == "1.000000 kg s-2 A-1" );
    REQUIRE( b( 1e+1 * gilbert() ) == "7.957747 A" );
    REQUIRE( b( 1e+4 * gill_imperial() ) == "1.420653 m+3" );
    REQUIRE( b( 1e+4 * gill_us() ) == "1.182941 m+3" );
    REQUIRE( s( 1e+2 * gon() ) == "1.570796" );
    REQUIRE( b( 1e+5 * grain() ) == "6.479891 kg" );
    REQUIRE( b( 1e-2 * horsepower() ) == "7.456999 m+2 kg s-3" );
    REQUIRE( b( 1e-3 * horsepower_boiler() ) == "9.809500 m+2 kg s-3" );
    REQUIRE( b( 1e-2 * horsepower_electric() ) == "7.460000 m+2 kg s-3" );
    REQUIRE( b( 1e-2 * horsepower_metric() ) == "7.354988 m+2 kg s-3" );
    REQUIRE( b( 1e-2 * horsepower_uk() ) == "7.457000 m+2 kg s-3" );
    REQUIRE( b( 1e-2 * horsepower_water() ) == "7.460430 m+2 kg s-3" );
    REQUIRE( b( 1e-3 * hour_sidereal() ) == "3.590170 s" );
    REQUIRE( b( 1e-1 * hundredweight_long() ) == "5.080235 kg" );
    REQUIRE( b( 1e-1 * hundredweight_short() ) == "4.535924 kg" );
    REQUIRE( b( 1e+2 * inch() ) == "2.540000 m" );
    REQUIRE( b( 1e-3 * inches_mercury() ) == "3.386389 m-1 kg s-2" );
    REQUIRE( b( 1e-2 * kayser() ) == "1.000000 m-1" );
    REQUIRE( b( kilogram_force() ) == "9.806650 m kg s-2" );
    REQUIRE( b( kilopond() ) == "9.806650 m kg s-2" );
    REQUIRE( b( 1e-3 * kip() ) == "4.448222 m kg s-2" );
    REQUIRE( b( 1e+9 * lambda_volume() ) == "1.000000 m+3" );
    REQUIRE( b( 1e-3 * lambert() ) == "3.183099 m-2 cd" );
    REQUIRE( b( 1e-4 * langley() ) == "4.184000 kg s-2" );
    REQUIRE( b( 1e-15 * light_year() ) == "9.460730 m" );
    REQUIRE( b( 1e+8 * maxwell() ) == "1.000000 m+2 kg s-2 A-1" );
    REQUIRE( b( mho() ) == "1.000000 m-2 kg-1 s+3 A+2" );
    REQUIRE( b( 1e+6 * micron() ) == "1.000000 m" );
    REQUIRE( b( 1e+5 * mil() ) == "2.540000 m" );
    REQUIRE( s     ( 1e+4 * mil_angle() ) == "9.817477" );
    REQUIRE( b( 1e+10 * mil_circular() ) == "5.067075 m+2" );
    REQUIRE( b( 1e-3 * mile() ) == "1.609344 m" );
    REQUIRE( b( 1e-3 * mile_us_survey() ) == "1.609347 m" );
    REQUIRE( b( 1e-1 * minute_sidereal() ) == "5.983617 s" );
    REQUIRE( b( 1e-1 * oersted() ) == "7.957747 m-1 A" );
    REQUIRE( b( 1e+2 * ounce_avdp() ) == "2.834952 kg" );
    REQUIRE( b( 1e+5 * ounce_fluid_imperial() ) == "2.841306 m+3" );
    REQUIRE( b( 1e+5 * ounce_fluid_us() ) == "2.957353 m+3" );
    REQUIRE( b( 1e+1 * ounce_force() ) == "2.780139 m kg s-2" );
    REQUIRE( b( 1e+2 * ounce_troy() ) == "3.110348 kg" );
    REQUIRE( b( 1e-16 * parsec() ) == "3.085678 m" );
    REQUIRE( b( 1e+3 * peck() ) == "8.809768 m+3" );
    REQUIRE( b( 1e+3 * pennyweight() ) == "1.555174 kg" );
    REQUIRE( b( 1e+11 * perm_0C() ) == "5.721350 m-1 s" );
    REQUIRE( b( 1e+11 * perm_23C() ) == "5.745250 m-1 s" );
    REQUIRE( b( 1e-4 * phot() ) == "1.000000 m-2 cd" );
    REQUIRE( b( 1e+3 * pica_computer() ) == "4.233333 m" );
    REQUIRE( b( 1e+3 * pica_printers() ) == "4.217518 m" );
    REQUIRE( b( 1e+4 * pint_dry() ) == "5.506105 m+3" );
    REQUIRE( b( 1e+4 * pint_liquid() ) == "4.731765 m+3" );
    REQUIRE( b( 1e+4 * point_computer() ) == "3.527778 m" );
    REQUIRE( b( 1e+4 * point_printers() ) == "3.514598 m" );
    REQUIRE( b( 1e+1 * poise() ) == "1.000000 m-1 kg s-1" );
}

TEST_CASE( "unit/other/part2", "Other units (continued)" )
{
    REQUIRE( b( 1e+1 * pound_avdp() ) == "4.535924 kg" );
    REQUIRE( b( pound_force() ) == "4.448222 m kg s-2" );
    REQUIRE( b( 1e+1 * pound_troy() ) == "3.732417 kg" );
    REQUIRE( b( 1e+1 * poundal() ) == "1.382550 m kg s-2" );
    REQUIRE( b( 1e-3 * psi() ) == "6.894757 m-1 kg s-2" );
    REQUIRE( b( 1e-18 * quad() ) == "1.055056 m+2 kg s-2" );
    REQUIRE( b( 1e+3 * quart_dry() ) == "1.101221 m+3" );
    REQUIRE( b( 1e+4 * quart_liquid() ) == "9.463529 m+3" );
    REQUIRE( s( revolution() ) == "6.283185" );
    REQUIRE( b( 1e-1 * rhe() ) == "1.000000 m kg-1 s" );
    REQUIRE( b( rod() ) == "5.029210 m" );
    REQUIRE( b( 1e+1 * rpm() ) == "1.047198 s-1" );
    REQUIRE( b( 1e+1 * second_sidereal() ) == "9.972696 s" );
    REQUIRE( b( 1e+8 * shake() ) == "1.000000 s" );
    REQUIRE( b( 1e-1 * slug() ) == "1.459390 kg" );
    REQUIRE( b( 1e+10 * statampere() ) == "3.335641 A" );
    REQUIRE( b( 1e+10 * statcoulomb() ) == "3.335641 s A" );
    REQUIRE( b( 1e+12 * statfarad() ) == "1.112650 m-2 kg-1 s+4 A+2" );
    REQUIRE( b( 1e-11 * stathenry() ) == "8.987552 m+2 kg s-2 A-2" );
    REQUIRE( b( 1e+12 * statmho() ) == "1.112650 m-2 kg-1 s+3 A+2" );
    REQUIRE( b( 1e-11 * statohm() ) == "8.987552 m+2 kg s-3 A-2" );
    REQUIRE( b( 1e-2 * statvolt() ) == "2.997925 m+2 kg s-3 A-1" );
    REQUIRE( b( stere() ) == "1.000000 m+3" );
    REQUIRE( b( 1e-4 * stilb() ) == "1.000000 m-2 cd" );
    REQUIRE( b( 1e+4 * stokes() ) == "1.000000 m+2 s-1" );
    REQUIRE( b( 1e+5 * tablespoon() ) == "1.478676 m+3" );
    REQUIRE( b( 1e+6 * teaspoon() ) == "4.928922 m+3" );
    REQUIRE( b( 1e+6 * tex() ) == "1.000000 m-1 kg" );
    REQUIRE( b( 1e-8 * therm_ec() ) == "1.055060 m+2 kg s-2" );
    REQUIRE( b( 1e-8 * therm_us() ) == "1.054804 m+2 kg s-2" );
    REQUIRE( b( 1e+2 * ton_assay() ) == "2.916667 kg" );
    REQUIRE( b( 1e-3 * ton_force() ) == "8.896443 m kg s-2" );
    REQUIRE( b( 1e-3 * ton_long() ) == "1.016047 kg" );
    REQUIRE( b( 1e-3 * ton_refrigeration() ) == "3.516853 m+2 kg s-3" );
    REQUIRE( b( ton_register() ) == "2.831685 m+3" );
    REQUIRE( b( 1e-2 * ton_short() ) == "9.071847 kg" );
    REQUIRE( b( 1e-9 * ton_tnt() ) == "4.184000 m+2 kg s-2" );
    REQUIRE( b( 1e-2 * torr() ) == "1.333224 m-1 kg s-2" );
    REQUIRE( b( 1e+7 * unit_pole() ) == "1.256637 m+2 kg s-2 A-1" );
    REQUIRE( b( 1e-5 * week() ) == "6.048000 s" );
    REQUIRE( b( 1e+13 * x_unit() ) == "1.002000 m" );
    REQUIRE( b( 1e+1 * yard() ) == "9.144000 m" );
    REQUIRE( b( 1e-7 * year_sidereal() ) == "3.155815 s" );
    REQUIRE( b( 1e-7 * year_std() ) == "3.153600 s" );
    REQUIRE( b( 1e-7 * year_tropical() ) == "3.155693 s" );
}

/*
 * end of file
 */
