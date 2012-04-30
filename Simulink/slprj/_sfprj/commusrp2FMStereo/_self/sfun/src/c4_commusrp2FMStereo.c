/* Include files */

#include "blascompat32.h"
#include "commusrp2FMStereo_sfun.h"
#include "c4_commusrp2FMStereo.h"
#include "mwmathutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void initialize_c4_commusrp2FMStereo(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance);
static void initialize_params_c4_commusrp2FMStereo
  (SFc4_commusrp2FMStereoInstanceStruct *chartInstance);
static void enable_c4_commusrp2FMStereo(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance);
static void disable_c4_commusrp2FMStereo(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c4_commusrp2FMStereo
  (SFc4_commusrp2FMStereoInstanceStruct *chartInstance);
static void set_sim_state_c4_commusrp2FMStereo
  (SFc4_commusrp2FMStereoInstanceStruct *chartInstance, const mxArray *c4_st);
static void finalize_c4_commusrp2FMStereo(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance);
static void sf_c4_commusrp2FMStereo(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance);
static void initSimStructsc4_commusrp2FMStereo
  (SFc4_commusrp2FMStereoInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber);
static void c4_emlrt_marshallIn(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance, const mxArray *c4_y, const char_T *c4_identifier, real32_T
  c4_b_y[272]);
static void c4_b_emlrt_marshallIn(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId,
  real32_T c4_y[272]);
static void c4_c_emlrt_marshallIn(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance, const mxArray *c4_b_pilot_delay, const char_T *c4_identifier,
  real32_T c4_y[2]);
static void c4_d_emlrt_marshallIn(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId,
  real32_T c4_y[2]);
static uint8_T c4_e_emlrt_marshallIn(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance, const mxArray *c4_b_is_active_c4_commusrp2FMStereo, const
  char_T *c4_identifier);
static uint8_T c4_f_emlrt_marshallIn(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void init_dsm_address_info(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c4_commusrp2FMStereo(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance)
{
  int32_T c4_i0;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c4_pilot_delay_not_empty = FALSE;
  chartInstance->c4_is_active_c4_commusrp2FMStereo = 0U;
  for (c4_i0 = 0; c4_i0 < 2; c4_i0++) {
    chartInstance->c4_pilot_delay[c4_i0] = 0.0F;
  }
}

static void initialize_params_c4_commusrp2FMStereo
  (SFc4_commusrp2FMStereoInstanceStruct *chartInstance)
{
}

static void enable_c4_commusrp2FMStereo(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c4_commusrp2FMStereo(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static const mxArray *get_sim_state_c4_commusrp2FMStereo
  (SFc4_commusrp2FMStereoInstanceStruct *chartInstance)
{
  const mxArray *c4_st;
  const mxArray *c4_y = NULL;
  int32_T c4_i1;
  real32_T c4_u[272];
  const mxArray *c4_b_y = NULL;
  real32_T c4_b_u[2];
  const mxArray *c4_c_y = NULL;
  uint8_T c4_c_u;
  const mxArray *c4_d_y = NULL;
  real32_T (*c4_e_y)[272];
  c4_e_y = (real32_T (*)[272])ssGetOutputPortSignal(chartInstance->S, 1);
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellarray(3));
  for (c4_i1 = 0; c4_i1 < 272; c4_i1++) {
    c4_u[c4_i1] = (*c4_e_y)[c4_i1];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_u, 1, 0U, 1U, 0U, 1, 272));
  sf_mex_setcell(c4_y, 0, c4_b_y);
  for (c4_i1 = 0; c4_i1 < 2; c4_i1++) {
    c4_b_u[c4_i1] = chartInstance->c4_pilot_delay[c4_i1];
  }

  c4_c_y = NULL;
  if (!chartInstance->c4_pilot_delay_not_empty) {
    sf_mex_assign(&c4_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c4_c_y, sf_mex_create("y", c4_b_u, 1, 0U, 1U, 0U, 1, 2));
  }

  sf_mex_setcell(c4_y, 1, c4_c_y);
  c4_c_u = chartInstance->c4_is_active_c4_commusrp2FMStereo;
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_c_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c4_y, 2, c4_d_y);
  sf_mex_assign(&c4_st, c4_y);
  return c4_st;
}

static void set_sim_state_c4_commusrp2FMStereo
  (SFc4_commusrp2FMStereoInstanceStruct *chartInstance, const mxArray *c4_st)
{
  const mxArray *c4_u;
  real32_T c4_fv0[272];
  int32_T c4_i2;
  real32_T c4_fv1[2];
  real32_T (*c4_y)[272];
  c4_y = (real32_T (*)[272])ssGetOutputPortSignal(chartInstance->S, 1);
  c4_u = sf_mex_dup(c4_st);
  c4_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 0)), "y",
                      c4_fv0);
  for (c4_i2 = 0; c4_i2 < 272; c4_i2++) {
    (*c4_y)[c4_i2] = c4_fv0[c4_i2];
  }

  c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 1)),
                        "pilot_delay", c4_fv1);
  for (c4_i2 = 0; c4_i2 < 2; c4_i2++) {
    chartInstance->c4_pilot_delay[c4_i2] = c4_fv1[c4_i2];
  }

  chartInstance->c4_is_active_c4_commusrp2FMStereo = c4_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 2)),
     "is_active_c4_commusrp2FMStereo");
  sf_mex_destroy(&c4_u);
  sf_mex_destroy(&c4_st);
}

