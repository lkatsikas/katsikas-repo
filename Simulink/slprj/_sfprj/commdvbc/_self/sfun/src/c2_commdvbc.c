/* Include files */

#include "blascompat32.h"
#include "commdvbc_sfun.h"
#include "c2_commdvbc.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "commdvbc_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c2_debug_family_names[4] = { "nargin", "nargout", "u", "y" };

/* Function Declarations */
static void initialize_c2_commdvbc(SFc2_commdvbcInstanceStruct *chartInstance);
static void initialize_params_c2_commdvbc(SFc2_commdvbcInstanceStruct
  *chartInstance);
static void enable_c2_commdvbc(SFc2_commdvbcInstanceStruct *chartInstance);
static void disable_c2_commdvbc(SFc2_commdvbcInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_commdvbc(SFc2_commdvbcInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_commdvbc(SFc2_commdvbcInstanceStruct
  *chartInstance);
static void set_sim_state_c2_commdvbc(SFc2_commdvbcInstanceStruct *chartInstance,
  const mxArray *c2_st);
static void finalize_c2_commdvbc(SFc2_commdvbcInstanceStruct *chartInstance);
static void sf_c2_commdvbc(SFc2_commdvbcInstanceStruct *chartInstance);
static void initSimStructsc2_commdvbc(SFc2_commdvbcInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_commdvbcInstanceStruct *chartInstance,
  const mxArray *c2_y, const char_T *c2_identifier, uint8_T c2_b_y[204]);
static void c2_b_emlrt_marshallIn(SFc2_commdvbcInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, uint8_T c2_y[204]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_c_emlrt_marshallIn(SFc2_commdvbcInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_convertMTuplesToBytesDVBCDemo(SFc2_commdvbcInstanceStruct
  *chartInstance, uint8_T c2_u[272], uint8_T c2_y[204]);
static void c2_realmax(SFc2_commdvbcInstanceStruct *chartInstance);
static void c2_rem(SFc2_commdvbcInstanceStruct *chartInstance, real_T c2_x[1632],
                   real_T c2_y, real_T c2_r[1632]);
static void c2_floor(SFc2_commdvbcInstanceStruct *chartInstance, real_T c2_x
                     [1632], real_T c2_b_x[1632]);
static void c2_eml_int_forloop_overflow_check(SFc2_commdvbcInstanceStruct
  *chartInstance);
static void c2_eml_scalar_eg(SFc2_commdvbcInstanceStruct *chartInstance);
static void c2_b_eml_int_forloop_overflow_check(SFc2_commdvbcInstanceStruct
  *chartInstance);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_d_emlrt_marshallIn(SFc2_commdvbcInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_e_emlrt_marshallIn(SFc2_commdvbcInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_commdvbc, const char_T *c2_identifier);
static uint8_T c2_f_emlrt_marshallIn(SFc2_commdvbcInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_floor(SFc2_commdvbcInstanceStruct *chartInstance, real_T c2_x
  [1632]);
static void init_dsm_address_info(SFc2_commdvbcInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_commdvbc(SFc2_commdvbcInstanceStruct *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_is_active_c2_commdvbc = 0U;
}

static void initialize_params_c2_commdvbc(SFc2_commdvbcInstanceStruct
  *chartInstance)
{
}

static void enable_c2_commdvbc(SFc2_commdvbcInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_commdvbc(SFc2_commdvbcInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_commdvbc(SFc2_commdvbcInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c2_commdvbc(SFc2_commdvbcInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i0;
  uint8_T c2_u[204];
  const mxArray *c2_b_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  uint8_T (*c2_d_y)[204];
  c2_d_y = (uint8_T (*)[204])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(2), FALSE);
  for (c2_i0 = 0; c2_i0 < 204; c2_i0++) {
    c2_u[c2_i0] = (*c2_d_y)[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 3, 0U, 1U, 0U, 1, 204), FALSE);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_commdvbc;
  c2_b_u = c2_hoistedGlobal;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  sf_mex_assign(&c2_st, c2_y, FALSE);
  return c2_st;
}

static void set_sim_state_c2_commdvbc(SFc2_commdvbcInstanceStruct *chartInstance,
  const mxArray *c2_st)
{
  const mxArray *c2_u;
  uint8_T c2_uv0[204];
  int32_T c2_i1;
  uint8_T (*c2_y)[204];
  c2_y = (uint8_T (*)[204])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)), "y",
                      c2_uv0);
  for (c2_i1 = 0; c2_i1 < 204; c2_i1++) {
    (*c2_y)[c2_i1] = c2_uv0[c2_i1];
  }

  chartInstance->c2_is_active_c2_commdvbc = c2_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 1)), "is_active_c2_commdvbc");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_commdvbc(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_commdvbc(SFc2_commdvbcInstanceStruct *chartInstance)
{
}

static void sf_c2_commdvbc(SFc2_commdvbcInstanceStruct *chartInstance)
{
  int32_T c2_i2;
  int32_T c2_i3;
  int32_T c2_i4;
  uint8_T c2_u[272];
  uint32_T c2_debug_family_var_map[4];
  real_T c2_nargin = 1.0;
  real_T c2_nargout = 1.0;
  uint8_T c2_y[204];
  int32_T c2_i5;
  uint8_T c2_b_u[272];
  uint8_T c2_uv1[204];
  int32_T c2_i6;
  int32_T c2_i7;
  uint8_T (*c2_b_y)[204];
  uint8_T (*c2_c_u)[272];
  c2_b_y = (uint8_T (*)[204])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_c_u = (uint8_T (*)[272])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i2 = 0; c2_i2 < 272; c2_i2++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c2_c_u)[c2_i2], 0U);
  }

  for (c2_i3 = 0; c2_i3 < 204; c2_i3++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c2_b_y)[c2_i3], 1U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i4 = 0; c2_i4 < 272; c2_i4++) {
    c2_u[c2_i4] = (*c2_c_u)[c2_i4];
  }

  sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c2_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 0U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 1U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c2_u, 2U, c2_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c2_y, 3U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 2);
  for (c2_i5 = 0; c2_i5 < 272; c2_i5++) {
    c2_b_u[c2_i5] = c2_u[c2_i5];
  }

  c2_convertMTuplesToBytesDVBCDemo(chartInstance, c2_b_u, c2_uv1);
  for (c2_i6 = 0; c2_i6 < 204; c2_i6++) {
    c2_y[c2_i6] = c2_uv1[c2_i6];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -2);
  sf_debug_symbol_scope_pop();
  for (c2_i7 = 0; c2_i7 < 204; c2_i7++) {
    (*c2_b_y)[c2_i7] = c2_y[c2_i7];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  sf_debug_check_for_state_inconsistency(_commdvbcMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc2_commdvbc(SFc2_commdvbcInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i8;
  uint8_T c2_b_inData[204];
  int32_T c2_i9;
  uint8_T c2_u[204];
  const mxArray *c2_y = NULL;
  SFc2_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc2_commdvbcInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i8 = 0; c2_i8 < 204; c2_i8++) {
    c2_b_inData[c2_i8] = (*(uint8_T (*)[204])c2_inData)[c2_i8];
  }

  for (c2_i9 = 0; c2_i9 < 204; c2_i9++) {
    c2_u[c2_i9] = c2_b_inData[c2_i9];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 3, 0U, 1U, 0U, 1, 204), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_commdvbcInstanceStruct *chartInstance,
  const mxArray *c2_y, const char_T *c2_identifier, uint8_T c2_b_y[204])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_y), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_y);
}

