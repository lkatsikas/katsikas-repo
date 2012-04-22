/* Include files */

#include "blascompat32.h"
#include "video_sfun.h"
#include "c5_video.h"
#include "mwmathutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void initialize_c5_video(SFc5_videoInstanceStruct *chartInstance);
static void initialize_params_c5_video(SFc5_videoInstanceStruct *chartInstance);
static void enable_c5_video(SFc5_videoInstanceStruct *chartInstance);
static void disable_c5_video(SFc5_videoInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c5_video(SFc5_videoInstanceStruct
  *chartInstance);
static void set_sim_state_c5_video(SFc5_videoInstanceStruct *chartInstance,
  const mxArray *c5_st);
static void finalize_c5_video(SFc5_videoInstanceStruct *chartInstance);
static void sf_c5_video(SFc5_videoInstanceStruct *chartInstance);
static void initSimStructsc5_video(SFc5_videoInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber);
static void c5_info_helper(c5_ResolvedFunctionInfo c5_info[17]);
static void c5_getbits(SFc5_videoInstanceStruct *chartInstance, int32_T c5_cbits,
  real_T c5_inpos, uint32_T c5_Temp, uint32_T c5_in[20], uint32_T c5_val, real_T
  c5_bits, real_T *c5_flag, int32_T *c5_cbitsO, real_T *c5_inposO, uint32_T
  *c5_TempO, uint32_T *c5_valO);
static void c5_eml_error(SFc5_videoInstanceStruct *chartInstance);
static void c5_emlrt_marshallIn(SFc5_videoInstanceStruct *chartInstance, const
  mxArray *c5_out, const char_T *c5_identifier, real32_T c5_y[64]);
static void c5_b_emlrt_marshallIn(SFc5_videoInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, real32_T c5_y[64]);
static void c5_c_emlrt_marshallIn(SFc5_videoInstanceStruct *chartInstance, const
  mxArray *c5_b_prev_out, const char_T *c5_identifier, real32_T c5_y[64]);
static void c5_d_emlrt_marshallIn(SFc5_videoInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, real32_T c5_y[64]);
static uint8_T c5_e_emlrt_marshallIn(SFc5_videoInstanceStruct *chartInstance,
  const mxArray *c5_b_is_active_c5_video, const char_T *c5_identifier);
static uint8_T c5_f_emlrt_marshallIn(SFc5_videoInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void init_dsm_address_info(SFc5_videoInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c5_video(SFc5_videoInstanceStruct *chartInstance)
{
  int32_T c5_i0;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c5_prev_out_not_empty = FALSE;
  chartInstance->c5_is_active_c5_video = 0U;
  for (c5_i0 = 0; c5_i0 < 64; c5_i0++) {
    chartInstance->c5_prev_out[c5_i0] = 0.0F;
  }
}

static void initialize_params_c5_video(SFc5_videoInstanceStruct *chartInstance)
{
}

static void enable_c5_video(SFc5_videoInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c5_video(SFc5_videoInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static const mxArray *get_sim_state_c5_video(SFc5_videoInstanceStruct
  *chartInstance)
{
  const mxArray *c5_st;
  const mxArray *c5_y = NULL;
  int32_T c5_i1;
  real32_T c5_u[64];
  const mxArray *c5_b_y = NULL;
  real32_T c5_b_u[64];
  const mxArray *c5_c_y = NULL;
  uint8_T c5_c_u;
  const mxArray *c5_d_y = NULL;
  real32_T (*c5_out)[64];
  c5_out = (real32_T (*)[64])ssGetOutputPortSignal(chartInstance->S, 1);
  c5_st = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createcellarray(3));
  for (c5_i1 = 0; c5_i1 < 64; c5_i1++) {
    c5_u[c5_i1] = (*c5_out)[c5_i1];
  }

  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", c5_u, 1, 0U, 1U, 0U, 1, 64));
  sf_mex_setcell(c5_y, 0, c5_b_y);
  for (c5_i1 = 0; c5_i1 < 64; c5_i1++) {
    c5_b_u[c5_i1] = chartInstance->c5_prev_out[c5_i1];
  }

  c5_c_y = NULL;
  if (!chartInstance->c5_prev_out_not_empty) {
    sf_mex_assign(&c5_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c5_c_y, sf_mex_create("y", c5_b_u, 1, 0U, 1U, 0U, 1, 64));
  }

  sf_mex_setcell(c5_y, 1, c5_c_y);
  c5_c_u = chartInstance->c5_is_active_c5_video;
  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_c_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c5_y, 2, c5_d_y);
  sf_mex_assign(&c5_st, c5_y);
  return c5_st;
}

static void set_sim_state_c5_video(SFc5_videoInstanceStruct *chartInstance,
  const mxArray *c5_st)
{
  const mxArray *c5_u;
  real32_T c5_fv0[64];
  int32_T c5_i2;
  real32_T (*c5_out)[64];
  c5_out = (real32_T (*)[64])ssGetOutputPortSignal(chartInstance->S, 1);
  c5_u = sf_mex_dup(c5_st);
  c5_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 0)), "out",
                      c5_fv0);
  for (c5_i2 = 0; c5_i2 < 64; c5_i2++) {
    (*c5_out)[c5_i2] = c5_fv0[c5_i2];
  }

  c5_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 1)),
                        "prev_out", c5_fv0);
  for (c5_i2 = 0; c5_i2 < 64; c5_i2++) {
    chartInstance->c5_prev_out[c5_i2] = c5_fv0[c5_i2];
  }

  chartInstance->c5_is_active_c5_video = c5_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 2)), "is_active_c5_video");
  sf_mex_destroy(&c5_u);
  sf_mex_destroy(&c5_st);
}

