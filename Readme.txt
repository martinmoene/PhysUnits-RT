Readme for Runtime Quantity C++ Library.

Runtime dimensional analysis and unit/quantity manipulation and conversion.

See also ReleaseNotes.txt and Readme.orig.txt

Directory structure:

./                      - license, readme, release notes.
./doc                   - quantity.html, rationale.html and weblinks.html
./phys
./phys/units            - Runtime Quantity library headers.
./projects
./projects/CodeBlocks   - CodeBlocks IDE project files
./projects/Doxygen      - doxygen configuration, CHM output
./projects/Doxygen/examples
                        - example programs, Makefile
./projects/gcc
./projects/gcc/Test     - GNUC compilation of Catch test program.
./projects/PhysUnits    - commandline and interactive program to exercise
                          reading and reporting of quantities.
./projects/Test
./projects/Test.orig    - original organization of tests. Compiles.
./projects/Time         - programs for performance timing. Currently empty.
./projects/VS2005
./projects/VS2005/Test  - VC8 compilation of Catch test program.
./projects/VS2010
./projects/VS2010/Test  - VC2010 compilation of Catch test program.
./projects/VS6
./projects/VS6/Test     - VC6 compilation of Catch test program.


Porting status:  All regression tests pass on:

- WinXP-32, Win7-64 / MSVC 6, VS 6
- WinXP-32, Win7-64 / MSVC 8, VS 2005
- WinXP-32, Win7-64 / MSVC 10, VS 2010
- WinXP-32          / g++ (GCC) 4.5.2, 4.6.2
- Win7-64           / g++ (tdm64-1) 4.6.1 (works with float, double;
                      problems with streaming of long double)

___

Last updated 18 October 2012, Martin Moene
