#ifndef __c15_YCbCrTesting_h__
#define __c15_YCbCrTesting_h__

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
} c15_ResolvedFunctionInfo;

typedef struct {
  SimStruct *S;
  uint32_T c15_prev_out[20];
  boolean_T c15_prev_out_not_empty;
  uint8_T c15_is_active_c15_YCbCrTesting;
  ChartInfoStruct chartInfo;
} SFc15_YCbCrTestingInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c15_YCbCrTesting_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c15_YCbCrTesting_get_check_sum(mxArray *plhs[]);
extern void c15_YCbCrTesting_method_dispatcher(SimStruct *S, int_T method, void *
  data);

#endif