static void finalize_c5_video(SFc5_videoInstanceStruct *chartInstance)
{
}

static void sf_c5_video(SFc5_videoInstanceStruct *chartInstance)
{
  int32_T c5_cbits;
  uint32_T c5_in[20];
  real32_T c5_out[64];
  int32_T c5_b_cbits;
  real_T c5_inpos;
  uint32_T c5_Temp;
  uint32_T c5_run;
  uint32_T c5_val;
  uint32_T c5_b_Temp;
  real_T c5_i;
  boolean_T c5_exitg1;
  uint32_T c5_b_run;
  real_T c5_b_inpos;
  real_T c5_flag;
  uint32_T c5_b_val;
  int32_T c5_j;
  real32_T (*c5_b_out)[64];
  uint32_T (*c5_b_in)[20];
  c5_b_out = (real32_T (*)[64])ssGetOutputPortSignal(chartInstance->S, 1);
  c5_b_in = (uint32_T (*)[20])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  for (c5_cbits = 0; c5_cbits < 20; c5_cbits++) {
    c5_in[c5_cbits] = (*c5_b_in)[c5_cbits];
  }

  chartInstance->c5_prev_out_not_empty = TRUE;
  for (c5_cbits = 0; c5_cbits < 64; c5_cbits++) {
    c5_out[c5_cbits] = chartInstance->c5_prev_out[c5_cbits];
  }

  c5_b_cbits = 0;
  c5_inpos = 2.0;
  c5_Temp = 0U;
  c5_run = 0U;
  c5_val = 0U;
  if (((*c5_b_in)[0] & 2147483648U) != 0U) {
    c5_b_Temp = MAX_uint32_T - (*c5_b_in)[0];
    if (c5_b_Temp > 2147483647U) {
      c5_b_Temp = 2147483647U;
    }

    c5_out[0] = (real32_T)(-(int32_T)c5_b_Temp - 1);
  } else {
    c5_b_Temp = (*c5_b_in)[0];
    if (c5_b_Temp > 2147483647U) {
      c5_b_Temp = 2147483647U;
    }

    c5_out[0] = (real32_T)c5_b_Temp;
  }

  c5_i = 2.0;
  c5_exitg1 = 0U;
  while ((c5_exitg1 == 0U) && (c5_i <= 64.0)) {
    c5_getbits(chartInstance, c5_b_cbits, c5_inpos, c5_Temp, c5_in, c5_run, 4.0,
               &c5_flag, &c5_cbits, &c5_b_inpos, &c5_b_Temp, &c5_b_run);
    c5_run = c5_b_run;
    if ((!(c5_flag != 0.0)) || (c5_b_run == 15U)) {
      c5_exitg1 = 1U;
    } else {
      c5_getbits(chartInstance, c5_cbits, c5_b_inpos, c5_b_Temp, c5_in, c5_val,
                 8.0, &c5_flag, &c5_b_cbits, &c5_inpos, &c5_Temp, &c5_b_val);
      c5_val = c5_b_val;
      if (!(c5_flag != 0.0)) {
        c5_exitg1 = 1U;
      } else {
        c5_flag = (real_T)c5_b_run + c5_i;
        c5_flag = muDoubleScalarFloor(c5_flag + 0.5);
        if (c5_flag < 4.294967296E+9) {
          c5_b_Temp = (uint32_T)c5_flag;
        } else {
          c5_b_Temp = MAX_uint32_T;
        }

        if (c5_b_Temp > 64U) {
          c5_cbits = 64;
        } else {
          c5_cbits = (int32_T)c5_b_Temp;
        }

        c5_j = (int32_T)c5_i;
        while ((uint32_T)c5_j <= (uint32_T)c5_cbits) {
          c5_out[c5_j - 1] = (real32_T)c5_b_val - 128.0F;
          c5_j = (int32_T)((uint32_T)c5_j + 1U);
          sf_mex_listen_for_ctrl_c(chartInstance->S);
        }

        c5_i = (c5_i + (real_T)c5_b_run) + 1.0;
        sf_mex_listen_for_ctrl_c(chartInstance->S);
      }
    }
  }

  while (c5_i <= 64.0) {
    c5_out[(int32_T)c5_i - 1] = 0.0F;
    c5_i++;
    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  for (c5_cbits = 0; c5_cbits < 64; c5_cbits++) {
    chartInstance->c5_prev_out[c5_cbits] = c5_out[c5_cbits];
    (*c5_b_out)[c5_cbits] = c5_out[c5_cbits];
  }
}

static void initSimStructsc5_video(SFc5_videoInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber)
{
}

const mxArray *sf_c5_video_get_eml_resolved_functions_info(void)
{
  const mxArray *c5_nameCaptureInfo;
  c5_ResolvedFunctionInfo c5_info[17];
  const mxArray *c5_m0 = NULL;
  int32_T c5_i3;
  c5_ResolvedFunctionInfo *c5_r0;
  c5_nameCaptureInfo = NULL;
  c5_info_helper(c5_info);
  sf_mex_assign(&c5_m0, sf_mex_createstruct("nameCaptureInfo", 1, 17));
  for (c5_i3 = 0; c5_i3 < 17; c5_i3++) {
    c5_r0 = &c5_info[c5_i3];
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", c5_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c5_r0->context)), "context", "nameCaptureInfo",
                    c5_i3);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", c5_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c5_r0->name)), "name", "nameCaptureInfo", c5_i3);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", c5_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c5_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c5_i3);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", c5_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c5_r0->resolved)), "resolved", "nameCaptureInfo",
                    c5_i3);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", &c5_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c5_i3);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", &c5_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c5_i3);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", &c5_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c5_i3);
    sf_mex_addfield(c5_m0, sf_mex_create("nameCaptureInfo", &c5_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c5_i3);
  }

  sf_mex_assign(&c5_nameCaptureInfo, c5_m0);
  return c5_nameCaptureInfo;
}

