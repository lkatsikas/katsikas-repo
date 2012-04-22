/* Include files */

#include "blascompat32.h"
#include "vipcodec_sfun.h"
#include "c1_vipcodec.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "vipcodec_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[15] = { "bitpos", "Temp", "run",
  "outpos", "pval", "cval", "numcoefs", "out1", "i", "flag", "nargin", "nargout",
  "in", "out", "prev_out" };

static const char * c1_b_debug_family_names[17] = { "valIn", "bitsIn",
  "bitsleft", "bval", "nargin", "nargout", "bitpos", "out", "Temp", "outpos",
  "val", "bits", "flag", "bitposO", "outO", "TempO", "outposO" };

static const char * c1_c_debug_family_names[17] = { "valIn", "bitsIn",
  "bitsleft", "bval", "nargin", "nargout", "bitpos", "out", "Temp", "outpos",
  "val", "bits", "flag", "bitposO", "outO", "TempO", "outposO" };

static const char * c1_d_debug_family_names[17] = { "valIn", "bitsIn",
  "bitsleft", "bval", "nargin", "nargout", "bitpos", "out", "Temp", "outpos",
  "val", "bits", "flag", "bitposO", "outO", "TempO", "outposO" };

static const char * c1_e_debug_family_names[11] = { "flag", "out", "nargin",
  "nargout", "bitpos", "Temp", "outpos", "bitposO", "outO", "TempO", "outposO" };

/* Function Declarations */
static void initialize_c1_vipcodec(SFc1_vipcodecInstanceStruct *chartInstance);
static void initialize_params_c1_vipcodec(SFc1_vipcodecInstanceStruct
  *chartInstance);
static void enable_c1_vipcodec(SFc1_vipcodecInstanceStruct *chartInstance);
static void disable_c1_vipcodec(SFc1_vipcodecInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_vipcodec(SFc1_vipcodecInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_vipcodec(SFc1_vipcodecInstanceStruct
  *chartInstance);
static void set_sim_state_c1_vipcodec(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_st);
static void finalize_c1_vipcodec(SFc1_vipcodecInstanceStruct *chartInstance);
static void sf_c1_vipcodec(SFc1_vipcodecInstanceStruct *chartInstance);
static void c1_chartstep_c1_vipcodec(SFc1_vipcodecInstanceStruct *chartInstance);
static void initSimStructsc1_vipcodec(SFc1_vipcodecInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static void c1_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_b_prev_out, const char_T *c1_identifier, uint32_T c1_y[15]);
static void c1_b_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint32_T c1_y[15]);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_c_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_out, const char_T *c1_identifier, uint32_T c1_y[15]);
static void c1_d_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint32_T c1_y[15]);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_e_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_f_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real32_T c1_g_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static uint32_T c1_h_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[16]);
static void c1_putbits(SFc1_vipcodecInstanceStruct *chartInstance, int32_T
  c1_bitpos, uint32_T c1_out[15], uint32_T c1_Temp, real_T c1_outpos, uint32_T
  c1_val, real_T c1_bits, real_T *c1_flag, int32_T *c1_bitposO, uint32_T
  c1_outO[15], uint32_T *c1_TempO, real_T *c1_outposO);
static void c1_eml_error(SFc1_vipcodecInstanceStruct *chartInstance);
static void c1_b_putbits(SFc1_vipcodecInstanceStruct *chartInstance, int32_T
  c1_bitpos, uint32_T c1_out[15], uint32_T c1_Temp, real_T c1_outpos, real32_T
  c1_val, real_T c1_bits, real_T *c1_flag, int32_T *c1_bitposO, uint32_T
  c1_outO[15], uint32_T *c1_TempO, real_T *c1_outposO);
static void c1_c_putbits(SFc1_vipcodecInstanceStruct *chartInstance, int32_T
  c1_bitpos, uint32_T c1_out[15], uint32_T c1_Temp, real_T c1_outpos, real_T
  c1_val, real_T c1_bits, real_T *c1_flag, int32_T *c1_bitposO, uint32_T
  c1_outO[15], uint32_T *c1_TempO, real_T *c1_outposO);
static uint8_T c1_i_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_vipcodec, const char_T *c1_identifier);
static uint8_T c1_j_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_vipcodecInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_vipcodec(SFc1_vipcodecInstanceStruct *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_prev_out_not_empty = FALSE;
  chartInstance->c1_is_active_c1_vipcodec = 0U;
}

static void initialize_params_c1_vipcodec(SFc1_vipcodecInstanceStruct
  *chartInstance)
{
}

static void enable_c1_vipcodec(SFc1_vipcodecInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_vipcodec(SFc1_vipcodecInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_vipcodec(SFc1_vipcodecInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c1_vipcodec(SFc1_vipcodecInstanceStruct
  *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  int32_T c1_i0;
  uint32_T c1_u[15];
  const mxArray *c1_b_y = NULL;
  int32_T c1_i1;
  uint32_T c1_b_u[15];
  const mxArray *c1_c_y = NULL;
  uint8_T c1_hoistedGlobal;
  uint8_T c1_c_u;
  const mxArray *c1_d_y = NULL;
  uint32_T (*c1_out)[15];
  c1_out = (uint32_T (*)[15])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(3));
  for (c1_i0 = 0; c1_i0 < 15; c1_i0++) {
    c1_u[c1_i0] = (*c1_out)[c1_i0];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u, 7, 0U, 1U, 0U, 1, 15));
  sf_mex_setcell(c1_y, 0, c1_b_y);
  for (c1_i1 = 0; c1_i1 < 15; c1_i1++) {
    c1_b_u[c1_i1] = chartInstance->c1_prev_out[c1_i1];
  }

  c1_c_y = NULL;
  if (!chartInstance->c1_prev_out_not_empty) {
    sf_mex_assign(&c1_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_b_u, 7, 0U, 1U, 0U, 1, 15));
  }

  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_hoistedGlobal = chartInstance->c1_is_active_c1_vipcodec;
  c1_c_u = c1_hoistedGlobal;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c1_y, 2, c1_d_y);
  sf_mex_assign(&c1_st, c1_y);
  return c1_st;
}

