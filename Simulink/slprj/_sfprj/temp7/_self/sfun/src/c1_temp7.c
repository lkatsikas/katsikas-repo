/* Include files */

#include "blascompat32.h"
#include "temp7_sfun.h"
#include "c1_temp7.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "temp7_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[19] = { "w", "symbols",
  "used_carriers", "tps_set", "pilot_set", "temp", "l", "v", "pilot", "tps", "u",
  "p", "t", "real", "nargin", "nargout", "data_in", "VAR", "data_out" };

/* Function Declarations */
static void initialize_c1_temp7(SFc1_temp7InstanceStruct *chartInstance);
static void initialize_params_c1_temp7(SFc1_temp7InstanceStruct *chartInstance);
static void enable_c1_temp7(SFc1_temp7InstanceStruct *chartInstance);
static void disable_c1_temp7(SFc1_temp7InstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_temp7(SFc1_temp7InstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_temp7(SFc1_temp7InstanceStruct
  *chartInstance);
static void set_sim_state_c1_temp7(SFc1_temp7InstanceStruct *chartInstance,
  const mxArray *c1_st);
static void finalize_c1_temp7(SFc1_temp7InstanceStruct *chartInstance);
static void sf_c1_temp7(SFc1_temp7InstanceStruct *chartInstance);
static void c1_chartstep_c1_temp7(SFc1_temp7InstanceStruct *chartInstance);
static void initSimStructsc1_temp7(SFc1_temp7InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static void c1_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_data_out, const char_T *c1_identifier, creal_T c1_y[115940]);
static void c1_b_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, creal_T c1_y[115940]);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_c_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  c1_struct_pff9OPVgTqbyCupd3ePNxF *c1_y);
static void c1_d_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[1705]);
static void c1_e_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[45]);
static void c1_f_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[17]);
static void c1_g_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[142]);
static void c1_h_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[11968]);
static void c1_i_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[2560]);
static void c1_j_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[2048]);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_k_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_l_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[115940]);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_m_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_n_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_temp7, const char_T *c1_identifier);
static uint8_T c1_o_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_temp7InstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_temp7(SFc1_temp7InstanceStruct *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_is_active_c1_temp7 = 0U;
}

static void initialize_params_c1_temp7(SFc1_temp7InstanceStruct *chartInstance)
{
  const mxArray *c1_m0 = NULL;
  const mxArray *c1_mxField;
  c1_struct_pff9OPVgTqbyCupd3ePNxF c1_r0;
  sf_set_error_prefix_string(
    "Error evaluating data 'VAR' in the parent workspace.\n");
  c1_m0 = sf_mex_get_sfun_param(chartInstance->S, 0, 1);
  c1_mxField = sf_mex_getfield(c1_m0, "w", "VAR", 0);
  sf_mex_import_named("VAR", sf_mex_dup(c1_mxField), c1_r0.w, 1, 0, 0U, 1, 0U, 2,
                      1, 1705);
  c1_mxField = sf_mex_getfield(c1_m0, "continual_pilots", "VAR", 0);
  sf_mex_import_named("VAR", sf_mex_dup(c1_mxField), c1_r0.continual_pilots, 1,
                      0, 0U, 1, 0U, 2, 1, 45);
  c1_mxField = sf_mex_getfield(c1_m0, "tps_signals", "VAR", 0);
  sf_mex_import_named("VAR", sf_mex_dup(c1_mxField), c1_r0.tps_signals, 1, 0, 0U,
                      1, 0U, 2, 1, 17);
  c1_mxField = sf_mex_getfield(c1_m0, "scattered_set", "VAR", 0);
  sf_mex_import_named("VAR", sf_mex_dup(c1_mxField), c1_r0.scattered_set, 1, 0,
                      0U, 1, 0U, 2, 1, 142);
  c1_mxField = sf_mex_getfield(c1_m0, "pilot_set", "VAR", 0);
  sf_mex_import_named("VAR", sf_mex_dup(c1_mxField), c1_r0.pilot_set, 1, 0, 0U,
                      1, 0U, 2, 176, 68);
  c1_mxField = sf_mex_getfield(c1_m0, "CyclicPrefixTX", "VAR", 0);
  sf_mex_import_named("VAR", sf_mex_dup(c1_mxField), c1_r0.CyclicPrefixTX, 1, 0,
                      0U, 1, 0U, 2, 1, 2560);
  c1_mxField = sf_mex_getfield(c1_m0, "CyclicPrefixRX", "VAR", 0);
  sf_mex_import_named("VAR", sf_mex_dup(c1_mxField), c1_r0.CyclicPrefixRX, 1, 0,
                      0U, 1, 0U, 2, 1, 2048);
  sf_mex_destroy(&c1_m0);
  chartInstance->c1_VAR = c1_r0;
  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
}

static void enable_c1_temp7(SFc1_temp7InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_temp7(SFc1_temp7InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_temp7(SFc1_temp7InstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c1_temp7(SFc1_temp7InstanceStruct
  *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  int32_T c1_i0;
  static creal_T c1_u[115940];
  const mxArray *c1_b_y = NULL;
  uint8_T c1_hoistedGlobal;
  uint8_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  creal_T (*c1_data_out)[115940];
  c1_data_out = (creal_T (*)[115940])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(2));
  for (c1_i0 = 0; c1_i0 < 115940; c1_i0++) {
    c1_u[c1_i0] = (*c1_data_out)[c1_i0];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u, 0, 1U, 1U, 0U, 2, 1705, 68));
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_hoistedGlobal = chartInstance->c1_is_active_c1_temp7;
  c1_b_u = c1_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c1_y, 1, c1_c_y);
  sf_mex_assign(&c1_st, c1_y);
  return c1_st;
}