static void c5_info_helper(c5_ResolvedFunctionInfo c5_info[17])
{
  c5_info[0].context = "";
  c5_info[0].name = "bitget";
  c5_info[0].dominantType = "uint32";
  c5_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c5_info[0].fileTimeLo = 1286815236U;
  c5_info[0].fileTimeHi = 0U;
  c5_info[0].mFileTimeLo = 0U;
  c5_info[0].mFileTimeHi = 0U;
  c5_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c5_info[1].name = "eml_scalar_eg";
  c5_info[1].dominantType = "uint32";
  c5_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c5_info[1].fileTimeLo = 1286815196U;
  c5_info[1].fileTimeHi = 0U;
  c5_info[1].mFileTimeLo = 0U;
  c5_info[1].mFileTimeHi = 0U;
  c5_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c5_info[2].name = "eml_scalexp_alloc";
  c5_info[2].dominantType = "uint32";
  c5_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c5_info[2].fileTimeLo = 1286815196U;
  c5_info[2].fileTimeHi = 0U;
  c5_info[2].mFileTimeLo = 0U;
  c5_info[2].mFileTimeHi = 0U;
  c5_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c5_info[3].name = "eml_isa_uint";
  c5_info[3].dominantType = "uint32";
  c5_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  c5_info[3].fileTimeLo = 1286815184U;
  c5_info[3].fileTimeHi = 0U;
  c5_info[3].mFileTimeLo = 0U;
  c5_info[3].mFileTimeHi = 0U;
  c5_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c5_info[4].name = "eml_int_nbits";
  c5_info[4].dominantType = "char";
  c5_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_nbits.m";
  c5_info[4].fileTimeLo = 1286815180U;
  c5_info[4].fileTimeHi = 0U;
  c5_info[4].mFileTimeLo = 0U;
  c5_info[4].mFileTimeHi = 0U;
  c5_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c5_info[5].name = "floor";
  c5_info[5].dominantType = "double";
  c5_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c5_info[5].fileTimeLo = 1286815142U;
  c5_info[5].fileTimeHi = 0U;
  c5_info[5].mFileTimeLo = 0U;
  c5_info[5].mFileTimeHi = 0U;
  c5_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c5_info[6].name = "eml_scalar_floor";
  c5_info[6].dominantType = "double";
  c5_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c5_info[6].fileTimeLo = 1286815126U;
  c5_info[6].fileTimeHi = 0U;
  c5_info[6].mFileTimeLo = 0U;
  c5_info[6].mFileTimeHi = 0U;
  c5_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c5_info[7].name = "eml_error";
  c5_info[7].dominantType = "uint8";
  c5_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c5_info[7].fileTimeLo = 1286815100U;
  c5_info[7].fileTimeHi = 0U;
  c5_info[7].mFileTimeLo = 0U;
  c5_info[7].mFileTimeHi = 0U;
  c5_info[8].context = "";
  c5_info[8].name = "intmax";
  c5_info[8].dominantType = "char";
  c5_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c5_info[8].fileTimeLo = 1286815156U;
  c5_info[8].fileTimeHi = 0U;
  c5_info[8].mFileTimeLo = 0U;
  c5_info[8].mFileTimeHi = 0U;
  c5_info[9].context = "";
  c5_info[9].name = "length";
  c5_info[9].dominantType = "uint32";
  c5_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c5_info[9].fileTimeLo = 1286815160U;
  c5_info[9].fileTimeHi = 0U;
  c5_info[9].mFileTimeLo = 0U;
  c5_info[9].mFileTimeHi = 0U;
  c5_info[10].context = "";
  c5_info[10].name = "bitshift";
  c5_info[10].dominantType = "uint32";
  c5_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c5_info[10].fileTimeLo = 1286815238U;
  c5_info[10].fileTimeHi = 0U;
  c5_info[10].mFileTimeLo = 0U;
  c5_info[10].mFileTimeHi = 0U;
  c5_info[11].context = "";
  c5_info[11].name = "bitor";
  c5_info[11].dominantType = "uint32";
  c5_info[11].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitor.m";
  c5_info[11].fileTimeLo = 1286815236U;
  c5_info[11].fileTimeHi = 0U;
  c5_info[11].mFileTimeLo = 0U;
  c5_info[11].mFileTimeHi = 0U;
  c5_info[12].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitor.m";
  c5_info[12].name = "eml_scalexp_compatible";
  c5_info[12].dominantType = "uint32";
  c5_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c5_info[12].fileTimeLo = 1286815196U;
  c5_info[12].fileTimeHi = 0U;
  c5_info[12].mFileTimeLo = 0U;
  c5_info[12].mFileTimeHi = 0U;
  c5_info[13].context = "";
  c5_info[13].name = "min";
  c5_info[13].dominantType = "uint32";
  c5_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c5_info[13].fileTimeLo = 1286815096U;
  c5_info[13].fileTimeHi = 0U;
  c5_info[13].mFileTimeLo = 0U;
  c5_info[13].mFileTimeHi = 0U;
  c5_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c5_info[14].name = "eml_min_or_max";
  c5_info[14].dominantType = "uint32";
  c5_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c5_info[14].fileTimeLo = 1286815188U;
  c5_info[14].fileTimeHi = 0U;
  c5_info[14].mFileTimeLo = 0U;
  c5_info[14].mFileTimeHi = 0U;
  c5_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c5_info[15].name = "eml_index_class";
  c5_info[15].dominantType = "";
  c5_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c5_info[15].fileTimeLo = 1286815178U;
  c5_info[15].fileTimeHi = 0U;
  c5_info[15].mFileTimeLo = 0U;
  c5_info[15].mFileTimeHi = 0U;
  c5_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c5_info[16].name = "isnan";
  c5_info[16].dominantType = "uint32";
  c5_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c5_info[16].fileTimeLo = 1286815160U;
  c5_info[16].fileTimeHi = 0U;
  c5_info[16].mFileTimeLo = 0U;
  c5_info[16].mFileTimeHi = 0U;
}

