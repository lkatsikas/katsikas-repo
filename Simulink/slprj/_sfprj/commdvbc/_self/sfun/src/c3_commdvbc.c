/* Include files */

#include "blascompat32.h"
#include "commdvbc_sfun.h"
#include "c3_commdvbc.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "commdvbc_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c3_debug_family_names[16] = { "symbolWL", "symWLMn1",
  "bit_wts", "b", "A_k", "B_k", "xor_Ak_Bk", "not_xor_Ak_Bk", "I_k", "Q_k",
  "nargin", "nargout", "u", "y", "I_kMinusOne", "Q_kMinusOne" };

/* Function Declarations */
static void initialize_c3_commdvbc(SFc3_commdvbcInstanceStruct *chartInstance);
static void initialize_params_c3_commdvbc(SFc3_commdvbcInstanceStruct
  *chartInstance);
static void enable_c3_commdvbc(SFc3_commdvbcInstanceStruct *chartInstance);
static void disable_c3_commdvbc(SFc3_commdvbcInstanceStruct *chartInstance);
static void c3_update_debugger_state_c3_commdvbc(SFc3_commdvbcInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c3_commdvbc(SFc3_commdvbcInstanceStruct
  *chartInstance);
static void set_sim_state_c3_commdvbc(SFc3_commdvbcInstanceStruct *chartInstance,
  const mxArray *c3_st);
static void finalize_c3_commdvbc(SFc3_commdvbcInstanceStruct *chartInstance);
static void sf_c3_commdvbc(SFc3_commdvbcInstanceStruct *chartInstance);
static void c3_chartstep_c3_commdvbc(SFc3_commdvbcInstanceStruct *chartInstance);
static void initSimStructsc3_commdvbc(SFc3_commdvbcInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData);
static boolean_T c3_emlrt_marshallIn(SFc3_commdvbcInstanceStruct *chartInstance,
  const mxArray *c3_b_Q_kMinusOne, const char_T *c3_identifier);
static boolean_T c3_b_emlrt_marshallIn(SFc3_commdvbcInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static boolean_T c3_c_emlrt_marshallIn(SFc3_commdvbcInstanceStruct
  *chartInstance, const mxArray *c3_b_I_kMinusOne, const char_T *c3_identifier);
static boolean_T c3_d_emlrt_marshallIn(SFc3_commdvbcInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_e_emlrt_marshallIn(SFc3_commdvbcInstanceStruct *chartInstance,
  const mxArray *c3_y, const char_T *c3_identifier, uint8_T c3_b_y[272]);
static void c3_f_emlrt_marshallIn(SFc3_commdvbcInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_y[272]);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_g_emlrt_marshallIn(SFc3_commdvbcInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static boolean_T c3_h_emlrt_marshallIn(SFc3_commdvbcInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_i_emlrt_marshallIn(SFc3_commdvbcInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, boolean_T c3_y[6]);
static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_h_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_realmax(SFc3_commdvbcInstanceStruct *chartInstance);
static void c3_eml_scalar_eg(SFc3_commdvbcInstanceStruct *chartInstance);
static void c3_eml_int_forloop_overflow_check(SFc3_commdvbcInstanceStruct
  *chartInstance);
static const mxArray *c3_i_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_j_emlrt_marshallIn(SFc3_commdvbcInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static uint8_T c3_k_emlrt_marshallIn(SFc3_commdvbcInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_commdvbc, const char_T *c3_identifier);
static uint8_T c3_l_emlrt_marshallIn(SFc3_commdvbcInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void init_dsm_address_info(SFc3_commdvbcInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c3_commdvbc(SFc3_commdvbcInstanceStruct *chartInstance)
{
  chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c3_I_kMinusOne_not_empty = FALSE;
  chartInstance->c3_Q_kMinusOne_not_empty = FALSE;
  chartInstance->c3_is_active_c3_commdvbc = 0U;
}

static void initialize_params_c3_commdvbc(SFc3_commdvbcInstanceStruct
  *chartInstance)
{
}

static void enable_c3_commdvbc(SFc3_commdvbcInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c3_commdvbc(SFc3_commdvbcInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c3_update_debugger_state_c3_commdvbc(SFc3_commdvbcInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c3_commdvbc(SFc3_commdvbcInstanceStruct
  *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  int32_T c3_i0;
  uint8_T c3_u[272];
  const mxArray *c3_b_y = NULL;
  boolean_T c3_hoistedGlobal;
  boolean_T c3_b_u;
  const mxArray *c3_c_y = NULL;
  boolean_T c3_b_hoistedGlobal;
  boolean_T c3_c_u;
  const mxArray *c3_d_y = NULL;
  uint8_T c3_c_hoistedGlobal;
  uint8_T c3_d_u;
  const mxArray *c3_e_y = NULL;
  uint8_T (*c3_f_y)[272];
  c3_f_y = (uint8_T (*)[272])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellarray(4), FALSE);
  for (c3_i0 = 0; c3_i0 < 272; c3_i0++) {
    c3_u[c3_i0] = (*c3_f_y)[c3_i0];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_u, 3, 0U, 1U, 0U, 1, 272), FALSE);
  sf_mex_setcell(c3_y, 0, c3_b_y);
  c3_hoistedGlobal = chartInstance->c3_I_kMinusOne;
  c3_b_u = c3_hoistedGlobal;
  c3_c_y = NULL;
  if (!chartInstance->c3_I_kMinusOne_not_empty) {
    sf_mex_assign(&c3_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c3_c_y, sf_mex_create("y", &c3_b_u, 11, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c3_y, 1, c3_c_y);
  c3_b_hoistedGlobal = chartInstance->c3_Q_kMinusOne;
  c3_c_u = c3_b_hoistedGlobal;
  c3_d_y = NULL;
  if (!chartInstance->c3_Q_kMinusOne_not_empty) {
    sf_mex_assign(&c3_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c3_d_y, sf_mex_create("y", &c3_c_u, 11, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c3_y, 2, c3_d_y);
  c3_c_hoistedGlobal = chartInstance->c3_is_active_c3_commdvbc;
  c3_d_u = c3_c_hoistedGlobal;
  c3_e_y = NULL;
  sf_mex_assign(&c3_e_y, sf_mex_create("y", &c3_d_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c3_y, 3, c3_e_y);
  sf_mex_assign(&c3_st, c3_y, FALSE);
  return c3_st;
}

static void set_sim_state_c3_commdvbc(SFc3_commdvbcInstanceStruct *chartInstance,
  const mxArray *c3_st)
{
  const mxArray *c3_u;
  uint8_T c3_uv0[272];
  int32_T c3_i1;
  uint8_T (*c3_y)[272];
  c3_y = (uint8_T (*)[272])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c3_doneDoubleBufferReInit = TRUE;
  c3_u = sf_mex_dup(c3_st);
  c3_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 0)), "y",
                        c3_uv0);
  for (c3_i1 = 0; c3_i1 < 272; c3_i1++) {
    (*c3_y)[c3_i1] = c3_uv0[c3_i1];
  }

  chartInstance->c3_I_kMinusOne = c3_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_u, 1)), "I_kMinusOne");
  chartInstance->c3_Q_kMinusOne = c3_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_u, 2)), "Q_kMinusOne");
  chartInstance->c3_is_active_c3_commdvbc = c3_k_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_u, 3)), "is_active_c3_commdvbc");
  sf_mex_destroy(&c3_u);
  c3_update_debugger_state_c3_commdvbc(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_commdvbc(SFc3_commdvbcInstanceStruct *chartInstance)
{
}

static void sf_c3_commdvbc(SFc3_commdvbcInstanceStruct *chartInstance)
{
  int32_T c3_i2;
  int32_T c3_i3;
  uint8_T (*c3_y)[272];
  uint8_T (*c3_u)[272];
  c3_y = (uint8_T (*)[272])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_u = (uint8_T (*)[272])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
  for (c3_i2 = 0; c3_i2 < 272; c3_i2++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c3_u)[c3_i2], 0U);
  }

  for (c3_i3 = 0; c3_i3 < 272; c3_i3++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c3_y)[c3_i3], 1U);
  }

  chartInstance->c3_sfEvent = CALL_EVENT;
  c3_chartstep_c3_commdvbc(chartInstance);
  sf_debug_check_for_state_inconsistency(_commdvbcMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c3_chartstep_c3_commdvbc(SFc3_commdvbcInstanceStruct *chartInstance)
{
  int32_T c3_i4;
  uint8_T c3_u[272];
  uint32_T c3_debug_family_var_map[16];
  real_T c3_symbolWL;
  real_T c3_symWLMn1;
  uint8_T c3_bit_wts[6];
  boolean_T c3_b[6];
  boolean_T c3_A_k;
  boolean_T c3_B_k;
  boolean_T c3_xor_Ak_Bk;
  boolean_T c3_not_xor_Ak_Bk;
  boolean_T c3_I_k;
  boolean_T c3_Q_k;
  real_T c3_nargin = 1.0;
  real_T c3_nargout = 1.0;
  uint8_T c3_y[272];
  int32_T c3_i5;
  int32_T c3_i6;
  static uint8_T c3_uv1[6] = { 32U, 16U, 8U, 4U, 2U, 1U };

  int32_T c3_symIdx;
  real_T c3_b_symIdx;
  real_T c3_a;
  int32_T c3_i7;
  static real_T c3_b_b[6] = { 0.03125, 0.0625, 0.125, 0.25, 0.5, 1.0 };

  real_T c3_b_y[6];
  int32_T c3_k;
  real_T c3_b_k;
  real_T c3_xk;
  real_T c3_x;
  real_T c3_r;
  real_T c3_b_r[6];
  int32_T c3_c_k;
  real_T c3_d_k;
  real_T c3_b_x;
  real_T c3_c_x;
  int32_T c3_i8;
  boolean_T c3_s;
  boolean_T c3_t;
  boolean_T c3_b_not_xor_Ak_Bk;
  boolean_T c3_hoistedGlobal;
  boolean_T c3_b_s;
  boolean_T c3_b_t;
  boolean_T c3_b0;
  boolean_T c3_b1;
  boolean_T c3_b_xor_Ak_Bk;
  boolean_T c3_b_hoistedGlobal;
  boolean_T c3_c_s;
  boolean_T c3_c_t;
  boolean_T c3_b2;
  boolean_T c3_b3;
  boolean_T c3_c_not_xor_Ak_Bk;
  boolean_T c3_c_hoistedGlobal;
  boolean_T c3_d_s;
  boolean_T c3_d_t;
  boolean_T c3_b4;
  boolean_T c3_b5;
  boolean_T c3_c_xor_Ak_Bk;
  boolean_T c3_d_hoistedGlobal;
  boolean_T c3_e_s;
  boolean_T c3_e_t;
  boolean_T c3_b6;
  boolean_T c3_b7;
  int32_T c3_i9;
  real_T c3_c_y;
  int32_T c3_e_k;
  int32_T c3_f_k;
  static real_T c3_c_b[6] = { 32.0, 16.0, 8.0, 4.0, 2.0, 1.0 };

  real_T c3_d0;
  uint8_T c3_u0;
  int32_T c3_i10;
  uint8_T (*c3_d_y)[272];
  uint8_T (*c3_b_u)[272];
  c3_d_y = (uint8_T (*)[272])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_b_u = (uint8_T (*)[272])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
  for (c3_i4 = 0; c3_i4 < 272; c3_i4++) {
    c3_u[c3_i4] = (*c3_b_u)[c3_i4];
  }

  sf_debug_symbol_scope_push_eml(0U, 16U, 16U, c3_debug_family_names,
    c3_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c3_symbolWL, 0U, c3_e_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c3_symWLMn1, 1U, c3_e_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c3_bit_wts, 2U, c3_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c3_b, 3U, c3_g_sf_marshallOut,
    c3_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_A_k, 4U, c3_f_sf_marshallOut,
    c3_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_B_k, 5U, c3_f_sf_marshallOut,
    c3_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_xor_Ak_Bk, 6U,
    c3_f_sf_marshallOut, c3_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_not_xor_Ak_Bk, 7U,
    c3_f_sf_marshallOut, c3_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_I_k, 8U, c3_f_sf_marshallOut,
    c3_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_Q_k, 9U, c3_f_sf_marshallOut,
    c3_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_nargin, 10U, c3_e_sf_marshallOut,
    c3_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_nargout, 11U, c3_e_sf_marshallOut,
    c3_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c3_u, 12U, c3_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c3_y, 13U, c3_c_sf_marshallOut,
    c3_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&chartInstance->c3_I_kMinusOne, 14U,
    c3_b_sf_marshallOut, c3_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&chartInstance->c3_Q_kMinusOne, 15U,
    c3_sf_marshallOut, c3_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 4);
  for (c3_i5 = 0; c3_i5 < 272; c3_i5++) {
    c3_y[c3_i5] = c3_u[c3_i5];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 7);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c3_I_kMinusOne_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 8);
    chartInstance->c3_I_kMinusOne = FALSE;
    chartInstance->c3_I_kMinusOne_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 12);
  if (CV_EML_IF(0, 1, 1, !chartInstance->c3_Q_kMinusOne_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 13);
    chartInstance->c3_Q_kMinusOne = FALSE;
    chartInstance->c3_Q_kMinusOne_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 17);
  c3_symbolWL = 6.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 18);
  c3_symWLMn1 = 5.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 19);
  c3_realmax(chartInstance);
  for (c3_i6 = 0; c3_i6 < 6; c3_i6++) {
    c3_bit_wts[c3_i6] = c3_uv1[c3_i6];
  }

  c3_symIdx = 0;
  while (c3_symIdx < 272) {
    c3_b_symIdx = 1.0 + (real_T)c3_symIdx;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 32);
    c3_realmax(chartInstance);
    c3_a = (real_T)c3_u[_SFD_EML_ARRAY_BOUNDS_CHECK("u", (int32_T)
      _SFD_INTEGER_CHECK("symIdx", c3_b_symIdx), 1, 272, 1, 0) - 1];
    for (c3_i7 = 0; c3_i7 < 6; c3_i7++) {
      c3_b_y[c3_i7] = c3_a * c3_b_b[c3_i7];
    }

    for (c3_k = 0; c3_k < 6; c3_k++) {
      c3_b_k = 1.0 + (real_T)c3_k;
      c3_xk = c3_b_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
        ("", c3_b_k), 1, 6, 1, 0) - 1];
      c3_x = c3_xk;
      c3_r = muDoubleScalarRem(c3_x, 2.0);
      c3_b_r[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        c3_b_k), 1, 6, 1, 0) - 1] = c3_r;
    }

    for (c3_c_k = 0; c3_c_k < 6; c3_c_k++) {
      c3_d_k = 1.0 + (real_T)c3_c_k;
      c3_b_x = c3_b_r[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c3_d_k), 1, 6, 1, 0) - 1];
      c3_c_x = c3_b_x;
      c3_c_x = muDoubleScalarFloor(c3_c_x);
      c3_b_r[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        c3_d_k), 1, 6, 1, 0) - 1] = c3_c_x;
    }

    for (c3_i8 = 0; c3_i8 < 6; c3_i8++) {
      c3_b[c3_i8] = (c3_b_r[c3_i8] != 0.0);
    }

    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 35);
    c3_A_k = c3_b[0];
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 36);
    c3_B_k = c3_b[1];
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 39);
    c3_s = c3_A_k;
    c3_t = c3_B_k;
    c3_xor_Ak_Bk = ((uint8_T)((uint8_T)c3_s ^ (uint8_T)c3_t) != 0);
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 40);
    c3_not_xor_Ak_Bk = !c3_xor_Ak_Bk;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 42);
    c3_b_not_xor_Ak_Bk = c3_not_xor_Ak_Bk;
    c3_hoistedGlobal = chartInstance->c3_I_kMinusOne;
    c3_b_s = c3_A_k;
    c3_b_t = c3_hoistedGlobal;
    c3_b0 = ((uint8_T)((uint8_T)c3_b_s ^ (uint8_T)c3_b_t) != 0);
    c3_b1 = (c3_b_not_xor_Ak_Bk && c3_b0);
    c3_b_xor_Ak_Bk = c3_xor_Ak_Bk;
    c3_b_hoistedGlobal = chartInstance->c3_Q_kMinusOne;
    c3_c_s = c3_A_k;
    c3_c_t = c3_b_hoistedGlobal;
    c3_b2 = ((uint8_T)((uint8_T)c3_c_s ^ (uint8_T)c3_c_t) != 0);
    c3_b3 = (c3_b_xor_Ak_Bk && c3_b2);
    c3_I_k = (c3_b1 || c3_b3);
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 45);
    c3_c_not_xor_Ak_Bk = c3_not_xor_Ak_Bk;
    c3_c_hoistedGlobal = chartInstance->c3_Q_kMinusOne;
    c3_d_s = c3_B_k;
    c3_d_t = c3_c_hoistedGlobal;
    c3_b4 = ((uint8_T)((uint8_T)c3_d_s ^ (uint8_T)c3_d_t) != 0);
    c3_b5 = (c3_c_not_xor_Ak_Bk && c3_b4);
    c3_c_xor_Ak_Bk = c3_xor_Ak_Bk;
    c3_d_hoistedGlobal = chartInstance->c3_I_kMinusOne;
    c3_e_s = c3_B_k;
    c3_e_t = c3_d_hoistedGlobal;
    c3_b6 = ((uint8_T)((uint8_T)c3_e_s ^ (uint8_T)c3_e_t) != 0);
    c3_b7 = (c3_c_xor_Ak_Bk && c3_b6);
    c3_Q_k = (c3_b5 || c3_b7);
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 49);
    chartInstance->c3_I_kMinusOne = c3_I_k;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 50);
    c3_b[0] = c3_I_k;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 52);
    chartInstance->c3_Q_kMinusOne = c3_Q_k;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 53);
    c3_b[1] = c3_Q_k;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 56);
    for (c3_i9 = 0; c3_i9 < 6; c3_i9++) {
      c3_b_y[c3_i9] = (real_T)c3_b[c3_i9];
    }

    c3_eml_scalar_eg(chartInstance);
    c3_eml_scalar_eg(chartInstance);
    c3_c_y = 0.0;
    c3_eml_int_forloop_overflow_check(chartInstance);
    for (c3_e_k = 1; c3_e_k < 7; c3_e_k++) {
      c3_f_k = c3_e_k;
      c3_c_y += c3_b_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c3_f_k), 1, 6, 1, 0) - 1] *
        c3_c_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c3_f_k), 1, 6, 1, 0) - 1];
    }

    c3_d0 = muDoubleScalarRound(c3_c_y);
    if (c3_d0 < 256.0) {
      if (c3_d0 >= 0.0) {
        c3_u0 = (uint8_T)c3_d0;
      } else {
        c3_u0 = 0U;
      }
    } else if (c3_d0 >= 256.0) {
      c3_u0 = MAX_uint8_T;
    } else {
      c3_u0 = 0U;
    }

    c3_y[_SFD_EML_ARRAY_BOUNDS_CHECK("y", (int32_T)_SFD_INTEGER_CHECK("symIdx",
      c3_b_symIdx), 1, 272, 1, 0) - 1] = c3_u0;
    c3_symIdx++;
    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, -56);
  sf_debug_symbol_scope_pop();
  for (c3_i10 = 0; c3_i10 < 272; c3_i10++) {
    (*c3_d_y)[c3_i10] = c3_y[c3_i10];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
}

