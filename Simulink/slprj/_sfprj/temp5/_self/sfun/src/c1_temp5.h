#ifndef __c1_temp5_h__
#define __c1_temp5_h__

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
} c1_ResolvedFunctionInfo;

#ifndef struct_struct_xiTGusujfWbfyD0i7ym1G_tag
#define struct_struct_xiTGusujfWbfyD0i7ym1G_tag

typedef struct struct_xiTGusujfWbfyD0i7ym1G_tag
{
  real_T alpha;
  real_T w[1705];
  real_T continual_pilots[45];
  real_T tps_signals[17];
  real_T scattered_set[142];
  real_T pilot_set[11968];
} c1_struct_xiTGusujfWbfyD0i7ym1G;

#else

typedef struct struct_xiTGusujfWbfyD0i7ym1G_tag c1_struct_xiTGusujfWbfyD0i7ym1G;

#endif

typedef struct {
  c1_struct_xiTGusujfWbfyD0i7ym1G c1_VAR;
  SimStruct *S;
  int32_T c1_sfEvent;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  boolean_T c1_doneDoubleBufferReInit;
  boolean_T c1_isStable;
  uint8_T c1_is_active_c1_temp5;
  ChartInfoStruct chartInfo;
} SFc1_temp5InstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_temp5_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_temp5_get_check_sum(mxArray *plhs[]);
extern void c1_temp5_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
