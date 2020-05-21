PhysUnits-RT
============

A C++ library for run-time dimensional analysis and unit/quantity manipulation and conversion.

This library is based on the quantity compile-time library by Michael S. Kenniston[1] and adapted and expanded for runtime use by Martin Moene.

This easy to use header-only library is intended to work with a wide range of compilers, including MSVC 6.

Example
---------

```C++
#include "phys/units/quantity.hpp"

using namespace phys::units;

int main()
{
    quantity speed = 45 * kilo() * meter() / second();
}
```

Other libraries
-----------------

- [PhysUnits-CT](https://github.com/martinmoene/PhysUnits-CT) - Compile-time companion of this library.  
- [PhysUnits-CT-Cpp11](https://github.com/martinmoene/PhysUnits-CT-Cpp11) - C++11 compile-time companion of this library.  
- [Boost.Units](http://www.boost.org/doc/libs/1_51_0/libs/units/) - Zero-overhead dimensional analysis and unit/quantity manipulation and conversion in C++.  
- [unitscpp](http://code.google.com/p/unitscpp/) - A lightweight C++ library for physical calculation with units.  

Usage
-------

### Definition of terms

Adapted from Boost.Units:
- <b>Base dimension</b>: A base dimension is loosely defined as a measurable entity of interest; in conventional dimensional analysis, base dimensions include length ([L]), mass ([M]), time ([T]), etc.. Base dimensions are essentially a tag type and provide no dimensional analysis functionality themselves.
- <b>Dimension</b>: A collection of zero or more base dimensions, each potentially raised to a different rational power. For example, length = [L]^1, area = [L]^2, velocity = [L]^1/[T]^1, and energy = [M]^1 [L]^2/[T]^2 are all dimensions.
- <b>Base unit</b>: A base unit represents a specific measure of a dimension. For example, while length is an abstract measure of distance, the meter is a concrete base unit of distance. Conversions are defined using base units. Much like base dimensions, base units are a tag type used solely to define units and do not support dimensional analysis algebra.
- <b>Unit</b>: A set of base units raised to rational exponents, e.g. m^1, kg^1, m^1/s^2.
- <b>System</b>: A unit system is a collection of base units representing all the measurable entities of interest for a specific problem. For example, the SI unit system defines seven base units : length ([L]) in meters, mass ([M]) in kilograms, time ([T]) in seconds, current ([I]) in amperes, temperature ([theta]) in kelvin, amount ([N]) in moles, and luminous intensity ([J]) in candelas. All measurable entities within the SI system can be represented as products of various integer or rational powers of these seven base units.
- <b>Quantity</b>: A quantity represents a concrete amount of a unit. Thus, while the meter is the base unit of length in the SI system, 5.5 meters is a quantity of length in that system.

### Limitations

This library only supports the use of the <em>SI unit system</em>. Note however that the library does provide a fixed number (10) of extension dimensions that you can assign names to.

This library only supports <em>integral powers</em> of the dimensions.

The <em>representation or value type</em> in the implementation of quantity is fixed and cannot be defined separately for each quantity. However you can change the type for all uses within a translation unit by defining `PHYS_UNITS_REP_TYPE` before inclusion of header quantity.hpp. Default this type is `double`.

### Output

The following example shows the quantity type in the computation of work from force and distance and the printing of the result on standard output.

```C++
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
    quantity      F ( 2.0 * newton());  // Define a quantity of force.
    quantity      dx( 2.0 * meter() );  // and a distance,
    quantity      E ( work( F, dx ) );  // and calculate the work done.

    std::cout << "F  = " << F  << std::endl
              << "dx = " << dx << std::endl
              << "E  = " << E  << std::endl;
}
```

The output produced is:

```Text
F  = 2 N
dx = 2 m
E  = 4 J
```

The following example demonstrates printing in default floating point notation and in [engineering notation](http://en.wikipedia.org/wiki/Engineering_notation), using [metric prefixes](http://en.wikipedia.org/wiki/Metric_prefix).

```C++
#include <iostream>

#include "phys/units/io.hpp"
#include "phys/units/quantity.hpp"

using namespace phys::units;

int main()
{
    quantity R( 4.7 * kilo() * volt() / ampere() );

    {
        using namespace phys::units::io;
        std::cout << "R = " << R << std::endl;
    }
    {
        using namespace phys::units::io::eng;
        std::cout << "R = " << R << std::endl;
    }
}
```

The output produced is:

```Text
R = 4700 Ohm
R = 4.7 kOhm
```

See namespaces `io` and `io::eng` for further information.

Instead of unit names such as J, you can also obtain the unit expressed in base dimensions.

```C++
#include <iostream>

#include "phys/units/io.hpp"
#include "phys/units/quantity.hpp"

using namespace phys::units;
using namespace phys::units::io;

int main()
{
    std::cout << "J = " << to_base_unit_symbols( joule() ) << std::endl;
}
```

The output produced is:

```Text
J = m+2 kg s-2
```

### Unit name extension

There are ten extension dimensions available: `extra_x0_d..extra_x9_d`. You can define names for these dimensions on a first come, first serve basis. The following example demonstrates the extension with a new unit (dimension) named `Foo`.

```C++
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
```

The output produced is:

```Text
O = 1 Ohm
F = 1 Foo
```

If you only want to make a limited number of self-defined unit names available, you can predefine these via for example `unit("Foo", extend())` and omit parameter `extend()` from further calls to `unit()` and `to_quantity()`.

### Input

A textual specification of a quantity can be converted to a quantity via function `to_quantity()` as the following example demonstrates.

```C++
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
```

The output produced is:

```Text
quantity = 3 Wb
quantity = 4
quantity = 5 Foo
```

Recognized quantity formats are for example: 1 m, 1 m2, 1 m/s, 1 m/s2, 1 (4 cm)2, 33 Hz, 33 1/s. If the magnitude is omitted, it is taken to be 1. To prevent misinterpretation with self-defined unit names, an escape character can be used as in: !foo , f!foo (same as ffoo).

Internally `to_quantity()` uses class `quantity_parser`.

### Convenience functions

There are several convenience functions, such as:

- `to_quantity(std::string text)` - the text, such as '9.8 m/s2' converted to quantity.
- `to_unit(std::string text)`- the text, such as '45 km/h' converted to quantity representing the unit as '1 km/h'.
- `to_numerical_value(std::string text)` - the text, such as '45 km/h' converted to value as '45'
- `magnitude(quantity const & q)` - the quantity's magnitude, e.g. 1000 for 1 km.
- `dimension(quantity const & q)` - the quantity's dimension, e.g. m/s for 1 km/h.
- `to_unit_symbol(quantity const &q, name_symbol use)` - the quantity's unit symol(s), for example 'm s-2'.
- `to_real(quantity const &q)` - a dimensionless quantity's magnitude as floating point value.
- `to_integer(quantity const &q)` - a dimensionless quantity's magnitude as integral value.

### Error handling

Exceptions are used to signal errors in expressions that use incompatible dimensions and for several error conditions related to handling the textual representation of a quantity.

The following example demonstrates simple error handling that prints the message provided by the exception.

```C++
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
```

The output produced is:

```
Error: quantity: parsing unit '3 m/s/s': repetition of solidus at position 6: use parenthesis to avoid ambiguity
```

For an example that uses `quantity_parser_error` from the quantity exception hierarchy, see the error handling in the program [PhysUnits.cpp](https://svn.eld.leidenuniv.nl/repos/eld-moene/PhysUnitsRT/trunk/projects/PhysUnits/PhysUnits.cpp), function `void interactive()`.

### Mixing run-time and compile-time libraries
Although this library seems to be in the `phys::units` namespace, it does so through *using* the `rt` namespace in the global namespace. So this library actually lives in the `rt::phys::units` namespace. When you want to mix this library with its compile-time companion, the `rt` namespace must be applied. This can be accomplished by defining `PHYS_UNITS_IN_RT_NAMESPACE`.

Dependencies
--------------

This library has no dependencies other than the standard C++ libraries.

Performance
-------------

```Text
Relative running time (lower is better)

Compiler        Option : double : quantity
-----------------------+--------+-------------
GCC 4.6.2         -O2  :  1     :  222 (1)
MS VC6/VS6        -O2  :  0.83  :  396 (1.8)
MS VC8/VS2005     -O2  :  0.83  :  269 (1.2)
MS VC2010/VS2010  -O2  :  0.66  :  391 (1.8)

Measured on a AMD Athlon 64 X2 Dual Core Processor 5600+, 64kB L1 Data, 64kB L1 Instruction, 512kB L2, 3.2 GB RAM
```

Compilers known to work
-------------------------

- GCC 4.5.2, 4.6.2
- MS VC6/VS6 - (VC6 lacks ADL).
- MS VC8/VS2005
- MS VC2010/VS2010

Ideas for improvement
-----------------------

Currently the number of extension dimensions is fixed. Perhaps the code can be made to work so that the number of extension dimensions can be specified via a user-defined value of `PHYS_UNITS_QUANTITY_UNIT_EXT_COUNT`.

Allow to specify a conversion offset between two units, e.g. to make conversion between 'C and K possible (see Boost.Units).

It may be nice if you can obtain a quantity in a unit representation of your choice, e.g. in kWh in stead of J [m+2 kg s-2]. See G.S. Novak. [Conversion of units of measurement (PDF)](http://reference.kfupm.edu.sa/content/c/o/conversion_of_units_of_measurement__42431.pdf)". 1 August 1997.

### References

[1] Michael Kenniston. [The Quantity Library](http://home.xnet.com/~msk/quantity/quantity.html). ([Rationale](http://home.xnet.com/%7Emsk/quantity/quantity.html), Quantity [folder](http://www.xnet.com/%7Emsk/quantity)). 16 July 2001, rev 0.4.

[2] Ambler Thompson and Barry N. Taylor. [Guide for the Use of the International System of Units (SI)](http://physics.nist.gov/cuu/pdf/sp811.pdf). NIST Special Publication 811 2008 Edition.