static void finalize_c4_commusrp2FMStereo(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance)
{
}

static void sf_c4_commusrp2FMStereo(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance)
{
  int32_T c4_itmp;
  real32_T c4_pilot[272];
  int32_T c4_idx;
  int32_T c4_sidx;
  real32_T c4_y[8];
  real32_T c4_currMax;
  int32_T c4_ix;
  boolean_T c4_guard1 = FALSE;
  boolean_T c4_searchingForNonNaN;
  int32_T c4_k;
  boolean_T c4_exitg1;
  real32_T c4_pilot_q;
  real32_T c4_pilot_i;
  real32_T c4_b_y[272];
  real32_T (*c4_c_y)[272];
  real32_T (*c4_b_pilot)[272];
  c4_c_y = (real32_T (*)[272])ssGetOutputPortSignal(chartInstance->S, 1);
  c4_b_pilot = (real32_T (*)[272])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  for (c4_itmp = 0; c4_itmp < 272; c4_itmp++) {
    c4_pilot[c4_itmp] = (*c4_b_pilot)[c4_itmp];
  }

  chartInstance->c4_pilot_delay_not_empty = TRUE;
  for (c4_idx = 0; c4_idx < 34; c4_idx++) {
    c4_sidx = c4_idx << 3;
    for (c4_itmp = 0; c4_itmp < 8; c4_itmp++) {
      c4_y[c4_itmp] = muSingleScalarAbs(c4_pilot[c4_itmp + c4_sidx]);
    }

    c4_currMax = c4_y[0];
    c4_itmp = 1;
    c4_ix = 0;
    c4_guard1 = FALSE;
    if (muSingleScalarIsNaN(c4_y[0])) {
      c4_searchingForNonNaN = TRUE;
      c4_k = 2;
      c4_exitg1 = 0U;
      while ((c4_exitg1 == 0U) && (c4_k < 9)) {
        c4_ix++;
        if (!muSingleScalarIsNaN(c4_y[c4_ix])) {
          c4_currMax = c4_y[c4_ix];
          c4_itmp = c4_k;
          c4_searchingForNonNaN = FALSE;
          c4_exitg1 = 1U;
        } else {
          c4_k++;
        }
      }

      if (c4_searchingForNonNaN) {
      } else {
        c4_guard1 = TRUE;
      }
    } else {
      c4_guard1 = TRUE;
    }

    if (c4_guard1 == TRUE) {
      while (c4_itmp + 1 < 9) {
        if (c4_y[c4_itmp] > c4_currMax) {
          c4_currMax = c4_y[c4_itmp];
        }

        c4_itmp++;
      }
    }

    if (c4_currMax < 1.1920929E-7F) {
      c4_currMax = 1.1920929E-7F;
    }

    c4_currMax = 1.0F / c4_currMax * 1.41421354F;
    for (c4_itmp = 0; c4_itmp < 8; c4_itmp++) {
      c4_pilot_q = c4_pilot[c4_sidx + c4_itmp] * c4_currMax;
      c4_pilot_i = chartInstance->c4_pilot_delay[1];
      chartInstance->c4_pilot_delay[1] = chartInstance->c4_pilot_delay[0];
      chartInstance->c4_pilot_delay[0] = c4_pilot_q;
      c4_b_y[c4_sidx + c4_itmp] = -2.0F * c4_pilot_q * c4_pilot_i;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  for (c4_itmp = 0; c4_itmp < 272; c4_itmp++) {
    (*c4_c_y)[c4_itmp] = c4_b_y[c4_itmp];
  }
}

static void initSimStructsc4_commusrp2FMStereo
  (SFc4_commusrp2FMStereoInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber)
{
}

const mxArray *sf_c4_commusrp2FMStereo_get_eml_resolved_functions_info(void)
{
  const mxArray *c4_nameCaptureInfo = NULL;
  c4_nameCaptureInfo = NULL;
  sf_mex_assign(&c4_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1));
  return c4_nameCaptureInfo;
}

static void c4_emlrt_marshallIn(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance, const mxArray *c4_y, const char_T *c4_identifier, real32_T
  c4_b_y[272])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_y), &c4_thisId, c4_b_y);
  sf_mex_destroy(&c4_y);
}