static void initSimStructsc3_commdvbc(SFc3_commdvbcInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber)
{
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  boolean_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc3_commdvbcInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(boolean_T *)c3_inData;
  c3_y = NULL;
  if (!chartInstance->c3_Q_kMinusOne_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 11, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static boolean_T c3_emlrt_marshallIn(SFc3_commdvbcInstanceStruct *chartInstance,
  const mxArray *c3_b_Q_kMinusOne, const char_T *c3_identifier)
{
  boolean_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_Q_kMinusOne),
    &c3_thisId);
  sf_mex_destroy(&c3_b_Q_kMinusOne);
  return c3_y;
}

static boolean_T c3_b_emlrt_marshallIn(SFc3_commdvbcInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  boolean_T c3_y;
  boolean_T c3_b8;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_Q_kMinusOne_not_empty = FALSE;
  } else {
    chartInstance->c3_Q_kMinusOne_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_b8, 1, 11, 0U, 0, 0U, 0);
    c3_y = c3_b8;
  }

  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_Q_kMinusOne;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  boolean_T c3_y;
  SFc3_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc3_commdvbcInstanceStruct *)chartInstanceVoid;
  c3_b_Q_kMinusOne = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_Q_kMinusOne),
    &c3_thisId);
  sf_mex_destroy(&c3_b_Q_kMinusOne);
  *(boolean_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  boolean_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc3_commdvbcInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(boolean_T *)c3_inData;
  c3_y = NULL;
  if (!chartInstance->c3_I_kMinusOne_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 11, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static boolean_T c3_c_emlrt_marshallIn(SFc3_commdvbcInstanceStruct
  *chartInstance, const mxArray *c3_b_I_kMinusOne, const char_T *c3_identifier)
{
  boolean_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_I_kMinusOne),
    &c3_thisId);
  sf_mex_destroy(&c3_b_I_kMinusOne);
  return c3_y;
}