static void set_sim_state_c1_vipcodec(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_st)
{
  const mxArray *c1_u;
  uint32_T c1_uv0[15];
  int32_T c1_i2;
  uint32_T c1_uv1[15];
  int32_T c1_i3;
  uint32_T (*c1_out)[15];
  c1_out = (uint32_T (*)[15])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)),
                        "out", c1_uv0);
  for (c1_i2 = 0; c1_i2 < 15; c1_i2++) {
    (*c1_out)[c1_i2] = c1_uv0[c1_i2];
  }

  c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 1)),
                      "prev_out", c1_uv1);
  for (c1_i3 = 0; c1_i3 < 15; c1_i3++) {
    chartInstance->c1_prev_out[c1_i3] = c1_uv1[c1_i3];
  }

  chartInstance->c1_is_active_c1_vipcodec = c1_i_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 2)), "is_active_c1_vipcodec");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_vipcodec(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_vipcodec(SFc1_vipcodecInstanceStruct *chartInstance)
{
}

static void sf_c1_vipcodec(SFc1_vipcodecInstanceStruct *chartInstance)
{
  int32_T c1_i4;
  int32_T c1_i5;
  uint32_T (*c1_out)[15];
  real32_T (*c1_in)[64];
  c1_out = (uint32_T (*)[15])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_in = (real32_T (*)[64])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i4 = 0; c1_i4 < 64; c1_i4++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c1_in)[c1_i4], 0U);
  }

  for (c1_i5 = 0; c1_i5 < 15; c1_i5++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c1_out)[c1_i5], 1U);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_vipcodec(chartInstance);
  sf_debug_check_for_state_inconsistency(_vipcodecMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c1_chartstep_c1_vipcodec(SFc1_vipcodecInstanceStruct *chartInstance)
{
  int32_T c1_i6;
  real32_T c1_in[64];
  uint32_T c1_debug_family_var_map[15];
  int32_T c1_bitpos;
  uint32_T c1_Temp;
  uint32_T c1_run;
  real_T c1_outpos;
  real32_T c1_pval;
  real32_T c1_cval;
  real_T c1_numcoefs;
  int32_T c1_out1;
  real_T c1_i;
  real_T c1_flag;
  real_T c1_nargin = 1.0;
  real_T c1_nargout = 1.0;
  uint32_T c1_out[15];
  int32_T c1_i7;
  int32_T c1_i8;
  real32_T c1_x;
  real32_T c1_b_x;
  real32_T c1_f0;
  real32_T c1_f1;
  real32_T c1_f2;
  int32_T c1_i9;
  int32_T c1_i10;
  int32_T c1_c_x;
  int32_T c1_d_x;
  int32_T c1_i11;
  int32_T c1_saturatedUnaryMinus;
  int32_T c1_y;
  uint32_T c1_q0;
  int32_T c1_i12;
  uint32_T c1_qY;
  uint64_T c1_u0;
  real32_T c1_e_x;
  real32_T c1_f_x;
  real32_T c1_g_x;
  real_T c1_b_i;
  real32_T c1_h_x;
  real32_T c1_i_x;
  uint64_T c1_u1;
  int32_T c1_i13;
  uint32_T c1_b_out[15];
  real_T c1_b_outpos;
  uint32_T c1_b_Temp;
  uint32_T c1_c_out[15];
  int32_T c1_b_bitpos;
  real_T c1_b_flag;
  int32_T c1_i14;
  int32_T c1_i15;
  int32_T c1_i16;
  uint32_T c1_d_out[15];
  real32_T c1_f3;
  real32_T c1_f4;
  real32_T c1_f5;
  uint32_T c1_u2;
  real_T c1_c_outpos;
  uint32_T c1_c_Temp;
  int32_T c1_c_bitpos;
  real_T c1_c_flag;
  int32_T c1_i17;
  int32_T c1_i18;
  int32_T c1_i19;
  uint32_T c1_e_out[15];
  real_T c1_d_outpos;
  uint32_T c1_d_Temp;
  int32_T c1_d_bitpos;
  real_T c1_d_flag;
  int32_T c1_i20;
  int32_T c1_i21;
  int32_T c1_i22;
  uint32_T c1_f_out[15];
  real_T c1_e_outpos;
  uint32_T c1_e_Temp;
  int32_T c1_e_bitpos;
  real_T c1_e_flag;
  int32_T c1_i23;
  int32_T c1_i24;
  int32_T c1_f_bitpos;
  int32_T c1_i25;
  uint32_T c1_g_out[15];
  uint32_T c1_f_Temp;
  real_T c1_f_outpos;
  uint32_T c1_b_debug_family_var_map[11];
  real_T c1_f_flag;
  uint32_T c1_h_out[15];
  real_T c1_b_nargin = 4.0;
  real_T c1_b_nargout = 4.0;
  int32_T c1_g_bitpos;
  uint32_T c1_i_out[15];
  uint32_T c1_g_Temp;
  real_T c1_g_outpos;
  int32_T c1_i26;
  int32_T c1_i27;
  uint32_T c1_j_out[15];
  real_T c1_outposO;
  uint32_T c1_TempO;
  int32_T c1_bitposO;
  real_T c1_g_flag;
  int32_T c1_i28;
  int32_T c1_i29;
  int32_T c1_i30;
  int32_T c1_i31;
  uint32_T (*c1_k_out)[15];
  real32_T (*c1_b_in)[64];
  int32_T exitg1;
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  c1_k_out = (uint32_T (*)[15])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_b_in = (real32_T (*)[64])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i6 = 0; c1_i6 < 64; c1_i6++) {
    c1_in[c1_i6] = (*c1_b_in)[c1_i6];
  }

  sf_debug_symbol_scope_push_eml(0U, 15U, 15U, c1_debug_family_names,
    c1_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c1_bitpos, 0U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_Temp, 1U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_run, 2U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_outpos, 3U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_pval, 4U, c1_f_sf_marshallOut,
    c1_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_cval, 5U, c1_f_sf_marshallOut,
    c1_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c1_numcoefs, 6U, c1_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c1_out1, 7U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_i, 8U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_flag, 9U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargin, 10U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargout, 11U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c1_in, 12U, c1_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c1_out, 13U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(chartInstance->c1_prev_out, 14U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 8);
  if (CV_EML_IF(0, 0, !chartInstance->c1_prev_out_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 9);
    for (c1_i7 = 0; c1_i7 < 15; c1_i7++) {
      chartInstance->c1_prev_out[c1_i7] = 0U;
    }

    chartInstance->c1_prev_out_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 11);
  for (c1_i8 = 0; c1_i8 < 15; c1_i8++) {
    c1_out[c1_i8] = chartInstance->c1_prev_out[c1_i8];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 13);
  c1_bitpos = 0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 14);
  c1_Temp = 0U;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 15);
  c1_run = 0U;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 16);
  c1_outpos = 2.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 17);
  c1_pval = 0.0F;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 18);
  c1_cval = 0.0F;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 20);
  c1_numcoefs = 64.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 22);
  c1_x = c1_in[0];
  c1_b_x = c1_x;
  if ((real_T)c1_b_x > 0.0) {
    c1_b_x = muSingleScalarFloor(c1_b_x);
  } else {
    c1_b_x = muSingleScalarCeil(c1_b_x);
  }

  c1_f0 = c1_b_x;
  c1_f1 = c1_f0;
  if ((c1_f1 < 8.388608E+6F) && (c1_f1 > -8.388608E+6F)) {
    c1_f1 = c1_f1 < 0.0F ? muSingleScalarCeil(c1_f1 - 0.5F) :
      muSingleScalarFloor(c1_f1 + 0.5F);
  }

  c1_f2 = c1_f1;
  if (c1_f2 < 2.14748365E+9F) {
    if (c1_f2 >= -2.14748365E+9F) {
      c1_i9 = (int32_T)c1_f2;
    } else {
      c1_i9 = MIN_int32_T;
    }
  } else if (c1_f2 >= 2.14748365E+9F) {
    c1_i9 = MAX_int32_T;
  } else {
    c1_i9 = 0;
  }

  c1_out1 = c1_i9;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 24);
  if (CV_EML_IF(0, 1, (real_T)c1_out1 >= -1.0)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 25);
    c1_i10 = c1_out1;
    if (c1_i10 <= 0) {
      c1_i10 = 0;
    }

    c1_out[0] = (uint32_T)c1_i10;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 27);
    c1_c_x = c1_out1;
    c1_d_x = c1_c_x;
    if ((real_T)c1_d_x < 0.0) {
      c1_i11 = c1_d_x;
      if (c1_i11 <= MIN_int32_T) {
        c1_saturatedUnaryMinus = MAX_int32_T;
      } else {
        c1_saturatedUnaryMinus = -c1_i11;
      }

      c1_y = c1_saturatedUnaryMinus;
    } else {
      c1_y = c1_d_x;
    }

    c1_q0 = MAX_uint32_T;
    c1_i12 = c1_y;
    if (c1_i12 <= 0) {
      c1_i12 = 0;
    }

    c1_qY = c1_q0 - (uint32_T)c1_i12;
    if (c1_qY > c1_q0) {
      c1_qY = 0U;
    }

    c1_u0 = (uint64_T)c1_qY + (uint64_T)2U;
    if (c1_u0 > 4294967295UL) {
      c1_u0 = 4294967295UL;
    }

    c1_out[0] = (uint32_T)c1_u0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 32);
  c1_e_x = c1_in[1] + 0.5F;
  c1_pval = c1_e_x;
  c1_f_x = c1_pval;
  c1_pval = c1_f_x;
  c1_g_x = c1_pval;
  c1_pval = c1_g_x;
  if ((real_T)c1_pval > 0.0) {
    c1_pval = muSingleScalarFloor(c1_pval);
  } else {
    c1_pval = muSingleScalarCeil(c1_pval);
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 33);
  if (CV_EML_IF(0, 2, (real_T)c1_pval > 127.0)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 33);
    c1_pval = 127.0F;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 34);
  if (CV_EML_IF(0, 3, (real_T)c1_pval < -128.0)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 34);
    c1_pval = -128.0F;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 36);
  c1_run = 0U;
  c1_i = 3.0;
  c1_b_i = 3.0;
  do {
    exitg1 = 0U;
    if (c1_b_i <= 64.0) {
      c1_i = c1_b_i;
      CV_EML_FOR(0, 0, 1);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 38);
      c1_h_x = c1_in[_SFD_EML_ARRAY_BOUNDS_CHECK("in", (int32_T)
        _SFD_INTEGER_CHECK("i", c1_i), 1, 64, 1, 0) - 1] + 0.5F;
      c1_cval = c1_h_x;
      c1_i_x = c1_cval;
      c1_cval = c1_i_x;
      c1_cval = muSingleScalarFloor(c1_cval);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 39);
      guard1 = FALSE;
      guard2 = FALSE;
      if (CV_EML_COND(0, 0, c1_pval == c1_cval)) {
        if (CV_EML_COND(0, 1, (real_T)c1_run < 14.0)) {
          CV_EML_MCDC(0, 0, TRUE);
          CV_EML_IF(0, 4, TRUE);
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 40);
          c1_u1 = (uint64_T)c1_run + (uint64_T)1U;
          if (c1_u1 > 4294967295UL) {
            c1_u1 = 4294967295UL;
          }

          c1_run = (uint32_T)c1_u1;
          guard1 = TRUE;
        } else {
          guard2 = TRUE;
        }
      } else {
        guard2 = TRUE;
      }

      if (guard2 == TRUE) {
        CV_EML_MCDC(0, 0, FALSE);
        CV_EML_IF(0, 4, FALSE);
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 42);
        for (c1_i13 = 0; c1_i13 < 15; c1_i13++) {
          c1_b_out[c1_i13] = c1_out[c1_i13];
        }

        c1_putbits(chartInstance, c1_bitpos, c1_b_out, c1_Temp, c1_outpos,
                   c1_run, 4.0, &c1_b_flag, &c1_b_bitpos, c1_c_out, &c1_b_Temp,
                   &c1_b_outpos);
        c1_flag = c1_b_flag;
        c1_bitpos = c1_b_bitpos;
        for (c1_i14 = 0; c1_i14 < 15; c1_i14++) {
          c1_out[c1_i14] = c1_c_out[c1_i14];
        }

        c1_Temp = c1_b_Temp;
        c1_outpos = c1_b_outpos;
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 43);
        if (CV_EML_IF(0, 5, CV_EML_MCDC(0, 1, !(CV_EML_COND(0, 2, c1_flag != 0.0)
               != 0.0)))) {
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 44);
          for (c1_i15 = 0; c1_i15 < 15; c1_i15++) {
            chartInstance->c1_prev_out[c1_i15] = c1_out[c1_i15];
          }

          exitg1 = 1U;
        } else {
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 48);
          if (CV_EML_IF(0, 6, (real_T)c1_pval > 127.0)) {
            _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 48);
            c1_pval = 127.0F;
          }

          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 49);
          if (CV_EML_IF(0, 7, (real_T)c1_pval < -128.0)) {
            _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 49);
            c1_pval = -128.0F;
          }

          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 50);
          c1_pval += 128.0F;
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 52);
          for (c1_i16 = 0; c1_i16 < 15; c1_i16++) {
            c1_d_out[c1_i16] = c1_out[c1_i16];
          }

          c1_f3 = c1_pval;
          c1_f4 = c1_f3;
          if ((c1_f4 < 8.388608E+6F) && (c1_f4 > -8.388608E+6F)) {
            c1_f4 = c1_f4 < 0.0F ? muSingleScalarCeil(c1_f4 - 0.5F) :
              muSingleScalarFloor(c1_f4 + 0.5F);
          }

          c1_f5 = c1_f4;
          if (c1_f5 < 4.2949673E+9F) {
            if (c1_f5 >= 0.0F) {
              c1_u2 = (uint32_T)c1_f5;
            } else {
              c1_u2 = 0U;
            }
          } else if (c1_f5 >= 4.2949673E+9F) {
            c1_u2 = MAX_uint32_T;
          } else {
            c1_u2 = 0U;
          }

          c1_putbits(chartInstance, c1_bitpos, c1_d_out, c1_Temp, c1_outpos,
                     c1_u2, 8.0, &c1_c_flag, &c1_c_bitpos, c1_c_out, &c1_c_Temp,
                     &c1_c_outpos);
          c1_flag = c1_c_flag;
          c1_bitpos = c1_c_bitpos;
          for (c1_i17 = 0; c1_i17 < 15; c1_i17++) {
            c1_out[c1_i17] = c1_c_out[c1_i17];
          }

          c1_Temp = c1_c_Temp;
          c1_outpos = c1_c_outpos;
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 53);
          if (CV_EML_IF(0, 8, CV_EML_MCDC(0, 2, !(CV_EML_COND(0, 3, c1_flag !=
                  0.0) != 0.0)))) {
            _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 54);
            for (c1_i18 = 0; c1_i18 < 15; c1_i18++) {
              chartInstance->c1_prev_out[c1_i18] = c1_out[c1_i18];
            }

            exitg1 = 1U;
          } else {
            _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 58);
            c1_run = 0U;
            guard1 = TRUE;
          }
        }
      }

      if (guard1 == TRUE) {
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 60);
        c1_pval = c1_cval;
        c1_b_i++;
        sf_mex_listen_for_ctrl_c(chartInstance->S);
      }
    } else {
      CV_EML_FOR(0, 0, 0);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 64);
      for (c1_i19 = 0; c1_i19 < 15; c1_i19++) {
        c1_e_out[c1_i19] = c1_out[c1_i19];
      }

      c1_putbits(chartInstance, c1_bitpos, c1_e_out, c1_Temp, c1_outpos, c1_run,
                 4.0, &c1_d_flag, &c1_d_bitpos, c1_c_out, &c1_d_Temp,
                 &c1_d_outpos);
      c1_flag = c1_d_flag;
      c1_bitpos = c1_d_bitpos;
      for (c1_i20 = 0; c1_i20 < 15; c1_i20++) {
        c1_out[c1_i20] = c1_c_out[c1_i20];
      }

      c1_Temp = c1_d_Temp;
      c1_outpos = c1_d_outpos;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 65);
      if (CV_EML_IF(0, 9, CV_EML_MCDC(0, 3, !(CV_EML_COND(0, 4, c1_flag != 0.0)
             != 0.0)))) {
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 66);
        for (c1_i21 = 0; c1_i21 < 15; c1_i21++) {
          chartInstance->c1_prev_out[c1_i21] = c1_out[c1_i21];
        }
      } else {
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 70);
        if (CV_EML_IF(0, 10, (real_T)c1_pval > 127.0)) {
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 70);
          c1_pval = 127.0F;
        }

        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 71);
        if (CV_EML_IF(0, 11, (real_T)c1_pval < -128.0)) {
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 71);
          c1_pval = -128.0F;
        }

        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 72);
        c1_pval += 128.0F;
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 74);
        for (c1_i22 = 0; c1_i22 < 15; c1_i22++) {
          c1_f_out[c1_i22] = c1_out[c1_i22];
        }

        c1_b_putbits(chartInstance, c1_bitpos, c1_f_out, c1_Temp, c1_outpos,
                     c1_pval, 8.0, &c1_e_flag, &c1_e_bitpos, c1_c_out,
                     &c1_e_Temp, &c1_e_outpos);
        c1_flag = c1_e_flag;
        c1_bitpos = c1_e_bitpos;
        for (c1_i23 = 0; c1_i23 < 15; c1_i23++) {
          c1_out[c1_i23] = c1_c_out[c1_i23];
        }

        c1_Temp = c1_e_Temp;
        c1_outpos = c1_e_outpos;
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 75);
        if (CV_EML_IF(0, 12, CV_EML_MCDC(0, 4, !(CV_EML_COND(0, 5, c1_flag !=
                0.0) != 0.0)))) {
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 76);
          for (c1_i24 = 0; c1_i24 < 15; c1_i24++) {
            chartInstance->c1_prev_out[c1_i24] = c1_out[c1_i24];
          }
        } else {
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 80);
          c1_f_bitpos = c1_bitpos;
          for (c1_i25 = 0; c1_i25 < 15; c1_i25++) {
            c1_g_out[c1_i25] = c1_out[c1_i25];
          }

          c1_f_Temp = c1_Temp;
          c1_f_outpos = c1_outpos;
          sf_debug_symbol_scope_push_eml(0U, 11U, 12U, c1_e_debug_family_names,
            c1_b_debug_family_var_map);
          sf_debug_symbol_scope_add_eml_importable(&c1_f_flag, 0U,
            c1_d_sf_marshallOut, c1_c_sf_marshallIn);
          sf_debug_symbol_scope_add_eml_importable(c1_h_out, MAX_uint32_T,
            c1_b_sf_marshallOut, c1_b_sf_marshallIn);
          sf_debug_symbol_scope_add_eml_importable(&c1_b_nargin, 2U,
            c1_d_sf_marshallOut, c1_c_sf_marshallIn);
          sf_debug_symbol_scope_add_eml_importable(&c1_b_nargout, 3U,
            c1_d_sf_marshallOut, c1_c_sf_marshallIn);
          sf_debug_symbol_scope_add_eml_importable(&c1_f_bitpos, 4U,
            c1_e_sf_marshallOut, c1_d_sf_marshallIn);
          sf_debug_symbol_scope_add_eml_importable(c1_g_out, 1U,
            c1_b_sf_marshallOut, c1_b_sf_marshallIn);
          sf_debug_symbol_scope_add_eml_importable(&c1_f_Temp, 5U,
            c1_g_sf_marshallOut, c1_f_sf_marshallIn);
          sf_debug_symbol_scope_add_eml_importable(&c1_f_outpos, 6U,
            c1_d_sf_marshallOut, c1_c_sf_marshallIn);
          sf_debug_symbol_scope_add_eml_importable(&c1_g_bitpos, 7U,
            c1_e_sf_marshallOut, c1_d_sf_marshallIn);
          sf_debug_symbol_scope_add_eml_importable(c1_i_out, 8U,
            c1_b_sf_marshallOut, c1_b_sf_marshallIn);
          sf_debug_symbol_scope_add_eml_importable(&c1_g_Temp, 9U,
            c1_g_sf_marshallOut, c1_f_sf_marshallIn);
          sf_debug_symbol_scope_add_eml_importable(&c1_g_outpos, 10U,
            c1_d_sf_marshallOut, c1_c_sf_marshallIn);
          for (c1_i26 = 0; c1_i26 < 15; c1_i26++) {
            c1_h_out[c1_i26] = c1_g_out[c1_i26];
          }

          sf_debug_symbol_switch(1U, 1U);
          CV_EML_FCN(0, 2);
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 120);
          for (c1_i27 = 0; c1_i27 < 15; c1_i27++) {
            c1_j_out[c1_i27] = c1_h_out[c1_i27];
          }

          c1_c_putbits(chartInstance, c1_f_bitpos, c1_j_out, c1_f_Temp,
                       c1_f_outpos, 15.0, 4.0, &c1_g_flag, &c1_bitposO, c1_c_out,
                       &c1_TempO, &c1_outposO);
          c1_f_flag = c1_g_flag;
          c1_g_bitpos = c1_bitposO;
          for (c1_i28 = 0; c1_i28 < 15; c1_i28++) {
            c1_i_out[c1_i28] = c1_c_out[c1_i28];
          }

          c1_g_Temp = c1_TempO;
          c1_g_outpos = c1_outposO;
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 121);
          if (CV_EML_IF(0, 15, CV_EML_MCDC(0, 5, !(CV_EML_COND(0, 6, c1_f_flag
                  != 0.0) != 0.0)))) {
          } else {
            _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 124);
            if (CV_EML_IF(0, 16, c1_g_outpos > 16.0)) {
            } else {
              _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 125);
              c1_i_out[_SFD_EML_ARRAY_BOUNDS_CHECK("outO", (int32_T)
                _SFD_INTEGER_CHECK("outposO", c1_g_outpos), 1, 15, 1, 0) - 1] =
                c1_g_Temp;
            }
          }

          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -125);
          sf_debug_symbol_scope_pop();
          c1_bitpos = c1_g_bitpos;
          for (c1_i29 = 0; c1_i29 < 15; c1_i29++) {
            c1_out[c1_i29] = c1_i_out[c1_i29];
          }

          c1_Temp = c1_g_Temp;
          c1_outpos = c1_g_outpos;
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 81);
          for (c1_i30 = 0; c1_i30 < 15; c1_i30++) {
            chartInstance->c1_prev_out[c1_i30] = c1_out[c1_i30];
          }
        }
      }

      exitg1 = 1U;
    }
  } while (exitg1 == 0U);

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -81);
  sf_debug_symbol_scope_pop();
  for (c1_i31 = 0; c1_i31 < 15; c1_i31++) {
    (*c1_k_out)[c1_i31] = c1_out[c1_i31];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_vipcodec(SFc1_vipcodecInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i32;
  uint32_T c1_b_inData[15];
  int32_T c1_i33;
  uint32_T c1_u[15];
  const mxArray *c1_y = NULL;
  SFc1_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc1_vipcodecInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i32 = 0; c1_i32 < 15; c1_i32++) {
    c1_b_inData[c1_i32] = (*(uint32_T (*)[15])c1_inData)[c1_i32];
  }

  for (c1_i33 = 0; c1_i33 < 15; c1_i33++) {
    c1_u[c1_i33] = c1_b_inData[c1_i33];
  }

  c1_y = NULL;
  if (!chartInstance->c1_prev_out_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 7, 0U, 1U, 0U, 1, 15));
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static void c1_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_b_prev_out, const char_T *c1_identifier, uint32_T c1_y[15])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_prev_out), &c1_thisId,
                        c1_y);
  sf_mex_destroy(&c1_b_prev_out);
}

