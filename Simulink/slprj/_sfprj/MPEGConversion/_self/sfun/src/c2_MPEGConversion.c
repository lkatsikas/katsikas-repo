/* Include files */

#include "blascompat32.h"
#include "MPEGConversion_sfun.h"
#include "c2_MPEGConversion.h"
#include "mwmathutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void initialize_c2_MPEGConversion(SFc2_MPEGConversionInstanceStruct
  *chartInstance);
static void initialize_params_c2_MPEGConversion
  (SFc2_MPEGConversionInstanceStruct *chartInstance);
static void enable_c2_MPEGConversion(SFc2_MPEGConversionInstanceStruct
  *chartInstance);
static void disable_c2_MPEGConversion(SFc2_MPEGConversionInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_MPEGConversion
  (SFc2_MPEGConversionInstanceStruct *chartInstance);
static void set_sim_state_c2_MPEGConversion(SFc2_MPEGConversionInstanceStruct
  *chartInstance, const mxArray *c2_st);
static void finalize_c2_MPEGConversion(SFc2_MPEGConversionInstanceStruct
  *chartInstance);
static void sf_c2_MPEGConversion(SFc2_MPEGConversionInstanceStruct
  *chartInstance);
static void c2_chartstep_c2_MPEGConversion(SFc2_MPEGConversionInstanceStruct
  *chartInstance);
static void initSimStructsc2_MPEGConversion(SFc2_MPEGConversionInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[16]);
static void c2_eml_error(SFc2_MPEGConversionInstanceStruct *chartInstance);
static void c2_emlrt_marshallIn(SFc2_MPEGConversionInstanceStruct *chartInstance,
  const mxArray *c2_out, const char_T *c2_identifier, uint32_T c2_y[20]);
static void c2_b_emlrt_marshallIn(SFc2_MPEGConversionInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  uint32_T c2_y[20]);
static void c2_c_emlrt_marshallIn(SFc2_MPEGConversionInstanceStruct
  *chartInstance, const mxArray *c2_b_prev_out, const char_T *c2_identifier,
  uint32_T c2_y[20]);
static void c2_d_emlrt_marshallIn(SFc2_MPEGConversionInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  uint32_T c2_y[20]);
static uint8_T c2_e_emlrt_marshallIn(SFc2_MPEGConversionInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_MPEGConversion, const char_T *
  c2_identifier);
static uint8_T c2_f_emlrt_marshallIn(SFc2_MPEGConversionInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_putbits(SFc2_MPEGConversionInstanceStruct *chartInstance, int32_T
  c2_bitpos, uint32_T c2_out[20], uint32_T c2_Temp, real_T c2_outpos, uint32_T
  c2_val, real_T c2_bits, real_T *c2_flag, int32_T *c2_bitposO, uint32_T
  *c2_TempO, real_T *c2_outposO);
static void init_dsm_address_info(SFc2_MPEGConversionInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_MPEGConversion(SFc2_MPEGConversionInstanceStruct
  *chartInstance)
{
  int32_T c2_i0;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_prev_out_not_empty = FALSE;
  chartInstance->c2_is_active_c2_MPEGConversion = 0U;
  for (c2_i0 = 0; c2_i0 < 20; c2_i0++) {
    chartInstance->c2_prev_out[c2_i0] = 0U;
  }
}

static void initialize_params_c2_MPEGConversion
  (SFc2_MPEGConversionInstanceStruct *chartInstance)
{
}

static void enable_c2_MPEGConversion(SFc2_MPEGConversionInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_MPEGConversion(SFc2_MPEGConversionInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static const mxArray *get_sim_state_c2_MPEGConversion
  (SFc2_MPEGConversionInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i1;
  uint32_T c2_u[20];
  const mxArray *c2_b_y = NULL;
  uint32_T c2_b_u[20];
  const mxArray *c2_c_y = NULL;
  uint8_T c2_c_u;
  const mxArray *c2_d_y = NULL;
  uint32_T (*c2_out)[20];
  c2_out = (uint32_T (*)[20])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(3));
  for (c2_i1 = 0; c2_i1 < 20; c2_i1++) {
    c2_u[c2_i1] = (*c2_out)[c2_i1];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 7, 0U, 1U, 0U, 1, 20));
  sf_mex_setcell(c2_y, 0, c2_b_y);
  for (c2_i1 = 0; c2_i1 < 20; c2_i1++) {
    c2_b_u[c2_i1] = chartInstance->c2_prev_out[c2_i1];
  }

  c2_c_y = NULL;
  if (!chartInstance->c2_prev_out_not_empty) {
    sf_mex_assign(&c2_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_b_u, 7, 0U, 1U, 0U, 1, 20));
  }

  sf_mex_setcell(c2_y, 1, c2_c_y);
  c2_c_u = chartInstance->c2_is_active_c2_MPEGConversion;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_c_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c2_y, 2, c2_d_y);
  sf_mex_assign(&c2_st, c2_y);
  return c2_st;
}

static void set_sim_state_c2_MPEGConversion(SFc2_MPEGConversionInstanceStruct
  *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  uint32_T c2_uv0[20];
  int32_T c2_i2;
  uint32_T (*c2_out)[20];
  c2_out = (uint32_T (*)[20])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)), "out",
                      c2_uv0);
  for (c2_i2 = 0; c2_i2 < 20; c2_i2++) {
    (*c2_out)[c2_i2] = c2_uv0[c2_i2];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)),
                        "prev_out", c2_uv0);
  for (c2_i2 = 0; c2_i2 < 20; c2_i2++) {
    chartInstance->c2_prev_out[c2_i2] = c2_uv0[c2_i2];
  }

  chartInstance->c2_is_active_c2_MPEGConversion = c2_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 2)),
     "is_active_c2_MPEGConversion");
  sf_mex_destroy(&c2_u);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_MPEGConversion(SFc2_MPEGConversionInstanceStruct
  *chartInstance)
{
}

static void sf_c2_MPEGConversion(SFc2_MPEGConversionInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  c2_chartstep_c2_MPEGConversion(chartInstance);
}