static void set_sim_state_c1_temp7(SFc1_temp7InstanceStruct *chartInstance,
  const mxArray *c1_st)
{
  const mxArray *c1_u;
  static creal_T c1_dcv0[115940];
  int32_T c1_i1;
  creal_T (*c1_data_out)[115940];
  c1_data_out = (creal_T (*)[115940])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)),
                      "data_out", c1_dcv0);
  for (c1_i1 = 0; c1_i1 < 115940; c1_i1++) {
    (*c1_data_out)[c1_i1] = c1_dcv0[c1_i1];
  }

  chartInstance->c1_is_active_c1_temp7 = c1_n_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 1)), "is_active_c1_temp7");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_temp7(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_temp7(SFc1_temp7InstanceStruct *chartInstance)
{
}

static void sf_c1_temp7(SFc1_temp7InstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_temp7(chartInstance);
  sf_debug_check_for_state_inconsistency(_temp7MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c1_chartstep_c1_temp7(SFc1_temp7InstanceStruct *chartInstance)
{
  int32_T c1_i2;
  static creal_T c1_data_in[102816];
  static c1_struct_pff9OPVgTqbyCupd3ePNxF c1_b_VAR;
  uint32_T c1_debug_family_var_map[19];
  real_T c1_w[1705];
  real_T c1_symbols;
  real_T c1_used_carriers;
  real_T c1_tps_set[17];
  real_T c1_pilot_set[11968];
  static real_T c1_temp[115940];
  real_T c1_l;
  real_T c1_v;
  real_T c1_pilot;
  real_T c1_tps;
  real_T c1_u;
  real_T c1_p;
  real_T c1_t;
  real_T c1_real;
  real_T c1_nargin = 2.0;
  real_T c1_nargout = 1.0;
  static creal_T c1_data_out[115940];
  int32_T c1_i3;
  int32_T c1_i4;
  int32_T c1_i5;
  int32_T c1_i6;
  int32_T c1_i7;
  real_T c1_b_l;
  real_T c1_b_u;
  real_T c1_b;
  real_T c1_b_b;
  int32_T c1_i8;
  creal_T (*c1_b_data_out)[115940];
  creal_T (*c1_b_data_in)[102816];
  c1_b_data_out = (creal_T (*)[115940])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_b_data_in = (creal_T (*)[102816])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i2 = 0; c1_i2 < 102816; c1_i2++) {
    c1_data_in[c1_i2] = (*c1_b_data_in)[c1_i2];
  }

  c1_b_VAR = chartInstance->c1_VAR;
  sf_debug_symbol_scope_push_eml(0U, 19U, 19U, c1_debug_family_names,
    c1_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(c1_w, 0U, c1_h_sf_marshallOut,
    c1_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c1_symbols, 1U, c1_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_used_carriers, 2U, c1_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c1_tps_set, 3U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_pilot_set, 4U, c1_f_sf_marshallOut,
    c1_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_temp, 5U, c1_e_sf_marshallOut,
    c1_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_l, 6U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_v, 7U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_pilot, 8U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_tps, 9U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_u, 10U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_p, 11U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_t, 12U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_real, 13U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargin, 14U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargout, 15U, c1_d_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c1_data_in, 16U, c1_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c1_b_VAR, 17U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_data_out, 18U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 3);
  for (c1_i3 = 0; c1_i3 < 1705; c1_i3++) {
    c1_w[c1_i3] = c1_b_VAR.w[c1_i3];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 4);
  c1_symbols = 68.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 5);
  c1_used_carriers = 1705.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 6);
  for (c1_i4 = 0; c1_i4 < 17; c1_i4++) {
    c1_tps_set[c1_i4] = c1_b_VAR.tps_signals[c1_i4];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 7);
  for (c1_i5 = 0; c1_i5 < 11968; c1_i5++) {
    c1_pilot_set[c1_i5] = c1_b_VAR.pilot_set[c1_i5];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 11);
  for (c1_i6 = 0; c1_i6 < 115940; c1_i6++) {
    c1_temp[c1_i6] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 12);
  for (c1_i7 = 0; c1_i7 < 115940; c1_i7++) {
    c1_data_out[c1_i7].re = c1_temp[c1_i7];
    c1_data_out[c1_i7].im = 0.0;
  }

  c1_l = 1.0;
  c1_b_l = 1.0;
  while (c1_b_l <= 68.0) {
    c1_l = c1_b_l;
    CV_EML_FOR(0, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 14);
    c1_v = 1.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 15);
    c1_pilot = 1.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 16);
    c1_tps = 1.0;
    c1_u = 1.0;
    c1_b_u = 1.0;
    while (c1_b_u <= 1705.0) {
      c1_u = c1_b_u;
      CV_EML_FOR(0, 1, 1);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 18);
      c1_p = 1.0 + c1_pilot_set[_SFD_EML_ARRAY_BOUNDS_CHECK("pilot_set",
        (int32_T)_SFD_INTEGER_CHECK("pilot", c1_pilot), 1, 11968, 1, 0) - 1];
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 19);
      if (CV_EML_IF(0, 0, c1_tps <= 17.0)) {
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 20);
        c1_t = 1.0 + c1_tps_set[_SFD_EML_ARRAY_BOUNDS_CHECK("tps_set", (int32_T)
          _SFD_INTEGER_CHECK("tps", c1_tps), 1, 17, 1, 0) - 1];
      } else {
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 22);
        c1_t = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 25);
      if (CV_EML_IF(0, 1, c1_u == c1_p)) {
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 26);
        c1_b = 0.5 - c1_w[_SFD_EML_ARRAY_BOUNDS_CHECK("w", (int32_T)
          _SFD_INTEGER_CHECK("p", c1_p), 1, 1705, 1, 0) - 1];
        c1_real = 2.6666666666666665 * c1_b;
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 27);
        c1_data_out[(_SFD_EML_ARRAY_BOUNDS_CHECK("data_out", (int32_T)
          _SFD_INTEGER_CHECK("u", c1_u), 1, 1705, 1, 0) + 1705 *
                     (_SFD_EML_ARRAY_BOUNDS_CHECK("data_out", (int32_T)
          _SFD_INTEGER_CHECK("l", c1_l), 1, 68, 2, 0) - 1)) - 1].re = c1_real;
        c1_data_out[(_SFD_EML_ARRAY_BOUNDS_CHECK("data_out", (int32_T)
          _SFD_INTEGER_CHECK("u", c1_u), 1, 1705, 1, 0) + 1705 *
                     (_SFD_EML_ARRAY_BOUNDS_CHECK("data_out", (int32_T)
          _SFD_INTEGER_CHECK("l", c1_l), 1, 68, 2, 0) - 1)) - 1].im = 0.0;
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 28);
        c1_pilot++;
      } else {
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 29);
        if (CV_EML_IF(0, 2, c1_u == c1_t)) {
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 30);
          c1_b_b = 0.5 - c1_w[_SFD_EML_ARRAY_BOUNDS_CHECK("w", (int32_T)
            _SFD_INTEGER_CHECK("p", c1_p), 1, 1705, 1, 0) - 1];
          c1_real = 2.0 * c1_b_b;
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 32);
          c1_data_out[(_SFD_EML_ARRAY_BOUNDS_CHECK("data_out", (int32_T)
            _SFD_INTEGER_CHECK("u", c1_u), 1, 1705, 1, 0) + 1705 *
                       (_SFD_EML_ARRAY_BOUNDS_CHECK("data_out", (int32_T)
            _SFD_INTEGER_CHECK("l", c1_l), 1, 68, 2, 0) - 1)) - 1].re = c1_real;
          c1_data_out[(_SFD_EML_ARRAY_BOUNDS_CHECK("data_out", (int32_T)
            _SFD_INTEGER_CHECK("u", c1_u), 1, 1705, 1, 0) + 1705 *
                       (_SFD_EML_ARRAY_BOUNDS_CHECK("data_out", (int32_T)
            _SFD_INTEGER_CHECK("l", c1_l), 1, 68, 2, 0) - 1)) - 1].im = 0.0;
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 33);
          c1_tps++;
        } else {
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 35);
          c1_data_out[(_SFD_EML_ARRAY_BOUNDS_CHECK("data_out", (int32_T)
            _SFD_INTEGER_CHECK("u", c1_u), 1, 1705, 1, 0) + 1705 *
                       (_SFD_EML_ARRAY_BOUNDS_CHECK("data_out", (int32_T)
            _SFD_INTEGER_CHECK("l", c1_l), 1, 68, 2, 0) - 1)) - 1] =
            c1_data_in[_SFD_EML_ARRAY_BOUNDS_CHECK("data_in", (int32_T)
            _SFD_INTEGER_CHECK("v", c1_v), 1, 102816, 1, 0) - 1];
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 36);
          c1_v++;
        }
      }

      c1_b_u++;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 0);
    c1_b_l++;
    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  CV_EML_FOR(0, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -36);
  sf_debug_symbol_scope_pop();
  for (c1_i8 = 0; c1_i8 < 115940; c1_i8++) {
    (*c1_b_data_out)[c1_i8] = c1_data_out[c1_i8];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_temp7(SFc1_temp7InstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i9;
  int32_T c1_i10;
  int32_T c1_i11;
  static creal_T c1_b_inData[115940];
  int32_T c1_i12;
  int32_T c1_i13;
  int32_T c1_i14;
  static creal_T c1_u[115940];
  const mxArray *c1_y = NULL;
  SFc1_temp7InstanceStruct *chartInstance;
  chartInstance = (SFc1_temp7InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i9 = 0;
  for (c1_i10 = 0; c1_i10 < 68; c1_i10++) {
    for (c1_i11 = 0; c1_i11 < 1705; c1_i11++) {
      c1_b_inData[c1_i11 + c1_i9] = (*(creal_T (*)[115940])c1_inData)[c1_i11 +
        c1_i9];
    }

    c1_i9 += 1705;
  }

  c1_i12 = 0;
  for (c1_i13 = 0; c1_i13 < 68; c1_i13++) {
    for (c1_i14 = 0; c1_i14 < 1705; c1_i14++) {
      c1_u[c1_i14 + c1_i12] = c1_b_inData[c1_i14 + c1_i12];
    }

    c1_i12 += 1705;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 1U, 1U, 0U, 2, 1705, 68));
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static void c1_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_data_out, const char_T *c1_identifier, creal_T c1_y[115940])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_data_out), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_data_out);
}

