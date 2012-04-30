/* Include files */

#include "blascompat32.h"
#include "video_sfun.h"
#include "c3_video.h"
#include "mwmathutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void initialize_c3_video(SFc3_videoInstanceStruct *chartInstance);
static void initialize_params_c3_video(SFc3_videoInstanceStruct *chartInstance);
static void enable_c3_video(SFc3_videoInstanceStruct *chartInstance);
static void disable_c3_video(SFc3_videoInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c3_video(SFc3_videoInstanceStruct
  *chartInstance);
static void set_sim_state_c3_video(SFc3_videoInstanceStruct *chartInstance,
  const mxArray *c3_st);
static void finalize_c3_video(SFc3_videoInstanceStruct *chartInstance);
static void sf_c3_video(SFc3_videoInstanceStruct *chartInstance);
static void initSimStructsc3_video(SFc3_videoInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber);
static real32_T c3_emlrt_marshallIn(SFc3_videoInstanceStruct *chartInstance,
  const mxArray *c3_bits, const char_T *c3_identifier);
static real32_T c3_b_emlrt_marshallIn(SFc3_videoInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static uint8_T c3_c_emlrt_marshallIn(SFc3_videoInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_video, const char_T *c3_identifier);
static uint8_T c3_d_emlrt_marshallIn(SFc3_videoInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void init_dsm_address_info(SFc3_videoInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c3_video(SFc3_videoInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c3_is_active_c3_video = 0U;
}

static void initialize_params_c3_video(SFc3_videoInstanceStruct *chartInstance)
{
}

static void enable_c3_video(SFc3_videoInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c3_video(SFc3_videoInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static const mxArray *get_sim_state_c3_video(SFc3_videoInstanceStruct
  *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  real32_T c3_u;
  const mxArray *c3_b_y = NULL;
  uint8_T c3_b_u;
  const mxArray *c3_c_y = NULL;
  real32_T *c3_bits;
  c3_bits = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellarray(2));
  c3_u = *c3_bits;
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_u, 1, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 0, c3_b_y);
  c3_b_u = chartInstance->c3_is_active_c3_video;
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", &c3_b_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 1, c3_c_y);
  sf_mex_assign(&c3_st, c3_y);
  return c3_st;
}

static void set_sim_state_c3_video(SFc3_videoInstanceStruct *chartInstance,
  const mxArray *c3_st)
{
  const mxArray *c3_u;
  real32_T *c3_bits;
  c3_bits = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c3_u = sf_mex_dup(c3_st);
  *c3_bits = c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u,
    0)), "bits");
  chartInstance->c3_is_active_c3_video = c3_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_u, 1)), "is_active_c3_video");
  sf_mex_destroy(&c3_u);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_video(SFc3_videoInstanceStruct *chartInstance)
{
}

