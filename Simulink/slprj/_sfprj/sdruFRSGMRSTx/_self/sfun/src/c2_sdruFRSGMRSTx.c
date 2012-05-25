/* Include files */

#include "blascompat32.h"
#include "sdruFRSGMRSTx_sfun.h"
#include "c2_sdruFRSGMRSTx.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "sdruFRSGMRSTx_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char * c2_debug_family_names[11] = { "Freq", "frameSize", "t",
  "nargin", "nargout", "code", "amplitude", "frs_toneFreqs", "frs_Fs", "tone",
  "t0" };

/* Function Declarations */
static void initialize_c2_sdruFRSGMRSTx(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance);
static void initialize_params_c2_sdruFRSGMRSTx(SFc2_sdruFRSGMRSTxInstanceStruct *
  chartInstance);
static void enable_c2_sdruFRSGMRSTx(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance);
static void disable_c2_sdruFRSGMRSTx(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance);
static void c2_update_debugger_state_c2_sdruFRSGMRSTx
  (SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_sdruFRSGMRSTx
  (SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance);
static void set_sim_state_c2_sdruFRSGMRSTx(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_st);
static void finalize_c2_sdruFRSGMRSTx(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance);
static void sf_c2_sdruFRSGMRSTx(SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance);
static void c2_chartstep_c2_sdruFRSGMRSTx(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance);
static void initSimStructsc2_sdruFRSGMRSTx(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static real_T c2_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_b_t0, const char_T *c2_identifier);
static real_T c2_b_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_c_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_tone, const char_T *c2_identifier, real32_T
  c2_y[160]);
static void c2_d_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real32_T c2_y[160]);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_e_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_f_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[38]);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_g_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[160]);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_eml_scalar_eg(SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance);
static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_h_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_i_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_sdruFRSGMRSTx, const char_T
  *c2_identifier);
static uint8_T c2_j_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_sdruFRSGMRSTx(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_t0_not_empty = FALSE;
  chartInstance->c2_is_active_c2_sdruFRSGMRSTx = 0U;
}