static void c1_b_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, creal_T c1_y[115940])
{
  static creal_T c1_dcv1[115940];
  int32_T c1_i15;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dcv1, 1, 0, 1U, 1, 0U, 2, 1705,
                68);
  for (c1_i15 = 0; c1_i15 < 115940; c1_i15++) {
    c1_y[c1_i15] = c1_dcv1[c1_i15];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_data_out;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  static creal_T c1_y[115940];
  int32_T c1_i16;
  int32_T c1_i17;
  int32_T c1_i18;
  SFc1_temp7InstanceStruct *chartInstance;
  chartInstance = (SFc1_temp7InstanceStruct *)chartInstanceVoid;
  c1_data_out = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_data_out), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_data_out);
  c1_i16 = 0;
  for (c1_i17 = 0; c1_i17 < 68; c1_i17++) {
    for (c1_i18 = 0; c1_i18 < 1705; c1_i18++) {
      (*(creal_T (*)[115940])c1_outData)[c1_i18 + c1_i16] = c1_y[c1_i18 + c1_i16];
    }

    c1_i16 += 1705;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  static c1_struct_pff9OPVgTqbyCupd3ePNxF c1_u;
  const mxArray *c1_y = NULL;
  int32_T c1_i19;
  real_T c1_b_u[1705];
  const mxArray *c1_b_y = NULL;
  int32_T c1_i20;
  real_T c1_c_u[45];
  const mxArray *c1_c_y = NULL;
  int32_T c1_i21;
  real_T c1_d_u[17];
  const mxArray *c1_d_y = NULL;
  int32_T c1_i22;
  real_T c1_e_u[142];
  const mxArray *c1_e_y = NULL;
  int32_T c1_i23;
  real_T c1_f_u[11968];
  const mxArray *c1_f_y = NULL;
  int32_T c1_i24;
  real_T c1_g_u[2560];
  const mxArray *c1_g_y = NULL;
  int32_T c1_i25;
  real_T c1_h_u[2048];
  const mxArray *c1_h_y = NULL;
  SFc1_temp7InstanceStruct *chartInstance;
  chartInstance = (SFc1_temp7InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(c1_struct_pff9OPVgTqbyCupd3ePNxF *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createstruct("structure", 2, 1, 1));
  for (c1_i19 = 0; c1_i19 < 1705; c1_i19++) {
    c1_b_u[c1_i19] = c1_u.w[c1_i19];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 2, 1, 1705));
  sf_mex_addfield(c1_y, c1_b_y, "w", "w", 0);
  for (c1_i20 = 0; c1_i20 < 45; c1_i20++) {
    c1_c_u[c1_i20] = c1_u.continual_pilots[c1_i20];
  }

  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 2, 1, 45));
  sf_mex_addfield(c1_y, c1_c_y, "continual_pilots", "continual_pilots", 0);
  for (c1_i21 = 0; c1_i21 < 17; c1_i21++) {
    c1_d_u[c1_i21] = c1_u.tps_signals[c1_i21];
  }

  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_d_u, 0, 0U, 1U, 0U, 2, 1, 17));
  sf_mex_addfield(c1_y, c1_d_y, "tps_signals", "tps_signals", 0);
  for (c1_i22 = 0; c1_i22 < 142; c1_i22++) {
    c1_e_u[c1_i22] = c1_u.scattered_set[c1_i22];
  }

  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", c1_e_u, 0, 0U, 1U, 0U, 2, 1, 142));
  sf_mex_addfield(c1_y, c1_e_y, "scattered_set", "scattered_set", 0);
  for (c1_i23 = 0; c1_i23 < 11968; c1_i23++) {
    c1_f_u[c1_i23] = c1_u.pilot_set[c1_i23];
  }

  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", c1_f_u, 0, 0U, 1U, 0U, 2, 176, 68));
  sf_mex_addfield(c1_y, c1_f_y, "pilot_set", "pilot_set", 0);
  for (c1_i24 = 0; c1_i24 < 2560; c1_i24++) {
    c1_g_u[c1_i24] = c1_u.CyclicPrefixTX[c1_i24];
  }

  c1_g_y = NULL;
  sf_mex_assign(&c1_g_y, sf_mex_create("y", c1_g_u, 0, 0U, 1U, 0U, 2, 1, 2560));
  sf_mex_addfield(c1_y, c1_g_y, "CyclicPrefixTX", "CyclicPrefixTX", 0);
  for (c1_i25 = 0; c1_i25 < 2048; c1_i25++) {
    c1_h_u[c1_i25] = c1_u.CyclicPrefixRX[c1_i25];
  }

  c1_h_y = NULL;
  sf_mex_assign(&c1_h_y, sf_mex_create("y", c1_h_u, 0, 0U, 1U, 0U, 2, 1, 2048));
  sf_mex_addfield(c1_y, c1_h_y, "CyclicPrefixRX", "CyclicPrefixRX", 0);
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static void c1_c_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  c1_struct_pff9OPVgTqbyCupd3ePNxF *c1_y)
{
  emlrtMsgIdentifier c1_thisId;
  static const char * c1_fieldNames[7] = { "w", "continual_pilots",
    "tps_signals", "scattered_set", "pilot_set", "CyclicPrefixTX",
    "CyclicPrefixRX" };

  c1_thisId.fParent = c1_parentId;
  sf_mex_check_struct(c1_parentId, c1_u, 7, c1_fieldNames, 0U, 0);
  c1_thisId.fIdentifier = "w";
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u, "w", "w",
    0)), &c1_thisId, c1_y->w);
  c1_thisId.fIdentifier = "continual_pilots";
  c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u,
    "continual_pilots", "continual_pilots", 0)), &c1_thisId,
                        c1_y->continual_pilots);
  c1_thisId.fIdentifier = "tps_signals";
  c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u,
    "tps_signals", "tps_signals", 0)), &c1_thisId, c1_y->tps_signals);
  c1_thisId.fIdentifier = "scattered_set";
  c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u,
    "scattered_set", "scattered_set", 0)), &c1_thisId, c1_y->scattered_set);
  c1_thisId.fIdentifier = "pilot_set";
  c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u,
    "pilot_set", "pilot_set", 0)), &c1_thisId, c1_y->pilot_set);
  c1_thisId.fIdentifier = "CyclicPrefixTX";
  c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u,
    "CyclicPrefixTX", "CyclicPrefixTX", 0)), &c1_thisId, c1_y->CyclicPrefixTX);
  c1_thisId.fIdentifier = "CyclicPrefixRX";
  c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u,
    "CyclicPrefixRX", "CyclicPrefixRX", 0)), &c1_thisId, c1_y->CyclicPrefixRX);
  sf_mex_destroy(&c1_u);
}