static void sf_c3_video(SFc3_videoInstanceStruct *chartInstance)
{
  int32_T c3_i;
  real32_T c3_in[64];
  real_T c3_numacbits;
  real_T c3_run;
  real32_T c3_f0;
  uint32_T c3_dcval;
  int32_T c3_b_i;
  boolean_T c3_exitg2;
  boolean_T c3_guard1 = FALSE;
  int32_T c3_j;
  int32_T c3_b_j;
  boolean_T c3_exitg1;
  static int8_T c3_iv0[160] = { 2, 2, 3, 4, 5, 7, 8, 10, 16, 16, 4, 5, 7, 9, 11,
    16, 16, 16, 16, 16, 5, 8, 10, 12, 16, 16, 16, 16, 16, 16, 6, 9, 12, 16, 16,
    16, 16, 16, 16, 16, 6, 10, 16, 16, 16, 16, 16, 16, 16, 16, 7, 11, 16, 16, 16,
    16, 16, 16, 16, 16, 7, 12, 16, 16, 16, 16, 16, 16, 16, 16, 8, 12, 16, 16, 16,
    16, 16, 16, 16, 16, 9, 15, 16, 16, 16, 16, 16, 16, 16, 16, 9, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 9, 16, 16, 16, 16, 16, 16, 16, 16, 16, 10, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 10, 16, 16, 16, 16, 16, 16, 16, 16, 16, 11, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16 };

  static int8_T c3_iv1[12] = { 2, 3, 3, 3, 3, 3, 4, 5, 6, 7, 8, 9 };

  real32_T *c3_bits;
  real32_T (*c3_b_in)[64];
  c3_bits = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c3_b_in = (real32_T (*)[64])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  for (c3_i = 0; c3_i < 64; c3_i++) {
    c3_in[c3_i] = (*c3_b_in)[c3_i];
  }

  c3_numacbits = 0.0;
  c3_run = 0.0;
  if ((real_T)(*c3_b_in)[0] < 0.0) {
    c3_f0 = -(*c3_b_in)[0];
    if ((c3_f0 < 8.388608E+6F) && (c3_f0 > -8.388608E+6F)) {
      c3_f0 = c3_f0 < 0.0F ? muSingleScalarCeil(c3_f0 - 0.5F) :
        muSingleScalarFloor(c3_f0 + 0.5F);
    }

    if (c3_f0 < 4.2949673E+9F) {
      if (c3_f0 >= 0.0F) {
        c3_dcval = (uint32_T)c3_f0;
      } else {
        c3_dcval = 0U;
      }
    } else if (c3_f0 >= 4.2949673E+9F) {
      c3_dcval = MAX_uint32_T;
    } else {
      c3_dcval = 0U;
    }
  } else {
    c3_f0 = (*c3_b_in)[0];
    if ((c3_f0 < 8.388608E+6F) && (c3_f0 > -8.388608E+6F)) {
      c3_f0 = c3_f0 < 0.0F ? muSingleScalarCeil(c3_f0 - 0.5F) :
        muSingleScalarFloor(c3_f0 + 0.5F);
    }

    if (c3_f0 < 4.2949673E+9F) {
      if (c3_f0 >= 0.0F) {
        c3_dcval = (uint32_T)c3_f0;
      } else {
        c3_dcval = 0U;
      }
    } else if (c3_f0 >= 4.2949673E+9F) {
      c3_dcval = MAX_uint32_T;
    } else {
      c3_dcval = 0U;
    }
  }

  c3_i = 0;
  c3_b_i = 0;
  c3_exitg2 = 0U;
  while ((c3_exitg2 == 0U) && (c3_b_i <= 11)) {
    c3_i = c3_b_i;
    if (c3_dcval == 0U) {
      c3_exitg2 = 1U;
    } else {
      c3_dcval >>= 1U;
      c3_b_i++;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }
  }

  for (c3_b_i = 0; c3_b_i < 63; c3_b_i++) {
    c3_guard1 = FALSE;
    if ((real_T)c3_in[c3_b_i + 1] == 0.0) {
      c3_run++;
      if (c3_b_i + 1 < 63) {
      } else {
        c3_guard1 = TRUE;
      }
    } else {
      c3_guard1 = TRUE;
    }

    if (c3_guard1 == TRUE) {
      if ((real_T)c3_in[c3_b_i + 1] < 0.0) {
        c3_f0 = -c3_in[c3_b_i + 1];
        if ((c3_f0 < 8.388608E+6F) && (c3_f0 > -8.388608E+6F)) {
          c3_f0 = c3_f0 < 0.0F ? muSingleScalarCeil(c3_f0 - 0.5F) :
            muSingleScalarFloor(c3_f0 + 0.5F);
        }

        if (c3_f0 < 4.2949673E+9F) {
          if (c3_f0 >= 0.0F) {
            c3_dcval = (uint32_T)c3_f0;
          } else {
            c3_dcval = 0U;
          }
        } else if (c3_f0 >= 4.2949673E+9F) {
          c3_dcval = MAX_uint32_T;
        } else {
          c3_dcval = 0U;
        }
      } else {
        c3_f0 = c3_in[c3_b_i + 1];
        if ((c3_f0 < 8.388608E+6F) && (c3_f0 > -8.388608E+6F)) {
          c3_f0 = c3_f0 < 0.0F ? muSingleScalarCeil(c3_f0 - 0.5F) :
            muSingleScalarFloor(c3_f0 + 0.5F);
        }

        if (c3_f0 < 4.2949673E+9F) {
          if (c3_f0 >= 0.0F) {
            c3_dcval = (uint32_T)c3_f0;
          } else {
            c3_dcval = 0U;
          }
        } else if (c3_f0 >= 4.2949673E+9F) {
          c3_dcval = MAX_uint32_T;
        } else {
          c3_dcval = 0U;
        }
      }

      c3_j = 0;
      c3_b_j = 0;
      c3_exitg1 = 0U;
      while ((c3_exitg1 == 0U) && (c3_b_j <= 31)) {
        c3_j = c3_b_j;
        if (c3_dcval == 0U) {
          c3_exitg1 = 1U;
        } else {
          c3_dcval >>= 1U;
          c3_b_j++;
          sf_mex_listen_for_ctrl_c(chartInstance->S);
        }
      }

      while (c3_run > 15.0) {
        c3_run -= 15.0;
        c3_numacbits += 11.0;
        sf_mex_listen_for_ctrl_c(chartInstance->S);
      }

      c3_numacbits = (c3_numacbits + (real_T)c3_iv0[sf_mex_lw_bounds_check
                      (((int32_T)c3_run * 10 + c3_j) + 1, 1, 160) - 1]) +
        (real_T)c3_j;
      c3_run = 0.0;
    }

    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  if (c3_run > 0.0) {
    c3_numacbits += 4.0;
  }

  *c3_bits = (real32_T)(c3_numacbits + (real_T)(c3_iv1[c3_i] + c3_i));
}

static void initSimStructsc3_video(SFc3_videoInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber)
{
}

const mxArray *sf_c3_video_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo;
  c3_ResolvedFunctionInfo c3_info[9];
  c3_ResolvedFunctionInfo (*c3_b_info)[9];
  const mxArray *c3_m0 = NULL;
  int32_T c3_i0;
  c3_ResolvedFunctionInfo *c3_r0;
  c3_nameCaptureInfo = NULL;
  c3_b_info = (c3_ResolvedFunctionInfo (*)[9])c3_info;
  (*c3_b_info)[0].context = "";
  (*c3_b_info)[0].name = "bitshift";
  (*c3_b_info)[0].dominantType = "uint32";
  (*c3_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  (*c3_b_info)[0].fileTimeLo = 1286815238U;
  (*c3_b_info)[0].fileTimeHi = 0U;
  (*c3_b_info)[0].mFileTimeLo = 0U;
  (*c3_b_info)[0].mFileTimeHi = 0U;
  (*c3_b_info)[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  (*c3_b_info)[1].name = "eml_isa_uint";
  (*c3_b_info)[1].dominantType = "uint32";
  (*c3_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  (*c3_b_info)[1].fileTimeLo = 1286815184U;
  (*c3_b_info)[1].fileTimeHi = 0U;
  (*c3_b_info)[1].mFileTimeLo = 0U;
  (*c3_b_info)[1].mFileTimeHi = 0U;
  (*c3_b_info)[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  (*c3_b_info)[2].name = "eml_int_nbits";
  (*c3_b_info)[2].dominantType = "char";
  (*c3_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_nbits.m";
  (*c3_b_info)[2].fileTimeLo = 1286815180U;
  (*c3_b_info)[2].fileTimeHi = 0U;
  (*c3_b_info)[2].mFileTimeLo = 0U;
  (*c3_b_info)[2].mFileTimeHi = 0U;
  (*c3_b_info)[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  (*c3_b_info)[3].name = "eml_scalar_eg";
  (*c3_b_info)[3].dominantType = "uint32";
  (*c3_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  (*c3_b_info)[3].fileTimeLo = 1286815196U;
  (*c3_b_info)[3].fileTimeHi = 0U;
  (*c3_b_info)[3].mFileTimeLo = 0U;
  (*c3_b_info)[3].mFileTimeHi = 0U;
  (*c3_b_info)[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  (*c3_b_info)[4].name = "eml_scalexp_alloc";
  (*c3_b_info)[4].dominantType = "uint32";
  (*c3_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  (*c3_b_info)[4].fileTimeLo = 1286815196U;
  (*c3_b_info)[4].fileTimeHi = 0U;
  (*c3_b_info)[4].mFileTimeLo = 0U;
  (*c3_b_info)[4].mFileTimeHi = 0U;
  (*c3_b_info)[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  (*c3_b_info)[5].name = "floor";
  (*c3_b_info)[5].dominantType = "double";
  (*c3_b_info)[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  (*c3_b_info)[5].fileTimeLo = 1286815142U;
  (*c3_b_info)[5].fileTimeHi = 0U;
  (*c3_b_info)[5].mFileTimeLo = 0U;
  (*c3_b_info)[5].mFileTimeHi = 0U;
  (*c3_b_info)[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  (*c3_b_info)[6].name = "eml_scalar_floor";
  (*c3_b_info)[6].dominantType = "double";
  (*c3_b_info)[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  (*c3_b_info)[6].fileTimeLo = 1286815126U;
  (*c3_b_info)[6].fileTimeHi = 0U;
  (*c3_b_info)[6].mFileTimeLo = 0U;
  (*c3_b_info)[6].mFileTimeHi = 0U;
  (*c3_b_info)[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  (*c3_b_info)[7].name = "eml_error";
  (*c3_b_info)[7].dominantType = "char";
  (*c3_b_info)[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  (*c3_b_info)[7].fileTimeLo = 1286815100U;
  (*c3_b_info)[7].fileTimeHi = 0U;
  (*c3_b_info)[7].mFileTimeLo = 0U;
  (*c3_b_info)[7].mFileTimeHi = 0U;
  (*c3_b_info)[8].context = "";
  (*c3_b_info)[8].name = "mtimes";
  (*c3_b_info)[8].dominantType = "double";
  (*c3_b_info)[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c3_b_info)[8].fileTimeLo = 1289516092U;
  (*c3_b_info)[8].fileTimeHi = 0U;
  (*c3_b_info)[8].mFileTimeLo = 0U;
  (*c3_b_info)[8].mFileTimeHi = 0U;
  sf_mex_assign(&c3_m0, sf_mex_createstruct("nameCaptureInfo", 1, 9));
  for (c3_i0 = 0; c3_i0 < 9; c3_i0++) {
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

static real32_T c3_emlrt_marshallIn(SFc3_videoInstanceStruct *chartInstance,
  const mxArray *c3_bits, const char_T *c3_identifier)
{
  real32_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_bits), &c3_thisId);
  sf_mex_destroy(&c3_bits);
  return c3_y;
}

static real32_T c3_b_emlrt_marshallIn(SFc3_videoInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real32_T c3_y;
  real32_T c3_f1;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_f1, 1, 1, 0U, 0, 0U, 0);
  c3_y = c3_f1;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static uint8_T c3_c_emlrt_marshallIn(SFc3_videoInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_video, const char_T *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_is_active_c3_video),
    &c3_thisId);
  sf_mex_destroy(&c3_b_is_active_c3_video);
  return c3_y;
}

static uint8_T c3_d_emlrt_marshallIn(SFc3_videoInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void init_dsm_address_info(SFc3_videoInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c3_video_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1600306915U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1495527792U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1513878834U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(479429615U);
}

mxArray *sf_c3_video_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(369700648U);
    pr[1] = (double)(1587851934U);
    pr[2] = (double)(2132570060U);
    pr[3] = (double)(3684332082U);
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

static const mxArray *sf_get_sim_state_info_c3_video(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"bits\",},{M[8],M[0],T\"is_active_c3_video\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_video_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void sf_opaque_initialize_c3_video(void *chartInstanceVar)
{
  initialize_params_c3_video((SFc3_videoInstanceStruct*) chartInstanceVar);
  initialize_c3_video((SFc3_videoInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c3_video(void *chartInstanceVar)
{
  enable_c3_video((SFc3_videoInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_video(void *chartInstanceVar)
{
  disable_c3_video((SFc3_videoInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_video(void *chartInstanceVar)
{
  sf_c3_video((SFc3_videoInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c3_video(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_video((SFc3_videoInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_video();/* state var info */
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

extern void sf_internal_set_sim_state_c3_video(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_video();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_video((SFc3_videoInstanceStruct*)chartInfo->chartInstance,
    mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c3_video(SimStruct* S)
{
  return sf_internal_get_sim_state_c3_video(S);
}

static void sf_opaque_set_sim_state_c3_video(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c3_video(S, st);
}

static void sf_opaque_terminate_c3_video(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_videoInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c3_video((SFc3_videoInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_video((SFc3_videoInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_video(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_video((SFc3_videoInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_video(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"video","video",3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"video","video",3,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"video","video",3,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"video","video",3,1);
      sf_mark_chart_reusable_outputs(S,"video","video",3,1);
    }

    sf_set_rtw_dwork_info(S,"video","video",3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1598346204U));
  ssSetChecksum1(S,(2019632550U));
  ssSetChecksum2(S,(1930731327U));
  ssSetChecksum3(S,(665916620U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c3_video(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "video", "video",3);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_video(SimStruct *S)
{
  SFc3_videoInstanceStruct *chartInstance;
  chartInstance = (SFc3_videoInstanceStruct *)malloc(sizeof
    (SFc3_videoInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_videoInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_video;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c3_video;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_video;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_video;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_video;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c3_video;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c3_video;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c3_video;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_video;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_video;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_video;
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

void c3_video_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_video(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_video(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_video(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_video_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