static void c2_chartstep_c2_MPEGConversion(SFc2_MPEGConversionInstanceStruct
  *chartInstance)
{
  int32_T c2_out1;
  real_T c2_in[64];
  uint32_T c2_out[20];
  int32_T c2_bitpos;
  uint32_T c2_Temp;
  real_T c2_outpos;
  real_T c2_x;
  real32_T c2_pval;
  int32_T c2_bitsIn;
  int32_T c2_exitg1;
  real32_T c2_cval;
  boolean_T c2_guard1 = FALSE;
  real_T c2_b_outpos;
  uint32_T c2_b_Temp;
  int32_T c2_b_bitpos;
  uint32_T c2_valIn;
  int64_T c2_i3;
  boolean_T c2_guard2 = FALSE;
  uint8_T c2_absk1;
  boolean_T c2_b_guard1 = FALSE;
  uint32_T (*c2_b_out)[20];
  real_T (*c2_b_in)[64];
  c2_b_out = (uint32_T (*)[20])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_b_in = (real_T (*)[64])ssGetInputPortSignal(chartInstance->S, 0);
  for (c2_out1 = 0; c2_out1 < 64; c2_out1++) {
    c2_in[c2_out1] = (*c2_b_in)[c2_out1];
  }

  chartInstance->c2_prev_out_not_empty = TRUE;
  for (c2_out1 = 0; c2_out1 < 20; c2_out1++) {
    c2_out[c2_out1] = chartInstance->c2_prev_out[c2_out1];
  }

  c2_bitpos = 0;
  c2_Temp = 0U;
  c2_outpos = 2.0;
  if ((*c2_b_in)[0] > 0.0) {
    c2_x = muDoubleScalarFloor((*c2_b_in)[0]);
  } else {
    c2_x = muDoubleScalarCeil((*c2_b_in)[0]);
  }

  c2_x = c2_x < 0.0 ? muDoubleScalarCeil(c2_x - 0.5) : muDoubleScalarFloor(c2_x
    + 0.5);
  if (c2_x < 2.147483648E+9) {
    if (c2_x >= -2.147483648E+9) {
      c2_out1 = (int32_T)c2_x;
    } else {
      c2_out1 = MIN_int32_T;
    }
  } else if (c2_x >= 2.147483648E+9) {
    c2_out1 = MAX_int32_T;
  } else {
    c2_out1 = 0;
  }

  if (c2_out1 >= -1) {
    if (c2_out1 <= 0) {
      c2_out1 = 0;
    }

    c2_out[0] = (uint32_T)c2_out1;
  } else {
    if (c2_out1 <= MIN_int32_T) {
      c2_out1 = MAX_int32_T;
    } else {
      c2_out1 = -c2_out1;
    }

    c2_out[0] = 1U - (uint32_T)c2_out1;
  }

  c2_x = (*c2_b_in)[1] + 0.5;
  if (c2_x > 0.0) {
    c2_x = muDoubleScalarFloor(c2_x);
  } else {
    c2_x = muDoubleScalarCeil(c2_x);
  }

  c2_pval = (real32_T)c2_x;
  if ((real_T)c2_pval > 127.0) {
    c2_pval = 127.0F;
  }

  if ((real_T)c2_pval < -128.0) {
    c2_pval = -128.0F;
  }

  c2_out1 = 0;
  c2_bitsIn = 3;
  do {
    c2_exitg1 = 0U;
    if (c2_bitsIn <= 64) {
      c2_cval = (real32_T)muDoubleScalarFloor(c2_in[c2_bitsIn - 1] + 0.5);
      c2_guard1 = FALSE;
      if ((c2_pval == c2_cval) && (c2_out1 < 14)) {
        c2_out1 = (int32_T)((uint32_T)c2_out1 + 1U);
        c2_guard1 = TRUE;
      } else {
        c2_putbits(chartInstance, c2_bitpos, c2_out, c2_Temp, c2_outpos,
                   (uint32_T)c2_out1, 4.0, &c2_x, &c2_b_bitpos, &c2_b_Temp,
                   &c2_b_outpos);
        if (!(c2_x != 0.0)) {
          for (c2_out1 = 0; c2_out1 < 20; c2_out1++) {
            chartInstance->c2_prev_out[c2_out1] = c2_out[c2_out1];
          }

          c2_exitg1 = 1U;
        } else {
          if ((real_T)c2_pval > 127.0) {
            c2_pval = 127.0F;
          }

          if ((real_T)c2_pval < -128.0) {
            c2_pval = -128.0F;
          }

          c2_pval += 128.0F;
          if ((c2_pval < 8.388608E+6F) && (c2_pval > -8.388608E+6F)) {
            c2_pval = muSingleScalarFloor(c2_pval + 0.5F);
          }

          if (c2_pval < 4.2949673E+9F) {
            c2_valIn = (uint32_T)c2_pval;
          } else {
            c2_valIn = 0U;
          }

          c2_putbits(chartInstance, c2_b_bitpos, c2_out, c2_b_Temp, c2_b_outpos,
                     c2_valIn, 8.0, &c2_x, &c2_bitpos, &c2_Temp, &c2_outpos);
          if (!(c2_x != 0.0)) {
            for (c2_out1 = 0; c2_out1 < 20; c2_out1++) {
              chartInstance->c2_prev_out[c2_out1] = c2_out[c2_out1];
            }

            c2_exitg1 = 1U;
          } else {
            c2_out1 = 0;
            c2_guard1 = TRUE;
          }
        }
      }

      if (c2_guard1 == TRUE) {
        c2_pval = c2_cval;
        c2_bitsIn++;
        sf_mex_listen_for_ctrl_c(chartInstance->S);
      }
    } else {
      c2_putbits(chartInstance, c2_bitpos, c2_out, c2_Temp, c2_outpos, (uint32_T)
                 c2_out1, 4.0, &c2_x, &c2_b_bitpos, &c2_b_Temp, &c2_b_outpos);
      if (!(c2_x != 0.0)) {
        for (c2_out1 = 0; c2_out1 < 20; c2_out1++) {
          chartInstance->c2_prev_out[c2_out1] = c2_out[c2_out1];
        }
      } else {
        if ((real_T)c2_pval > 127.0) {
          c2_pval = 127.0F;
        }

        if ((real_T)c2_pval < -128.0) {
          c2_pval = -128.0F;
        }

        c2_pval += 128.0F;
        if ((c2_pval < 8.388608E+6F) && (c2_pval > -8.388608E+6F)) {
          c2_pval = muSingleScalarFloor(c2_pval + 0.5F);
        }

        if (c2_pval < 4.2949673E+9F) {
          c2_valIn = (uint32_T)c2_pval;
        } else {
          c2_valIn = 0U;
        }

        c2_bitsIn = 8;
        c2_i3 = (int64_T)c2_b_bitpos + (int64_T)8;
        if (c2_i3 > 2147483647L) {
          c2_i3 = 2147483647L;
        } else {
          if (c2_i3 <= -2147483648L) {
            c2_i3 = -2147483648L;
          }
        }

        c2_guard2 = FALSE;
        if ((int32_T)c2_i3 > 32) {
          c2_i3 = (int64_T)32 - (int64_T)c2_b_bitpos;
          if (c2_i3 > 2147483647L) {
            c2_i3 = 2147483647L;
          } else {
            if (c2_i3 <= -2147483648L) {
              c2_i3 = -2147483648L;
            }
          }

          c2_bitsIn = (int32_T)c2_i3 - 8;
          c2_out1 = -(-c2_bitsIn);
          c2_Temp = 0U;
          if (c2_out1 < 0) {
            c2_out1 = -c2_out1;
            if (c2_out1 <= 0) {
              c2_out1 = 0;
            } else {
              if (c2_out1 > 255) {
                c2_out1 = 255;
              }
            }

            c2_absk1 = (uint8_T)c2_out1;
            if (c2_absk1 < 32) {
              c2_Temp = c2_valIn >> (uint32_T)c2_absk1;
            }
          } else {
            if (c2_out1 <= 0) {
              c2_out1 = 0;
            } else {
              if (c2_out1 > 255) {
                c2_out1 = 255;
              }
            }

            c2_absk1 = (uint8_T)c2_out1;
            if (c2_absk1 < 32) {
              c2_Temp = c2_valIn << (uint32_T)c2_absk1;
            }
          }

          c2_b_Temp |= c2_Temp;
          c2_out[sf_mex_lw_bounds_check((int32_T)c2_b_outpos, 1, 20) - 1] =
            c2_b_Temp;
          c2_b_outpos++;
          if (c2_b_outpos > 20.0) {
            c2_out1 = 0;
          } else {
            c2_b_Temp = 0U;
            c2_b_bitpos = 0;
            c2_bitsIn = -c2_bitsIn;
            c2_Temp = c2_valIn;
            c2_i3 = (int64_T)32 - (int64_T)c2_bitsIn;
            if (c2_i3 > 2147483647L) {
              c2_i3 = 2147483647L;
            } else {
              if (c2_i3 <= -2147483648L) {
                c2_i3 = -2147483648L;
              }
            }

            c2_out1 = (int32_T)c2_i3;
            c2_valIn = 0U;
            if (c2_out1 < 0) {
              c2_out1 = -c2_out1;
              if (c2_out1 <= 0) {
                c2_out1 = 0;
              } else {
                if (c2_out1 > 255) {
                  c2_out1 = 255;
                }
              }

              c2_absk1 = (uint8_T)c2_out1;
              if (c2_absk1 < 32) {
                c2_valIn = c2_Temp >> (uint32_T)c2_absk1;
              }
            } else {
              if (c2_out1 <= 0) {
                c2_out1 = 0;
              } else {
                if (c2_out1 > 255) {
                  c2_out1 = 255;
                }
              }

              c2_absk1 = (uint8_T)c2_out1;
              if (c2_absk1 < 32) {
                c2_valIn = c2_Temp << (uint32_T)c2_absk1;
              }
            }

            c2_Temp = c2_valIn;
            c2_i3 = (int64_T)32 - (int64_T)c2_bitsIn;
            if (c2_i3 > 2147483647L) {
              c2_i3 = 2147483647L;
            } else {
              if (c2_i3 <= -2147483648L) {
                c2_i3 = -2147483648L;
              }
            }

            c2_out1 = -(int32_T)c2_i3;
            c2_valIn = 0U;
            if (c2_out1 < 0) {
              c2_out1 = -c2_out1;
              if (c2_out1 <= 0) {
                c2_out1 = 0;
              } else {
                if (c2_out1 > 255) {
                  c2_out1 = 255;
                }
              }

              c2_absk1 = (uint8_T)c2_out1;
              if (c2_absk1 < 32) {
                c2_valIn = c2_Temp >> (uint32_T)c2_absk1;
              }
            } else {
              if (c2_out1 <= 0) {
                c2_out1 = 0;
              } else {
                if (c2_out1 > 255) {
                  c2_out1 = 255;
                }
              }

              c2_absk1 = (uint8_T)c2_out1;
              if (c2_absk1 < 32) {
                c2_valIn = c2_Temp << (uint32_T)c2_absk1;
              }
            }

            c2_guard2 = TRUE;
          }
        } else {
          c2_guard2 = TRUE;
        }

        if (c2_guard2 == TRUE) {
          c2_Temp = c2_valIn;
          c2_i3 = (int64_T)c2_bitsIn + (int64_T)c2_b_bitpos;
          if (c2_i3 > 2147483647L) {
            c2_i3 = 2147483647L;
          } else {
            if (c2_i3 <= -2147483648L) {
              c2_i3 = -2147483648L;
            }
          }

          c2_i3 = (int64_T)32 - (int64_T)(int32_T)c2_i3;
          if (c2_i3 > 2147483647L) {
            c2_i3 = 2147483647L;
          } else {
            if (c2_i3 <= -2147483648L) {
              c2_i3 = -2147483648L;
            }
          }

          c2_out1 = (int32_T)c2_i3;
          c2_valIn = 0U;
          if (c2_out1 < 0) {
            c2_out1 = -c2_out1;
            if (c2_out1 <= 0) {
              c2_out1 = 0;
            } else {
              if (c2_out1 > 255) {
                c2_out1 = 255;
              }
            }

            c2_absk1 = (uint8_T)c2_out1;
            if (c2_absk1 < 32) {
              c2_valIn = c2_Temp >> (uint32_T)c2_absk1;
            }
          } else {
            if (c2_out1 <= 0) {
              c2_out1 = 0;
            } else {
              if (c2_out1 > 255) {
                c2_out1 = 255;
              }
            }

            c2_absk1 = (uint8_T)c2_out1;
            if (c2_absk1 < 32) {
              c2_valIn = c2_Temp << (uint32_T)c2_absk1;
            }
          }

          c2_b_Temp |= c2_valIn;
          c2_i3 = (int64_T)c2_b_bitpos + (int64_T)c2_bitsIn;
          if (c2_i3 > 2147483647L) {
            c2_i3 = 2147483647L;
          } else {
            if (c2_i3 <= -2147483648L) {
              c2_i3 = -2147483648L;
            }
          }

          c2_b_bitpos = (int32_T)c2_i3;
          c2_out1 = 1;
        }

        if (!(c2_out1 != 0)) {
          for (c2_out1 = 0; c2_out1 < 20; c2_out1++) {
            chartInstance->c2_prev_out[c2_out1] = c2_out[c2_out1];
          }
        } else {
          c2_valIn = 15U;
          c2_bitsIn = 4;
          c2_i3 = (int64_T)c2_b_bitpos + (int64_T)4;
          if (c2_i3 > 2147483647L) {
            c2_i3 = 2147483647L;
          } else {
            if (c2_i3 <= -2147483648L) {
              c2_i3 = -2147483648L;
            }
          }

          c2_b_guard1 = FALSE;
          if ((int32_T)c2_i3 > 32) {
            c2_i3 = (int64_T)32 - (int64_T)c2_b_bitpos;
            if (c2_i3 > 2147483647L) {
              c2_i3 = 2147483647L;
            } else {
              if (c2_i3 <= -2147483648L) {
                c2_i3 = -2147483648L;
              }
            }

            c2_bitsIn = (int32_T)c2_i3 - 4;
            c2_out1 = -(-c2_bitsIn);
            c2_Temp = 0U;
            if (c2_out1 < 0) {
              c2_out1 = -c2_out1;
              if (c2_out1 <= 0) {
                c2_out1 = 0;
              } else {
                if (c2_out1 > 255) {
                  c2_out1 = 255;
                }
              }

              c2_absk1 = (uint8_T)c2_out1;
              if (c2_absk1 < 32) {
                c2_Temp = 15U >> (uint32_T)c2_absk1;
              }
            } else {
              if (c2_out1 <= 0) {
                c2_out1 = 0;
              } else {
                if (c2_out1 > 255) {
                  c2_out1 = 255;
                }
              }

              c2_absk1 = (uint8_T)c2_out1;
              if (c2_absk1 < 32) {
                c2_Temp = 15U << (uint32_T)c2_absk1;
              }
            }

            c2_b_Temp |= c2_Temp;
            c2_out[sf_mex_lw_bounds_check((int32_T)c2_b_outpos, 1, 20) - 1] =
              c2_b_Temp;
            c2_b_outpos++;
            if (c2_b_outpos > 20.0) {
              c2_out1 = 0;
            } else {
              c2_b_Temp = 0U;
              c2_b_bitpos = 0;
              c2_bitsIn = -c2_bitsIn;
              c2_i3 = (int64_T)32 - (int64_T)c2_bitsIn;
              if (c2_i3 > 2147483647L) {
                c2_i3 = 2147483647L;
              } else {
                if (c2_i3 <= -2147483648L) {
                  c2_i3 = -2147483648L;
                }
              }

              c2_out1 = (int32_T)c2_i3;
              c2_valIn = 0U;
              if (c2_out1 < 0) {
                c2_out1 = -c2_out1;
                if (c2_out1 <= 0) {
                  c2_out1 = 0;
                } else {
                  if (c2_out1 > 255) {
                    c2_out1 = 255;
                  }
                }

                c2_absk1 = (uint8_T)c2_out1;
                if (c2_absk1 < 32) {
                  c2_valIn = 15U >> (uint32_T)c2_absk1;
                }
              } else {
                if (c2_out1 <= 0) {
                  c2_out1 = 0;
                } else {
                  if (c2_out1 > 255) {
                    c2_out1 = 255;
                  }
                }

                c2_absk1 = (uint8_T)c2_out1;
                if (c2_absk1 < 32) {
                  c2_valIn = 15U << (uint32_T)c2_absk1;
                }
              }

              c2_Temp = c2_valIn;
              c2_i3 = (int64_T)32 - (int64_T)c2_bitsIn;
              if (c2_i3 > 2147483647L) {
                c2_i3 = 2147483647L;
              } else {
                if (c2_i3 <= -2147483648L) {
                  c2_i3 = -2147483648L;
                }
              }

              c2_out1 = -(int32_T)c2_i3;
              c2_valIn = 0U;
              if (c2_out1 < 0) {
                c2_out1 = -c2_out1;
                if (c2_out1 <= 0) {
                  c2_out1 = 0;
                } else {
                  if (c2_out1 > 255) {
                    c2_out1 = 255;
                  }
                }

                c2_absk1 = (uint8_T)c2_out1;
                if (c2_absk1 < 32) {
                  c2_valIn = c2_Temp >> (uint32_T)c2_absk1;
                }
              } else {
                if (c2_out1 <= 0) {
                  c2_out1 = 0;
                } else {
                  if (c2_out1 > 255) {
                    c2_out1 = 255;
                  }
                }

                c2_absk1 = (uint8_T)c2_out1;
                if (c2_absk1 < 32) {
                  c2_valIn = c2_Temp << (uint32_T)c2_absk1;
                }
              }

              c2_b_guard1 = TRUE;
            }
          } else {
            c2_b_guard1 = TRUE;
          }

          if (c2_b_guard1 == TRUE) {
            c2_Temp = c2_valIn;
            c2_i3 = (int64_T)c2_bitsIn + (int64_T)c2_b_bitpos;
            if (c2_i3 > 2147483647L) {
              c2_i3 = 2147483647L;
            } else {
              if (c2_i3 <= -2147483648L) {
                c2_i3 = -2147483648L;
              }
            }

            c2_i3 = (int64_T)32 - (int64_T)(int32_T)c2_i3;
            if (c2_i3 > 2147483647L) {
              c2_i3 = 2147483647L;
            } else {
              if (c2_i3 <= -2147483648L) {
                c2_i3 = -2147483648L;
              }
            }

            c2_out1 = (int32_T)c2_i3;
            c2_valIn = 0U;
            if (c2_out1 < 0) {
              c2_out1 = -c2_out1;
              if (c2_out1 <= 0) {
                c2_out1 = 0;
              } else {
                if (c2_out1 > 255) {
                  c2_out1 = 255;
                }
              }

              c2_absk1 = (uint8_T)c2_out1;
              if (c2_absk1 < 32) {
                c2_valIn = c2_Temp >> (uint32_T)c2_absk1;
              }
            } else {
              if (c2_out1 <= 0) {
                c2_out1 = 0;
              } else {
                if (c2_out1 > 255) {
                  c2_out1 = 255;
                }
              }

              c2_absk1 = (uint8_T)c2_out1;
              if (c2_absk1 < 32) {
                c2_valIn = c2_Temp << (uint32_T)c2_absk1;
              }
            }

            c2_b_Temp |= c2_valIn;
            c2_out1 = 1;
          }

          if ((c2_out1 != 0) && (!(c2_b_outpos > 21.0))) {
            c2_out[sf_mex_lw_bounds_check((int32_T)c2_b_outpos, 1, 20) - 1] =
              c2_b_Temp;
          }

          for (c2_out1 = 0; c2_out1 < 20; c2_out1++) {
            chartInstance->c2_prev_out[c2_out1] = c2_out[c2_out1];
          }
        }
      }

      c2_exitg1 = 1U;
    }
  } while (c2_exitg1 == 0U);

  for (c2_out1 = 0; c2_out1 < 20; c2_out1++) {
    (*c2_b_out)[c2_out1] = c2_out[c2_out1];
  }
}