static void c1_b_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint32_T c1_y[15])
{
  uint32_T c1_uv2[15];
  int32_T c1_i34;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_prev_out_not_empty = FALSE;
  } else {
    chartInstance->c1_prev_out_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_uv2, 1, 7, 0U, 1, 0U, 1, 15);
    for (c1_i34 = 0; c1_i34 < 15; c1_i34++) {
      c1_y[c1_i34] = c1_uv2[c1_i34];
    }
  }

  sf_mex_destroy(&c1_u);
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_prev_out;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  uint32_T c1_y[15];
  int32_T c1_i35;
  SFc1_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc1_vipcodecInstanceStruct *)chartInstanceVoid;
  c1_b_prev_out = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_prev_out), &c1_thisId,
                        c1_y);
  sf_mex_destroy(&c1_b_prev_out);
  for (c1_i35 = 0; c1_i35 < 15; c1_i35++) {
    (*(uint32_T (*)[15])c1_outData)[c1_i35] = c1_y[c1_i35];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i36;
  uint32_T c1_b_inData[15];
  int32_T c1_i37;
  uint32_T c1_u[15];
  const mxArray *c1_y = NULL;
  SFc1_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc1_vipcodecInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i36 = 0; c1_i36 < 15; c1_i36++) {
    c1_b_inData[c1_i36] = (*(uint32_T (*)[15])c1_inData)[c1_i36];
  }

  for (c1_i37 = 0; c1_i37 < 15; c1_i37++) {
    c1_u[c1_i37] = c1_b_inData[c1_i37];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 7, 0U, 1U, 0U, 1, 15));
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static void c1_c_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_out, const char_T *c1_identifier, uint32_T c1_y[15])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_out), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_out);
}

