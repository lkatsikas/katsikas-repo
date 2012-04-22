/* Include files */

#include "blascompat32.h"
#include "vipcodec_sfun.h"
#include "c3_vipcodec.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "vipcodec_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char * c3_debug_family_names[14] = { "cbits", "inpos", "Temp",
  "run", "val", "numcoefs", "i", "flag", "j", "nargin", "nargout", "in", "out",
  "prev_out" };

static const char * c3_b_debug_family_names[16] = { "lval", "temp", "inwidth",
  "nargin", "nargout", "cbits", "inpos", "Temp", "in", "val", "bits", "flag",
  "cbitsO", "inposO", "TempO", "valO" };

/* Function Declarations */
static void initialize_c3_vipcodec(SFc3_vipcodecInstanceStruct *chartInstance);
static void initialize_params_c3_vipcodec(SFc3_vipcodecInstanceStruct
  *chartInstance);
static void enable_c3_vipcodec(SFc3_vipcodecInstanceStruct *chartInstance);
static void disable_c3_vipcodec(SFc3_vipcodecInstanceStruct *chartInstance);
static void c3_update_debugger_state_c3_vipcodec(SFc3_vipcodecInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c3_vipcodec(SFc3_vipcodecInstanceStruct
  *chartInstance);
static void set_sim_state_c3_vipcodec(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_st);
static void finalize_c3_vipcodec(SFc3_vipcodecInstanceStruct *chartInstance);
static void sf_c3_vipcodec(SFc3_vipcodecInstanceStruct *chartInstance);
static void c3_chartstep_c3_vipcodec(SFc3_vipcodecInstanceStruct *chartInstance);
static void initSimStructsc3_vipcodec(SFc3_vipcodecInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData);
static void c3_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_b_prev_out, const char_T *c3_identifier, real32_T c3_y[64]);
static void c3_b_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real32_T c3_y[64]);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_c_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_out, const char_T *c3_identifier, real32_T c3_y[64]);
static void c3_d_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real32_T c3_y[64]);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_e_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static uint32_T c3_f_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_g_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_h_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint32_T c3_y[15]);
static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_info_helper(c3_ResolvedFunctionInfo c3_info[17]);
static void c3_getbits(SFc3_vipcodecInstanceStruct *chartInstance, int32_T
  c3_cbits, real_T c3_inpos, uint32_T c3_Temp, uint32_T c3_in[15], uint32_T
  c3_val, real_T c3_bits, real_T *c3_flag, int32_T *c3_cbitsO, real_T *c3_inposO,
  uint32_T *c3_TempO, uint32_T *c3_valO);
