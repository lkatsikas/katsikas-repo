/* Include files */

#include "blascompat32.h"
#include "vipcodec_sfun.h"
#include "c2_vipcodec.h"
#include "mwmathutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void initialize_c2_vipcodec(SFc2_vipcodecInstanceStruct *chartInstance);
static void initialize_params_c2_vipcodec(SFc2_vipcodecInstanceStruct
  *chartInstance);
static void enable_c2_vipcodec(SFc2_vipcodecInstanceStruct *chartInstance);
static void disable_c2_vipcodec(SFc2_vipcodecInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_vipcodec(SFc2_vipcodecInstanceStruct
  *chartInstance);
static void set_sim_state_c2_vipcodec(SFc2_vipcodecInstanceStruct *chartInstance,
  const mxArray *c2_st);
static void finalize_c2_vipcodec(SFc2_vipcodecInstanceStruct *chartInstance);
static void sf_c2_vipcodec(SFc2_vipcodecInstanceStruct *chartInstance);
static void initSimStructsc2_vipcodec(SFc2_vipcodecInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static real32_T c2_emlrt_marshallIn(SFc2_vipcodecInstanceStruct *chartInstance,
  const mxArray *c2_bits, const char_T *c2_identifier);
static real32_T c2_b_emlrt_marshallIn(SFc2_vipcodecInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static uint8_T c2_c_emlrt_marshallIn(SFc2_vipcodecInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_vipcodec, const char_T *c2_identifier);
static uint8_T c2_d_emlrt_marshallIn(SFc2_vipcodecInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_vipcodecInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_vipcodec(SFc2_vipcodecInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_is_active_c2_vipcodec = 0U;
}

static void initialize_params_c2_vipcodec(SFc2_vipcodecInstanceStruct
  *chartInstance)
{
}

static void enable_c2_vipcodec(SFc2_vipcodecInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_vipcodec(SFc2_vipcodecInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static const mxArray *get_sim_state_c2_vipcodec(SFc2_vipcodecInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  real32_T c2_u;
  const mxArray *c2_b_y = NULL;
  uint8_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  real32_T *c2_bits;
  c2_bits = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(2));
  c2_u = *c2_bits;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_u, 1, 0U, 0U, 0U, 0));
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_b_u = chartInstance->c2_is_active_c2_vipcodec;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c2_y, 1, c2_c_y);
  sf_mex_assign(&c2_st, c2_y);
  return c2_st;
}

static void set_sim_state_c2_vipcodec(SFc2_vipcodecInstanceStruct *chartInstance,
  const mxArray *c2_st)
{
  const mxArray *c2_u;
  real32_T *c2_bits;
  c2_bits = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c2_u = sf_mex_dup(c2_st);
  *c2_bits = c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u,
    0)), "bits");
  chartInstance->c2_is_active_c2_vipcodec = c2_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 1)), "is_active_c2_vipcodec");
  sf_mex_destroy(&c2_u);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_vipcodec(SFc2_vipcodecInstanceStruct *chartInstance)
{
}