static void c1_d_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint32_T c1_y[15])
{
  uint32_T c1_uv3[15];
  int32_T c1_i38;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_uv3, 1, 7, 0U, 1, 0U, 1, 15);
  for (c1_i38 = 0; c1_i38 < 15; c1_i38++) {
    c1_y[c1_i38] = c1_uv3[c1_i38];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_out;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  uint32_T c1_y[15];
  int32_T c1_i39;
  SFc1_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc1_vipcodecInstanceStruct *)chartInstanceVoid;
  c1_out = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_out), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_out);
  for (c1_i39 = 0; c1_i39 < 15; c1_i39++) {
    (*(uint32_T (*)[15])c1_outData)[c1_i39] = c1_y[c1_i39];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i40;
  real32_T c1_b_inData[64];
  int32_T c1_i41;
  real32_T c1_u[64];
  const mxArray *c1_y = NULL;
  SFc1_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc1_vipcodecInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i40 = 0; c1_i40 < 64; c1_i40++) {
    c1_b_inData[c1_i40] = (*(real32_T (*)[64])c1_inData)[c1_i40];
  }

  for (c1_i41 = 0; c1_i41 < 64; c1_i41++) {
    c1_u[c1_i41] = c1_b_inData[c1_i41];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 1, 0U, 1U, 0U, 2, 64, 1));
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc1_vipcodecInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static real_T c1_e_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_nargout;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc1_vipcodecInstanceStruct *)chartInstanceVoid;
  c1_nargout = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nargout), &c1_thisId);
  sf_mex_destroy(&c1_nargout);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc1_vipcodecInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0));
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static int32_T c1_f_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i42;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i42, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i42;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_out1;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc1_vipcodecInstanceStruct *)chartInstanceVoid;
  c1_out1 = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_out1), &c1_thisId);
  sf_mex_destroy(&c1_out1);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc1_vipcodecInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 1, 0U, 0U, 0U, 0));
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static real32_T c1_g_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real32_T c1_y;
  real32_T c1_f6;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_f6, 1, 1, 0U, 0, 0U, 0);
  c1_y = c1_f6;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_cval;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real32_T c1_y;
  SFc1_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc1_vipcodecInstanceStruct *)chartInstanceVoid;
  c1_cval = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_cval), &c1_thisId);
  sf_mex_destroy(&c1_cval);
  *(real32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  uint32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc1_vipcodecInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(uint32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 7, 0U, 0U, 0U, 0));
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static uint32_T c1_h_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint32_T c1_y;
  uint32_T c1_u3;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u3, 1, 7, 0U, 0, 0U, 0);
  c1_y = c1_u3;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_run;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  uint32_T c1_y;
  SFc1_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc1_vipcodecInstanceStruct *)chartInstanceVoid;
  c1_run = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_run), &c1_thisId);
  sf_mex_destroy(&c1_run);
  *(uint32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_vipcodec_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo;
  c1_ResolvedFunctionInfo c1_info[16];
  const mxArray *c1_m0 = NULL;
  int32_T c1_i43;
  c1_ResolvedFunctionInfo *c1_r0;
  c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  c1_info_helper(c1_info);
  sf_mex_assign(&c1_m0, sf_mex_createstruct("nameCaptureInfo", 1, 16));
  for (c1_i43 = 0; c1_i43 < 16; c1_i43++) {
    c1_r0 = &c1_info[c1_i43];
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->context)), "context", "nameCaptureInfo",
                    c1_i43);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c1_r0->name)), "name", "nameCaptureInfo", c1_i43);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c1_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c1_i43);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->resolved)), "resolved", "nameCaptureInfo",
                    c1_i43);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c1_i43);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c1_i43);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c1_i43);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c1_i43);
  }

  sf_mex_assign(&c1_nameCaptureInfo, c1_m0);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[16])
{
  c1_info[0].context = "";
  c1_info[0].name = "fix";
  c1_info[0].dominantType = "single";
  c1_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/fix.m";
  c1_info[0].fileTimeLo = 1286815142U;
  c1_info[0].fileTimeHi = 0U;
  c1_info[0].mFileTimeLo = 0U;
  c1_info[0].mFileTimeHi = 0U;
  c1_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/fix.m";
  c1_info[1].name = "eml_scalar_fix";
  c1_info[1].dominantType = "single";
  c1_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_fix.m";
  c1_info[1].fileTimeLo = 1286815126U;
  c1_info[1].fileTimeHi = 0U;
  c1_info[1].mFileTimeLo = 0U;
  c1_info[1].mFileTimeHi = 0U;
  c1_info[2].context = "";
  c1_info[2].name = "intmax";
  c1_info[2].dominantType = "char";
  c1_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c1_info[2].fileTimeLo = 1286815156U;
  c1_info[2].fileTimeHi = 0U;
  c1_info[2].mFileTimeLo = 0U;
  c1_info[2].mFileTimeHi = 0U;
  c1_info[3].context = "";
  c1_info[3].name = "abs";
  c1_info[3].dominantType = "int32";
  c1_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[3].fileTimeLo = 1286815094U;
  c1_info[3].fileTimeHi = 0U;
  c1_info[3].mFileTimeLo = 0U;
  c1_info[3].mFileTimeHi = 0U;
  c1_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[4].name = "eml_scalar_abs";
  c1_info[4].dominantType = "int32";
  c1_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c1_info[4].fileTimeLo = 1286815112U;
  c1_info[4].fileTimeHi = 0U;
  c1_info[4].mFileTimeLo = 0U;
  c1_info[4].mFileTimeHi = 0U;
  c1_info[5].context = "";
  c1_info[5].name = "floor";
  c1_info[5].dominantType = "single";
  c1_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[5].fileTimeLo = 1286815142U;
  c1_info[5].fileTimeHi = 0U;
  c1_info[5].mFileTimeLo = 0U;
  c1_info[5].mFileTimeHi = 0U;
  c1_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[6].name = "eml_scalar_floor";
  c1_info[6].dominantType = "single";
  c1_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c1_info[6].fileTimeLo = 1286815126U;
  c1_info[6].fileTimeHi = 0U;
  c1_info[6].mFileTimeLo = 0U;
  c1_info[6].mFileTimeHi = 0U;
  c1_info[7].context = "";
  c1_info[7].name = "bitshift";
  c1_info[7].dominantType = "uint32";
  c1_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c1_info[7].fileTimeLo = 1286815238U;
  c1_info[7].fileTimeHi = 0U;
  c1_info[7].mFileTimeLo = 0U;
  c1_info[7].mFileTimeHi = 0U;
  c1_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c1_info[8].name = "eml_isa_uint";
  c1_info[8].dominantType = "uint32";
  c1_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  c1_info[8].fileTimeLo = 1286815184U;
  c1_info[8].fileTimeHi = 0U;
  c1_info[8].mFileTimeLo = 0U;
  c1_info[8].mFileTimeHi = 0U;
  c1_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c1_info[9].name = "eml_int_nbits";
  c1_info[9].dominantType = "char";
  c1_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_nbits.m";
  c1_info[9].fileTimeLo = 1286815180U;
  c1_info[9].fileTimeHi = 0U;
  c1_info[9].mFileTimeLo = 0U;
  c1_info[9].mFileTimeHi = 0U;
  c1_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c1_info[10].name = "eml_scalar_eg";
  c1_info[10].dominantType = "uint32";
  c1_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[10].fileTimeLo = 1286815196U;
  c1_info[10].fileTimeHi = 0U;
  c1_info[10].mFileTimeLo = 0U;
  c1_info[10].mFileTimeHi = 0U;
  c1_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c1_info[11].name = "eml_scalexp_alloc";
  c1_info[11].dominantType = "uint32";
  c1_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c1_info[11].fileTimeLo = 1286815196U;
  c1_info[11].fileTimeHi = 0U;
  c1_info[11].mFileTimeLo = 0U;
  c1_info[11].mFileTimeHi = 0U;
  c1_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c1_info[12].name = "eml_error";
  c1_info[12].dominantType = "char";
  c1_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c1_info[12].fileTimeLo = 1286815100U;
  c1_info[12].fileTimeHi = 0U;
  c1_info[12].mFileTimeLo = 0U;
  c1_info[12].mFileTimeHi = 0U;
  c1_info[13].context = "";
  c1_info[13].name = "bitor";
  c1_info[13].dominantType = "uint32";
  c1_info[13].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitor.m";
  c1_info[13].fileTimeLo = 1286815236U;
  c1_info[13].fileTimeHi = 0U;
  c1_info[13].mFileTimeLo = 0U;
  c1_info[13].mFileTimeHi = 0U;
  c1_info[14].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitor.m";
  c1_info[14].name = "eml_scalexp_compatible";
  c1_info[14].dominantType = "uint32";
  c1_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c1_info[14].fileTimeLo = 1286815196U;
  c1_info[14].fileTimeHi = 0U;
  c1_info[14].mFileTimeLo = 0U;
  c1_info[14].mFileTimeHi = 0U;
  c1_info[15].context = "";
  c1_info[15].name = "length";
  c1_info[15].dominantType = "uint32";
  c1_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c1_info[15].fileTimeLo = 1286815160U;
  c1_info[15].fileTimeHi = 0U;
  c1_info[15].mFileTimeLo = 0U;
  c1_info[15].mFileTimeHi = 0U;
}

