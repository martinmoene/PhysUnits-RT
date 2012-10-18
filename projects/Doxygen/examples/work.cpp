#include <iostream>

#include "phys/units/io.hpp"
#include "phys/units/quantity.hpp"

using namespace phys::units;
using namespace phys::units::io;

quantity
work( const quantity & F, const quantity & dx )
{
    return F * dx; // Defines the relation: work = force * distance.
}

int main()
{
    /// Test calculation of work.
    quantity      F ( 2.0 * newton());  // Define a quantity of force.
    quantity      dx( 2.0 * meter() );  // and a distance,
    quantity      E ( work( F, dx ) );  // and calculate the work done.

    std::cout << "F  = " << F  << std::endl
              << "dx = " << dx << std::endl
              << "E  = " << E  << std::endl;
}