static boolean_T c3_d_emlrt_marshallIn(SFc3_commdvbcInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  boolean_T c3_y;
  boolean_T c3_b9;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_I_kMinusOne_not_empty = FALSE;
  } else {
    chartInstance->c3_I_kMinusOne_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_b9, 1, 11, 0U, 0, 0U, 0);
    c3_y = c3_b9;
  }

  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_I_kMinusOne;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  boolean_T c3_y;
  SFc3_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc3_commdvbcInstanceStruct *)chartInstanceVoid;
  c3_b_I_kMinusOne = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_I_kMinusOne),
    &c3_thisId);
  sf_mex_destroy(&c3_b_I_kMinusOne);
  *(boolean_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i11;
  uint8_T c3_b_inData[272];
  int32_T c3_i12;
  uint8_T c3_u[272];
  const mxArray *c3_y = NULL;
  SFc3_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc3_commdvbcInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i11 = 0; c3_i11 < 272; c3_i11++) {
    c3_b_inData[c3_i11] = (*(uint8_T (*)[272])c3_inData)[c3_i11];
  }

  for (c3_i12 = 0; c3_i12 < 272; c3_i12++) {
    c3_u[c3_i12] = c3_b_inData[c3_i12];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 3, 0U, 1U, 0U, 1, 272), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_e_emlrt_marshallIn(SFc3_commdvbcInstanceStruct *chartInstance,
  const mxArray *c3_y, const char_T *c3_identifier, uint8_T c3_b_y[272])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_y), &c3_thisId, c3_b_y);
  sf_mex_destroy(&c3_y);
}