static void c4_b_emlrt_marshallIn(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId,
  real32_T c4_y[272])
{
  real32_T c4_fv2[272];
  int32_T c4_i3;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_fv2, 1, 1, 0U, 1, 0U, 1, 272);
  for (c4_i3 = 0; c4_i3 < 272; c4_i3++) {
    c4_y[c4_i3] = c4_fv2[c4_i3];
  }

  sf_mex_destroy(&c4_u);
}

static void c4_c_emlrt_marshallIn(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance, const mxArray *c4_b_pilot_delay, const char_T *c4_identifier,
  real32_T c4_y[2])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_pilot_delay), &c4_thisId,
                        c4_y);
  sf_mex_destroy(&c4_b_pilot_delay);
}

static void c4_d_emlrt_marshallIn(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId,
  real32_T c4_y[2])
{
  real32_T c4_fv3[2];
  int32_T c4_i4;
  if (mxIsEmpty(c4_u)) {
    chartInstance->c4_pilot_delay_not_empty = FALSE;
  } else {
    chartInstance->c4_pilot_delay_not_empty = TRUE;
    sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_fv3, 1, 1, 0U, 1, 0U, 1, 2);
    for (c4_i4 = 0; c4_i4 < 2; c4_i4++) {
      c4_y[c4_i4] = c4_fv3[c4_i4];
    }
  }

  sf_mex_destroy(&c4_u);
}

static uint8_T c4_e_emlrt_marshallIn(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance, const mxArray *c4_b_is_active_c4_commusrp2FMStereo, const
  char_T *c4_identifier)
{
  uint8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_b_is_active_c4_commusrp2FMStereo), &c4_thisId);
  sf_mex_destroy(&c4_b_is_active_c4_commusrp2FMStereo);
  return c4_y;
}

static uint8_T c4_f_emlrt_marshallIn(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  uint8_T c4_u0;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_u0, 1, 3, 0U, 0, 0U, 0);
  c4_y = c4_u0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void init_dsm_address_info(SFc4_commusrp2FMStereoInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c4_commusrp2FMStereo_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1258294032U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1503858173U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3936948745U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3405394506U);
}