static void initSimStructsc2_MPEGConversion(SFc2_MPEGConversionInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

const mxArray *sf_c2_MPEGConversion_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo;
  c2_ResolvedFunctionInfo c2_info[16];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i4;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_info_helper(c2_info);
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 16));
  for (c2_i4 = 0; c2_i4 < 16; c2_i4++) {
    c2_r0 = &c2_info[c2_i4];
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->context)), "context", "nameCaptureInfo",
                    c2_i4);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c2_r0->name)), "name", "nameCaptureInfo", c2_i4);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c2_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c2_i4);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->resolved)), "resolved", "nameCaptureInfo",
                    c2_i4);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c2_i4);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c2_i4);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c2_i4);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c2_i4);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m0);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[16])
{
  c2_info[0].context = "";
  c2_info[0].name = "fix";
  c2_info[0].dominantType = "double";
  c2_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/fix.m";
  c2_info[0].fileTimeLo = 1286815142U;
  c2_info[0].fileTimeHi = 0U;
  c2_info[0].mFileTimeLo = 0U;
  c2_info[0].mFileTimeHi = 0U;
  c2_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/fix.m";
  c2_info[1].name = "eml_scalar_fix";
  c2_info[1].dominantType = "double";
  c2_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_fix.m";
  c2_info[1].fileTimeLo = 1286815126U;
  c2_info[1].fileTimeHi = 0U;
  c2_info[1].mFileTimeLo = 0U;
  c2_info[1].mFileTimeHi = 0U;
  c2_info[2].context = "";
  c2_info[2].name = "intmax";
  c2_info[2].dominantType = "char";
  c2_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[2].fileTimeLo = 1286815156U;
  c2_info[2].fileTimeHi = 0U;
  c2_info[2].mFileTimeLo = 0U;
  c2_info[2].mFileTimeHi = 0U;
  c2_info[3].context = "";
  c2_info[3].name = "abs";
  c2_info[3].dominantType = "int32";
  c2_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[3].fileTimeLo = 1286815094U;
  c2_info[3].fileTimeHi = 0U;
  c2_info[3].mFileTimeLo = 0U;
  c2_info[3].mFileTimeHi = 0U;
  c2_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[4].name = "eml_scalar_abs";
  c2_info[4].dominantType = "int32";
  c2_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c2_info[4].fileTimeLo = 1286815112U;
  c2_info[4].fileTimeHi = 0U;
  c2_info[4].mFileTimeLo = 0U;
  c2_info[4].mFileTimeHi = 0U;
  c2_info[5].context = "";
  c2_info[5].name = "floor";
  c2_info[5].dominantType = "double";
  c2_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[5].fileTimeLo = 1286815142U;
  c2_info[5].fileTimeHi = 0U;
  c2_info[5].mFileTimeLo = 0U;
  c2_info[5].mFileTimeHi = 0U;
  c2_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[6].name = "eml_scalar_floor";
  c2_info[6].dominantType = "double";
  c2_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c2_info[6].fileTimeLo = 1286815126U;
  c2_info[6].fileTimeHi = 0U;
  c2_info[6].mFileTimeLo = 0U;
  c2_info[6].mFileTimeHi = 0U;
  c2_info[7].context = "";
  c2_info[7].name = "bitshift";
  c2_info[7].dominantType = "uint32";
  c2_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c2_info[7].fileTimeLo = 1286815238U;
  c2_info[7].fileTimeHi = 0U;
  c2_info[7].mFileTimeLo = 0U;
  c2_info[7].mFileTimeHi = 0U;
  c2_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c2_info[8].name = "eml_isa_uint";
  c2_info[8].dominantType = "uint32";
  c2_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  c2_info[8].fileTimeLo = 1286815184U;
  c2_info[8].fileTimeHi = 0U;
  c2_info[8].mFileTimeLo = 0U;
  c2_info[8].mFileTimeHi = 0U;
  c2_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c2_info[9].name = "eml_int_nbits";
  c2_info[9].dominantType = "char";
  c2_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_nbits.m";
  c2_info[9].fileTimeLo = 1286815180U;
  c2_info[9].fileTimeHi = 0U;
  c2_info[9].mFileTimeLo = 0U;
  c2_info[9].mFileTimeHi = 0U;
  c2_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c2_info[10].name = "eml_scalar_eg";
  c2_info[10].dominantType = "uint32";
  c2_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[10].fileTimeLo = 1286815196U;
  c2_info[10].fileTimeHi = 0U;
  c2_info[10].mFileTimeLo = 0U;
  c2_info[10].mFileTimeHi = 0U;
  c2_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c2_info[11].name = "eml_scalexp_alloc";
  c2_info[11].dominantType = "uint32";
  c2_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c2_info[11].fileTimeLo = 1286815196U;
  c2_info[11].fileTimeHi = 0U;
  c2_info[11].mFileTimeLo = 0U;
  c2_info[11].mFileTimeHi = 0U;
  c2_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c2_info[12].name = "eml_error";
  c2_info[12].dominantType = "char";
  c2_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c2_info[12].fileTimeLo = 1286815100U;
  c2_info[12].fileTimeHi = 0U;
  c2_info[12].mFileTimeLo = 0U;
  c2_info[12].mFileTimeHi = 0U;
  c2_info[13].context = "";
  c2_info[13].name = "bitor";
  c2_info[13].dominantType = "uint32";
  c2_info[13].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitor.m";
  c2_info[13].fileTimeLo = 1286815236U;
  c2_info[13].fileTimeHi = 0U;
  c2_info[13].mFileTimeLo = 0U;
  c2_info[13].mFileTimeHi = 0U;
  c2_info[14].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitor.m";
  c2_info[14].name = "eml_scalexp_compatible";
  c2_info[14].dominantType = "uint32";
  c2_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c2_info[14].fileTimeLo = 1286815196U;
  c2_info[14].fileTimeHi = 0U;
  c2_info[14].mFileTimeLo = 0U;
  c2_info[14].mFileTimeHi = 0U;
  c2_info[15].context = "";
  c2_info[15].name = "length";
  c2_info[15].dominantType = "uint32";
  c2_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c2_info[15].fileTimeLo = 1286815160U;
  c2_info[15].fileTimeHi = 0U;
  c2_info[15].mFileTimeLo = 0U;
  c2_info[15].mFileTimeHi = 0U;
}

