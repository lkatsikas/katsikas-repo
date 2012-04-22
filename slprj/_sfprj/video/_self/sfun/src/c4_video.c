/* Include files */

#include "blascompat32.h"
#include "video_sfun.h"
#include "c4_video.h"
#include "mwmathutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void initialize_c4_video(SFc4_videoInstanceStruct *chartInstance);
static void initialize_params_c4_video(SFc4_videoInstanceStruct *chartInstance);
static void enable_c4_video(SFc4_videoInstanceStruct *chartInstance);
static void disable_c4_video(SFc4_videoInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c4_video(SFc4_videoInstanceStruct
  *chartInstance);
static void set_sim_state_c4_video(SFc4_videoInstanceStruct *chartInstance,
  const mxArray *c4_st);
static void finalize_c4_video(SFc4_videoInstanceStruct *chartInstance);
static void sf_c4_video(SFc4_videoInstanceStruct *chartInstance);
static void initSimStructsc4_video(SFc4_videoInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber);
static void c4_info_helper(c4_ResolvedFunctionInfo c4_info[17]);
static void c4_getbits(SFc4_videoInstanceStruct *chartInstance, int32_T c4_cbits,
  real_T c4_inpos, uint32_T c4_Temp, uint32_T c4_in[20], uint32_T c4_val, real_T
  c4_bits, real_T *c4_flag, int32_T *c4_cbitsO, real_T *c4_inposO, uint32_T
  *c4_TempO, uint32_T *c4_valO);
static void c4_eml_error(SFc4_videoInstanceStruct *chartInstance);
static void c4_emlrt_marshallIn(SFc4_videoInstanceStruct *chartInstance, const
  mxArray *c4_out, const char_T *c4_identifier, real32_T c4_y[64]);
static void c4_b_emlrt_marshallIn(SFc4_videoInstanceStruct *chartInstance, const
  mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real32_T c4_y[64]);
static void c4_c_emlrt_marshallIn(SFc4_videoInstanceStruct *chartInstance, const
  mxArray *c4_b_prev_out, const char_T *c4_identifier, real32_T c4_y[64]);
static void c4_d_emlrt_marshallIn(SFc4_videoInstanceStruct *chartInstance, const
  mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real32_T c4_y[64]);
static uint8_T c4_e_emlrt_marshallIn(SFc4_videoInstanceStruct *chartInstance,
  const mxArray *c4_b_is_active_c4_video, const char_T *c4_identifier);
static uint8_T c4_f_emlrt_marshallIn(SFc4_videoInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void init_dsm_address_info(SFc4_videoInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c4_video(SFc4_videoInstanceStruct *chartInstance)
{
  int32_T c4_i0;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c4_prev_out_not_empty = FALSE;
  chartInstance->c4_is_active_c4_video = 0U;
  for (c4_i0 = 0; c4_i0 < 64; c4_i0++) {
    chartInstance->c4_prev_out[c4_i0] = 0.0F;
  }
}

static void initialize_params_c4_video(SFc4_videoInstanceStruct *chartInstance)
{
}

static void enable_c4_video(SFc4_videoInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c4_video(SFc4_videoInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static const mxArray *get_sim_state_c4_video(SFc4_videoInstanceStruct
  *chartInstance)
{
  const mxArray *c4_st;
  const mxArray *c4_y = NULL;
  int32_T c4_i1;
  real32_T c4_u[64];
  const mxArray *c4_b_y = NULL;
  real32_T c4_b_u[64];
  const mxArray *c4_c_y = NULL;
  uint8_T c4_c_u;
  const mxArray *c4_d_y = NULL;
  real32_T (*c4_out)[64];
  c4_out = (real32_T (*)[64])ssGetOutputPortSignal(chartInstance->S, 1);
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellarray(3));
  for (c4_i1 = 0; c4_i1 < 64; c4_i1++) {
    c4_u[c4_i1] = (*c4_out)[c4_i1];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_u, 1, 0U, 1U, 0U, 1, 64));
  sf_mex_setcell(c4_y, 0, c4_b_y);
  for (c4_i1 = 0; c4_i1 < 64; c4_i1++) {
    c4_b_u[c4_i1] = chartInstance->c4_prev_out[c4_i1];
  }

  c4_c_y = NULL;
  if (!chartInstance->c4_prev_out_not_empty) {
    sf_mex_assign(&c4_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c4_c_y, sf_mex_create("y", c4_b_u, 1, 0U, 1U, 0U, 1, 64));
  }

  sf_mex_setcell(c4_y, 1, c4_c_y);
  c4_c_u = chartInstance->c4_is_active_c4_video;
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_c_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c4_y, 2, c4_d_y);
  sf_mex_assign(&c4_st, c4_y);
  return c4_st;
}

static void set_sim_state_c4_video(SFc4_videoInstanceStruct *chartInstance,
  const mxArray *c4_st)
{
  const mxArray *c4_u;
  real32_T c4_fv0[64];
  int32_T c4_i2;
  real32_T (*c4_out)[64];
  c4_out = (real32_T (*)[64])ssGetOutputPortSignal(chartInstance->S, 1);
  c4_u = sf_mex_dup(c4_st);
  c4_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 0)), "out",
                      c4_fv0);
  for (c4_i2 = 0; c4_i2 < 64; c4_i2++) {
    (*c4_out)[c4_i2] = c4_fv0[c4_i2];
  }

  c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 1)),
                        "prev_out", c4_fv0);
  for (c4_i2 = 0; c4_i2 < 64; c4_i2++) {
    chartInstance->c4_prev_out[c4_i2] = c4_fv0[c4_i2];
  }

  chartInstance->c4_is_active_c4_video = c4_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c4_u, 2)), "is_active_c4_video");
  sf_mex_destroy(&c4_u);
  sf_mex_destroy(&c4_st);
}