mxArray *sf_c4_commusrp2FMStereo_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(3916549479U);
    pr[1] = (double)(106930667U);
    pr[2] = (double)(1429420926U);
    pr[3] = (double)(1757532562U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(272);
      pr[1] = (double)(1);
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
      pr[0] = (double)(272);
      pr[1] = (double)(1);
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

static const mxArray *sf_get_sim_state_info_c4_commusrp2FMStereo(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[4],M[0],T\"pilot_delay\",S'l','i','p'{{M1x2[515 526],M[0],}}},{M[8],M[0],T\"is_active_c4_commusrp2FMStereo\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_commusrp2FMStereo_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void sf_opaque_initialize_c4_commusrp2FMStereo(void *chartInstanceVar)
{
  initialize_params_c4_commusrp2FMStereo((SFc4_commusrp2FMStereoInstanceStruct*)
    chartInstanceVar);
  initialize_c4_commusrp2FMStereo((SFc4_commusrp2FMStereoInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c4_commusrp2FMStereo(void *chartInstanceVar)
{
  enable_c4_commusrp2FMStereo((SFc4_commusrp2FMStereoInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c4_commusrp2FMStereo(void *chartInstanceVar)
{
  disable_c4_commusrp2FMStereo((SFc4_commusrp2FMStereoInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c4_commusrp2FMStereo(void *chartInstanceVar)
{
  sf_c4_commusrp2FMStereo((SFc4_commusrp2FMStereoInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c4_commusrp2FMStereo(SimStruct*
  S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c4_commusrp2FMStereo
    ((SFc4_commusrp2FMStereoInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_commusrp2FMStereo();/* state var info */
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

extern void sf_internal_set_sim_state_c4_commusrp2FMStereo(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_commusrp2FMStereo();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c4_commusrp2FMStereo((SFc4_commusrp2FMStereoInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c4_commusrp2FMStereo(SimStruct* S)
{
  return sf_internal_get_sim_state_c4_commusrp2FMStereo(S);
}

static void sf_opaque_set_sim_state_c4_commusrp2FMStereo(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c4_commusrp2FMStereo(S, st);
}

static void sf_opaque_terminate_c4_commusrp2FMStereo(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc4_commusrp2FMStereoInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c4_commusrp2FMStereo((SFc4_commusrp2FMStereoInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc4_commusrp2FMStereo((SFc4_commusrp2FMStereoInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c4_commusrp2FMStereo(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c4_commusrp2FMStereo((SFc4_commusrp2FMStereoInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c4_commusrp2FMStereo(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"commusrp2FMStereo","commusrp2FMStereo",4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"commusrp2FMStereo","commusrp2FMStereo",
                4,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"commusrp2FMStereo",
      "commusrp2FMStereo",4,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"commusrp2FMStereo",
        "commusrp2FMStereo",4,1);
      sf_mark_chart_reusable_outputs(S,"commusrp2FMStereo","commusrp2FMStereo",4,
        1);
    }

    sf_set_rtw_dwork_info(S,"commusrp2FMStereo","commusrp2FMStereo",4);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1531741991U));
  ssSetChecksum1(S,(3900899177U));
  ssSetChecksum2(S,(2937981465U));
  ssSetChecksum3(S,(1790767800U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c4_commusrp2FMStereo(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "commusrp2FMStereo", "commusrp2FMStereo",4);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c4_commusrp2FMStereo(SimStruct *S)
{
  SFc4_commusrp2FMStereoInstanceStruct *chartInstance;
  chartInstance = (SFc4_commusrp2FMStereoInstanceStruct *)malloc(sizeof
    (SFc4_commusrp2FMStereoInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc4_commusrp2FMStereoInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c4_commusrp2FMStereo;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c4_commusrp2FMStereo;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c4_commusrp2FMStereo;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c4_commusrp2FMStereo;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c4_commusrp2FMStereo;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c4_commusrp2FMStereo;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c4_commusrp2FMStereo;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c4_commusrp2FMStereo;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c4_commusrp2FMStereo;
  chartInstance->chartInfo.mdlStart = mdlStart_c4_commusrp2FMStereo;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c4_commusrp2FMStereo;
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

void c4_commusrp2FMStereo_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c4_commusrp2FMStereo(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_commusrp2FMStereo(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_commusrp2FMStereo(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_commusrp2FMStereo_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
