/* Include files */

#include "blascompat32.h"
#include "video_sfun.h"
#include "c15_video.h"
#include "mwmathutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void initialize_c15_video(SFc15_videoInstanceStruct *chartInstance);
static void initialize_params_c15_video(SFc15_videoInstanceStruct *chartInstance);
static void enable_c15_video(SFc15_videoInstanceStruct *chartInstance);
static void disable_c15_video(SFc15_videoInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c15_video(SFc15_videoInstanceStruct
  *chartInstance);
static void set_sim_state_c15_video(SFc15_videoInstanceStruct *chartInstance,
  const mxArray *c15_st);
static void finalize_c15_video(SFc15_videoInstanceStruct *chartInstance);
static void sf_c15_video(SFc15_videoInstanceStruct *chartInstance);
static void c15_chartstep_c15_video(SFc15_videoInstanceStruct *chartInstance);
static void initSimStructsc15_video(SFc15_videoInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c15_machineNumber, uint32_T
  c15_chartNumber);
static void c15_info_helper(c15_ResolvedFunctionInfo c15_info[16]);
static void c15_eml_error(SFc15_videoInstanceStruct *chartInstance);
static void c15_emlrt_marshallIn(SFc15_videoInstanceStruct *chartInstance, const
  mxArray *c15_out, const char_T *c15_identifier, uint32_T c15_y[20]);
static void c15_b_emlrt_marshallIn(SFc15_videoInstanceStruct *chartInstance,
  const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId, uint32_T c15_y
  [20]);
static void c15_c_emlrt_marshallIn(SFc15_videoInstanceStruct *chartInstance,
  const mxArray *c15_b_prev_out, const char_T *c15_identifier, uint32_T c15_y[20]);
static void c15_d_emlrt_marshallIn(SFc15_videoInstanceStruct *chartInstance,
  const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId, uint32_T c15_y
  [20]);
static uint8_T c15_e_emlrt_marshallIn(SFc15_videoInstanceStruct *chartInstance,
  const mxArray *c15_b_is_active_c15_video, const char_T *c15_identifier);
static uint8_T c15_f_emlrt_marshallIn(SFc15_videoInstanceStruct *chartInstance,
  const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId);
static void c15_putbits(SFc15_videoInstanceStruct *chartInstance, int32_T
  c15_bitpos, uint32_T c15_out[20], uint32_T c15_Temp, real_T c15_outpos,
  uint32_T c15_val, real_T c15_bits, real_T *c15_flag, int32_T *c15_bitposO,
  uint32_T *c15_TempO, real_T *c15_outposO);
static void init_dsm_address_info(SFc15_videoInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c15_video(SFc15_videoInstanceStruct *chartInstance)
{
  int32_T c15_i0;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c15_prev_out_not_empty = FALSE;
  chartInstance->c15_is_active_c15_video = 0U;
  for (c15_i0 = 0; c15_i0 < 20; c15_i0++) {
    chartInstance->c15_prev_out[c15_i0] = 0U;
  }
}

static void initialize_params_c15_video(SFc15_videoInstanceStruct *chartInstance)
{
}

static void enable_c15_video(SFc15_videoInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c15_video(SFc15_videoInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static const mxArray *get_sim_state_c15_video(SFc15_videoInstanceStruct
  *chartInstance)
{
  const mxArray *c15_st;
  const mxArray *c15_y = NULL;
  int32_T c15_i1;
  uint32_T c15_u[20];
  const mxArray *c15_b_y = NULL;
  uint32_T c15_b_u[20];
  const mxArray *c15_c_y = NULL;
  uint8_T c15_c_u;
  const mxArray *c15_d_y = NULL;
  uint32_T (*c15_out)[20];
  c15_out = (uint32_T (*)[20])ssGetOutputPortSignal(chartInstance->S, 1);
  c15_st = NULL;
  c15_y = NULL;
  sf_mex_assign(&c15_y, sf_mex_createcellarray(3));
  for (c15_i1 = 0; c15_i1 < 20; c15_i1++) {
    c15_u[c15_i1] = (*c15_out)[c15_i1];
  }

  c15_b_y = NULL;
  sf_mex_assign(&c15_b_y, sf_mex_create("y", c15_u, 7, 0U, 1U, 0U, 1, 20));
  sf_mex_setcell(c15_y, 0, c15_b_y);
  for (c15_i1 = 0; c15_i1 < 20; c15_i1++) {
    c15_b_u[c15_i1] = chartInstance->c15_prev_out[c15_i1];
  }

  c15_c_y = NULL;
  if (!chartInstance->c15_prev_out_not_empty) {
    sf_mex_assign(&c15_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c15_c_y, sf_mex_create("y", c15_b_u, 7, 0U, 1U, 0U, 1, 20));
  }

  sf_mex_setcell(c15_y, 1, c15_c_y);
  c15_c_u = chartInstance->c15_is_active_c15_video;
  c15_d_y = NULL;
  sf_mex_assign(&c15_d_y, sf_mex_create("y", &c15_c_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c15_y, 2, c15_d_y);
  sf_mex_assign(&c15_st, c15_y);
  return c15_st;
}

static void set_sim_state_c15_video(SFc15_videoInstanceStruct *chartInstance,
  const mxArray *c15_st)
{
  const mxArray *c15_u;
  uint32_T c15_uv0[20];
  int32_T c15_i2;
  uint32_T (*c15_out)[20];
  c15_out = (uint32_T (*)[20])ssGetOutputPortSignal(chartInstance->S, 1);
  c15_u = sf_mex_dup(c15_st);
  c15_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c15_u, 0)),
                       "out", c15_uv0);
  for (c15_i2 = 0; c15_i2 < 20; c15_i2++) {
    (*c15_out)[c15_i2] = c15_uv0[c15_i2];
  }

  c15_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c15_u, 1)),
    "prev_out", c15_uv0);
  for (c15_i2 = 0; c15_i2 < 20; c15_i2++) {
    chartInstance->c15_prev_out[c15_i2] = c15_uv0[c15_i2];
  }

  chartInstance->c15_is_active_c15_video = c15_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c15_u, 2)), "is_active_c15_video");
  sf_mex_destroy(&c15_u);
  sf_mex_destroy(&c15_st);
}

static void finalize_c15_video(SFc15_videoInstanceStruct *chartInstance)
{
}

static void sf_c15_video(SFc15_videoInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  c15_chartstep_c15_video(chartInstance);
}

