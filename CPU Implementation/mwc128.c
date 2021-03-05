/*  Written in 2021 by Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include <stdint.h>

/* This is a Marsaglia multiply-with-carry generator with period
   approximately 2^127. It is close in speed to a scrambled linear
   generator, as its only 128-bit operations are a multiplication and sum;
   is an excellent generator based on congruential arithmetic.

   As all MWC generators, it simulates a multiplicative LCG with
   prime modulus m = 0xff3a275c007b8ee5ffffffffffffffff and
   multiplier given by the inverse of 2^64 modulo m. The modulus has a
   particular form, which creates some theoretical issues, but at this
   size a generator of this kind passes all known statistical tests. For a
   generator of the same type with stronger theoretical guarantees
   consider a Goresky-Klapper generalized multiply-with-carry generator.
*/

/* The state must be neither all zero, nor x = 2^64 - 1, c = MWC_A1 -
   1. The condition 0 < c < MWC_A1 - 1 is thus sufficient. */

uint64_t x, c = 1;

#define MWC_A1 0xff3a275c007b8ee6

uint64_t inline next() {
	const __uint128_t t = MWC_A1 * (__uint128_t)x + c;
	c = t >> 64;
	return x = t;
}