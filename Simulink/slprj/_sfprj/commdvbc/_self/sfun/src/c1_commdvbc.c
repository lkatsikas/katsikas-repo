/* Include files */

#include "blascompat32.h"
#include "commdvbc_sfun.h"
#include "c1_commdvbc.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "commdvbc_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[4] = { "nargin", "nargout", "u", "y" };

/* Function Declarations */
static void initialize_c1_commdvbc(SFc1_commdvbcInstanceStruct *chartInstance);
static void initialize_params_c1_commdvbc(SFc1_commdvbcInstanceStruct
  *chartInstance);
static void enable_c1_commdvbc(SFc1_commdvbcInstanceStruct *chartInstance);
static void disable_c1_commdvbc(SFc1_commdvbcInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_commdvbc(SFc1_commdvbcInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_commdvbc(SFc1_commdvbcInstanceStruct
  *chartInstance);
static void set_sim_state_c1_commdvbc(SFc1_commdvbcInstanceStruct *chartInstance,
  const mxArray *c1_st);
static void finalize_c1_commdvbc(SFc1_commdvbcInstanceStruct *chartInstance);
static void sf_c1_commdvbc(SFc1_commdvbcInstanceStruct *chartInstance);
static void initSimStructsc1_commdvbc(SFc1_commdvbcInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static void c1_emlrt_marshallIn(SFc1_commdvbcInstanceStruct *chartInstance,
  const mxArray *c1_y, const char_T *c1_identifier, uint8_T c1_b_y[272]);
static void c1_b_emlrt_marshallIn(SFc1_commdvbcInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint8_T c1_y[272]);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_c_emlrt_marshallIn(SFc1_commdvbcInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_convertBytesToMTuplesDVBCDemo(SFc1_commdvbcInstanceStruct
  *chartInstance, uint8_T c1_u[204], uint8_T c1_y[272]);
static void c1_realmax(SFc1_commdvbcInstanceStruct *chartInstance);
static void c1_rem(SFc1_commdvbcInstanceStruct *chartInstance, real_T c1_x[1632],
                   real_T c1_y, real_T c1_r[1632]);
static void c1_floor(SFc1_commdvbcInstanceStruct *chartInstance, real_T c1_x
                     [1632], real_T c1_b_x[1632]);
static void c1_eml_int_forloop_overflow_check(SFc1_commdvbcInstanceStruct
  *chartInstance);
static void c1_eml_scalar_eg(SFc1_commdvbcInstanceStruct *chartInstance);
static void c1_b_eml_int_forloop_overflow_check(SFc1_commdvbcInstanceStruct
  *chartInstance);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_d_emlrt_marshallIn(SFc1_commdvbcInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_e_emlrt_marshallIn(SFc1_commdvbcInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_commdvbc, const char_T *c1_identifier);
static uint8_T c1_f_emlrt_marshallIn(SFc1_commdvbcInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_floor(SFc1_commdvbcInstanceStruct *chartInstance, real_T c1_x
  [1632]);
static void init_dsm_address_info(SFc1_commdvbcInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_commdvbc(SFc1_commdvbcInstanceStruct *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_is_active_c1_commdvbc = 0U;
}

static void initialize_params_c1_commdvbc(SFc1_commdvbcInstanceStruct
  *chartInstance)
{
}

static void enable_c1_commdvbc(SFc1_commdvbcInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_commdvbc(SFc1_commdvbcInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_commdvbc(SFc1_commdvbcInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c1_commdvbc(SFc1_commdvbcInstanceStruct
  *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  int32_T c1_i0;
  uint8_T c1_u[272];
  const mxArray *c1_b_y = NULL;
  uint8_T c1_hoistedGlobal;
  uint8_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  uint8_T (*c1_d_y)[272];
  c1_d_y = (uint8_T (*)[272])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(2), FALSE);
  for (c1_i0 = 0; c1_i0 < 272; c1_i0++) {
    c1_u[c1_i0] = (*c1_d_y)[c1_i0];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u, 3, 0U, 1U, 0U, 1, 272), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_hoistedGlobal = chartInstance->c1_is_active_c1_commdvbc;
  c1_b_u = c1_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_commdvbc(SFc1_commdvbcInstanceStruct *chartInstance,
  const mxArray *c1_st)
{
  const mxArray *c1_u;
  uint8_T c1_uv0[272];
  int32_T c1_i1;
  uint8_T (*c1_y)[272];
  c1_y = (uint8_T (*)[272])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)), "y",
                      c1_uv0);
  for (c1_i1 = 0; c1_i1 < 272; c1_i1++) {
    (*c1_y)[c1_i1] = c1_uv0[c1_i1];
  }

  chartInstance->c1_is_active_c1_commdvbc = c1_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 1)), "is_active_c1_commdvbc");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_commdvbc(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_commdvbc(SFc1_commdvbcInstanceStruct *chartInstance)
{
}

static void sf_c1_commdvbc(SFc1_commdvbcInstanceStruct *chartInstance)
{
  int32_T c1_i2;
  int32_T c1_i3;
  int32_T c1_i4;
  uint8_T c1_u[204];
  uint32_T c1_debug_family_var_map[4];
  real_T c1_nargin = 1.0;
  real_T c1_nargout = 1.0;
  uint8_T c1_y[272];
  int32_T c1_i5;
  uint8_T c1_b_u[204];
  uint8_T c1_uv1[272];
  int32_T c1_i6;
  int32_T c1_i7;
  uint8_T (*c1_b_y)[272];
  uint8_T (*c1_c_u)[204];
  c1_b_y = (uint8_T (*)[272])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_c_u = (uint8_T (*)[204])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i2 = 0; c1_i2 < 204; c1_i2++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c1_c_u)[c1_i2], 0U);
  }

  for (c1_i3 = 0; c1_i3 < 272; c1_i3++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c1_b_y)[c1_i3], 1U);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i4 = 0; c1_i4 < 204; c1_i4++) {
    c1_u[c1_i4] = (*c1_c_u)[c1_i4];
  }

  sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c1_debug_family_names,
    c1_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargin, 0U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargout, 1U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c1_u, 2U, c1_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c1_y, 3U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 2);
  for (c1_i5 = 0; c1_i5 < 204; c1_i5++) {
    c1_b_u[c1_i5] = c1_u[c1_i5];
  }

  c1_convertBytesToMTuplesDVBCDemo(chartInstance, c1_b_u, c1_uv1);
  for (c1_i6 = 0; c1_i6 < 272; c1_i6++) {
    c1_y[c1_i6] = c1_uv1[c1_i6];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -2);
  sf_debug_symbol_scope_pop();
  for (c1_i7 = 0; c1_i7 < 272; c1_i7++) {
    (*c1_b_y)[c1_i7] = c1_y[c1_i7];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  sf_debug_check_for_state_inconsistency(_commdvbcMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc1_commdvbc(SFc1_commdvbcInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i8;
  uint8_T c1_b_inData[272];
  int32_T c1_i9;
  uint8_T c1_u[272];
  const mxArray *c1_y = NULL;
  SFc1_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc1_commdvbcInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i8 = 0; c1_i8 < 272; c1_i8++) {
    c1_b_inData[c1_i8] = (*(uint8_T (*)[272])c1_inData)[c1_i8];
  }

  for (c1_i9 = 0; c1_i9 < 272; c1_i9++) {
    c1_u[c1_i9] = c1_b_inData[c1_i9];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 3, 0U, 1U, 0U, 1, 272), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_emlrt_marshallIn(SFc1_commdvbcInstanceStruct *chartInstance,
  const mxArray *c1_y, const char_T *c1_identifier, uint8_T c1_b_y[272])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_y), &c1_thisId, c1_b_y);
  sf_mex_destroy(&c1_y);
}