static void c5_getbits(SFc5_videoInstanceStruct *chartInstance, int32_T c5_cbits,
  real_T c5_inpos, uint32_T c5_Temp, uint32_T c5_in[20], uint32_T c5_val, real_T
  c5_bits, real_T *c5_flag, int32_T *c5_cbitsO, real_T *c5_inposO, uint32_T
  *c5_TempO, uint32_T *c5_valO)
{
  uint32_T c5_lval;
  boolean_T c5_guard1 = FALSE;
  int64_T c5_i4;
  int32_T c5_k;
  uint8_T c5_absk1;
  real_T c5_b_k;
  uint32_T c5_a;
  uint32_T c5_temp;
  c5_lval = 0U;
  *c5_cbitsO = c5_cbits;
  *c5_inposO = c5_inpos;
  *c5_TempO = c5_Temp;
  *c5_valO = c5_val;
  c5_guard1 = FALSE;
  if ((real_T)c5_cbits < c5_bits) {
    if (c5_inpos > 20.0) {
      *c5_flag = 0.0;
    } else {
      c5_i4 = (int64_T)32 - (int64_T)c5_cbits;
      if (c5_i4 > 2147483647L) {
        c5_i4 = 2147483647L;
      } else {
        if (c5_i4 <= -2147483648L) {
          c5_i4 = -2147483648L;
        }
      }

      c5_k = -(int32_T)c5_i4;
      if (c5_k < 0) {
        c5_k = -c5_k;
        if (c5_k <= 0) {
          c5_k = 0;
        } else {
          if (c5_k > 255) {
            c5_k = 255;
          }
        }

        c5_absk1 = (uint8_T)c5_k;
        if (c5_absk1 < 32) {
          c5_lval = c5_Temp >> (uint32_T)c5_absk1;
        }
      } else {
        if (c5_k <= 0) {
          c5_k = 0;
        } else {
          if (c5_k > 255) {
            c5_k = 255;
          }
        }

        c5_absk1 = (uint8_T)c5_k;
        if (c5_absk1 < 32) {
          c5_lval = c5_Temp << (uint32_T)c5_absk1;
        }
      }

      c5_b_k = c5_bits - (real_T)c5_cbits;
      c5_b_k = c5_b_k < 0.0 ? muDoubleScalarCeil(c5_b_k - 0.5) :
        muDoubleScalarFloor(c5_b_k + 0.5);
      if (c5_b_k < 2.147483648E+9) {
        if (c5_b_k >= -2.147483648E+9) {
          c5_k = (int32_T)c5_b_k;
        } else {
          c5_k = MIN_int32_T;
        }
      } else {
        c5_k = MAX_int32_T;
      }

      c5_bits = (real_T)c5_k;
      *c5_TempO = c5_in[sf_mex_lw_bounds_check((int32_T)c5_inpos, 1, 20) - 1];
      *c5_inposO = c5_inpos + 1.0;
      c5_a = c5_lval;
      if (c5_bits != c5_bits) {
        c5_eml_error(chartInstance);
      }

      c5_lval = 0U;
      if (c5_bits < 0.0) {
        c5_temp = (uint32_T)-c5_bits;
        c5_temp = (uint32_T)muDoubleScalarFloor((real_T)c5_temp + 0.5);
        if (c5_temp < 256U) {
          c5_absk1 = (uint8_T)c5_temp;
        } else {
          c5_absk1 = MAX_uint8_T;
        }

        if (c5_absk1 < 32) {
          c5_lval = c5_a >> (uint32_T)c5_absk1;
        }
      } else {
        c5_k = (int32_T)c5_bits;
        c5_k = (int32_T)muDoubleScalarFloor((real_T)c5_k + 0.5);
        if (c5_k < 256) {
          c5_absk1 = (uint8_T)c5_k;
        } else {
          c5_absk1 = MAX_uint8_T;
        }

        if (c5_absk1 < 32) {
          c5_lval = c5_a << (uint32_T)c5_absk1;
        }
      }

      *c5_cbitsO = 32;
      c5_guard1 = TRUE;
    }
  } else {
    c5_guard1 = TRUE;
  }

  if (c5_guard1 == TRUE) {
    c5_b_k = -(32.0 - c5_bits);
    if (c5_b_k != muDoubleScalarFloor(c5_b_k)) {
      c5_eml_error(chartInstance);
    }

    c5_temp = 0U;
    if (c5_b_k < 0.0) {
      c5_b_k = -c5_b_k;
      c5_b_k = muDoubleScalarFloor(c5_b_k + 0.5);
      if (c5_b_k < 256.0) {
        c5_absk1 = (uint8_T)c5_b_k;
      } else {
        c5_absk1 = MAX_uint8_T;
      }

      if (c5_absk1 < 32) {
        c5_temp = *c5_TempO >> (uint32_T)c5_absk1;
      }
    } else {
      c5_b_k = muDoubleScalarFloor(c5_b_k + 0.5);
      if (c5_b_k < 256.0) {
        c5_absk1 = (uint8_T)c5_b_k;
      } else if (c5_b_k >= 256.0) {
        c5_absk1 = MAX_uint8_T;
      } else {
        c5_absk1 = 0U;
      }

      if (c5_absk1 < 32) {
        c5_temp = *c5_TempO << (uint32_T)c5_absk1;
      }
    }

    c5_a = *c5_TempO;
    if (c5_bits != muDoubleScalarFloor(c5_bits)) {
      c5_eml_error(chartInstance);
    }

    *c5_TempO = 0U;
    if (c5_bits < 0.0) {
      c5_b_k = -c5_bits;
      c5_b_k = muDoubleScalarFloor(c5_b_k + 0.5);
      if (c5_b_k < 256.0) {
        c5_absk1 = (uint8_T)c5_b_k;
      } else {
        c5_absk1 = MAX_uint8_T;
      }

      if (c5_absk1 < 32) {
        *c5_TempO = c5_a >> (uint32_T)c5_absk1;
      }
    } else {
      c5_b_k = c5_bits;
      c5_b_k = muDoubleScalarFloor(c5_b_k + 0.5);
      if (c5_b_k < 256.0) {
        c5_absk1 = (uint8_T)c5_b_k;
      } else if (c5_b_k >= 256.0) {
        c5_absk1 = MAX_uint8_T;
      } else {
        c5_absk1 = 0U;
      }

      if (c5_absk1 < 32) {
        *c5_TempO = c5_a << (uint32_T)c5_absk1;
      }
    }

    *c5_valO = c5_lval | c5_temp;
    c5_b_k = (real_T)*c5_cbitsO - c5_bits;
    c5_b_k = c5_b_k < 0.0 ? muDoubleScalarCeil(c5_b_k - 0.5) :
      muDoubleScalarFloor(c5_b_k + 0.5);
    if (c5_b_k < 2.147483648E+9) {
      if (c5_b_k >= -2.147483648E+9) {
        *c5_cbitsO = (int32_T)c5_b_k;
      } else {
        *c5_cbitsO = MIN_int32_T;
      }
    } else if (c5_b_k >= 2.147483648E+9) {
      *c5_cbitsO = MAX_int32_T;
    } else {
      *c5_cbitsO = 0;
    }

    *c5_flag = 1.0;
  }
}