static void c3_f_emlrt_marshallIn(SFc3_commdvbcInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_y[272])
{
  uint8_T c3_uv2[272];
  int32_T c3_i13;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_uv2, 1, 3, 0U, 1, 0U, 1, 272);
  for (c3_i13 = 0; c3_i13 < 272; c3_i13++) {
    c3_y[c3_i13] = c3_uv2[c3_i13];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_y;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  uint8_T c3_b_y[272];
  int32_T c3_i14;
  SFc3_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc3_commdvbcInstanceStruct *)chartInstanceVoid;
  c3_y = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_y), &c3_thisId, c3_b_y);
  sf_mex_destroy(&c3_y);
  for (c3_i14 = 0; c3_i14 < 272; c3_i14++) {
    (*(uint8_T (*)[272])c3_outData)[c3_i14] = c3_b_y[c3_i14];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i15;
  uint8_T c3_b_inData[272];
  int32_T c3_i16;
  uint8_T c3_u[272];
  const mxArray *c3_y = NULL;
  SFc3_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc3_commdvbcInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i15 = 0; c3_i15 < 272; c3_i15++) {
    c3_b_inData[c3_i15] = (*(uint8_T (*)[272])c3_inData)[c3_i15];
  }

  for (c3_i16 = 0; c3_i16 < 272; c3_i16++) {
    c3_u[c3_i16] = c3_b_inData[c3_i16];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 3, 0U, 1U, 0U, 2, 272, 1), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc3_commdvbcInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static real_T c3_g_emlrt_marshallIn(SFc3_commdvbcInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d1;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d1, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d1;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_nargout;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc3_commdvbcInstanceStruct *)chartInstanceVoid;
  c3_nargout = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_nargout), &c3_thisId);
  sf_mex_destroy(&c3_nargout);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  boolean_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc3_commdvbcInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(boolean_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 11, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static boolean_T c3_h_emlrt_marshallIn(SFc3_commdvbcInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  boolean_T c3_y;
  boolean_T c3_b10;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_b10, 1, 11, 0U, 0, 0U, 0);
  c3_y = c3_b10;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_Q_k;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  boolean_T c3_y;
  SFc3_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc3_commdvbcInstanceStruct *)chartInstanceVoid;
  c3_Q_k = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_Q_k), &c3_thisId);
  sf_mex_destroy(&c3_Q_k);
  *(boolean_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i17;
  boolean_T c3_b_inData[6];
  int32_T c3_i18;
  boolean_T c3_u[6];
  const mxArray *c3_y = NULL;
  SFc3_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc3_commdvbcInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i17 = 0; c3_i17 < 6; c3_i17++) {
    c3_b_inData[c3_i17] = (*(boolean_T (*)[6])c3_inData)[c3_i17];
  }

  for (c3_i18 = 0; c3_i18 < 6; c3_i18++) {
    c3_u[c3_i18] = c3_b_inData[c3_i18];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 11, 0U, 1U, 0U, 2, 1, 6), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_i_emlrt_marshallIn(SFc3_commdvbcInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, boolean_T c3_y[6])
{
  boolean_T c3_bv0[6];
  int32_T c3_i19;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_bv0, 1, 11, 0U, 1, 0U, 2, 1, 6);
  for (c3_i19 = 0; c3_i19 < 6; c3_i19++) {
    c3_y[c3_i19] = c3_bv0[c3_i19];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  boolean_T c3_y[6];
  int32_T c3_i20;
  SFc3_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc3_commdvbcInstanceStruct *)chartInstanceVoid;
  c3_b = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b);
  for (c3_i20 = 0; c3_i20 < 6; c3_i20++) {
    (*(boolean_T (*)[6])c3_outData)[c3_i20] = c3_y[c3_i20];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_h_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i21;
  uint8_T c3_b_inData[6];
  int32_T c3_i22;
  uint8_T c3_u[6];
  const mxArray *c3_y = NULL;
  SFc3_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc3_commdvbcInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i21 = 0; c3_i21 < 6; c3_i21++) {
    c3_b_inData[c3_i21] = (*(uint8_T (*)[6])c3_inData)[c3_i21];
  }

  for (c3_i22 = 0; c3_i22 < 6; c3_i22++) {
    c3_u[c3_i22] = c3_b_inData[c3_i22];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 3, 0U, 1U, 0U, 1, 6), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

