#ifndef __c2_sdruFMStereo_h__
#define __c2_sdruFMStereo_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
typedef struct {
  SimStruct *S;
  uint8_T c2_is_active_c2_sdruFMStereo;
  ChartInfoStruct chartInfo;
} SFc2_sdruFMStereoInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_sdruFMStereo_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_sdruFMStereo_get_check_sum(mxArray *plhs[]);
extern void c2_sdruFMStereo_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