static void c3_eml_error(SFc3_vipcodecInstanceStruct *chartInstance);
static void c3_eml_scalar_eg(SFc3_vipcodecInstanceStruct *chartInstance);
static uint8_T c3_i_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_vipcodec, const char_T *c3_identifier);
static uint8_T c3_j_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void init_dsm_address_info(SFc3_vipcodecInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c3_vipcodec(SFc3_vipcodecInstanceStruct *chartInstance)
{
  chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c3_prev_out_not_empty = FALSE;
  chartInstance->c3_is_active_c3_vipcodec = 0U;
}

static void initialize_params_c3_vipcodec(SFc3_vipcodecInstanceStruct
  *chartInstance)
{
}

static void enable_c3_vipcodec(SFc3_vipcodecInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c3_vipcodec(SFc3_vipcodecInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c3_update_debugger_state_c3_vipcodec(SFc3_vipcodecInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c3_vipcodec(SFc3_vipcodecInstanceStruct
  *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  int32_T c3_i0;
  real32_T c3_u[64];
  const mxArray *c3_b_y = NULL;
  int32_T c3_i1;
  real32_T c3_b_u[64];
  const mxArray *c3_c_y = NULL;
  uint8_T c3_hoistedGlobal;
  uint8_T c3_c_u;
  const mxArray *c3_d_y = NULL;
  real32_T (*c3_out)[64];
  c3_out = (real32_T (*)[64])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellarray(3));
  for (c3_i0 = 0; c3_i0 < 64; c3_i0++) {
    c3_u[c3_i0] = (*c3_out)[c3_i0];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_u, 1, 0U, 1U, 0U, 1, 64));
  sf_mex_setcell(c3_y, 0, c3_b_y);
  for (c3_i1 = 0; c3_i1 < 64; c3_i1++) {
    c3_b_u[c3_i1] = chartInstance->c3_prev_out[c3_i1];
  }

  c3_c_y = NULL;
  if (!chartInstance->c3_prev_out_not_empty) {
    sf_mex_assign(&c3_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_b_u, 1, 0U, 1U, 0U, 1, 64));
  }

  sf_mex_setcell(c3_y, 1, c3_c_y);
  c3_hoistedGlobal = chartInstance->c3_is_active_c3_vipcodec;
  c3_c_u = c3_hoistedGlobal;
  c3_d_y = NULL;
  sf_mex_assign(&c3_d_y, sf_mex_create("y", &c3_c_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 2, c3_d_y);
  sf_mex_assign(&c3_st, c3_y);
  return c3_st;
}

static void set_sim_state_c3_vipcodec(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_st)
{
  const mxArray *c3_u;
  real32_T c3_fv0[64];
  int32_T c3_i2;
  real32_T c3_fv1[64];
  int32_T c3_i3;
  real32_T (*c3_out)[64];
  c3_out = (real32_T (*)[64])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c3_doneDoubleBufferReInit = TRUE;
  c3_u = sf_mex_dup(c3_st);
  c3_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 0)),
                        "out", c3_fv0);
  for (c3_i2 = 0; c3_i2 < 64; c3_i2++) {
    (*c3_out)[c3_i2] = c3_fv0[c3_i2];
  }

  c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 1)),
                      "prev_out", c3_fv1);
  for (c3_i3 = 0; c3_i3 < 64; c3_i3++) {
    chartInstance->c3_prev_out[c3_i3] = c3_fv1[c3_i3];
  }

  chartInstance->c3_is_active_c3_vipcodec = c3_i_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_u, 2)), "is_active_c3_vipcodec");
  sf_mex_destroy(&c3_u);
  c3_update_debugger_state_c3_vipcodec(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_vipcodec(SFc3_vipcodecInstanceStruct *chartInstance)
{
}

static void sf_c3_vipcodec(SFc3_vipcodecInstanceStruct *chartInstance)
{
  int32_T c3_i4;
  int32_T c3_i5;
  real32_T (*c3_out)[64];
  uint32_T (*c3_in)[15];
  c3_out = (real32_T (*)[64])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_in = (uint32_T (*)[15])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
  for (c3_i4 = 0; c3_i4 < 15; c3_i4++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c3_in)[c3_i4], 0U);
  }

  for (c3_i5 = 0; c3_i5 < 64; c3_i5++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c3_out)[c3_i5], 1U);
  }

  chartInstance->c3_sfEvent = CALL_EVENT;
  c3_chartstep_c3_vipcodec(chartInstance);
  sf_debug_check_for_state_inconsistency(_vipcodecMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c3_chartstep_c3_vipcodec(SFc3_vipcodecInstanceStruct *chartInstance)
{
  int32_T c3_i6;
  uint32_T c3_in[15];
  uint32_T c3_debug_family_var_map[14];
  int32_T c3_cbits;
  real_T c3_inpos;
  uint32_T c3_Temp;
  uint32_T c3_run;
  uint32_T c3_val;
  real_T c3_numcoefs;
  real_T c3_i;
  real_T c3_flag;
  uint32_T c3_j;
  real_T c3_nargin = 1.0;
  real_T c3_nargout = 1.0;
  real32_T c3_out[64];
  int32_T c3_i7;
  int32_T c3_i8;
  uint32_T c3_a;
  uint32_T c3_ak;
  uint32_T c3_c;
  uint32_T c3_q0;
  uint32_T c3_qY;
  uint32_T c3_u0;
  int32_T c3_i9;
  int32_T c3_saturatedUnaryMinus;
  int64_T c3_i10;
  uint32_T c3_u1;
  int32_T c3_i11;
  uint32_T c3_b_in[15];
  uint32_T c3_b_run;
  uint32_T c3_b_Temp;
  real_T c3_b_inpos;
  int32_T c3_b_cbits;
  real_T c3_b_flag;
  int32_T c3_i12;
  uint32_T c3_c_in[15];
  uint32_T c3_b_val;
  uint32_T c3_c_Temp;
  real_T c3_c_inpos;
  int32_T c3_c_cbits;
  real_T c3_c_flag;
  uint32_T c3_u2;
  real_T c3_d0;
  real_T c3_d1;
  real_T c3_d2;
  uint32_T c3_u3;
  uint32_T c3_varargin_1;
  uint32_T c3_x;
  uint32_T c3_b_x;
  uint32_T c3_xk;
  uint32_T c3_c_x;
  uint32_T c3_rx;
  uint32_T c3_loop_ub;
  uint32_T c3_b_j;
  real_T c3_b_i;
  real_T c3_c_i;
  int32_T c3_i13;
  int32_T c3_i14;
  real32_T (*c3_b_out)[64];
  uint32_T (*c3_d_in)[15];
  boolean_T exitg1;
  c3_b_out = (real32_T (*)[64])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_d_in = (uint32_T (*)[15])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
  for (c3_i6 = 0; c3_i6 < 15; c3_i6++) {
    c3_in[c3_i6] = (*c3_d_in)[c3_i6];
  }

  sf_debug_symbol_scope_push_eml(0U, 14U, 14U, c3_debug_family_names,
    c3_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c3_cbits, 0U, c3_f_sf_marshallOut,
    c3_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_inpos, 1U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_Temp, 2U, c3_e_sf_marshallOut,
    c3_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_run, 3U, c3_e_sf_marshallOut,
    c3_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_val, 4U, c3_e_sf_marshallOut,
    c3_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c3_numcoefs, 5U, c3_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c3_i, 6U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_flag, 7U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_j, 8U, c3_e_sf_marshallOut,
    c3_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_nargin, 9U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_nargout, 10U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c3_in, 11U, c3_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c3_out, 12U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(chartInstance->c3_prev_out, 13U,
    c3_sf_marshallOut, c3_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 7);
  if (CV_EML_IF(0, 0, !chartInstance->c3_prev_out_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 8);
    for (c3_i7 = 0; c3_i7 < 64; c3_i7++) {
      chartInstance->c3_prev_out[c3_i7] = 0.0F;
    }

    chartInstance->c3_prev_out_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 10);
  for (c3_i8 = 0; c3_i8 < 64; c3_i8++) {
    c3_out[c3_i8] = chartInstance->c3_prev_out[c3_i8];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 11);
  c3_cbits = 0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 12);
  c3_inpos = 2.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 13);
  c3_Temp = 0U;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 14);
  c3_run = 0U;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 15);
  c3_val = 0U;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 17);
  c3_numcoefs = 64.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 18);
  c3_a = c3_in[0];
  c3_ak = c3_a;
  c3_c = (uint32_T)((real_T)(c3_ak & 2147483648U) != 0.0);
  if (CV_EML_IF(0, 1, c3_c != 0U) != 0U) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 19);
    c3_q0 = MAX_uint32_T;
    c3_qY = c3_q0 - c3_in[0];
    if (c3_qY > c3_q0) {
      c3_qY = 0U;
    }

    c3_u0 = c3_qY;
    if (c3_u0 > 2147483647U) {
      c3_u0 = 2147483647U;
    }

    c3_i9 = (int32_T)c3_u0;
    if (c3_i9 <= MIN_int32_T) {
      c3_saturatedUnaryMinus = MAX_int32_T;
    } else {
      c3_saturatedUnaryMinus = -c3_i9;
    }

    c3_i10 = (int64_T)c3_saturatedUnaryMinus - (int64_T)1;
    if (c3_i10 > 2147483647L) {
      c3_i10 = 2147483647L;
    } else {
      if (c3_i10 <= -2147483648L) {
        c3_i10 = -2147483648L;
      }
    }

    c3_out[0] = (real32_T)(int32_T)c3_i10;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 21);
    c3_u1 = c3_in[0];
    if (c3_u1 > 2147483647U) {
      c3_u1 = 2147483647U;
    }

    c3_out[0] = (real32_T)(int32_T)c3_u1;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 26);
  c3_i = 2.0;
  exitg1 = 0U;
  while ((exitg1 == 0U) && CV_EML_WHILE(0, 0, c3_i <= c3_numcoefs)) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 29);
    for (c3_i11 = 0; c3_i11 < 15; c3_i11++) {
      c3_b_in[c3_i11] = c3_in[c3_i11];
    }

    c3_getbits(chartInstance, c3_cbits, c3_inpos, c3_Temp, c3_b_in, c3_run, 4.0,
               &c3_b_flag, &c3_b_cbits, &c3_b_inpos, &c3_b_Temp, &c3_b_run);
    c3_flag = c3_b_flag;
    c3_cbits = c3_b_cbits;
    c3_inpos = c3_b_inpos;
    c3_Temp = c3_b_Temp;
    c3_run = c3_b_run;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 30);
    if (CV_EML_IF(0, 2, CV_EML_MCDC(0, 0, !(CV_EML_COND(0, 0, c3_flag != 0.0) !=
           0.0)))) {
      exitg1 = 1U;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 33);
      if (CV_EML_IF(0, 3, (real_T)c3_run == 15.0)) {
        exitg1 = 1U;
      } else {
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 35);
        for (c3_i12 = 0; c3_i12 < 15; c3_i12++) {
          c3_c_in[c3_i12] = c3_in[c3_i12];
        }

        c3_getbits(chartInstance, c3_cbits, c3_inpos, c3_Temp, c3_c_in, c3_val,
                   8.0, &c3_c_flag, &c3_c_cbits, &c3_c_inpos, &c3_c_Temp,
                   &c3_b_val);
        c3_flag = c3_c_flag;
        c3_cbits = c3_c_cbits;
        c3_inpos = c3_c_inpos;
        c3_Temp = c3_c_Temp;
        c3_val = c3_b_val;
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 36);
        if (CV_EML_IF(0, 4, CV_EML_MCDC(0, 1, !(CV_EML_COND(0, 1, c3_flag != 0.0)
               != 0.0)))) {
          exitg1 = 1U;
        } else {
          c3_u2 = (uint32_T)_SFD_INTEGER_CHECK("i", c3_i);
          c3_j = c3_u2;
          c3_d0 = (real_T)c3_run + c3_i;
          c3_d1 = c3_d0;
          c3_d1 = c3_d1 < 0.0 ? muDoubleScalarCeil(c3_d1 - 0.5) :
            muDoubleScalarFloor(c3_d1 + 0.5);
          c3_d2 = c3_d1;
          if (c3_d2 < 4.294967296E+9) {
            if (c3_d2 >= 0.0) {
              c3_u3 = (uint32_T)c3_d2;
            } else {
              c3_u3 = 0U;
            }
          } else if (c3_d2 >= 4.294967296E+9) {
            c3_u3 = MAX_uint32_T;
          } else {
            c3_u3 = 0U;
          }

          c3_varargin_1 = c3_u3;
          c3_x = c3_varargin_1;
          c3_b_x = c3_x;
          c3_eml_scalar_eg(chartInstance);
          c3_xk = c3_b_x;
          c3_c_x = c3_xk;
          c3_rx = c3_xk;
          c3_eml_scalar_eg(chartInstance);
          if ((real_T)c3_rx > 64.0) {
            c3_loop_ub = 64U;
          } else {
            c3_loop_ub = c3_c_x;
          }

          c3_b_j = c3_u2;
          while (c3_b_j <= c3_loop_ub) {
            c3_j = c3_b_j;
            CV_EML_FOR(0, 0, 1);
            _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 41);
            c3_out[(int32_T)(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("out",
              (int32_T)(uint32_T)_SFD_INTEGER_CHECK("j", (real_T)c3_j), 1, 64, 1,
              0) - 1] = (real32_T)c3_val - 128.0F;
            c3_b_j++;
            sf_mex_listen_for_ctrl_c(chartInstance->S);
          }

          CV_EML_FOR(0, 0, 0);
          _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 43);
          c3_i = (c3_i + (real_T)c3_run) + 1.0;
          sf_mex_listen_for_ctrl_c(chartInstance->S);
        }
      }
    }
  }

  c3_b_i = c3_i;
  c3_i = c3_b_i;
  c3_c_i = c3_b_i;
  while (c3_c_i <= 64.0) {
    c3_i = c3_c_i;
    CV_EML_FOR(0, 1, 1);
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 48);
    c3_out[_SFD_EML_ARRAY_BOUNDS_CHECK("out", (int32_T)_SFD_INTEGER_CHECK("i",
      c3_i), 1, 64, 1, 0) - 1] = 0.0F;
    c3_c_i++;
    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 50);
  for (c3_i13 = 0; c3_i13 < 64; c3_i13++) {
    chartInstance->c3_prev_out[c3_i13] = c3_out[c3_i13];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, -50);
  sf_debug_symbol_scope_pop();
  for (c3_i14 = 0; c3_i14 < 64; c3_i14++) {
    (*c3_b_out)[c3_i14] = c3_out[c3_i14];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
}

