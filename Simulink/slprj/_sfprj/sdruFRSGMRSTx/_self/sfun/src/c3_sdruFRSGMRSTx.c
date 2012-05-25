/* Include files */

#include "blascompat32.h"
#include "sdruFRSGMRSTx_sfun.h"
#include "c3_sdruFRSGMRSTx.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "sdruFRSGMRSTx_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char * c3_debug_family_names[4] = { "nargin", "nargout", "channel",
  "fc" };

static const char * c3_b_debug_family_names[4] = { "channel", "nargin",
  "nargout", "fc" };

/* Function Declarations */
static void initialize_c3_sdruFRSGMRSTx(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance);
static void initialize_params_c3_sdruFRSGMRSTx(SFc3_sdruFRSGMRSTxInstanceStruct *
  chartInstance);
static void enable_c3_sdruFRSGMRSTx(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance);
static void disable_c3_sdruFRSGMRSTx(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance);
static void c3_update_debugger_state_c3_sdruFRSGMRSTx
  (SFc3_sdruFRSGMRSTxInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c3_sdruFRSGMRSTx
  (SFc3_sdruFRSGMRSTxInstanceStruct *chartInstance);
static void set_sim_state_c3_sdruFRSGMRSTx(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c3_st);
static void finalize_c3_sdruFRSGMRSTx(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance);
static void sf_c3_sdruFRSGMRSTx(SFc3_sdruFRSGMRSTxInstanceStruct *chartInstance);
static void initSimStructsc3_sdruFRSGMRSTx(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData);
static real_T c3_emlrt_marshallIn(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c3_fc, const char_T *c3_identifier);
static real_T c3_b_emlrt_marshallIn(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static uint8_T c3_c_emlrt_marshallIn(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c3_channel, const char_T *c3_identifier);
static uint8_T c3_d_emlrt_marshallIn(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_e_emlrt_marshallIn(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void init_dsm_address_info(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c3_sdruFRSGMRSTx(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance)
{
  chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c3_is_active_c3_sdruFRSGMRSTx = 0U;
}

static void initialize_params_c3_sdruFRSGMRSTx(SFc3_sdruFRSGMRSTxInstanceStruct *
  chartInstance)
{
}

static void enable_c3_sdruFRSGMRSTx(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c3_sdruFRSGMRSTx(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c3_update_debugger_state_c3_sdruFRSGMRSTx
  (SFc3_sdruFRSGMRSTxInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c3_sdruFRSGMRSTx
  (SFc3_sdruFRSGMRSTxInstanceStruct *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  real_T c3_hoistedGlobal;
  real_T c3_u;
  const mxArray *c3_b_y = NULL;
  uint8_T c3_b_hoistedGlobal;
  uint8_T c3_b_u;
  const mxArray *c3_c_y = NULL;
  real_T *c3_fc;
  c3_fc = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellarray(2));
  c3_hoistedGlobal = *c3_fc;
  c3_u = c3_hoistedGlobal;
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 0, c3_b_y);
  c3_b_hoistedGlobal = chartInstance->c3_is_active_c3_sdruFRSGMRSTx;
  c3_b_u = c3_b_hoistedGlobal;
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", &c3_b_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 1, c3_c_y);
  sf_mex_assign(&c3_st, c3_y);
  return c3_st;
}

static void set_sim_state_c3_sdruFRSGMRSTx(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c3_st)
{
  const mxArray *c3_u;
  real_T *c3_fc;
  c3_fc = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c3_doneDoubleBufferReInit = TRUE;
  c3_u = sf_mex_dup(c3_st);
  *c3_fc = c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 0)),
    "fc");
  chartInstance->c3_is_active_c3_sdruFRSGMRSTx = c3_c_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 1)),
     "is_active_c3_sdruFRSGMRSTx");
  sf_mex_destroy(&c3_u);
  c3_update_debugger_state_c3_sdruFRSGMRSTx(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_sdruFRSGMRSTx(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance)
{
}

static void sf_c3_sdruFRSGMRSTx(SFc3_sdruFRSGMRSTxInstanceStruct *chartInstance)
{
  uint8_T c3_hoistedGlobal;
  uint8_T c3_channel;
  uint32_T c3_debug_family_var_map[4];
  real_T c3_nargin = 1.0;
  real_T c3_nargout = 1.0;
  real_T c3_fc;
  uint8_T c3_b_channel;
  real_T c3_c_channel;
  real_T c3_b_nargin = 1.0;
  real_T c3_b_nargout = 1.0;
  real_T c3_b;
  real_T c3_y;
  real_T c3_b_b;
  real_T c3_b_y;
  uint8_T *c3_d_channel;
  real_T *c3_b_fc;
  c3_b_fc = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c3_d_channel = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c3_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*c3_d_channel, 0U);
  _SFD_DATA_RANGE_CHECK(*c3_b_fc, 1U);
  chartInstance->c3_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c3_sfEvent);
  c3_hoistedGlobal = *c3_d_channel;
  c3_channel = c3_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c3_debug_family_names,
    c3_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c3_nargin, 0U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_nargout, 1U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c3_channel, 2U, c3_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c3_fc, 3U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 5);
  c3_b_channel = c3_channel;
  sf_debug_symbol_scope_push_eml(0U, 4U, 5U, c3_b_debug_family_names,
    c3_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c3_c_channel, MAX_uint32_T,
    c3_sf_marshallOut, c3_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_b_nargin, 1U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_b_nargout, 2U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_b_channel, 0U,
    c3_b_sf_marshallOut, c3_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_fc, 3U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 25);
  c3_c_channel = (real_T)c3_b_channel;
  sf_debug_symbol_switch(0U, 0U);
  _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 26);
  if (CV_SCRIPT_IF(0, 0, c3_c_channel <= 7.0)) {
    _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 27);
    c3_b = c3_c_channel - 1.0;
    c3_y = 25000.0 * c3_b;
    c3_fc = 4.625625E+8 + c3_y;
  } else {
    _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 28);
    if (CV_SCRIPT_IF(0, 1, c3_c_channel <= 14.0)) {
      _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 29);
      c3_b_b = c3_c_channel - 8.0;
      c3_b_y = 25000.0 * c3_b_b;
      c3_fc = 4.675625E+8 + c3_b_y;
    } else {
      _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 31);
      c3_fc = 4.625625E+8;
    }
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, -31);
  sf_debug_symbol_scope_pop();
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, -5);
  sf_debug_symbol_scope_pop();
  *c3_b_fc = c3_fc;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c3_sfEvent);
  sf_debug_check_for_state_inconsistency(_sdruFRSGMRSTxMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc3_sdruFRSGMRSTx(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber)
{
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, 0U, sf_debug_get_script_id(
    "/home/katsikas/commusrp/usrpdemos/convertChan2FreqFRSGMRSDemo.m"));
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc3_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c3_mxArrayOutData, c3_y);
  return c3_mxArrayOutData;
}

