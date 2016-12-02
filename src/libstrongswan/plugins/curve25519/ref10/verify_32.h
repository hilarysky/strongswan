/*
 * Copyright (C) 2016 Andreas Steffen
 * HSR Hochschule fuer Technik Rapperswil
 *
 * Based on the public domain libsodium adaptation by Frank Denis
 * of the SUPERCOP ref10 implementation by  Daniel J. Bernstein,
 * Niels Duif, Peter Schwabe, Tanja Lange and Bo-Yin Yang.
 */

#ifndef VERIFY_32_H
#define VERIFY_32_H

#include <stddef.h>

#include "export.h"

#define crypto_verify_32_BYTES 32U
SODIUM_EXPORT
size_t crypto_verify_32_bytes(void);

SODIUM_EXPORT
int verify_32(const uint8_t *x, const uint8_t *y)
			  __attribute__ ((warn_unused_result));

#endif