static void finalize_c4_video(SFc4_videoInstanceStruct *chartInstance)
{
}

static void sf_c4_video(SFc4_videoInstanceStruct *chartInstance)
{
  int32_T c4_cbits;
  uint32_T c4_in[20];
  real32_T c4_out[64];
  int32_T c4_b_cbits;
  real_T c4_inpos;
  uint32_T c4_Temp;
  uint32_T c4_run;
  uint32_T c4_val;
  uint32_T c4_b_Temp;
  real_T c4_i;
  boolean_T c4_exitg1;
  uint32_T c4_b_run;
  real_T c4_b_inpos;
  real_T c4_flag;
  uint32_T c4_b_val;
  int32_T c4_j;
  real32_T (*c4_b_out)[64];
  uint32_T (*c4_b_in)[20];
  c4_b_out = (real32_T (*)[64])ssGetOutputPortSignal(chartInstance->S, 1);
  c4_b_in = (uint32_T (*)[20])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  for (c4_cbits = 0; c4_cbits < 20; c4_cbits++) {
    c4_in[c4_cbits] = (*c4_b_in)[c4_cbits];
  }

  chartInstance->c4_prev_out_not_empty = TRUE;
  for (c4_cbits = 0; c4_cbits < 64; c4_cbits++) {
    c4_out[c4_cbits] = chartInstance->c4_prev_out[c4_cbits];
  }

  c4_b_cbits = 0;
  c4_inpos = 2.0;
  c4_Temp = 0U;
  c4_run = 0U;
  c4_val = 0U;
  if (((*c4_b_in)[0] & 2147483648U) != 0U) {
    c4_b_Temp = MAX_uint32_T - (*c4_b_in)[0];
    if (c4_b_Temp > 2147483647U) {
      c4_b_Temp = 2147483647U;
    }

    c4_out[0] = (real32_T)(-(int32_T)c4_b_Temp - 1);
  } else {
    c4_b_Temp = (*c4_b_in)[0];
    if (c4_b_Temp > 2147483647U) {
      c4_b_Temp = 2147483647U;
    }

    c4_out[0] = (real32_T)c4_b_Temp;
  }

  c4_i = 2.0;
  c4_exitg1 = 0U;
  while ((c4_exitg1 == 0U) && (c4_i <= 64.0)) {
    c4_getbits(chartInstance, c4_b_cbits, c4_inpos, c4_Temp, c4_in, c4_run, 4.0,
               &c4_flag, &c4_cbits, &c4_b_inpos, &c4_b_Temp, &c4_b_run);
    c4_run = c4_b_run;
    if ((!(c4_flag != 0.0)) || (c4_b_run == 15U)) {
      c4_exitg1 = 1U;
    } else {
      c4_getbits(chartInstance, c4_cbits, c4_b_inpos, c4_b_Temp, c4_in, c4_val,
                 8.0, &c4_flag, &c4_b_cbits, &c4_inpos, &c4_Temp, &c4_b_val);
      c4_val = c4_b_val;
      if (!(c4_flag != 0.0)) {
        c4_exitg1 = 1U;
      } else {
        c4_flag = (real_T)c4_b_run + c4_i;
        c4_flag = muDoubleScalarFloor(c4_flag + 0.5);
        if (c4_flag < 4.294967296E+9) {
          c4_b_Temp = (uint32_T)c4_flag;
        } else {
          c4_b_Temp = MAX_uint32_T;
        }

        if (c4_b_Temp > 64U) {
          c4_cbits = 64;
        } else {
          c4_cbits = (int32_T)c4_b_Temp;
        }

        c4_j = (int32_T)c4_i;
        while ((uint32_T)c4_j <= (uint32_T)c4_cbits) {
          c4_out[c4_j - 1] = (real32_T)c4_b_val - 128.0F;
          c4_j = (int32_T)((uint32_T)c4_j + 1U);
          sf_mex_listen_for_ctrl_c(chartInstance->S);
        }

        c4_i = (c4_i + (real_T)c4_b_run) + 1.0;
        sf_mex_listen_for_ctrl_c(chartInstance->S);
      }
    }
  }

  while (c4_i <= 64.0) {
    c4_out[(int32_T)c4_i - 1] = 0.0F;
    c4_i++;
    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  for (c4_cbits = 0; c4_cbits < 64; c4_cbits++) {
    chartInstance->c4_prev_out[c4_cbits] = c4_out[c4_cbits];
    (*c4_b_out)[c4_cbits] = c4_out[c4_cbits];
  }
}

static void initSimStructsc4_video(SFc4_videoInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber)
{
}

const mxArray *sf_c4_video_get_eml_resolved_functions_info(void)
{
  const mxArray *c4_nameCaptureInfo;
  c4_ResolvedFunctionInfo c4_info[17];
  const mxArray *c4_m0 = NULL;
  int32_T c4_i3;
  c4_ResolvedFunctionInfo *c4_r0;
  c4_nameCaptureInfo = NULL;
  c4_info_helper(c4_info);
  sf_mex_assign(&c4_m0, sf_mex_createstruct("nameCaptureInfo", 1, 17));
  for (c4_i3 = 0; c4_i3 < 17; c4_i3++) {
    c4_r0 = &c4_info[c4_i3];
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c4_r0->context)), "context", "nameCaptureInfo",
                    c4_i3);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c4_r0->name)), "name", "nameCaptureInfo", c4_i3);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c4_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c4_i3);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c4_r0->resolved)), "resolved", "nameCaptureInfo",
                    c4_i3);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c4_i3);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c4_i3);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c4_i3);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c4_i3);
  }

  sf_mex_assign(&c4_nameCaptureInfo, c4_m0);
  return c4_nameCaptureInfo;
}