static void c2_eml_error(SFc2_MPEGConversionInstanceStruct *chartInstance)
{
  int32_T c2_i5;
  static char_T c2_varargin_1[42] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'b', 'i', 't', 's', 'h', 'i', 'f', 't', '_', 'i',
    'n', 'p', 'u', 't', 's', 'M', 'u', 's', 't', 'B', 'e', 'I', 'n', 't', 'e',
    'g', 'e', 'r', 's' };

  char_T c2_u[42];
  const mxArray *c2_y = NULL;
  for (c2_i5 = 0; c2_i5 < 42; c2_i5++) {
    c2_u[c2_i5] = c2_varargin_1[c2_i5];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 42));
  sf_mex_call("error", 0U, 1U, 14, sf_mex_call("message", 1U, 1U, 14, c2_y));
}

static void c2_emlrt_marshallIn(SFc2_MPEGConversionInstanceStruct *chartInstance,
  const mxArray *c2_out, const char_T *c2_identifier, uint32_T c2_y[20])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_out), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_out);
}

static void c2_b_emlrt_marshallIn(SFc2_MPEGConversionInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  uint32_T c2_y[20])
{
  uint32_T c2_uv1[20];
  int32_T c2_i6;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_uv1, 1, 7, 0U, 1, 0U, 1, 20);
  for (c2_i6 = 0; c2_i6 < 20; c2_i6++) {
    c2_y[c2_i6] = c2_uv1[c2_i6];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_c_emlrt_marshallIn(SFc2_MPEGConversionInstanceStruct
  *chartInstance, const mxArray *c2_b_prev_out, const char_T *c2_identifier,
  uint32_T c2_y[20])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_prev_out), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_b_prev_out);
}

