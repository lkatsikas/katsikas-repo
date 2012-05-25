#ifndef __c2_sdruFRSGMRSTx_h__
#define __c2_sdruFRSGMRSTx_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
typedef struct {
  SimStruct *S;
  real_T c2_frs_Fs;
  real_T c2_frs_toneFreqs[38];
  real_T c2_t0;
  int32_T c2_sfEvent;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  boolean_T c2_doneDoubleBufferReInit;
  boolean_T c2_isStable;
  boolean_T c2_t0_not_empty;
  uint8_T c2_is_active_c2_sdruFRSGMRSTx;
  ChartInfoStruct chartInfo;
} SFc2_sdruFRSGMRSTxInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_sdruFRSGMRSTx_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_sdruFRSGMRSTx_get_check_sum(mxArray *plhs[]);
extern void c2_sdruFRSGMRSTx_method_dispatcher(SimStruct *S, int_T method, void *
  data);

#endif
