/* Include files */

#include "blascompat32.h"
#include "sdruFMStereo_sfun.h"
#include "c2_sdruFMStereo.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void initialize_c2_sdruFMStereo(SFc2_sdruFMStereoInstanceStruct
  *chartInstance);
static void initialize_params_c2_sdruFMStereo(SFc2_sdruFMStereoInstanceStruct
  *chartInstance);
static void enable_c2_sdruFMStereo(SFc2_sdruFMStereoInstanceStruct
  *chartInstance);
static void disable_c2_sdruFMStereo(SFc2_sdruFMStereoInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_sdruFMStereo
  (SFc2_sdruFMStereoInstanceStruct *chartInstance);
static void set_sim_state_c2_sdruFMStereo(SFc2_sdruFMStereoInstanceStruct
  *chartInstance, const mxArray *c2_st);
static void finalize_c2_sdruFMStereo(SFc2_sdruFMStereoInstanceStruct
  *chartInstance);
static void sf_c2_sdruFMStereo(SFc2_sdruFMStereoInstanceStruct *chartInstance);
static void c2_chartstep_c2_sdruFMStereo(SFc2_sdruFMStereoInstanceStruct
  *chartInstance);
static void initSimStructsc2_sdruFMStereo(SFc2_sdruFMStereoInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static void c2_emlrt_marshallIn(SFc2_sdruFMStereoInstanceStruct *chartInstance,
  const mxArray *c2_y, const char_T *c2_identifier, real32_T c2_b_y[1920]);
static void c2_b_emlrt_marshallIn(SFc2_sdruFMStereoInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real32_T c2_y[1920]);
static uint8_T c2_c_emlrt_marshallIn(SFc2_sdruFMStereoInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_sdruFMStereo, const char_T
  *c2_identifier);
static uint8_T c2_d_emlrt_marshallIn(SFc2_sdruFMStereoInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_sdruFMStereoInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_sdruFMStereo(SFc2_sdruFMStereoInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_is_active_c2_sdruFMStereo = 0U;
}

static void initialize_params_c2_sdruFMStereo(SFc2_sdruFMStereoInstanceStruct
  *chartInstance)
{
}

static void enable_c2_sdruFMStereo(SFc2_sdruFMStereoInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_sdruFMStereo(SFc2_sdruFMStereoInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static const mxArray *get_sim_state_c2_sdruFMStereo
  (SFc2_sdruFMStereoInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i0;
  real32_T c2_u[1920];
  const mxArray *c2_b_y = NULL;
  uint8_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  real32_T (*c2_d_y)[1920];
  c2_d_y = (real32_T (*)[1920])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(2));
  for (c2_i0 = 0; c2_i0 < 1920; c2_i0++) {
    c2_u[c2_i0] = (*c2_d_y)[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 1, 0U, 1U, 0U, 2, 960, 2));
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_b_u = chartInstance->c2_is_active_c2_sdruFMStereo;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c2_y, 1, c2_c_y);
  sf_mex_assign(&c2_st, c2_y);
  return c2_st;
}

static void set_sim_state_c2_sdruFMStereo(SFc2_sdruFMStereoInstanceStruct
  *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real32_T c2_fv0[1920];
  int32_T c2_i1;
  real32_T (*c2_y)[1920];
  c2_y = (real32_T (*)[1920])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)), "y",
                      c2_fv0);
  for (c2_i1 = 0; c2_i1 < 1920; c2_i1++) {
    (*c2_y)[c2_i1] = c2_fv0[c2_i1];
  }

  chartInstance->c2_is_active_c2_sdruFMStereo = c2_c_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)),
     "is_active_c2_sdruFMStereo");
  sf_mex_destroy(&c2_u);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_sdruFMStereo(SFc2_sdruFMStereoInstanceStruct
  *chartInstance)
{
}

static void sf_c2_sdruFMStereo(SFc2_sdruFMStereoInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  c2_chartstep_c2_sdruFMStereo(chartInstance);
}

static void c2_chartstep_c2_sdruFMStereo(SFc2_sdruFMStereoInstanceStruct
  *chartInstance)
{
  int32_T c2_i2;
  real32_T (*c2_y)[1920];
  real32_T (*c2_u)[1920];
  c2_y = (real32_T (*)[1920])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_u = (real32_T (*)[1920])ssGetInputPortSignal(chartInstance->S, 0);
  for (c2_i2 = 0; c2_i2 < 960; c2_i2++) {
    (*c2_y)[c2_i2] = (*c2_u)[c2_i2] + (*c2_u)[c2_i2 + 960];
    (*c2_y)[c2_i2 + 960] = (*c2_u)[c2_i2] - (*c2_u)[c2_i2 + 960];
  }
}