static void c15_chartstep_c15_video(SFc15_videoInstanceStruct *chartInstance)
{
  int32_T c15_out1;
  real32_T c15_in[64];
  uint32_T c15_out[20];
  int32_T c15_bitpos;
  uint32_T c15_Temp;
  real_T c15_outpos;
  real32_T c15_cval;
  real32_T c15_pval;
  int32_T c15_bitsIn;
  int32_T c15_exitg1;
  boolean_T c15_guard1 = FALSE;
  real_T c15_b_outpos;
  uint32_T c15_b_Temp;
  int32_T c15_b_bitpos;
  real_T c15_flag;
  uint32_T c15_valIn;
  int64_T c15_i3;
  boolean_T c15_guard2 = FALSE;
  uint8_T c15_absk1;
  boolean_T c15_b_guard1 = FALSE;
  uint32_T (*c15_b_out)[20];
  real32_T (*c15_b_in)[64];
  c15_b_out = (uint32_T (*)[20])ssGetOutputPortSignal(chartInstance->S, 1);
  c15_b_in = (real32_T (*)[64])ssGetInputPortSignal(chartInstance->S, 0);
  for (c15_out1 = 0; c15_out1 < 64; c15_out1++) {
    c15_in[c15_out1] = (*c15_b_in)[c15_out1];
  }

  chartInstance->c15_prev_out_not_empty = TRUE;
  for (c15_out1 = 0; c15_out1 < 20; c15_out1++) {
    c15_out[c15_out1] = chartInstance->c15_prev_out[c15_out1];
  }

  c15_bitpos = 0;
  c15_Temp = 0U;
  c15_outpos = 2.0;
  if ((real_T)(*c15_b_in)[0] > 0.0) {
    c15_cval = muSingleScalarFloor((*c15_b_in)[0]);
  } else {
    c15_cval = muSingleScalarCeil((*c15_b_in)[0]);
  }

  if ((c15_cval < 8.388608E+6F) && (c15_cval > -8.388608E+6F)) {
    c15_cval = (real_T)c15_cval < 0.0 ? muSingleScalarCeil(c15_cval - 0.5F) :
      muSingleScalarFloor(c15_cval + 0.5F);
  }

  if (c15_cval < 2.14748365E+9F) {
    if (c15_cval >= -2.14748365E+9F) {
      c15_out1 = (int32_T)c15_cval;
    } else {
      c15_out1 = MIN_int32_T;
    }
  } else if (c15_cval >= 2.14748365E+9F) {
    c15_out1 = MAX_int32_T;
  } else {
    c15_out1 = 0;
  }

  if (c15_out1 >= -1) {
    if (c15_out1 <= 0) {
      c15_out1 = 0;
    }

    c15_out[0] = (uint32_T)c15_out1;
  } else {
    if (c15_out1 <= MIN_int32_T) {
      c15_out1 = MAX_int32_T;
    } else {
      c15_out1 = -c15_out1;
    }

    c15_out[0] = 1U - (uint32_T)c15_out1;
  }

  c15_cval = (*c15_b_in)[1] + 0.5F;
  if ((real_T)c15_cval > 0.0) {
    c15_pval = muSingleScalarFloor(c15_cval);
  } else {
    c15_pval = muSingleScalarCeil(c15_cval);
  }

  if ((real_T)c15_pval > 127.0) {
    c15_pval = 127.0F;
  }

  if ((real_T)c15_pval < -128.0) {
    c15_pval = -128.0F;
  }

  c15_out1 = 0;
  c15_bitsIn = 3;
  do {
    c15_exitg1 = 0U;
    if (c15_bitsIn <= 64) {
      c15_cval = c15_in[c15_bitsIn - 1] + 0.5F;
      c15_cval = muSingleScalarFloor(c15_cval);
      c15_guard1 = FALSE;
      if ((c15_pval == c15_cval) && (c15_out1 < 14)) {
        c15_out1 = (int32_T)((uint32_T)c15_out1 + 1U);
        c15_guard1 = TRUE;
      } else {
        c15_putbits(chartInstance, c15_bitpos, c15_out, c15_Temp, c15_outpos,
                    (uint32_T)c15_out1, 4.0, &c15_flag, &c15_b_bitpos,
                    &c15_b_Temp, &c15_b_outpos);
        if (!(c15_flag != 0.0)) {
          for (c15_out1 = 0; c15_out1 < 20; c15_out1++) {
            chartInstance->c15_prev_out[c15_out1] = c15_out[c15_out1];
          }

          c15_exitg1 = 1U;
        } else {
          if ((real_T)c15_pval > 127.0) {
            c15_pval = 127.0F;
          }

          if ((real_T)c15_pval < -128.0) {
            c15_pval = -128.0F;
          }

          c15_pval += 128.0F;
          if ((c15_pval < 8.388608E+6F) && (c15_pval > -8.388608E+6F)) {
            c15_pval = muSingleScalarFloor(c15_pval + 0.5F);
          }

          if (c15_pval < 4.2949673E+9F) {
            c15_valIn = (uint32_T)c15_pval;
          } else {
            c15_valIn = 0U;
          }

          c15_putbits(chartInstance, c15_b_bitpos, c15_out, c15_b_Temp,
                      c15_b_outpos, c15_valIn, 8.0, &c15_flag, &c15_bitpos,
                      &c15_Temp, &c15_outpos);
          if (!(c15_flag != 0.0)) {
            for (c15_out1 = 0; c15_out1 < 20; c15_out1++) {
              chartInstance->c15_prev_out[c15_out1] = c15_out[c15_out1];
            }

            c15_exitg1 = 1U;
          } else {
            c15_out1 = 0;
            c15_guard1 = TRUE;
          }
        }
      }

      if (c15_guard1 == TRUE) {
        c15_pval = c15_cval;
        c15_bitsIn++;
        sf_mex_listen_for_ctrl_c(chartInstance->S);
      }
    } else {
      c15_putbits(chartInstance, c15_bitpos, c15_out, c15_Temp, c15_outpos,
                  (uint32_T)c15_out1, 4.0, &c15_flag, &c15_b_bitpos, &c15_b_Temp,
                  &c15_b_outpos);
      if (!(c15_flag != 0.0)) {
        for (c15_out1 = 0; c15_out1 < 20; c15_out1++) {
          chartInstance->c15_prev_out[c15_out1] = c15_out[c15_out1];
        }
      } else {
        if ((real_T)c15_pval > 127.0) {
          c15_pval = 127.0F;
        }

        if ((real_T)c15_pval < -128.0) {
          c15_pval = -128.0F;
        }

        c15_pval += 128.0F;
        if ((c15_pval < 8.388608E+6F) && (c15_pval > -8.388608E+6F)) {
          c15_pval = muSingleScalarFloor(c15_pval + 0.5F);
        }

        if (c15_pval < 4.2949673E+9F) {
          c15_valIn = (uint32_T)c15_pval;
        } else {
          c15_valIn = 0U;
        }

        c15_bitsIn = 8;
        c15_i3 = (int64_T)c15_b_bitpos + (int64_T)8;
        if (c15_i3 > 2147483647L) {
          c15_i3 = 2147483647L;
        } else {
          if (c15_i3 <= -2147483648L) {
            c15_i3 = -2147483648L;
          }
        }

        c15_guard2 = FALSE;
        if ((int32_T)c15_i3 > 32) {
          c15_i3 = (int64_T)32 - (int64_T)c15_b_bitpos;
          if (c15_i3 > 2147483647L) {
            c15_i3 = 2147483647L;
          } else {
            if (c15_i3 <= -2147483648L) {
              c15_i3 = -2147483648L;
            }
          }

          c15_bitsIn = (int32_T)c15_i3 - 8;
          c15_out1 = -(-c15_bitsIn);
          c15_Temp = 0U;
          if (c15_out1 < 0) {
            c15_out1 = -c15_out1;
            if (c15_out1 <= 0) {
              c15_out1 = 0;
            } else {
              if (c15_out1 > 255) {
                c15_out1 = 255;
              }
            }

            c15_absk1 = (uint8_T)c15_out1;
            if (c15_absk1 < 32) {
              c15_Temp = c15_valIn >> (uint32_T)c15_absk1;
            }
          } else {
            if (c15_out1 <= 0) {
              c15_out1 = 0;
            } else {
              if (c15_out1 > 255) {
                c15_out1 = 255;
              }
            }

            c15_absk1 = (uint8_T)c15_out1;
            if (c15_absk1 < 32) {
              c15_Temp = c15_valIn << (uint32_T)c15_absk1;
            }
          }

          c15_b_Temp |= c15_Temp;
          c15_out[sf_mex_lw_bounds_check((int32_T)c15_b_outpos, 1, 20) - 1] =
            c15_b_Temp;
          c15_b_outpos++;
          if (c15_b_outpos > 20.0) {
            c15_out1 = 0;
          } else {
            c15_b_Temp = 0U;
            c15_b_bitpos = 0;
            c15_bitsIn = -c15_bitsIn;
            c15_Temp = c15_valIn;
            c15_i3 = (int64_T)32 - (int64_T)c15_bitsIn;
            if (c15_i3 > 2147483647L) {
              c15_i3 = 2147483647L;
            } else {
              if (c15_i3 <= -2147483648L) {
                c15_i3 = -2147483648L;
              }
            }

            c15_out1 = (int32_T)c15_i3;
            c15_valIn = 0U;
            if (c15_out1 < 0) {
              c15_out1 = -c15_out1;
              if (c15_out1 <= 0) {
                c15_out1 = 0;
              } else {
                if (c15_out1 > 255) {
                  c15_out1 = 255;
                }
              }

              c15_absk1 = (uint8_T)c15_out1;
              if (c15_absk1 < 32) {
                c15_valIn = c15_Temp >> (uint32_T)c15_absk1;
              }
            } else {
              if (c15_out1 <= 0) {
                c15_out1 = 0;
              } else {
                if (c15_out1 > 255) {
                  c15_out1 = 255;
                }
              }

              c15_absk1 = (uint8_T)c15_out1;
              if (c15_absk1 < 32) {
                c15_valIn = c15_Temp << (uint32_T)c15_absk1;
              }
            }

            c15_Temp = c15_valIn;
            c15_i3 = (int64_T)32 - (int64_T)c15_bitsIn;
            if (c15_i3 > 2147483647L) {
              c15_i3 = 2147483647L;
            } else {
              if (c15_i3 <= -2147483648L) {
                c15_i3 = -2147483648L;
              }
            }

            c15_out1 = -(int32_T)c15_i3;
            c15_valIn = 0U;
            if (c15_out1 < 0) {
              c15_out1 = -c15_out1;
              if (c15_out1 <= 0) {
                c15_out1 = 0;
              } else {
                if (c15_out1 > 255) {
                  c15_out1 = 255;
                }
              }

              c15_absk1 = (uint8_T)c15_out1;
              if (c15_absk1 < 32) {
                c15_valIn = c15_Temp >> (uint32_T)c15_absk1;
              }
            } else {
              if (c15_out1 <= 0) {
                c15_out1 = 0;
              } else {
                if (c15_out1 > 255) {
                  c15_out1 = 255;
                }
              }

              c15_absk1 = (uint8_T)c15_out1;
              if (c15_absk1 < 32) {
                c15_valIn = c15_Temp << (uint32_T)c15_absk1;
              }
            }

            c15_guard2 = TRUE;
          }
        } else {
          c15_guard2 = TRUE;
        }

        if (c15_guard2 == TRUE) {
          c15_Temp = c15_valIn;
          c15_i3 = (int64_T)c15_bitsIn + (int64_T)c15_b_bitpos;
          if (c15_i3 > 2147483647L) {
            c15_i3 = 2147483647L;
          } else {
            if (c15_i3 <= -2147483648L) {
              c15_i3 = -2147483648L;
            }
          }

          c15_i3 = (int64_T)32 - (int64_T)(int32_T)c15_i3;
          if (c15_i3 > 2147483647L) {
            c15_i3 = 2147483647L;
          } else {
            if (c15_i3 <= -2147483648L) {
              c15_i3 = -2147483648L;
            }
          }

          c15_out1 = (int32_T)c15_i3;
          c15_valIn = 0U;
          if (c15_out1 < 0) {
            c15_out1 = -c15_out1;
            if (c15_out1 <= 0) {
              c15_out1 = 0;
            } else {
              if (c15_out1 > 255) {
                c15_out1 = 255;
              }
            }

            c15_absk1 = (uint8_T)c15_out1;
            if (c15_absk1 < 32) {
              c15_valIn = c15_Temp >> (uint32_T)c15_absk1;
            }
          } else {
            if (c15_out1 <= 0) {
              c15_out1 = 0;
            } else {
              if (c15_out1 > 255) {
                c15_out1 = 255;
              }
            }

            c15_absk1 = (uint8_T)c15_out1;
            if (c15_absk1 < 32) {
              c15_valIn = c15_Temp << (uint32_T)c15_absk1;
            }
          }

          c15_b_Temp |= c15_valIn;
          c15_i3 = (int64_T)c15_b_bitpos + (int64_T)c15_bitsIn;
          if (c15_i3 > 2147483647L) {
            c15_i3 = 2147483647L;
          } else {
            if (c15_i3 <= -2147483648L) {
              c15_i3 = -2147483648L;
            }
          }

          c15_b_bitpos = (int32_T)c15_i3;
          c15_out1 = 1;
        }

        if (!(c15_out1 != 0)) {
          for (c15_out1 = 0; c15_out1 < 20; c15_out1++) {
            chartInstance->c15_prev_out[c15_out1] = c15_out[c15_out1];
          }
        } else {
          c15_valIn = 15U;
          c15_bitsIn = 4;
          c15_i3 = (int64_T)c15_b_bitpos + (int64_T)4;
          if (c15_i3 > 2147483647L) {
            c15_i3 = 2147483647L;
          } else {
            if (c15_i3 <= -2147483648L) {
              c15_i3 = -2147483648L;
            }
          }

          c15_b_guard1 = FALSE;
          if ((int32_T)c15_i3 > 32) {
            c15_i3 = (int64_T)32 - (int64_T)c15_b_bitpos;
            if (c15_i3 > 2147483647L) {
              c15_i3 = 2147483647L;
            } else {
              if (c15_i3 <= -2147483648L) {
                c15_i3 = -2147483648L;
              }
            }

            c15_bitsIn = (int32_T)c15_i3 - 4;
            c15_out1 = -(-c15_bitsIn);
            c15_Temp = 0U;
            if (c15_out1 < 0) {
              c15_out1 = -c15_out1;
              if (c15_out1 <= 0) {
                c15_out1 = 0;
              } else {
                if (c15_out1 > 255) {
                  c15_out1 = 255;
                }
              }

              c15_absk1 = (uint8_T)c15_out1;
              if (c15_absk1 < 32) {
                c15_Temp = 15U >> (uint32_T)c15_absk1;
              }
            } else {
              if (c15_out1 <= 0) {
                c15_out1 = 0;
              } else {
                if (c15_out1 > 255) {
                  c15_out1 = 255;
                }
              }

              c15_absk1 = (uint8_T)c15_out1;
              if (c15_absk1 < 32) {
                c15_Temp = 15U << (uint32_T)c15_absk1;
              }
            }

            c15_b_Temp |= c15_Temp;
            c15_out[sf_mex_lw_bounds_check((int32_T)c15_b_outpos, 1, 20) - 1] =
              c15_b_Temp;
            c15_b_outpos++;
            if (c15_b_outpos > 20.0) {
              c15_out1 = 0;
            } else {
              c15_b_Temp = 0U;
              c15_b_bitpos = 0;
              c15_bitsIn = -c15_bitsIn;
              c15_i3 = (int64_T)32 - (int64_T)c15_bitsIn;
              if (c15_i3 > 2147483647L) {
                c15_i3 = 2147483647L;
              } else {
                if (c15_i3 <= -2147483648L) {
                  c15_i3 = -2147483648L;
                }
              }

              c15_out1 = (int32_T)c15_i3;
              c15_valIn = 0U;
              if (c15_out1 < 0) {
                c15_out1 = -c15_out1;
                if (c15_out1 <= 0) {
                  c15_out1 = 0;
                } else {
                  if (c15_out1 > 255) {
                    c15_out1 = 255;
                  }
                }

                c15_absk1 = (uint8_T)c15_out1;
                if (c15_absk1 < 32) {
                  c15_valIn = 15U >> (uint32_T)c15_absk1;
                }
              } else {
                if (c15_out1 <= 0) {
                  c15_out1 = 0;
                } else {
                  if (c15_out1 > 255) {
                    c15_out1 = 255;
                  }
                }

                c15_absk1 = (uint8_T)c15_out1;
                if (c15_absk1 < 32) {
                  c15_valIn = 15U << (uint32_T)c15_absk1;
                }
              }

              c15_Temp = c15_valIn;
              c15_i3 = (int64_T)32 - (int64_T)c15_bitsIn;
              if (c15_i3 > 2147483647L) {
                c15_i3 = 2147483647L;
              } else {
                if (c15_i3 <= -2147483648L) {
                  c15_i3 = -2147483648L;
                }
              }

              c15_out1 = -(int32_T)c15_i3;
              c15_valIn = 0U;
              if (c15_out1 < 0) {
                c15_out1 = -c15_out1;
                if (c15_out1 <= 0) {
                  c15_out1 = 0;
                } else {
                  if (c15_out1 > 255) {
                    c15_out1 = 255;
                  }
                }

                c15_absk1 = (uint8_T)c15_out1;
                if (c15_absk1 < 32) {
                  c15_valIn = c15_Temp >> (uint32_T)c15_absk1;
                }
              } else {
                if (c15_out1 <= 0) {
                  c15_out1 = 0;
                } else {
                  if (c15_out1 > 255) {
                    c15_out1 = 255;
                  }
                }

                c15_absk1 = (uint8_T)c15_out1;
                if (c15_absk1 < 32) {
                  c15_valIn = c15_Temp << (uint32_T)c15_absk1;
                }
              }

              c15_b_guard1 = TRUE;
            }
          } else {
            c15_b_guard1 = TRUE;
          }

          if (c15_b_guard1 == TRUE) {
            c15_Temp = c15_valIn;
            c15_i3 = (int64_T)c15_bitsIn + (int64_T)c15_b_bitpos;
            if (c15_i3 > 2147483647L) {
              c15_i3 = 2147483647L;
            } else {
              if (c15_i3 <= -2147483648L) {
                c15_i3 = -2147483648L;
              }
            }

            c15_i3 = (int64_T)32 - (int64_T)(int32_T)c15_i3;
            if (c15_i3 > 2147483647L) {
              c15_i3 = 2147483647L;
            } else {
              if (c15_i3 <= -2147483648L) {
                c15_i3 = -2147483648L;
              }
            }

            c15_out1 = (int32_T)c15_i3;
            c15_valIn = 0U;
            if (c15_out1 < 0) {
              c15_out1 = -c15_out1;
              if (c15_out1 <= 0) {
                c15_out1 = 0;
              } else {
                if (c15_out1 > 255) {
                  c15_out1 = 255;
                }
              }

              c15_absk1 = (uint8_T)c15_out1;
              if (c15_absk1 < 32) {
                c15_valIn = c15_Temp >> (uint32_T)c15_absk1;
              }
            } else {
              if (c15_out1 <= 0) {
                c15_out1 = 0;
              } else {
                if (c15_out1 > 255) {
                  c15_out1 = 255;
                }
              }

              c15_absk1 = (uint8_T)c15_out1;
              if (c15_absk1 < 32) {
                c15_valIn = c15_Temp << (uint32_T)c15_absk1;
              }
            }

            c15_b_Temp |= c15_valIn;
            c15_out1 = 1;
          }

          if ((c15_out1 != 0) && (!(c15_b_outpos > 21.0))) {
            c15_out[sf_mex_lw_bounds_check((int32_T)c15_b_outpos, 1, 20) - 1] =
              c15_b_Temp;
          }

          for (c15_out1 = 0; c15_out1 < 20; c15_out1++) {
            chartInstance->c15_prev_out[c15_out1] = c15_out[c15_out1];
          }
        }
      }

      c15_exitg1 = 1U;
    }
  } while (c15_exitg1 == 0U);

  for (c15_out1 = 0; c15_out1 < 20; c15_out1++) {
    (*c15_b_out)[c15_out1] = c15_out[c15_out1];
  }
}

