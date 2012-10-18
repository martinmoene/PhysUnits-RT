#
# ./doxygen/examples/Makefile
#
# Created by Martin on 11 October 2012.
# Copyright 2012 Universiteit Leiden. All rights reserved.
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

RM = rm

SOURCES = hello.cpp work.cpp engineering.cpp extend.cpp base.cpp input.cpp exception.cpp

PROGRAMS = $(SOURCES:.cpp=.exe)

CXXFLAGS = $(CXXFLAGS) -nologo -W3 -EHsc -GX -Ox -I../../../

TARGET = compile
all compile: $(PROGRAMS)

#$(PROGAMS): quantity.hpp io.hpp

clean:
   -$(RM) *.bak

distclean: clean
   -$(RM) *.obj *.exe

#
# implicit rules:
#

.cpp.obj:
        $(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $<

.cpp.exe:
        -$(CXX) $(CXXFLAGS) $(LFLAGS) -Fe$@ $< $(LIBS)
        -$@

#
# end of file
#