static void sf_c2_vipcodec(SFc2_vipcodecInstanceStruct *chartInstance)
{
  int32_T c2_i;
  real32_T c2_in[64];
  real_T c2_numacbits;
  real_T c2_run;
  real32_T c2_f0;
  uint32_T c2_dcval;
  int32_T c2_b_i;
  boolean_T c2_exitg2;
  boolean_T c2_guard1 = FALSE;
  int32_T c2_j;
  int32_T c2_b_j;
  boolean_T c2_exitg1;
  static int8_T c2_iv0[160] = { 2, 2, 3, 4, 5, 7, 8, 10, 16, 16, 4, 5, 7, 9, 11,
    16, 16, 16, 16, 16, 5, 8, 10, 12, 16, 16, 16, 16, 16, 16, 6, 9, 12, 16, 16,
    16, 16, 16, 16, 16, 6, 10, 16, 16, 16, 16, 16, 16, 16, 16, 7, 11, 16, 16, 16,
    16, 16, 16, 16, 16, 7, 12, 16, 16, 16, 16, 16, 16, 16, 16, 8, 12, 16, 16, 16,
    16, 16, 16, 16, 16, 9, 15, 16, 16, 16, 16, 16, 16, 16, 16, 9, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 9, 16, 16, 16, 16, 16, 16, 16, 16, 16, 10, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 10, 16, 16, 16, 16, 16, 16, 16, 16, 16, 11, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16 };

  static int8_T c2_iv1[12] = { 2, 3, 3, 3, 3, 3, 4, 5, 6, 7, 8, 9 };

  real32_T *c2_bits;
  real32_T (*c2_b_in)[64];
  c2_bits = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c2_b_in = (real32_T (*)[64])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  for (c2_i = 0; c2_i < 64; c2_i++) {
    c2_in[c2_i] = (*c2_b_in)[c2_i];
  }

  c2_numacbits = 0.0;
  c2_run = 0.0;
  if ((real_T)(*c2_b_in)[0] < 0.0) {
    c2_f0 = -(*c2_b_in)[0];
    if ((c2_f0 < 8.388608E+6F) && (c2_f0 > -8.388608E+6F)) {
      c2_f0 = c2_f0 < 0.0F ? muSingleScalarCeil(c2_f0 - 0.5F) :
        muSingleScalarFloor(c2_f0 + 0.5F);
    }

    if (c2_f0 < 4.2949673E+9F) {
      if (c2_f0 >= 0.0F) {
        c2_dcval = (uint32_T)c2_f0;
      } else {
        c2_dcval = 0U;
      }
    } else if (c2_f0 >= 4.2949673E+9F) {
      c2_dcval = MAX_uint32_T;
    } else {
      c2_dcval = 0U;
    }
  } else {
    c2_f0 = (*c2_b_in)[0];
    if ((c2_f0 < 8.388608E+6F) && (c2_f0 > -8.388608E+6F)) {
      c2_f0 = c2_f0 < 0.0F ? muSingleScalarCeil(c2_f0 - 0.5F) :
        muSingleScalarFloor(c2_f0 + 0.5F);
    }

    if (c2_f0 < 4.2949673E+9F) {
      if (c2_f0 >= 0.0F) {
        c2_dcval = (uint32_T)c2_f0;
      } else {
        c2_dcval = 0U;
      }
    } else if (c2_f0 >= 4.2949673E+9F) {
      c2_dcval = MAX_uint32_T;
    } else {
      c2_dcval = 0U;
    }
  }

  c2_i = 0;
  c2_b_i = 0;
  c2_exitg2 = 0U;
  while ((c2_exitg2 == 0U) && (c2_b_i <= 11)) {
    c2_i = c2_b_i;
    if (c2_dcval == 0U) {
      c2_exitg2 = 1U;
    } else {
      c2_dcval >>= 1U;
      c2_b_i++;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }
  }

  for (c2_b_i = 0; c2_b_i < 63; c2_b_i++) {
    c2_guard1 = FALSE;
    if ((real_T)c2_in[c2_b_i + 1] == 0.0) {
      c2_run++;
      if (c2_b_i + 1 < 63) {
      } else {
        c2_guard1 = TRUE;
      }
    } else {
      c2_guard1 = TRUE;
    }

    if (c2_guard1 == TRUE) {
      if ((real_T)c2_in[c2_b_i + 1] < 0.0) {
        c2_f0 = -c2_in[c2_b_i + 1];
        if ((c2_f0 < 8.388608E+6F) && (c2_f0 > -8.388608E+6F)) {
          c2_f0 = c2_f0 < 0.0F ? muSingleScalarCeil(c2_f0 - 0.5F) :
            muSingleScalarFloor(c2_f0 + 0.5F);
        }

        if (c2_f0 < 4.2949673E+9F) {
          if (c2_f0 >= 0.0F) {
            c2_dcval = (uint32_T)c2_f0;
          } else {
            c2_dcval = 0U;
          }
        } else if (c2_f0 >= 4.2949673E+9F) {
          c2_dcval = MAX_uint32_T;
        } else {
          c2_dcval = 0U;
        }
      } else {
        c2_f0 = c2_in[c2_b_i + 1];
        if ((c2_f0 < 8.388608E+6F) && (c2_f0 > -8.388608E+6F)) {
          c2_f0 = c2_f0 < 0.0F ? muSingleScalarCeil(c2_f0 - 0.5F) :
            muSingleScalarFloor(c2_f0 + 0.5F);
        }

        if (c2_f0 < 4.2949673E+9F) {
          if (c2_f0 >= 0.0F) {
            c2_dcval = (uint32_T)c2_f0;
          } else {
            c2_dcval = 0U;
          }
        } else if (c2_f0 >= 4.2949673E+9F) {
          c2_dcval = MAX_uint32_T;
        } else {
          c2_dcval = 0U;
        }
      }

      c2_j = 0;
      c2_b_j = 0;
      c2_exitg1 = 0U;
      while ((c2_exitg1 == 0U) && (c2_b_j <= 31)) {
        c2_j = c2_b_j;
        if (c2_dcval == 0U) {
          c2_exitg1 = 1U;
        } else {
          c2_dcval >>= 1U;
          c2_b_j++;
          sf_mex_listen_for_ctrl_c(chartInstance->S);
        }
      }

      while (c2_run > 15.0) {
        c2_run -= 15.0;
        c2_numacbits += 11.0;
        sf_mex_listen_for_ctrl_c(chartInstance->S);
      }

      c2_numacbits = (c2_numacbits + (real_T)c2_iv0[sf_mex_lw_bounds_check
                      (((int32_T)c2_run * 10 + c2_j) + 1, 1, 160) - 1]) +
        (real_T)c2_j;
      c2_run = 0.0;
    }

    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  if (c2_run > 0.0) {
    c2_numacbits += 4.0;
  }

  *c2_bits = (real32_T)(c2_numacbits + (real_T)(c2_iv1[c2_i] + c2_i));
}

static void initSimStructsc2_vipcodec(SFc2_vipcodecInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

const mxArray *sf_c2_vipcodec_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo;
  c2_ResolvedFunctionInfo c2_info[9];
  c2_ResolvedFunctionInfo (*c2_b_info)[9];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i0;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_b_info = (c2_ResolvedFunctionInfo (*)[9])c2_info;
  (*c2_b_info)[0].context = "";
  (*c2_b_info)[0].name = "bitshift";
  (*c2_b_info)[0].dominantType = "uint32";
  (*c2_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  (*c2_b_info)[0].fileTimeLo = 1286815238U;
  (*c2_b_info)[0].fileTimeHi = 0U;
  (*c2_b_info)[0].mFileTimeLo = 0U;
  (*c2_b_info)[0].mFileTimeHi = 0U;
  (*c2_b_info)[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  (*c2_b_info)[1].name = "eml_isa_uint";
  (*c2_b_info)[1].dominantType = "uint32";
  (*c2_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  (*c2_b_info)[1].fileTimeLo = 1286815184U;
  (*c2_b_info)[1].fileTimeHi = 0U;
  (*c2_b_info)[1].mFileTimeLo = 0U;
  (*c2_b_info)[1].mFileTimeHi = 0U;
  (*c2_b_info)[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  (*c2_b_info)[2].name = "eml_int_nbits";
  (*c2_b_info)[2].dominantType = "char";
  (*c2_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_nbits.m";
  (*c2_b_info)[2].fileTimeLo = 1286815180U;
  (*c2_b_info)[2].fileTimeHi = 0U;
  (*c2_b_info)[2].mFileTimeLo = 0U;
  (*c2_b_info)[2].mFileTimeHi = 0U;
  (*c2_b_info)[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  (*c2_b_info)[3].name = "eml_scalar_eg";
  (*c2_b_info)[3].dominantType = "uint32";
  (*c2_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  (*c2_b_info)[3].fileTimeLo = 1286815196U;
  (*c2_b_info)[3].fileTimeHi = 0U;
  (*c2_b_info)[3].mFileTimeLo = 0U;
  (*c2_b_info)[3].mFileTimeHi = 0U;
  (*c2_b_info)[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  (*c2_b_info)[4].name = "eml_scalexp_alloc";
  (*c2_b_info)[4].dominantType = "uint32";
  (*c2_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  (*c2_b_info)[4].fileTimeLo = 1286815196U;
  (*c2_b_info)[4].fileTimeHi = 0U;
  (*c2_b_info)[4].mFileTimeLo = 0U;
  (*c2_b_info)[4].mFileTimeHi = 0U;
  (*c2_b_info)[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  (*c2_b_info)[5].name = "floor";
  (*c2_b_info)[5].dominantType = "double";
  (*c2_b_info)[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  (*c2_b_info)[5].fileTimeLo = 1286815142U;
  (*c2_b_info)[5].fileTimeHi = 0U;
  (*c2_b_info)[5].mFileTimeLo = 0U;
  (*c2_b_info)[5].mFileTimeHi = 0U;
  (*c2_b_info)[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  (*c2_b_info)[6].name = "eml_scalar_floor";
  (*c2_b_info)[6].dominantType = "double";
  (*c2_b_info)[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  (*c2_b_info)[6].fileTimeLo = 1286815126U;
  (*c2_b_info)[6].fileTimeHi = 0U;
  (*c2_b_info)[6].mFileTimeLo = 0U;
  (*c2_b_info)[6].mFileTimeHi = 0U;
  (*c2_b_info)[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  (*c2_b_info)[7].name = "eml_error";
  (*c2_b_info)[7].dominantType = "char";
  (*c2_b_info)[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  (*c2_b_info)[7].fileTimeLo = 1286815100U;
  (*c2_b_info)[7].fileTimeHi = 0U;
  (*c2_b_info)[7].mFileTimeLo = 0U;
  (*c2_b_info)[7].mFileTimeHi = 0U;
  (*c2_b_info)[8].context = "";
  (*c2_b_info)[8].name = "mtimes";
  (*c2_b_info)[8].dominantType = "double";
  (*c2_b_info)[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c2_b_info)[8].fileTimeLo = 1289516092U;
  (*c2_b_info)[8].fileTimeHi = 0U;
  (*c2_b_info)[8].mFileTimeLo = 0U;
  (*c2_b_info)[8].mFileTimeHi = 0U;
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 9));
  for (c2_i0 = 0; c2_i0 < 9; c2_i0++) {
    c2_r0 = &c2_info[c2_i0];
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->context)), "context", "nameCaptureInfo",
                    c2_i0);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c2_r0->name)), "name", "nameCaptureInfo", c2_i0);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c2_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c2_i0);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->resolved)), "resolved", "nameCaptureInfo",
                    c2_i0);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c2_i0);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c2_i0);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c2_i0);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c2_i0);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m0);
  return c2_nameCaptureInfo;
}