static void c1_b_emlrt_marshallIn(SFc1_commdvbcInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint8_T c1_y[272])
{
  uint8_T c1_uv2[272];
  int32_T c1_i10;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_uv2, 1, 3, 0U, 1, 0U, 1, 272);
  for (c1_i10 = 0; c1_i10 < 272; c1_i10++) {
    c1_y[c1_i10] = c1_uv2[c1_i10];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_y;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  uint8_T c1_b_y[272];
  int32_T c1_i11;
  SFc1_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc1_commdvbcInstanceStruct *)chartInstanceVoid;
  c1_y = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_y), &c1_thisId, c1_b_y);
  sf_mex_destroy(&c1_y);
  for (c1_i11 = 0; c1_i11 < 272; c1_i11++) {
    (*(uint8_T (*)[272])c1_outData)[c1_i11] = c1_b_y[c1_i11];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i12;
  uint8_T c1_b_inData[204];
  int32_T c1_i13;
  uint8_T c1_u[204];
  const mxArray *c1_y = NULL;
  SFc1_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc1_commdvbcInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i12 = 0; c1_i12 < 204; c1_i12++) {
    c1_b_inData[c1_i12] = (*(uint8_T (*)[204])c1_inData)[c1_i12];
  }

  for (c1_i13 = 0; c1_i13 < 204; c1_i13++) {
    c1_u[c1_i13] = c1_b_inData[c1_i13];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 3, 0U, 1U, 0U, 2, 204, 1), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc1_commdvbcInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_c_emlrt_marshallIn(SFc1_commdvbcInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_nargout;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc1_commdvbcInstanceStruct *)chartInstanceVoid;
  c1_nargout = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nargout), &c1_thisId);
  sf_mex_destroy(&c1_nargout);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_commdvbc_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), FALSE);
  return c1_nameCaptureInfo;
}