const mxArray *sf_c3_commdvbc_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  sf_mex_assign(&c3_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), FALSE);
  return c3_nameCaptureInfo;
}

static void c3_realmax(SFc3_commdvbcInstanceStruct *chartInstance)
{
}

static void c3_eml_scalar_eg(SFc3_commdvbcInstanceStruct *chartInstance)
{
}

static void c3_eml_int_forloop_overflow_check(SFc3_commdvbcInstanceStruct
  *chartInstance)
{
}

static const mxArray *c3_i_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc3_commdvbcInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(int32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static int32_T c3_j_emlrt_marshallIn(SFc3_commdvbcInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_y;
  int32_T c3_i23;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_i23, 1, 6, 0U, 0, 0U, 0);
  c3_y = c3_i23;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sfEvent;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_y;
  SFc3_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc3_commdvbcInstanceStruct *)chartInstanceVoid;
  c3_b_sfEvent = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sfEvent),
    &c3_thisId);
  sf_mex_destroy(&c3_b_sfEvent);
  *(int32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static uint8_T c3_k_emlrt_marshallIn(SFc3_commdvbcInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_commdvbc, const char_T *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_l_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_b_is_active_c3_commdvbc), &c3_thisId);
  sf_mex_destroy(&c3_b_is_active_c3_commdvbc);
  return c3_y;
}