static void initSimStructsc15_video(SFc15_videoInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c15_machineNumber, uint32_T
  c15_chartNumber)
{
}

const mxArray *sf_c15_video_get_eml_resolved_functions_info(void)
{
  const mxArray *c15_nameCaptureInfo;
  c15_ResolvedFunctionInfo c15_info[16];
  const mxArray *c15_m0 = NULL;
  int32_T c15_i4;
  c15_ResolvedFunctionInfo *c15_r0;
  c15_nameCaptureInfo = NULL;
  c15_info_helper(c15_info);
  sf_mex_assign(&c15_m0, sf_mex_createstruct("nameCaptureInfo", 1, 16));
  for (c15_i4 = 0; c15_i4 < 16; c15_i4++) {
    c15_r0 = &c15_info[c15_i4];
    sf_mex_addfield(c15_m0, sf_mex_create("nameCaptureInfo", c15_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c15_r0->context)), "context", "nameCaptureInfo",
                    c15_i4);
    sf_mex_addfield(c15_m0, sf_mex_create("nameCaptureInfo", c15_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c15_r0->name)), "name", "nameCaptureInfo", c15_i4);
    sf_mex_addfield(c15_m0, sf_mex_create("nameCaptureInfo",
      c15_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c15_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c15_i4);
    sf_mex_addfield(c15_m0, sf_mex_create("nameCaptureInfo", c15_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c15_r0->resolved)), "resolved",
                    "nameCaptureInfo", c15_i4);
    sf_mex_addfield(c15_m0, sf_mex_create("nameCaptureInfo", &c15_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c15_i4);
    sf_mex_addfield(c15_m0, sf_mex_create("nameCaptureInfo", &c15_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c15_i4);
    sf_mex_addfield(c15_m0, sf_mex_create("nameCaptureInfo",
      &c15_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c15_i4);
    sf_mex_addfield(c15_m0, sf_mex_create("nameCaptureInfo",
      &c15_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c15_i4);
  }

  sf_mex_assign(&c15_nameCaptureInfo, c15_m0);
  return c15_nameCaptureInfo;
}

static void c15_info_helper(c15_ResolvedFunctionInfo c15_info[16])
{
  c15_info[0].context = "";
  c15_info[0].name = "fix";
  c15_info[0].dominantType = "single";
  c15_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/fix.m";
  c15_info[0].fileTimeLo = 1286815142U;
  c15_info[0].fileTimeHi = 0U;
  c15_info[0].mFileTimeLo = 0U;
  c15_info[0].mFileTimeHi = 0U;
  c15_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/fix.m";
  c15_info[1].name = "eml_scalar_fix";
  c15_info[1].dominantType = "single";
  c15_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_fix.m";
  c15_info[1].fileTimeLo = 1286815126U;
  c15_info[1].fileTimeHi = 0U;
  c15_info[1].mFileTimeLo = 0U;
  c15_info[1].mFileTimeHi = 0U;
  c15_info[2].context = "";
  c15_info[2].name = "intmax";
  c15_info[2].dominantType = "char";
  c15_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c15_info[2].fileTimeLo = 1286815156U;
  c15_info[2].fileTimeHi = 0U;
  c15_info[2].mFileTimeLo = 0U;
  c15_info[2].mFileTimeHi = 0U;
  c15_info[3].context = "";
  c15_info[3].name = "abs";
  c15_info[3].dominantType = "int32";
  c15_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c15_info[3].fileTimeLo = 1286815094U;
  c15_info[3].fileTimeHi = 0U;
  c15_info[3].mFileTimeLo = 0U;
  c15_info[3].mFileTimeHi = 0U;
  c15_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c15_info[4].name = "eml_scalar_abs";
  c15_info[4].dominantType = "int32";
  c15_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c15_info[4].fileTimeLo = 1286815112U;
  c15_info[4].fileTimeHi = 0U;
  c15_info[4].mFileTimeLo = 0U;
  c15_info[4].mFileTimeHi = 0U;
  c15_info[5].context = "";
  c15_info[5].name = "floor";
  c15_info[5].dominantType = "single";
  c15_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c15_info[5].fileTimeLo = 1286815142U;
  c15_info[5].fileTimeHi = 0U;
  c15_info[5].mFileTimeLo = 0U;
  c15_info[5].mFileTimeHi = 0U;
  c15_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c15_info[6].name = "eml_scalar_floor";
  c15_info[6].dominantType = "single";
  c15_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c15_info[6].fileTimeLo = 1286815126U;
  c15_info[6].fileTimeHi = 0U;
  c15_info[6].mFileTimeLo = 0U;
  c15_info[6].mFileTimeHi = 0U;
  c15_info[7].context = "";
  c15_info[7].name = "bitshift";
  c15_info[7].dominantType = "uint32";
  c15_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c15_info[7].fileTimeLo = 1286815238U;
  c15_info[7].fileTimeHi = 0U;
  c15_info[7].mFileTimeLo = 0U;
  c15_info[7].mFileTimeHi = 0U;
  c15_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c15_info[8].name = "eml_isa_uint";
  c15_info[8].dominantType = "uint32";
  c15_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  c15_info[8].fileTimeLo = 1286815184U;
  c15_info[8].fileTimeHi = 0U;
  c15_info[8].mFileTimeLo = 0U;
  c15_info[8].mFileTimeHi = 0U;
  c15_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c15_info[9].name = "eml_int_nbits";
  c15_info[9].dominantType = "char";
  c15_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_nbits.m";
  c15_info[9].fileTimeLo = 1286815180U;
  c15_info[9].fileTimeHi = 0U;
  c15_info[9].mFileTimeLo = 0U;
  c15_info[9].mFileTimeHi = 0U;
  c15_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c15_info[10].name = "eml_scalar_eg";
  c15_info[10].dominantType = "uint32";
  c15_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c15_info[10].fileTimeLo = 1286815196U;
  c15_info[10].fileTimeHi = 0U;
  c15_info[10].mFileTimeLo = 0U;
  c15_info[10].mFileTimeHi = 0U;
  c15_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c15_info[11].name = "eml_scalexp_alloc";
  c15_info[11].dominantType = "uint32";
  c15_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c15_info[11].fileTimeLo = 1286815196U;
  c15_info[11].fileTimeHi = 0U;
  c15_info[11].mFileTimeLo = 0U;
  c15_info[11].mFileTimeHi = 0U;
  c15_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c15_info[12].name = "eml_error";
  c15_info[12].dominantType = "char";
  c15_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c15_info[12].fileTimeLo = 1286815100U;
  c15_info[12].fileTimeHi = 0U;
  c15_info[12].mFileTimeLo = 0U;
  c15_info[12].mFileTimeHi = 0U;
  c15_info[13].context = "";
  c15_info[13].name = "bitor";
  c15_info[13].dominantType = "uint32";
  c15_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitor.m";
  c15_info[13].fileTimeLo = 1286815236U;
  c15_info[13].fileTimeHi = 0U;
  c15_info[13].mFileTimeLo = 0U;
  c15_info[13].mFileTimeHi = 0U;
  c15_info[14].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitor.m";
  c15_info[14].name = "eml_scalexp_compatible";
  c15_info[14].dominantType = "uint32";
  c15_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c15_info[14].fileTimeLo = 1286815196U;
  c15_info[14].fileTimeHi = 0U;
  c15_info[14].mFileTimeLo = 0U;
  c15_info[14].mFileTimeHi = 0U;
  c15_info[15].context = "";
  c15_info[15].name = "length";
  c15_info[15].dominantType = "uint32";
  c15_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c15_info[15].fileTimeLo = 1286815160U;
  c15_info[15].fileTimeHi = 0U;
  c15_info[15].mFileTimeLo = 0U;
  c15_info[15].mFileTimeHi = 0U;
}

static void c15_eml_error(SFc15_videoInstanceStruct *chartInstance)
{
  int32_T c15_i5;
  static char_T c15_varargin_1[42] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'b', 'i', 't', 's', 'h', 'i', 'f', 't', '_', 'i',
    'n', 'p', 'u', 't', 's', 'M', 'u', 's', 't', 'B', 'e', 'I', 'n', 't', 'e',
    'g', 'e', 'r', 's' };

  char_T c15_u[42];
  const mxArray *c15_y = NULL;
  for (c15_i5 = 0; c15_i5 < 42; c15_i5++) {
    c15_u[c15_i5] = c15_varargin_1[c15_i5];
  }

  c15_y = NULL;
  sf_mex_assign(&c15_y, sf_mex_create("y", c15_u, 10, 0U, 1U, 0U, 2, 1, 42));
  sf_mex_call("error", 0U, 1U, 14, sf_mex_call("message", 1U, 1U, 14, c15_y));
}

static void c15_emlrt_marshallIn(SFc15_videoInstanceStruct *chartInstance, const
  mxArray *c15_out, const char_T *c15_identifier, uint32_T c15_y[20])
{
  emlrtMsgIdentifier c15_thisId;
  c15_thisId.fIdentifier = c15_identifier;
  c15_thisId.fParent = NULL;
  c15_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c15_out), &c15_thisId, c15_y);
  sf_mex_destroy(&c15_out);
}

