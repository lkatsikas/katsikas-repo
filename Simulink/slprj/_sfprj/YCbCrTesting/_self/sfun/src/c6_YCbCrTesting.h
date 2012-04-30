#ifndef __c6_YCbCrTesting_h__
#define __c6_YCbCrTesting_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
typedef struct {
  const char * context;
  const char * name;
  const char * dominantType;
  const char * resolved;
  uint32_T fileTimeLo;
  uint32_T fileTimeHi;
  uint32_T mFileTimeLo;
  uint32_T mFileTimeHi;
} c6_ResolvedFunctionInfo;

typedef struct {
  SimStruct *S;
  real32_T c6_prev_out[64];
  boolean_T c6_prev_out_not_empty;
  uint8_T c6_is_active_c6_YCbCrTesting;
  ChartInfoStruct chartInfo;
} SFc6_YCbCrTestingInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c6_YCbCrTesting_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c6_YCbCrTesting_get_check_sum(mxArray *plhs[]);
extern void c6_YCbCrTesting_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