static void c1_convertBytesToMTuplesDVBCDemo(SFc1_commdvbcInstanceStruct
  *chartInstance, uint8_T c1_u[204], uint8_T c1_y[272])
{
  int32_T c1_i14;
  int32_T c1_i15;
  real_T c1_a[204];
  int32_T c1_i16;
  int32_T c1_i17;
  int32_T c1_i18;
  static real_T c1_b[8] = { 0.0078125, 0.015625, 0.03125, 0.0625, 0.125, 0.25,
    0.5, 1.0 };

  real_T c1_b_y[1632];
  int32_T c1_i19;
  real_T c1_c_y[1632];
  int32_T c1_i20;
  real_T c1_d1;
  uint8_T c1_u0;
  uint8_T c1_b_b[1632];
  int32_T c1_i21;
  int32_T c1_i22;
  int32_T c1_i23;
  int32_T c1_i24;
  uint8_T c1_x[1632];
  int32_T c1_k;
  int32_T c1_b_k;
  uint8_T c1_bit_vals[1632];
  int32_T c1_out_idx;
  real_T c1_b_out_idx;
  int32_T c1_i25;
  uint8_T c1_next_sym_bits[6];
  real_T c1_c_b;
  real_T c1_d_y;
  real_T c1_bit_idx_start;
  int32_T c1_bit_idx_offset;
  real_T c1_b_bit_idx_offset;
  int32_T c1_i26;
  real_T c1_d_b[6];
  real_T c1_e_y;
  int32_T c1_c_k;
  int32_T c1_d_k;
  static real_T c1_dv0[6] = { 32.0, 16.0, 8.0, 4.0, 2.0, 1.0 };

  real_T c1_d2;
  uint8_T c1_u1;
  for (c1_i14 = 0; c1_i14 < 272; c1_i14++) {
    c1_y[c1_i14] = 0U;
  }

  c1_realmax(chartInstance);
  for (c1_i15 = 0; c1_i15 < 204; c1_i15++) {
    c1_a[c1_i15] = (real_T)c1_u[c1_i15];
  }

  c1_i16 = 0;
  for (c1_i17 = 0; c1_i17 < 8; c1_i17++) {
    for (c1_i18 = 0; c1_i18 < 204; c1_i18++) {
      c1_b_y[c1_i18 + c1_i16] = c1_a[c1_i18] * c1_b[c1_i17];
    }

    c1_i16 += 204;
  }

  for (c1_i19 = 0; c1_i19 < 1632; c1_i19++) {
    c1_c_y[c1_i19] = c1_b_y[c1_i19];
  }

  c1_rem(chartInstance, c1_c_y, 2.0, c1_b_y);
  c1_b_floor(chartInstance, c1_b_y);
  for (c1_i20 = 0; c1_i20 < 1632; c1_i20++) {
    c1_d1 = muDoubleScalarRound(c1_b_y[c1_i20]);
    if (c1_d1 < 256.0) {
      if (c1_d1 >= 0.0) {
        c1_u0 = (uint8_T)c1_d1;
      } else {
        c1_u0 = 0U;
      }
    } else if (c1_d1 >= 256.0) {
      c1_u0 = MAX_uint8_T;
    } else {
      c1_u0 = 0U;
    }

    c1_b_b[c1_i20] = c1_u0;
  }

  c1_i21 = 0;
  for (c1_i22 = 0; c1_i22 < 204; c1_i22++) {
    c1_i23 = 0;
    for (c1_i24 = 0; c1_i24 < 8; c1_i24++) {
      c1_x[c1_i24 + c1_i21] = c1_b_b[c1_i23 + c1_i22];
      c1_i23 += 204;
    }

    c1_i21 += 8;
  }

  c1_eml_int_forloop_overflow_check(chartInstance);
  for (c1_k = 1; c1_k < 1633; c1_k++) {
    c1_b_k = c1_k;
    c1_bit_vals[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c1_b_k), 1, 1632, 1, 0) - 1] = c1_x[_SFD_EML_ARRAY_BOUNDS_CHECK("",
      (int32_T)_SFD_INTEGER_CHECK("", (real_T)c1_b_k), 1, 1632, 1, 0) - 1];
  }

  c1_realmax(chartInstance);
  for (c1_out_idx = 0; c1_out_idx < 272; c1_out_idx++) {
    c1_b_out_idx = 1.0 + (real_T)c1_out_idx;
    for (c1_i25 = 0; c1_i25 < 6; c1_i25++) {
      c1_next_sym_bits[c1_i25] = 0U;
    }

    c1_c_b = c1_b_out_idx - 1.0;
    c1_d_y = 6.0 * c1_c_b;
    c1_bit_idx_start = c1_d_y + 1.0;
    for (c1_bit_idx_offset = 0; c1_bit_idx_offset < 6; c1_bit_idx_offset++) {
      c1_b_bit_idx_offset = (real_T)c1_bit_idx_offset;
      c1_next_sym_bits[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", 1.0 + c1_b_bit_idx_offset), 1, 6, 1, 0) - 1] =
        c1_bit_vals[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", c1_bit_idx_start + c1_b_bit_idx_offset), 1, 1632, 1, 0) - 1];
    }

    for (c1_i26 = 0; c1_i26 < 6; c1_i26++) {
      c1_d_b[c1_i26] = (real_T)c1_next_sym_bits[c1_i26];
    }

    c1_eml_scalar_eg(chartInstance);
    c1_eml_scalar_eg(chartInstance);
    c1_e_y = 0.0;
    c1_b_eml_int_forloop_overflow_check(chartInstance);
    for (c1_c_k = 1; c1_c_k < 7; c1_c_k++) {
      c1_d_k = c1_c_k;
      c1_e_y += c1_dv0[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c1_d_k), 1, 6, 1, 0) - 1] *
        c1_d_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c1_d_k), 1, 6, 1, 0) - 1];
    }

    c1_d2 = muDoubleScalarRound(c1_e_y);
    if (c1_d2 < 256.0) {
      if (c1_d2 >= 0.0) {
        c1_u1 = (uint8_T)c1_d2;
      } else {
        c1_u1 = 0U;
      }
    } else if (c1_d2 >= 256.0) {
      c1_u1 = MAX_uint8_T;
    } else {
      c1_u1 = 0U;
    }

    c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      c1_b_out_idx), 1, 272, 1, 0) - 1] = c1_u1;
  }
}