static void c2_b_emlrt_marshallIn(SFc2_commdvbcInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, uint8_T c2_y[204])
{
  uint8_T c2_uv2[204];
  int32_T c2_i10;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_uv2, 1, 3, 0U, 1, 0U, 1, 204);
  for (c2_i10 = 0; c2_i10 < 204; c2_i10++) {
    c2_y[c2_i10] = c2_uv2[c2_i10];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_y;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_b_y[204];
  int32_T c2_i11;
  SFc2_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc2_commdvbcInstanceStruct *)chartInstanceVoid;
  c2_y = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_y), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_y);
  for (c2_i11 = 0; c2_i11 < 204; c2_i11++) {
    (*(uint8_T (*)[204])c2_outData)[c2_i11] = c2_b_y[c2_i11];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i12;
  uint8_T c2_b_inData[272];
  int32_T c2_i13;
  uint8_T c2_u[272];
  const mxArray *c2_y = NULL;
  SFc2_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc2_commdvbcInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i12 = 0; c2_i12 < 272; c2_i12++) {
    c2_b_inData[c2_i12] = (*(uint8_T (*)[272])c2_inData)[c2_i12];
  }

  for (c2_i13 = 0; c2_i13 < 272; c2_i13++) {
    c2_u[c2_i13] = c2_b_inData[c2_i13];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 3, 0U, 1U, 0U, 2, 272, 1), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc2_commdvbcInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_c_emlrt_marshallIn(SFc2_commdvbcInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc2_commdvbcInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_commdvbc_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), FALSE);
  return c2_nameCaptureInfo;
}