static void initSimStructsc3_vipcodec(SFc3_vipcodecInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber)
{
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i15;
  real32_T c3_b_inData[64];
  int32_T c3_i16;
  real32_T c3_u[64];
  const mxArray *c3_y = NULL;
  SFc3_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc3_vipcodecInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i15 = 0; c3_i15 < 64; c3_i15++) {
    c3_b_inData[c3_i15] = (*(real32_T (*)[64])c3_inData)[c3_i15];
  }

  for (c3_i16 = 0; c3_i16 < 64; c3_i16++) {
    c3_u[c3_i16] = c3_b_inData[c3_i16];
  }

  c3_y = NULL;
  if (!chartInstance->c3_prev_out_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 1, 0U, 1U, 0U, 1, 64));
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y);
  return c3_mxArrayOutData;
}

static void c3_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_b_prev_out, const char_T *c3_identifier, real32_T c3_y[64])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_prev_out), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_b_prev_out);
}

static void c3_b_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real32_T c3_y[64])
{
  real32_T c3_fv2[64];
  int32_T c3_i17;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_prev_out_not_empty = FALSE;
  } else {
    chartInstance->c3_prev_out_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_fv2, 1, 1, 0U, 1, 0U, 1, 64);
    for (c3_i17 = 0; c3_i17 < 64; c3_i17++) {
      c3_y[c3_i17] = c3_fv2[c3_i17];
    }
  }

  sf_mex_destroy(&c3_u);
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_prev_out;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real32_T c3_y[64];
  int32_T c3_i18;
  SFc3_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc3_vipcodecInstanceStruct *)chartInstanceVoid;
  c3_b_prev_out = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_prev_out), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_b_prev_out);
  for (c3_i18 = 0; c3_i18 < 64; c3_i18++) {
    (*(real32_T (*)[64])c3_outData)[c3_i18] = c3_y[c3_i18];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i19;
  real32_T c3_b_inData[64];
  int32_T c3_i20;
  real32_T c3_u[64];
  const mxArray *c3_y = NULL;
  SFc3_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc3_vipcodecInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i19 = 0; c3_i19 < 64; c3_i19++) {
    c3_b_inData[c3_i19] = (*(real32_T (*)[64])c3_inData)[c3_i19];
  }

  for (c3_i20 = 0; c3_i20 < 64; c3_i20++) {
    c3_u[c3_i20] = c3_b_inData[c3_i20];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 1, 0U, 1U, 0U, 1, 64));
  sf_mex_assign(&c3_mxArrayOutData, c3_y);
  return c3_mxArrayOutData;
}

static void c3_c_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_out, const char_T *c3_identifier, real32_T c3_y[64])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_out), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_out);
}