static void c4_info_helper(c4_ResolvedFunctionInfo c4_info[17])
{
  c4_info[0].context = "";
  c4_info[0].name = "bitget";
  c4_info[0].dominantType = "uint32";
  c4_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c4_info[0].fileTimeLo = 1286815236U;
  c4_info[0].fileTimeHi = 0U;
  c4_info[0].mFileTimeLo = 0U;
  c4_info[0].mFileTimeHi = 0U;
  c4_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c4_info[1].name = "eml_scalar_eg";
  c4_info[1].dominantType = "uint32";
  c4_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c4_info[1].fileTimeLo = 1286815196U;
  c4_info[1].fileTimeHi = 0U;
  c4_info[1].mFileTimeLo = 0U;
  c4_info[1].mFileTimeHi = 0U;
  c4_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c4_info[2].name = "eml_scalexp_alloc";
  c4_info[2].dominantType = "uint32";
  c4_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c4_info[2].fileTimeLo = 1286815196U;
  c4_info[2].fileTimeHi = 0U;
  c4_info[2].mFileTimeLo = 0U;
  c4_info[2].mFileTimeHi = 0U;
  c4_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c4_info[3].name = "eml_isa_uint";
  c4_info[3].dominantType = "uint32";
  c4_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  c4_info[3].fileTimeLo = 1286815184U;
  c4_info[3].fileTimeHi = 0U;
  c4_info[3].mFileTimeLo = 0U;
  c4_info[3].mFileTimeHi = 0U;
  c4_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c4_info[4].name = "eml_int_nbits";
  c4_info[4].dominantType = "char";
  c4_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_nbits.m";
  c4_info[4].fileTimeLo = 1286815180U;
  c4_info[4].fileTimeHi = 0U;
  c4_info[4].mFileTimeLo = 0U;
  c4_info[4].mFileTimeHi = 0U;
  c4_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c4_info[5].name = "floor";
  c4_info[5].dominantType = "double";
  c4_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c4_info[5].fileTimeLo = 1286815142U;
  c4_info[5].fileTimeHi = 0U;
  c4_info[5].mFileTimeLo = 0U;
  c4_info[5].mFileTimeHi = 0U;
  c4_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c4_info[6].name = "eml_scalar_floor";
  c4_info[6].dominantType = "double";
  c4_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c4_info[6].fileTimeLo = 1286815126U;
  c4_info[6].fileTimeHi = 0U;
  c4_info[6].mFileTimeLo = 0U;
  c4_info[6].mFileTimeHi = 0U;
  c4_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitget.m";
  c4_info[7].name = "eml_error";
  c4_info[7].dominantType = "uint8";
  c4_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c4_info[7].fileTimeLo = 1286815100U;
  c4_info[7].fileTimeHi = 0U;
  c4_info[7].mFileTimeLo = 0U;
  c4_info[7].mFileTimeHi = 0U;
  c4_info[8].context = "";
  c4_info[8].name = "intmax";
  c4_info[8].dominantType = "char";
  c4_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c4_info[8].fileTimeLo = 1286815156U;
  c4_info[8].fileTimeHi = 0U;
  c4_info[8].mFileTimeLo = 0U;
  c4_info[8].mFileTimeHi = 0U;
  c4_info[9].context = "";
  c4_info[9].name = "length";
  c4_info[9].dominantType = "uint32";
  c4_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c4_info[9].fileTimeLo = 1286815160U;
  c4_info[9].fileTimeHi = 0U;
  c4_info[9].mFileTimeLo = 0U;
  c4_info[9].mFileTimeHi = 0U;
  c4_info[10].context = "";
  c4_info[10].name = "bitshift";
  c4_info[10].dominantType = "uint32";
  c4_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c4_info[10].fileTimeLo = 1286815238U;
  c4_info[10].fileTimeHi = 0U;
  c4_info[10].mFileTimeLo = 0U;
  c4_info[10].mFileTimeHi = 0U;
  c4_info[11].context = "";
  c4_info[11].name = "bitor";
  c4_info[11].dominantType = "uint32";
  c4_info[11].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitor.m";
  c4_info[11].fileTimeLo = 1286815236U;
  c4_info[11].fileTimeHi = 0U;
  c4_info[11].mFileTimeLo = 0U;
  c4_info[11].mFileTimeHi = 0U;
  c4_info[12].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitor.m";
  c4_info[12].name = "eml_scalexp_compatible";
  c4_info[12].dominantType = "uint32";
  c4_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c4_info[12].fileTimeLo = 1286815196U;
  c4_info[12].fileTimeHi = 0U;
  c4_info[12].mFileTimeLo = 0U;
  c4_info[12].mFileTimeHi = 0U;
  c4_info[13].context = "";
  c4_info[13].name = "min";
  c4_info[13].dominantType = "uint32";
  c4_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c4_info[13].fileTimeLo = 1286815096U;
  c4_info[13].fileTimeHi = 0U;
  c4_info[13].mFileTimeLo = 0U;
  c4_info[13].mFileTimeHi = 0U;
  c4_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c4_info[14].name = "eml_min_or_max";
  c4_info[14].dominantType = "uint32";
  c4_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c4_info[14].fileTimeLo = 1286815188U;
  c4_info[14].fileTimeHi = 0U;
  c4_info[14].mFileTimeLo = 0U;
  c4_info[14].mFileTimeHi = 0U;
  c4_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c4_info[15].name = "eml_index_class";
  c4_info[15].dominantType = "";
  c4_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[15].fileTimeLo = 1286815178U;
  c4_info[15].fileTimeHi = 0U;
  c4_info[15].mFileTimeLo = 0U;
  c4_info[15].mFileTimeHi = 0U;
  c4_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c4_info[16].name = "isnan";
  c4_info[16].dominantType = "uint32";
  c4_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c4_info[16].fileTimeLo = 1286815160U;
  c4_info[16].fileTimeHi = 0U;
  c4_info[16].mFileTimeLo = 0U;
  c4_info[16].mFileTimeHi = 0U;
}