static void c5_eml_error(SFc5_videoInstanceStruct *chartInstance)
{
  int32_T c5_i5;
  static char_T c5_varargin_1[42] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'b', 'i', 't', 's', 'h', 'i', 'f', 't', '_', 'i',
    'n', 'p', 'u', 't', 's', 'M', 'u', 's', 't', 'B', 'e', 'I', 'n', 't', 'e',
    'g', 'e', 'r', 's' };

  char_T c5_u[42];
  const mxArray *c5_y = NULL;
  for (c5_i5 = 0; c5_i5 < 42; c5_i5++) {
    c5_u[c5_i5] = c5_varargin_1[c5_i5];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 10, 0U, 1U, 0U, 2, 1, 42));
  sf_mex_call("error", 0U, 1U, 14, sf_mex_call("message", 1U, 1U, 14, c5_y));
}

static void c5_emlrt_marshallIn(SFc5_videoInstanceStruct *chartInstance, const
  mxArray *c5_out, const char_T *c5_identifier, real32_T c5_y[64])
{
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_out), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_out);
}

static void c5_b_emlrt_marshallIn(SFc5_videoInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, real32_T c5_y[64])
{
  real32_T c5_fv1[64];
  int32_T c5_i6;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_fv1, 1, 1, 0U, 1, 0U, 1, 64);
  for (c5_i6 = 0; c5_i6 < 64; c5_i6++) {
    c5_y[c5_i6] = c5_fv1[c5_i6];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_c_emlrt_marshallIn(SFc5_videoInstanceStruct *chartInstance, const
  mxArray *c5_b_prev_out, const char_T *c5_identifier, real32_T c5_y[64])
{
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_prev_out), &c5_thisId,
                        c5_y);
  sf_mex_destroy(&c5_b_prev_out);
}