static void initialize_params_c2_sdruFRSGMRSTx(SFc2_sdruFRSGMRSTxInstanceStruct *
  chartInstance)
{
  real_T c2_dv0[38];
  int32_T c2_i0;
  real_T c2_d0;
  sf_set_error_prefix_string(
    "Error evaluating data 'frs_toneFreqs' in the parent workspace.\n");
  sf_mex_import_named("frs_toneFreqs", sf_mex_get_sfun_param(chartInstance->S, 1,
    0), c2_dv0, 0, 0, 0U, 1, 0U, 1, 38);
  for (c2_i0 = 0; c2_i0 < 38; c2_i0++) {
    chartInstance->c2_frs_toneFreqs[c2_i0] = c2_dv0[c2_i0];
  }

  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  sf_set_error_prefix_string(
    "Error evaluating data 'frs_Fs' in the parent workspace.\n");
  sf_mex_import_named("frs_Fs", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c2_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c2_frs_Fs = c2_d0;
  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
}

static void enable_c2_sdruFRSGMRSTx(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_sdruFRSGMRSTx(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_sdruFRSGMRSTx
  (SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c2_sdruFRSGMRSTx
  (SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i1;
  real32_T c2_u[160];
  const mxArray *c2_b_y = NULL;
  real_T c2_hoistedGlobal;
  real_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  uint8_T c2_b_hoistedGlobal;
  uint8_T c2_c_u;
  const mxArray *c2_d_y = NULL;
  real32_T (*c2_tone)[160];
  c2_tone = (real32_T (*)[160])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(3));
  for (c2_i1 = 0; c2_i1 < 160; c2_i1++) {
    c2_u[c2_i1] = (*c2_tone)[c2_i1];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 1, 0U, 1U, 0U, 2, 160, 1));
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_hoistedGlobal = chartInstance->c2_t0;
  c2_b_u = c2_hoistedGlobal;
  c2_c_y = NULL;
  if (!chartInstance->c2_t0_not_empty) {
    sf_mex_assign(&c2_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c2_y, 1, c2_c_y);
  c2_b_hoistedGlobal = chartInstance->c2_is_active_c2_sdruFRSGMRSTx;
  c2_c_u = c2_b_hoistedGlobal;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_c_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c2_y, 2, c2_d_y);
  sf_mex_assign(&c2_st, c2_y);
  return c2_st;
}

static void set_sim_state_c2_sdruFRSGMRSTx(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real32_T c2_fv0[160];
  int32_T c2_i2;
  real32_T (*c2_tone)[160];
  c2_tone = (real32_T (*)[160])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)),
                        "tone", c2_fv0);
  for (c2_i2 = 0; c2_i2 < 160; c2_i2++) {
    (*c2_tone)[c2_i2] = c2_fv0[c2_i2];
  }

  chartInstance->c2_t0 = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 1)), "t0");
  chartInstance->c2_is_active_c2_sdruFRSGMRSTx = c2_i_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 2)),
     "is_active_c2_sdruFRSGMRSTx");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_sdruFRSGMRSTx(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_sdruFRSGMRSTx(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance)
{
}

static void sf_c2_sdruFRSGMRSTx(SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance)
{
  int32_T c2_i3;
  int32_T c2_i4;
  uint8_T *c2_code;
  real32_T *c2_amplitude;
  real32_T (*c2_tone)[160];
  c2_amplitude = (real32_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c2_tone = (real32_T (*)[160])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_code = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_code, 0U);
  for (c2_i3 = 0; c2_i3 < 160; c2_i3++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c2_tone)[c2_i3], 1U);
  }

  _SFD_DATA_RANGE_CHECK((real_T)*c2_amplitude, 2U);
  for (c2_i4 = 0; c2_i4 < 38; c2_i4++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c2_frs_toneFreqs[c2_i4], 3U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c2_frs_Fs, 4U);
  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_sdruFRSGMRSTx(chartInstance);
  sf_debug_check_for_state_inconsistency(_sdruFRSGMRSTxMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c2_chartstep_c2_sdruFRSGMRSTx(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance)
{
  uint8_T c2_hoistedGlobal;
  real32_T c2_b_hoistedGlobal;
  real_T c2_c_hoistedGlobal;
  uint8_T c2_code;
  real32_T c2_amplitude;
  int32_T c2_i5;
  real_T c2_b_frs_toneFreqs[38];
  real_T c2_b_frs_Fs;
  uint32_T c2_debug_family_var_map[11];
  real_T c2_Freq;
  real_T c2_frameSize;
  real_T c2_t[160];
  real_T c2_nargin = 4.0;
  real_T c2_nargout = 1.0;
  real32_T c2_tone[160];
  real_T c2_d_hoistedGlobal;
  real_T c2_B;
  real_T c2_y;
  real_T c2_b_y;
  real_T c2_c_y;
  int32_T c2_i6;
  real_T c2_d_y[160];
  int32_T c2_i7;
  real_T c2_e_hoistedGlobal;
  real_T c2_b_B;
  real_T c2_e_y;
  real_T c2_f_y;
  real_T c2_g_y;
  real_T c2_h_y;
  real_T c2_f_hoistedGlobal;
  real_T c2_c_B;
  real_T c2_i_y;
  real_T c2_j_y;
  real_T c2_k_y;
  real_T c2_l_y;
  real_T c2_g_hoistedGlobal;
  real_T c2_d_B;
  real_T c2_m_y;
  real_T c2_n_y;
  real_T c2_o_y;
  real_T c2_p_y;
  real_T c2_x;
  real_T c2_q_y;
  real_T c2_xk;
  real_T c2_yk;
  real_T c2_b_x;
  real_T c2_r_y;
  real_T c2_r;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_i_x;
  real_T c2_j_x;
  real_T c2_s_y;
  real_T c2_k_x;
  real_T c2_t_y;
  real_T c2_b;
  real_T c2_u_y;
  real_T c2_l_x;
  real_T c2_m_x;
  real_T c2_b_b;
  real_T c2_v_y;
  real_T c2_a;
  int32_T c2_i8;
  int32_T c2_i9;
  real_T c2_k;
  real_T c2_b_k;
  real_T c2_n_x;
  real_T c2_o_x;
  real32_T c2_b_a;
  int32_T c2_i10;
  real32_T c2_w_y[160];
  int32_T c2_i11;
  int32_T c2_i12;
  uint8_T *c2_b_code;
  real32_T *c2_b_amplitude;
  real32_T (*c2_b_tone)[160];
  c2_b_amplitude = (real32_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c2_b_tone = (real32_T (*)[160])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_b_code = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *c2_b_code;
  c2_b_hoistedGlobal = *c2_b_amplitude;
  c2_c_hoistedGlobal = chartInstance->c2_frs_Fs;
  c2_code = c2_hoistedGlobal;
  c2_amplitude = c2_b_hoistedGlobal;
  for (c2_i5 = 0; c2_i5 < 38; c2_i5++) {
    c2_b_frs_toneFreqs[c2_i5] = chartInstance->c2_frs_toneFreqs[c2_i5];
  }

  c2_b_frs_Fs = c2_c_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 11U, 11U, c2_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c2_Freq, 0U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c2_frameSize, 1U, c2_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c2_t, 2U, c2_g_sf_marshallOut,
    c2_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 3U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 4U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c2_code, 5U, c2_f_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_amplitude, 6U, c2_e_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c2_b_frs_toneFreqs, 7U,
    c2_d_sf_marshallOut, c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_b_frs_Fs, 8U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_tone, 9U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&chartInstance->c2_t0, 10U,
    c2_sf_marshallOut, c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 31);
  c2_Freq = c2_b_frs_toneFreqs[(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
    "frs_toneFreqs", (int32_T)(uint8_T)_SFD_INTEGER_CHECK("code", (real_T)
    c2_code), 1, 38, 1, 0) - 1];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 32);
  c2_frameSize = 160.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 34);
  if (CV_EML_IF(0, 0, !chartInstance->c2_t0_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 35);
    chartInstance->c2_t0 = 0.0;
    chartInstance->c2_t0_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 38);
  c2_d_hoistedGlobal = chartInstance->c2_t0;
  c2_B = c2_b_frs_Fs;
  c2_y = c2_B;
  c2_b_y = c2_y;
  c2_c_y = c2_b_y;
  for (c2_i6 = 0; c2_i6 < 160; c2_i6++) {
    c2_d_y[c2_i6] = (real_T)c2_i6 / c2_c_y;
  }

  for (c2_i7 = 0; c2_i7 < 160; c2_i7++) {
    c2_t[c2_i7] = c2_d_hoistedGlobal + c2_d_y[c2_i7];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 40);
  c2_e_hoistedGlobal = chartInstance->c2_t0;
  c2_b_B = c2_b_frs_Fs;
  c2_e_y = c2_b_B;
  c2_f_y = c2_e_y;
  c2_g_y = c2_f_y;
  c2_h_y = 160.0 / c2_g_y;
  chartInstance->c2_t0 = c2_e_hoistedGlobal + c2_h_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
  c2_f_hoistedGlobal = chartInstance->c2_t0;
  c2_c_B = c2_Freq;
  c2_i_y = c2_c_B;
  c2_j_y = c2_i_y;
  c2_k_y = c2_j_y;
  c2_l_y = 1.0 / c2_k_y;
  if (CV_EML_IF(0, 1, c2_f_hoistedGlobal > c2_l_y)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 44);
    c2_g_hoistedGlobal = chartInstance->c2_t0;
    c2_d_B = c2_Freq;
    c2_m_y = c2_d_B;
    c2_n_y = c2_m_y;
    c2_o_y = c2_n_y;
    c2_p_y = 1.0 / c2_o_y;
    c2_x = c2_g_hoistedGlobal;
    c2_q_y = c2_p_y;
    c2_eml_scalar_eg(chartInstance);
    c2_xk = c2_x;
    c2_yk = c2_q_y;
    c2_b_x = c2_xk;
    c2_r_y = c2_yk;
    c2_eml_scalar_eg(chartInstance);
    if (c2_r_y == 0.0) {
      c2_r = c2_b_x;
    } else {
      c2_c_x = c2_r_y;
      c2_d_x = c2_c_x;
      c2_d_x = muDoubleScalarFloor(c2_d_x);
      if (c2_r_y == c2_d_x) {
        c2_e_x = c2_b_x / c2_r_y;
        c2_f_x = c2_e_x;
        c2_f_x = muDoubleScalarFloor(c2_f_x);
        c2_r = c2_b_x - c2_f_x * c2_r_y;
      } else {
        c2_r = c2_b_x / c2_r_y;
        c2_g_x = c2_r;
        c2_h_x = c2_g_x;
        c2_i_x = c2_h_x;
        if (muDoubleScalarAbs(c2_i_x) > 4.503599627370496E+15) {
        } else if (c2_i_x >= 0.5) {
          c2_h_x = muDoubleScalarFloor(c2_i_x + 0.5);
        } else if (c2_i_x > -0.5) {
          c2_h_x = c2_i_x * 0.0;
        } else {
          c2_h_x = muDoubleScalarCeil(c2_i_x - 0.5);
        }

        c2_j_x = c2_r - c2_h_x;
        c2_s_y = muDoubleScalarAbs(c2_j_x);
        c2_k_x = c2_r;
        c2_t_y = muDoubleScalarAbs(c2_k_x);
        c2_b = c2_t_y;
        c2_u_y = 2.2204460492503131E-16 * c2_b;
        if (c2_s_y <= c2_u_y) {
          c2_r = 0.0;
        } else {
          c2_l_x = c2_r;
          c2_m_x = c2_l_x;
          c2_m_x = muDoubleScalarFloor(c2_m_x);
          c2_r = (c2_r - c2_m_x) * c2_r_y;
        }
      }
    }

    chartInstance->c2_t0 = c2_r;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 47);
  c2_b_b = c2_Freq;
  c2_v_y = 6.2831853071795862 * c2_b_b;
  c2_a = c2_v_y;
  for (c2_i8 = 0; c2_i8 < 160; c2_i8++) {
    c2_d_y[c2_i8] = c2_t[c2_i8];
  }

  for (c2_i9 = 0; c2_i9 < 160; c2_i9++) {
    c2_d_y[c2_i9] *= c2_a;
  }

  for (c2_k = 1.0; c2_k <= 160.0; c2_k++) {
    c2_b_k = c2_k;
    c2_n_x = c2_d_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
      "", c2_b_k), 1, 160, 1, 0) - 1];
    c2_o_x = c2_n_x;
    c2_o_x = muDoubleScalarSin(c2_o_x);
    c2_d_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      c2_b_k), 1, 160, 1, 0) - 1] = c2_o_x;
  }

  c2_b_a = c2_amplitude;
  for (c2_i10 = 0; c2_i10 < 160; c2_i10++) {
    c2_w_y[c2_i10] = c2_b_a * (real32_T)c2_d_y[c2_i10];
  }

  for (c2_i11 = 0; c2_i11 < 160; c2_i11++) {
    c2_tone[c2_i11] = c2_w_y[c2_i11];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -47);
  sf_debug_symbol_scope_pop();
  for (c2_i12 = 0; c2_i12 < 160; c2_i12++) {
    (*c2_b_tone)[c2_i12] = c2_tone[c2_i12];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_sdruFRSGMRSTx(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc2_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  if (!chartInstance->c2_t0_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static real_T c2_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_b_t0, const char_T *c2_identifier)
{
  real_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_t0), &c2_thisId);
  sf_mex_destroy(&c2_b_t0);
  return c2_y;
}