static real_T c3_emlrt_marshallIn(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c3_fc, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_fc), &c3_thisId);
  sf_mex_destroy(&c3_fc);
  return c3_y;
}

static real_T c3_b_emlrt_marshallIn(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d0;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d0, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_fc;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc3_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c3_fc = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_fc), &c3_thisId);
  sf_mex_destroy(&c3_fc);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  uint8_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc3_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(uint8_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 3, 0U, 0U, 0U, 0));
  sf_mex_assign(&c3_mxArrayOutData, c3_y);
  return c3_mxArrayOutData;
}

static uint8_T c3_c_emlrt_marshallIn(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c3_channel, const char_T *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_channel), &c3_thisId);
  sf_mex_destroy(&c3_channel);
  return c3_y;
}

static uint8_T c3_d_emlrt_marshallIn(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_channel;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  uint8_T c3_y;
  SFc3_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc3_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c3_channel = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_channel), &c3_thisId);
  sf_mex_destroy(&c3_channel);
  *(uint8_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

const mxArray *sf_c3_sdruFRSGMRSTx_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo;
  c3_ResolvedFunctionInfo c3_info[1];
  c3_ResolvedFunctionInfo (*c3_b_info)[1];
  const mxArray *c3_m0 = NULL;
  int32_T c3_i0;
  c3_ResolvedFunctionInfo *c3_r0;
  c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  c3_b_info = (c3_ResolvedFunctionInfo (*)[1])c3_info;
  (*c3_b_info)[0].context = "";
  (*c3_b_info)[0].name = "convertChan2FreqFRSGMRSDemo";
  (*c3_b_info)[0].dominantType = "uint8";
  (*c3_b_info)[0].resolved =
    "[E]/home/katsikas/commusrp/usrpdemos/convertChan2FreqFRSGMRSDemo.m";
  (*c3_b_info)[0].fileTimeLo = 1308924742U;
  (*c3_b_info)[0].fileTimeHi = 0U;
  (*c3_b_info)[0].mFileTimeLo = 0U;
  (*c3_b_info)[0].mFileTimeHi = 0U;
  sf_mex_assign(&c3_m0, sf_mex_createstruct("nameCaptureInfo", 1, 1));
  for (c3_i0 = 0; c3_i0 < 1; c3_i0++) {
    c3_r0 = &c3_info[c3_i0];
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r0->context)), "context", "nameCaptureInfo",
                    c3_i0);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c3_r0->name)), "name", "nameCaptureInfo", c3_i0);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c3_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c3_i0);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r0->resolved)), "resolved", "nameCaptureInfo",
                    c3_i0);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c3_i0);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c3_i0);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c3_i0);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c3_i0);
  }

  sf_mex_assign(&c3_nameCaptureInfo, c3_m0);
  return c3_nameCaptureInfo;
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc3_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(int32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 6, 0U, 0U, 0U, 0));
  sf_mex_assign(&c3_mxArrayOutData, c3_y);
  return c3_mxArrayOutData;
}