static void c1_putbits(SFc1_vipcodecInstanceStruct *chartInstance, int32_T
  c1_bitpos, uint32_T c1_out[15], uint32_T c1_Temp, real_T c1_outpos, uint32_T
  c1_val, real_T c1_bits, real_T *c1_flag, int32_T *c1_bitposO, uint32_T
  c1_outO[15], uint32_T *c1_TempO, real_T *c1_outposO)
{
  uint32_T c1_debug_family_var_map[17];
  uint32_T c1_valIn;
  int32_T c1_bitsIn;
  int32_T c1_bitsleft;
  uint32_T c1_bval;
  real_T c1_nargin = 6.0;
  real_T c1_nargout = 5.0;
  real_T c1_d1;
  real_T c1_d2;
  real_T c1_d3;
  int32_T c1_i44;
  int32_T c1_i45;
  int64_T c1_i46;
  int64_T c1_i47;
  uint32_T c1_a;
  int64_T c1_i48;
  int32_T c1_i49;
  int32_T c1_saturatedUnaryMinus;
  int32_T c1_k;
  int32_T c1_x;
  int32_T c1_b_x;
  uint32_T c1_a1;
  int32_T c1_k1;
  int32_T c1_i50;
  int32_T c1_b_saturatedUnaryMinus;
  int32_T c1_i51;
  uint8_T c1_absk1;
  int32_T c1_i52;
  uint32_T c1_b_a;
  uint32_T c1_b;
  int64_T c1_i53;
  uint32_T c1_c_a;
  int64_T c1_i54;
  int32_T c1_b_k;
  int32_T c1_c_x;
  int32_T c1_d_x;
  uint32_T c1_b_a1;
  int32_T c1_b_k1;
  int32_T c1_i55;
  int32_T c1_c_saturatedUnaryMinus;
  int32_T c1_i56;
  uint8_T c1_b_absk1;
  int32_T c1_i57;
  uint32_T c1_d_a;
  int64_T c1_i58;
  int32_T c1_i59;
  int32_T c1_d_saturatedUnaryMinus;
  int32_T c1_c_k;
  int32_T c1_e_x;
  int32_T c1_f_x;
  uint32_T c1_c_a1;
  int32_T c1_c_k1;
  int32_T c1_i60;
  int32_T c1_e_saturatedUnaryMinus;
  int32_T c1_i61;
  uint8_T c1_c_absk1;
  int32_T c1_i62;
  uint32_T c1_e_a;
  int64_T c1_i63;
  int64_T c1_i64;
  int32_T c1_d_k;
  int32_T c1_g_x;
  int32_T c1_h_x;
  uint32_T c1_d_a1;
  int32_T c1_d_k1;
  int32_T c1_i65;
  int32_T c1_f_saturatedUnaryMinus;
  int32_T c1_i66;
  uint8_T c1_d_absk1;
  int32_T c1_i67;
  uint32_T c1_f_a;
  uint32_T c1_b_b;
  int64_T c1_i68;
  boolean_T guard1 = FALSE;
  sf_debug_symbol_scope_push_eml(0U, 17U, 17U, c1_b_debug_family_names,
    c1_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c1_valIn, 0U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_bitsIn, 1U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_bitsleft, 2U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_bval, 3U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargin, 4U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargout, 5U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_bitpos, 6U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_out, 7U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_Temp, 8U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_outpos, 9U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_val, 10U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_bits, 11U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_flag, 12U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_bitposO, 13U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_outO, 14U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_TempO, 15U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_outposO, 16U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  CV_EML_FCN(0, 1);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 87);
  c1_valIn = c1_val;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 88);
  c1_d1 = c1_bits;
  c1_d2 = c1_d1;
  c1_d2 = c1_d2 < 0.0 ? muDoubleScalarCeil(c1_d2 - 0.5) : muDoubleScalarFloor
    (c1_d2 + 0.5);
  c1_d3 = c1_d2;
  if (c1_d3 < 2.147483648E+9) {
    if (c1_d3 >= -2.147483648E+9) {
      c1_i44 = (int32_T)c1_d3;
    } else {
      c1_i44 = MIN_int32_T;
    }
  } else if (c1_d3 >= 2.147483648E+9) {
    c1_i44 = MAX_int32_T;
  } else {
    c1_i44 = 0;
  }

  c1_bitsIn = c1_i44;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 89);
  *c1_bitposO = c1_bitpos;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 90);
  for (c1_i45 = 0; c1_i45 < 15; c1_i45++) {
    c1_outO[c1_i45] = c1_out[c1_i45];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 91);
  *c1_TempO = c1_Temp;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 92);
  *c1_outposO = c1_outpos;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 94);
  c1_i46 = (int64_T)*c1_bitposO + (int64_T)c1_bitsIn;
  if (c1_i46 > 2147483647L) {
    c1_i46 = 2147483647L;
  } else {
    if (c1_i46 <= -2147483648L) {
      c1_i46 = -2147483648L;
    }
  }

  guard1 = FALSE;
  if (CV_EML_IF(0, 13, (real_T)(int32_T)c1_i46 > 32.0)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 95);
    c1_i47 = (int64_T)32 - (int64_T)*c1_bitposO;
    if (c1_i47 > 2147483647L) {
      c1_i47 = 2147483647L;
    } else {
      if (c1_i47 <= -2147483648L) {
        c1_i47 = -2147483648L;
      }
    }

    c1_bitsleft = (int32_T)c1_i47;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 96);
    c1_bval = 0U;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 97);
    c1_a = c1_valIn;
    c1_i48 = (int64_T)c1_bitsIn - (int64_T)c1_bitsleft;
    if (c1_i48 > 2147483647L) {
      c1_i48 = 2147483647L;
    } else {
      if (c1_i48 <= -2147483648L) {
        c1_i48 = -2147483648L;
      }
    }

    c1_i49 = (int32_T)c1_i48;
    if (c1_i49 <= MIN_int32_T) {
      c1_saturatedUnaryMinus = MAX_int32_T;
    } else {
      c1_saturatedUnaryMinus = -c1_i49;
    }

    c1_k = c1_saturatedUnaryMinus;
    c1_x = c1_k;
    c1_b_x = c1_x;
    if (c1_k != c1_b_x) {
      c1_eml_error(chartInstance);
    }

    c1_a1 = c1_a;
    c1_k1 = c1_k;
    c1_bval = 0U;
    if ((real_T)c1_k1 < 0.0) {
      c1_i50 = c1_k1;
      if (c1_i50 <= MIN_int32_T) {
        c1_b_saturatedUnaryMinus = MAX_int32_T;
      } else {
        c1_b_saturatedUnaryMinus = -c1_i50;
      }

      c1_i51 = c1_b_saturatedUnaryMinus;
      if (c1_i51 <= 0) {
        c1_i51 = 0;
      } else {
        if (c1_i51 > 255) {
          c1_i51 = 255;
        }
      }

      c1_absk1 = (uint8_T)c1_i51;
      if (c1_absk1 < 32) {
        c1_bval = c1_a1 >> (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_absk1), 0, 31, 1,
          1);
      }
    } else {
      c1_i52 = c1_k1;
      if (c1_i52 <= 0) {
        c1_i52 = 0;
      } else {
        if (c1_i52 > 255) {
          c1_i52 = 255;
        }
      }

      c1_absk1 = (uint8_T)c1_i52;
      if (c1_absk1 < 32) {
        c1_bval = c1_a1 << (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_absk1), 0, 31, 1,
          1);
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 98);
    c1_b_a = *c1_TempO;
    c1_b = c1_bval;
    *c1_TempO = c1_b_a | c1_b;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 99);
    c1_outO[_SFD_EML_ARRAY_BOUNDS_CHECK("outO", (int32_T)_SFD_INTEGER_CHECK(
      "outposO", *c1_outposO), 1, 15, 1, 0) - 1] = *c1_TempO;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 100);
    (*c1_outposO)++;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 101);
    if (CV_EML_IF(0, 14, *c1_outposO > 15.0)) {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 102);
      *c1_flag = 0.0;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 105);
      *c1_TempO = 0U;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 106);
      *c1_bitposO = 0;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 107);
      c1_i53 = (int64_T)c1_bitsIn - (int64_T)c1_bitsleft;
      if (c1_i53 > 2147483647L) {
        c1_i53 = 2147483647L;
      } else {
        if (c1_i53 <= -2147483648L) {
          c1_i53 = -2147483648L;
        }
      }

      c1_bitsIn = (int32_T)c1_i53;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 108);
      c1_c_a = c1_valIn;
      c1_i54 = (int64_T)32 - (int64_T)c1_bitsIn;
      if (c1_i54 > 2147483647L) {
        c1_i54 = 2147483647L;
      } else {
        if (c1_i54 <= -2147483648L) {
          c1_i54 = -2147483648L;
        }
      }

      c1_b_k = (int32_T)c1_i54;
      c1_c_x = c1_b_k;
      c1_d_x = c1_c_x;
      if (c1_b_k != c1_d_x) {
        c1_eml_error(chartInstance);
      }

      c1_b_a1 = c1_c_a;
      c1_b_k1 = c1_b_k;
      c1_valIn = 0U;
      if ((real_T)c1_b_k1 < 0.0) {
        c1_i55 = c1_b_k1;
        if (c1_i55 <= MIN_int32_T) {
          c1_c_saturatedUnaryMinus = MAX_int32_T;
        } else {
          c1_c_saturatedUnaryMinus = -c1_i55;
        }

        c1_i56 = c1_c_saturatedUnaryMinus;
        if (c1_i56 <= 0) {
          c1_i56 = 0;
        } else {
          if (c1_i56 > 255) {
            c1_i56 = 255;
          }
        }

        c1_b_absk1 = (uint8_T)c1_i56;
        if (c1_b_absk1 < 32) {
          c1_valIn = c1_b_a1 >> (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
            "", (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_b_absk1), 0,
            31, 1, 1);
        }
      } else {
        c1_i57 = c1_b_k1;
        if (c1_i57 <= 0) {
          c1_i57 = 0;
        } else {
          if (c1_i57 > 255) {
            c1_i57 = 255;
          }
        }

        c1_b_absk1 = (uint8_T)c1_i57;
        if (c1_b_absk1 < 32) {
          c1_valIn = c1_b_a1 << (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
            "", (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_b_absk1), 0,
            31, 1, 1);
        }
      }

      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 109);
      c1_d_a = c1_valIn;
      c1_i58 = (int64_T)32 - (int64_T)c1_bitsIn;
      if (c1_i58 > 2147483647L) {
        c1_i58 = 2147483647L;
      } else {
        if (c1_i58 <= -2147483648L) {
          c1_i58 = -2147483648L;
        }
      }

      c1_i59 = (int32_T)c1_i58;
      if (c1_i59 <= MIN_int32_T) {
        c1_d_saturatedUnaryMinus = MAX_int32_T;
      } else {
        c1_d_saturatedUnaryMinus = -c1_i59;
      }

      c1_c_k = c1_d_saturatedUnaryMinus;
      c1_e_x = c1_c_k;
      c1_f_x = c1_e_x;
      if (c1_c_k != c1_f_x) {
        c1_eml_error(chartInstance);
      }

      c1_c_a1 = c1_d_a;
      c1_c_k1 = c1_c_k;
      c1_valIn = 0U;
      if ((real_T)c1_c_k1 < 0.0) {
        c1_i60 = c1_c_k1;
        if (c1_i60 <= MIN_int32_T) {
          c1_e_saturatedUnaryMinus = MAX_int32_T;
        } else {
          c1_e_saturatedUnaryMinus = -c1_i60;
        }

        c1_i61 = c1_e_saturatedUnaryMinus;
        if (c1_i61 <= 0) {
          c1_i61 = 0;
        } else {
          if (c1_i61 > 255) {
            c1_i61 = 255;
          }
        }

        c1_c_absk1 = (uint8_T)c1_i61;
        if (c1_c_absk1 < 32) {
          c1_valIn = c1_c_a1 >> (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
            "", (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_c_absk1), 0,
            31, 1, 1);
        }
      } else {
        c1_i62 = c1_c_k1;
        if (c1_i62 <= 0) {
          c1_i62 = 0;
        } else {
          if (c1_i62 > 255) {
            c1_i62 = 255;
          }
        }

        c1_c_absk1 = (uint8_T)c1_i62;
        if (c1_c_absk1 < 32) {
          c1_valIn = c1_c_a1 << (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
            "", (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_c_absk1), 0,
            31, 1, 1);
        }
      }

      guard1 = TRUE;
    }
  } else {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 111);
    c1_e_a = c1_valIn;
    c1_i63 = (int64_T)c1_bitsIn + (int64_T)*c1_bitposO;
    if (c1_i63 > 2147483647L) {
      c1_i63 = 2147483647L;
    } else {
      if (c1_i63 <= -2147483648L) {
        c1_i63 = -2147483648L;
      }
    }

    c1_i64 = (int64_T)32 - (int64_T)(int32_T)c1_i63;
    if (c1_i64 > 2147483647L) {
      c1_i64 = 2147483647L;
    } else {
      if (c1_i64 <= -2147483648L) {
        c1_i64 = -2147483648L;
      }
    }

    c1_d_k = (int32_T)c1_i64;
    c1_g_x = c1_d_k;
    c1_h_x = c1_g_x;
    if (c1_d_k != c1_h_x) {
      c1_eml_error(chartInstance);
    }

    c1_d_a1 = c1_e_a;
    c1_d_k1 = c1_d_k;
    c1_valIn = 0U;
    if ((real_T)c1_d_k1 < 0.0) {
      c1_i65 = c1_d_k1;
      if (c1_i65 <= MIN_int32_T) {
        c1_f_saturatedUnaryMinus = MAX_int32_T;
      } else {
        c1_f_saturatedUnaryMinus = -c1_i65;
      }

      c1_i66 = c1_f_saturatedUnaryMinus;
      if (c1_i66 <= 0) {
        c1_i66 = 0;
      } else {
        if (c1_i66 > 255) {
          c1_i66 = 255;
        }
      }

      c1_d_absk1 = (uint8_T)c1_i66;
      if (c1_d_absk1 < 32) {
        c1_valIn = c1_d_a1 >> (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_d_absk1), 0, 31, 1,
          1);
      }
    } else {
      c1_i67 = c1_d_k1;
      if (c1_i67 <= 0) {
        c1_i67 = 0;
      } else {
        if (c1_i67 > 255) {
          c1_i67 = 255;
        }
      }

      c1_d_absk1 = (uint8_T)c1_i67;
      if (c1_d_absk1 < 32) {
        c1_valIn = c1_d_a1 << (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_d_absk1), 0, 31, 1,
          1);
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 112);
    c1_f_a = *c1_TempO;
    c1_b_b = c1_valIn;
    *c1_TempO = c1_f_a | c1_b_b;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 113);
    c1_i68 = (int64_T)*c1_bitposO + (int64_T)c1_bitsIn;
    if (c1_i68 > 2147483647L) {
      c1_i68 = 2147483647L;
    } else {
      if (c1_i68 <= -2147483648L) {
        c1_i68 = -2147483648L;
      }
    }

    *c1_bitposO = (int32_T)c1_i68;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 114);
    *c1_flag = 1.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -114);
  sf_debug_symbol_scope_pop();
}

static void c1_eml_error(SFc1_vipcodecInstanceStruct *chartInstance)
{
  int32_T c1_i69;
  static char_T c1_varargin_1[42] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'b', 'i', 't', 's', 'h', 'i', 'f', 't', '_', 'i',
    'n', 'p', 'u', 't', 's', 'M', 'u', 's', 't', 'B', 'e', 'I', 'n', 't', 'e',
    'g', 'e', 'r', 's' };

  char_T c1_u[42];
  const mxArray *c1_y = NULL;
  for (c1_i69 = 0; c1_i69 < 42; c1_i69++) {
    c1_u[c1_i69] = c1_varargin_1[c1_i69];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 42));
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U, 14,
    c1_y));
}