static void initSimStructsc2_sdruFMStereo(SFc2_sdruFMStereoInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

const mxArray *sf_c2_sdruFMStereo_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1));
  return c2_nameCaptureInfo;
}

static void c2_emlrt_marshallIn(SFc2_sdruFMStereoInstanceStruct *chartInstance,
  const mxArray *c2_y, const char_T *c2_identifier, real32_T c2_b_y[1920])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_y), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_y);
}

static void c2_b_emlrt_marshallIn(SFc2_sdruFMStereoInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real32_T c2_y[1920])
{
  real32_T c2_fv1[1920];
  int32_T c2_i3;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_fv1, 1, 1, 0U, 1, 0U, 2, 960,
                2);
  for (c2_i3 = 0; c2_i3 < 1920; c2_i3++) {
    c2_y[c2_i3] = c2_fv1[c2_i3];
  }

  sf_mex_destroy(&c2_u);
}

static uint8_T c2_c_emlrt_marshallIn(SFc2_sdruFMStereoInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_sdruFMStereo, const char_T
  *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_sdruFMStereo), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_sdruFMStereo);
  return c2_y;
}

static uint8_T c2_d_emlrt_marshallIn(SFc2_sdruFMStereoInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_sdruFMStereoInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c2_sdruFMStereo_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2709331330U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(36777976U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3017089548U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3488041504U);
}

mxArray *sf_c2_sdruFMStereo_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(503180122U);
    pr[1] = (double)(930117548U);
    pr[2] = (double)(765888271U);
    pr[3] = (double)(1085939468U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(960);
      pr[1] = (double)(2);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(960);
      pr[1] = (double)(2);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c2_sdruFMStereo(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[8],M[0],T\"is_active_c2_sdruFMStereo\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_sdruFMStereo_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void sf_opaque_initialize_c2_sdruFMStereo(void *chartInstanceVar)
{
  initialize_params_c2_sdruFMStereo((SFc2_sdruFMStereoInstanceStruct*)
    chartInstanceVar);
  initialize_c2_sdruFMStereo((SFc2_sdruFMStereoInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_sdruFMStereo(void *chartInstanceVar)
{
  enable_c2_sdruFMStereo((SFc2_sdruFMStereoInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_sdruFMStereo(void *chartInstanceVar)
{
  disable_c2_sdruFMStereo((SFc2_sdruFMStereoInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_sdruFMStereo(void *chartInstanceVar)
{
  sf_c2_sdruFMStereo((SFc2_sdruFMStereoInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_sdruFMStereo(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_sdruFMStereo
    ((SFc2_sdruFMStereoInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_sdruFMStereo();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c2_sdruFMStereo(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_sdruFMStereo();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_sdruFMStereo((SFc2_sdruFMStereoInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_sdruFMStereo(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_sdruFMStereo(S);
}

static void sf_opaque_set_sim_state_c2_sdruFMStereo(SimStruct* S, const mxArray *
  st)
{
  sf_internal_set_sim_state_c2_sdruFMStereo(S, st);
}

static void sf_opaque_terminate_c2_sdruFMStereo(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_sdruFMStereoInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c2_sdruFMStereo((SFc2_sdruFMStereoInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_sdruFMStereo((SFc2_sdruFMStereoInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_sdruFMStereo(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_sdruFMStereo((SFc2_sdruFMStereoInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_sdruFMStereo(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"sdruFMStereo","sdruFMStereo",2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"sdruFMStereo","sdruFMStereo",2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"sdruFMStereo",
      "sdruFMStereo",2,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"sdruFMStereo","sdruFMStereo",2,1);
      sf_mark_chart_reusable_outputs(S,"sdruFMStereo","sdruFMStereo",2,1);
    }

    sf_set_rtw_dwork_info(S,"sdruFMStereo","sdruFMStereo",2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3148477152U));
  ssSetChecksum1(S,(3543860980U));
  ssSetChecksum2(S,(3928985362U));
  ssSetChecksum3(S,(2523592242U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c2_sdruFMStereo(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "sdruFMStereo", "sdruFMStereo",2);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_sdruFMStereo(SimStruct *S)
{
  SFc2_sdruFMStereoInstanceStruct *chartInstance;
  chartInstance = (SFc2_sdruFMStereoInstanceStruct *)malloc(sizeof
    (SFc2_sdruFMStereoInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_sdruFMStereoInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_sdruFMStereo;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_sdruFMStereo;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_sdruFMStereo;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_sdruFMStereo;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_sdruFMStereo;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_sdruFMStereo;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_sdruFMStereo;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_sdruFMStereo;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_sdruFMStereo;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_sdruFMStereo;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_sdruFMStereo;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
}

void c2_sdruFMStereo_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_sdruFMStereo(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_sdruFMStereo(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_sdruFMStereo(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_sdruFMStereo_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
