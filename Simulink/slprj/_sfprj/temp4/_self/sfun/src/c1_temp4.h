#ifndef __c1_temp4_h__
#define __c1_temp4_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
typedef struct {
  SimStruct *S;
  int32_T c1_sfEvent;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  boolean_T c1_doneDoubleBufferReInit;
  boolean_T c1_isStable;
  uint8_T c1_is_active_c1_temp4;
  ChartInfoStruct chartInfo;
} SFc1_temp4InstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_temp4_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_temp4_get_check_sum(mxArray *plhs[]);
extern void c1_temp4_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
