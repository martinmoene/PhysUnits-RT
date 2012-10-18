
// cl -W3 -EHsc -I.. exceptions.cpp  &&  exceptions

#include "phys/units/io.hpp"
#include <iostream>

using namespace phys::units;
using namespace phys::units::io;

int main()
{
   try
   {
      // incompatible dimensions
      quantity length = meter();
      quantity current = ampere();
      current = length;
      current += length;
   }
   catch( std::exception const & e )
   {
      std::cout << "Error: " << e.what() << std::endl;
   }

   return 0; // VC6
}