static void c4_getbits(SFc4_videoInstanceStruct *chartInstance, int32_T c4_cbits,
  real_T c4_inpos, uint32_T c4_Temp, uint32_T c4_in[20], uint32_T c4_val, real_T
  c4_bits, real_T *c4_flag, int32_T *c4_cbitsO, real_T *c4_inposO, uint32_T
  *c4_TempO, uint32_T *c4_valO)
{
  uint32_T c4_lval;
  boolean_T c4_guard1 = FALSE;
  int64_T c4_i4;
  int32_T c4_k;
  uint8_T c4_absk1;
  real_T c4_b_k;
  uint32_T c4_a;
  uint32_T c4_temp;
  c4_lval = 0U;
  *c4_cbitsO = c4_cbits;
  *c4_inposO = c4_inpos;
  *c4_TempO = c4_Temp;
  *c4_valO = c4_val;
  c4_guard1 = FALSE;
  if ((real_T)c4_cbits < c4_bits) {
    if (c4_inpos > 20.0) {
      *c4_flag = 0.0;
    } else {
      c4_i4 = (int64_T)32 - (int64_T)c4_cbits;
      if (c4_i4 > 2147483647L) {
        c4_i4 = 2147483647L;
      } else {
        if (c4_i4 <= -2147483648L) {
          c4_i4 = -2147483648L;
        }
      }

      c4_k = -(int32_T)c4_i4;
      if (c4_k < 0) {
        c4_k = -c4_k;
        if (c4_k <= 0) {
          c4_k = 0;
        } else {
          if (c4_k > 255) {
            c4_k = 255;
          }
        }

        c4_absk1 = (uint8_T)c4_k;
        if (c4_absk1 < 32) {
          c4_lval = c4_Temp >> (uint32_T)c4_absk1;
        }
      } else {
        if (c4_k <= 0) {
          c4_k = 0;
        } else {
          if (c4_k > 255) {
            c4_k = 255;
          }
        }

        c4_absk1 = (uint8_T)c4_k;
        if (c4_absk1 < 32) {
          c4_lval = c4_Temp << (uint32_T)c4_absk1;
        }
      }

      c4_b_k = c4_bits - (real_T)c4_cbits;
      c4_b_k = c4_b_k < 0.0 ? muDoubleScalarCeil(c4_b_k - 0.5) :
        muDoubleScalarFloor(c4_b_k + 0.5);
      if (c4_b_k < 2.147483648E+9) {
        if (c4_b_k >= -2.147483648E+9) {
          c4_k = (int32_T)c4_b_k;
        } else {
          c4_k = MIN_int32_T;
        }
      } else {
        c4_k = MAX_int32_T;
      }

      c4_bits = (real_T)c4_k;
      *c4_TempO = c4_in[sf_mex_lw_bounds_check((int32_T)c4_inpos, 1, 20) - 1];
      *c4_inposO = c4_inpos + 1.0;
      c4_a = c4_lval;
      if (c4_bits != c4_bits) {
        c4_eml_error(chartInstance);
      }

      c4_lval = 0U;
      if (c4_bits < 0.0) {
        c4_temp = (uint32_T)-c4_bits;
        c4_temp = (uint32_T)muDoubleScalarFloor((real_T)c4_temp + 0.5);
        if (c4_temp < 256U) {
          c4_absk1 = (uint8_T)c4_temp;
        } else {
          c4_absk1 = MAX_uint8_T;
        }

        if (c4_absk1 < 32) {
          c4_lval = c4_a >> (uint32_T)c4_absk1;
        }
      } else {
        c4_k = (int32_T)c4_bits;
        c4_k = (int32_T)muDoubleScalarFloor((real_T)c4_k + 0.5);
        if (c4_k < 256) {
          c4_absk1 = (uint8_T)c4_k;
        } else {
          c4_absk1 = MAX_uint8_T;
        }

        if (c4_absk1 < 32) {
          c4_lval = c4_a << (uint32_T)c4_absk1;
        }
      }

      *c4_cbitsO = 32;
      c4_guard1 = TRUE;
    }
  } else {
    c4_guard1 = TRUE;
  }

  if (c4_guard1 == TRUE) {
    c4_b_k = -(32.0 - c4_bits);
    if (c4_b_k != muDoubleScalarFloor(c4_b_k)) {
      c4_eml_error(chartInstance);
    }

    c4_temp = 0U;
    if (c4_b_k < 0.0) {
      c4_b_k = -c4_b_k;
      c4_b_k = muDoubleScalarFloor(c4_b_k + 0.5);
      if (c4_b_k < 256.0) {
        c4_absk1 = (uint8_T)c4_b_k;
      } else {
        c4_absk1 = MAX_uint8_T;
      }

      if (c4_absk1 < 32) {
        c4_temp = *c4_TempO >> (uint32_T)c4_absk1;
      }
    } else {
      c4_b_k = muDoubleScalarFloor(c4_b_k + 0.5);
      if (c4_b_k < 256.0) {
        c4_absk1 = (uint8_T)c4_b_k;
      } else if (c4_b_k >= 256.0) {
        c4_absk1 = MAX_uint8_T;
      } else {
        c4_absk1 = 0U;
      }

      if (c4_absk1 < 32) {
        c4_temp = *c4_TempO << (uint32_T)c4_absk1;
      }
    }

    c4_a = *c4_TempO;
    if (c4_bits != muDoubleScalarFloor(c4_bits)) {
      c4_eml_error(chartInstance);
    }

    *c4_TempO = 0U;
    if (c4_bits < 0.0) {
      c4_b_k = -c4_bits;
      c4_b_k = muDoubleScalarFloor(c4_b_k + 0.5);
      if (c4_b_k < 256.0) {
        c4_absk1 = (uint8_T)c4_b_k;
      } else {
        c4_absk1 = MAX_uint8_T;
      }

      if (c4_absk1 < 32) {
        *c4_TempO = c4_a >> (uint32_T)c4_absk1;
      }
    } else {
      c4_b_k = c4_bits;
      c4_b_k = muDoubleScalarFloor(c4_b_k + 0.5);
      if (c4_b_k < 256.0) {
        c4_absk1 = (uint8_T)c4_b_k;
      } else if (c4_b_k >= 256.0) {
        c4_absk1 = MAX_uint8_T;
      } else {
        c4_absk1 = 0U;
      }

      if (c4_absk1 < 32) {
        *c4_TempO = c4_a << (uint32_T)c4_absk1;
      }
    }

    *c4_valO = c4_lval | c4_temp;
    c4_b_k = (real_T)*c4_cbitsO - c4_bits;
    c4_b_k = c4_b_k < 0.0 ? muDoubleScalarCeil(c4_b_k - 0.5) :
      muDoubleScalarFloor(c4_b_k + 0.5);
    if (c4_b_k < 2.147483648E+9) {
      if (c4_b_k >= -2.147483648E+9) {
        *c4_cbitsO = (int32_T)c4_b_k;
      } else {
        *c4_cbitsO = MIN_int32_T;
      }
    } else if (c4_b_k >= 2.147483648E+9) {
      *c4_cbitsO = MAX_int32_T;
    } else {
      *c4_cbitsO = 0;
    }

    *c4_flag = 1.0;
  }
}