static void c1_realmax(SFc1_commdvbcInstanceStruct *chartInstance)
{
}

static void c1_rem(SFc1_commdvbcInstanceStruct *chartInstance, real_T c1_x[1632],
                   real_T c1_y, real_T c1_r[1632])
{
  int32_T c1_k;
  real_T c1_b_k;
  real_T c1_xk;
  real_T c1_yk;
  real_T c1_b_x;
  real_T c1_b_y;
  real_T c1_b_r;
  for (c1_k = 0; c1_k < 1632; c1_k++) {
    c1_b_k = 1.0 + (real_T)c1_k;
    c1_xk = c1_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      c1_b_k), 1, 1632, 1, 0) - 1];
    c1_yk = c1_y;
    c1_b_x = c1_xk;
    c1_b_y = c1_yk;
    c1_b_r = muDoubleScalarRem(c1_b_x, c1_b_y);
    c1_r[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", c1_b_k),
      1, 1632, 1, 0) - 1] = c1_b_r;
  }
}

static void c1_floor(SFc1_commdvbcInstanceStruct *chartInstance, real_T c1_x
                     [1632], real_T c1_b_x[1632])
{
  int32_T c1_i27;
  for (c1_i27 = 0; c1_i27 < 1632; c1_i27++) {
    c1_b_x[c1_i27] = c1_x[c1_i27];
  }

  c1_b_floor(chartInstance, c1_b_x);
}

static void c1_eml_int_forloop_overflow_check(SFc1_commdvbcInstanceStruct
  *chartInstance)
{
}

static void c1_eml_scalar_eg(SFc1_commdvbcInstanceStruct *chartInstance)
{
}