static real_T c2_b_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d1;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_t0_not_empty = FALSE;
  } else {
    chartInstance->c2_t0_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d1, 1, 0, 0U, 0, 0U, 0);
    c2_y = c2_d1;
  }

  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_t0;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc2_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c2_b_t0 = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_t0), &c2_thisId);
  sf_mex_destroy(&c2_b_t0);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i13;
  real32_T c2_b_inData[160];
  int32_T c2_i14;
  real32_T c2_u[160];
  const mxArray *c2_y = NULL;
  SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc2_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i13 = 0; c2_i13 < 160; c2_i13++) {
    c2_b_inData[c2_i13] = (*(real32_T (*)[160])c2_inData)[c2_i13];
  }

  for (c2_i14 = 0; c2_i14 < 160; c2_i14++) {
    c2_u[c2_i14] = c2_b_inData[c2_i14];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 1, 0U, 1U, 0U, 2, 160, 1));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static void c2_c_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_tone, const char_T *c2_identifier, real32_T
  c2_y[160])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_tone), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_tone);
}

static void c2_d_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real32_T c2_y[160])
{
  real32_T c2_fv1[160];
  int32_T c2_i15;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_fv1, 1, 1, 0U, 1, 0U, 2, 160,
                1);
  for (c2_i15 = 0; c2_i15 < 160; c2_i15++) {
    c2_y[c2_i15] = c2_fv1[c2_i15];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_tone;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real32_T c2_y[160];
  int32_T c2_i16;
  SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc2_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c2_tone = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_tone), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_tone);
  for (c2_i16 = 0; c2_i16 < 160; c2_i16++) {
    (*(real32_T (*)[160])c2_outData)[c2_i16] = c2_y[c2_i16];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc2_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static real_T c2_e_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d2;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d2, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d2;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_frs_Fs;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc2_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c2_b_frs_Fs = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_frs_Fs),
    &c2_thisId);
  sf_mex_destroy(&c2_b_frs_Fs);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i17;
  real_T c2_b_inData[38];
  int32_T c2_i18;
  real_T c2_u[38];
  const mxArray *c2_y = NULL;
  SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc2_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i17 = 0; c2_i17 < 38; c2_i17++) {
    c2_b_inData[c2_i17] = (*(real_T (*)[38])c2_inData)[c2_i17];
  }

  for (c2_i18 = 0; c2_i18 < 38; c2_i18++) {
    c2_u[c2_i18] = c2_b_inData[c2_i18];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 38));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static void c2_f_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[38])
{
  real_T c2_dv1[38];
  int32_T c2_i19;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv1, 1, 0, 0U, 1, 0U, 1, 38);
  for (c2_i19 = 0; c2_i19 < 38; c2_i19++) {
    c2_y[c2_i19] = c2_dv1[c2_i19];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_frs_toneFreqs;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[38];
  int32_T c2_i20;
  SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc2_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c2_b_frs_toneFreqs = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_frs_toneFreqs),
                        &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_frs_toneFreqs);
  for (c2_i20 = 0; c2_i20 < 38; c2_i20++) {
    (*(real_T (*)[38])c2_outData)[c2_i20] = c2_y[c2_i20];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc2_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 1, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc2_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(uint8_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 3, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i21;
  real_T c2_b_inData[160];
  int32_T c2_i22;
  real_T c2_u[160];
  const mxArray *c2_y = NULL;
  SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc2_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i21 = 0; c2_i21 < 160; c2_i21++) {
    c2_b_inData[c2_i21] = (*(real_T (*)[160])c2_inData)[c2_i21];
  }

  for (c2_i22 = 0; c2_i22 < 160; c2_i22++) {
    c2_u[c2_i22] = c2_b_inData[c2_i22];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 160));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static void c2_g_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[160])
{
  real_T c2_dv2[160];
  int32_T c2_i23;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv2, 1, 0, 0U, 1, 0U, 2, 1,
                160);
  for (c2_i23 = 0; c2_i23 < 160; c2_i23++) {
    c2_y[c2_i23] = c2_dv2[c2_i23];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_t;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[160];
  int32_T c2_i24;
  SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc2_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c2_t = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_t), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_t);
  for (c2_i24 = 0; c2_i24 < 160; c2_i24++) {
    (*(real_T (*)[160])c2_outData)[c2_i24] = c2_y[c2_i24];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_sdruFRSGMRSTx_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1));
  return c2_nameCaptureInfo;
}