static void c2_convertMTuplesToBytesDVBCDemo(SFc2_commdvbcInstanceStruct
  *chartInstance, uint8_T c2_u[272], uint8_T c2_y[204])
{
  int32_T c2_i14;
  int32_T c2_i15;
  real_T c2_a[272];
  int32_T c2_i16;
  int32_T c2_i17;
  int32_T c2_i18;
  static real_T c2_b[6] = { 0.03125, 0.0625, 0.125, 0.25, 0.5, 1.0 };

  real_T c2_b_y[1632];
  int32_T c2_i19;
  real_T c2_c_y[1632];
  int32_T c2_i20;
  real_T c2_d1;
  uint8_T c2_u0;
  uint8_T c2_b_b[1632];
  int32_T c2_i21;
  int32_T c2_i22;
  int32_T c2_i23;
  int32_T c2_i24;
  uint8_T c2_x[1632];
  int32_T c2_k;
  int32_T c2_b_k;
  uint8_T c2_bit_vals[1632];
  int32_T c2_out_idx;
  real_T c2_b_out_idx;
  int32_T c2_i25;
  uint8_T c2_next_bits[8];
  real_T c2_c_b;
  real_T c2_d_y;
  real_T c2_bit_idx_start;
  int32_T c2_bit_idx_offset;
  real_T c2_b_bit_idx_offset;
  int32_T c2_i26;
  real_T c2_d_b[8];
  real_T c2_e_y;
  int32_T c2_c_k;
  int32_T c2_d_k;
  static real_T c2_dv0[8] = { 128.0, 64.0, 32.0, 16.0, 8.0, 4.0, 2.0, 1.0 };

  real_T c2_d2;
  uint8_T c2_u1;
  for (c2_i14 = 0; c2_i14 < 204; c2_i14++) {
    c2_y[c2_i14] = 0U;
  }

  c2_realmax(chartInstance);
  for (c2_i15 = 0; c2_i15 < 272; c2_i15++) {
    c2_a[c2_i15] = (real_T)c2_u[c2_i15];
  }

  c2_i16 = 0;
  for (c2_i17 = 0; c2_i17 < 6; c2_i17++) {
    for (c2_i18 = 0; c2_i18 < 272; c2_i18++) {
      c2_b_y[c2_i18 + c2_i16] = c2_a[c2_i18] * c2_b[c2_i17];
    }

    c2_i16 += 272;
  }

  for (c2_i19 = 0; c2_i19 < 1632; c2_i19++) {
    c2_c_y[c2_i19] = c2_b_y[c2_i19];
  }

  c2_rem(chartInstance, c2_c_y, 2.0, c2_b_y);
  c2_b_floor(chartInstance, c2_b_y);
  for (c2_i20 = 0; c2_i20 < 1632; c2_i20++) {
    c2_d1 = muDoubleScalarRound(c2_b_y[c2_i20]);
    if (c2_d1 < 256.0) {
      if (c2_d1 >= 0.0) {
        c2_u0 = (uint8_T)c2_d1;
      } else {
        c2_u0 = 0U;
      }
    } else if (c2_d1 >= 256.0) {
      c2_u0 = MAX_uint8_T;
    } else {
      c2_u0 = 0U;
    }

    c2_b_b[c2_i20] = c2_u0;
  }

  c2_i21 = 0;
  for (c2_i22 = 0; c2_i22 < 272; c2_i22++) {
    c2_i23 = 0;
    for (c2_i24 = 0; c2_i24 < 6; c2_i24++) {
      c2_x[c2_i24 + c2_i21] = c2_b_b[c2_i23 + c2_i22];
      c2_i23 += 272;
    }

    c2_i21 += 6;
  }

  c2_eml_int_forloop_overflow_check(chartInstance);
  for (c2_k = 1; c2_k < 1633; c2_k++) {
    c2_b_k = c2_k;
    c2_bit_vals[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_b_k), 1, 1632, 1, 0) - 1] = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("",
      (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 1632, 1, 0) - 1];
  }

  c2_realmax(chartInstance);
  for (c2_out_idx = 0; c2_out_idx < 204; c2_out_idx++) {
    c2_b_out_idx = 1.0 + (real_T)c2_out_idx;
    for (c2_i25 = 0; c2_i25 < 8; c2_i25++) {
      c2_next_bits[c2_i25] = 0U;
    }

    c2_c_b = c2_b_out_idx - 1.0;
    c2_d_y = 8.0 * c2_c_b;
    c2_bit_idx_start = c2_d_y + 1.0;
    for (c2_bit_idx_offset = 0; c2_bit_idx_offset < 8; c2_bit_idx_offset++) {
      c2_b_bit_idx_offset = (real_T)c2_bit_idx_offset;
      c2_next_bits[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", 1.0 + c2_b_bit_idx_offset), 1, 8, 1, 0) - 1] =
        c2_bit_vals[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", c2_bit_idx_start + c2_b_bit_idx_offset), 1, 1632, 1, 0) - 1];
    }

    for (c2_i26 = 0; c2_i26 < 8; c2_i26++) {
      c2_d_b[c2_i26] = (real_T)c2_next_bits[c2_i26];
    }

    c2_eml_scalar_eg(chartInstance);
    c2_eml_scalar_eg(chartInstance);
    c2_e_y = 0.0;
    c2_b_eml_int_forloop_overflow_check(chartInstance);
    for (c2_c_k = 1; c2_c_k < 9; c2_c_k++) {
      c2_d_k = c2_c_k;
      c2_e_y += c2_dv0[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_d_k), 1, 8, 1, 0) - 1] *
        c2_d_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_d_k), 1, 8, 1, 0) - 1];
    }

    c2_d2 = muDoubleScalarRound(c2_e_y);
    if (c2_d2 < 256.0) {
      if (c2_d2 >= 0.0) {
        c2_u1 = (uint8_T)c2_d2;
      } else {
        c2_u1 = 0U;
      }
    } else if (c2_d2 >= 256.0) {
      c2_u1 = MAX_uint8_T;
    } else {
      c2_u1 = 0U;
    }

    c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      c2_b_out_idx), 1, 204, 1, 0) - 1] = c2_u1;
  }
}

