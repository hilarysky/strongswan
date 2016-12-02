/*
 * Copyright (C) 2016 Andreas Steffen
 * HSR Hochschule fuer Technik Rapperswil
 *
 * Based on the public domain libsodium adaptation by Frank Denis
 * of the SUPERCOP ref10 implementation by  Daniel J. Bernstein,
 * Niels Duif, Peter Schwabe, Tanja Lange and Bo-Yin Yang.
 */

#include <stddef.h>
#include <stdint.h>

#include "verify_32.h"

int verify_32(const uint8_t *x, const uint8_t *y)
{
	uint_fast16_t d = 0U;
	int i;

	for (i = 0; i < 32; i++)
	{
		d |= x[i] ^ y[i];
	}
	return (1 & ((d - 1) >> 8)) - 1;
}