static void c2_eml_scalar_eg(SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance)
{
}

static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc2_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static int32_T c2_h_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i25;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i25, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i25;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc2_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_i_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_sdruFRSGMRSTx, const char_T
  *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_sdruFRSGMRSTx), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_sdruFRSGMRSTx);
  return c2_y;
}

static uint8_T c2_j_emlrt_marshallIn(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_sdruFRSGMRSTxInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c2_sdruFRSGMRSTx_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3094820967U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1138545318U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2371324867U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2399808457U);
}

mxArray *sf_c2_sdruFRSGMRSTx_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(2852351026U);
    pr[1] = (double)(3531997559U);
    pr[2] = (double)(3210309501U);
    pr[3] = (double)(4220485560U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(38);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(160);
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

static const mxArray *sf_get_sim_state_info_c2_sdruFRSGMRSTx(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[11],T\"tone\",},{M[4],M[0],T\"t0\",S'l','i','p'{{M1x2[773 775],M[0],}}},{M[8],M[0],T\"is_active_c2_sdruFRSGMRSTx\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_sdruFRSGMRSTx_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance;
    chartInstance = (SFc2_sdruFRSGMRSTxInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_sdruFRSGMRSTxMachineNumber_,
           2,
           1,
           1,
           5,
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
          init_script_number_translation(_sdruFRSGMRSTxMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (_sdruFRSGMRSTxMachineNumber_,chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_sdruFRSGMRSTxMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"code");
          _SFD_SET_DATA_PROPS(1,2,0,1,"tone");
          _SFD_SET_DATA_PROPS(2,1,1,0,"amplitude");
          _SFD_SET_DATA_PROPS(3,10,0,0,"frs_toneFreqs");
          _SFD_SET_DATA_PROPS(4,10,0,0,"frs_Fs");
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
        _SFD_CV_INIT_EML(0,1,2,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1158);
        _SFD_CV_INIT_EML_IF(0,0,862,876,-1,892);
        _SFD_CV_INIT_EML_IF(0,1,1056,1072,-1,1102);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 160;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_SINGLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_e_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 38;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)
            c2_d_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)c2_c_sf_marshallIn);

        {
          uint8_T *c2_code;
          real32_T *c2_amplitude;
          real32_T (*c2_tone)[160];
          c2_amplitude = (real32_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c2_tone = (real32_T (*)[160])ssGetOutputPortSignal(chartInstance->S, 1);
          c2_code = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c2_code);
          _SFD_SET_DATA_VALUE_PTR(1U, *c2_tone);
          _SFD_SET_DATA_VALUE_PTR(2U, c2_amplitude);
          _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c2_frs_toneFreqs);
          _SFD_SET_DATA_VALUE_PTR(4U, &chartInstance->c2_frs_Fs);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_sdruFRSGMRSTxMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c2_sdruFRSGMRSTx(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_sdruFRSGMRSTxInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_sdruFRSGMRSTx((SFc2_sdruFRSGMRSTxInstanceStruct*)
    chartInstanceVar);
  initialize_c2_sdruFRSGMRSTx((SFc2_sdruFRSGMRSTxInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_sdruFRSGMRSTx(void *chartInstanceVar)
{
  enable_c2_sdruFRSGMRSTx((SFc2_sdruFRSGMRSTxInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_sdruFRSGMRSTx(void *chartInstanceVar)
{
  disable_c2_sdruFRSGMRSTx((SFc2_sdruFRSGMRSTxInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_sdruFRSGMRSTx(void *chartInstanceVar)
{
  sf_c2_sdruFRSGMRSTx((SFc2_sdruFRSGMRSTxInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_sdruFRSGMRSTx(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_sdruFRSGMRSTx
    ((SFc2_sdruFRSGMRSTxInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_sdruFRSGMRSTx();/* state var info */
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

extern void sf_internal_set_sim_state_c2_sdruFRSGMRSTx(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_sdruFRSGMRSTx();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_sdruFRSGMRSTx((SFc2_sdruFRSGMRSTxInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_sdruFRSGMRSTx(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_sdruFRSGMRSTx(S);
}

static void sf_opaque_set_sim_state_c2_sdruFRSGMRSTx(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c2_sdruFRSGMRSTx(S, st);
}

static void sf_opaque_terminate_c2_sdruFRSGMRSTx(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_sdruFRSGMRSTxInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c2_sdruFRSGMRSTx((SFc2_sdruFRSGMRSTxInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_sdruFRSGMRSTx((SFc2_sdruFRSGMRSTxInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_sdruFRSGMRSTx(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_sdruFRSGMRSTx((SFc2_sdruFRSGMRSTxInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_sdruFRSGMRSTx(SimStruct *S)
{
  /* Actual parameters from chart:
     frs_Fs frs_toneFreqs
   */
  const char_T *rtParamNames[] = { "p1", "p2" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for frs_Fs*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);

  /* registration for frs_toneFreqs*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_DOUBLE);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"sdruFRSGMRSTx","sdruFRSGMRSTx",2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"sdruFRSGMRSTx","sdruFRSGMRSTx",2,
                "RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"sdruFRSGMRSTx",
      "sdruFRSGMRSTx",2,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"sdruFRSGMRSTx","sdruFRSGMRSTx",2,2);
      sf_mark_chart_reusable_outputs(S,"sdruFRSGMRSTx","sdruFRSGMRSTx",2,1);
    }

    sf_set_rtw_dwork_info(S,"sdruFRSGMRSTx","sdruFRSGMRSTx",2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3822674219U));
  ssSetChecksum1(S,(2424651885U));
  ssSetChecksum2(S,(2548714385U));
  ssSetChecksum3(S,(72878912U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c2_sdruFRSGMRSTx(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "sdruFRSGMRSTx", "sdruFRSGMRSTx",2);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_sdruFRSGMRSTx(SimStruct *S)
{
  SFc2_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc2_sdruFRSGMRSTxInstanceStruct *)malloc(sizeof
    (SFc2_sdruFRSGMRSTxInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_sdruFRSGMRSTxInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_sdruFRSGMRSTx;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_sdruFRSGMRSTx;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_sdruFRSGMRSTx;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_sdruFRSGMRSTx;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_sdruFRSGMRSTx;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_sdruFRSGMRSTx;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_sdruFRSGMRSTx;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_sdruFRSGMRSTx;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_sdruFRSGMRSTx;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_sdruFRSGMRSTx;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_sdruFRSGMRSTx;
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

void c2_sdruFRSGMRSTx_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_sdruFRSGMRSTx(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_sdruFRSGMRSTx(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_sdruFRSGMRSTx(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_sdruFRSGMRSTx_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