static void c15_b_emlrt_marshallIn(SFc15_videoInstanceStruct *chartInstance,
  const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId, uint32_T c15_y
  [20])
{
  uint32_T c15_uv1[20];
  int32_T c15_i6;
  sf_mex_import(c15_parentId, sf_mex_dup(c15_u), c15_uv1, 1, 7, 0U, 1, 0U, 1, 20);
  for (c15_i6 = 0; c15_i6 < 20; c15_i6++) {
    c15_y[c15_i6] = c15_uv1[c15_i6];
  }

  sf_mex_destroy(&c15_u);
}

static void c15_c_emlrt_marshallIn(SFc15_videoInstanceStruct *chartInstance,
  const mxArray *c15_b_prev_out, const char_T *c15_identifier, uint32_T c15_y[20])
{
  emlrtMsgIdentifier c15_thisId;
  c15_thisId.fIdentifier = c15_identifier;
  c15_thisId.fParent = NULL;
  c15_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c15_b_prev_out), &c15_thisId,
    c15_y);
  sf_mex_destroy(&c15_b_prev_out);
}

static void c15_d_emlrt_marshallIn(SFc15_videoInstanceStruct *chartInstance,
  const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId, uint32_T c15_y
  [20])
{
  uint32_T c15_uv2[20];
  int32_T c15_i7;
  if (mxIsEmpty(c15_u)) {
    chartInstance->c15_prev_out_not_empty = FALSE;
  } else {
    chartInstance->c15_prev_out_not_empty = TRUE;
    sf_mex_import(c15_parentId, sf_mex_dup(c15_u), c15_uv2, 1, 7, 0U, 1, 0U, 1,
                  20);
    for (c15_i7 = 0; c15_i7 < 20; c15_i7++) {
      c15_y[c15_i7] = c15_uv2[c15_i7];
    }
  }

  sf_mex_destroy(&c15_u);
}