static void c4_eml_error(SFc4_videoInstanceStruct *chartInstance)
{
  int32_T c4_i5;
  static char_T c4_varargin_1[42] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'b', 'i', 't', 's', 'h', 'i', 'f', 't', '_', 'i',
    'n', 'p', 'u', 't', 's', 'M', 'u', 's', 't', 'B', 'e', 'I', 'n', 't', 'e',
    'g', 'e', 'r', 's' };

  char_T c4_u[42];
  const mxArray *c4_y = NULL;
  for (c4_i5 = 0; c4_i5 < 42; c4_i5++) {
    c4_u[c4_i5] = c4_varargin_1[c4_i5];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 10, 0U, 1U, 0U, 2, 1, 42));
  sf_mex_call("error", 0U, 1U, 14, sf_mex_call("message", 1U, 1U, 14, c4_y));
}

static void c4_emlrt_marshallIn(SFc4_videoInstanceStruct *chartInstance, const
  mxArray *c4_out, const char_T *c4_identifier, real32_T c4_y[64])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_out), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_out);
}

static void c4_b_emlrt_marshallIn(SFc4_videoInstanceStruct *chartInstance, const
  mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real32_T c4_y[64])
{
  real32_T c4_fv1[64];
  int32_T c4_i6;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_fv1, 1, 1, 0U, 1, 0U, 1, 64);
  for (c4_i6 = 0; c4_i6 < 64; c4_i6++) {
    c4_y[c4_i6] = c4_fv1[c4_i6];
  }

  sf_mex_destroy(&c4_u);
}