static void c5_d_emlrt_marshallIn(SFc5_videoInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, real32_T c5_y[64])
{
  real32_T c5_fv2[64];
  int32_T c5_i7;
  if (mxIsEmpty(c5_u)) {
    chartInstance->c5_prev_out_not_empty = FALSE;
  } else {
    chartInstance->c5_prev_out_not_empty = TRUE;
    sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_fv2, 1, 1, 0U, 1, 0U, 1, 64);
    for (c5_i7 = 0; c5_i7 < 64; c5_i7++) {
      c5_y[c5_i7] = c5_fv2[c5_i7];
    }
  }

  sf_mex_destroy(&c5_u);
}

static uint8_T c5_e_emlrt_marshallIn(SFc5_videoInstanceStruct *chartInstance,
  const mxArray *c5_b_is_active_c5_video, const char_T *c5_identifier)
{
  uint8_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_is_active_c5_video),
    &c5_thisId);
  sf_mex_destroy(&c5_b_is_active_c5_video);
  return c5_y;
}

static uint8_T c5_f_emlrt_marshallIn(SFc5_videoInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint8_T c5_y;
  uint8_T c5_u0;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u0, 1, 3, 0U, 0, 0U, 0);
  c5_y = c5_u0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void init_dsm_address_info(SFc5_videoInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c5_video_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1433736736U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(530681178U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3258148491U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4065504135U);
}

