#ifndef __c4_commusrp2FMStereo_h__
#define __c4_commusrp2FMStereo_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
typedef struct {
  SimStruct *S;
  real32_T c4_pilot_delay[2];
  boolean_T c4_pilot_delay_not_empty;
  uint8_T c4_is_active_c4_commusrp2FMStereo;
  ChartInfoStruct chartInfo;
} SFc4_commusrp2FMStereoInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c4_commusrp2FMStereo_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c4_commusrp2FMStereo_get_check_sum(mxArray *plhs[]);
extern void c4_commusrp2FMStereo_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