static void c4_c_emlrt_marshallIn(SFc4_videoInstanceStruct *chartInstance, const
  mxArray *c4_b_prev_out, const char_T *c4_identifier, real32_T c4_y[64])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_prev_out), &c4_thisId,
                        c4_y);
  sf_mex_destroy(&c4_b_prev_out);
}

static void c4_d_emlrt_marshallIn(SFc4_videoInstanceStruct *chartInstance, const
  mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real32_T c4_y[64])
{
  real32_T c4_fv2[64];
  int32_T c4_i7;
  if (mxIsEmpty(c4_u)) {
    chartInstance->c4_prev_out_not_empty = FALSE;
  } else {
    chartInstance->c4_prev_out_not_empty = TRUE;
    sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_fv2, 1, 1, 0U, 1, 0U, 1, 64);
    for (c4_i7 = 0; c4_i7 < 64; c4_i7++) {
      c4_y[c4_i7] = c4_fv2[c4_i7];
    }
  }

  sf_mex_destroy(&c4_u);
}

static uint8_T c4_e_emlrt_marshallIn(SFc4_videoInstanceStruct *chartInstance,
  const mxArray *c4_b_is_active_c4_video, const char_T *c4_identifier)
{
  uint8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_is_active_c4_video),
    &c4_thisId);
  sf_mex_destroy(&c4_b_is_active_c4_video);
  return c4_y;
}

