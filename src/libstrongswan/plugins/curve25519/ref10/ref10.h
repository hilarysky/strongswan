/*
 * Copyright (C) 2016 Andreas Steffen
 * HSR Hochschule fuer Technik Rapperswil
 *
 * Based on the public domain libsodium adaptation by Frank Denis
 * of the SUPERCOP ref10 implementation by  Daniel J. Bernstein,
 * Niels Duif, Peter Schwabe, Tanja Lange and Bo-Yin Yang.
 */

#ifndef REF10_H_
#define REF10_H_

#include <stddef.h>
#include <stdint.h>

typedef int32_t fe[10];

/**
 * fe means field element.
 * Here the field is \Z/(2^255-19).
 * An element t, entries t[0]...t[9], represents the integer
 * t[0]+2^26 t[1]+2^51 t[2]+2^77 t[3]+2^102 t[4]+...+2^230 t[9].
 * Bounds on each t[i] vary depending on context.
 */

extern void fe_frombytes(fe,const uint8_t *);
extern void fe_tobytes(uint8_t *, const fe);

extern void fe_copy(fe, const fe);
extern int  fe_isnonzero(const fe);
extern int  fe_isnegative(const fe);
extern void fe_0(fe);
extern void fe_1(fe);
extern void fe_cmov(fe, const fe, unsigned int);
extern void fe_add(fe, const fe, const fe);
extern void fe_sub(fe, const fe, const fe);
extern void fe_neg(fe, const fe);
extern void fe_mul(fe, const fe, const fe);
extern void fe_sq(fe, const fe);
extern void fe_sq2(fe, const fe);
extern void fe_invert(fe, const fe);
extern void fe_pow22523(fe, const fe);

/**
 * ge means group element.
 *
 * Here the group is the set of pairs (x,y) of field elements (see fe.h)
 * satisfying -x^2 + y^2 = 1 + d x^2y^2
 * where d = -121665/121666.
 *
 * Representations:
 * ge_p2 (projective): (X:Y:Z) satisfying x=X/Z, y=Y/Z
 * ge_p3 (extended): (X:Y:Z:T) satisfying x=X/Z, y=Y/Z, XY=ZT
 * ge_p1p1 (completed): ((X:Z),(Y:T)) satisfying x=X/Z, y=Y/T
 * ge_precomp (Duif): (y+x,y-x,2dxy)
 */

typedef struct {
	fe X;
	fe Y;
	fe Z;
} ge_p2;

typedef struct {
	fe X;
	fe Y;
	fe Z;
	fe T;
} ge_p3;

typedef struct {
	fe X;
	fe Y;
	fe Z;
	fe T;
} ge_p1p1;

typedef struct {
	fe yplusx;
	fe yminusx;
	fe xy2d;
} ge_precomp;

typedef struct {
	fe YplusX;
	fe YminusX;
	fe Z;
	fe T2d;
} ge_cached;

extern void ge_tobytes(uint8_t *, const ge_p2 *);
extern void ge_p3_tobytes(uint8_t *, const ge_p3 *);
extern  int ge_frombytes_negate_vartime(ge_p3 *, const uint8_t *);

extern void ge_p2_0(ge_p2 *);
extern void ge_p3_0(ge_p3 *);
extern void ge_precomp_0(ge_precomp *);
extern void ge_p3_to_p2(ge_p2 *, const ge_p3 *);
extern void ge_p3_to_cached(ge_cached *, const ge_p3 *);
extern void ge_p1p1_to_p2(ge_p2 *, const ge_p1p1 *);
extern void ge_p1p1_to_p3(ge_p3 *, const ge_p1p1 *);
extern void ge_p2_dbl(ge_p1p1 *, const ge_p2 *);
extern void ge_p3_dbl(ge_p1p1 *, const ge_p3 *);

extern void ge_madd(ge_p1p1 *, const ge_p3 *, const ge_precomp *);
extern void ge_msub(ge_p1p1 *,const ge_p3 *, const ge_precomp *);
extern void ge_add(ge_p1p1 *, const ge_p3 *, const ge_cached *);
extern void ge_sub(ge_p1p1 *, const ge_p3 *, const ge_cached *);
extern void ge_scalarmult_base(ge_p3 *, const uint8_t *);
extern void ge_double_scalarmult_vartime(ge_p2 *, const uint8_t *,
			const ge_p3 *, const uint8_t *);
extern void ge_scalarmult_vartime(ge_p3 *, const uint8_t *, const ge_p3 *);

/**
 * The set of scalars is \Z/l
 * where l = 2^252 + 27742317777372353535851937790883648493.
 */

extern void sc_reduce(uint8_t *);
extern void sc_muladd(uint8_t *, const uint8_t *, const uint8_t *, const uint8_t *);

#endif /** REF10_H_ */