static void c2_realmax(SFc2_commdvbcInstanceStruct *chartInstance)
{
}

static void c2_rem(SFc2_commdvbcInstanceStruct *chartInstance, real_T c2_x[1632],
                   real_T c2_y, real_T c2_r[1632])
{
  int32_T c2_k;
  real_T c2_b_k;
  real_T c2_xk;
  real_T c2_yk;
  real_T c2_b_x;
  real_T c2_b_y;
  real_T c2_b_r;
  for (c2_k = 0; c2_k < 1632; c2_k++) {
    c2_b_k = 1.0 + (real_T)c2_k;
    c2_xk = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      c2_b_k), 1, 1632, 1, 0) - 1];
    c2_yk = c2_y;
    c2_b_x = c2_xk;
    c2_b_y = c2_yk;
    c2_b_r = muDoubleScalarRem(c2_b_x, c2_b_y);
    c2_r[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", c2_b_k),
      1, 1632, 1, 0) - 1] = c2_b_r;
  }
}

static void c2_floor(SFc2_commdvbcInstanceStruct *chartInstance, real_T c2_x
                     [1632], real_T c2_b_x[1632])
{
  int32_T c2_i27;
  for (c2_i27 = 0; c2_i27 < 1632; c2_i27++) {
    c2_b_x[c2_i27] = c2_x[c2_i27];
  }

  c2_b_floor(chartInstance, c2_b_x);
}

static void c2_eml_int_forloop_overflow_check(SFc2_commdvbcInstanceStruct
  *chartInstance)
{
}

static void c2_eml_scalar_eg(SFc2_commdvbcInstanceStruct *chartInstance)
{
}

