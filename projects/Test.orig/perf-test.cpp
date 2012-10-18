//
//      perf-test.cpp - performance test for quantity library
//
//	Copyright (c) 2001 by Michael S. Kenniston.  The most recent
//	version will be available at www.xnet.com/~msk/quantity.  Permission is granted
//	to use this code without restriction so long as this copyright
//	notice appears in all source files.

//	This code is provided as-is, with no warrantee of correctness.

/*
	This program tests the quantity library to verify that the
	performance of quantity computations is the same as that of
	the underlying double operations.
*/

#include "phys/units/quantity.hpp"
#include "phys/units/io_output.hpp"

#include <iostream>
#include <time.h>

using namespace phys::units;
using namespace phys::units::io;
using namespace std;

const int meg = 1000000;
const int k = 10; // 60; // scale factor - make it bigger for faster machines

template< typename T1, typename T2, typename T3 >
T1 do_work( T1 v1, T2 v2, T3 v3 )
{
	// Do a bunch of work.  We don't really care about the answer;
	// this is just to exercise addition, subtraction, multiplication, and division.
	T1 x1 = v1;
	T2 x2 = v2;
	T3 x3 = v3;
	for( int i = 0; i < meg; i++ )
	{
		for( int j = 0; j < k; j++ )
		{
			x2 = -x2 - v2;
			x3 *= 1.00002;
			x1 += x2 / x3;
		}
	}
	return x1;
}

quantity flip()
{
	return ( siemens() );
}

const quantity biga( 2 * ohm() );
const quantity bigb( siemens() / 2 );

quantity do_more_work(
			quantity v1,
			quantity v2,
			quantity v3 )
{
	// Do a bunch of work.  We don't really care about the answer;
	// this is just to exercise addition, subtraction, multiplication, and division.
	quantity x1 = v1;
	quantity x2 = v2;
	quantity x3 = v3;
	for( int i = 0; i < meg; i++ )
	{
		for( int j = 0; j < k; j++ )
		{
			x2 = -x2 - v2;
			x3 *= to_real( biga * 1.00002 * bigb );
			x1 += x2 / x3;
		}
	}
	return x1;
}

int main()
{
   cout << "Performance test of run-time quantity library." << endl;

	clock_t t0 = clock();

	// do some work with doubles
	volatile double d = do_work( 0.1, 0.2, 0.3 );

	clock_t t1 = clock();

	// do exact same work with quantity
	quantity s = do_work( 0.1*meter()/second(), 0.2*meter(), 0.3*second() );

	clock_t t2 = clock();

	quantity s2 = do_more_work( 0.1*meter()/second(), 0.2*meter(), 0.3*second() );

	clock_t t3 = clock();

	const double cps = CLOCKS_PER_SEC;
	cout << "one double work loop =     " << (t1-t0)/cps/k << " usec" << endl;
	cout << "one quantity work loop =   " << (t2-t1)/cps/k << " usec " << endl;
	cout << "one quantity++ work loop = " << (t3-t2)/cps/k << " usec " << endl;

	cout << "d = " << d << endl;
	cout << "s = " << s << endl;

    return 0;
}