static uint8_T c15_e_emlrt_marshallIn(SFc15_videoInstanceStruct *chartInstance,
  const mxArray *c15_b_is_active_c15_video, const char_T *c15_identifier)
{
  uint8_T c15_y;
  emlrtMsgIdentifier c15_thisId;
  c15_thisId.fIdentifier = c15_identifier;
  c15_thisId.fParent = NULL;
  c15_y = c15_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c15_b_is_active_c15_video), &c15_thisId);
  sf_mex_destroy(&c15_b_is_active_c15_video);
  return c15_y;
}

static uint8_T c15_f_emlrt_marshallIn(SFc15_videoInstanceStruct *chartInstance,
  const mxArray *c15_u, const emlrtMsgIdentifier *c15_parentId)
{
  uint8_T c15_y;
  uint8_T c15_u0;
  sf_mex_import(c15_parentId, sf_mex_dup(c15_u), &c15_u0, 1, 3, 0U, 0, 0U, 0);
  c15_y = c15_u0;
  sf_mex_destroy(&c15_u);
  return c15_y;
}

static void c15_putbits(SFc15_videoInstanceStruct *chartInstance, int32_T
  c15_bitpos, uint32_T c15_out[20], uint32_T c15_Temp, real_T c15_outpos,
  uint32_T c15_val, real_T c15_bits, real_T *c15_flag, int32_T *c15_bitposO,
  uint32_T *c15_TempO, real_T *c15_outposO)
{
  uint32_T c15_valIn;
  real_T c15_d0;
  int32_T c15_bitsIn;
  int64_T c15_i8;
  boolean_T c15_guard1 = FALSE;
  int32_T c15_bitsleft;
  int32_T c15_saturatedUnaryMinus;
  uint8_T c15_absk1;
  uint32_T c15_a;
  c15_valIn = c15_val;
  c15_d0 = c15_bits;
  c15_d0 = c15_d0 < 0.0 ? muDoubleScalarCeil(c15_d0 - 0.5) : muDoubleScalarFloor
    (c15_d0 + 0.5);
  if (c15_d0 < 2.147483648E+9) {
    if (c15_d0 >= -2.147483648E+9) {
      c15_bitsIn = (int32_T)c15_d0;
    } else {
      c15_bitsIn = MIN_int32_T;
    }
  } else if (c15_d0 >= 2.147483648E+9) {
    c15_bitsIn = MAX_int32_T;
  } else {
    c15_bitsIn = 0;
  }

  *c15_bitposO = c15_bitpos;
  *c15_TempO = c15_Temp;
  *c15_outposO = c15_outpos;
  c15_i8 = (int64_T)c15_bitpos + (int64_T)c15_bitsIn;
  if (c15_i8 > 2147483647L) {
    c15_i8 = 2147483647L;
  } else {
    if (c15_i8 <= -2147483648L) {
      c15_i8 = -2147483648L;
    }
  }

  c15_guard1 = FALSE;
  if ((int32_T)c15_i8 > 32) {
    c15_i8 = (int64_T)32 - (int64_T)c15_bitpos;
    if (c15_i8 > 2147483647L) {
      c15_i8 = 2147483647L;
    } else {
      if (c15_i8 <= -2147483648L) {
        c15_i8 = -2147483648L;
      }
    }

    c15_bitsleft = (int32_T)c15_i8;
    c15_i8 = (int64_T)c15_bitsIn - (int64_T)c15_bitsleft;
    if (c15_i8 > 2147483647L) {
      c15_i8 = 2147483647L;
    } else {
      if (c15_i8 <= -2147483648L) {
        c15_i8 = -2147483648L;
      }
    }

    c15_saturatedUnaryMinus = (int32_T)c15_i8;
    if (c15_saturatedUnaryMinus <= MIN_int32_T) {
      c15_saturatedUnaryMinus = MAX_int32_T;
    } else {
      c15_saturatedUnaryMinus = -c15_saturatedUnaryMinus;
    }

    c15_valIn = 0U;
    if (c15_saturatedUnaryMinus < 0) {
      c15_saturatedUnaryMinus = -c15_saturatedUnaryMinus;
      if (c15_saturatedUnaryMinus > 255) {
        c15_saturatedUnaryMinus = 255;
      }

      c15_absk1 = (uint8_T)c15_saturatedUnaryMinus;
      if (c15_absk1 < 32) {
        c15_valIn = c15_val >> (uint32_T)c15_absk1;
      }
    } else {
      if (c15_saturatedUnaryMinus <= 0) {
        c15_saturatedUnaryMinus = 0;
      } else {
        if (c15_saturatedUnaryMinus > 255) {
          c15_saturatedUnaryMinus = 255;
        }
      }

      c15_absk1 = (uint8_T)c15_saturatedUnaryMinus;
      if (c15_absk1 < 32) {
        c15_valIn = c15_val << (uint32_T)c15_absk1;
      }
    }

    *c15_TempO = c15_Temp | c15_valIn;
    c15_out[sf_mex_lw_bounds_check((int32_T)c15_outpos, 1, 20) - 1] = *c15_TempO;
    *c15_outposO = c15_outpos + 1.0;
    if (*c15_outposO > 20.0) {
      *c15_flag = 0.0;
    } else {
      *c15_TempO = 0U;
      *c15_bitposO = 0;
      c15_i8 = (int64_T)c15_bitsIn - (int64_T)c15_bitsleft;
      if (c15_i8 > 2147483647L) {
        c15_i8 = 2147483647L;
      } else {
        if (c15_i8 <= -2147483648L) {
          c15_i8 = -2147483648L;
        }
      }

      c15_bitsIn = (int32_T)c15_i8;
      c15_i8 = (int64_T)32 - (int64_T)c15_bitsIn;
      if (c15_i8 > 2147483647L) {
        c15_i8 = 2147483647L;
      } else {
        if (c15_i8 <= -2147483648L) {
          c15_i8 = -2147483648L;
        }
      }

      c15_saturatedUnaryMinus = (int32_T)c15_i8;
      c15_valIn = 0U;
      if (c15_saturatedUnaryMinus < 0) {
        c15_saturatedUnaryMinus = -c15_saturatedUnaryMinus;
        if (c15_saturatedUnaryMinus <= 0) {
          c15_saturatedUnaryMinus = 0;
        } else {
          if (c15_saturatedUnaryMinus > 255) {
            c15_saturatedUnaryMinus = 255;
          }
        }

        c15_absk1 = (uint8_T)c15_saturatedUnaryMinus;
        if (c15_absk1 < 32) {
          c15_valIn = c15_val >> (uint32_T)c15_absk1;
        }
      } else {
        if (c15_saturatedUnaryMinus <= 0) {
          c15_saturatedUnaryMinus = 0;
        } else {
          if (c15_saturatedUnaryMinus > 255) {
            c15_saturatedUnaryMinus = 255;
          }
        }

        c15_absk1 = (uint8_T)c15_saturatedUnaryMinus;
        if (c15_absk1 < 32) {
          c15_valIn = c15_val << (uint32_T)c15_absk1;
        }
      }

      c15_a = c15_valIn;
      c15_i8 = (int64_T)32 - (int64_T)c15_bitsIn;
      if (c15_i8 > 2147483647L) {
        c15_i8 = 2147483647L;
      } else {
        if (c15_i8 <= -2147483648L) {
          c15_i8 = -2147483648L;
        }
      }

      c15_saturatedUnaryMinus = -(int32_T)c15_i8;
      c15_valIn = 0U;
      if (c15_saturatedUnaryMinus < 0) {
        c15_saturatedUnaryMinus = -c15_saturatedUnaryMinus;
        if (c15_saturatedUnaryMinus <= 0) {
          c15_saturatedUnaryMinus = 0;
        } else {
          if (c15_saturatedUnaryMinus > 255) {
            c15_saturatedUnaryMinus = 255;
          }
        }

        c15_absk1 = (uint8_T)c15_saturatedUnaryMinus;
        if (c15_absk1 < 32) {
          c15_valIn = c15_a >> (uint32_T)c15_absk1;
        }
      } else {
        if (c15_saturatedUnaryMinus <= 0) {
          c15_saturatedUnaryMinus = 0;
        } else {
          if (c15_saturatedUnaryMinus > 255) {
            c15_saturatedUnaryMinus = 255;
          }
        }

        c15_absk1 = (uint8_T)c15_saturatedUnaryMinus;
        if (c15_absk1 < 32) {
          c15_valIn = c15_a << (uint32_T)c15_absk1;
        }
      }

      c15_guard1 = TRUE;
    }
  } else {
    c15_guard1 = TRUE;
  }

  if (c15_guard1 == TRUE) {
    c15_a = c15_valIn;
    c15_i8 = (int64_T)c15_bitsIn + (int64_T)*c15_bitposO;
    if (c15_i8 > 2147483647L) {
      c15_i8 = 2147483647L;
    } else {
      if (c15_i8 <= -2147483648L) {
        c15_i8 = -2147483648L;
      }
    }

    c15_i8 = (int64_T)32 - (int64_T)(int32_T)c15_i8;
    if (c15_i8 > 2147483647L) {
      c15_i8 = 2147483647L;
    } else {
      if (c15_i8 <= -2147483648L) {
        c15_i8 = -2147483648L;
      }
    }

    c15_saturatedUnaryMinus = (int32_T)c15_i8;
    c15_valIn = 0U;
    if (c15_saturatedUnaryMinus < 0) {
      c15_saturatedUnaryMinus = -c15_saturatedUnaryMinus;
      if (c15_saturatedUnaryMinus <= 0) {
        c15_saturatedUnaryMinus = 0;
      } else {
        if (c15_saturatedUnaryMinus > 255) {
          c15_saturatedUnaryMinus = 255;
        }
      }

      c15_absk1 = (uint8_T)c15_saturatedUnaryMinus;
      if (c15_absk1 < 32) {
        c15_valIn = c15_a >> (uint32_T)c15_absk1;
      }
    } else {
      if (c15_saturatedUnaryMinus <= 0) {
        c15_saturatedUnaryMinus = 0;
      } else {
        if (c15_saturatedUnaryMinus > 255) {
          c15_saturatedUnaryMinus = 255;
        }
      }

      c15_absk1 = (uint8_T)c15_saturatedUnaryMinus;
      if (c15_absk1 < 32) {
        c15_valIn = c15_a << (uint32_T)c15_absk1;
      }
    }

    *c15_TempO |= c15_valIn;
    c15_i8 = (int64_T)*c15_bitposO + (int64_T)c15_bitsIn;
    if (c15_i8 > 2147483647L) {
      c15_i8 = 2147483647L;
    } else {
      if (c15_i8 <= -2147483648L) {
        c15_i8 = -2147483648L;
      }
    }

    *c15_bitposO = (int32_T)c15_i8;
    *c15_flag = 1.0;
  }
}

