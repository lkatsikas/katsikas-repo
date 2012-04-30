#ifndef __commusrp2FMStereo_sfun_h__
#define __commusrp2FMStereo_sfun_h__

/* Include files */
#define S_FUNCTION_NAME                sf_sfun
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"
#define rtInf                          (mxGetInf())
#define rtMinusInf                     (-(mxGetInf()))
#define rtNaN                          (mxGetNaN())
#define rtIsNaN(X)                     ((int)mxIsNaN(X))
#define rtIsInf(X)                     ((int)mxIsInf(X))

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */
extern real_T _sfTime_;

/* Variable Definitions */

/* Function Declarations */
extern void commusrp2FMStereo_initializer(void);
extern void commusrp2FMStereo_terminator(void);

/* Function Definitions */
#endif
