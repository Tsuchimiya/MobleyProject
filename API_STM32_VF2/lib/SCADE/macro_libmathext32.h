/*
 * Copyright (C) 2015 ESTEREL TECHNOLOGIES SAS. ALL RIGHTS RESERVED.
 * This source file may be used and distributed without restriction provided that this copyright statement is not removed from the file and that any derivative work contains this copyright notice.
 * 
 * Warranty
 * ESTEREL TECHNOLOGIES SAS makes no warranty of any kind with regard to the use of this Software, either expressed or implied, including, but not limited to the fitness for a particular purpose.
 */


/*
 * macro_libmathext32.h
 *
 * Copyright(c) 2003-2014 Esterel Technologies
 *
 *
 */

#include <math.h>
#include "kcg_types.h"


/* Inverse hyperbolic cosine */
#define AcoshR32_mathext_mathextimpl(In) ((kcg_float32) log((float) In +sqrt((((float) In) * ((float) In)) - 1.0)))

/* Inverse Cosine */
#define AcosR32_mathext_mathextimpl(In) ((kcg_float32) acos((float) In))

/* Inverse hyperbolic sine */
/*	The Result is slightly different from Simulink result
	Difference is of kind  E-13 
	(for big input (for example E4) difference is of kind E-8) */
#define AsinhR32_mathext_mathextimpl(In) ((kcg_float32) log(((float) In) + sqrt(1.0 + (((float) In) * ((float) In)))))


/* Inverse sine */
#define AsinR32_mathext_mathextimpl(In) ((kcg_float32) asin((float) In))

/* Inverse hyperbolic tangent */
#define AtanhR32_mathext_mathextimpl(In) ((kcg_float32) (0.5 * log((1 + ((float) In)) / (1 - ((float) In)))))

/* Inverse tangent */
#define AtanR32_mathext_mathextimpl(In) ((kcg_float32) atan((float) In))

/* Four quadrant inverse tangent */
#define Atan2R32_mathext_mathextimpl(In1, In2) ((kcg_float32) atan2((float) In1, (float) In2))


/* Hyperbolic cosine */
#define CoshR32_mathext_mathextimpl(In) ((kcg_float32) cosh((float) In))

/* Cosine */
#define CosR32_mathext_mathextimpl(In) ((kcg_float32) cos((float) In))

/* Exponential */
#define ExpR32_mathext_mathextimpl(In) ((kcg_float32) exp((float) In))

/* Logarithm with base e */
#define LnR32_mathext_mathextimpl(In) ((kcg_float32) log((float) In))

/* Logarithm with base 10 */
#define LogR32_mathext_mathextimpl(In) ((kcg_float32) log10((float) In))

/* Power */
#define PowerI_mathext(In, Power)  ((kcg_int32) pow((float) In, (float) Power))
#define PowerR32_mathext_mathextimpl(In, Power)  ((kcg_float32) pow((float) In, (float) Power))
/* Note: In SCADE 5.1, there was an assert in simulation mode to check validity of parameters.  */
/*       In SCADE 6.0, this operator will likely end-up not being an imported operator anymore. */
#define PowerRR32_mathext_mathextimpl(In, Power) ((kcg_float32) pow((float) In, (float) Power))


/* Hyperbolic sine */
#define SinhR32_mathext_mathextimpl(In) ((kcg_float32) sinh((float) In))

/* Sine */
#define SinR32_mathext_mathextimpl(In) ((kcg_float32) sin((float) In))

/* Sqrt */
#define SqrtR32_mathext_mathextimpl(In) ((kcg_float32) sqrt((float) In))


/* Tangent */
#define TanR32_mathext_mathextimpl(In) ((kcg_float32) tan((float) In))

/* Hyperbolic tangent */
#define TanhR32_mathext_mathextimpl(In) ((kcg_float32) tanh((float) In))

/* 10^x */
#define TenPowR32_mathext_mathextimpl(In) ((kcg_float32) pow((float) 10, (float) In))
