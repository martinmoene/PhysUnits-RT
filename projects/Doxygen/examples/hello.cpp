#include "phys/units/quantity.hpp"

using namespace phys::units;

int main()
{
    quantity speed = 45 * kilo() * meter() / second();
}