static void c3_d_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real32_T c3_y[64])
{
  real32_T c3_fv3[64];
  int32_T c3_i21;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_fv3, 1, 1, 0U, 1, 0U, 1, 64);
  for (c3_i21 = 0; c3_i21 < 64; c3_i21++) {
    c3_y[c3_i21] = c3_fv3[c3_i21];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_out;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real32_T c3_y[64];
  int32_T c3_i22;
  SFc3_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc3_vipcodecInstanceStruct *)chartInstanceVoid;
  c3_out = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_out), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_out);
  for (c3_i22 = 0; c3_i22 < 64; c3_i22++) {
    (*(real32_T (*)[64])c3_outData)[c3_i22] = c3_y[c3_i22];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i23;
  uint32_T c3_b_inData[15];
  int32_T c3_i24;
  uint32_T c3_u[15];
  const mxArray *c3_y = NULL;
  SFc3_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc3_vipcodecInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i23 = 0; c3_i23 < 15; c3_i23++) {
    c3_b_inData[c3_i23] = (*(uint32_T (*)[15])c3_inData)[c3_i23];
  }

  for (c3_i24 = 0; c3_i24 < 15; c3_i24++) {
    c3_u[c3_i24] = c3_b_inData[c3_i24];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 7, 0U, 1U, 0U, 2, 15, 1));
  sf_mex_assign(&c3_mxArrayOutData, c3_y);
  return c3_mxArrayOutData;
}

static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc3_vipcodecInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c3_mxArrayOutData, c3_y);
  return c3_mxArrayOutData;
}

static real_T c3_e_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d3;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d3, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d3;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_nargout;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc3_vipcodecInstanceStruct *)chartInstanceVoid;
  c3_nargout = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_nargout), &c3_thisId);
  sf_mex_destroy(&c3_nargout);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  uint32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc3_vipcodecInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(uint32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 7, 0U, 0U, 0U, 0));
  sf_mex_assign(&c3_mxArrayOutData, c3_y);
  return c3_mxArrayOutData;
}

static uint32_T c3_f_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint32_T c3_y;
  uint32_T c3_u4;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u4, 1, 7, 0U, 0, 0U, 0);
  c3_y = c3_u4;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_j;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  uint32_T c3_y;
  SFc3_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc3_vipcodecInstanceStruct *)chartInstanceVoid;
  c3_j = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_j), &c3_thisId);
  sf_mex_destroy(&c3_j);
  *(uint32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc3_vipcodecInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(int32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 6, 0U, 0U, 0U, 0));
  sf_mex_assign(&c3_mxArrayOutData, c3_y);
  return c3_mxArrayOutData;
}

static int32_T c3_g_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_y;
  int32_T c3_i25;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_i25, 1, 6, 0U, 0, 0U, 0);
  c3_y = c3_i25;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_cbits;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_y;
  SFc3_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc3_vipcodecInstanceStruct *)chartInstanceVoid;
  c3_cbits = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_cbits), &c3_thisId);
  sf_mex_destroy(&c3_cbits);
  *(int32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i26;
  uint32_T c3_b_inData[15];
  int32_T c3_i27;
  uint32_T c3_u[15];
  const mxArray *c3_y = NULL;
  SFc3_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc3_vipcodecInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i26 = 0; c3_i26 < 15; c3_i26++) {
    c3_b_inData[c3_i26] = (*(uint32_T (*)[15])c3_inData)[c3_i26];
  }

  for (c3_i27 = 0; c3_i27 < 15; c3_i27++) {
    c3_u[c3_i27] = c3_b_inData[c3_i27];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 7, 0U, 1U, 0U, 1, 15));
  sf_mex_assign(&c3_mxArrayOutData, c3_y);
  return c3_mxArrayOutData;
}

static void c3_h_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint32_T c3_y[15])
{
  uint32_T c3_uv0[15];
  int32_T c3_i28;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_uv0, 1, 7, 0U, 1, 0U, 1, 15);
  for (c3_i28 = 0; c3_i28 < 15; c3_i28++) {
    c3_y[c3_i28] = c3_uv0[c3_i28];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_in;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  uint32_T c3_y[15];
  int32_T c3_i29;
  SFc3_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc3_vipcodecInstanceStruct *)chartInstanceVoid;
  c3_in = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_in), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_in);
  for (c3_i29 = 0; c3_i29 < 15; c3_i29++) {
    (*(uint32_T (*)[15])c3_outData)[c3_i29] = c3_y[c3_i29];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

const mxArray *sf_c3_vipcodec_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo;
  c3_ResolvedFunctionInfo c3_info[17];
  const mxArray *c3_m0 = NULL;
  int32_T c3_i30;
  c3_ResolvedFunctionInfo *c3_r0;
  c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  c3_info_helper(c3_info);
  sf_mex_assign(&c3_m0, sf_mex_createstruct("nameCaptureInfo", 1, 17));
  for (c3_i30 = 0; c3_i30 < 17; c3_i30++) {
    c3_r0 = &c3_info[c3_i30];
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r0->context)), "context", "nameCaptureInfo",
                    c3_i30);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c3_r0->name)), "name", "nameCaptureInfo", c3_i30);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c3_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c3_i30);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r0->resolved)), "resolved", "nameCaptureInfo",
                    c3_i30);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c3_i30);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c3_i30);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c3_i30);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c3_i30);
  }

  sf_mex_assign(&c3_nameCaptureInfo, c3_m0);
  return c3_nameCaptureInfo;
}

