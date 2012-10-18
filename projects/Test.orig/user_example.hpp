//
//      user_example.hpp
//
//	Copyright (c) 2001 by Michael S. Kenniston.  For the most
//	recent version check www.xnet.com/~msk/quantity.  Permission is granted
//	to use this code without restriction so long as this copyright
//	notice appears in all source files.

//	This code is provided as-is, with no warrantee of correctness.

//	This file simply demonstrates how a programmer can add more
//	physical quantity types and units without modifying the
//	library.

#ifndef USER_EXAMPLE_HPP_MSK20010704
#define USER_EXAMPLE_HPP_MSK20010704

#include "phys/units/quantity.hpp"
#include "phys/units/io.hpp"

namespace hyperspace {

// warp factor dimensions are m-2 kg+3 s-1 A

const phys::units::dimensions warp_factor_d( -2, 3, -1, 1 );

// standard unit of measurement for warp factor is the Scotty

inline phys::units::quantity scotty()
{
	using phys::units::meter;
	using phys::units::kilogram;
	using phys::units::second;
	using phys::units::ampere;

	return 1.0
		/ meter() / meter()
		* kilogram() * kilogram() * kilogram()
		/ second()
		* ampere();
}

} // namespace hyperspace

//namespace phys { namespace units {
//
//// user-defined unit name and symbol
//
//template<>
//struct unit_info< hyperspace::warp_factor_d >
//{
//    static bool        single() { return true; }
//    static std::string name()   { return "Scotty"; }
//    static std::string symbol() { return "Sc"; }
//};
//
//}} // namespace phys::units

//
// You can now say things like:
//
//	warp_factor_t full_power = 3.27 * mega() * scotty();
// std::cout << "full power: " << full_power ;
//

#endif // USER_EXAMPLE_HPP_MSK20010704
