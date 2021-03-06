/*
 * Copyright (C) 2015  University of Oregon
 *
 * You may distribute under the terms of either the GNU General Public
 * License or the Apache License, as specified in the README file.
 *
 * For more information, see the README file.
 */
/* dv7scl.f -- translated by f2c (version 20090411).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/* Subroutine */ int dv7scl_(integer *n, doublereal *x, doublereal *a, 
	doublereal *y)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__;


/*  ***  SET X(I) = A*Y(I), I = 1(1)N  *** */



    /* Parameter adjustments */
    --y;
    --x;

    /* Function Body */
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L10: */
	x[i__] = *a * y[i__];
    }
/* L999: */
    return 0;
/*  ***  LAST LINE OF DV7SCL FOLLOWS  *** */
} /* dv7scl_ */

