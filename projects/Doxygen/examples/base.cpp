#include <iostream>

#include "phys/units/io.hpp"
#include "phys/units/quantity.hpp"

using namespace phys::units;
using namespace phys::units::io;

int main()
{
    std::cout << "J = " << to_base_unit_symbols( joule() ) << std::endl;
}