static real32_T c2_emlrt_marshallIn(SFc2_vipcodecInstanceStruct *chartInstance,
  const mxArray *c2_bits, const char_T *c2_identifier)
{
  real32_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_bits), &c2_thisId);
  sf_mex_destroy(&c2_bits);
  return c2_y;
}

static real32_T c2_b_emlrt_marshallIn(SFc2_vipcodecInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real32_T c2_y;
  real32_T c2_f1;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_f1, 1, 1, 0U, 0, 0U, 0);
  c2_y = c2_f1;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static uint8_T c2_c_emlrt_marshallIn(SFc2_vipcodecInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_vipcodec, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_vipcodec), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_vipcodec);
  return c2_y;
}

static uint8_T c2_d_emlrt_marshallIn(SFc2_vipcodecInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_vipcodecInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c2_vipcodec_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2478181392U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1584717582U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(314709297U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1178073929U);
}

mxArray *sf_c2_vipcodec_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(2516534237U);
    pr[1] = (double)(65869683U);
    pr[2] = (double)(2156563749U);
    pr[3] = (double)(2860792461U);
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
      pr[0] = (double)(1);
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

static const mxArray *sf_get_sim_state_info_c2_vipcodec(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"bits\",},{M[8],M[0],T\"is_active_c2_vipcodec\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_vipcodec_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void sf_opaque_initialize_c2_vipcodec(void *chartInstanceVar)
{
  initialize_params_c2_vipcodec((SFc2_vipcodecInstanceStruct*) chartInstanceVar);
  initialize_c2_vipcodec((SFc2_vipcodecInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_vipcodec(void *chartInstanceVar)
{
  enable_c2_vipcodec((SFc2_vipcodecInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_vipcodec(void *chartInstanceVar)
{
  disable_c2_vipcodec((SFc2_vipcodecInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_vipcodec(void *chartInstanceVar)
{
  sf_c2_vipcodec((SFc2_vipcodecInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_vipcodec(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_vipcodec((SFc2_vipcodecInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_vipcodec();/* state var info */
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

extern void sf_internal_set_sim_state_c2_vipcodec(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_vipcodec();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_vipcodec((SFc2_vipcodecInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_vipcodec(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_vipcodec(S);
}

static void sf_opaque_set_sim_state_c2_vipcodec(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c2_vipcodec(S, st);
}

static void sf_opaque_terminate_c2_vipcodec(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_vipcodecInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c2_vipcodec((SFc2_vipcodecInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_vipcodec((SFc2_vipcodecInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_vipcodec(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_vipcodec((SFc2_vipcodecInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_vipcodec(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"vipcodec","vipcodec",2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"vipcodec","vipcodec",2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"vipcodec","vipcodec",2,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"vipcodec","vipcodec",2,1);
      sf_mark_chart_reusable_outputs(S,"vipcodec","vipcodec",2,1);
    }

    sf_set_rtw_dwork_info(S,"vipcodec","vipcodec",2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1981671962U));
  ssSetChecksum1(S,(3620684265U));
  ssSetChecksum2(S,(734916288U));
  ssSetChecksum3(S,(3651312268U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c2_vipcodec(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "vipcodec", "vipcodec",2);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_vipcodec(SimStruct *S)
{
  SFc2_vipcodecInstanceStruct *chartInstance;
  chartInstance = (SFc2_vipcodecInstanceStruct *)malloc(sizeof
    (SFc2_vipcodecInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_vipcodecInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_vipcodec;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_vipcodec;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_vipcodec;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_vipcodec;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_vipcodec;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_vipcodec;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_vipcodec;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_vipcodec;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_vipcodec;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_vipcodec;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_vipcodec;
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

void c2_vipcodec_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_vipcodec(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_vipcodec(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_vipcodec(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_vipcodec_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
