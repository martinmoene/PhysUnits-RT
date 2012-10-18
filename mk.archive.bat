@echo off & setlocal enableextensions
::
:: mk.archive.bat - export git working copy and create
::                  compressed tar file in parent directory.
::

set RELEASE=1.0.0
set DATE=20121018

git archive --format tar --output ../PhysUnits-RT-%RELEASE%-%DATE%.tar.gz master

endlocal & goto :EOF

::
:: end of file
::
