#ifndef __c2_commusrp2FMStereo_h__
#define __c2_commusrp2FMStereo_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
typedef struct {
  SimStruct *S;
  uint8_T c2_is_active_c2_commusrp2FMStereo;
  ChartInfoStruct chartInfo;
} SFc2_commusrp2FMStereoInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_commusrp2FMStereo_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c2_commusrp2FMStereo_get_check_sum(mxArray *plhs[]);
extern void c2_commusrp2FMStereo_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
