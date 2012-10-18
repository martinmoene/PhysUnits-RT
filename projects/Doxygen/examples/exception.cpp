#include <iostream>

#include "phys/units/io.hpp"
#include "phys/units/quantity.hpp"

using namespace phys::units;
using namespace phys::units::io;

int main()
{
    try
    {
        std::cout << "quantity = " << to_quantity( "3 m/s/s" ) << std::endl;
    }
    catch( std::exception const & e )
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