static void c3_info_helper(c3_ResolvedFunctionInfo c3_info[17])
{
  c3_info[0].context = "";
  c3_info[0].name = "bitget";
  c3_info[0].dominantType = "uint32";
  c3_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c3_info[0].fileTimeLo = 1286815236U;
  c3_info[0].fileTimeHi = 0U;
  c3_info[0].mFileTimeLo = 0U;
  c3_info[0].mFileTimeHi = 0U;
  c3_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c3_info[1].name = "eml_scalar_eg";
  c3_info[1].dominantType = "uint32";
  c3_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c3_info[1].fileTimeLo = 1286815196U;
  c3_info[1].fileTimeHi = 0U;
  c3_info[1].mFileTimeLo = 0U;
  c3_info[1].mFileTimeHi = 0U;
  c3_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c3_info[2].name = "eml_scalexp_alloc";
  c3_info[2].dominantType = "uint32";
  c3_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c3_info[2].fileTimeLo = 1286815196U;
  c3_info[2].fileTimeHi = 0U;
  c3_info[2].mFileTimeLo = 0U;
  c3_info[2].mFileTimeHi = 0U;
  c3_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c3_info[3].name = "eml_isa_uint";
  c3_info[3].dominantType = "uint32";
  c3_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  c3_info[3].fileTimeLo = 1286815184U;
  c3_info[3].fileTimeHi = 0U;
  c3_info[3].mFileTimeLo = 0U;
  c3_info[3].mFileTimeHi = 0U;
  c3_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c3_info[4].name = "eml_int_nbits";
  c3_info[4].dominantType = "char";
  c3_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_nbits.m";
  c3_info[4].fileTimeLo = 1286815180U;
  c3_info[4].fileTimeHi = 0U;
  c3_info[4].mFileTimeLo = 0U;
  c3_info[4].mFileTimeHi = 0U;
  c3_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c3_info[5].name = "floor";
  c3_info[5].dominantType = "double";
  c3_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c3_info[5].fileTimeLo = 1286815142U;
  c3_info[5].fileTimeHi = 0U;
  c3_info[5].mFileTimeLo = 0U;
  c3_info[5].mFileTimeHi = 0U;
  c3_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c3_info[6].name = "eml_scalar_floor";
  c3_info[6].dominantType = "double";
  c3_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c3_info[6].fileTimeLo = 1286815126U;
  c3_info[6].fileTimeHi = 0U;
  c3_info[6].mFileTimeLo = 0U;
  c3_info[6].mFileTimeHi = 0U;
  c3_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c3_info[7].name = "eml_error";
  c3_info[7].dominantType = "uint8";
  c3_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c3_info[7].fileTimeLo = 1286815100U;
  c3_info[7].fileTimeHi = 0U;
  c3_info[7].mFileTimeLo = 0U;
  c3_info[7].mFileTimeHi = 0U;
  c3_info[8].context = "";
  c3_info[8].name = "intmax";
  c3_info[8].dominantType = "char";
  c3_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c3_info[8].fileTimeLo = 1286815156U;
  c3_info[8].fileTimeHi = 0U;
  c3_info[8].mFileTimeLo = 0U;
  c3_info[8].mFileTimeHi = 0U;
  c3_info[9].context = "";
  c3_info[9].name = "length";
  c3_info[9].dominantType = "uint32";
  c3_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c3_info[9].fileTimeLo = 1286815160U;
  c3_info[9].fileTimeHi = 0U;
  c3_info[9].mFileTimeLo = 0U;
  c3_info[9].mFileTimeHi = 0U;
  c3_info[10].context = "";
  c3_info[10].name = "bitshift";
  c3_info[10].dominantType = "uint32";
  c3_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c3_info[10].fileTimeLo = 1286815238U;
  c3_info[10].fileTimeHi = 0U;
  c3_info[10].mFileTimeLo = 0U;
  c3_info[10].mFileTimeHi = 0U;
  c3_info[11].context = "";
  c3_info[11].name = "bitor";
  c3_info[11].dominantType = "uint32";
  c3_info[11].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitor.m";
  c3_info[11].fileTimeLo = 1286815236U;
  c3_info[11].fileTimeHi = 0U;
  c3_info[11].mFileTimeLo = 0U;
  c3_info[11].mFileTimeHi = 0U;
  c3_info[12].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitor.m";
  c3_info[12].name = "eml_scalexp_compatible";
  c3_info[12].dominantType = "uint32";
  c3_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c3_info[12].fileTimeLo = 1286815196U;
  c3_info[12].fileTimeHi = 0U;
  c3_info[12].mFileTimeLo = 0U;
  c3_info[12].mFileTimeHi = 0U;
  c3_info[13].context = "";
  c3_info[13].name = "min";
  c3_info[13].dominantType = "uint32";
  c3_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c3_info[13].fileTimeLo = 1286815096U;
  c3_info[13].fileTimeHi = 0U;
  c3_info[13].mFileTimeLo = 0U;
  c3_info[13].mFileTimeHi = 0U;
  c3_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c3_info[14].name = "eml_min_or_max";
  c3_info[14].dominantType = "uint32";
  c3_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c3_info[14].fileTimeLo = 1286815188U;
  c3_info[14].fileTimeHi = 0U;
  c3_info[14].mFileTimeLo = 0U;
  c3_info[14].mFileTimeHi = 0U;
  c3_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c3_info[15].name = "eml_index_class";
  c3_info[15].dominantType = "";
  c3_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[15].fileTimeLo = 1286815178U;
  c3_info[15].fileTimeHi = 0U;
  c3_info[15].mFileTimeLo = 0U;
  c3_info[15].mFileTimeHi = 0U;
  c3_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c3_info[16].name = "isnan";
  c3_info[16].dominantType = "uint32";
  c3_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c3_info[16].fileTimeLo = 1286815160U;
  c3_info[16].fileTimeHi = 0U;
  c3_info[16].mFileTimeLo = 0U;
  c3_info[16].mFileTimeHi = 0U;
}

