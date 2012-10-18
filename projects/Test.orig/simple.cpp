// cl -W3 -EHsc -I.. simple.cpp  &&  simple

#include "phys/units/io.hpp"
#include <iostream>

using namespace phys::units;
using namespace phys::units::io;

int main()
{
   try
   {
      quantity n( number() );
      quantity x( meter() );
      quantity x2( meter() * meter() );

      x = sqrt( x2 );
      x = nth_root( x2, 2 );

      x = 1 * meter();
      x = meter() * 1;

      x = x + x;

      quantity v = x / second();

      quantity y(x);

      quantity z = x * y;

      z += z;

      // z+=x;

      z < z;

      quantity q = z * quantity_x1() * quantity_x1();

      std::cout << "n:" << n << std::endl;
      std::cout << "x:" << x << std::endl;
      std::cout << "v:" << v << std::endl;
      std::cout << "z.value():" << z.value() << std::endl;
      std::cout << "z:" << z << std::endl;
      std::cout << "q:" << q << std::endl;

      quantity f = unit( "foo", extend() );
      quantity g = unit( "gggg", extend() );
      quantity h = unit( "hhhh", extend() );
      quantity w = unit( "hhhh", extend() );

      std::cout << "f:" << f << std::endl;
      std::cout << "g:" << g << std::endl;
      std::cout << "h:" << h << std::endl;
      std::cout << "w:" << w << std::endl;
      std::cout << "w*w:" << w*w << std::endl;

      std::cout << "\nunit(\"m\"):" << unit("m") << std::endl;
      std::cout << "unit(\"kg\"):" << unit("kg") << std::endl;
      std::cout << "unit(\"s\"):" << unit("s") << std::endl;
      std::cout << "unit(\"A\"):" << unit("A") << std::endl;
      std::cout << "unit(\"K\"):" << unit("K") << std::endl;
      std::cout << "unit(\"mol\"):" << unit("mol") << std::endl;
      std::cout << "unit(\"cd\"):" << unit("cd") << std::endl;

      std::cout << "\nunit(\"Hz\"):" << unit("Hz") << std::endl;
      std::cout << "unit(\"N\"):" << unit("N") << std::endl;
      std::cout << "unit(\"Pa\"):" << unit("Pa") << std::endl;
      std::cout << "unit(\"J\"):" << unit("J") << std::endl;
      std::cout << "unit(\"W\"):" << unit("W") << std::endl;
      std::cout << "unit(\"C\"):" << unit("C") << std::endl;
      std::cout << "unit(\"J\"):" << unit("J") << std::endl;
      std::cout << "unit(\"V\"):" << unit("V") << std::endl;
      std::cout << "unit(\"F\"):" << unit("F") << std::endl;
      std::cout << "unit(\"Ohm\"):" << unit("Ohm") << std::endl;
      std::cout << "unit(\"S\"):" << unit("S") << std::endl;
      std::cout << "unit(\"T\"):" << unit("T") << std::endl;
      std::cout << "unit(\"H\"):" << unit("H") << std::endl;
      std::cout << "unit(\"'C\"):" << unit("'C") << std::endl;
      std::cout << "unit(\"lm\"):" << unit("lm") << std::endl;
      std::cout << "unit(\"lx\"):" << unit("lx") << std::endl;
      std::cout << "unit(\"Bq\"):" << unit("Bq") << std::endl;
      std::cout << "unit(\"Gy\"):" << unit("Gy") << std::endl;
      std::cout << "unit(\"Sv\"):" << unit("Sv") << std::endl;

      std::cout << "\n1/second():" << (1/second()) << std::endl;
      std::cout << "number()/second():" << (number()/second()) << std::endl;
      std::cout << "hertz():" << hertz() << std::endl;
      std::cout << "meter()/second():" << meter()/second() << std::endl;
      std::cout << "meter()/(second()*second()):" << meter()/(second()*second()) << std::endl;
      std::cout << "volt()/second():" << volt()/second() << std::endl;
      std::cout << "volt()/f:" << volt()/f << std::endl;

      std::cout << "to_unit_name(length_d):" << to_unit_name(length_d) << std::endl;
      std::cout << "to_unit_name(mass_d):" << to_unit_name(mass_d) << std::endl;
      std::cout << "to_unit_name(time_interval_d):" << to_unit_name(time_interval_d) << std::endl;
      std::cout << "to_unit_name(electric_current_d):" << to_unit_name(electric_current_d) << std::endl;
      std::cout << "to_unit_name(thermodynamic_temperature_d):" << to_unit_name(thermodynamic_temperature_d) << std::endl;
      std::cout << "to_unit_name(amount_of_substance_d):" << to_unit_name(amount_of_substance_d) << std::endl;
      std::cout << "to_unit_name(luminous_intensity_d):" << to_unit_name(luminous_intensity_d) << std::endl;

      std::cout << "prefix(\"f\"):" << prefix("f") << std::endl;
      std::cout << "prefix(\"p\"):" << prefix("p") << std::endl;
      std::cout << "prefix(\"u\"):" << prefix("u") << std::endl;
      std::cout << "prefix(\"m\"):" << prefix("m") << std::endl;
      std::cout << "prefix(\"k\"):" << prefix("k") << std::endl;
      std::cout << "prefix(\"M\"):" << prefix("M") << std::endl;
      std::cout << "prefix(\"G\"):" << prefix("G") << std::endl;
      std::cout << "prefix(\"T\"):" << prefix("T") << std::endl;

      // invalid prefix, throw exception:
      std::cout << "\nexpecting exception:" << std::endl;
      std::cout << "prefix(\"x\"):" << prefix("x") << std::endl;
   }
   catch( std::exception const & e )
   {
      std::cout << "Error: " << e.what() << std::endl;
   }

   return 0;
}