mxArray *sf_c5_video_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(574566818U);
    pr[1] = (double)(3381398915U);
    pr[2] = (double)(1036735490U);
    pr[3] = (double)(2140464582U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(20);
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

static const mxArray *sf_get_sim_state_info_c5_video(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"out\",},{M[4],M[0],T\"prev_out\",S'l','i','p'{{M1x2[188 196],M[0],}}},{M[8],M[0],T\"is_active_c5_video\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c5_video_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void sf_opaque_initialize_c5_video(void *chartInstanceVar)
{
  initialize_params_c5_video((SFc5_videoInstanceStruct*) chartInstanceVar);
  initialize_c5_video((SFc5_videoInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c5_video(void *chartInstanceVar)
{
  enable_c5_video((SFc5_videoInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c5_video(void *chartInstanceVar)
{
  disable_c5_video((SFc5_videoInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c5_video(void *chartInstanceVar)
{
  sf_c5_video((SFc5_videoInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c5_video(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c5_video((SFc5_videoInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c5_video();/* state var info */
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

extern void sf_internal_set_sim_state_c5_video(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c5_video();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c5_video((SFc5_videoInstanceStruct*)chartInfo->chartInstance,
    mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c5_video(SimStruct* S)
{
  return sf_internal_get_sim_state_c5_video(S);
}

static void sf_opaque_set_sim_state_c5_video(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c5_video(S, st);
}

static void sf_opaque_terminate_c5_video(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc5_videoInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c5_video((SFc5_videoInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc5_video((SFc5_videoInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c5_video(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c5_video((SFc5_videoInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c5_video(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"video","video",5);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"video","video",5,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"video","video",5,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"video","video",5,1);
      sf_mark_chart_reusable_outputs(S,"video","video",5,1);
    }

    sf_set_rtw_dwork_info(S,"video","video",5);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(640156352U));
  ssSetChecksum1(S,(2953723829U));
  ssSetChecksum2(S,(951268444U));
  ssSetChecksum3(S,(2236278499U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c5_video(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "video", "video",5);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c5_video(SimStruct *S)
{
  SFc5_videoInstanceStruct *chartInstance;
  chartInstance = (SFc5_videoInstanceStruct *)malloc(sizeof
    (SFc5_videoInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc5_videoInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c5_video;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c5_video;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c5_video;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c5_video;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c5_video;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c5_video;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c5_video;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c5_video;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c5_video;
  chartInstance->chartInfo.mdlStart = mdlStart_c5_video;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c5_video;
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

void c5_video_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c5_video(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c5_video(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c5_video(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c5_video_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
