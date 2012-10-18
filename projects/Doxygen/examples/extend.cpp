#include <iostream>

#include "phys/units/io.hpp"
#include "phys/units/quantity.hpp"

using namespace phys::units;
using namespace phys::units::io;

int main()
{
    quantity O( unit( "Ohm"           ) );  // the default is no_extend()
    quantity F( unit( "Foo", extend() ) );  // extend() enables extension needed here

    std::cout << "O = " << O << std::endl
              << "F = " << F << std::endl;
}