static void init_dsm_address_info(SFc15_videoInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c15_video_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3832975803U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2120001566U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4005946966U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2003834566U);
}

mxArray *sf_c15_video_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(4232487868U);
    pr[1] = (double)(1311394154U);
    pr[2] = (double)(2571272459U);
    pr[3] = (double)(2123894124U);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c15_video(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"out\",},{M[4],M[0],T\"prev_out\",S'l','i','p'{{M1x2[264 272],M[0],}}},{M[8],M[0],T\"is_active_c15_video\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c15_video_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void sf_opaque_initialize_c15_video(void *chartInstanceVar)
{
  initialize_params_c15_video((SFc15_videoInstanceStruct*) chartInstanceVar);
  initialize_c15_video((SFc15_videoInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c15_video(void *chartInstanceVar)
{
  enable_c15_video((SFc15_videoInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c15_video(void *chartInstanceVar)
{
  disable_c15_video((SFc15_videoInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c15_video(void *chartInstanceVar)
{
  sf_c15_video((SFc15_videoInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c15_video(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c15_video((SFc15_videoInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c15_video();/* state var info */
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

extern void sf_internal_set_sim_state_c15_video(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c15_video();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c15_video((SFc15_videoInstanceStruct*)chartInfo->chartInstance,
    mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c15_video(SimStruct* S)
{
  return sf_internal_get_sim_state_c15_video(S);
}

static void sf_opaque_set_sim_state_c15_video(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c15_video(S, st);
}

static void sf_opaque_terminate_c15_video(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc15_videoInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c15_video((SFc15_videoInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc15_video((SFc15_videoInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c15_video(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c15_video((SFc15_videoInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c15_video(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"video","video",15);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"video","video",15,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"video","video",15,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"video","video",15,1);
      sf_mark_chart_reusable_outputs(S,"video","video",15,1);
    }

    sf_set_rtw_dwork_info(S,"video","video",15);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3761957463U));
  ssSetChecksum1(S,(3661021555U));
  ssSetChecksum2(S,(1336052382U));
  ssSetChecksum3(S,(4069991243U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c15_video(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "video", "video",15);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c15_video(SimStruct *S)
{
  SFc15_videoInstanceStruct *chartInstance;
  chartInstance = (SFc15_videoInstanceStruct *)malloc(sizeof
    (SFc15_videoInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc15_videoInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c15_video;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c15_video;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c15_video;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c15_video;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c15_video;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c15_video;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c15_video;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c15_video;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c15_video;
  chartInstance->chartInfo.mdlStart = mdlStart_c15_video;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c15_video;
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

void c15_video_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c15_video(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c15_video(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c15_video(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c15_video_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