static void c1_b_putbits(SFc1_vipcodecInstanceStruct *chartInstance, int32_T
  c1_bitpos, uint32_T c1_out[15], uint32_T c1_Temp, real_T c1_outpos, real32_T
  c1_val, real_T c1_bits, real_T *c1_flag, int32_T *c1_bitposO, uint32_T
  c1_outO[15], uint32_T *c1_TempO, real_T *c1_outposO)
{
  uint32_T c1_debug_family_var_map[17];
  uint32_T c1_valIn;
  int32_T c1_bitsIn;
  int32_T c1_bitsleft;
  uint32_T c1_bval;
  real_T c1_nargin = 6.0;
  real_T c1_nargout = 5.0;
  real32_T c1_f7;
  real32_T c1_f8;
  real32_T c1_f9;
  uint32_T c1_u4;
  real_T c1_d4;
  real_T c1_d5;
  real_T c1_d6;
  int32_T c1_i70;
  int32_T c1_i71;
  int64_T c1_i72;
  int64_T c1_i73;
  uint32_T c1_a;
  int64_T c1_i74;
  int32_T c1_i75;
  int32_T c1_saturatedUnaryMinus;
  int32_T c1_k;
  int32_T c1_x;
  int32_T c1_b_x;
  uint32_T c1_a1;
  int32_T c1_k1;
  int32_T c1_i76;
  int32_T c1_b_saturatedUnaryMinus;
  int32_T c1_i77;
  uint8_T c1_absk1;
  int32_T c1_i78;
  uint32_T c1_b_a;
  uint32_T c1_b;
  int64_T c1_i79;
  uint32_T c1_c_a;
  int64_T c1_i80;
  int32_T c1_b_k;
  int32_T c1_c_x;
  int32_T c1_d_x;
  uint32_T c1_b_a1;
  int32_T c1_b_k1;
  int32_T c1_i81;
  int32_T c1_c_saturatedUnaryMinus;
  int32_T c1_i82;
  uint8_T c1_b_absk1;
  int32_T c1_i83;
  uint32_T c1_d_a;
  int64_T c1_i84;
  int32_T c1_i85;
  int32_T c1_d_saturatedUnaryMinus;
  int32_T c1_c_k;
  int32_T c1_e_x;
  int32_T c1_f_x;
  uint32_T c1_c_a1;
  int32_T c1_c_k1;
  int32_T c1_i86;
  int32_T c1_e_saturatedUnaryMinus;
  int32_T c1_i87;
  uint8_T c1_c_absk1;
  int32_T c1_i88;
  uint32_T c1_e_a;
  int64_T c1_i89;
  int64_T c1_i90;
  int32_T c1_d_k;
  int32_T c1_g_x;
  int32_T c1_h_x;
  uint32_T c1_d_a1;
  int32_T c1_d_k1;
  int32_T c1_i91;
  int32_T c1_f_saturatedUnaryMinus;
  int32_T c1_i92;
  uint8_T c1_d_absk1;
  int32_T c1_i93;
  uint32_T c1_f_a;
  uint32_T c1_b_b;
  int64_T c1_i94;
  boolean_T guard1 = FALSE;
  sf_debug_symbol_scope_push_eml(0U, 17U, 17U, c1_c_debug_family_names,
    c1_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c1_valIn, 0U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_bitsIn, 1U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_bitsleft, 2U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_bval, 3U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargin, 4U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargout, 5U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_bitpos, 6U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_out, 7U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_Temp, 8U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_outpos, 9U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_val, 10U, c1_f_sf_marshallOut,
    c1_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_bits, 11U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_flag, 12U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_bitposO, 13U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_outO, 14U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_TempO, 15U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_outposO, 16U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  CV_EML_FCN(0, 1);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 87);
  c1_f7 = c1_val;
  c1_f8 = c1_f7;
  if ((c1_f8 < 8.388608E+6F) && (c1_f8 > -8.388608E+6F)) {
    c1_f8 = c1_f8 < 0.0F ? muSingleScalarCeil(c1_f8 - 0.5F) :
      muSingleScalarFloor(c1_f8 + 0.5F);
  }

  c1_f9 = c1_f8;
  if (c1_f9 < 4.2949673E+9F) {
    if (c1_f9 >= 0.0F) {
      c1_u4 = (uint32_T)c1_f9;
    } else {
      c1_u4 = 0U;
    }
  } else if (c1_f9 >= 4.2949673E+9F) {
    c1_u4 = MAX_uint32_T;
  } else {
    c1_u4 = 0U;
  }

  c1_valIn = c1_u4;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 88);
  c1_d4 = c1_bits;
  c1_d5 = c1_d4;
  c1_d5 = c1_d5 < 0.0 ? muDoubleScalarCeil(c1_d5 - 0.5) : muDoubleScalarFloor
    (c1_d5 + 0.5);
  c1_d6 = c1_d5;
  if (c1_d6 < 2.147483648E+9) {
    if (c1_d6 >= -2.147483648E+9) {
      c1_i70 = (int32_T)c1_d6;
    } else {
      c1_i70 = MIN_int32_T;
    }
  } else if (c1_d6 >= 2.147483648E+9) {
    c1_i70 = MAX_int32_T;
  } else {
    c1_i70 = 0;
  }

  c1_bitsIn = c1_i70;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 89);
  *c1_bitposO = c1_bitpos;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 90);
  for (c1_i71 = 0; c1_i71 < 15; c1_i71++) {
    c1_outO[c1_i71] = c1_out[c1_i71];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 91);
  *c1_TempO = c1_Temp;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 92);
  *c1_outposO = c1_outpos;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 94);
  c1_i72 = (int64_T)*c1_bitposO + (int64_T)c1_bitsIn;
  if (c1_i72 > 2147483647L) {
    c1_i72 = 2147483647L;
  } else {
    if (c1_i72 <= -2147483648L) {
      c1_i72 = -2147483648L;
    }
  }

  guard1 = FALSE;
  if (CV_EML_IF(0, 13, (real_T)(int32_T)c1_i72 > 32.0)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 95);
    c1_i73 = (int64_T)32 - (int64_T)*c1_bitposO;
    if (c1_i73 > 2147483647L) {
      c1_i73 = 2147483647L;
    } else {
      if (c1_i73 <= -2147483648L) {
        c1_i73 = -2147483648L;
      }
    }

    c1_bitsleft = (int32_T)c1_i73;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 96);
    c1_bval = 0U;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 97);
    c1_a = c1_valIn;
    c1_i74 = (int64_T)c1_bitsIn - (int64_T)c1_bitsleft;
    if (c1_i74 > 2147483647L) {
      c1_i74 = 2147483647L;
    } else {
      if (c1_i74 <= -2147483648L) {
        c1_i74 = -2147483648L;
      }
    }

    c1_i75 = (int32_T)c1_i74;
    if (c1_i75 <= MIN_int32_T) {
      c1_saturatedUnaryMinus = MAX_int32_T;
    } else {
      c1_saturatedUnaryMinus = -c1_i75;
    }

    c1_k = c1_saturatedUnaryMinus;
    c1_x = c1_k;
    c1_b_x = c1_x;
    if (c1_k != c1_b_x) {
      c1_eml_error(chartInstance);
    }

    c1_a1 = c1_a;
    c1_k1 = c1_k;
    c1_bval = 0U;
    if ((real_T)c1_k1 < 0.0) {
      c1_i76 = c1_k1;
      if (c1_i76 <= MIN_int32_T) {
        c1_b_saturatedUnaryMinus = MAX_int32_T;
      } else {
        c1_b_saturatedUnaryMinus = -c1_i76;
      }

      c1_i77 = c1_b_saturatedUnaryMinus;
      if (c1_i77 <= 0) {
        c1_i77 = 0;
      } else {
        if (c1_i77 > 255) {
          c1_i77 = 255;
        }
      }

      c1_absk1 = (uint8_T)c1_i77;
      if (c1_absk1 < 32) {
        c1_bval = c1_a1 >> (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_absk1), 0, 31, 1,
          1);
      }
    } else {
      c1_i78 = c1_k1;
      if (c1_i78 <= 0) {
        c1_i78 = 0;
      } else {
        if (c1_i78 > 255) {
          c1_i78 = 255;
        }
      }

      c1_absk1 = (uint8_T)c1_i78;
      if (c1_absk1 < 32) {
        c1_bval = c1_a1 << (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_absk1), 0, 31, 1,
          1);
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 98);
    c1_b_a = *c1_TempO;
    c1_b = c1_bval;
    *c1_TempO = c1_b_a | c1_b;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 99);
    c1_outO[_SFD_EML_ARRAY_BOUNDS_CHECK("outO", (int32_T)_SFD_INTEGER_CHECK(
      "outposO", *c1_outposO), 1, 15, 1, 0) - 1] = *c1_TempO;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 100);
    (*c1_outposO)++;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 101);
    if (CV_EML_IF(0, 14, *c1_outposO > 15.0)) {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 102);
      *c1_flag = 0.0;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 105);
      *c1_TempO = 0U;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 106);
      *c1_bitposO = 0;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 107);
      c1_i79 = (int64_T)c1_bitsIn - (int64_T)c1_bitsleft;
      if (c1_i79 > 2147483647L) {
        c1_i79 = 2147483647L;
      } else {
        if (c1_i79 <= -2147483648L) {
          c1_i79 = -2147483648L;
        }
      }

      c1_bitsIn = (int32_T)c1_i79;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 108);
      c1_c_a = c1_valIn;
      c1_i80 = (int64_T)32 - (int64_T)c1_bitsIn;
      if (c1_i80 > 2147483647L) {
        c1_i80 = 2147483647L;
      } else {
        if (c1_i80 <= -2147483648L) {
          c1_i80 = -2147483648L;
        }
      }

      c1_b_k = (int32_T)c1_i80;
      c1_c_x = c1_b_k;
      c1_d_x = c1_c_x;
      if (c1_b_k != c1_d_x) {
        c1_eml_error(chartInstance);
      }

      c1_b_a1 = c1_c_a;
      c1_b_k1 = c1_b_k;
      c1_valIn = 0U;
      if ((real_T)c1_b_k1 < 0.0) {
        c1_i81 = c1_b_k1;
        if (c1_i81 <= MIN_int32_T) {
          c1_c_saturatedUnaryMinus = MAX_int32_T;
        } else {
          c1_c_saturatedUnaryMinus = -c1_i81;
        }

        c1_i82 = c1_c_saturatedUnaryMinus;
        if (c1_i82 <= 0) {
          c1_i82 = 0;
        } else {
          if (c1_i82 > 255) {
            c1_i82 = 255;
          }
        }

        c1_b_absk1 = (uint8_T)c1_i82;
        if (c1_b_absk1 < 32) {
          c1_valIn = c1_b_a1 >> (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
            "", (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_b_absk1), 0,
            31, 1, 1);
        }
      } else {
        c1_i83 = c1_b_k1;
        if (c1_i83 <= 0) {
          c1_i83 = 0;
        } else {
          if (c1_i83 > 255) {
            c1_i83 = 255;
          }
        }

        c1_b_absk1 = (uint8_T)c1_i83;
        if (c1_b_absk1 < 32) {
          c1_valIn = c1_b_a1 << (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
            "", (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_b_absk1), 0,
            31, 1, 1);
        }
      }

      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 109);
      c1_d_a = c1_valIn;
      c1_i84 = (int64_T)32 - (int64_T)c1_bitsIn;
      if (c1_i84 > 2147483647L) {
        c1_i84 = 2147483647L;
      } else {
        if (c1_i84 <= -2147483648L) {
          c1_i84 = -2147483648L;
        }
      }

      c1_i85 = (int32_T)c1_i84;
      if (c1_i85 <= MIN_int32_T) {
        c1_d_saturatedUnaryMinus = MAX_int32_T;
      } else {
        c1_d_saturatedUnaryMinus = -c1_i85;
      }

      c1_c_k = c1_d_saturatedUnaryMinus;
      c1_e_x = c1_c_k;
      c1_f_x = c1_e_x;
      if (c1_c_k != c1_f_x) {
        c1_eml_error(chartInstance);
      }

      c1_c_a1 = c1_d_a;
      c1_c_k1 = c1_c_k;
      c1_valIn = 0U;
      if ((real_T)c1_c_k1 < 0.0) {
        c1_i86 = c1_c_k1;
        if (c1_i86 <= MIN_int32_T) {
          c1_e_saturatedUnaryMinus = MAX_int32_T;
        } else {
          c1_e_saturatedUnaryMinus = -c1_i86;
        }

        c1_i87 = c1_e_saturatedUnaryMinus;
        if (c1_i87 <= 0) {
          c1_i87 = 0;
        } else {
          if (c1_i87 > 255) {
            c1_i87 = 255;
          }
        }

        c1_c_absk1 = (uint8_T)c1_i87;
        if (c1_c_absk1 < 32) {
          c1_valIn = c1_c_a1 >> (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
            "", (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_c_absk1), 0,
            31, 1, 1);
        }
      } else {
        c1_i88 = c1_c_k1;
        if (c1_i88 <= 0) {
          c1_i88 = 0;
        } else {
          if (c1_i88 > 255) {
            c1_i88 = 255;
          }
        }

        c1_c_absk1 = (uint8_T)c1_i88;
        if (c1_c_absk1 < 32) {
          c1_valIn = c1_c_a1 << (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
            "", (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_c_absk1), 0,
            31, 1, 1);
        }
      }

      guard1 = TRUE;
    }
  } else {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 111);
    c1_e_a = c1_valIn;
    c1_i89 = (int64_T)c1_bitsIn + (int64_T)*c1_bitposO;
    if (c1_i89 > 2147483647L) {
      c1_i89 = 2147483647L;
    } else {
      if (c1_i89 <= -2147483648L) {
        c1_i89 = -2147483648L;
      }
    }

    c1_i90 = (int64_T)32 - (int64_T)(int32_T)c1_i89;
    if (c1_i90 > 2147483647L) {
      c1_i90 = 2147483647L;
    } else {
      if (c1_i90 <= -2147483648L) {
        c1_i90 = -2147483648L;
      }
    }

    c1_d_k = (int32_T)c1_i90;
    c1_g_x = c1_d_k;
    c1_h_x = c1_g_x;
    if (c1_d_k != c1_h_x) {
      c1_eml_error(chartInstance);
    }

    c1_d_a1 = c1_e_a;
    c1_d_k1 = c1_d_k;
    c1_valIn = 0U;
    if ((real_T)c1_d_k1 < 0.0) {
      c1_i91 = c1_d_k1;
      if (c1_i91 <= MIN_int32_T) {
        c1_f_saturatedUnaryMinus = MAX_int32_T;
      } else {
        c1_f_saturatedUnaryMinus = -c1_i91;
      }

      c1_i92 = c1_f_saturatedUnaryMinus;
      if (c1_i92 <= 0) {
        c1_i92 = 0;
      } else {
        if (c1_i92 > 255) {
          c1_i92 = 255;
        }
      }

      c1_d_absk1 = (uint8_T)c1_i92;
      if (c1_d_absk1 < 32) {
        c1_valIn = c1_d_a1 >> (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_d_absk1), 0, 31, 1,
          1);
      }
    } else {
      c1_i93 = c1_d_k1;
      if (c1_i93 <= 0) {
        c1_i93 = 0;
      } else {
        if (c1_i93 > 255) {
          c1_i93 = 255;
        }
      }

      c1_d_absk1 = (uint8_T)c1_i93;
      if (c1_d_absk1 < 32) {
        c1_valIn = c1_d_a1 << (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_d_absk1), 0, 31, 1,
          1);
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 112);
    c1_f_a = *c1_TempO;
    c1_b_b = c1_valIn;
    *c1_TempO = c1_f_a | c1_b_b;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 113);
    c1_i94 = (int64_T)*c1_bitposO + (int64_T)c1_bitsIn;
    if (c1_i94 > 2147483647L) {
      c1_i94 = 2147483647L;
    } else {
      if (c1_i94 <= -2147483648L) {
        c1_i94 = -2147483648L;
      }
    }

    *c1_bitposO = (int32_T)c1_i94;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 114);
    *c1_flag = 1.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -114);
  sf_debug_symbol_scope_pop();
}