static uint8_T c4_f_emlrt_marshallIn(SFc4_videoInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  uint8_T c4_u0;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_u0, 1, 3, 0U, 0, 0U, 0);
  c4_y = c4_u0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void init_dsm_address_info(SFc4_videoInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c4_video_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1433736736U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(530681178U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3258148491U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4065504135U);
}

mxArray *sf_c4_video_get_autoinheritance_info(void)
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

static const mxArray *sf_get_sim_state_info_c4_video(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"out\",},{M[4],M[0],T\"prev_out\",S'l','i','p'{{M1x2[188 196],M[0],}}},{M[8],M[0],T\"is_active_c4_video\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_video_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void sf_opaque_initialize_c4_video(void *chartInstanceVar)
{
  initialize_params_c4_video((SFc4_videoInstanceStruct*) chartInstanceVar);
  initialize_c4_video((SFc4_videoInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c4_video(void *chartInstanceVar)
{
  enable_c4_video((SFc4_videoInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c4_video(void *chartInstanceVar)
{
  disable_c4_video((SFc4_videoInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c4_video(void *chartInstanceVar)
{
  sf_c4_video((SFc4_videoInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c4_video(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c4_video((SFc4_videoInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_video();/* state var info */
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

extern void sf_internal_set_sim_state_c4_video(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_video();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c4_video((SFc4_videoInstanceStruct*)chartInfo->chartInstance,
    mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c4_video(SimStruct* S)
{
  return sf_internal_get_sim_state_c4_video(S);
}

static void sf_opaque_set_sim_state_c4_video(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c4_video(S, st);
}

static void sf_opaque_terminate_c4_video(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc4_videoInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c4_video((SFc4_videoInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc4_video((SFc4_videoInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c4_video(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c4_video((SFc4_videoInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c4_video(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"video","video",4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"video","video",4,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"video","video",4,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"video","video",4,1);
      sf_mark_chart_reusable_outputs(S,"video","video",4,1);
    }

    sf_set_rtw_dwork_info(S,"video","video",4);
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

static void mdlRTW_c4_video(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "video", "video",4);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c4_video(SimStruct *S)
{
  SFc4_videoInstanceStruct *chartInstance;
  chartInstance = (SFc4_videoInstanceStruct *)malloc(sizeof
    (SFc4_videoInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc4_videoInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c4_video;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c4_video;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c4_video;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c4_video;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c4_video;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c4_video;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c4_video;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c4_video;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c4_video;
  chartInstance->chartInfo.mdlStart = mdlStart_c4_video;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c4_video;
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

void c4_video_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c4_video(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_video(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_video(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_video_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