static int32_T c3_e_emlrt_marshallIn(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_y;
  int32_T c3_i1;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_i1, 1, 6, 0U, 0, 0U, 0);
  c3_y = c3_i1;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sfEvent;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_y;
  SFc3_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc3_sdruFRSGMRSTxInstanceStruct *)chartInstanceVoid;
  c3_b_sfEvent = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sfEvent),
    &c3_thisId);
  sf_mex_destroy(&c3_b_sfEvent);
  *(int32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static void init_dsm_address_info(SFc3_sdruFRSGMRSTxInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c3_sdruFRSGMRSTx_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1704303603U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3065041085U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4189227142U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3473381988U);
}

mxArray *sf_c3_sdruFRSGMRSTx_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(3922616301U);
    pr[1] = (double)(2387326630U);
    pr[2] = (double)(952980525U);
    pr[3] = (double)(915085616U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c3_sdruFRSGMRSTx(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"fc\",},{M[8],M[0],T\"is_active_c3_sdruFRSGMRSTx\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_sdruFRSGMRSTx_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_sdruFRSGMRSTxInstanceStruct *chartInstance;
    chartInstance = (SFc3_sdruFRSGMRSTxInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_sdruFRSGMRSTxMachineNumber_,
           3,
           1,
           1,
           2,
           0,
           0,
           0,
           0,
           1,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"channel");
          _SFD_SET_DATA_PROPS(1,2,0,1,"fc");
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
        _SFD_CV_INIT_EML(0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,147);
        _SFD_CV_INIT_SCRIPT(0,1,2,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"convertChan2FreqFRSGMRSDemo",0,-1,871);
        _SFD_CV_INIT_SCRIPT_IF(0,0,701,716,769,870);
        _SFD_CV_INIT_SCRIPT_IF(0,1,769,789,842,870);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);

        {
          uint8_T *c3_channel;
          real_T *c3_fc;
          c3_fc = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c3_channel = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c3_channel);
          _SFD_SET_DATA_VALUE_PTR(1U, c3_fc);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_sdruFRSGMRSTxMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c3_sdruFRSGMRSTx(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_sdruFRSGMRSTxInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c3_sdruFRSGMRSTx((SFc3_sdruFRSGMRSTxInstanceStruct*)
    chartInstanceVar);
  initialize_c3_sdruFRSGMRSTx((SFc3_sdruFRSGMRSTxInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c3_sdruFRSGMRSTx(void *chartInstanceVar)
{
  enable_c3_sdruFRSGMRSTx((SFc3_sdruFRSGMRSTxInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_sdruFRSGMRSTx(void *chartInstanceVar)
{
  disable_c3_sdruFRSGMRSTx((SFc3_sdruFRSGMRSTxInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_sdruFRSGMRSTx(void *chartInstanceVar)
{
  sf_c3_sdruFRSGMRSTx((SFc3_sdruFRSGMRSTxInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c3_sdruFRSGMRSTx(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_sdruFRSGMRSTx
    ((SFc3_sdruFRSGMRSTxInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_sdruFRSGMRSTx();/* state var info */
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

extern void sf_internal_set_sim_state_c3_sdruFRSGMRSTx(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_sdruFRSGMRSTx();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_sdruFRSGMRSTx((SFc3_sdruFRSGMRSTxInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c3_sdruFRSGMRSTx(SimStruct* S)
{
  return sf_internal_get_sim_state_c3_sdruFRSGMRSTx(S);
}

static void sf_opaque_set_sim_state_c3_sdruFRSGMRSTx(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c3_sdruFRSGMRSTx(S, st);
}

static void sf_opaque_terminate_c3_sdruFRSGMRSTx(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_sdruFRSGMRSTxInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c3_sdruFRSGMRSTx((SFc3_sdruFRSGMRSTxInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_sdruFRSGMRSTx((SFc3_sdruFRSGMRSTxInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_sdruFRSGMRSTx(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_sdruFRSGMRSTx((SFc3_sdruFRSGMRSTxInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_sdruFRSGMRSTx(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"sdruFRSGMRSTx","sdruFRSGMRSTx",3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"sdruFRSGMRSTx","sdruFRSGMRSTx",3,
                "RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"sdruFRSGMRSTx",
      "sdruFRSGMRSTx",3,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"sdruFRSGMRSTx","sdruFRSGMRSTx",3,1);
      sf_mark_chart_reusable_outputs(S,"sdruFRSGMRSTx","sdruFRSGMRSTx",3,1);
    }

    sf_set_rtw_dwork_info(S,"sdruFRSGMRSTx","sdruFRSGMRSTx",3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(397222624U));
  ssSetChecksum1(S,(1592744220U));
  ssSetChecksum2(S,(61639677U));
  ssSetChecksum3(S,(1503560318U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c3_sdruFRSGMRSTx(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "sdruFRSGMRSTx", "sdruFRSGMRSTx",3);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_sdruFRSGMRSTx(SimStruct *S)
{
  SFc3_sdruFRSGMRSTxInstanceStruct *chartInstance;
  chartInstance = (SFc3_sdruFRSGMRSTxInstanceStruct *)malloc(sizeof
    (SFc3_sdruFRSGMRSTxInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_sdruFRSGMRSTxInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_sdruFRSGMRSTx;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c3_sdruFRSGMRSTx;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_sdruFRSGMRSTx;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_sdruFRSGMRSTx;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_sdruFRSGMRSTx;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c3_sdruFRSGMRSTx;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c3_sdruFRSGMRSTx;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c3_sdruFRSGMRSTx;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_sdruFRSGMRSTx;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_sdruFRSGMRSTx;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_sdruFRSGMRSTx;
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

void c3_sdruFRSGMRSTx_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_sdruFRSGMRSTx(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_sdruFRSGMRSTx(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_sdruFRSGMRSTx(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_sdruFRSGMRSTx_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