static void c2_b_eml_int_forloop_overflow_check(SFc2_commdvbcInstanceStruct
  *chartInstance)
{
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc2_commdvbcInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static int32_T c2_d_emlrt_marshallIn(SFc2_commdvbcInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i28;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i28, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i28;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc2_commdvbcInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_e_emlrt_marshallIn(SFc2_commdvbcInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_commdvbc, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_commdvbc), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_commdvbc);
  return c2_y;
}

static uint8_T c2_f_emlrt_marshallIn(SFc2_commdvbcInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u2;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u2, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u2;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_floor(SFc2_commdvbcInstanceStruct *chartInstance, real_T c2_x
  [1632])
{
  int32_T c2_k;
  real_T c2_b_k;
  real_T c2_b_x;
  real_T c2_c_x;
  for (c2_k = 0; c2_k < 1632; c2_k++) {
    c2_b_k = 1.0 + (real_T)c2_k;
    c2_b_x = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      c2_b_k), 1, 1632, 1, 0) - 1];
    c2_c_x = c2_b_x;
    c2_c_x = muDoubleScalarFloor(c2_c_x);
    c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", c2_b_k),
      1, 1632, 1, 0) - 1] = c2_c_x;
  }
}

static void init_dsm_address_info(SFc2_commdvbcInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c2_commdvbc_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1529331544U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1956439655U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1118977393U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(325760475U);
}

mxArray *sf_c2_commdvbc_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("74y3jalsvAqtgtg364imCG");
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c2_commdvbc(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[8],M[0],T\"is_active_c2_commdvbc\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_commdvbc_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_commdvbcInstanceStruct *chartInstance;
    chartInstance = (SFc2_commdvbcInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart(_commdvbcMachineNumber_,
          2,
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
          dimVector[0]= 272;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 204;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        {
          uint8_T (*c2_u)[272];
          uint8_T (*c2_y)[204];
          c2_y = (uint8_T (*)[204])ssGetOutputPortSignal(chartInstance->S, 1);
          c2_u = (uint8_T (*)[272])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_u);
          _SFD_SET_DATA_VALUE_PTR(1U, *c2_y);
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
  return "61i8zikU0ER2uYlX4ZuAqE";
}

static void sf_opaque_initialize_c2_commdvbc(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_commdvbcInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c2_commdvbc((SFc2_commdvbcInstanceStruct*) chartInstanceVar);
  initialize_c2_commdvbc((SFc2_commdvbcInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_commdvbc(void *chartInstanceVar)
{
  enable_c2_commdvbc((SFc2_commdvbcInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_commdvbc(void *chartInstanceVar)
{
  disable_c2_commdvbc((SFc2_commdvbcInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_commdvbc(void *chartInstanceVar)
{
  sf_c2_commdvbc((SFc2_commdvbcInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_commdvbc(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_commdvbc((SFc2_commdvbcInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_commdvbc();/* state var info */
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

extern void sf_internal_set_sim_state_c2_commdvbc(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_commdvbc();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_commdvbc((SFc2_commdvbcInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_commdvbc(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_commdvbc(S);
}

static void sf_opaque_set_sim_state_c2_commdvbc(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c2_commdvbc(S, st);
}

static void sf_opaque_terminate_c2_commdvbc(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_commdvbcInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c2_commdvbc((SFc2_commdvbcInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_commdvbc_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_commdvbc((SFc2_commdvbcInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_commdvbc(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_commdvbc((SFc2_commdvbcInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_commdvbc(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_commdvbc_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,2,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2911077688U));
  ssSetChecksum1(S,(66653630U));
  ssSetChecksum2(S,(3654776115U));
  ssSetChecksum3(S,(3960008822U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c2_commdvbc(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_commdvbc(SimStruct *S)
{
  SFc2_commdvbcInstanceStruct *chartInstance;
  chartInstance = (SFc2_commdvbcInstanceStruct *)malloc(sizeof
    (SFc2_commdvbcInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_commdvbcInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_commdvbc;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_commdvbc;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_commdvbc;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_commdvbc;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_commdvbc;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_commdvbc;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_commdvbc;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_commdvbc;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_commdvbc;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_commdvbc;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_commdvbc;
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

void c2_commdvbc_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_commdvbc(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_commdvbc(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_commdvbc(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_commdvbc_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