static uint8_T c3_l_emlrt_marshallIn(SFc3_commdvbcInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u1;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u1, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u1;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void init_dsm_address_info(SFc3_commdvbcInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c3_commdvbc_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(405516412U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1400909538U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3558427932U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(169513413U);
}

mxArray *sf_c3_commdvbc_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("Jmu6MHmRrzrkeXPC1X7CCG");
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
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

static const mxArray *sf_get_sim_state_info_c3_commdvbc(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[4],M[0],T\"I_kMinusOne\",S'l','i','p'{{M1x2[79 90],M[0],}}},{M[4],M[0],T\"Q_kMinusOne\",S'l','i','p'{{M1x2[171 182],M[0],}}},{M[8],M[0],T\"is_active_c3_commdvbc\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_commdvbc_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_commdvbcInstanceStruct *chartInstance;
    chartInstance = (SFc3_commdvbcInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart(_commdvbcMachineNumber_,
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
          init_script_number_translation(_commdvbcMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting(_commdvbcMachineNumber_,
            chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_commdvbcMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"u");
          _SFD_SET_DATA_PROPS(1,2,0,1,"y");
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
        _SFD_CV_INIT_EML(0,1,1,2,0,0,1,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1681);
        _SFD_CV_INIT_EML_IF(0,1,0,91,114,-1,158);
        _SFD_CV_INIT_EML_IF(0,1,1,183,206,-1,250);
        _SFD_CV_INIT_EML_FOR(0,1,0,618,643,1680);
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
          dimVector[0]= 272;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 272;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)
            c3_c_sf_marshallIn);
        }

        {
          uint8_T (*c3_u)[272];
          uint8_T (*c3_y)[272];
          c3_y = (uint8_T (*)[272])ssGetOutputPortSignal(chartInstance->S, 1);
          c3_u = (uint8_T (*)[272])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c3_u);
          _SFD_SET_DATA_VALUE_PTR(1U, *c3_y);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_commdvbcMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization()
{
  return "z7TX1CHDahySpmv8cvNZeB";
}

static void sf_opaque_initialize_c3_commdvbc(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_commdvbcInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c3_commdvbc((SFc3_commdvbcInstanceStruct*) chartInstanceVar);
  initialize_c3_commdvbc((SFc3_commdvbcInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c3_commdvbc(void *chartInstanceVar)
{
  enable_c3_commdvbc((SFc3_commdvbcInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_commdvbc(void *chartInstanceVar)
{
  disable_c3_commdvbc((SFc3_commdvbcInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_commdvbc(void *chartInstanceVar)
{
  sf_c3_commdvbc((SFc3_commdvbcInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c3_commdvbc(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_commdvbc((SFc3_commdvbcInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_commdvbc();/* state var info */
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

extern void sf_internal_set_sim_state_c3_commdvbc(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_commdvbc();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_commdvbc((SFc3_commdvbcInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c3_commdvbc(SimStruct* S)
{
  return sf_internal_get_sim_state_c3_commdvbc(S);
}

static void sf_opaque_set_sim_state_c3_commdvbc(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c3_commdvbc(S, st);
}

static void sf_opaque_terminate_c3_commdvbc(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_commdvbcInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c3_commdvbc((SFc3_commdvbcInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_commdvbc_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_commdvbc((SFc3_commdvbcInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_commdvbc(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_commdvbc((SFc3_commdvbcInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_commdvbc(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_commdvbc_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,3,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,3,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,3,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,3,1);
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1725899797U));
  ssSetChecksum1(S,(3314386031U));
  ssSetChecksum2(S,(2560400898U));
  ssSetChecksum3(S,(2875073629U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c3_commdvbc(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_commdvbc(SimStruct *S)
{
  SFc3_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc3_commdvbcInstanceStruct *)malloc(sizeof
    (SFc3_commdvbcInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_commdvbcInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_commdvbc;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c3_commdvbc;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_commdvbc;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_commdvbc;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_commdvbc;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c3_commdvbc;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c3_commdvbc;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c3_commdvbc;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_commdvbc;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_commdvbc;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_commdvbc;
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

void c3_commdvbc_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_commdvbc(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_commdvbc(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_commdvbc(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_commdvbc_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