static void c1_c_putbits(SFc1_vipcodecInstanceStruct *chartInstance, int32_T
  c1_bitpos, uint32_T c1_out[15], uint32_T c1_Temp, real_T c1_outpos, real_T
  c1_val, real_T c1_bits, real_T *c1_flag, int32_T *c1_bitposO, uint32_T
  c1_outO[15], uint32_T *c1_TempO, real_T *c1_outposO)
{
  uint32_T c1_debug_family_var_map[17];
  uint32_T c1_valIn;
  int32_T c1_bitsIn;
  int32_T c1_bitsleft;
  uint32_T c1_bval;
  real_T c1_nargin = 6.0;
  real_T c1_nargout = 5.0;
  real_T c1_d7;
  real_T c1_d8;
  real_T c1_d9;
  uint32_T c1_u5;
  real_T c1_d10;
  real_T c1_d11;
  real_T c1_d12;
  int32_T c1_i95;
  int32_T c1_i96;
  int64_T c1_i97;
  int64_T c1_i98;
  uint32_T c1_a;
  int64_T c1_i99;
  int32_T c1_i100;
  int32_T c1_saturatedUnaryMinus;
  int32_T c1_k;
  int32_T c1_x;
  int32_T c1_b_x;
  uint32_T c1_a1;
  int32_T c1_k1;
  int32_T c1_i101;
  int32_T c1_b_saturatedUnaryMinus;
  int32_T c1_i102;
  uint8_T c1_absk1;
  int32_T c1_i103;
  uint32_T c1_b_a;
  uint32_T c1_b;
  int64_T c1_i104;
  uint32_T c1_c_a;
  int64_T c1_i105;
  int32_T c1_b_k;
  int32_T c1_c_x;
  int32_T c1_d_x;
  uint32_T c1_b_a1;
  int32_T c1_b_k1;
  int32_T c1_i106;
  int32_T c1_c_saturatedUnaryMinus;
  int32_T c1_i107;
  uint8_T c1_b_absk1;
  int32_T c1_i108;
  uint32_T c1_d_a;
  int64_T c1_i109;
  int32_T c1_i110;
  int32_T c1_d_saturatedUnaryMinus;
  int32_T c1_c_k;
  int32_T c1_e_x;
  int32_T c1_f_x;
  uint32_T c1_c_a1;
  int32_T c1_c_k1;
  int32_T c1_i111;
  int32_T c1_e_saturatedUnaryMinus;
  int32_T c1_i112;
  uint8_T c1_c_absk1;
  int32_T c1_i113;
  uint32_T c1_e_a;
  int64_T c1_i114;
  int64_T c1_i115;
  int32_T c1_d_k;
  int32_T c1_g_x;
  int32_T c1_h_x;
  uint32_T c1_d_a1;
  int32_T c1_d_k1;
  int32_T c1_i116;
  int32_T c1_f_saturatedUnaryMinus;
  int32_T c1_i117;
  uint8_T c1_d_absk1;
  int32_T c1_i118;
  uint32_T c1_f_a;
  uint32_T c1_b_b;
  int64_T c1_i119;
  boolean_T guard1 = FALSE;
  sf_debug_symbol_scope_push_eml(0U, 17U, 17U, c1_d_debug_family_names,
    c1_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c1_valIn, 0U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_bitsIn, 1U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_bitsleft, 2U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_bval, 3U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargin, 4U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargout, 5U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_bitpos, 6U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_out, 7U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_Temp, 8U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_outpos, 9U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_val, 10U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_bits, 11U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_flag, 12U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_bitposO, 13U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_outO, 14U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_TempO, 15U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_outposO, 16U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  CV_EML_FCN(0, 1);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 87);
  c1_d7 = c1_val;
  c1_d8 = c1_d7;
  c1_d8 = c1_d8 < 0.0 ? muDoubleScalarCeil(c1_d8 - 0.5) : muDoubleScalarFloor
    (c1_d8 + 0.5);
  c1_d9 = c1_d8;
  if (c1_d9 < 4.294967296E+9) {
    if (c1_d9 >= 0.0) {
      c1_u5 = (uint32_T)c1_d9;
    } else {
      c1_u5 = 0U;
    }
  } else if (c1_d9 >= 4.294967296E+9) {
    c1_u5 = MAX_uint32_T;
  } else {
    c1_u5 = 0U;
  }

  c1_valIn = c1_u5;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 88);
  c1_d10 = c1_bits;
  c1_d11 = c1_d10;
  c1_d11 = c1_d11 < 0.0 ? muDoubleScalarCeil(c1_d11 - 0.5) : muDoubleScalarFloor
    (c1_d11 + 0.5);
  c1_d12 = c1_d11;
  if (c1_d12 < 2.147483648E+9) {
    if (c1_d12 >= -2.147483648E+9) {
      c1_i95 = (int32_T)c1_d12;
    } else {
      c1_i95 = MIN_int32_T;
    }
  } else if (c1_d12 >= 2.147483648E+9) {
    c1_i95 = MAX_int32_T;
  } else {
    c1_i95 = 0;
  }

  c1_bitsIn = c1_i95;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 89);
  *c1_bitposO = c1_bitpos;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 90);
  for (c1_i96 = 0; c1_i96 < 15; c1_i96++) {
    c1_outO[c1_i96] = c1_out[c1_i96];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 91);
  *c1_TempO = c1_Temp;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 92);
  *c1_outposO = c1_outpos;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 94);
  c1_i97 = (int64_T)*c1_bitposO + (int64_T)c1_bitsIn;
  if (c1_i97 > 2147483647L) {
    c1_i97 = 2147483647L;
  } else {
    if (c1_i97 <= -2147483648L) {
      c1_i97 = -2147483648L;
    }
  }

  guard1 = FALSE;
  if (CV_EML_IF(0, 13, (real_T)(int32_T)c1_i97 > 32.0)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 95);
    c1_i98 = (int64_T)32 - (int64_T)*c1_bitposO;
    if (c1_i98 > 2147483647L) {
      c1_i98 = 2147483647L;
    } else {
      if (c1_i98 <= -2147483648L) {
        c1_i98 = -2147483648L;
      }
    }

    c1_bitsleft = (int32_T)c1_i98;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 96);
    c1_bval = 0U;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 97);
    c1_a = c1_valIn;
    c1_i99 = (int64_T)c1_bitsIn - (int64_T)c1_bitsleft;
    if (c1_i99 > 2147483647L) {
      c1_i99 = 2147483647L;
    } else {
      if (c1_i99 <= -2147483648L) {
        c1_i99 = -2147483648L;
      }
    }

    c1_i100 = (int32_T)c1_i99;
    if (c1_i100 <= MIN_int32_T) {
      c1_saturatedUnaryMinus = MAX_int32_T;
    } else {
      c1_saturatedUnaryMinus = -c1_i100;
    }

    c1_k = c1_saturatedUnaryMinus;
    c1_x = c1_k;
    c1_b_x = c1_x;
    if (c1_k != c1_b_x) {
      c1_eml_error(chartInstance);
    }

    c1_a1 = c1_a;
    c1_k1 = c1_k;
    c1_bval = 0U;
    if ((real_T)c1_k1 < 0.0) {
      c1_i101 = c1_k1;
      if (c1_i101 <= MIN_int32_T) {
        c1_b_saturatedUnaryMinus = MAX_int32_T;
      } else {
        c1_b_saturatedUnaryMinus = -c1_i101;
      }

      c1_i102 = c1_b_saturatedUnaryMinus;
      if (c1_i102 <= 0) {
        c1_i102 = 0;
      } else {
        if (c1_i102 > 255) {
          c1_i102 = 255;
        }
      }

      c1_absk1 = (uint8_T)c1_i102;
      if (c1_absk1 < 32) {
        c1_bval = c1_a1 >> (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_absk1), 0, 31, 1,
          1);
      }
    } else {
      c1_i103 = c1_k1;
      if (c1_i103 <= 0) {
        c1_i103 = 0;
      } else {
        if (c1_i103 > 255) {
          c1_i103 = 255;
        }
      }

      c1_absk1 = (uint8_T)c1_i103;
      if (c1_absk1 < 32) {
        c1_bval = c1_a1 << (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_absk1), 0, 31, 1,
          1);
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 98);
    c1_b_a = *c1_TempO;
    c1_b = c1_bval;
    *c1_TempO = c1_b_a | c1_b;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 99);
    c1_outO[_SFD_EML_ARRAY_BOUNDS_CHECK("outO", (int32_T)_SFD_INTEGER_CHECK(
      "outposO", *c1_outposO), 1, 15, 1, 0) - 1] = *c1_TempO;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 100);
    (*c1_outposO)++;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 101);
    if (CV_EML_IF(0, 14, *c1_outposO > 15.0)) {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 102);
      *c1_flag = 0.0;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 105);
      *c1_TempO = 0U;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 106);
      *c1_bitposO = 0;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 107);
      c1_i104 = (int64_T)c1_bitsIn - (int64_T)c1_bitsleft;
      if (c1_i104 > 2147483647L) {
        c1_i104 = 2147483647L;
      } else {
        if (c1_i104 <= -2147483648L) {
          c1_i104 = -2147483648L;
        }
      }

      c1_bitsIn = (int32_T)c1_i104;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 108);
      c1_c_a = c1_valIn;
      c1_i105 = (int64_T)32 - (int64_T)c1_bitsIn;
      if (c1_i105 > 2147483647L) {
        c1_i105 = 2147483647L;
      } else {
        if (c1_i105 <= -2147483648L) {
          c1_i105 = -2147483648L;
        }
      }

      c1_b_k = (int32_T)c1_i105;
      c1_c_x = c1_b_k;
      c1_d_x = c1_c_x;
      if (c1_b_k != c1_d_x) {
        c1_eml_error(chartInstance);
      }

      c1_b_a1 = c1_c_a;
      c1_b_k1 = c1_b_k;
      c1_valIn = 0U;
      if ((real_T)c1_b_k1 < 0.0) {
        c1_i106 = c1_b_k1;
        if (c1_i106 <= MIN_int32_T) {
          c1_c_saturatedUnaryMinus = MAX_int32_T;
        } else {
          c1_c_saturatedUnaryMinus = -c1_i106;
        }

        c1_i107 = c1_c_saturatedUnaryMinus;
        if (c1_i107 <= 0) {
          c1_i107 = 0;
        } else {
          if (c1_i107 > 255) {
            c1_i107 = 255;
          }
        }

        c1_b_absk1 = (uint8_T)c1_i107;
        if (c1_b_absk1 < 32) {
          c1_valIn = c1_b_a1 >> (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
            "", (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_b_absk1), 0,
            31, 1, 1);
        }
      } else {
        c1_i108 = c1_b_k1;
        if (c1_i108 <= 0) {
          c1_i108 = 0;
        } else {
          if (c1_i108 > 255) {
            c1_i108 = 255;
          }
        }

        c1_b_absk1 = (uint8_T)c1_i108;
        if (c1_b_absk1 < 32) {
          c1_valIn = c1_b_a1 << (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
            "", (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_b_absk1), 0,
            31, 1, 1);
        }
      }

      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 109);
      c1_d_a = c1_valIn;
      c1_i109 = (int64_T)32 - (int64_T)c1_bitsIn;
      if (c1_i109 > 2147483647L) {
        c1_i109 = 2147483647L;
      } else {
        if (c1_i109 <= -2147483648L) {
          c1_i109 = -2147483648L;
        }
      }

      c1_i110 = (int32_T)c1_i109;
      if (c1_i110 <= MIN_int32_T) {
        c1_d_saturatedUnaryMinus = MAX_int32_T;
      } else {
        c1_d_saturatedUnaryMinus = -c1_i110;
      }

      c1_c_k = c1_d_saturatedUnaryMinus;
      c1_e_x = c1_c_k;
      c1_f_x = c1_e_x;
      if (c1_c_k != c1_f_x) {
        c1_eml_error(chartInstance);
      }

      c1_c_a1 = c1_d_a;
      c1_c_k1 = c1_c_k;
      c1_valIn = 0U;
      if ((real_T)c1_c_k1 < 0.0) {
        c1_i111 = c1_c_k1;
        if (c1_i111 <= MIN_int32_T) {
          c1_e_saturatedUnaryMinus = MAX_int32_T;
        } else {
          c1_e_saturatedUnaryMinus = -c1_i111;
        }

        c1_i112 = c1_e_saturatedUnaryMinus;
        if (c1_i112 <= 0) {
          c1_i112 = 0;
        } else {
          if (c1_i112 > 255) {
            c1_i112 = 255;
          }
        }

        c1_c_absk1 = (uint8_T)c1_i112;
        if (c1_c_absk1 < 32) {
          c1_valIn = c1_c_a1 >> (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
            "", (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_c_absk1), 0,
            31, 1, 1);
        }
      } else {
        c1_i113 = c1_c_k1;
        if (c1_i113 <= 0) {
          c1_i113 = 0;
        } else {
          if (c1_i113 > 255) {
            c1_i113 = 255;
          }
        }

        c1_c_absk1 = (uint8_T)c1_i113;
        if (c1_c_absk1 < 32) {
          c1_valIn = c1_c_a1 << (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
            "", (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_c_absk1), 0,
            31, 1, 1);
        }
      }

      guard1 = TRUE;
    }
  } else {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 111);
    c1_e_a = c1_valIn;
    c1_i114 = (int64_T)c1_bitsIn + (int64_T)*c1_bitposO;
    if (c1_i114 > 2147483647L) {
      c1_i114 = 2147483647L;
    } else {
      if (c1_i114 <= -2147483648L) {
        c1_i114 = -2147483648L;
      }
    }

    c1_i115 = (int64_T)32 - (int64_T)(int32_T)c1_i114;
    if (c1_i115 > 2147483647L) {
      c1_i115 = 2147483647L;
    } else {
      if (c1_i115 <= -2147483648L) {
        c1_i115 = -2147483648L;
      }
    }

    c1_d_k = (int32_T)c1_i115;
    c1_g_x = c1_d_k;
    c1_h_x = c1_g_x;
    if (c1_d_k != c1_h_x) {
      c1_eml_error(chartInstance);
    }

    c1_d_a1 = c1_e_a;
    c1_d_k1 = c1_d_k;
    c1_valIn = 0U;
    if ((real_T)c1_d_k1 < 0.0) {
      c1_i116 = c1_d_k1;
      if (c1_i116 <= MIN_int32_T) {
        c1_f_saturatedUnaryMinus = MAX_int32_T;
      } else {
        c1_f_saturatedUnaryMinus = -c1_i116;
      }

      c1_i117 = c1_f_saturatedUnaryMinus;
      if (c1_i117 <= 0) {
        c1_i117 = 0;
      } else {
        if (c1_i117 > 255) {
          c1_i117 = 255;
        }
      }

      c1_d_absk1 = (uint8_T)c1_i117;
      if (c1_d_absk1 < 32) {
        c1_valIn = c1_d_a1 >> (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_d_absk1), 0, 31, 1,
          1);
      }
    } else {
      c1_i118 = c1_d_k1;
      if (c1_i118 <= 0) {
        c1_i118 = 0;
      } else {
        if (c1_i118 > 255) {
          c1_i118 = 255;
        }
      }

      c1_d_absk1 = (uint8_T)c1_i118;
      if (c1_d_absk1 < 32) {
        c1_valIn = c1_d_a1 << (uint32_T)(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
          (int32_T)(uint8_T)_SFD_INTEGER_CHECK("", (real_T)c1_d_absk1), 0, 31, 1,
          1);
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 112);
    c1_f_a = *c1_TempO;
    c1_b_b = c1_valIn;
    *c1_TempO = c1_f_a | c1_b_b;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 113);
    c1_i119 = (int64_T)*c1_bitposO + (int64_T)c1_bitsIn;
    if (c1_i119 > 2147483647L) {
      c1_i119 = 2147483647L;
    } else {
      if (c1_i119 <= -2147483648L) {
        c1_i119 = -2147483648L;
      }
    }

    *c1_bitposO = (int32_T)c1_i119;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 114);
    *c1_flag = 1.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -114);
  sf_debug_symbol_scope_pop();
}