static void c1_d_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[1705])
{
  real_T c1_dv0[1705];
  int32_T c1_i26;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv0, 1, 0, 0U, 1, 0U, 2, 1,
                1705);
  for (c1_i26 = 0; c1_i26 < 1705; c1_i26++) {
    c1_y[c1_i26] = c1_dv0[c1_i26];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_e_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[45])
{
  real_T c1_dv1[45];
  int32_T c1_i27;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv1, 1, 0, 0U, 1, 0U, 2, 1, 45);
  for (c1_i27 = 0; c1_i27 < 45; c1_i27++) {
    c1_y[c1_i27] = c1_dv1[c1_i27];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_f_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[17])
{
  real_T c1_dv2[17];
  int32_T c1_i28;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv2, 1, 0, 0U, 1, 0U, 2, 1, 17);
  for (c1_i28 = 0; c1_i28 < 17; c1_i28++) {
    c1_y[c1_i28] = c1_dv2[c1_i28];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_g_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[142])
{
  real_T c1_dv3[142];
  int32_T c1_i29;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv3, 1, 0, 0U, 1, 0U, 2, 1,
                142);
  for (c1_i29 = 0; c1_i29 < 142; c1_i29++) {
    c1_y[c1_i29] = c1_dv3[c1_i29];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_h_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[11968])
{
  real_T c1_dv4[11968];
  int32_T c1_i30;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv4, 1, 0, 0U, 1, 0U, 2, 176,
                68);
  for (c1_i30 = 0; c1_i30 < 11968; c1_i30++) {
    c1_y[c1_i30] = c1_dv4[c1_i30];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_i_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[2560])
{
  real_T c1_dv5[2560];
  int32_T c1_i31;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv5, 1, 0, 0U, 1, 0U, 2, 1,
                2560);
  for (c1_i31 = 0; c1_i31 < 2560; c1_i31++) {
    c1_y[c1_i31] = c1_dv5[c1_i31];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_j_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[2048])
{
  real_T c1_dv6[2048];
  int32_T c1_i32;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv6, 1, 0, 0U, 1, 0U, 2, 1,
                2048);
  for (c1_i32 = 0; c1_i32 < 2048; c1_i32++) {
    c1_y[c1_i32] = c1_dv6[c1_i32];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_VAR;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  static c1_struct_pff9OPVgTqbyCupd3ePNxF c1_y;
  SFc1_temp7InstanceStruct *chartInstance;
  chartInstance = (SFc1_temp7InstanceStruct *)chartInstanceVoid;
  c1_b_VAR = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_VAR), &c1_thisId, &c1_y);
  sf_mex_destroy(&c1_b_VAR);
  *(c1_struct_pff9OPVgTqbyCupd3ePNxF *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i33;
  int32_T c1_i34;
  int32_T c1_i35;
  static creal_T c1_b_inData[102816];
  int32_T c1_i36;
  int32_T c1_i37;
  int32_T c1_i38;
  static creal_T c1_u[102816];
  const mxArray *c1_y = NULL;
  SFc1_temp7InstanceStruct *chartInstance;
  chartInstance = (SFc1_temp7InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i33 = 0;
  for (c1_i34 = 0; c1_i34 < 68; c1_i34++) {
    for (c1_i35 = 0; c1_i35 < 1512; c1_i35++) {
      c1_b_inData[c1_i35 + c1_i33] = (*(creal_T (*)[102816])c1_inData)[c1_i35 +
        c1_i33];
    }

    c1_i33 += 1512;
  }

  c1_i36 = 0;
  for (c1_i37 = 0; c1_i37 < 68; c1_i37++) {
    for (c1_i38 = 0; c1_i38 < 1512; c1_i38++) {
      c1_u[c1_i38 + c1_i36] = c1_b_inData[c1_i38 + c1_i36];
    }

    c1_i36 += 1512;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 1U, 1U, 0U, 2, 1512, 68));
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_temp7InstanceStruct *chartInstance;
  chartInstance = (SFc1_temp7InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static real_T c1_k_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance,
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
  SFc1_temp7InstanceStruct *chartInstance;
  chartInstance = (SFc1_temp7InstanceStruct *)chartInstanceVoid;
  c1_nargout = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nargout), &c1_thisId);
  sf_mex_destroy(&c1_nargout);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i39;
  int32_T c1_i40;
  int32_T c1_i41;
  static real_T c1_b_inData[115940];
  int32_T c1_i42;
  int32_T c1_i43;
  int32_T c1_i44;
  static real_T c1_u[115940];
  const mxArray *c1_y = NULL;
  SFc1_temp7InstanceStruct *chartInstance;
  chartInstance = (SFc1_temp7InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i39 = 0;
  for (c1_i40 = 0; c1_i40 < 68; c1_i40++) {
    for (c1_i41 = 0; c1_i41 < 1705; c1_i41++) {
      c1_b_inData[c1_i41 + c1_i39] = (*(real_T (*)[115940])c1_inData)[c1_i41 +
        c1_i39];
    }

    c1_i39 += 1705;
  }

  c1_i42 = 0;
  for (c1_i43 = 0; c1_i43 < 68; c1_i43++) {
    for (c1_i44 = 0; c1_i44 < 1705; c1_i44++) {
      c1_u[c1_i44 + c1_i42] = c1_b_inData[c1_i44 + c1_i42];
    }

    c1_i42 += 1705;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 1705, 68));
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static void c1_l_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[115940])
{
  static real_T c1_dv7[115940];
  int32_T c1_i45;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv7, 1, 0, 0U, 1, 0U, 2, 1705,
                68);
  for (c1_i45 = 0; c1_i45 < 115940; c1_i45++) {
    c1_y[c1_i45] = c1_dv7[c1_i45];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_temp;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  static real_T c1_y[115940];
  int32_T c1_i46;
  int32_T c1_i47;
  int32_T c1_i48;
  SFc1_temp7InstanceStruct *chartInstance;
  chartInstance = (SFc1_temp7InstanceStruct *)chartInstanceVoid;
  c1_temp = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_temp), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_temp);
  c1_i46 = 0;
  for (c1_i47 = 0; c1_i47 < 68; c1_i47++) {
    for (c1_i48 = 0; c1_i48 < 1705; c1_i48++) {
      (*(real_T (*)[115940])c1_outData)[c1_i48 + c1_i46] = c1_y[c1_i48 + c1_i46];
    }

    c1_i46 += 1705;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i49;
  int32_T c1_i50;
  int32_T c1_i51;
  real_T c1_b_inData[11968];
  int32_T c1_i52;
  int32_T c1_i53;
  int32_T c1_i54;
  real_T c1_u[11968];
  const mxArray *c1_y = NULL;
  SFc1_temp7InstanceStruct *chartInstance;
  chartInstance = (SFc1_temp7InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i49 = 0;
  for (c1_i50 = 0; c1_i50 < 68; c1_i50++) {
    for (c1_i51 = 0; c1_i51 < 176; c1_i51++) {
      c1_b_inData[c1_i51 + c1_i49] = (*(real_T (*)[11968])c1_inData)[c1_i51 +
        c1_i49];
    }

    c1_i49 += 176;
  }

  c1_i52 = 0;
  for (c1_i53 = 0; c1_i53 < 68; c1_i53++) {
    for (c1_i54 = 0; c1_i54 < 176; c1_i54++) {
      c1_u[c1_i54 + c1_i52] = c1_b_inData[c1_i54 + c1_i52];
    }

    c1_i52 += 176;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 176, 68));
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_pilot_set;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[11968];
  int32_T c1_i55;
  int32_T c1_i56;
  int32_T c1_i57;
  SFc1_temp7InstanceStruct *chartInstance;
  chartInstance = (SFc1_temp7InstanceStruct *)chartInstanceVoid;
  c1_pilot_set = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_pilot_set), &c1_thisId,
                        c1_y);
  sf_mex_destroy(&c1_pilot_set);
  c1_i55 = 0;
  for (c1_i56 = 0; c1_i56 < 68; c1_i56++) {
    for (c1_i57 = 0; c1_i57 < 176; c1_i57++) {
      (*(real_T (*)[11968])c1_outData)[c1_i57 + c1_i55] = c1_y[c1_i57 + c1_i55];
    }

    c1_i55 += 176;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i58;
  real_T c1_b_inData[17];
  int32_T c1_i59;
  real_T c1_u[17];
  const mxArray *c1_y = NULL;
  SFc1_temp7InstanceStruct *chartInstance;
  chartInstance = (SFc1_temp7InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i58 = 0; c1_i58 < 17; c1_i58++) {
    c1_b_inData[c1_i58] = (*(real_T (*)[17])c1_inData)[c1_i58];
  }

  for (c1_i59 = 0; c1_i59 < 17; c1_i59++) {
    c1_u[c1_i59] = c1_b_inData[c1_i59];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 1, 17));
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_tps_set;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[17];
  int32_T c1_i60;
  SFc1_temp7InstanceStruct *chartInstance;
  chartInstance = (SFc1_temp7InstanceStruct *)chartInstanceVoid;
  c1_tps_set = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_tps_set), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_tps_set);
  for (c1_i60 = 0; c1_i60 < 17; c1_i60++) {
    (*(real_T (*)[17])c1_outData)[c1_i60] = c1_y[c1_i60];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i61;
  real_T c1_b_inData[1705];
  int32_T c1_i62;
  real_T c1_u[1705];
  const mxArray *c1_y = NULL;
  SFc1_temp7InstanceStruct *chartInstance;
  chartInstance = (SFc1_temp7InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i61 = 0; c1_i61 < 1705; c1_i61++) {
    c1_b_inData[c1_i61] = (*(real_T (*)[1705])c1_inData)[c1_i61];
  }

  for (c1_i62 = 0; c1_i62 < 1705; c1_i62++) {
    c1_u[c1_i62] = c1_b_inData[c1_i62];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 1, 1705));
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_w;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[1705];
  int32_T c1_i63;
  SFc1_temp7InstanceStruct *chartInstance;
  chartInstance = (SFc1_temp7InstanceStruct *)chartInstanceVoid;
  c1_w = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_w), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_w);
  for (c1_i63 = 0; c1_i63 < 1705; c1_i63++) {
    (*(real_T (*)[1705])c1_outData)[c1_i63] = c1_y[c1_i63];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_temp7_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo;
  c1_ResolvedFunctionInfo c1_info[5];
  c1_ResolvedFunctionInfo (*c1_b_info)[5];
  const mxArray *c1_m1 = NULL;
  int32_T c1_i64;
  c1_ResolvedFunctionInfo *c1_r1;
  c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  c1_b_info = (c1_ResolvedFunctionInfo (*)[5])c1_info;
  (*c1_b_info)[0].context = "";
  (*c1_b_info)[0].name = "length";
  (*c1_b_info)[0].dominantType = "double";
  (*c1_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  (*c1_b_info)[0].fileTimeLo = 1286815160U;
  (*c1_b_info)[0].fileTimeHi = 0U;
  (*c1_b_info)[0].mFileTimeLo = 0U;
  (*c1_b_info)[0].mFileTimeHi = 0U;
  (*c1_b_info)[1].context = "";
  (*c1_b_info)[1].name = "mrdivide";
  (*c1_b_info)[1].dominantType = "double";
  (*c1_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c1_b_info)[1].fileTimeLo = 1296661054U;
  (*c1_b_info)[1].fileTimeHi = 0U;
  (*c1_b_info)[1].mFileTimeLo = 1289516092U;
  (*c1_b_info)[1].mFileTimeHi = 0U;
  (*c1_b_info)[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c1_b_info)[2].name = "rdivide";
  (*c1_b_info)[2].dominantType = "double";
  (*c1_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c1_b_info)[2].fileTimeLo = 1286815244U;
  (*c1_b_info)[2].fileTimeHi = 0U;
  (*c1_b_info)[2].mFileTimeLo = 0U;
  (*c1_b_info)[2].mFileTimeHi = 0U;
  (*c1_b_info)[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c1_b_info)[3].name = "eml_div";
  (*c1_b_info)[3].dominantType = "double";
  (*c1_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  (*c1_b_info)[3].fileTimeLo = 1286815098U;
  (*c1_b_info)[3].fileTimeHi = 0U;
  (*c1_b_info)[3].mFileTimeLo = 0U;
  (*c1_b_info)[3].mFileTimeHi = 0U;
  (*c1_b_info)[4].context = "";
  (*c1_b_info)[4].name = "mtimes";
  (*c1_b_info)[4].dominantType = "double";
  (*c1_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c1_b_info)[4].fileTimeLo = 1289516092U;
  (*c1_b_info)[4].fileTimeHi = 0U;
  (*c1_b_info)[4].mFileTimeLo = 0U;
  (*c1_b_info)[4].mFileTimeHi = 0U;
  sf_mex_assign(&c1_m1, sf_mex_createstruct("nameCaptureInfo", 1, 5));
  for (c1_i64 = 0; c1_i64 < 5; c1_i64++) {
    c1_r1 = &c1_info[c1_i64];
    sf_mex_addfield(c1_m1, sf_mex_create("nameCaptureInfo", c1_r1->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r1->context)), "context", "nameCaptureInfo",
                    c1_i64);
    sf_mex_addfield(c1_m1, sf_mex_create("nameCaptureInfo", c1_r1->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c1_r1->name)), "name", "nameCaptureInfo", c1_i64);
    sf_mex_addfield(c1_m1, sf_mex_create("nameCaptureInfo", c1_r1->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c1_r1->dominantType)), "dominantType",
                    "nameCaptureInfo", c1_i64);
    sf_mex_addfield(c1_m1, sf_mex_create("nameCaptureInfo", c1_r1->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r1->resolved)), "resolved", "nameCaptureInfo",
                    c1_i64);
    sf_mex_addfield(c1_m1, sf_mex_create("nameCaptureInfo", &c1_r1->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c1_i64);
    sf_mex_addfield(c1_m1, sf_mex_create("nameCaptureInfo", &c1_r1->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c1_i64);
    sf_mex_addfield(c1_m1, sf_mex_create("nameCaptureInfo", &c1_r1->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c1_i64);
    sf_mex_addfield(c1_m1, sf_mex_create("nameCaptureInfo", &c1_r1->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c1_i64);
  }

  sf_mex_assign(&c1_nameCaptureInfo, c1_m1);
  return c1_nameCaptureInfo;
}

static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_temp7InstanceStruct *chartInstance;
  chartInstance = (SFc1_temp7InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0));
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static int32_T c1_m_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i65;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i65, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i65;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_temp7InstanceStruct *chartInstance;
  chartInstance = (SFc1_temp7InstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_n_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_temp7, const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_is_active_c1_temp7),
    &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_temp7);
  return c1_y;
}

