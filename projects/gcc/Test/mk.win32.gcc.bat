@echo off & setlocal
::
:: Created by Martin on 16 September 2012.
::
:: Compile PhysUnits tests, GNUC
::

if [%CATCH_INCLUDE%] == [] goto :CATCH_ERROR

mingw32-make.exe -f Makefile.win32.gcc %*
goto :EOF

:CATCH_ERROR
echo Error: Please specify environment variable CATCH_INCLUDE to point to the Catch test framework include directory.
echo Catch: https://github.com/philsquared/Catch
echo Catch-VC6: https://github.com/martinmoene/Catch
exit /b 1

endlocal

::
:: End of file
::
