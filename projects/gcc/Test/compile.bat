@echo off & setlocal
::
:: Created by Martin on 13 October 2012.
::
:: Compile PhysUnits tests, GNUC
::

set G_OPT=-DPHYS_UNITS_IN_RT_NAMESPACE

if [%CATCH_INCLUDE%] == [] goto :CATCH_ERROR

if [%1] == [-h] goto :USAGE
if [%1] == [help] goto :USAGE
if [%1] == [all] goto :ALL
if [%1] == [default] goto :DEFAULT
if [%1] == [optimize] goto :OPTIMIZE
if [%1] == [debug] goto :DEBUG
if not [%1] == [] goto :USAGE
goto :DEFAULT

:ALL
echo Default build:   && call :DEFAULT &&^
echo Optimized build: && call :OPTIMIZE &&^
echo Debug build:     && call :DEBUG
goto :EOF

:DEFAULT
call :COMPILE
goto :EOF

:OPTIMIZE
call :AWHILE
call :COMPILE -O2
goto :EOF

:DEBUG
call :COMPILE -MDd -D_DEBUG
goto :EOF

:COMPILE
setlocal
set OPT=%*
g++ -Wall %G_OPT% %OPT% -I../../../ -I%CATCH_INCLUDE% -o Test.exe ../../Test/Test.cpp ../../Test/TestArithmetic.cpp ../../Test/TestComparison.cpp ../../Test/TestCompile.cpp ../../Test/TestFunction.cpp ../../Test/TestInput.cpp ../../Test/TestOutput.cpp ../../Test/TestPrefix.cpp ../../Test/TestUnit.cpp && Test
endlocal & goto :EOF

:CATCH_ERROR
echo Error: Please specify environment variable CATCH_INCLUDE to point to the Catch test framework include directory.
echo Catch: https://github.com/philsquared/Catch
echo Catch-VC6: https://github.com/martinmoene/Catch
exit /b 1

:AWHILE
echo.
echo This is going to take a while...
echo.
goto :EOF

:USAGE
echo Usage: %0 [-h] [default] [optimize] [debug] [all] {-bo}
goto :EOF

endlocal

::
:: End of file
::