static uint8_T c1_o_emlrt_marshallIn(SFc1_temp7InstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_temp7InstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c1_temp7_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2646170353U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2399007460U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(779148408U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(232381735U);
}

mxArray *sf_c1_temp7_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(787598067U);
    pr[1] = (double)(4115039025U);
    pr[2] = (double)(1800738645U);
    pr[3] = (double)(692899074U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1512);
      pr[1] = (double)(68);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(1));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1705);
      pr[1] = (double)(68);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(1));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c1_temp7(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"data_out\",},{M[8],M[0],T\"is_active_c1_temp7\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_temp7_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_temp7InstanceStruct *chartInstance;
    chartInstance = (SFc1_temp7InstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart(_temp7MachineNumber_,
          1,
          1,
          1,
          3,
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
          init_script_number_translation(_temp7MachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting(_temp7MachineNumber_,
            chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_temp7MachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"data_in");
          _SFD_SET_DATA_PROPS(1,2,0,1,"data_out");
          _SFD_SET_DATA_PROPS(2,10,0,0,"VAR");
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
        _SFD_CV_INIT_EML(0,1,3,0,0,2,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1227);
        _SFD_CV_INIT_EML_IF(0,0,540,565,630,673);
        _SFD_CV_INIT_EML_IF(0,1,687,696,860,1188);
        _SFD_CV_INIT_EML_IF(0,2,860,873,1072,1188);
        _SFD_CV_INIT_EML_FOR(0,0,260,276,1206);
        _SFD_CV_INIT_EML_FOR(0,1,425,449,1200);
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
          dimVector[0]= 1512;
          dimVector[1]= 68;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,1,(MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1705;
          dimVector[1]= 68;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,1,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)
            c1_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);

        {
          creal_T (*c1_data_in)[102816];
          creal_T (*c1_data_out)[115940];
          c1_data_out = (creal_T (*)[115940])ssGetOutputPortSignal
            (chartInstance->S, 1);
          c1_data_in = (creal_T (*)[102816])ssGetInputPortSignal
            (chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c1_data_in);
          _SFD_SET_DATA_VALUE_PTR(1U, *c1_data_out);
          _SFD_SET_DATA_VALUE_PTR(2U, &chartInstance->c1_VAR);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_temp7MachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c1_temp7(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_temp7InstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c1_temp7((SFc1_temp7InstanceStruct*) chartInstanceVar);
  initialize_c1_temp7((SFc1_temp7InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_temp7(void *chartInstanceVar)
{
  enable_c1_temp7((SFc1_temp7InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_temp7(void *chartInstanceVar)
{
  disable_c1_temp7((SFc1_temp7InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_temp7(void *chartInstanceVar)
{
  sf_c1_temp7((SFc1_temp7InstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_temp7(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_temp7((SFc1_temp7InstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_temp7();/* state var info */
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

extern void sf_internal_set_sim_state_c1_temp7(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_temp7();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_temp7((SFc1_temp7InstanceStruct*)chartInfo->chartInstance,
    mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_temp7(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_temp7(S);
}

static void sf_opaque_set_sim_state_c1_temp7(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c1_temp7(S, st);
}

static void sf_opaque_terminate_c1_temp7(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_temp7InstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c1_temp7((SFc1_temp7InstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_temp7((SFc1_temp7InstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_temp7(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_temp7((SFc1_temp7InstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_temp7(SimStruct *S)
{
  /* Actual parameters from chart:
     VAR
   */
  const char_T *rtParamNames[] = { "p1" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0],
    sf_get_param_data_type_id(S,0));
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"temp7","temp7",1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"temp7","temp7",1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"temp7","temp7",1,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"temp7","temp7",1,1);
      sf_mark_chart_reusable_outputs(S,"temp7","temp7",1,1);
    }

    sf_set_rtw_dwork_info(S,"temp7","temp7",1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1513683468U));
  ssSetChecksum1(S,(3758813973U));
  ssSetChecksum2(S,(1429419837U));
  ssSetChecksum3(S,(3371489117U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c1_temp7(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "temp7", "temp7",1);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_temp7(SimStruct *S)
{
  SFc1_temp7InstanceStruct *chartInstance;
  chartInstance = (SFc1_temp7InstanceStruct *)malloc(sizeof
    (SFc1_temp7InstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_temp7InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_temp7;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_temp7;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_temp7;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_temp7;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_temp7;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_temp7;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_temp7;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_temp7;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_temp7;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_temp7;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_temp7;
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

void c1_temp7_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_temp7(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_temp7(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_temp7(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_temp7_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
