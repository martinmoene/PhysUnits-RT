#include <iostream>

#include "phys/units/io.hpp"
#include "phys/units/quantity.hpp"

using namespace phys::units;
using namespace phys::units::io;

int main()
{
    std::cout << "quantity = " << to_quantity( "3 J/A" )                   << std::endl
              << "quantity = " << to_quantity( "4"     , dimensionless() ) << std::endl
              << "quantity = " << to_quantity( "5 Foo" , extend()        ) << std::endl;
}