static void c3_getbits(SFc3_vipcodecInstanceStruct *chartInstance, int32_T
  c3_cbits, real_T c3_inpos, uint32_T c3_Temp, uint32_T c3_in[15], uint32_T
  c3_val, real_T c3_bits, real_T *c3_flag, int32_T *c3_cbitsO, real_T *c3_inposO,
  uint32_T *c3_TempO, uint32_T *c3_valO)
{
  uint32_T c3_debug_family_var_map[16];
  uint32_T c3_lval;
  uint32_T c3_temp;
  real_T c3_inwidth;
  real_T c3_nargin = 6.0;
  real_T c3_nargout = 5.0;
  uint32_T c3_a;
  int64_T c3_i31;
  int32_T c3_i32;
  int32_T c3_saturatedUnaryMinus;
  int32_T c3_k;
  int32_T c3_x;
  int32_T c3_b_x;
  uint32_T c3_a1;
  int32_T c3_k1;
  int32_T c3_i33;
  int32_T c3_b_saturatedUnaryMinus;
  int32_T c3_i34;
  uint8_T c3_absk1;
  int32_T c3_i35;
  real_T c3_d4;
  real_T c3_d5;
  real_T c3_d6;
  int32_T c3_i36;
  uint32_T c3_b_a;
  real_T c3_b_k;
  real_T c3_c_x;
  real_T c3_d_x;
  uint32_T c3_b_a1;
  real_T c3_b_k1;
  real_T c3_d7;
  real_T c3_d8;
  real_T c3_d9;
  uint8_T c3_u5;
  uint8_T c3_b_absk1;
  real_T c3_d10;
  real_T c3_d11;
  real_T c3_d12;
  uint8_T c3_u6;
  uint32_T c3_c_a;
  real_T c3_c_k;
  real_T c3_e_x;
  real_T c3_f_x;
  uint32_T c3_c_a1;
  real_T c3_c_k1;
  real_T c3_d13;
  real_T c3_d14;
  real_T c3_d15;
  uint8_T c3_u7;
  uint8_T c3_c_absk1;
  real_T c3_d16;
  real_T c3_d17;
  real_T c3_d18;
  uint8_T c3_u8;
  uint32_T c3_d_a;
  real_T c3_d_k;
  real_T c3_g_x;
  real_T c3_h_x;
  uint32_T c3_d_a1;
  real_T c3_d_k1;
  real_T c3_d19;
  real_T c3_d20;
  real_T c3_d21;
  uint8_T c3_u9;
  uint8_T c3_d_absk1;
  real_T c3_d22;
  real_T c3_d23;
  real_T c3_d24;
  uint8_T c3_u10;
  uint32_T c3_e_a;
  uint32_T c3_b;
  real_T c3_d25;
  real_T c3_d26;
  real_T c3_d27;
  int32_T c3_i37;
  boolean_T guard1 = FALSE;
  sf_debug_symbol_scope_push_eml(0U, 16U, 16U, c3_b_debug_family_names,
    c3_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c3_lval, 0U, c3_e_sf_marshallOut,
    c3_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_temp, 1U, c3_e_sf_marshallOut,
    c3_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_inwidth, 2U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_nargin, 3U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_nargout, 4U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_cbits, 5U, c3_f_sf_marshallOut,
    c3_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_inpos, 6U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_Temp, 7U, c3_e_sf_marshallOut,
    c3_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c3_in, 8U, c3_g_sf_marshallOut,
    c3_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_val, 9U, c3_e_sf_marshallOut,
    c3_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_bits, 10U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c3_flag, 11U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c3_cbitsO, 12U, c3_f_sf_marshallOut,
    c3_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c3_inposO, 13U, c3_d_sf_marshallOut,
    c3_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c3_TempO, 14U, c3_e_sf_marshallOut,
    c3_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c3_valO, 15U, c3_e_sf_marshallOut,
    c3_d_sf_marshallIn);
  CV_EML_FCN(0, 1);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 56);
  c3_lval = 0U;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 57);
  c3_temp = 0U;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 58);
  *c3_cbitsO = c3_cbits;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 59);
  *c3_inposO = c3_inpos;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 60);
  *c3_TempO = c3_Temp;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 61);
  *c3_valO = c3_val;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 62);
  c3_inwidth = 15.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 63);
  guard1 = FALSE;
  if (CV_EML_IF(0, 5, (real_T)*c3_cbitsO < c3_bits)) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 64);
    if (CV_EML_IF(0, 6, *c3_inposO > c3_inwidth)) {
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 65);
      *c3_flag = 0.0;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 69);
      c3_a = *c3_TempO;
      c3_i31 = (int64_T)32 - (int64_T)*c3_cbitsO;
      if (c3_i31 > 2147483647L) {
        c3_i31 = 2147483647L;
      } else {
        if (c3_i31 <= -2147483648L) {
          c3_i31 = -2147483648L;
        }
      }

      c3_i32 = (int32_T)c3_i31;
      if (c3_i32 <= MIN_int32_T) {
        c3_saturatedUnaryMinus = MAX_int32_T;
      } else {
        c3_saturatedUnaryMinus = -c3_i32;
      }

      c3_k = c3_saturatedUnaryMinus;
      c3_x = c3_k;
      c3_b_x = c3_x;
      if (c3_k != c3_b_x) {
        c3_eml_error(chartInstance);
      }

      c3_a1 = c3_a;
      c3_k1 = c3_k;
      c3_lval = 0U;
      if ((real_T)c3_k1 < 0.0) {
        c3_i33 = c3_k1;
        if (c3_i33 <= MIN_int32_T) {
          c3_b_saturatedUnaryMinus = MAX_int32_T;
        } else {
          c3_b_saturatedUnaryMinus = -c3_i33;
        }

        c3_i34 = c3_b_saturatedUnaryMinus;
        if (c3_i34 <= 0) {
          c3_i34 = 0;
        } else {
          if (c3_i34 > 255) {
            c3_i34 = 255;
          }
        }

        c3_absk1 = (uint8_T)c3_i34;
        if (c3_absk1 < 32) {
          c3_lval = c3_a1 >> (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c3_absk1), 0, 31, 1,
            1);
        }
      } else {
        c3_i35 = c3_k1;
        if (c3_i35 <= 0) {
          c3_i35 = 0;
        } else {
          if (c3_i35 > 255) {
            c3_i35 = 255;
          }
        }

        c3_absk1 = (uint8_T)c3_i35;
        if (c3_absk1 < 32) {
          c3_lval = c3_a1 << (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c3_absk1), 0, 31, 1,
            1);
        }
      }

      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 70);
      c3_d4 = c3_bits - (real_T)*c3_cbitsO;
      c3_d5 = c3_d4;
      c3_d5 = c3_d5 < 0.0 ? muDoubleScalarCeil(c3_d5 - 0.5) :
        muDoubleScalarFloor(c3_d5 + 0.5);
      c3_d6 = c3_d5;
      if (c3_d6 < 2.147483648E+9) {
        if (c3_d6 >= -2.147483648E+9) {
          c3_i36 = (int32_T)c3_d6;
        } else {
          c3_i36 = MIN_int32_T;
        }
      } else if (c3_d6 >= 2.147483648E+9) {
        c3_i36 = MAX_int32_T;
      } else {
        c3_i36 = 0;
      }

      c3_bits = (real_T)c3_i36;
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 71);
      *c3_TempO = c3_in[_SFD_EML_ARRAY_BOUNDS_CHECK("in", (int32_T)
        _SFD_INTEGER_CHECK("inposO", *c3_inposO), 1, 15, 1, 0) - 1];
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 71);
      (*c3_inposO)++;
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 72);
      c3_b_a = c3_lval;
      c3_b_k = c3_bits;
      c3_c_x = c3_b_k;
      c3_d_x = c3_c_x;
      c3_d_x = muDoubleScalarFloor(c3_d_x);
      if (c3_b_k != c3_d_x) {
        c3_eml_error(chartInstance);
      }

      c3_b_a1 = c3_b_a;
      c3_b_k1 = c3_b_k;
      c3_lval = 0U;
      if (c3_b_k1 < 0.0) {
        c3_d7 = -c3_b_k1;
        c3_d8 = c3_d7;
        c3_d8 = c3_d8 < 0.0 ? muDoubleScalarCeil(c3_d8 - 0.5) :
          muDoubleScalarFloor(c3_d8 + 0.5);
        c3_d9 = c3_d8;
        if (c3_d9 < 256.0) {
          if (c3_d9 >= 0.0) {
            c3_u5 = (uint8_T)c3_d9;
          } else {
            c3_u5 = 0U;
          }
        } else if (c3_d9 >= 256.0) {
          c3_u5 = MAX_uint8_T;
        } else {
          c3_u5 = 0U;
        }

        c3_b_absk1 = c3_u5;
        if (c3_b_absk1 < 32) {
          c3_lval = c3_b_a1 >> (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c3_b_absk1), 0, 31,
            1, 1);
        }
      } else {
        c3_d10 = c3_b_k1;
        c3_d11 = c3_d10;
        c3_d11 = c3_d11 < 0.0 ? muDoubleScalarCeil(c3_d11 - 0.5) :
          muDoubleScalarFloor(c3_d11 + 0.5);
        c3_d12 = c3_d11;
        if (c3_d12 < 256.0) {
          if (c3_d12 >= 0.0) {
            c3_u6 = (uint8_T)c3_d12;
          } else {
            c3_u6 = 0U;
          }
        } else if (c3_d12 >= 256.0) {
          c3_u6 = MAX_uint8_T;
        } else {
          c3_u6 = 0U;
        }

        c3_b_absk1 = c3_u6;
        if (c3_b_absk1 < 32) {
          c3_lval = c3_b_a1 << (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c3_b_absk1), 0, 31,
            1, 1);
        }
      }

      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 73);
      *c3_cbitsO = 32;
      guard1 = TRUE;
    }
  } else {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 76);
    c3_c_a = *c3_TempO;
    c3_c_k = -(32.0 - c3_bits);
    c3_e_x = c3_c_k;
    c3_f_x = c3_e_x;
    c3_f_x = muDoubleScalarFloor(c3_f_x);
    if (c3_c_k != c3_f_x) {
      c3_eml_error(chartInstance);
    }

    c3_c_a1 = c3_c_a;
    c3_c_k1 = c3_c_k;
    c3_temp = 0U;
    if (c3_c_k1 < 0.0) {
      c3_d13 = -c3_c_k1;
      c3_d14 = c3_d13;
      c3_d14 = c3_d14 < 0.0 ? muDoubleScalarCeil(c3_d14 - 0.5) :
        muDoubleScalarFloor(c3_d14 + 0.5);
      c3_d15 = c3_d14;
      if (c3_d15 < 256.0) {
        if (c3_d15 >= 0.0) {
          c3_u7 = (uint8_T)c3_d15;
        } else {
          c3_u7 = 0U;
        }
      } else if (c3_d15 >= 256.0) {
        c3_u7 = MAX_uint8_T;
      } else {
        c3_u7 = 0U;
      }

      c3_c_absk1 = c3_u7;
      if (c3_c_absk1 < 32) {
        c3_temp = c3_c_a1 >> (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c3_c_absk1), 0, 31, 1,
          1);
      }
    } else {
      c3_d16 = c3_c_k1;
      c3_d17 = c3_d16;
      c3_d17 = c3_d17 < 0.0 ? muDoubleScalarCeil(c3_d17 - 0.5) :
        muDoubleScalarFloor(c3_d17 + 0.5);
      c3_d18 = c3_d17;
      if (c3_d18 < 256.0) {
        if (c3_d18 >= 0.0) {
          c3_u8 = (uint8_T)c3_d18;
        } else {
          c3_u8 = 0U;
        }
      } else if (c3_d18 >= 256.0) {
        c3_u8 = MAX_uint8_T;
      } else {
        c3_u8 = 0U;
      }

      c3_c_absk1 = c3_u8;
      if (c3_c_absk1 < 32) {
        c3_temp = c3_c_a1 << (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c3_c_absk1), 0, 31, 1,
          1);
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 77);
    c3_d_a = *c3_TempO;
    c3_d_k = c3_bits;
    c3_g_x = c3_d_k;
    c3_h_x = c3_g_x;
    c3_h_x = muDoubleScalarFloor(c3_h_x);
    if (c3_d_k != c3_h_x) {
      c3_eml_error(chartInstance);
    }

    c3_d_a1 = c3_d_a;
    c3_d_k1 = c3_d_k;
    *c3_TempO = 0U;
    if (c3_d_k1 < 0.0) {
      c3_d19 = -c3_d_k1;
      c3_d20 = c3_d19;
      c3_d20 = c3_d20 < 0.0 ? muDoubleScalarCeil(c3_d20 - 0.5) :
        muDoubleScalarFloor(c3_d20 + 0.5);
      c3_d21 = c3_d20;
      if (c3_d21 < 256.0) {
        if (c3_d21 >= 0.0) {
          c3_u9 = (uint8_T)c3_d21;
        } else {
          c3_u9 = 0U;
        }
      } else if (c3_d21 >= 256.0) {
        c3_u9 = MAX_uint8_T;
      } else {
        c3_u9 = 0U;
      }

      c3_d_absk1 = c3_u9;
      if (c3_d_absk1 < 32) {
        *c3_TempO = c3_d_a1 >> (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c3_d_absk1), 0, 31, 1,
          1);
      }
    } else {
      c3_d22 = c3_d_k1;
      c3_d23 = c3_d22;
      c3_d23 = c3_d23 < 0.0 ? muDoubleScalarCeil(c3_d23 - 0.5) :
        muDoubleScalarFloor(c3_d23 + 0.5);
      c3_d24 = c3_d23;
      if (c3_d24 < 256.0) {
        if (c3_d24 >= 0.0) {
          c3_u10 = (uint8_T)c3_d24;
        } else {
          c3_u10 = 0U;
        }
      } else if (c3_d24 >= 256.0) {
        c3_u10 = MAX_uint8_T;
      } else {
        c3_u10 = 0U;
      }

      c3_d_absk1 = c3_u10;
      if (c3_d_absk1 < 32) {
        *c3_TempO = c3_d_a1 << (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c3_d_absk1), 0, 31, 1,
          1);
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 78);
    c3_e_a = c3_lval;
    c3_b = c3_temp;
    *c3_valO = c3_e_a | c3_b;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 79);
    c3_d25 = (real_T)*c3_cbitsO - c3_bits;
    c3_d26 = c3_d25;
    c3_d26 = c3_d26 < 0.0 ? muDoubleScalarCeil(c3_d26 - 0.5) :
      muDoubleScalarFloor(c3_d26 + 0.5);
    c3_d27 = c3_d26;
    if (c3_d27 < 2.147483648E+9) {
      if (c3_d27 >= -2.147483648E+9) {
        c3_i37 = (int32_T)c3_d27;
      } else {
        c3_i37 = MIN_int32_T;
      }
    } else if (c3_d27 >= 2.147483648E+9) {
      c3_i37 = MAX_int32_T;
    } else {
      c3_i37 = 0;
    }

    *c3_cbitsO = c3_i37;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 81);
    *c3_flag = 1.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, -81);
  sf_debug_symbol_scope_pop();
}