static void c2_d_emlrt_marshallIn(SFc2_MPEGConversionInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  uint32_T c2_y[20])
{
  uint32_T c2_uv2[20];
  int32_T c2_i7;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_prev_out_not_empty = FALSE;
  } else {
    chartInstance->c2_prev_out_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_uv2, 1, 7, 0U, 1, 0U, 1, 20);
    for (c2_i7 = 0; c2_i7 < 20; c2_i7++) {
      c2_y[c2_i7] = c2_uv2[c2_i7];
    }
  }

  sf_mex_destroy(&c2_u);
}

static uint8_T c2_e_emlrt_marshallIn(SFc2_MPEGConversionInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_MPEGConversion, const char_T *
  c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_MPEGConversion), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_MPEGConversion);
  return c2_y;
}

static uint8_T c2_f_emlrt_marshallIn(SFc2_MPEGConversionInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_putbits(SFc2_MPEGConversionInstanceStruct *chartInstance, int32_T
  c2_bitpos, uint32_T c2_out[20], uint32_T c2_Temp, real_T c2_outpos, uint32_T
  c2_val, real_T c2_bits, real_T *c2_flag, int32_T *c2_bitposO, uint32_T
  *c2_TempO, real_T *c2_outposO)
{
  uint32_T c2_valIn;
  real_T c2_d0;
  int32_T c2_bitsIn;
  int64_T c2_i8;
  boolean_T c2_guard1 = FALSE;
  int32_T c2_bitsleft;
  int32_T c2_saturatedUnaryMinus;
  uint8_T c2_absk1;
  uint32_T c2_a;
  c2_valIn = c2_val;
  c2_d0 = c2_bits;
  c2_d0 = c2_d0 < 0.0 ? muDoubleScalarCeil(c2_d0 - 0.5) : muDoubleScalarFloor
    (c2_d0 + 0.5);
  if (c2_d0 < 2.147483648E+9) {
    if (c2_d0 >= -2.147483648E+9) {
      c2_bitsIn = (int32_T)c2_d0;
    } else {
      c2_bitsIn = MIN_int32_T;
    }
  } else if (c2_d0 >= 2.147483648E+9) {
    c2_bitsIn = MAX_int32_T;
  } else {
    c2_bitsIn = 0;
  }

  *c2_bitposO = c2_bitpos;
  *c2_TempO = c2_Temp;
  *c2_outposO = c2_outpos;
  c2_i8 = (int64_T)c2_bitpos + (int64_T)c2_bitsIn;
  if (c2_i8 > 2147483647L) {
    c2_i8 = 2147483647L;
  } else {
    if (c2_i8 <= -2147483648L) {
      c2_i8 = -2147483648L;
    }
  }

  c2_guard1 = FALSE;
  if ((int32_T)c2_i8 > 32) {
    c2_i8 = (int64_T)32 - (int64_T)c2_bitpos;
    if (c2_i8 > 2147483647L) {
      c2_i8 = 2147483647L;
    } else {
      if (c2_i8 <= -2147483648L) {
        c2_i8 = -2147483648L;
      }
    }

    c2_bitsleft = (int32_T)c2_i8;
    c2_i8 = (int64_T)c2_bitsIn - (int64_T)c2_bitsleft;
    if (c2_i8 > 2147483647L) {
      c2_i8 = 2147483647L;
    } else {
      if (c2_i8 <= -2147483648L) {
        c2_i8 = -2147483648L;
      }
    }

    c2_saturatedUnaryMinus = (int32_T)c2_i8;
    if (c2_saturatedUnaryMinus <= MIN_int32_T) {
      c2_saturatedUnaryMinus = MAX_int32_T;
    } else {
      c2_saturatedUnaryMinus = -c2_saturatedUnaryMinus;
    }

    c2_valIn = 0U;
    if (c2_saturatedUnaryMinus < 0) {
      c2_saturatedUnaryMinus = -c2_saturatedUnaryMinus;
      if (c2_saturatedUnaryMinus > 255) {
        c2_saturatedUnaryMinus = 255;
      }

      c2_absk1 = (uint8_T)c2_saturatedUnaryMinus;
      if (c2_absk1 < 32) {
        c2_valIn = c2_val >> (uint32_T)c2_absk1;
      }
    } else {
      if (c2_saturatedUnaryMinus <= 0) {
        c2_saturatedUnaryMinus = 0;
      } else {
        if (c2_saturatedUnaryMinus > 255) {
          c2_saturatedUnaryMinus = 255;
        }
      }

      c2_absk1 = (uint8_T)c2_saturatedUnaryMinus;
      if (c2_absk1 < 32) {
        c2_valIn = c2_val << (uint32_T)c2_absk1;
      }
    }

    *c2_TempO = c2_Temp | c2_valIn;
    c2_out[sf_mex_lw_bounds_check((int32_T)c2_outpos, 1, 20) - 1] = *c2_TempO;
    *c2_outposO = c2_outpos + 1.0;
    if (*c2_outposO > 20.0) {
      *c2_flag = 0.0;
    } else {
      *c2_TempO = 0U;
      *c2_bitposO = 0;
      c2_i8 = (int64_T)c2_bitsIn - (int64_T)c2_bitsleft;
      if (c2_i8 > 2147483647L) {
        c2_i8 = 2147483647L;
      } else {
        if (c2_i8 <= -2147483648L) {
          c2_i8 = -2147483648L;
        }
      }

      c2_bitsIn = (int32_T)c2_i8;
      c2_i8 = (int64_T)32 - (int64_T)c2_bitsIn;
      if (c2_i8 > 2147483647L) {
        c2_i8 = 2147483647L;
      } else {
        if (c2_i8 <= -2147483648L) {
          c2_i8 = -2147483648L;
        }
      }

      c2_saturatedUnaryMinus = (int32_T)c2_i8;
      c2_valIn = 0U;
      if (c2_saturatedUnaryMinus < 0) {
        c2_saturatedUnaryMinus = -c2_saturatedUnaryMinus;
        if (c2_saturatedUnaryMinus <= 0) {
          c2_saturatedUnaryMinus = 0;
        } else {
          if (c2_saturatedUnaryMinus > 255) {
            c2_saturatedUnaryMinus = 255;
          }
        }

        c2_absk1 = (uint8_T)c2_saturatedUnaryMinus;
        if (c2_absk1 < 32) {
          c2_valIn = c2_val >> (uint32_T)c2_absk1;
        }
      } else {
        if (c2_saturatedUnaryMinus <= 0) {
          c2_saturatedUnaryMinus = 0;
        } else {
          if (c2_saturatedUnaryMinus > 255) {
            c2_saturatedUnaryMinus = 255;
          }
        }

        c2_absk1 = (uint8_T)c2_saturatedUnaryMinus;
        if (c2_absk1 < 32) {
          c2_valIn = c2_val << (uint32_T)c2_absk1;
        }
      }

      c2_a = c2_valIn;
      c2_i8 = (int64_T)32 - (int64_T)c2_bitsIn;
      if (c2_i8 > 2147483647L) {
        c2_i8 = 2147483647L;
      } else {
        if (c2_i8 <= -2147483648L) {
          c2_i8 = -2147483648L;
        }
      }

      c2_saturatedUnaryMinus = -(int32_T)c2_i8;
      c2_valIn = 0U;
      if (c2_saturatedUnaryMinus < 0) {
        c2_saturatedUnaryMinus = -c2_saturatedUnaryMinus;
        if (c2_saturatedUnaryMinus <= 0) {
          c2_saturatedUnaryMinus = 0;
        } else {
          if (c2_saturatedUnaryMinus > 255) {
            c2_saturatedUnaryMinus = 255;
          }
        }

        c2_absk1 = (uint8_T)c2_saturatedUnaryMinus;
        if (c2_absk1 < 32) {
          c2_valIn = c2_a >> (uint32_T)c2_absk1;
        }
      } else {
        if (c2_saturatedUnaryMinus <= 0) {
          c2_saturatedUnaryMinus = 0;
        } else {
          if (c2_saturatedUnaryMinus > 255) {
            c2_saturatedUnaryMinus = 255;
          }
        }

        c2_absk1 = (uint8_T)c2_saturatedUnaryMinus;
        if (c2_absk1 < 32) {
          c2_valIn = c2_a << (uint32_T)c2_absk1;
        }
      }

      c2_guard1 = TRUE;
    }
  } else {
    c2_guard1 = TRUE;
  }

  if (c2_guard1 == TRUE) {
    c2_a = c2_valIn;
    c2_i8 = (int64_T)c2_bitsIn + (int64_T)*c2_bitposO;
    if (c2_i8 > 2147483647L) {
      c2_i8 = 2147483647L;
    } else {
      if (c2_i8 <= -2147483648L) {
        c2_i8 = -2147483648L;
      }
    }

    c2_i8 = (int64_T)32 - (int64_T)(int32_T)c2_i8;
    if (c2_i8 > 2147483647L) {
      c2_i8 = 2147483647L;
    } else {
      if (c2_i8 <= -2147483648L) {
        c2_i8 = -2147483648L;
      }
    }

    c2_saturatedUnaryMinus = (int32_T)c2_i8;
    c2_valIn = 0U;
    if (c2_saturatedUnaryMinus < 0) {
      c2_saturatedUnaryMinus = -c2_saturatedUnaryMinus;
      if (c2_saturatedUnaryMinus <= 0) {
        c2_saturatedUnaryMinus = 0;
      } else {
        if (c2_saturatedUnaryMinus > 255) {
          c2_saturatedUnaryMinus = 255;
        }
      }

      c2_absk1 = (uint8_T)c2_saturatedUnaryMinus;
      if (c2_absk1 < 32) {
        c2_valIn = c2_a >> (uint32_T)c2_absk1;
      }
    } else {
      if (c2_saturatedUnaryMinus <= 0) {
        c2_saturatedUnaryMinus = 0;
      } else {
        if (c2_saturatedUnaryMinus > 255) {
          c2_saturatedUnaryMinus = 255;
        }
      }

      c2_absk1 = (uint8_T)c2_saturatedUnaryMinus;
      if (c2_absk1 < 32) {
        c2_valIn = c2_a << (uint32_T)c2_absk1;
      }
    }

    *c2_TempO |= c2_valIn;
    c2_i8 = (int64_T)*c2_bitposO + (int64_T)c2_bitsIn;
    if (c2_i8 > 2147483647L) {
      c2_i8 = 2147483647L;
    } else {
      if (c2_i8 <= -2147483648L) {
        c2_i8 = -2147483648L;
      }
    }

    *c2_bitposO = (int32_T)c2_i8;
    *c2_flag = 1.0;
  }
}

static void init_dsm_address_info(SFc2_MPEGConversionInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c2_MPEGConversion_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(44103396U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4151141811U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3115125656U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3648465714U);
}

mxArray *sf_c2_MPEGConversion_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(4022564126U);
    pr[1] = (double)(1375026931U);
    pr[2] = (double)(2001545527U);
    pr[3] = (double)(569330922U);
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
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

static const mxArray *sf_get_sim_state_info_c2_MPEGConversion(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"out\",},{M[4],M[0],T\"prev_out\",S'l','i','p'{{M1x2[264 272],M[0],}}},{M[8],M[0],T\"is_active_c2_MPEGConversion\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_MPEGConversion_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void sf_opaque_initialize_c2_MPEGConversion(void *chartInstanceVar)
{
  initialize_params_c2_MPEGConversion((SFc2_MPEGConversionInstanceStruct*)
    chartInstanceVar);
  initialize_c2_MPEGConversion((SFc2_MPEGConversionInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_MPEGConversion(void *chartInstanceVar)
{
  enable_c2_MPEGConversion((SFc2_MPEGConversionInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_MPEGConversion(void *chartInstanceVar)
{
  disable_c2_MPEGConversion((SFc2_MPEGConversionInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c2_MPEGConversion(void *chartInstanceVar)
{
  sf_c2_MPEGConversion((SFc2_MPEGConversionInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_MPEGConversion(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_MPEGConversion
    ((SFc2_MPEGConversionInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_MPEGConversion();/* state var info */
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

extern void sf_internal_set_sim_state_c2_MPEGConversion(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_MPEGConversion();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_MPEGConversion((SFc2_MPEGConversionInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_MPEGConversion(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_MPEGConversion(S);
}

static void sf_opaque_set_sim_state_c2_MPEGConversion(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c2_MPEGConversion(S, st);
}

static void sf_opaque_terminate_c2_MPEGConversion(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_MPEGConversionInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c2_MPEGConversion((SFc2_MPEGConversionInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_MPEGConversion((SFc2_MPEGConversionInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_MPEGConversion(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_MPEGConversion((SFc2_MPEGConversionInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_MPEGConversion(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"MPEGConversion","MPEGConversion",2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"MPEGConversion","MPEGConversion",2,
                "RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"MPEGConversion",
      "MPEGConversion",2,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"MPEGConversion","MPEGConversion",2,
        1);
      sf_mark_chart_reusable_outputs(S,"MPEGConversion","MPEGConversion",2,1);
    }

    sf_set_rtw_dwork_info(S,"MPEGConversion","MPEGConversion",2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(568776090U));
  ssSetChecksum1(S,(1942899661U));
  ssSetChecksum2(S,(3864694604U));
  ssSetChecksum3(S,(2937017777U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c2_MPEGConversion(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "MPEGConversion", "MPEGConversion",2);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_MPEGConversion(SimStruct *S)
{
  SFc2_MPEGConversionInstanceStruct *chartInstance;
  chartInstance = (SFc2_MPEGConversionInstanceStruct *)malloc(sizeof
    (SFc2_MPEGConversionInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_MPEGConversionInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_MPEGConversion;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_MPEGConversion;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_MPEGConversion;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_MPEGConversion;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_MPEGConversion;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_MPEGConversion;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_MPEGConversion;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_MPEGConversion;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_MPEGConversion;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_MPEGConversion;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_MPEGConversion;
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

void c2_MPEGConversion_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_MPEGConversion(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_MPEGConversion(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_MPEGConversion(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_MPEGConversion_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