static uint8_T c1_i_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_vipcodec, const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_vipcodec), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_vipcodec);
  return c1_y;
}

static uint8_T c1_j_emlrt_marshallIn(SFc1_vipcodecInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u6;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u6, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u6;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_vipcodecInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c1_vipcodec_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(190631419U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2576093230U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1512237881U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1580099340U);
}

mxArray *sf_c1_vipcodec_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(3315946183U);
    pr[1] = (double)(2337356126U);
    pr[2] = (double)(2145780040U);
    pr[3] = (double)(511504813U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c1_vipcodec(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"out\",},{M[4],M[0],T\"prev_out\",S'l','i','p'{{M1x2[264 272],M[0],}}},{M[8],M[0],T\"is_active_c1_vipcodec\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_vipcodec_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_vipcodecInstanceStruct *chartInstance;
    chartInstance = (SFc1_vipcodecInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart(_vipcodecMachineNumber_,
          1,
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
        _SFD_CV_INIT_EML(0,3,17,0,0,1,0,7,6);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,2258);
        _SFD_CV_INIT_EML_FCN(0,1,"putbits",2335,-1,3275);
        _SFD_CV_INIT_EML_FCN(0,2,"flushbits",3352,-1,3643);
        _SFD_CV_INIT_EML_IF(0,0,274,294,-1,334);
        _SFD_CV_INIT_EML_IF(0,1,578,589,627,712);
        _SFD_CV_INIT_EML_IF(0,2,826,841,-1,862);
        _SFD_CV_INIT_EML_IF(0,3,880,896,-1,917);
        _SFD_CV_INIT_EML_IF(0,4,1007,1036,1076,1667);
        _SFD_CV_INIT_EML_IF(0,5,1187,1197,1283,1320);
        _SFD_CV_INIT_EML_IF(0,6,1283,1298,-1,1320);
        _SFD_CV_INIT_EML_IF(0,7,1346,1362,-1,1383);
        _SFD_CV_INIT_EML_IF(0,8,1548,1558,-1,-2);
        _SFD_CV_INIT_EML_IF(0,9,1814,1824,1878,1915);
        _SFD_CV_INIT_EML_IF(0,10,1878,1893,-1,1915);
        _SFD_CV_INIT_EML_IF(0,11,1932,1948,-1,1969);
        _SFD_CV_INIT_EML_IF(0,12,2101,2111,-1,-2);
        _SFD_CV_INIT_EML_IF(0,13,2595,2621,-1,3133);
        _SFD_CV_INIT_EML_IF(0,14,2851,2877,-1,-2);
        _SFD_CV_INIT_EML_IF(0,15,3530,3540,3571,3612);
        _SFD_CV_INIT_EML_IF(0,16,3571,3599,-1,-2);
        _SFD_CV_INIT_EML_FOR(0,0,939,959,1699);

        {
          static int condStart[] = { 1011, 1027 };

          static int condEnd[] = { 1023, 1035 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,0,1011,1035,2,0,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 1192 };

          static int condEnd[] = { 1196 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_EML_MCDC(0,1,1191,1196,1,2,&(condStart[0]),&(condEnd[0]),
                                2,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 1553 };

          static int condEnd[] = { 1557 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_EML_MCDC(0,2,1552,1557,1,3,&(condStart[0]),&(condEnd[0]),
                                2,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 1819 };

          static int condEnd[] = { 1823 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_EML_MCDC(0,3,1818,1823,1,4,&(condStart[0]),&(condEnd[0]),
                                2,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 2106 };

          static int condEnd[] = { 2110 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_EML_MCDC(0,4,2105,2110,1,5,&(condStart[0]),&(condEnd[0]),
                                2,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 3535 };

          static int condEnd[] = { 3539 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_EML_MCDC(0,5,3534,3539,1,6,&(condStart[0]),&(condEnd[0]),
                                2,&(pfixExpr[0]));
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
          dimVector[0]= 64;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_SINGLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 15;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT32,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)
            c1_b_sf_marshallIn);
        }

        {
          real32_T (*c1_in)[64];
          uint32_T (*c1_out)[15];
          c1_out = (uint32_T (*)[15])ssGetOutputPortSignal(chartInstance->S, 1);
          c1_in = (real32_T (*)[64])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c1_in);
          _SFD_SET_DATA_VALUE_PTR(1U, *c1_out);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_vipcodecMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c1_vipcodec(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_vipcodecInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c1_vipcodec((SFc1_vipcodecInstanceStruct*) chartInstanceVar);
  initialize_c1_vipcodec((SFc1_vipcodecInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_vipcodec(void *chartInstanceVar)
{
  enable_c1_vipcodec((SFc1_vipcodecInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_vipcodec(void *chartInstanceVar)
{
  disable_c1_vipcodec((SFc1_vipcodecInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_vipcodec(void *chartInstanceVar)
{
  sf_c1_vipcodec((SFc1_vipcodecInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_vipcodec(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_vipcodec((SFc1_vipcodecInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_vipcodec();/* state var info */
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

extern void sf_internal_set_sim_state_c1_vipcodec(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_vipcodec();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_vipcodec((SFc1_vipcodecInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_vipcodec(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_vipcodec(S);
}

static void sf_opaque_set_sim_state_c1_vipcodec(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c1_vipcodec(S, st);
}

static void sf_opaque_terminate_c1_vipcodec(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_vipcodecInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c1_vipcodec((SFc1_vipcodecInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_vipcodec((SFc1_vipcodecInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_vipcodec(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_vipcodec((SFc1_vipcodecInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_vipcodec(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"vipcodec","vipcodec",1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"vipcodec","vipcodec",1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"vipcodec","vipcodec",1,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"vipcodec","vipcodec",1,1);
      sf_mark_chart_reusable_outputs(S,"vipcodec","vipcodec",1,1);
    }

    sf_set_rtw_dwork_info(S,"vipcodec","vipcodec",1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(873400085U));
  ssSetChecksum1(S,(4228914159U));
  ssSetChecksum2(S,(4116199499U));
  ssSetChecksum3(S,(2436554416U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c1_vipcodec(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "vipcodec", "vipcodec",1);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_vipcodec(SimStruct *S)
{
  SFc1_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc1_vipcodecInstanceStruct *)malloc(sizeof
    (SFc1_vipcodecInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_vipcodecInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_vipcodec;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_vipcodec;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_vipcodec;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_vipcodec;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_vipcodec;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_vipcodec;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_vipcodec;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_vipcodec;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_vipcodec;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_vipcodec;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_vipcodec;
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

void c1_vipcodec_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_vipcodec(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_vipcodec(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_vipcodec(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_vipcodec_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