static void c3_eml_error(SFc3_vipcodecInstanceStruct *chartInstance)
{
  int32_T c3_i38;
  static char_T c3_varargin_1[42] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'b', 'i', 't', 's', 'h', 'i', 'f', 't', '_', 'i',
    'n', 'p', 'u', 't', 's', 'M', 'u', 's', 't', 'B', 'e', 'I', 'n', 't', 'e',
    'g', 'e', 'r', 's' };

  char_T c3_u[42];
  const mxArray *c3_y = NULL;
  for (c3_i38 = 0; c3_i38 < 42; c3_i38++) {
    c3_u[c3_i38] = c3_varargin_1[c3_i38];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 42));
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U, 14,
    c3_y));
}

static void c3_eml_scalar_eg(SFc3_vipcodecInstanceStruct *chartInstance)
{
}

static uint8_T c3_i_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_vipcodec, const char_T *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_b_is_active_c3_vipcodec), &c3_thisId);
  sf_mex_destroy(&c3_b_is_active_c3_vipcodec);
  return c3_y;
}

static uint8_T c3_j_emlrt_marshallIn(SFc3_vipcodecInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u11;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u11, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u11;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void init_dsm_address_info(SFc3_vipcodecInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c3_vipcodec_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3499007692U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2842537415U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(860946988U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2887679911U);
}

mxArray *sf_c3_vipcodec_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(2891418207U);
    pr[1] = (double)(2855042616U);
    pr[2] = (double)(3264998034U);
    pr[3] = (double)(1114649224U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(15);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(7));
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
      pr[0] = (double)(64);
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

static const mxArray *sf_get_sim_state_info_c3_vipcodec(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"out\",},{M[4],M[0],T\"prev_out\",S'l','i','p'{{M1x2[188 196],M[0],}}},{M[8],M[0],T\"is_active_c3_vipcodec\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_vipcodec_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_vipcodecInstanceStruct *chartInstance;
    chartInstance = (SFc3_vipcodecInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart(_vipcodecMachineNumber_,
          3,
          1,
          1,
          2,
          0,
          0,
          0,
          0,
          0,
          &(chartInstance->chartNumber),
          &(chartInstance->instanceNumber),
          ssGetPath(S),
          (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_vipcodecMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting(_vipcodecMachineNumber_,
            chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_vipcodecMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"in");
          _SFD_SET_DATA_PROPS(1,2,0,1,"out");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,2,7,0,0,2,1,2,2);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1294);
        _SFD_CV_INIT_EML_FCN(0,1,"getbits",1348,-1,2099);
        _SFD_CV_INIT_EML_IF(0,0,198,218,-1,258);
        _SFD_CV_INIT_EML_IF(0,1,407,426,507,548);
        _SFD_CV_INIT_EML_IF(0,2,769,779,821,849);
        _SFD_CV_INIT_EML_IF(0,3,821,835,968,1011);
        _SFD_CV_INIT_EML_IF(0,4,968,978,-1,-2);
        _SFD_CV_INIT_EML_IF(0,5,1611,1629,-1,1929);
        _SFD_CV_INIT_EML_IF(0,6,1640,1661,-1,-2);
        _SFD_CV_INIT_EML_FOR(0,0,1030,1061,1126);
        _SFD_CV_INIT_EML_FOR(0,1,1221,1238,1269);
        _SFD_CV_INIT_EML_WHILE(0,0,645,664,1165);

        {
          static int condStart[] = { 774 };

          static int condEnd[] = { 778 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_EML_MCDC(0,0,773,778,1,0,&(condStart[0]),&(condEnd[0]),2,
                                &(pfixExpr[0]));
        }

        {
          static int condStart[] = { 973 };

          static int condEnd[] = { 977 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_EML_MCDC(0,1,972,977,1,1,&(condStart[0]),&(condEnd[0]),2,
                                &(pfixExpr[0]));
        }

        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 15;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT32,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 64;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_SINGLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)
            c3_b_sf_marshallIn);
        }

        {
          uint32_T (*c3_in)[15];
          real32_T (*c3_out)[64];
          c3_out = (real32_T (*)[64])ssGetOutputPortSignal(chartInstance->S, 1);
          c3_in = (uint32_T (*)[15])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c3_in);
          _SFD_SET_DATA_VALUE_PTR(1U, *c3_out);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_vipcodecMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c3_vipcodec(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_vipcodecInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c3_vipcodec((SFc3_vipcodecInstanceStruct*) chartInstanceVar);
  initialize_c3_vipcodec((SFc3_vipcodecInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c3_vipcodec(void *chartInstanceVar)
{
  enable_c3_vipcodec((SFc3_vipcodecInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_vipcodec(void *chartInstanceVar)
{
  disable_c3_vipcodec((SFc3_vipcodecInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_vipcodec(void *chartInstanceVar)
{
  sf_c3_vipcodec((SFc3_vipcodecInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c3_vipcodec(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_vipcodec((SFc3_vipcodecInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_vipcodec();/* state var info */
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

extern void sf_internal_set_sim_state_c3_vipcodec(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_vipcodec();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_vipcodec((SFc3_vipcodecInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c3_vipcodec(SimStruct* S)
{
  return sf_internal_get_sim_state_c3_vipcodec(S);
}

static void sf_opaque_set_sim_state_c3_vipcodec(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c3_vipcodec(S, st);
}

static void sf_opaque_terminate_c3_vipcodec(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_vipcodecInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c3_vipcodec((SFc3_vipcodecInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_vipcodec((SFc3_vipcodecInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_vipcodec(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_vipcodec((SFc3_vipcodecInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_vipcodec(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"vipcodec","vipcodec",3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"vipcodec","vipcodec",3,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"vipcodec","vipcodec",3,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"vipcodec","vipcodec",3,1);
      sf_mark_chart_reusable_outputs(S,"vipcodec","vipcodec",3,1);
    }

    sf_set_rtw_dwork_info(S,"vipcodec","vipcodec",3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(4242124724U));
  ssSetChecksum1(S,(1315326251U));
  ssSetChecksum2(S,(3826938656U));
  ssSetChecksum3(S,(1321036376U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c3_vipcodec(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "vipcodec", "vipcodec",3);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_vipcodec(SimStruct *S)
{
  SFc3_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc3_vipcodecInstanceStruct *)malloc(sizeof
    (SFc3_vipcodecInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_vipcodecInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_vipcodec;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c3_vipcodec;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_vipcodec;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_vipcodec;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_vipcodec;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c3_vipcodec;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c3_vipcodec;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c3_vipcodec;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_vipcodec;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_vipcodec;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_vipcodec;
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
  chart_debug_initialization(S,1);
}

void c3_vipcodec_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_vipcodec(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_vipcodec(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_vipcodec(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_vipcodec_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