static void c1_b_eml_int_forloop_overflow_check(SFc1_commdvbcInstanceStruct
  *chartInstance)
{
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc1_commdvbcInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_d_emlrt_marshallIn(SFc1_commdvbcInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i28;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i28, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i28;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc1_commdvbcInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_e_emlrt_marshallIn(SFc1_commdvbcInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_commdvbc, const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_commdvbc), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_commdvbc);
  return c1_y;
}

static uint8_T c1_f_emlrt_marshallIn(SFc1_commdvbcInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u2;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u2, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u2;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_floor(SFc1_commdvbcInstanceStruct *chartInstance, real_T c1_x
  [1632])
{
  int32_T c1_k;
  real_T c1_b_k;
  real_T c1_b_x;
  real_T c1_c_x;
  for (c1_k = 0; c1_k < 1632; c1_k++) {
    c1_b_k = 1.0 + (real_T)c1_k;
    c1_b_x = c1_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      c1_b_k), 1, 1632, 1, 0) - 1];
    c1_c_x = c1_b_x;
    c1_c_x = muDoubleScalarFloor(c1_c_x);
    c1_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", c1_b_k),
      1, 1632, 1, 0) - 1] = c1_c_x;
  }
}

static void init_dsm_address_info(SFc1_commdvbcInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c1_commdvbc_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1920578805U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2303737625U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(555556680U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2894802346U);
}

mxArray *sf_c1_commdvbc_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("n9SIKzyWtphHcXne8I19BC");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(204);
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

static const mxArray *sf_get_sim_state_info_c1_commdvbc(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[8],M[0],T\"is_active_c1_commdvbc\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_commdvbc_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_commdvbcInstanceStruct *chartInstance;
    chartInstance = (SFc1_commdvbcInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart(_commdvbcMachineNumber_,
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
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,66);
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
          dimVector[0]= 204;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 272;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)
            c1_sf_marshallIn);
        }

        {
          uint8_T (*c1_u)[204];
          uint8_T (*c1_y)[272];
          c1_y = (uint8_T (*)[272])ssGetOutputPortSignal(chartInstance->S, 1);
          c1_u = (uint8_T (*)[204])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c1_u);
          _SFD_SET_DATA_VALUE_PTR(1U, *c1_y);
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
  return "MqLCVmZPlagAFUbrIxnIkD";
}

static void sf_opaque_initialize_c1_commdvbc(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_commdvbcInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c1_commdvbc((SFc1_commdvbcInstanceStruct*) chartInstanceVar);
  initialize_c1_commdvbc((SFc1_commdvbcInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_commdvbc(void *chartInstanceVar)
{
  enable_c1_commdvbc((SFc1_commdvbcInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_commdvbc(void *chartInstanceVar)
{
  disable_c1_commdvbc((SFc1_commdvbcInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_commdvbc(void *chartInstanceVar)
{
  sf_c1_commdvbc((SFc1_commdvbcInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_commdvbc(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_commdvbc((SFc1_commdvbcInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_commdvbc();/* state var info */
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

extern void sf_internal_set_sim_state_c1_commdvbc(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_commdvbc();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_commdvbc((SFc1_commdvbcInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_commdvbc(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_commdvbc(S);
}

static void sf_opaque_set_sim_state_c1_commdvbc(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c1_commdvbc(S, st);
}

static void sf_opaque_terminate_c1_commdvbc(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_commdvbcInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c1_commdvbc((SFc1_commdvbcInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_commdvbc_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_commdvbc((SFc1_commdvbcInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_commdvbc(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_commdvbc((SFc1_commdvbcInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_commdvbc(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_commdvbc_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,1,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,1);
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2849583881U));
  ssSetChecksum1(S,(630015857U));
  ssSetChecksum2(S,(3133290457U));
  ssSetChecksum3(S,(790654790U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c1_commdvbc(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_commdvbc(SimStruct *S)
{
  SFc1_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc1_commdvbcInstanceStruct *)malloc(sizeof
    (SFc1_commdvbcInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_commdvbcInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_commdvbc;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_commdvbc;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_commdvbc;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_commdvbc;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_commdvbc;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_commdvbc;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_commdvbc;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_commdvbc;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_commdvbc;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_commdvbc;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_commdvbc;
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

void c1_commdvbc_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_commdvbc(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_commdvbc(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_commdvbc(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_commdvbc_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
