/**
 * \file regrtest2.cpp
 *
 * \brief   regression test for Quantity library.
 * \author  Michael S. Kenniston
 * \date    16 July 2001
 * \since   0.4
 *
 * Copyright (c) 2001 by Michael S. Kenniston.  For the most
 * recent version check www.xnet.com/~msk/quantity.  Permission is granted
 * to use this code without restriction so long as this copyright
 * notice appears in all source files.
 *
 * This code is provided as-is, with no warrantee of correctness.
 *
 * This program tests all the features of the Quantity Library
 * that are /not/ supposed to work, i.e. the things that should be
 * caught as errors at compiler-time.  It is intended to be
 * compiled with -DFAIL_1, -DFAIL_2, etc. and should fail the compile
 * every time.
 */

#define PHYS_UNITS_REP_TYPE double

#include "phys/units/quantity.hpp"
#include "phys/units/io_output.hpp"
#include "phys/units/other_units.hpp"
#include "phys/units/physical_constants.hpp"

#include "user_example.hpp"

#include <iostream>
#include <cstdlib>

using namespace std;
using namespace phys::units;
using namespace phys::units::io;

int main()
{
    quantity qp( 2 * watt() );
    quantity qe( 3 * joule() );
    Rep x( 5.6 );
    bool b( true );

    // comparisons

    #ifdef FAIL_1
        b = ( qp == qe );
    #endif

    #ifdef FAIL_2
        b = ( qp != qe );
    #endif

    #ifdef FAIL_3
        b = ( qp <= qe );
    #endif

    #ifdef FAIL_4
        b = ( qp >= qe );
    #endif

    #ifdef FAIL_5
        b = ( qp < qe );
    #endif

    #ifdef FAIL_6
        b = ( qp > qe );
    #endif

    #ifdef FAIL_7
        b = ( qp == 1.0 );
    #endif

    #ifdef FAIL_8
        b = ( qp != 1.0 );
    #endif

    #ifdef FAIL_9
        b = ( qp <= 1.0 );
    #endif

    #ifdef FAIL_10
        b = ( qp >= 1.0 );
    #endif

    #ifdef FAIL_11
        b = ( qp < 1.0 );
    #endif

    #ifdef FAIL_12
        b = ( qp > 1.0 );
    #endif

    #ifdef FAIL_13
        b = ( 1.0 == qp );
    #endif

    #ifdef FAIL_14
        b = ( 1.0 != qp );
    #endif

    #ifdef FAIL_15
        b = ( 1.0 <= qp );
    #endif

    #ifdef FAIL_16
        b = ( 1.0 >= qp );
    #endif

    #ifdef FAIL_17
        b = ( 1.0 < qp );
    #endif

    #ifdef FAIL_18
        b = ( 1.0 > qp );
    #endif

    // undefined units

    #ifdef FAIL_19
        cout << kings_foot() << "\n";
    #endif

    // constructors

    #ifdef FAIL_20
        quantity< length_d > ql( 1.0 );
    #endif

    #ifdef FAIL_21
        quantity< length_d > ql( quantity< mass_d >::zero() );
    #endif

    // assignment

    #ifdef FAIL_22
        qp = qe;
    #endif

    #ifdef FAIL_23
        qp = x;
    #endif

    #ifdef FAIL_24
        x = qp;
    #endif

    // addition

    #ifdef FAIL_25
        qp += x;
    #endif

    #ifdef FAIL_26
        qp += qe;
    #endif

    #ifdef FAIL_27
        x += qe;
    #endif

    #ifdef FAIL_28
        qp ++;
    #endif

    #ifdef FAIL_29
        ++ qp;
    #endif

    #ifdef FAIL_30
        cout << qp + x;
    #endif

    #ifdef FAIL_31
        cout << x + qp;
    #endif

    #ifdef FAIL_32
        cout << qp + qe;
    #endif

    // subtraction

    #ifdef FAIL_33
        qp -= x;
    #endif

    #ifdef FAIL_34
        qp -= qe;
    #endif

    #ifdef FAIL_35
        x -= qe;
    #endif

    #ifdef FAIL_36
        qp --;
    #endif

    #ifdef FAIL_37
        -- qp;
    #endif

    #ifdef FAIL_38
        cout << qp - x;
    #endif

    #ifdef FAIL_39
        cout << x - qp;
    #endif

    #ifdef FAIL_40
        cout << qp - qe;
    #endif

    // multiplication

    #ifdef FAIL_41
        qp *= qe;
    #endif

    #ifdef FAIL_42
        x *= qp;
    #endif

    // division

    #ifdef FAIL_43
        qp /= qe;
    #endif

    #ifdef FAIL_44
        x /= qp;
    #endif

    // roots

    #ifdef FAIL_45
        cout << sqrt( qp );
    #endif

    #ifdef FAIL_46
        cout << nth_root( meter(), 0 );
    #endif

    #ifdef FAIL_461
        cout << nth_root( meter(), 3 );
    #endif

    #ifdef FAIL_47
        cout << nth_root( meter() * meter() * meter() * meter() * second() * second() * second(), 4 );
    #endif

    // misc syntax errors

    #ifdef FAIL_48
        qp = watt;
    #endif

    #ifdef FAIL_49
        qp = 4 * watt;
    #endif

    #ifdef FAIL_50
        quantity< dimensions< 0, 0, 0 > > dimensionless;
    #endif

    #ifdef FAIL_501
        quantity< dimensionless_d > dimensionless;
    #endif

    #ifdef FAIL_51
        quantity< quantity< dimensions< 1, 1, 1 > > > nested;
    #endif

    #ifdef FAIL_52
        quantity< double > nodimsatall;
    #endif

    return 0;
}

/*
 * end of file
 */

