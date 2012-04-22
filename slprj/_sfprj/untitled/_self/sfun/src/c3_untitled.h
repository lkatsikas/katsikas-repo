#ifndef __c3_untitled_h__
#define __c3_untitled_h__

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
} c3_ResolvedFunctionInfo;

typedef struct {
  SimStruct *S;
  int32_T c3_sfEvent;
  real32_T c3_prev_out[64];
  uint32_T chartNumber;
  uint32_T instanceNumber;
  boolean_T c3_doneDoubleBufferReInit;
  boolean_T c3_isStable;
  boolean_T c3_prev_out_not_empty;
  uint8_T c3_is_active_c3_untitled;
  ChartInfoStruct chartInfo;
} SFc3_untitledInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c3_untitled_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c3_untitled_get_check_sum(mxArray *plhs[]);
extern void c3_untitled_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
