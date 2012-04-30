/* Include files */

#include "blascompat32.h"
#include "commsdrhw_sfun.h"
#include "c1_commsdrhw.h"
#include <math.h>
#include <string.h>
#include "mwmathutil.h"

/* Type Definitions */

/* Named Constants */
#define c1_b_USRP2_CONTROL_PORT        (32768.0)
#define c1_b_HOST_CONTROL_PORT         (30001.0)

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void initialize_c1_commsdrhw(SFc1_commsdrhwInstanceStruct *chartInstance);
static void initialize_params_c1_commsdrhw(SFc1_commsdrhwInstanceStruct
  *chartInstance);
static void enable_c1_commsdrhw(SFc1_commsdrhwInstanceStruct *chartInstance);
static void disable_c1_commsdrhw(SFc1_commsdrhwInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_commsdrhw(SFc1_commsdrhwInstanceStruct
  *chartInstance);
static void set_sim_state_c1_commsdrhw(SFc1_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c1_st);
static void finalize_c1_commsdrhw(SFc1_commsdrhwInstanceStruct *chartInstance);
static void sf_c1_commsdrhw(SFc1_commsdrhwInstanceStruct *chartInstance);
static void c1_chartstep_c1_commsdrhw(SFc1_commsdrhwInstanceStruct
  *chartInstance);
static void initSimStructsc1_commsdrhw(SFc1_commsdrhwInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[61]);
static void c1_USRP2CmdDef(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_USRP2Opcodes c1_cmd, c1_s7P91ApZ2CkwDPZE5FamWSB c1_cmdDef[18]);
static void c1_l_fdef(SFc1_commsdrhwInstanceStruct *chartInstance, real_T
                      c1_offset, real_T c1_fsize, c1_USRP2FieldDtypes c1_dtype,
                      real_T *c1_s_offset, real_T *c1_s_fsize,
                      c1_USRP2FieldDtypes *c1_s_dtype, uint8_T c1_s_bytes[16]);
static void c1_b_l_fdef(SFc1_commsdrhwInstanceStruct *chartInstance, real_T
  c1_offset, real_T c1_fsize, c1_USRP2FieldDtypes c1_dtype, real_T c1_val,
  real_T *c1_s_offset, real_T *c1_s_fsize, c1_USRP2FieldDtypes *c1_s_dtype,
  uint8_T c1_s_bytes[16]);
static void c1_USRP2PackFieldVal(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_USRP2FieldDtypes c1_dtype, real_T c1_val, uint8_T c1_bytes[16]);
static real_T c1_mod(SFc1_commsdrhwInstanceStruct *chartInstance, real_T c1_x,
                     real_T c1_y);
static void c1_USRP2Cmd2Pkt(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_cmdDef[18], uint8_T c1_pkt[255], real_T
  *c1_pktLen);
static real_T c1_l_CalcScale(SFc1_commsdrhwInstanceStruct *chartInstance, real_T
  c1_interpolation);
static void c1_eml_error(SFc1_commsdrhwInstanceStruct *chartInstance);
static void c1_USRP2RuntimeControl(SFc1_commsdrhwInstanceStruct *chartInstance,
  real_T c1_varargin_3, real_T *c1_pktLength, uint8_T c1_pkt[255], uint8_T
  *c1_b_replyId, real_T *c1_varargout_1_ValidMask, real_T *c1_varargout_1_Fc,
  real_T *c1_varargout_1_Gain, real_T *c1_varargout_1_DecimInterp, real_T
  *c1_varargout_1_ScaleI, real_T *c1_varargout_1_ScaleQ);
static void c1_b_USRP2RuntimeControl(SFc1_commsdrhwInstanceStruct *chartInstance,
  real_T c1_varargin_3, real_T *c1_pktLength, uint8_T c1_pkt[255], uint8_T
  *c1_b_replyId, real_T *c1_varargout_1_ValidMask, real_T *c1_varargout_1_Fc,
  real_T *c1_varargout_1_Gain, real_T *c1_varargout_1_DecimInterp, real_T
  *c1_varargout_1_ScaleI, real_T *c1_varargout_1_ScaleQ);
static void c1_c_USRP2RuntimeControl(SFc1_commsdrhwInstanceStruct *chartInstance,
  real_T c1_varargin_3, real_T *c1_pktLength, uint8_T c1_pkt[255], uint8_T
  *c1_b_replyId, real_T *c1_varargout_1_ValidMask, real_T *c1_varargout_1_Fc,
  real_T *c1_varargout_1_Gain, real_T *c1_varargout_1_DecimInterp, real_T
  *c1_varargout_1_ScaleI, real_T *c1_varargout_1_ScaleQ);
static void c1_b_USRP2CmdDef(SFc1_commsdrhwInstanceStruct *chartInstance,
  uint8_T c1_cmd, c1_s7P91ApZ2CkwDPZE5FamWSB c1_cmdDef[18]);
static void c1_USRP2RuntimeControlReplies(SFc1_commsdrhwInstanceStruct
  *chartInstance, uint8_T c1_pkt[255], uint16_T c1_pktLen, char_T
  c1_errStr_data[56], int32_T c1_errStr_sizes[2], real_T *c1_b_replyId);
static real_T c1_USRP2UnpackFieldVal(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_USRP2FieldDtypes c1_dtype, uint8_T c1_bytes[16]);
static void c1_d_USRP2RuntimeControl(SFc1_commsdrhwInstanceStruct *chartInstance,
  real_T c1_varargin_3, real_T *c1_pktLength, uint8_T c1_pkt[255], uint8_T
  *c1_b_replyId, real_T *c1_varargout_1_ValidMask, real_T *c1_varargout_1_Fc,
  real_T *c1_varargout_1_Gain, real_T *c1_varargout_1_DecimInterp, real_T
  *c1_varargout_1_ScaleI, real_T *c1_varargout_1_ScaleQ);
static void c1_e_USRP2RuntimeControl(SFc1_commsdrhwInstanceStruct *chartInstance,
  real_T c1_varargin_3, real_T *c1_pktLength, uint8_T c1_pkt[255], uint8_T
  *c1_b_replyId, real_T *c1_varargout_1_ValidMask, real_T *c1_varargout_1_Fc,
  real_T *c1_varargout_1_Gain, real_T *c1_varargout_1_DecimInterp, real_T
  *c1_varargout_1_ScaleI, real_T *c1_varargout_1_ScaleQ);
static void c1_f_USRP2RuntimeControl(SFc1_commsdrhwInstanceStruct *chartInstance,
  real_T c1_varargin_3, real_T *c1_pktLength, uint8_T c1_pkt[255], uint8_T
  *c1_b_replyId, real_T *c1_varargout_1_ValidMask, real_T *c1_varargout_1_Fc,
  real_T *c1_varargout_1_Gain, real_T *c1_varargout_1_DecimInterp, real_T
  *c1_varargout_1_ScaleI, real_T *c1_varargout_1_ScaleQ);
static uint16_T c1_VRTGetDataStream(SFc1_commsdrhwInstanceStruct *chartInstance);
static uint8_T c1_b_VRTGetDataStream(SFc1_commsdrhwInstanceStruct *chartInstance);
static void c1_Update(SFc1_commsdrhwInstanceStruct *chartInstance, uint8_T
                      c1_U0[255], real_T c1_U1);
static void c1_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_packet, const char_T *c1_identifier, uint8_T c1_y_data[8000],
  int32_T c1_y_sizes[2]);
static void c1_b_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint8_T c1_y_data
  [8000], int32_T c1_y_sizes[2]);
static void c1_c_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_d_NetworkLib, const char_T *c1_identifier, real_T c1_y[137]);
static void c1_d_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[137]);
static void c1_e_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_d_NetworkLib, const char_T *c1_identifier, real_T c1_y[137]);
static void c1_f_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[137]);
static void c1_g_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_d_NetworkLib, const char_T *c1_identifier, real_T c1_y[137]);
static void c1_h_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[137]);
static void c1_i_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_b_Tx, const char_T *c1_identifier, char_T c1_y_datatype[5],
  uint8_T *c1_y_hasTrailer, uint32_T *c1_y_trailer, uint8_T
  *c1_y_stream_hasStreamID, uint32_T *c1_y_stream_streamID, uint8_T
  *c1_y_stream_hasClassID, uint32_T c1_y_stream_classID[2], uint8_T
  *c1_y_stream_packetType, uint8_T *c1_y_stream_TSI, uint8_T *c1_y_stream_TSF,
  uint8_T *c1_y_stream_packetCount, uint16_T *c1_y_stream_packetSize);
static void c1_j_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, char_T
  c1_y_datatype[5], uint8_T *c1_y_hasTrailer, uint32_T *c1_y_trailer, uint8_T
  *c1_y_stream_hasStreamID, uint32_T *c1_y_stream_streamID, uint8_T
  *c1_y_stream_hasClassID, uint32_T c1_y_stream_classID[2], uint8_T
  *c1_y_stream_packetType, uint8_T *c1_y_stream_TSI, uint8_T *c1_y_stream_TSF,
  uint8_T *c1_y_stream_packetCount, uint16_T *c1_y_stream_packetSize);
static void c1_k_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y[5]);
static uint8_T c1_l_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static uint32_T c1_m_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_n_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint8_T
  *c1_y_hasStreamID, uint32_T *c1_y_streamID, uint8_T *c1_y_hasClassID, uint32_T
  c1_y_classID[2], uint8_T *c1_y_packetType, uint8_T *c1_y_TSI, uint8_T
  *c1_y_TSF, uint8_T *c1_y_packetCount, uint16_T *c1_y_packetSize);
static void c1_o_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint32_T c1_y[2]);
static uint16_T c1_p_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_q_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_c_Y0, const char_T *c1_identifier, uint8_T c1_y[255]);
static void c1_r_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint8_T c1_y[255]);
static void c1_s_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_c_Y0, const char_T *c1_identifier, uint8_T c1_y[255]);
static void c1_t_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint8_T c1_y[255]);
static uint16_T c1_u_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c1_c_Y1, const char_T *c1_identifier);
static uint16_T c1_v_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static uint16_T c1_w_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c1_c_Y1, const char_T *c1_identifier);
static uint16_T c1_x_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_y_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_ctrlReceiver, const char_T *c1_identifier);
static void c1_ab_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_bb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_ctrlReceiverBlocking, const char_T *c1_identifier);
static void c1_cb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_db_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_ctrlSender, const char_T *c1_identifier);
static void c1_eb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static real_T c1_fb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_b_lastCF, const char_T *c1_identifier);
static real_T c1_gb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static real_T c1_hb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_b_lastDI, const char_T *c1_identifier);
static real_T c1_ib_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static real_T c1_jb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_b_lastG, const char_T *c1_identifier);
static real_T c1_kb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static real_T c1_lb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_b_lastI, const char_T *c1_identifier);
static real_T c1_mb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static real_T c1_nb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_b_lastQ, const char_T *c1_identifier);
static real_T c1_ob_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static real_T c1_pb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_b_replyId, const char_T *c1_identifier);
static real_T c1_qb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_rb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_b_replyQueue, const char_T *c1_identifier,
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_y[255]);
static void c1_sb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_y[255]);
static real_T c1_tb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static uint8_T c1_ub_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_commsdrhw, const char_T
  *c1_identifier);
static real_T c1_l_SendConfig(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_b_replyQueue[255], real_T c1_centerFreq, real_T
  c1_gain, real_T c1_interpolation, real_T c1_scaleI, real_T c1_scaleQ);
static void c1_l_addToQueue(SFc1_commsdrhwInstanceStruct *chartInstance, uint8_T
  c1_ctrlData[255], real_T c1_ctrlLength, c1_sgyjHZtUMVZuM1aKBgGok1D
  c1_b_replyQueue[255], uint8_T c1_b_replyId, real_T c1_currCfg_ValidMask,
  real_T c1_currCfg_Fc, real_T c1_currCfg_Gain, real_T c1_currCfg_DecimInterp,
  real_T c1_currCfg_ScaleI, real_T c1_currCfg_ScaleQ, real_T
  *c1_repliesOutstanding);
static boolean_T c1_l_ReceiveReply(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_b_replyQueue[255]);
static void c1_l_CheckConfig(SFc1_commsdrhwInstanceStruct *chartInstance, char_T
  c1_errStr_data[169], int32_T c1_errStr_sizes[2], real_T c1_cfgEntry_ValidMask,
  real_T c1_cfgEntry_Fc, real_T c1_cfgEntry_Gain, real_T c1_cfgEntry_DecimInterp,
  real_T c1_cfgEntry_ScaleI, real_T c1_cfgEntry_ScaleQ);
static real_T c1_b_l_SendConfig(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_b_replyQueue[255], real_T c1_centerFreq, real_T
  c1_gain, real_T c1_interpolation, real_T c1_scaleI, real_T c1_scaleQ);
static boolean_T c1_b_l_ReceiveReply(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_b_replyQueue[255]);
static void c1_VRTEncoder(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_s69xIfXV5nXp8sDnVHzDOMB *c1_S, creal_T c1_data[358], uint8_T
  c1_packet_data[1436], int32_T c1_packet_sizes[1]);
static void c1_VRTSetDataStream(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_s69xIfXV5nXp8sDnVHzDOMB *c1_S, real_T c1_value);
static void c1_writeHeader(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_s6AmiQ3Zcve7MnsJ9ypFbFH *c1_S, uint8_T c1_h1, uint8_T c1_packet[4]);
static void init_dsm_address_info(SFc1_commsdrhwInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_commsdrhw(SFc1_commsdrhwInstanceStruct *chartInstance)
{
  char_T *c1_sErr;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_Tx_not_empty = FALSE;
  chartInstance->c1_ctrlSender_not_empty = FALSE;
  chartInstance->c1_ctrlReceiver_not_empty = FALSE;
  chartInstance->c1_ctrlReceiverBlocking_not_empty = FALSE;
  chartInstance->c1_replyQueue_not_empty = FALSE;
  chartInstance->c1_lastCF_not_empty = FALSE;
  chartInstance->c1_lastG_not_empty = FALSE;
  chartInstance->c1_lastDI_not_empty = FALSE;
  chartInstance->c1_lastI_not_empty = FALSE;
  chartInstance->c1_lastQ_not_empty = FALSE;
  chartInstance->c1_replyId_not_empty = FALSE;
  chartInstance->c1_is_active_c1_commsdrhw = 0U;
  if (!ssIsExternalSim(chartInstance->S)) {
    c1_sErr = GetErrorBuffer(&chartInstance->c1_NetworkLib[0U]);
    CreateUDPInterface(&chartInstance->c1_NetworkLib[0U]);
    if (*c1_sErr == 0) {
      LibCreate_Network(&chartInstance->c1_NetworkLib[0U], 0, "0.0.0.0", 30001,
                        "192.168.10.2", -1, 8192, 1, 0);
    }

    if (*c1_sErr == 0) {
      LibStart(&chartInstance->c1_NetworkLib[0U]);
    }

    if (*c1_sErr != 0) {
      DestroyUDPInterface(&chartInstance->c1_NetworkLib[0U]);
      if (*c1_sErr != 0) {
        PrintError(c1_sErr);
      }
    }
  }

  if (!ssIsExternalSim(chartInstance->S)) {
    c1_sErr = GetErrorBuffer(&chartInstance->c1_b_NetworkLib[0U]);
    CreateUDPInterface(&chartInstance->c1_b_NetworkLib[0U]);
    if (*c1_sErr == 0) {
      LibCreate_Network(&chartInstance->c1_b_NetworkLib[0U], 0, "0.0.0.0", 30001,
                        "192.168.10.2", -1, 8192, 1, 100);
    }

    if (*c1_sErr == 0) {
      LibStart(&chartInstance->c1_b_NetworkLib[0U]);
    }

    if (*c1_sErr != 0) {
      DestroyUDPInterface(&chartInstance->c1_b_NetworkLib[0U]);
      if (*c1_sErr != 0) {
        PrintError(c1_sErr);
      }
    }
  }

  if (!ssIsExternalSim(chartInstance->S)) {
    c1_sErr = GetErrorBuffer(&chartInstance->c1_c_NetworkLib[0U]);
    CreateUDPInterface(&chartInstance->c1_c_NetworkLib[0U]);
    if (*c1_sErr == 0) {
      LibCreate_Network(&chartInstance->c1_c_NetworkLib[0U], 1, "0.0.0.0", 30001,
                        "192.168.10.2", 32768, 8192, 1, 0);
    }

    if (*c1_sErr == 0) {
      LibStart(&chartInstance->c1_c_NetworkLib[0U]);
    }

    if (*c1_sErr != 0) {
      DestroyUDPInterface(&chartInstance->c1_c_NetworkLib[0U]);
      if (*c1_sErr != 0) {
        PrintError(c1_sErr);
      }
    }
  }

  chartInstance->c1_replyId = 1.0;
  chartInstance->c1_lastCF = 0.0;
  chartInstance->c1_lastG = 0.0;
  chartInstance->c1_lastDI = 0.0;
  chartInstance->c1_lastI = 0.0;
  chartInstance->c1_lastQ = 0.0;
}

static void initialize_params_c1_commsdrhw(SFc1_commsdrhwInstanceStruct
  *chartInstance)
{
  real_T c1_d0;
  real_T c1_d1;
  real_T c1_dv0[12];
  int32_T c1_i0;
  sf_set_error_prefix_string(
    "Error evaluating data 'HOST_CONTROL_PORT' in the parent workspace.\n");
  sf_mex_import_named("HOST_CONTROL_PORT", sf_mex_get_sfun_param
                      (chartInstance->S, 0, 0), &c1_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_HOST_CONTROL_PORT = c1_d0;
  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  sf_set_error_prefix_string(
    "Error evaluating data 'USRP2_CONTROL_PORT' in the parent workspace.\n");
  sf_mex_import_named("USRP2_CONTROL_PORT", sf_mex_get_sfun_param
                      (chartInstance->S, 1, 0), &c1_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_USRP2_CONTROL_PORT = c1_d1;
  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  sf_set_error_prefix_string(
    "Error evaluating data 'USRP2_IP_NUM' in the parent workspace.\n");
  sf_mex_import_named("USRP2_IP_NUM", sf_mex_get_sfun_param(chartInstance->S, 2,
    0), c1_dv0, 0, 0, 0U, 1, 0U, 2, 1, 12);
  for (c1_i0 = 0; c1_i0 < 12; c1_i0++) {
    chartInstance->c1_USRP2_IP_NUM[c1_i0] = c1_dv0[c1_i0];
  }

  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
}

static void enable_c1_commsdrhw(SFc1_commsdrhwInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_commsdrhw(SFc1_commsdrhwInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static const mxArray *get_sim_state_c1_commsdrhw(SFc1_commsdrhwInstanceStruct
  *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  int32_T c1_loop_ub;
  int32_T c1_i1;
  uint8_T c1_u_data[8000];
  const mxArray *c1_b_y = NULL;
  real_T c1_u[137];
  const mxArray *c1_c_y = NULL;
  real_T c1_b_u[137];
  const mxArray *c1_d_y = NULL;
  real_T c1_c_u[137];
  const mxArray *c1_e_y = NULL;
  char_T c1_u_datatype[5];
  uint8_T c1_u_hasTrailer;
  uint32_T c1_u_trailer;
  uint8_T c1_u_stream_hasStreamID;
  uint32_T c1_u_stream_streamID;
  uint8_T c1_u_stream_hasClassID;
  uint32_T c1_u_stream_classID[2];
  uint8_T c1_u_stream_packetType;
  uint8_T c1_u_stream_TSI;
  uint8_T c1_u_stream_TSF;
  uint8_T c1_u_stream_packetCount;
  uint16_T c1_u_stream_packetSize;
  const mxArray *c1_f_y = NULL;
  char_T c1_d_u[5];
  const mxArray *c1_g_y = NULL;
  uint8_T c1_e_u;
  const mxArray *c1_h_y = NULL;
  uint32_T c1_f_u;
  const mxArray *c1_i_y = NULL;
  const mxArray *c1_j_y = NULL;
  uint8_T c1_g_u;
  const mxArray *c1_k_y = NULL;
  uint32_T c1_h_u;
  const mxArray *c1_l_y = NULL;
  uint8_T c1_i_u;
  const mxArray *c1_m_y = NULL;
  uint32_T c1_j_u[2];
  const mxArray *c1_n_y = NULL;
  uint8_T c1_k_u;
  const mxArray *c1_o_y = NULL;
  uint8_T c1_l_u;
  const mxArray *c1_p_y = NULL;
  uint8_T c1_m_u;
  const mxArray *c1_q_y = NULL;
  uint8_T c1_n_u;
  const mxArray *c1_r_y = NULL;
  uint16_T c1_o_u;
  const mxArray *c1_s_y = NULL;
  uint8_T c1_p_u[255];
  const mxArray *c1_t_y = NULL;
  uint8_T c1_q_u[255];
  const mxArray *c1_u_y = NULL;
  uint16_T c1_r_u;
  const mxArray *c1_v_y = NULL;
  uint16_T c1_s_u;
  const mxArray *c1_w_y = NULL;
  const mxArray *c1_x_y = NULL;
  const mxArray *c1_y_y = NULL;
  const mxArray *c1_ab_y = NULL;
  real_T c1_t_u;
  const mxArray *c1_bb_y = NULL;
  real_T c1_u_u;
  const mxArray *c1_cb_y = NULL;
  real_T c1_v_u;
  const mxArray *c1_db_y = NULL;
  real_T c1_w_u;
  const mxArray *c1_eb_y = NULL;
  real_T c1_x_u;
  const mxArray *c1_fb_y = NULL;
  real_T c1_y_u;
  const mxArray *c1_gb_y = NULL;
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_ab_u[255];
  const mxArray *c1_hb_y = NULL;
  int32_T c1_iv0[2];
  c1_sgyjHZtUMVZuM1aKBgGok1D *c1_r0;
  real_T c1_bb_u;
  const mxArray *c1_ib_y = NULL;
  real_T c1_cb_u;
  const mxArray *c1_jb_y = NULL;
  real_T c1_db_u;
  const mxArray *c1_kb_y = NULL;
  real_T c1_eb_u;
  const mxArray *c1_lb_y = NULL;
  real_T c1_fb_u;
  const mxArray *c1_mb_y = NULL;
  real_T c1_gb_u;
  const mxArray *c1_nb_y = NULL;
  uint8_T c1_hb_u;
  const mxArray *c1_ob_y = NULL;
  int32_T (*c1_packet_sizes)[2];
  uint8_T (*c1_packet_data)[8000];
  c1_packet_sizes = (int32_T (*)[2])ssGetCurrentOutputPortDimensions_wrapper
    (chartInstance->S, 1);
  c1_packet_data = (uint8_T (*)[8000])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(20));
  c1_loop_ub = (*c1_packet_sizes)[0] * (*c1_packet_sizes)[1] - 1;
  for (c1_i1 = 0; c1_i1 <= c1_loop_ub; c1_i1++) {
    c1_u_data[c1_i1] = (*c1_packet_data)[c1_i1];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u_data, 3, 0U, 1U, 0U, 2,
    (*c1_packet_sizes)[0], 1));
  sf_mex_setcell(c1_y, 0, c1_b_y);
  for (c1_i1 = 0; c1_i1 < 137; c1_i1++) {
    c1_u[c1_i1] = chartInstance->c1_NetworkLib[c1_i1];
  }

  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 137));
  sf_mex_setcell(c1_y, 1, c1_c_y);
  for (c1_i1 = 0; c1_i1 < 137; c1_i1++) {
    c1_b_u[c1_i1] = chartInstance->c1_b_NetworkLib[c1_i1];
  }

  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 1, 137));
  sf_mex_setcell(c1_y, 2, c1_d_y);
  for (c1_i1 = 0; c1_i1 < 137; c1_i1++) {
    c1_c_u[c1_i1] = chartInstance->c1_c_NetworkLib[c1_i1];
  }

  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 1, 137));
  sf_mex_setcell(c1_y, 3, c1_e_y);
  for (c1_i1 = 0; c1_i1 < 5; c1_i1++) {
    c1_u_datatype[c1_i1] = chartInstance->c1_Tx.datatype[c1_i1];
  }

  c1_u_hasTrailer = chartInstance->c1_Tx.hasTrailer;
  c1_u_trailer = chartInstance->c1_Tx.trailer;
  c1_u_stream_hasStreamID = chartInstance->c1_Tx.stream.hasStreamID;
  c1_u_stream_streamID = chartInstance->c1_Tx.stream.streamID;
  c1_u_stream_hasClassID = chartInstance->c1_Tx.stream.hasClassID;
  for (c1_i1 = 0; c1_i1 < 2; c1_i1++) {
    c1_u_stream_classID[c1_i1] = chartInstance->c1_Tx.stream.classID[c1_i1];
  }

  c1_u_stream_packetType = chartInstance->c1_Tx.stream.packetType;
  c1_u_stream_TSI = chartInstance->c1_Tx.stream.TSI;
  c1_u_stream_TSF = chartInstance->c1_Tx.stream.TSF;
  c1_u_stream_packetCount = chartInstance->c1_Tx.stream.packetCount;
  c1_u_stream_packetSize = chartInstance->c1_Tx.stream.packetSize;
  c1_f_y = NULL;
  if (!chartInstance->c1_Tx_not_empty) {
    sf_mex_assign(&c1_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_f_y, sf_mex_createstruct("structure", 2, 1, 1));
    for (c1_i1 = 0; c1_i1 < 5; c1_i1++) {
      c1_d_u[c1_i1] = c1_u_datatype[c1_i1];
    }

    c1_g_y = NULL;
    sf_mex_assign(&c1_g_y, sf_mex_create("y", c1_d_u, 10, 0U, 1U, 0U, 2, 1, 5));
    sf_mex_addfield(c1_f_y, c1_g_y, "datatype", "datatype", 0);
    c1_e_u = c1_u_hasTrailer;
    c1_h_y = NULL;
    sf_mex_assign(&c1_h_y, sf_mex_create("y", &c1_e_u, 3, 0U, 0U, 0U, 0));
    sf_mex_addfield(c1_f_y, c1_h_y, "hasTrailer", "hasTrailer", 0);
    c1_f_u = c1_u_trailer;
    c1_i_y = NULL;
    sf_mex_assign(&c1_i_y, sf_mex_create("y", &c1_f_u, 7, 0U, 0U, 0U, 0));
    sf_mex_addfield(c1_f_y, c1_i_y, "trailer", "trailer", 0);
    c1_j_y = NULL;
    sf_mex_assign(&c1_j_y, sf_mex_createstruct("structure", 2, 1, 1));
    c1_g_u = c1_u_stream_hasStreamID;
    c1_k_y = NULL;
    sf_mex_assign(&c1_k_y, sf_mex_create("y", &c1_g_u, 3, 0U, 0U, 0U, 0));
    sf_mex_addfield(c1_j_y, c1_k_y, "hasStreamID", "hasStreamID", 0);
    c1_h_u = c1_u_stream_streamID;
    c1_l_y = NULL;
    sf_mex_assign(&c1_l_y, sf_mex_create("y", &c1_h_u, 7, 0U, 0U, 0U, 0));
    sf_mex_addfield(c1_j_y, c1_l_y, "streamID", "streamID", 0);
    c1_i_u = c1_u_stream_hasClassID;
    c1_m_y = NULL;
    sf_mex_assign(&c1_m_y, sf_mex_create("y", &c1_i_u, 3, 0U, 0U, 0U, 0));
    sf_mex_addfield(c1_j_y, c1_m_y, "hasClassID", "hasClassID", 0);
    for (c1_i1 = 0; c1_i1 < 2; c1_i1++) {
      c1_j_u[c1_i1] = c1_u_stream_classID[c1_i1];
    }

    c1_n_y = NULL;
    sf_mex_assign(&c1_n_y, sf_mex_create("y", c1_j_u, 7, 0U, 1U, 0U, 2, 1, 2));
    sf_mex_addfield(c1_j_y, c1_n_y, "classID", "classID", 0);
    c1_k_u = c1_u_stream_packetType;
    c1_o_y = NULL;
    sf_mex_assign(&c1_o_y, sf_mex_create("y", &c1_k_u, 3, 0U, 0U, 0U, 0));
    sf_mex_addfield(c1_j_y, c1_o_y, "packetType", "packetType", 0);
    c1_l_u = c1_u_stream_TSI;
    c1_p_y = NULL;
    sf_mex_assign(&c1_p_y, sf_mex_create("y", &c1_l_u, 3, 0U, 0U, 0U, 0));
    sf_mex_addfield(c1_j_y, c1_p_y, "TSI", "TSI", 0);
    c1_m_u = c1_u_stream_TSF;
    c1_q_y = NULL;
    sf_mex_assign(&c1_q_y, sf_mex_create("y", &c1_m_u, 3, 0U, 0U, 0U, 0));
    sf_mex_addfield(c1_j_y, c1_q_y, "TSF", "TSF", 0);
    c1_n_u = c1_u_stream_packetCount;
    c1_r_y = NULL;
    sf_mex_assign(&c1_r_y, sf_mex_create("y", &c1_n_u, 3, 0U, 0U, 0U, 0));
    sf_mex_addfield(c1_j_y, c1_r_y, "packetCount", "packetCount", 0);
    c1_o_u = c1_u_stream_packetSize;
    c1_s_y = NULL;
    sf_mex_assign(&c1_s_y, sf_mex_create("y", &c1_o_u, 5, 0U, 0U, 0U, 0));
    sf_mex_addfield(c1_j_y, c1_s_y, "packetSize", "packetSize", 0);
    sf_mex_addfield(c1_f_y, c1_j_y, "stream", "stream", 0);
  }

  sf_mex_setcell(c1_y, 4, c1_f_y);
  for (c1_i1 = 0; c1_i1 < 255; c1_i1++) {
    c1_p_u[c1_i1] = chartInstance->c1_Y0[c1_i1];
  }

  c1_t_y = NULL;
  sf_mex_assign(&c1_t_y, sf_mex_create("y", c1_p_u, 3, 0U, 1U, 0U, 2, 255, 1));
  sf_mex_setcell(c1_y, 5, c1_t_y);
  for (c1_i1 = 0; c1_i1 < 255; c1_i1++) {
    c1_q_u[c1_i1] = chartInstance->c1_b_Y0[c1_i1];
  }

  c1_u_y = NULL;
  sf_mex_assign(&c1_u_y, sf_mex_create("y", c1_q_u, 3, 0U, 1U, 0U, 2, 255, 1));
  sf_mex_setcell(c1_y, 6, c1_u_y);
  c1_r_u = chartInstance->c1_Y1;
  c1_v_y = NULL;
  sf_mex_assign(&c1_v_y, sf_mex_create("y", &c1_r_u, 5, 0U, 0U, 0U, 0));
  sf_mex_setcell(c1_y, 7, c1_v_y);
  c1_s_u = chartInstance->c1_b_Y1;
  c1_w_y = NULL;
  sf_mex_assign(&c1_w_y, sf_mex_create("y", &c1_s_u, 5, 0U, 0U, 0U, 0));
  sf_mex_setcell(c1_y, 8, c1_w_y);
  c1_x_y = NULL;
  if (!chartInstance->c1_ctrlReceiver_not_empty) {
    sf_mex_assign(&c1_x_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_x_y, sf_mex_call("dsp.UDPReceiver", 1U, 4U, 15,
      "LocalIPPort", 6, 30001.0, 15, "RemoteIPAddress", 15, "192.168.10.2"));
  }

  sf_mex_setcell(c1_y, 9, c1_x_y);
  c1_y_y = NULL;
  if (!chartInstance->c1_ctrlReceiverBlocking_not_empty) {
    sf_mex_assign(&c1_y_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_y_y, sf_mex_call("dsp.UDPReceiver", 1U, 4U, 15,
      "LocalIPPort", 6, 30001.0, 15, "RemoteIPAddress", 15, "192.168.10.2"));
  }

  sf_mex_setcell(c1_y, 10, c1_y_y);
  c1_ab_y = NULL;
  if (!chartInstance->c1_ctrlSender_not_empty) {
    sf_mex_assign(&c1_ab_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_ab_y, sf_mex_call("dsp.UDPSender", 1U, 8U, 15,
      "RemoteIPAddress", 15, "192.168.10.2", 15, "RemoteIPPort", 6, 32768.0, 15,
      "LocalIPPortSource", 15, "Property", 15, "LocalIPPort", 6, 30001.0));
  }

  sf_mex_setcell(c1_y, 11, c1_ab_y);
  c1_t_u = chartInstance->c1_lastCF;
  c1_bb_y = NULL;
  if (!chartInstance->c1_lastCF_not_empty) {
    sf_mex_assign(&c1_bb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_bb_y, sf_mex_create("y", &c1_t_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c1_y, 12, c1_bb_y);
  c1_u_u = chartInstance->c1_lastDI;
  c1_cb_y = NULL;
  if (!chartInstance->c1_lastDI_not_empty) {
    sf_mex_assign(&c1_cb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_cb_y, sf_mex_create("y", &c1_u_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c1_y, 13, c1_cb_y);
  c1_v_u = chartInstance->c1_lastG;
  c1_db_y = NULL;
  if (!chartInstance->c1_lastG_not_empty) {
    sf_mex_assign(&c1_db_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_db_y, sf_mex_create("y", &c1_v_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c1_y, 14, c1_db_y);
  c1_w_u = chartInstance->c1_lastI;
  c1_eb_y = NULL;
  if (!chartInstance->c1_lastI_not_empty) {
    sf_mex_assign(&c1_eb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_eb_y, sf_mex_create("y", &c1_w_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c1_y, 15, c1_eb_y);
  c1_x_u = chartInstance->c1_lastQ;
  c1_fb_y = NULL;
  if (!chartInstance->c1_lastQ_not_empty) {
    sf_mex_assign(&c1_fb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_fb_y, sf_mex_create("y", &c1_x_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c1_y, 16, c1_fb_y);
  c1_y_u = chartInstance->c1_replyId;
  c1_gb_y = NULL;
  if (!chartInstance->c1_replyId_not_empty) {
    sf_mex_assign(&c1_gb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_gb_y, sf_mex_create("y", &c1_y_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c1_y, 17, c1_gb_y);
  for (c1_i1 = 0; c1_i1 < 255; c1_i1++) {
    c1_ab_u[c1_i1] = chartInstance->c1_replyQueue[c1_i1];
  }

  c1_hb_y = NULL;
  if (!chartInstance->c1_replyQueue_not_empty) {
    sf_mex_assign(&c1_hb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    for (c1_i1 = 0; c1_i1 < 2; c1_i1++) {
      c1_iv0[c1_i1] = 1 + 254 * c1_i1;
    }

    sf_mex_assign(&c1_hb_y, sf_mex_createstructarray("structure", 2, c1_iv0));
    for (c1_i1 = 0; c1_i1 < 255; c1_i1++) {
      c1_r0 = &c1_ab_u[c1_i1];
      c1_bb_u = c1_r0->ValidMask;
      c1_ib_y = NULL;
      sf_mex_assign(&c1_ib_y, sf_mex_create("y", &c1_bb_u, 0, 0U, 0U, 0U, 0));
      sf_mex_addfield(c1_hb_y, c1_ib_y, "ValidMask", "ValidMask", c1_i1);
      c1_cb_u = c1_r0->Fc;
      c1_jb_y = NULL;
      sf_mex_assign(&c1_jb_y, sf_mex_create("y", &c1_cb_u, 0, 0U, 0U, 0U, 0));
      sf_mex_addfield(c1_hb_y, c1_jb_y, "Fc", "Fc", c1_i1);
      c1_db_u = c1_r0->Gain;
      c1_kb_y = NULL;
      sf_mex_assign(&c1_kb_y, sf_mex_create("y", &c1_db_u, 0, 0U, 0U, 0U, 0));
      sf_mex_addfield(c1_hb_y, c1_kb_y, "Gain", "Gain", c1_i1);
      c1_eb_u = c1_r0->DecimInterp;
      c1_lb_y = NULL;
      sf_mex_assign(&c1_lb_y, sf_mex_create("y", &c1_eb_u, 0, 0U, 0U, 0U, 0));
      sf_mex_addfield(c1_hb_y, c1_lb_y, "DecimInterp", "DecimInterp", c1_i1);
      c1_fb_u = c1_r0->ScaleI;
      c1_mb_y = NULL;
      sf_mex_assign(&c1_mb_y, sf_mex_create("y", &c1_fb_u, 0, 0U, 0U, 0U, 0));
      sf_mex_addfield(c1_hb_y, c1_mb_y, "ScaleI", "ScaleI", c1_i1);
      c1_gb_u = c1_r0->ScaleQ;
      c1_nb_y = NULL;
      sf_mex_assign(&c1_nb_y, sf_mex_create("y", &c1_gb_u, 0, 0U, 0U, 0U, 0));
      sf_mex_addfield(c1_hb_y, c1_nb_y, "ScaleQ", "ScaleQ", c1_i1);
    }
  }

  sf_mex_setcell(c1_y, 18, c1_hb_y);
  c1_hb_u = chartInstance->c1_is_active_c1_commsdrhw;
  c1_ob_y = NULL;
  sf_mex_assign(&c1_ob_y, sf_mex_create("y", &c1_hb_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c1_y, 19, c1_ob_y);
  sf_mex_assign(&c1_st, c1_y);
  return c1_st;
}

static void set_sim_state_c1_commsdrhw(SFc1_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_u;
  int32_T c1_tmp_sizes[2];
  uint8_T c1_tmp_data[8000];
  int32_T c1_loop_ub;
  int32_T c1_i2;
  real_T c1_dv1[137];
  uint16_T c1_u0;
  uint8_T c1_u1;
  uint8_T c1_u2;
  uint8_T c1_u3;
  uint8_T c1_u4;
  uint32_T c1_uv0[2];
  uint8_T c1_u5;
  uint32_T c1_u6;
  uint8_T c1_u7;
  uint32_T c1_u8;
  uint8_T c1_u9;
  char_T c1_cv0[5];
  uint8_T c1_uv1[255];
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_rv0[255];
  uint8_T (*c1_packet_data)[8000];
  c1_packet_data = (uint8_T (*)[8000])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_u = sf_mex_dup(c1_st);
  c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)),
                      "packet", c1_tmp_data, c1_tmp_sizes);
  ssSetCurrentOutputPortDimensions(chartInstance->S, 1, 0, c1_tmp_sizes[0]);
  ssSetCurrentOutputPortDimensions(chartInstance->S, 1, 1, 1);
  c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
  for (c1_i2 = 0; c1_i2 <= c1_loop_ub; c1_i2++) {
    (*c1_packet_data)[c1_i2] = c1_tmp_data[c1_i2];
  }

  c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 1)),
                        "NetworkLib", c1_dv1);
  for (c1_i2 = 0; c1_i2 < 137; c1_i2++) {
    chartInstance->c1_NetworkLib[c1_i2] = c1_dv1[c1_i2];
  }

  c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 2)),
                        "NetworkLib", c1_dv1);
  for (c1_i2 = 0; c1_i2 < 137; c1_i2++) {
    chartInstance->c1_b_NetworkLib[c1_i2] = c1_dv1[c1_i2];
  }

  c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 3)),
                        "NetworkLib", c1_dv1);
  for (c1_i2 = 0; c1_i2 < 137; c1_i2++) {
    chartInstance->c1_c_NetworkLib[c1_i2] = c1_dv1[c1_i2];
  }

  c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 4)), "Tx",
                        c1_cv0, &c1_u9, &c1_u8, &c1_u7, &c1_u6, &c1_u5, c1_uv0,
                        &c1_u4, &c1_u3, &c1_u2, &c1_u1, &c1_u0);
  chartInstance->c1_Tx.stream.packetSize = c1_u0;
  chartInstance->c1_Tx.stream.packetCount = c1_u1;
  chartInstance->c1_Tx.stream.TSF = c1_u2;
  chartInstance->c1_Tx.stream.TSI = c1_u3;
  chartInstance->c1_Tx.stream.packetType = c1_u4;
  for (c1_i2 = 0; c1_i2 < 2; c1_i2++) {
    chartInstance->c1_Tx.stream.classID[c1_i2] = c1_uv0[c1_i2];
  }

  chartInstance->c1_Tx.stream.hasClassID = c1_u5;
  chartInstance->c1_Tx.stream.streamID = c1_u6;
  chartInstance->c1_Tx.stream.hasStreamID = c1_u7;
  chartInstance->c1_Tx.trailer = c1_u8;
  chartInstance->c1_Tx.hasTrailer = c1_u9;
  for (c1_i2 = 0; c1_i2 < 5; c1_i2++) {
    chartInstance->c1_Tx.datatype[c1_i2] = c1_cv0[c1_i2];
  }

  c1_q_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 5)), "Y0",
                        c1_uv1);
  for (c1_i2 = 0; c1_i2 < 255; c1_i2++) {
    chartInstance->c1_Y0[c1_i2] = c1_uv1[c1_i2];
  }

  c1_s_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 6)), "Y0",
                        c1_uv1);
  for (c1_i2 = 0; c1_i2 < 255; c1_i2++) {
    chartInstance->c1_b_Y0[c1_i2] = c1_uv1[c1_i2];
  }

  chartInstance->c1_Y1 = c1_u_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 7)), "Y1");
  chartInstance->c1_b_Y1 = c1_w_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 8)), "Y1");
  c1_y_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 9)),
                        "ctrlReceiver");
  c1_bb_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 10)),
    "ctrlReceiverBlocking");
  c1_db_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 11)),
    "ctrlSender");
  chartInstance->c1_lastCF = c1_fb_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 12)), "lastCF");
  chartInstance->c1_lastDI = c1_hb_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 13)), "lastDI");
  chartInstance->c1_lastG = c1_jb_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 14)), "lastG");
  chartInstance->c1_lastI = c1_lb_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 15)), "lastI");
  chartInstance->c1_lastQ = c1_nb_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 16)), "lastQ");
  chartInstance->c1_replyId = c1_pb_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 17)), "replyId");
  c1_rb_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 18)),
    "replyQueue", c1_rv0);
  for (c1_i2 = 0; c1_i2 < 255; c1_i2++) {
    chartInstance->c1_replyQueue[c1_i2] = c1_rv0[c1_i2];
  }

  chartInstance->c1_is_active_c1_commsdrhw = c1_ub_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 19)),
     "is_active_c1_commsdrhw");
  sf_mex_destroy(&c1_u);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_commsdrhw(SFc1_commsdrhwInstanceStruct *chartInstance)
{
  char_T *c1_sErr;

  /* System object Terminate function: dsp.UDPSender */
  c1_sErr = GetErrorBuffer(&chartInstance->c1_c_NetworkLib[0U]);
  LibTerminate(&chartInstance->c1_c_NetworkLib[0U]);
  if (*c1_sErr != 0) {
    PrintError(c1_sErr);
  }

  LibDestroy(&chartInstance->c1_c_NetworkLib[0U], 1);
  DestroyUDPInterface(&chartInstance->c1_c_NetworkLib[0U]);

  /* System object Terminate function: dsp.UDPReceiver */
  c1_sErr = GetErrorBuffer(&chartInstance->c1_b_NetworkLib[0U]);
  LibTerminate(&chartInstance->c1_b_NetworkLib[0U]);
  if (*c1_sErr != 0) {
    PrintError(c1_sErr);
  }

  LibDestroy(&chartInstance->c1_b_NetworkLib[0U], 0);
  DestroyUDPInterface(&chartInstance->c1_b_NetworkLib[0U]);

  /* System object Terminate function: dsp.UDPReceiver */
  c1_sErr = GetErrorBuffer(&chartInstance->c1_NetworkLib[0U]);
  LibTerminate(&chartInstance->c1_NetworkLib[0U]);
  if (*c1_sErr != 0) {
    PrintError(c1_sErr);
  }

  LibDestroy(&chartInstance->c1_NetworkLib[0U], 0);
  DestroyUDPInterface(&chartInstance->c1_NetworkLib[0U]);
}

static void sf_c1_commsdrhw(SFc1_commsdrhwInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  c1_chartstep_c1_commsdrhw(chartInstance);
}

static void c1_chartstep_c1_commsdrhw(SFc1_commsdrhwInstanceStruct
  *chartInstance)
{
  int32_T c1_packet_sizes;
  creal_T c1_data[358];
  real_T c1_centerFreq;
  real_T c1_gain;
  real_T c1_interpolation;
  static char_T c1_t2_datatype[5] = { 'i', 'n', 't', '1', '6' };

  char_T *c1_sErr;
  int32_T c1_samplesRead;
  int32_T c1_b_samplesRead;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_cmdDef[18];
  real_T c1_pktLength;
  uint8_T c1_pkt[255];
  real_T c1_scale;
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_b_replyQueue[255];
  uint8_T c1_packet_data[1436];
  real_T *c1_b_centerFreq;
  real_T *c1_b_gain;
  real_T *c1_b_interpolation;
  uint8_T (*c1_b_packet_data)[8000];
  creal_T (*c1_b_data)[358];
  c1_b_interpolation = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c1_b_gain = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c1_b_centerFreq = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c1_b_packet_data = (uint8_T (*)[8000])ssGetOutputPortSignal(chartInstance->S,
    1);
  c1_b_data = (creal_T (*)[358])ssGetInputPortSignal(chartInstance->S, 0);
  for (c1_packet_sizes = 0; c1_packet_sizes < 358; c1_packet_sizes++) {
    c1_data[c1_packet_sizes] = (*c1_b_data)[c1_packet_sizes];
  }

  c1_centerFreq = *c1_b_centerFreq;
  c1_gain = *c1_b_gain;
  c1_interpolation = *c1_b_interpolation;
  if (!chartInstance->c1_Tx_not_empty) {
    for (c1_packet_sizes = 0; c1_packet_sizes < 5; c1_packet_sizes++) {
      chartInstance->c1_Tx.datatype[c1_packet_sizes] =
        c1_t2_datatype[c1_packet_sizes];
    }

    chartInstance->c1_Tx.hasTrailer = 0U;
    chartInstance->c1_Tx.trailer = 0U;
    chartInstance->c1_Tx.stream.hasStreamID = 0U;
    chartInstance->c1_Tx.stream.streamID = 0U;
    chartInstance->c1_Tx.stream.hasClassID = 0U;
    for (c1_packet_sizes = 0; c1_packet_sizes < 2; c1_packet_sizes++) {
      chartInstance->c1_Tx.stream.classID[c1_packet_sizes] = 0U;
    }

    chartInstance->c1_Tx.stream.packetType = 0U;
    chartInstance->c1_Tx.stream.TSI = 0U;
    chartInstance->c1_Tx.stream.TSF = 0U;
    chartInstance->c1_Tx.stream.packetCount = 0U;
    chartInstance->c1_Tx.stream.packetSize = 0U;
    chartInstance->c1_Tx_not_empty = TRUE;
    for (c1_packet_sizes = 0; c1_packet_sizes < 255; c1_packet_sizes++) {
      chartInstance->c1_replyQueue[c1_packet_sizes].ValidMask = 0.0;
      chartInstance->c1_replyQueue[c1_packet_sizes].Fc = 0.0;
      chartInstance->c1_replyQueue[c1_packet_sizes].Gain = 0.0;
      chartInstance->c1_replyQueue[c1_packet_sizes].DecimInterp = 0.0;
      chartInstance->c1_replyQueue[c1_packet_sizes].ScaleI = 0.0;
      chartInstance->c1_replyQueue[c1_packet_sizes].ScaleQ = 0.0;
    }

    chartInstance->c1_replyQueue_not_empty = TRUE;
    chartInstance->c1_ctrlSender_not_empty = TRUE;
    chartInstance->c1_ctrlReceiver_not_empty = TRUE;

    /* System object Outputs function: dsp.UDPReceiver */
    c1_sErr = GetErrorBuffer(&chartInstance->c1_NetworkLib[0U]);
    c1_samplesRead = 255;
    LibOutputs_Network(&chartInstance->c1_NetworkLib[0U], &chartInstance->c1_Y0
                       [0], &(&c1_samplesRead)[0U]);
    if (*c1_sErr != 0) {
      PrintError(c1_sErr);
    }

    chartInstance->c1_Y1 = (uint16_T)c1_samplesRead;
    chartInstance->c1_ctrlReceiverBlocking_not_empty = TRUE;

    /* System object Outputs function: dsp.UDPReceiver */
    c1_sErr = GetErrorBuffer(&chartInstance->c1_b_NetworkLib[0U]);
    c1_b_samplesRead = 255;
    LibOutputs_Network(&chartInstance->c1_b_NetworkLib[0U],
                       &chartInstance->c1_b_Y0[0], &(&c1_b_samplesRead)[0U]);
    if (*c1_sErr != 0) {
      PrintError(c1_sErr);
    }

    chartInstance->c1_b_Y1 = (uint16_T)c1_b_samplesRead;
    c1_USRP2CmdDef(chartInstance, USRP2Opcodes_GetDboardInfo, c1_cmdDef);
    c1_USRP2Cmd2Pkt(chartInstance, c1_cmdDef, c1_pkt, &c1_pktLength);
    c1_Update(chartInstance, c1_pkt, c1_pktLength);
    c1_scale = c1_l_CalcScale(chartInstance, c1_interpolation);
    for (c1_packet_sizes = 0; c1_packet_sizes < 255; c1_packet_sizes++) {
      c1_b_replyQueue[c1_packet_sizes] = chartInstance->
        c1_replyQueue[c1_packet_sizes];
    }

    c1_scale = c1_l_SendConfig(chartInstance, c1_b_replyQueue, c1_centerFreq,
      c1_gain, c1_interpolation, c1_scale, c1_scale);
    for (c1_packet_sizes = 0; c1_packet_sizes < 255; c1_packet_sizes++) {
      chartInstance->c1_replyQueue[c1_packet_sizes] =
        c1_b_replyQueue[c1_packet_sizes];
    }

    c1_pktLength = 1.0;
    while (c1_pktLength <= c1_scale) {
      for (c1_packet_sizes = 0; c1_packet_sizes < 255; c1_packet_sizes++) {
        c1_b_replyQueue[c1_packet_sizes] = chartInstance->
          c1_replyQueue[c1_packet_sizes];
      }

      c1_l_ReceiveReply(chartInstance, c1_b_replyQueue);
      for (c1_packet_sizes = 0; c1_packet_sizes < 255; c1_packet_sizes++) {
        chartInstance->c1_replyQueue[c1_packet_sizes] =
          c1_b_replyQueue[c1_packet_sizes];
      }

      c1_pktLength++;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }
  } else {
    c1_scale = c1_l_CalcScale(chartInstance, *c1_b_interpolation);
    for (c1_packet_sizes = 0; c1_packet_sizes < 255; c1_packet_sizes++) {
      c1_b_replyQueue[c1_packet_sizes] = chartInstance->
        c1_replyQueue[c1_packet_sizes];
    }

    c1_b_l_SendConfig(chartInstance, c1_b_replyQueue, c1_centerFreq, c1_gain,
                      c1_interpolation, c1_scale, c1_scale);
    for (c1_packet_sizes = 0; c1_packet_sizes < 255; c1_packet_sizes++) {
      chartInstance->c1_replyQueue[c1_packet_sizes] =
        c1_b_replyQueue[c1_packet_sizes];
    }
  }

  for (c1_packet_sizes = 0; c1_packet_sizes < 255; c1_packet_sizes++) {
    c1_b_replyQueue[c1_packet_sizes] = chartInstance->
      c1_replyQueue[c1_packet_sizes];
  }

  c1_b_l_ReceiveReply(chartInstance, c1_b_replyQueue);
  for (c1_packet_sizes = 0; c1_packet_sizes < 255; c1_packet_sizes++) {
    chartInstance->c1_replyQueue[c1_packet_sizes] =
      c1_b_replyQueue[c1_packet_sizes];
  }

  c1_VRTEncoder(chartInstance, &chartInstance->c1_Tx, c1_data, c1_packet_data,
                &c1_packet_sizes);
  sf_mex_lw_dim_size_geq_check(8000, 1436, 1);
  ssSetCurrentOutputPortDimensions(chartInstance->S, 1, 0, 1436);
  ssSetCurrentOutputPortDimensions(chartInstance->S, 1, 1, 1);
  for (c1_packet_sizes = 0; c1_packet_sizes < 1436; c1_packet_sizes++) {
    (*c1_b_packet_data)[c1_packet_sizes] = c1_packet_data[c1_packet_sizes];
  }
}

static void initSimStructsc1_commsdrhw(SFc1_commsdrhwInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

const mxArray *sf_c1_commsdrhw_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo;
  c1_ResolvedFunctionInfo c1_info[61];
  const mxArray *c1_m0 = NULL;
  int32_T c1_i3;
  c1_ResolvedFunctionInfo *c1_r1;
  c1_nameCaptureInfo = NULL;
  c1_info_helper(c1_info);
  sf_mex_assign(&c1_m0, sf_mex_createstruct("nameCaptureInfo", 1, 61));
  for (c1_i3 = 0; c1_i3 < 61; c1_i3++) {
    c1_r1 = &c1_info[c1_i3];
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r1->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r1->context)), "context", "nameCaptureInfo",
                    c1_i3);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r1->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c1_r1->name)), "name", "nameCaptureInfo", c1_i3);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r1->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c1_r1->dominantType)), "dominantType",
                    "nameCaptureInfo", c1_i3);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r1->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r1->resolved)), "resolved", "nameCaptureInfo",
                    c1_i3);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r1->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c1_i3);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r1->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c1_i3);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r1->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c1_i3);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r1->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c1_i3);
  }

  sf_mex_assign(&c1_nameCaptureInfo, c1_m0);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[61])
{
  c1_info[0].context = "";
  c1_info[0].name = "VRTEncoder";
  c1_info[0].dominantType = "";
  c1_info[0].resolved =
    "[IXE]$matlabroot$/toolbox/comm/commutilities/VRTEncoder.m";
  c1_info[0].fileTimeLo = 1294315956U;
  c1_info[0].fileTimeHi = 0U;
  c1_info[0].mFileTimeLo = 0U;
  c1_info[0].mFileTimeHi = 0U;
  c1_info[1].context =
    "[IXE]$matlabroot$/toolbox/comm/commutilities/VRTEncoder.m";
  c1_info[1].name = "VRTGetDataStream";
  c1_info[1].dominantType = "";
  c1_info[1].resolved =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/VRTGetDataStream.m";
  c1_info[1].fileTimeLo = 1283100036U;
  c1_info[1].fileTimeHi = 0U;
  c1_info[1].mFileTimeLo = 0U;
  c1_info[1].mFileTimeHi = 0U;
  c1_info[2].context =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/VRTGetDataStream.m";
  c1_info[2].name = "VRTGetStream";
  c1_info[2].dominantType = "";
  c1_info[2].resolved =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/VRTGetStream.m";
  c1_info[2].fileTimeLo = 1283100038U;
  c1_info[2].fileTimeHi = 0U;
  c1_info[2].mFileTimeLo = 0U;
  c1_info[2].mFileTimeHi = 0U;
  c1_info[3].context =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/VRTGetDataStream.m";
  c1_info[3].name = "VRTSetStream";
  c1_info[3].dominantType = "struct";
  c1_info[3].resolved =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/VRTSetStream.m";
  c1_info[3].fileTimeLo = 1283100040U;
  c1_info[3].fileTimeHi = 0U;
  c1_info[3].mFileTimeLo = 0U;
  c1_info[3].mFileTimeHi = 0U;
  c1_info[4].context =
    "[IXE]$matlabroot$/toolbox/comm/commutilities/VRTEncoder.m";
  c1_info[4].name = "VRTSetDataStream";
  c1_info[4].dominantType = "struct";
  c1_info[4].resolved =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/VRTSetDataStream.m";
  c1_info[4].fileTimeLo = 1283100040U;
  c1_info[4].fileTimeHi = 0U;
  c1_info[4].mFileTimeLo = 0U;
  c1_info[4].mFileTimeHi = 0U;
  c1_info[5].context = "";
  c1_info[5].name = "repmat";
  c1_info[5].dominantType = "struct";
  c1_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/repmat.m";
  c1_info[5].fileTimeLo = 1286815168U;
  c1_info[5].fileTimeHi = 0U;
  c1_info[5].mFileTimeLo = 0U;
  c1_info[5].mFileTimeHi = 0U;
  c1_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/repmat.m";
  c1_info[6].name = "eml_assert_valid_size_arg";
  c1_info[6].dominantType = "double";
  c1_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c1_info[6].fileTimeLo = 1286815094U;
  c1_info[6].fileTimeHi = 0U;
  c1_info[6].mFileTimeLo = 0U;
  c1_info[6].mFileTimeHi = 0U;
  c1_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c1_info[7].name = "isinf";
  c1_info[7].dominantType = "double";
  c1_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m";
  c1_info[7].fileTimeLo = 1286815160U;
  c1_info[7].fileTimeHi = 0U;
  c1_info[7].mFileTimeLo = 0U;
  c1_info[7].mFileTimeHi = 0U;
  c1_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c1_info[8].name = "mtimes";
  c1_info[8].dominantType = "double";
  c1_info[8].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[8].fileTimeLo = 1289516092U;
  c1_info[8].fileTimeHi = 0U;
  c1_info[8].mFileTimeLo = 0U;
  c1_info[8].mFileTimeHi = 0U;
  c1_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c1_info[9].name = "eml_index_class";
  c1_info[9].dominantType = "";
  c1_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[9].fileTimeLo = 1286815178U;
  c1_info[9].fileTimeHi = 0U;
  c1_info[9].mFileTimeLo = 0U;
  c1_info[9].mFileTimeHi = 0U;
  c1_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c1_info[10].name = "intmax";
  c1_info[10].dominantType = "char";
  c1_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c1_info[10].fileTimeLo = 1286815156U;
  c1_info[10].fileTimeHi = 0U;
  c1_info[10].mFileTimeLo = 0U;
  c1_info[10].mFileTimeHi = 0U;
  c1_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/repmat.m";
  c1_info[11].name = "eml_index_minus";
  c1_info[11].dominantType = "int32";
  c1_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c1_info[11].fileTimeLo = 1286815178U;
  c1_info[11].fileTimeHi = 0U;
  c1_info[11].mFileTimeLo = 0U;
  c1_info[11].mFileTimeHi = 0U;
  c1_info[12].context = "";
  c1_info[12].name = "createsystemobject";
  c1_info[12].dominantType = "";
  c1_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/scomp/createsystemobject.p";
  c1_info[12].fileTimeLo = 1296661054U;
  c1_info[12].fileTimeHi = 0U;
  c1_info[12].mFileTimeLo = 0U;
  c1_info[12].mFileTimeHi = 0U;
  c1_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/scomp/createsystemobject.p";
  c1_info[13].name = "length";
  c1_info[13].dominantType = "cell";
  c1_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c1_info[13].fileTimeLo = 1286815160U;
  c1_info[13].fileTimeHi = 0U;
  c1_info[13].mFileTimeLo = 0U;
  c1_info[13].mFileTimeHi = 0U;
  c1_info[14].context = "";
  c1_info[14].name = "step";
  c1_info[14].dominantType = "dsp.UDPReceiver";
  c1_info[14].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/scomp/step.m";
  c1_info[14].fileTimeLo = 1295970824U;
  c1_info[14].fileTimeHi = 0U;
  c1_info[14].mFileTimeLo = 0U;
  c1_info[14].mFileTimeHi = 0U;
  c1_info[15].context = "";
  c1_info[15].name = "USRP2Opcodes";
  c1_info[15].dominantType = "";
  c1_info[15].resolved =
    "[IXN]$matlabroot$/toolbox/comm/commutilities/USRP2Opcodes.m";
  c1_info[15].fileTimeLo = 1283099606U;
  c1_info[15].fileTimeHi = 0U;
  c1_info[15].mFileTimeLo = 0U;
  c1_info[15].mFileTimeHi = 0U;
  c1_info[16].context = "";
  c1_info[16].name = "USRP2RuntimeControl";
  c1_info[16].dominantType = "USRP2Opcodes";
  c1_info[16].resolved =
    "[IXE]$matlabroot$/toolbox/comm/commutilities/USRP2RuntimeControl.m";
  c1_info[16].fileTimeLo = 1289515708U;
  c1_info[16].fileTimeHi = 0U;
  c1_info[16].mFileTimeLo = 0U;
  c1_info[16].mFileTimeHi = 0U;
  c1_info[17].context =
    "[IXE]$matlabroot$/toolbox/comm/commutilities/USRP2RuntimeControl.m!l_Generic";
  c1_info[17].name = "USRP2CmdDef";
  c1_info[17].dominantType = "USRP2Opcodes";
  c1_info[17].resolved =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/USRP2CmdDef.m";
  c1_info[17].fileTimeLo = 1283100026U;
  c1_info[17].fileTimeHi = 0U;
  c1_info[17].mFileTimeLo = 0U;
  c1_info[17].mFileTimeHi = 0U;
  c1_info[18].context =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/USRP2CmdDef.m";
  c1_info[18].name = "USRP2FieldDtypes";
  c1_info[18].dominantType = "";
  c1_info[18].resolved =
    "[IXN]$matlabroot$/toolbox/comm/commutilities/USRP2FieldDtypes.m";
  c1_info[18].fileTimeLo = 1283099604U;
  c1_info[18].fileTimeHi = 0U;
  c1_info[18].mFileTimeLo = 0U;
  c1_info[18].mFileTimeHi = 0U;
  c1_info[19].context =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/USRP2CmdDef.m!l_fdef";
  c1_info[19].name = "USRP2PackFieldVal";
  c1_info[19].dominantType = "USRP2FieldDtypes";
  c1_info[19].resolved =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/USRP2PackFieldVal.m";
  c1_info[19].fileTimeLo = 1283100030U;
  c1_info[19].fileTimeHi = 0U;
  c1_info[19].mFileTimeLo = 0U;
  c1_info[19].mFileTimeHi = 0U;
  c1_info[20].context =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/USRP2PackFieldVal.m";
  c1_info[20].name = "VRTConvertData";
  c1_info[20].dominantType = "char";
  c1_info[20].resolved =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/VRTConvertData.m";
  c1_info[20].fileTimeLo = 1283100034U;
  c1_info[20].fileTimeHi = 0U;
  c1_info[20].mFileTimeLo = 0U;
  c1_info[20].mFileTimeHi = 0U;
  c1_info[21].context =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/VRTConvertData.m";
  c1_info[21].name = "mpower";
  c1_info[21].dominantType = "double";
  c1_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c1_info[21].fileTimeLo = 1286815242U;
  c1_info[21].fileTimeHi = 0U;
  c1_info[21].mFileTimeLo = 0U;
  c1_info[21].mFileTimeHi = 0U;
  c1_info[22].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c1_info[22].name = "power";
  c1_info[22].dominantType = "double";
  c1_info[22].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c1_info[22].fileTimeLo = 1286815244U;
  c1_info[22].fileTimeHi = 0U;
  c1_info[22].mFileTimeLo = 0U;
  c1_info[22].mFileTimeHi = 0U;
  c1_info[23].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c1_info[23].name = "eml_scalar_eg";
  c1_info[23].dominantType = "double";
  c1_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[23].fileTimeLo = 1286815196U;
  c1_info[23].fileTimeHi = 0U;
  c1_info[23].mFileTimeLo = 0U;
  c1_info[23].mFileTimeHi = 0U;
  c1_info[24].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c1_info[24].name = "eml_scalexp_alloc";
  c1_info[24].dominantType = "double";
  c1_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c1_info[24].fileTimeLo = 1286815196U;
  c1_info[24].fileTimeHi = 0U;
  c1_info[24].mFileTimeLo = 0U;
  c1_info[24].mFileTimeHi = 0U;
  c1_info[25].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c1_info[25].name = "eml_scalar_floor";
  c1_info[25].dominantType = "double";
  c1_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c1_info[25].fileTimeLo = 1286815126U;
  c1_info[25].fileTimeHi = 0U;
  c1_info[25].mFileTimeLo = 0U;
  c1_info[25].mFileTimeHi = 0U;
  c1_info[26].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c1_info[26].name = "eml_error";
  c1_info[26].dominantType = "char";
  c1_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c1_info[26].fileTimeLo = 1286815100U;
  c1_info[26].fileTimeHi = 0U;
  c1_info[26].mFileTimeLo = 0U;
  c1_info[26].mFileTimeHi = 0U;
  c1_info[27].context =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/VRTConvertData.m";
  c1_info[27].name = "floor";
  c1_info[27].dominantType = "double";
  c1_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[27].fileTimeLo = 1286815142U;
  c1_info[27].fileTimeHi = 0U;
  c1_info[27].mFileTimeLo = 0U;
  c1_info[27].mFileTimeHi = 0U;
  c1_info[28].context =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/VRTConvertData.m";
  c1_info[28].name = "mod";
  c1_info[28].dominantType = "double";
  c1_info[28].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m";
  c1_info[28].fileTimeLo = 1286815144U;
  c1_info[28].fileTimeHi = 0U;
  c1_info[28].mFileTimeLo = 0U;
  c1_info[28].mFileTimeHi = 0U;
  c1_info[29].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m";
  c1_info[29].name = "eml_scalar_mod";
  c1_info[29].dominantType = "double";
  c1_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_mod.m";
  c1_info[29].fileTimeLo = 1286815130U;
  c1_info[29].fileTimeHi = 0U;
  c1_info[29].mFileTimeLo = 0U;
  c1_info[29].mFileTimeHi = 0U;
  c1_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_mod.m";
  c1_info[30].name = "eml_scalar_round";
  c1_info[30].dominantType = "double";
  c1_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_round.m";
  c1_info[30].fileTimeLo = 1289516028U;
  c1_info[30].fileTimeHi = 0U;
  c1_info[30].mFileTimeLo = 0U;
  c1_info[30].mFileTimeHi = 0U;
  c1_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_round.m!scalar_round";
  c1_info[31].name = "eps";
  c1_info[31].dominantType = "char";
  c1_info[31].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c1_info[31].fileTimeLo = 1286815086U;
  c1_info[31].fileTimeHi = 0U;
  c1_info[31].mFileTimeLo = 0U;
  c1_info[31].mFileTimeHi = 0U;
  c1_info[32].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c1_info[32].name = "eml_is_float_class";
  c1_info[32].dominantType = "char";
  c1_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c1_info[32].fileTimeLo = 1286815182U;
  c1_info[32].fileTimeHi = 0U;
  c1_info[32].mFileTimeLo = 0U;
  c1_info[32].mFileTimeHi = 0U;
  c1_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_round.m!scalar_round";
  c1_info[33].name = "mrdivide";
  c1_info[33].dominantType = "double";
  c1_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[33].fileTimeLo = 1296661054U;
  c1_info[33].fileTimeHi = 0U;
  c1_info[33].mFileTimeLo = 1289516092U;
  c1_info[33].mFileTimeHi = 0U;
  c1_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[34].name = "rdivide";
  c1_info[34].dominantType = "double";
  c1_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[34].fileTimeLo = 1286815244U;
  c1_info[34].fileTimeHi = 0U;
  c1_info[34].mFileTimeLo = 0U;
  c1_info[34].mFileTimeHi = 0U;
  c1_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[35].name = "eml_div";
  c1_info[35].dominantType = "double";
  c1_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c1_info[35].fileTimeLo = 1286815098U;
  c1_info[35].fileTimeHi = 0U;
  c1_info[35].mFileTimeLo = 0U;
  c1_info[35].mFileTimeHi = 0U;
  c1_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_mod.m";
  c1_info[36].name = "eml_scalar_abs";
  c1_info[36].dominantType = "double";
  c1_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c1_info[36].fileTimeLo = 1286815112U;
  c1_info[36].fileTimeHi = 0U;
  c1_info[36].mFileTimeLo = 0U;
  c1_info[36].mFileTimeHi = 0U;
  c1_info[37].context =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/USRP2PackFieldVal.m";
  c1_info[37].name = "typecast";
  c1_info[37].dominantType = "uint32";
  c1_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datatypes/typecast.m";
  c1_info[37].fileTimeLo = 1286815076U;
  c1_info[37].fileTimeHi = 0U;
  c1_info[37].mFileTimeLo = 0U;
  c1_info[37].mFileTimeHi = 0U;
  c1_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datatypes/typecast.m";
  c1_info[38].name = "eml_unsigned_class";
  c1_info[38].dominantType = "char";
  c1_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m";
  c1_info[38].fileTimeLo = 1286815200U;
  c1_info[38].fileTimeHi = 0U;
  c1_info[38].mFileTimeLo = 0U;
  c1_info[38].mFileTimeHi = 0U;
  c1_info[39].context =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/USRP2CmdDef.m";
  c1_info[39].name = "USRP2CmdFields";
  c1_info[39].dominantType = "";
  c1_info[39].resolved =
    "[IXN]$matlabroot$/toolbox/comm/commutilities/USRP2CmdFields.m";
  c1_info[39].fileTimeLo = 1283099604U;
  c1_info[39].fileTimeHi = 0U;
  c1_info[39].mFileTimeLo = 0U;
  c1_info[39].mFileTimeHi = 0U;
  c1_info[40].context =
    "[IXE]$matlabroot$/toolbox/comm/commutilities/USRP2RuntimeControl.m!l_Generic";
  c1_info[40].name = "USRP2Cmd2Pkt";
  c1_info[40].dominantType = "struct";
  c1_info[40].resolved =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/USRP2Cmd2Pkt.m";
  c1_info[40].fileTimeLo = 1283100026U;
  c1_info[40].fileTimeHi = 0U;
  c1_info[40].mFileTimeLo = 0U;
  c1_info[40].mFileTimeHi = 0U;
  c1_info[41].context = "";
  c1_info[41].name = "log2";
  c1_info[41].dominantType = "double";
  c1_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/log2.m";
  c1_info[41].fileTimeLo = 1286815144U;
  c1_info[41].fileTimeHi = 0U;
  c1_info[41].mFileTimeLo = 0U;
  c1_info[41].mFileTimeHi = 0U;
  c1_info[42].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/log2.m";
  c1_info[42].name = "eml_scalar_log2";
  c1_info[42].dominantType = "double";
  c1_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_log2.m";
  c1_info[42].fileTimeLo = 1286815128U;
  c1_info[42].fileTimeHi = 0U;
  c1_info[42].mFileTimeLo = 0U;
  c1_info[42].mFileTimeHi = 0U;
  c1_info[43].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_log2.m!scalar_log2";
  c1_info[43].name = "realmax";
  c1_info[43].dominantType = "char";
  c1_info[43].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmax.m";
  c1_info[43].fileTimeLo = 1286815166U;
  c1_info[43].fileTimeHi = 0U;
  c1_info[43].mFileTimeLo = 0U;
  c1_info[43].mFileTimeHi = 0U;
  c1_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_log2.m!scalar_real_log2";
  c1_info[44].name = "eml_guarded_inf";
  c1_info[44].dominantType = "char";
  c1_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_inf.m";
  c1_info[44].fileTimeLo = 1286815176U;
  c1_info[44].fileTimeHi = 0U;
  c1_info[44].mFileTimeLo = 0U;
  c1_info[44].mFileTimeHi = 0U;
  c1_info[45].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_log2.m!scalar_real_log2";
  c1_info[45].name = "eml_guarded_nan";
  c1_info[45].dominantType = "char";
  c1_info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c1_info[45].fileTimeLo = 1286815176U;
  c1_info[45].fileTimeHi = 0U;
  c1_info[45].mFileTimeLo = 0U;
  c1_info[45].mFileTimeHi = 0U;
  c1_info[46].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_log2.m!scalar_real_log2";
  c1_info[46].name = "isfinite";
  c1_info[46].dominantType = "double";
  c1_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isfinite.m";
  c1_info[46].fileTimeLo = 1286815158U;
  c1_info[46].fileTimeHi = 0U;
  c1_info[46].mFileTimeLo = 0U;
  c1_info[46].mFileTimeHi = 0U;
  c1_info[47].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isfinite.m";
  c1_info[47].name = "isnan";
  c1_info[47].dominantType = "double";
  c1_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c1_info[47].fileTimeLo = 1286815160U;
  c1_info[47].fileTimeHi = 0U;
  c1_info[47].mFileTimeLo = 0U;
  c1_info[47].mFileTimeHi = 0U;
  c1_info[48].context = "";
  c1_info[48].name = "ceil";
  c1_info[48].dominantType = "double";
  c1_info[48].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/ceil.m";
  c1_info[48].fileTimeLo = 1286815106U;
  c1_info[48].fileTimeHi = 0U;
  c1_info[48].mFileTimeLo = 0U;
  c1_info[48].mFileTimeHi = 0U;
  c1_info[49].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/ceil.m";
  c1_info[49].name = "eml_scalar_ceil";
  c1_info[49].dominantType = "double";
  c1_info[49].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_ceil.m";
  c1_info[49].fileTimeLo = 1286815120U;
  c1_info[49].fileTimeHi = 0U;
  c1_info[49].mFileTimeLo = 0U;
  c1_info[49].mFileTimeHi = 0U;
  c1_info[50].context =
    "[IXE]$matlabroot$/toolbox/comm/commutilities/USRP2RuntimeControl.m!l_Config";
  c1_info[50].name = "USRP2SetCmdVal";
  c1_info[50].dominantType = "USRP2CmdFields";
  c1_info[50].resolved =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/USRP2SetCmdVal.m";
  c1_info[50].fileTimeLo = 1283100032U;
  c1_info[50].fileTimeHi = 0U;
  c1_info[50].mFileTimeLo = 0U;
  c1_info[50].mFileTimeHi = 0U;
  c1_info[51].context =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/USRP2SetCmdVal.m";
  c1_info[51].name = "error";
  c1_info[51].dominantType = "char";
  c1_info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/lang/error.m";
  c1_info[51].fileTimeLo = 1286815218U;
  c1_info[51].fileTimeHi = 0U;
  c1_info[51].mFileTimeLo = 0U;
  c1_info[51].mFileTimeHi = 0U;
  c1_info[52].context = "";
  c1_info[52].name = "USRP2RuntimeControlReplies";
  c1_info[52].dominantType = "uint8";
  c1_info[52].resolved =
    "[IXE]$matlabroot$/toolbox/comm/commutilities/USRP2RuntimeControlReplies.m";
  c1_info[52].fileTimeLo = 1289515708U;
  c1_info[52].fileTimeHi = 0U;
  c1_info[52].mFileTimeLo = 0U;
  c1_info[52].mFileTimeHi = 0U;
  c1_info[53].context =
    "[IXE]$matlabroot$/toolbox/comm/commutilities/USRP2RuntimeControlReplies.m";
  c1_info[53].name = "USRP2Pkt2Cmd";
  c1_info[53].dominantType = "uint8";
  c1_info[53].resolved =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/USRP2Pkt2Cmd.m";
  c1_info[53].fileTimeLo = 1283100030U;
  c1_info[53].fileTimeHi = 0U;
  c1_info[53].mFileTimeLo = 0U;
  c1_info[53].mFileTimeHi = 0U;
  c1_info[54].context =
    "[IXE]$matlabroot$/toolbox/comm/commutilities/USRP2RuntimeControlReplies.m";
  c1_info[54].name = "USRP2GetCmdVal";
  c1_info[54].dominantType = "USRP2CmdFields";
  c1_info[54].resolved =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/USRP2GetCmdVal.m";
  c1_info[54].fileTimeLo = 1283100028U;
  c1_info[54].fileTimeHi = 0U;
  c1_info[54].mFileTimeLo = 0U;
  c1_info[54].mFileTimeHi = 0U;
  c1_info[55].context =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/USRP2GetCmdVal.m";
  c1_info[55].name = "USRP2UnpackFieldVal";
  c1_info[55].dominantType = "USRP2FieldDtypes";
  c1_info[55].resolved =
    "[IXPE]$matlabroot$/toolbox/comm/commutilities/private/USRP2UnpackFieldVal.m";
  c1_info[55].fileTimeLo = 1283100032U;
  c1_info[55].fileTimeHi = 0U;
  c1_info[55].mFileTimeLo = 0U;
  c1_info[55].mFileTimeHi = 0U;
  c1_info[56].context = "";
  c1_info[56].name = "bitand";
  c1_info[56].dominantType = "uint8";
  c1_info[56].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitand.m";
  c1_info[56].fileTimeLo = 1286815234U;
  c1_info[56].fileTimeHi = 0U;
  c1_info[56].mFileTimeLo = 0U;
  c1_info[56].mFileTimeHi = 0U;
  c1_info[57].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitand.m";
  c1_info[57].name = "eml_scalexp_compatible";
  c1_info[57].dominantType = "uint8";
  c1_info[57].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c1_info[57].fileTimeLo = 1286815196U;
  c1_info[57].fileTimeHi = 0U;
  c1_info[57].mFileTimeLo = 0U;
  c1_info[57].mFileTimeHi = 0U;
  c1_info[58].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitand.m";
  c1_info[58].name = "eml_isa_uint";
  c1_info[58].dominantType = "uint8";
  c1_info[58].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  c1_info[58].fileTimeLo = 1286815184U;
  c1_info[58].fileTimeHi = 0U;
  c1_info[58].mFileTimeLo = 0U;
  c1_info[58].mFileTimeHi = 0U;
  c1_info[59].context =
    "[IXE]$matlabroot$/toolbox/comm/commutilities/VRTEncoder.m!writeIFDataPacket";
  c1_info[59].name = "bitshift";
  c1_info[59].dominantType = "uint8";
  c1_info[59].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c1_info[59].fileTimeLo = 1286815238U;
  c1_info[59].fileTimeHi = 0U;
  c1_info[59].mFileTimeLo = 0U;
  c1_info[59].mFileTimeHi = 0U;
  c1_info[60].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c1_info[60].name = "eml_int_nbits";
  c1_info[60].dominantType = "char";
  c1_info[60].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_nbits.m";
  c1_info[60].fileTimeLo = 1286815180U;
  c1_info[60].fileTimeHi = 0U;
  c1_info[60].mFileTimeLo = 0U;
  c1_info[60].mFileTimeHi = 0U;
}

static void c1_USRP2CmdDef(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_USRP2Opcodes c1_cmd, c1_s7P91ApZ2CkwDPZE5FamWSB c1_cmdDef[18])
{
  int32_T c1_i4;
  static c1_s7P91ApZ2CkwDPZE5FamWSB c1_r2 = { 0.0, 0.0,
    USRP2FieldDtypes_usrp2_uint8_T, { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
      0U, 0U, 0U, 0U, 0U } };

  c1_s7P91ApZ2CkwDPZE5FamWSB c1_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_b_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_c_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_d_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_e_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_f_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_g_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_h_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_i_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_j_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_k_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_l_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_m_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_n_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_o_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_p_expl_temp;
  for (c1_i4 = 0; c1_i4 < 18; c1_i4++) {
    c1_cmdDef[c1_i4] = c1_r2;
  }

  c1_b_l_fdef(chartInstance, 1.0, 1.0, USRP2FieldDtypes_usrp2_uint8_T, (real_T)
              (int32_T)c1_cmd, &c1_cmdDef[(int32_T)USRP2CmdFields_Opcode - 1].
              offset, &c1_cmdDef[(int32_T)USRP2CmdFields_Opcode - 1].fsize,
              &c1_cmdDef[(int32_T)USRP2CmdFields_Opcode - 1].dtype, c1_cmdDef
              [(int32_T)USRP2CmdFields_Opcode - 1].bytes);
  c1_l_fdef(chartInstance, 2.0, 1.0, USRP2FieldDtypes_usrp2_uint8_T, &c1_cmdDef
            [(int32_T)USRP2CmdFields_Length - 1].offset, &c1_cmdDef[(int32_T)
            USRP2CmdFields_Length - 1].fsize, &c1_cmdDef[(int32_T)
            USRP2CmdFields_Length - 1].dtype, c1_cmdDef[(int32_T)
            USRP2CmdFields_Length - 1].bytes);
  c1_expl_temp.offset = 3.0;
  c1_expl_temp.fsize = 1.0;
  c1_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint8_T;
  for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
    c1_expl_temp.bytes[c1_i4] = 0U;
  }

  c1_cmdDef[(int32_T)USRP2CmdFields_ReplyId - 1] = c1_expl_temp;
  c1_b_expl_temp.offset = 4.0;
  c1_b_expl_temp.fsize = 1.0;
  c1_b_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint8_T;
  for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
    c1_b_expl_temp.bytes[c1_i4] = 0U;
  }

  c1_cmdDef[(int32_T)USRP2CmdFields_Ok - 1] = c1_b_expl_temp;
  switch ((int32_T)c1_cmd) {
   case 129:
    c1_c_expl_temp.offset = 5.0;
    c1_c_expl_temp.fsize = 6.0;
    c1_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_c_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_MacAddr - 1] = c1_c_expl_temp;
    c1_d_expl_temp.offset = 11.0;
    c1_d_expl_temp.fsize = 2.0;
    c1_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_d_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_HwRev - 1] = c1_d_expl_temp;
    c1_e_expl_temp.offset = 13.0;
    c1_e_expl_temp.fsize = 8.0;
    c1_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_e_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_FpgaMd5Lo - 1] = c1_e_expl_temp;
    c1_f_expl_temp.offset = 21.0;
    c1_f_expl_temp.fsize = 8.0;
    c1_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_f_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_FpgaMd5Hi - 1] = c1_f_expl_temp;
    c1_g_expl_temp.offset = 29.0;
    c1_g_expl_temp.fsize = 8.0;
    c1_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_g_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_FirmwareMd5Lo - 1] = c1_g_expl_temp;
    c1_h_expl_temp.offset = 37.0;
    c1_h_expl_temp.fsize = 8.0;
    c1_h_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_h_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_FirmwareMd5Hi - 1] = c1_h_expl_temp;
    break;

   case 4:
    c1_c_expl_temp.offset = 5.0;
    c1_c_expl_temp.fsize = 2.0;
    c1_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_c_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_Valid - 1] = c1_c_expl_temp;
    c1_d_expl_temp.offset = 7.0;
    c1_d_expl_temp.fsize = 2.0;
    c1_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_d_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_Gain - 1] = c1_d_expl_temp;
    c1_e_expl_temp.offset = 9.0;
    c1_e_expl_temp.fsize = 8.0;
    c1_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_e_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_CenterFreq - 1] = c1_e_expl_temp;
    c1_f_expl_temp.offset = 17.0;
    c1_f_expl_temp.fsize = 4.0;
    c1_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_f_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_Decimation - 1] = c1_f_expl_temp;
    c1_g_expl_temp.offset = 21.0;
    c1_g_expl_temp.fsize = 2.0;
    c1_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_g_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_ScaleI - 1] = c1_g_expl_temp;
    c1_h_expl_temp.offset = 23.0;
    c1_h_expl_temp.fsize = 2.0;
    c1_h_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_h_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_ScaleQ - 1] = c1_h_expl_temp;
    break;

   case 132:
    c1_c_expl_temp.offset = 5.0;
    c1_c_expl_temp.fsize = 2.0;
    c1_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_c_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_ConfigOk - 1] = c1_c_expl_temp;
    c1_d_expl_temp.offset = 7.0;
    c1_d_expl_temp.fsize = 2.0;
    c1_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_d_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_SpectrumInverted - 1] = c1_d_expl_temp;
    c1_e_expl_temp.offset = 9.0;
    c1_e_expl_temp.fsize = 8.0;
    c1_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_e_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_BasebandFreq - 1] = c1_e_expl_temp;
    c1_f_expl_temp.offset = 17.0;
    c1_f_expl_temp.fsize = 8.0;
    c1_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_f_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_DdcFreq - 1] = c1_f_expl_temp;
    c1_g_expl_temp.offset = 25.0;
    c1_g_expl_temp.fsize = 8.0;
    c1_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_g_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_ResidualFreq - 1] = c1_g_expl_temp;
    break;

   case 5:
    c1_c_expl_temp.offset = 5.0;
    c1_c_expl_temp.fsize = 2.0;
    c1_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_c_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_Valid - 1] = c1_c_expl_temp;
    c1_d_expl_temp.offset = 7.0;
    c1_d_expl_temp.fsize = 2.0;
    c1_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_d_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_Gain - 1] = c1_d_expl_temp;
    c1_e_expl_temp.offset = 9.0;
    c1_e_expl_temp.fsize = 8.0;
    c1_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_e_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_CenterFreq - 1] = c1_e_expl_temp;
    c1_f_expl_temp.offset = 17.0;
    c1_f_expl_temp.fsize = 4.0;
    c1_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_f_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_Interpolation - 1] = c1_f_expl_temp;
    c1_g_expl_temp.offset = 21.0;
    c1_g_expl_temp.fsize = 2.0;
    c1_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_g_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_ScaleI - 1] = c1_g_expl_temp;
    c1_h_expl_temp.offset = 23.0;
    c1_h_expl_temp.fsize = 2.0;
    c1_h_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_h_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_ScaleQ - 1] = c1_h_expl_temp;
    break;

   case 133:
    c1_c_expl_temp.offset = 5.0;
    c1_c_expl_temp.fsize = 2.0;
    c1_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_c_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_ConfigOk - 1] = c1_c_expl_temp;
    c1_d_expl_temp.offset = 7.0;
    c1_d_expl_temp.fsize = 2.0;
    c1_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_d_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_SpectrumInverted - 1] = c1_d_expl_temp;
    c1_e_expl_temp.offset = 9.0;
    c1_e_expl_temp.fsize = 8.0;
    c1_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_e_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_BasebandFreq - 1] = c1_e_expl_temp;
    c1_f_expl_temp.offset = 17.0;
    c1_f_expl_temp.fsize = 8.0;
    c1_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_f_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_DucFreq - 1] = c1_f_expl_temp;
    c1_g_expl_temp.offset = 25.0;
    c1_g_expl_temp.fsize = 8.0;
    c1_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_g_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_ResidualFreq - 1] = c1_g_expl_temp;
    break;

   case 6:
    c1_c_expl_temp.offset = 5.0;
    c1_c_expl_temp.fsize = 4.0;
    c1_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_c_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_ItemsPerFrame - 1] = c1_c_expl_temp;
    c1_d_expl_temp.offset = 9.0;
    c1_d_expl_temp.fsize = 4.0;
    c1_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_d_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_TimeInt - 1] = c1_d_expl_temp;
    c1_e_expl_temp.offset = 13.0;
    c1_e_expl_temp.fsize = 4.0;
    c1_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_e_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_TimeFrac - 1] = c1_e_expl_temp;
    break;

   case 137:
    c1_c_expl_temp.offset = 5.0;
    c1_c_expl_temp.fsize = 4.0;
    c1_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_c_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_TxDbId - 1] = c1_c_expl_temp;
    c1_d_expl_temp.offset = 9.0;
    c1_d_expl_temp.fsize = 8.0;
    c1_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_d_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_TxFreqMin - 1] = c1_d_expl_temp;
    c1_e_expl_temp.offset = 17.0;
    c1_e_expl_temp.fsize = 8.0;
    c1_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_e_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_TxFreqMax - 1] = c1_e_expl_temp;
    c1_f_expl_temp.offset = 25.0;
    c1_f_expl_temp.fsize = 2.0;
    c1_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_f_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_TxGainMin - 1] = c1_f_expl_temp;
    c1_g_expl_temp.offset = 27.0;
    c1_g_expl_temp.fsize = 2.0;
    c1_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_g_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_TxGainMax - 1] = c1_g_expl_temp;
    c1_h_expl_temp.offset = 29.0;
    c1_h_expl_temp.fsize = 2.0;
    c1_h_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_h_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_TxGainStepSize - 1] = c1_h_expl_temp;
    c1_i_expl_temp.offset = 31.0;
    c1_i_expl_temp.fsize = 2.0;
    c1_i_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_i_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_TxDbReserved - 1] = c1_i_expl_temp;
    c1_j_expl_temp.offset = 33.0;
    c1_j_expl_temp.fsize = 4.0;
    c1_j_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_j_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_RxDbId - 1] = c1_j_expl_temp;
    c1_k_expl_temp.offset = 37.0;
    c1_k_expl_temp.fsize = 8.0;
    c1_k_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_k_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_RxFreqMin - 1] = c1_k_expl_temp;
    c1_l_expl_temp.offset = 45.0;
    c1_l_expl_temp.fsize = 8.0;
    c1_l_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_l_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_RxFreqMax - 1] = c1_l_expl_temp;
    c1_m_expl_temp.offset = 53.0;
    c1_m_expl_temp.fsize = 2.0;
    c1_m_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_m_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_RxGainMin - 1] = c1_m_expl_temp;
    c1_n_expl_temp.offset = 55.0;
    c1_n_expl_temp.fsize = 2.0;
    c1_n_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_n_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_RxGainMax - 1] = c1_n_expl_temp;
    c1_o_expl_temp.offset = 57.0;
    c1_o_expl_temp.fsize = 2.0;
    c1_o_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_o_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_RxGainStepSize - 1] = c1_o_expl_temp;
    c1_p_expl_temp.offset = 59.0;
    c1_p_expl_temp.fsize = 2.0;
    c1_p_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_p_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_RxDbReserved - 1] = c1_p_expl_temp;
    break;

   case 14:
    c1_c_expl_temp.offset = 5.0;
    c1_c_expl_temp.fsize = 8.0;
    c1_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_c_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_FreqOffset - 1] = c1_c_expl_temp;
    break;

   case 13:
    c1_c_expl_temp.offset = 5.0;
    c1_c_expl_temp.fsize = 8.0;
    c1_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i4 = 0; c1_i4 < 16; c1_i4++) {
      c1_c_expl_temp.bytes[c1_i4] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_FreqOffset - 1] = c1_c_expl_temp;
    break;
  }
}

static void c1_l_fdef(SFc1_commsdrhwInstanceStruct *chartInstance, real_T
                      c1_offset, real_T c1_fsize, c1_USRP2FieldDtypes c1_dtype,
                      real_T *c1_s_offset, real_T *c1_s_fsize,
                      c1_USRP2FieldDtypes *c1_s_dtype, uint8_T c1_s_bytes[16])
{
  int32_T c1_i5;
  *c1_s_offset = c1_offset;
  *c1_s_fsize = c1_fsize;
  *c1_s_dtype = c1_dtype;
  for (c1_i5 = 0; c1_i5 < 16; c1_i5++) {
    c1_s_bytes[c1_i5] = 0U;
  }
}

static void c1_b_l_fdef(SFc1_commsdrhwInstanceStruct *chartInstance, real_T
  c1_offset, real_T c1_fsize, c1_USRP2FieldDtypes c1_dtype, real_T c1_val,
  real_T *c1_s_offset, real_T *c1_s_fsize, c1_USRP2FieldDtypes *c1_s_dtype,
  uint8_T c1_s_bytes[16])
{
  *c1_s_offset = 1.0;
  *c1_s_fsize = 1.0;
  *c1_s_dtype = c1_dtype;
  c1_USRP2PackFieldVal(chartInstance, c1_dtype, c1_val, c1_s_bytes);
}

static void c1_USRP2PackFieldVal(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_USRP2FieldDtypes c1_dtype, real_T c1_val, uint8_T c1_bytes[16])
{
  int32_T c1_i6;
  real_T c1_d2;
  uint8_T c1_leBytes;
  uint16_T c1_x;
  uint8_T c1_b_leBytes[2];
  uint32_T c1_b_x;
  uint8_T c1_c_leBytes[4];
  real_T c1_y;
  uint8_T c1_d_leBytes[8];
  static char_T c1_cv1[30] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's', ':', 'U',
    'S', 'R', 'P', '2', ':', 'U', 'n', 'p', 'a', 'c', 'k', 'a', 'b', 'l', 'e',
    'D', 't', 'y', 'p', 'e' };

  char_T c1_u[30];
  const mxArray *c1_b_y = NULL;
  static char_T c1_cv2[30] = { 'T', 'h', 'e', ' ', 'd', 'a', 't', 'a', 't', 'y',
    'p', 'e', ' ', 'c', 'a', 'n', 'n', 'o', 't', ' ', 'b', 'e', ' ', 'p', 'a',
    'c', 'k', 'e', 'd', '.' };

  char_T c1_b_u[30];
  const mxArray *c1_c_y = NULL;
  const mxArray *c1_d_y = NULL;
  char_T c1_c_u[32];
  const mxArray *c1_e_y = NULL;
  char_T c1_d_u[37];
  static char_T c1_cv3[32] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's', ':', 'U',
    'S', 'R', 'P', '2', ':', 'U', 'n', 'k', 'n', 'o', 'w', 'n', 'F', 'i', 'e',
    'l', 'd', 'D', 't', 'y', 'p', 'e' };

  static char_T c1_cv4[37] = { 'U', 'n', 'k', 'n', 'o', 'w', 'n', ' ', 'U', 'S',
    'R', 'P', '2', ' ', 'd', 'a', 't', 'a', 't', 'y', 'p', 'e', ' ', 's', 'p',
    'e', 'c', 'i', 'f', 'i', 'c', 'a', 't', 'i', 'o', 'n', '.' };

  for (c1_i6 = 0; c1_i6 < 16; c1_i6++) {
    c1_bytes[c1_i6] = 0U;
  }

  switch (c1_dtype) {
   case USRP2FieldDtypes_usrp2_uint8_T:
    c1_d2 = c1_val;
    c1_d2 = c1_d2 < 0.0 ? muDoubleScalarCeil(c1_d2 - 0.5) : muDoubleScalarFloor
      (c1_d2 + 0.5);
    if (c1_d2 < 256.0) {
      if (c1_d2 >= 0.0) {
        c1_leBytes = (uint8_T)c1_d2;
      } else {
        c1_leBytes = 0U;
      }
    } else if (c1_d2 >= 256.0) {
      c1_leBytes = MAX_uint8_T;
    } else {
      c1_leBytes = 0U;
    }

    c1_bytes[0] = c1_leBytes;
    break;

   case USRP2FieldDtypes_usrp2_uint16_T:
    c1_d2 = c1_val;
    c1_d2 = c1_d2 < 0.0 ? muDoubleScalarCeil(c1_d2 - 0.5) : muDoubleScalarFloor
      (c1_d2 + 0.5);
    if (c1_d2 < 65536.0) {
      if (c1_d2 >= 0.0) {
        c1_x = (uint16_T)c1_d2;
      } else {
        c1_x = 0U;
      }
    } else if (c1_d2 >= 65536.0) {
      c1_x = MAX_uint16_T;
    } else {
      c1_x = 0U;
    }

    memcpy((void *)&c1_b_leBytes[0], (void *)&c1_x, 2U);
    for (c1_i6 = 0; c1_i6 < 2; c1_i6++) {
      c1_bytes[c1_i6] = c1_b_leBytes[1 - c1_i6];
    }
    break;

   case USRP2FieldDtypes_usrp2_uint32_T:
    c1_d2 = c1_val;
    c1_d2 = c1_d2 < 0.0 ? muDoubleScalarCeil(c1_d2 - 0.5) : muDoubleScalarFloor
      (c1_d2 + 0.5);
    if (c1_d2 < 4.294967296E+9) {
      if (c1_d2 >= 0.0) {
        c1_b_x = (uint32_T)c1_d2;
      } else {
        c1_b_x = 0U;
      }
    } else if (c1_d2 >= 4.294967296E+9) {
      c1_b_x = MAX_uint32_T;
    } else {
      c1_b_x = 0U;
    }

    memcpy((void *)&c1_c_leBytes[0], (void *)&c1_b_x, 4U);
    for (c1_i6 = 0; c1_i6 < 4; c1_i6++) {
      c1_bytes[c1_i6] = c1_c_leBytes[3 - c1_i6];
    }
    break;

   case USRP2FieldDtypes_usrp2_sfix16_En7_T:
    c1_y = muDoubleScalarFloor(c1_val * 128.0);
    for (c1_i6 = 0; c1_i6 < 2; c1_i6++) {
      c1_d2 = c1_mod(chartInstance, c1_y, 256.0);
      c1_d2 = c1_d2 < 0.0 ? muDoubleScalarCeil(c1_d2 - 0.5) :
        muDoubleScalarFloor(c1_d2 + 0.5);
      if (c1_d2 < 256.0) {
        if (c1_d2 >= 0.0) {
          c1_leBytes = (uint8_T)c1_d2;
        } else {
          c1_leBytes = 0U;
        }
      } else if (c1_d2 >= 256.0) {
        c1_leBytes = MAX_uint8_T;
      } else {
        c1_leBytes = 0U;
      }

      c1_y = (c1_y - (real_T)c1_leBytes) / 256.0;
      c1_b_leBytes[c1_i6] = c1_leBytes;
    }

    for (c1_i6 = 0; c1_i6 < 2; c1_i6++) {
      c1_bytes[c1_i6] = c1_b_leBytes[1 - c1_i6];
    }
    break;

   case USRP2FieldDtypes_usrp2_sfix64_En20_T:
    c1_y = muDoubleScalarFloor(c1_val * 1.048576E+6);
    for (c1_i6 = 0; c1_i6 < 8; c1_i6++) {
      c1_d2 = c1_mod(chartInstance, c1_y, 256.0);
      c1_d2 = c1_d2 < 0.0 ? muDoubleScalarCeil(c1_d2 - 0.5) :
        muDoubleScalarFloor(c1_d2 + 0.5);
      if (c1_d2 < 256.0) {
        if (c1_d2 >= 0.0) {
          c1_leBytes = (uint8_T)c1_d2;
        } else {
          c1_leBytes = 0U;
        }
      } else if (c1_d2 >= 256.0) {
        c1_leBytes = MAX_uint8_T;
      } else {
        c1_leBytes = 0U;
      }

      c1_y = (c1_y - (real_T)c1_leBytes) / 256.0;
      c1_d_leBytes[c1_i6] = c1_leBytes;
    }

    for (c1_i6 = 0; c1_i6 < 8; c1_i6++) {
      c1_bytes[c1_i6] = c1_d_leBytes[7 - c1_i6];
    }
    break;

   case USRP2FieldDtypes_usrp2_byteArray_T:
    for (c1_i6 = 0; c1_i6 < 30; c1_i6++) {
      c1_u[c1_i6] = c1_cv1[c1_i6];
    }

    c1_b_y = NULL;
    sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 30));
    for (c1_i6 = 0; c1_i6 < 30; c1_i6++) {
      c1_b_u[c1_i6] = c1_cv2[c1_i6];
    }

    c1_c_y = NULL;
    sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1, 30));
    sf_mex_call("error", 0U, 2U, 14, c1_b_y, 14, c1_c_y);
    break;

   default:
    for (c1_i6 = 0; c1_i6 < 32; c1_i6++) {
      c1_c_u[c1_i6] = c1_cv3[c1_i6];
    }

    c1_d_y = NULL;
    sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_c_u, 10, 0U, 1U, 0U, 2, 1, 32));
    for (c1_i6 = 0; c1_i6 < 37; c1_i6++) {
      c1_d_u[c1_i6] = c1_cv4[c1_i6];
    }

    c1_e_y = NULL;
    sf_mex_assign(&c1_e_y, sf_mex_create("y", c1_d_u, 10, 0U, 1U, 0U, 2, 1, 37));
    sf_mex_call("error", 0U, 2U, 14, c1_d_y, 14, c1_e_y);
    break;
  }
}

static real_T c1_mod(SFc1_commsdrhwInstanceStruct *chartInstance, real_T c1_x,
                     real_T c1_y)
{
  return c1_x - muDoubleScalarFloor(c1_x / 256.0) * 256.0;
}

static void c1_USRP2Cmd2Pkt(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_cmdDef[18], uint8_T c1_pkt[255], real_T
  *c1_pktLen)
{
  int32_T c1_fidx;
  real_T c1_bidx;
  uint8_T c1_lf_bytes[16];
  int32_T c1_tmp_sizes;
  int32_T c1_i7;
  int32_T c1_b_tmp_sizes;
  int32_T c1_loop_ub;
  int32_T c1_tmp_data[66];
  int32_T c1_b_tmp_data[66];
  int32_T c1_c_tmp_data[8];
  static uint8_T c1_uv2[4] = { 0U, 4U, 0U, 0U };

  *c1_pktLen = 0.0;
  for (c1_fidx = 0; c1_fidx < 255; c1_fidx++) {
    c1_pkt[c1_fidx] = 0U;
  }

  c1_fidx = 0;
  while ((c1_fidx + 1 <= 18) && (!(c1_cmdDef[c1_fidx].fsize == 0.0))) {
    for (c1_bidx = 1.0; c1_bidx <= c1_cmdDef[c1_fidx].fsize; c1_bidx++) {
      c1_pkt[sf_mex_lw_bounds_check((int32_T)((c1_cmdDef[c1_fidx].offset +
        c1_bidx) - 1.0), 1, 255) - 1] = c1_cmdDef[c1_fidx].bytes[(int32_T)
        c1_bidx - 1];
    }

    *c1_pktLen += c1_cmdDef[c1_fidx].fsize;
    c1_fidx++;
  }

  c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[1].dtype, *c1_pktLen,
                       c1_lf_bytes);
  if (1.0 > c1_cmdDef[1].fsize) {
    c1_tmp_sizes = 0;
  } else {
    c1_tmp_sizes = sf_mex_lw_bounds_check((int32_T)c1_cmdDef[1].fsize, 1, 16);
  }

  c1_bidx = (c1_cmdDef[1].offset + c1_cmdDef[1].fsize) - 1.0;
  if (c1_cmdDef[1].offset > c1_bidx) {
    c1_fidx = 1;
    c1_i7 = 0;
  } else {
    c1_fidx = sf_mex_lw_bounds_check((int32_T)c1_cmdDef[1].offset, 1, 255);
    c1_i7 = sf_mex_lw_bounds_check((int32_T)c1_bidx, 1, 255);
  }

  c1_b_tmp_sizes = (c1_i7 - c1_fidx) + 1;
  c1_loop_ub = c1_i7 - c1_fidx;
  for (c1_i7 = 0; c1_i7 <= c1_loop_ub; c1_i7++) {
    c1_tmp_data[c1_i7] = c1_fidx + c1_i7;
  }

  c1_loop_ub = c1_b_tmp_sizes - 1;
  for (c1_fidx = 0; c1_fidx <= c1_loop_ub; c1_fidx++) {
    c1_b_tmp_data[c1_fidx] = c1_tmp_data[c1_fidx];
  }

  sf_mex_lw_size_eq_check_1d(c1_b_tmp_sizes, c1_tmp_sizes);
  c1_loop_ub = c1_tmp_sizes - 1;
  for (c1_fidx = 0; c1_fidx <= c1_loop_ub; c1_fidx++) {
    c1_c_tmp_data[c1_fidx] = 1 + c1_fidx;
  }

  c1_loop_ub = c1_tmp_sizes - 1;
  for (c1_fidx = 0; c1_fidx <= c1_loop_ub; c1_fidx++) {
    c1_pkt[c1_b_tmp_data[c1_fidx] - 1] = c1_lf_bytes[c1_c_tmp_data[c1_fidx] - 1];
  }

  chartInstance->c1_replyId_not_empty = TRUE;
  chartInstance->c1_replyId++;
  if (chartInstance->c1_replyId == 255.0) {
    chartInstance->c1_replyId = 1.0;
  }

  c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[2].dtype,
                       chartInstance->c1_replyId, c1_lf_bytes);
  if (1.0 > c1_cmdDef[2].fsize) {
    c1_tmp_sizes = 0;
  } else {
    c1_tmp_sizes = sf_mex_lw_bounds_check((int32_T)c1_cmdDef[2].fsize, 1, 16);
  }

  c1_bidx = (c1_cmdDef[2].offset + c1_cmdDef[2].fsize) - 1.0;
  if (c1_cmdDef[2].offset > c1_bidx) {
    c1_fidx = 1;
    c1_i7 = 0;
  } else {
    c1_fidx = sf_mex_lw_bounds_check((int32_T)c1_cmdDef[2].offset, 1, 255);
    c1_i7 = sf_mex_lw_bounds_check((int32_T)c1_bidx, 1, 255);
  }

  c1_b_tmp_sizes = (c1_i7 - c1_fidx) + 1;
  c1_loop_ub = c1_i7 - c1_fidx;
  for (c1_i7 = 0; c1_i7 <= c1_loop_ub; c1_i7++) {
    c1_tmp_data[c1_i7] = c1_fidx + c1_i7;
  }

  c1_loop_ub = c1_b_tmp_sizes - 1;
  for (c1_fidx = 0; c1_fidx <= c1_loop_ub; c1_fidx++) {
    c1_b_tmp_data[c1_fidx] = c1_tmp_data[c1_fidx];
  }

  sf_mex_lw_size_eq_check_1d(c1_b_tmp_sizes, c1_tmp_sizes);
  c1_loop_ub = c1_tmp_sizes - 1;
  for (c1_fidx = 0; c1_fidx <= c1_loop_ub; c1_fidx++) {
    c1_c_tmp_data[c1_fidx] = 1 + c1_fidx;
  }

  c1_loop_ub = c1_tmp_sizes - 1;
  for (c1_fidx = 0; c1_fidx <= c1_loop_ub; c1_fidx++) {
    c1_pkt[c1_b_tmp_data[c1_fidx] - 1] = c1_lf_bytes[c1_c_tmp_data[c1_fidx] - 1];
  }

  for (c1_fidx = 0; c1_fidx < 4; c1_fidx++) {
    c1_pkt[sf_mex_lw_bounds_check((int32_T)(*c1_pktLen + (1.0 + (real_T)c1_fidx)),
      1, 255) - 1] = c1_uv2[c1_fidx];
  }

  *c1_pktLen += 4.0;
}

static real_T c1_l_CalcScale(SFc1_commsdrhwInstanceStruct *chartInstance, real_T
  c1_interpolation)
{
  real_T c1_fdbl;
  int32_T c1_eint;
  int16_T c1_i8;
  c1_fdbl = muDoubleScalarPower(c1_interpolation, 3.0);
  if (c1_fdbl < 0.0) {
    c1_eml_error(chartInstance);
  }

  if (c1_fdbl == 0.0) {
    c1_fdbl = rtMinusInf;
  } else if (c1_fdbl < 0.0) {
    c1_fdbl = rtNaN;
  } else {
    if ((!muDoubleScalarIsInf(c1_fdbl)) && (!muDoubleScalarIsNaN(c1_fdbl))) {
      if ((!muDoubleScalarIsInf(c1_fdbl)) && (!muDoubleScalarIsNaN(c1_fdbl))) {
        c1_fdbl = frexp(c1_fdbl, &c1_eint);
      } else {
        c1_eint = 0;
      }

      if (c1_fdbl == 0.5) {
        c1_fdbl = (real_T)c1_eint - 1.0;
      } else {
        c1_fdbl = muDoubleScalarLog(c1_fdbl) / 0.69314718055994529 + (real_T)
          c1_eint;
      }
    }
  }

  c1_fdbl = 1.0 / (0.00040283203125 * (muDoubleScalarPower(c1_interpolation, 3.0)
    / muDoubleScalarPower(2.0, muDoubleScalarCeil(c1_fdbl))));
  c1_fdbl = c1_fdbl < 0.0 ? muDoubleScalarCeil(c1_fdbl - 0.5) :
    muDoubleScalarFloor(c1_fdbl + 0.5);
  if (c1_fdbl < 32768.0) {
    if (c1_fdbl >= -32768.0) {
      c1_i8 = (int16_T)c1_fdbl;
    } else {
      c1_i8 = MIN_int16_T;
    }
  } else if (c1_fdbl >= 32768.0) {
    c1_i8 = MAX_int16_T;
  } else {
    c1_i8 = 0;
  }

  return (real_T)c1_i8;
}

static void c1_eml_error(SFc1_commsdrhwInstanceStruct *chartInstance)
{
  int32_T c1_i9;
  static char_T c1_varargin_1[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o',
    'o', 'l', 'b', 'o', 'x', ':', 'l', 'o', 'g', '2', '_', 'd', 'o', 'm', 'a',
    'i', 'n', 'E', 'r', 'r', 'o', 'r' };

  char_T c1_u[30];
  const mxArray *c1_y = NULL;
  for (c1_i9 = 0; c1_i9 < 30; c1_i9++) {
    c1_u[c1_i9] = c1_varargin_1[c1_i9];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 30));
  sf_mex_call("error", 0U, 1U, 14, sf_mex_call("message", 1U, 1U, 14, c1_y));
}

static void c1_USRP2RuntimeControl(SFc1_commsdrhwInstanceStruct *chartInstance,
  real_T c1_varargin_3, real_T *c1_pktLength, uint8_T c1_pkt[255], uint8_T
  *c1_b_replyId, real_T *c1_varargout_1_ValidMask, real_T *c1_varargout_1_Fc,
  real_T *c1_varargout_1_Gain, real_T *c1_varargout_1_DecimInterp, real_T
  *c1_varargout_1_ScaleI, real_T *c1_varargout_1_ScaleQ)
{
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_cmdDef[18];
  int32_T c1_i10;
  static char_T c1_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c1_u[23];
  const mxArray *c1_y = NULL;
  char_T c1_b_u[40];
  static char_T c1_cv5[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  const mxArray *c1_b_y = NULL;
  char_T c1_c_u[23];
  const mxArray *c1_c_y = NULL;
  char_T c1_d_u[40];
  const mxArray *c1_d_y = NULL;
  chartInstance->c1_lastCF_not_empty = TRUE;
  chartInstance->c1_lastG_not_empty = TRUE;
  chartInstance->c1_lastDI_not_empty = TRUE;
  chartInstance->c1_lastI_not_empty = TRUE;
  chartInstance->c1_lastQ_not_empty = TRUE;
  c1_USRP2CmdDef(chartInstance, USRP2Opcodes_ConfigTx, c1_cmdDef);
  *c1_varargout_1_Gain = chartInstance->c1_lastG;
  *c1_varargout_1_DecimInterp = chartInstance->c1_lastDI;
  *c1_varargout_1_ScaleI = chartInstance->c1_lastI;
  *c1_varargout_1_ScaleQ = chartInstance->c1_lastQ;
  *c1_varargout_1_Fc = c1_varargin_3;
  *c1_varargout_1_ValidMask = 2.0;
  if (c1_cmdDef[sf_mex_lw_bounds_check((int32_T)USRP2CmdFields_CenterFreq, 1, 18)
      - 1].fsize == 0.0) {
    for (c1_i10 = 0; c1_i10 < 23; c1_i10++) {
      c1_u[c1_i10] = c1_varargin_1[c1_i10];
    }

    c1_y = NULL;
    sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c1_b_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_CenterFreq;
    for (c1_i10 = 0; c1_i10 < 39; c1_i10++) {
      c1_b_u[c1_i10 + 1] = c1_cv5[c1_i10];
    }

    c1_b_y = NULL;
    sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c1_y, 14, c1_b_y);
  } else {
    c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[(int32_T)
                         USRP2CmdFields_CenterFreq - 1].dtype, c1_varargin_3,
                         c1_cmdDef[sf_mex_lw_bounds_check((int32_T)
      USRP2CmdFields_CenterFreq, 1, 18) - 1].bytes);
  }

  if (c1_cmdDef[sf_mex_lw_bounds_check((int32_T)USRP2CmdFields_Valid, 1, 18) - 1]
      .fsize == 0.0) {
    for (c1_i10 = 0; c1_i10 < 23; c1_i10++) {
      c1_c_u[c1_i10] = c1_varargin_1[c1_i10];
    }

    c1_c_y = NULL;
    sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_c_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c1_d_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Valid;
    for (c1_i10 = 0; c1_i10 < 39; c1_i10++) {
      c1_d_u[c1_i10 + 1] = c1_cv5[c1_i10];
    }

    c1_d_y = NULL;
    sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_d_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c1_c_y, 14, c1_d_y);
  } else {
    c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[(int32_T)USRP2CmdFields_Valid
                         - 1].dtype, 2.0, c1_cmdDef[sf_mex_lw_bounds_check
                         ((int32_T)USRP2CmdFields_Valid, 1, 18) - 1].bytes);
  }

  c1_USRP2Cmd2Pkt(chartInstance, c1_cmdDef, c1_pkt, c1_pktLength);
  chartInstance->c1_lastCF = c1_varargin_3;
  chartInstance->c1_lastG = *c1_varargout_1_Gain;
  chartInstance->c1_lastDI = *c1_varargout_1_DecimInterp;
  chartInstance->c1_lastI = *c1_varargout_1_ScaleI;
  chartInstance->c1_lastQ = *c1_varargout_1_ScaleQ;
  *c1_b_replyId = c1_pkt[2];
}

static void c1_b_USRP2RuntimeControl(SFc1_commsdrhwInstanceStruct *chartInstance,
  real_T c1_varargin_3, real_T *c1_pktLength, uint8_T c1_pkt[255], uint8_T
  *c1_b_replyId, real_T *c1_varargout_1_ValidMask, real_T *c1_varargout_1_Fc,
  real_T *c1_varargout_1_Gain, real_T *c1_varargout_1_DecimInterp, real_T
  *c1_varargout_1_ScaleI, real_T *c1_varargout_1_ScaleQ)
{
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_cmdDef[18];
  int32_T c1_i11;
  static char_T c1_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c1_u[23];
  const mxArray *c1_y = NULL;
  char_T c1_b_u[40];
  static char_T c1_cv6[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  const mxArray *c1_b_y = NULL;
  char_T c1_c_u[23];
  const mxArray *c1_c_y = NULL;
  char_T c1_d_u[40];
  const mxArray *c1_d_y = NULL;
  chartInstance->c1_lastCF_not_empty = TRUE;
  chartInstance->c1_lastG_not_empty = TRUE;
  chartInstance->c1_lastDI_not_empty = TRUE;
  chartInstance->c1_lastI_not_empty = TRUE;
  chartInstance->c1_lastQ_not_empty = TRUE;
  c1_USRP2CmdDef(chartInstance, USRP2Opcodes_ConfigTx, c1_cmdDef);
  *c1_varargout_1_Fc = chartInstance->c1_lastCF;
  *c1_varargout_1_DecimInterp = chartInstance->c1_lastDI;
  *c1_varargout_1_ScaleI = chartInstance->c1_lastI;
  *c1_varargout_1_ScaleQ = chartInstance->c1_lastQ;
  *c1_varargout_1_Gain = c1_varargin_3;
  *c1_varargout_1_ValidMask = 1.0;
  if (c1_cmdDef[sf_mex_lw_bounds_check((int32_T)USRP2CmdFields_Gain, 1, 18) - 1]
      .fsize == 0.0) {
    for (c1_i11 = 0; c1_i11 < 23; c1_i11++) {
      c1_u[c1_i11] = c1_varargin_1[c1_i11];
    }

    c1_y = NULL;
    sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c1_b_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Gain;
    for (c1_i11 = 0; c1_i11 < 39; c1_i11++) {
      c1_b_u[c1_i11 + 1] = c1_cv6[c1_i11];
    }

    c1_b_y = NULL;
    sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c1_y, 14, c1_b_y);
  } else {
    c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[(int32_T)USRP2CmdFields_Gain -
                         1].dtype, c1_varargin_3,
                         c1_cmdDef[sf_mex_lw_bounds_check((int32_T)
      USRP2CmdFields_Gain, 1, 18) - 1].bytes);
  }

  if (c1_cmdDef[sf_mex_lw_bounds_check((int32_T)USRP2CmdFields_Valid, 1, 18) - 1]
      .fsize == 0.0) {
    for (c1_i11 = 0; c1_i11 < 23; c1_i11++) {
      c1_c_u[c1_i11] = c1_varargin_1[c1_i11];
    }

    c1_c_y = NULL;
    sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_c_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c1_d_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Valid;
    for (c1_i11 = 0; c1_i11 < 39; c1_i11++) {
      c1_d_u[c1_i11 + 1] = c1_cv6[c1_i11];
    }

    c1_d_y = NULL;
    sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_d_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c1_c_y, 14, c1_d_y);
  } else {
    c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[(int32_T)USRP2CmdFields_Valid
                         - 1].dtype, 1.0, c1_cmdDef[sf_mex_lw_bounds_check
                         ((int32_T)USRP2CmdFields_Valid, 1, 18) - 1].bytes);
  }

  c1_USRP2Cmd2Pkt(chartInstance, c1_cmdDef, c1_pkt, c1_pktLength);
  chartInstance->c1_lastCF = *c1_varargout_1_Fc;
  chartInstance->c1_lastG = c1_varargin_3;
  chartInstance->c1_lastDI = *c1_varargout_1_DecimInterp;
  chartInstance->c1_lastI = *c1_varargout_1_ScaleI;
  chartInstance->c1_lastQ = *c1_varargout_1_ScaleQ;
  *c1_b_replyId = c1_pkt[2];
}

static void c1_c_USRP2RuntimeControl(SFc1_commsdrhwInstanceStruct *chartInstance,
  real_T c1_varargin_3, real_T *c1_pktLength, uint8_T c1_pkt[255], uint8_T
  *c1_b_replyId, real_T *c1_varargout_1_ValidMask, real_T *c1_varargout_1_Fc,
  real_T *c1_varargout_1_Gain, real_T *c1_varargout_1_DecimInterp, real_T
  *c1_varargout_1_ScaleI, real_T *c1_varargout_1_ScaleQ)
{
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_cmdDef[18];
  int32_T c1_i12;
  static char_T c1_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c1_u[23];
  const mxArray *c1_y = NULL;
  char_T c1_b_u[40];
  static char_T c1_cv7[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  const mxArray *c1_b_y = NULL;
  char_T c1_c_u[23];
  const mxArray *c1_c_y = NULL;
  char_T c1_d_u[40];
  const mxArray *c1_d_y = NULL;
  chartInstance->c1_lastCF_not_empty = TRUE;
  chartInstance->c1_lastG_not_empty = TRUE;
  chartInstance->c1_lastDI_not_empty = TRUE;
  chartInstance->c1_lastI_not_empty = TRUE;
  chartInstance->c1_lastQ_not_empty = TRUE;
  c1_USRP2CmdDef(chartInstance, USRP2Opcodes_ConfigTx, c1_cmdDef);
  *c1_varargout_1_Fc = chartInstance->c1_lastCF;
  *c1_varargout_1_Gain = chartInstance->c1_lastG;
  *c1_varargout_1_ScaleI = chartInstance->c1_lastI;
  *c1_varargout_1_ScaleQ = chartInstance->c1_lastQ;
  *c1_varargout_1_DecimInterp = c1_varargin_3;
  *c1_varargout_1_ValidMask = 4.0;
  if (c1_cmdDef[sf_mex_lw_bounds_check((int32_T)USRP2CmdFields_Decimation, 1, 18)
      - 1].fsize == 0.0) {
    for (c1_i12 = 0; c1_i12 < 23; c1_i12++) {
      c1_u[c1_i12] = c1_varargin_1[c1_i12];
    }

    c1_y = NULL;
    sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c1_b_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Decimation;
    for (c1_i12 = 0; c1_i12 < 39; c1_i12++) {
      c1_b_u[c1_i12 + 1] = c1_cv7[c1_i12];
    }

    c1_b_y = NULL;
    sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c1_y, 14, c1_b_y);
  } else {
    c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[(int32_T)
                         USRP2CmdFields_Decimation - 1].dtype, c1_varargin_3,
                         c1_cmdDef[sf_mex_lw_bounds_check((int32_T)
      USRP2CmdFields_Decimation, 1, 18) - 1].bytes);
  }

  if (c1_cmdDef[sf_mex_lw_bounds_check((int32_T)USRP2CmdFields_Valid, 1, 18) - 1]
      .fsize == 0.0) {
    for (c1_i12 = 0; c1_i12 < 23; c1_i12++) {
      c1_c_u[c1_i12] = c1_varargin_1[c1_i12];
    }

    c1_c_y = NULL;
    sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_c_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c1_d_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Valid;
    for (c1_i12 = 0; c1_i12 < 39; c1_i12++) {
      c1_d_u[c1_i12 + 1] = c1_cv7[c1_i12];
    }

    c1_d_y = NULL;
    sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_d_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c1_c_y, 14, c1_d_y);
  } else {
    c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[(int32_T)USRP2CmdFields_Valid
                         - 1].dtype, 4.0, c1_cmdDef[sf_mex_lw_bounds_check
                         ((int32_T)USRP2CmdFields_Valid, 1, 18) - 1].bytes);
  }

  c1_USRP2Cmd2Pkt(chartInstance, c1_cmdDef, c1_pkt, c1_pktLength);
  chartInstance->c1_lastCF = *c1_varargout_1_Fc;
  chartInstance->c1_lastG = *c1_varargout_1_Gain;
  chartInstance->c1_lastDI = c1_varargin_3;
  chartInstance->c1_lastI = *c1_varargout_1_ScaleI;
  chartInstance->c1_lastQ = *c1_varargout_1_ScaleQ;
  *c1_b_replyId = c1_pkt[2];
}

static void c1_b_USRP2CmdDef(SFc1_commsdrhwInstanceStruct *chartInstance,
  uint8_T c1_cmd, c1_s7P91ApZ2CkwDPZE5FamWSB c1_cmdDef[18])
{
  int32_T c1_i13;
  static c1_s7P91ApZ2CkwDPZE5FamWSB c1_r3 = { 0.0, 0.0,
    USRP2FieldDtypes_usrp2_uint8_T, { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
      0U, 0U, 0U, 0U, 0U } };

  c1_s7P91ApZ2CkwDPZE5FamWSB c1_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_b_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_c_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_d_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_e_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_f_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_g_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_h_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_i_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_j_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_k_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_l_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_m_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_n_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_o_expl_temp;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_p_expl_temp;
  for (c1_i13 = 0; c1_i13 < 18; c1_i13++) {
    c1_cmdDef[c1_i13] = c1_r3;
  }

  c1_b_l_fdef(chartInstance, 1.0, 1.0, USRP2FieldDtypes_usrp2_uint8_T, (real_T)
              c1_cmd, &c1_cmdDef[(int32_T)USRP2CmdFields_Opcode - 1].offset,
              &c1_cmdDef[(int32_T)USRP2CmdFields_Opcode - 1].fsize, &c1_cmdDef
              [(int32_T)USRP2CmdFields_Opcode - 1].dtype, c1_cmdDef[(int32_T)
              USRP2CmdFields_Opcode - 1].bytes);
  c1_l_fdef(chartInstance, 2.0, 1.0, USRP2FieldDtypes_usrp2_uint8_T, &c1_cmdDef
            [(int32_T)USRP2CmdFields_Length - 1].offset, &c1_cmdDef[(int32_T)
            USRP2CmdFields_Length - 1].fsize, &c1_cmdDef[(int32_T)
            USRP2CmdFields_Length - 1].dtype, c1_cmdDef[(int32_T)
            USRP2CmdFields_Length - 1].bytes);
  c1_expl_temp.offset = 3.0;
  c1_expl_temp.fsize = 1.0;
  c1_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint8_T;
  for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
    c1_expl_temp.bytes[c1_i13] = 0U;
  }

  c1_cmdDef[(int32_T)USRP2CmdFields_ReplyId - 1] = c1_expl_temp;
  c1_b_expl_temp.offset = 4.0;
  c1_b_expl_temp.fsize = 1.0;
  c1_b_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint8_T;
  for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
    c1_b_expl_temp.bytes[c1_i13] = 0U;
  }

  c1_cmdDef[(int32_T)USRP2CmdFields_Ok - 1] = c1_b_expl_temp;
  switch (c1_cmd) {
   case 129:
    c1_c_expl_temp.offset = 5.0;
    c1_c_expl_temp.fsize = 6.0;
    c1_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_c_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_MacAddr - 1] = c1_c_expl_temp;
    c1_d_expl_temp.offset = 11.0;
    c1_d_expl_temp.fsize = 2.0;
    c1_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_d_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_HwRev - 1] = c1_d_expl_temp;
    c1_e_expl_temp.offset = 13.0;
    c1_e_expl_temp.fsize = 8.0;
    c1_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_e_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_FpgaMd5Lo - 1] = c1_e_expl_temp;
    c1_f_expl_temp.offset = 21.0;
    c1_f_expl_temp.fsize = 8.0;
    c1_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_f_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_FpgaMd5Hi - 1] = c1_f_expl_temp;
    c1_g_expl_temp.offset = 29.0;
    c1_g_expl_temp.fsize = 8.0;
    c1_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_g_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_FirmwareMd5Lo - 1] = c1_g_expl_temp;
    c1_h_expl_temp.offset = 37.0;
    c1_h_expl_temp.fsize = 8.0;
    c1_h_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_h_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_FirmwareMd5Hi - 1] = c1_h_expl_temp;
    break;

   case 4:
    c1_c_expl_temp.offset = 5.0;
    c1_c_expl_temp.fsize = 2.0;
    c1_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_c_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_Valid - 1] = c1_c_expl_temp;
    c1_d_expl_temp.offset = 7.0;
    c1_d_expl_temp.fsize = 2.0;
    c1_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_d_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_Gain - 1] = c1_d_expl_temp;
    c1_e_expl_temp.offset = 9.0;
    c1_e_expl_temp.fsize = 8.0;
    c1_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_e_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_CenterFreq - 1] = c1_e_expl_temp;
    c1_f_expl_temp.offset = 17.0;
    c1_f_expl_temp.fsize = 4.0;
    c1_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_f_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_Decimation - 1] = c1_f_expl_temp;
    c1_g_expl_temp.offset = 21.0;
    c1_g_expl_temp.fsize = 2.0;
    c1_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_g_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_ScaleI - 1] = c1_g_expl_temp;
    c1_h_expl_temp.offset = 23.0;
    c1_h_expl_temp.fsize = 2.0;
    c1_h_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_h_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_ScaleQ - 1] = c1_h_expl_temp;
    break;

   case 132:
    c1_c_expl_temp.offset = 5.0;
    c1_c_expl_temp.fsize = 2.0;
    c1_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_c_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_ConfigOk - 1] = c1_c_expl_temp;
    c1_d_expl_temp.offset = 7.0;
    c1_d_expl_temp.fsize = 2.0;
    c1_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_d_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_SpectrumInverted - 1] = c1_d_expl_temp;
    c1_e_expl_temp.offset = 9.0;
    c1_e_expl_temp.fsize = 8.0;
    c1_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_e_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_BasebandFreq - 1] = c1_e_expl_temp;
    c1_f_expl_temp.offset = 17.0;
    c1_f_expl_temp.fsize = 8.0;
    c1_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_f_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_DdcFreq - 1] = c1_f_expl_temp;
    c1_g_expl_temp.offset = 25.0;
    c1_g_expl_temp.fsize = 8.0;
    c1_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_g_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_ResidualFreq - 1] = c1_g_expl_temp;
    break;

   case 5:
    c1_c_expl_temp.offset = 5.0;
    c1_c_expl_temp.fsize = 2.0;
    c1_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_c_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_Valid - 1] = c1_c_expl_temp;
    c1_d_expl_temp.offset = 7.0;
    c1_d_expl_temp.fsize = 2.0;
    c1_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_d_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_Gain - 1] = c1_d_expl_temp;
    c1_e_expl_temp.offset = 9.0;
    c1_e_expl_temp.fsize = 8.0;
    c1_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_e_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_CenterFreq - 1] = c1_e_expl_temp;
    c1_f_expl_temp.offset = 17.0;
    c1_f_expl_temp.fsize = 4.0;
    c1_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_f_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_Interpolation - 1] = c1_f_expl_temp;
    c1_g_expl_temp.offset = 21.0;
    c1_g_expl_temp.fsize = 2.0;
    c1_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_g_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_ScaleI - 1] = c1_g_expl_temp;
    c1_h_expl_temp.offset = 23.0;
    c1_h_expl_temp.fsize = 2.0;
    c1_h_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_h_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_ScaleQ - 1] = c1_h_expl_temp;
    break;

   case 133:
    c1_c_expl_temp.offset = 5.0;
    c1_c_expl_temp.fsize = 2.0;
    c1_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_c_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_ConfigOk - 1] = c1_c_expl_temp;
    c1_d_expl_temp.offset = 7.0;
    c1_d_expl_temp.fsize = 2.0;
    c1_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_d_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_SpectrumInverted - 1] = c1_d_expl_temp;
    c1_e_expl_temp.offset = 9.0;
    c1_e_expl_temp.fsize = 8.0;
    c1_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_e_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_BasebandFreq - 1] = c1_e_expl_temp;
    c1_f_expl_temp.offset = 17.0;
    c1_f_expl_temp.fsize = 8.0;
    c1_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_f_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_DucFreq - 1] = c1_f_expl_temp;
    c1_g_expl_temp.offset = 25.0;
    c1_g_expl_temp.fsize = 8.0;
    c1_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_g_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_ResidualFreq - 1] = c1_g_expl_temp;
    break;

   case 6:
    c1_c_expl_temp.offset = 5.0;
    c1_c_expl_temp.fsize = 4.0;
    c1_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_c_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_ItemsPerFrame - 1] = c1_c_expl_temp;
    c1_d_expl_temp.offset = 9.0;
    c1_d_expl_temp.fsize = 4.0;
    c1_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_d_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_TimeInt - 1] = c1_d_expl_temp;
    c1_e_expl_temp.offset = 13.0;
    c1_e_expl_temp.fsize = 4.0;
    c1_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_e_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_TimeFrac - 1] = c1_e_expl_temp;
    break;

   case 137:
    c1_c_expl_temp.offset = 5.0;
    c1_c_expl_temp.fsize = 4.0;
    c1_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_c_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_TxDbId - 1] = c1_c_expl_temp;
    c1_d_expl_temp.offset = 9.0;
    c1_d_expl_temp.fsize = 8.0;
    c1_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_d_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_TxFreqMin - 1] = c1_d_expl_temp;
    c1_e_expl_temp.offset = 17.0;
    c1_e_expl_temp.fsize = 8.0;
    c1_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_e_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_TxFreqMax - 1] = c1_e_expl_temp;
    c1_f_expl_temp.offset = 25.0;
    c1_f_expl_temp.fsize = 2.0;
    c1_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_f_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_TxGainMin - 1] = c1_f_expl_temp;
    c1_g_expl_temp.offset = 27.0;
    c1_g_expl_temp.fsize = 2.0;
    c1_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_g_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_TxGainMax - 1] = c1_g_expl_temp;
    c1_h_expl_temp.offset = 29.0;
    c1_h_expl_temp.fsize = 2.0;
    c1_h_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_h_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_TxGainStepSize - 1] = c1_h_expl_temp;
    c1_i_expl_temp.offset = 31.0;
    c1_i_expl_temp.fsize = 2.0;
    c1_i_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_i_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_TxDbReserved - 1] = c1_i_expl_temp;
    c1_j_expl_temp.offset = 33.0;
    c1_j_expl_temp.fsize = 4.0;
    c1_j_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_j_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_RxDbId - 1] = c1_j_expl_temp;
    c1_k_expl_temp.offset = 37.0;
    c1_k_expl_temp.fsize = 8.0;
    c1_k_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_k_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_RxFreqMin - 1] = c1_k_expl_temp;
    c1_l_expl_temp.offset = 45.0;
    c1_l_expl_temp.fsize = 8.0;
    c1_l_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_l_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_RxFreqMax - 1] = c1_l_expl_temp;
    c1_m_expl_temp.offset = 53.0;
    c1_m_expl_temp.fsize = 2.0;
    c1_m_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_m_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_RxGainMin - 1] = c1_m_expl_temp;
    c1_n_expl_temp.offset = 55.0;
    c1_n_expl_temp.fsize = 2.0;
    c1_n_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_n_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_RxGainMax - 1] = c1_n_expl_temp;
    c1_o_expl_temp.offset = 57.0;
    c1_o_expl_temp.fsize = 2.0;
    c1_o_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_o_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_RxGainStepSize - 1] = c1_o_expl_temp;
    c1_p_expl_temp.offset = 59.0;
    c1_p_expl_temp.fsize = 2.0;
    c1_p_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_p_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_RxDbReserved - 1] = c1_p_expl_temp;
    break;

   case 14:
    c1_c_expl_temp.offset = 5.0;
    c1_c_expl_temp.fsize = 8.0;
    c1_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_c_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_FreqOffset - 1] = c1_c_expl_temp;
    break;

   case 13:
    c1_c_expl_temp.offset = 5.0;
    c1_c_expl_temp.fsize = 8.0;
    c1_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
      c1_c_expl_temp.bytes[c1_i13] = 0U;
    }

    c1_cmdDef[(int32_T)USRP2CmdFields_FreqOffset - 1] = c1_c_expl_temp;
    break;
  }
}

static void c1_USRP2RuntimeControlReplies(SFc1_commsdrhwInstanceStruct
  *chartInstance, uint8_T c1_pkt[255], uint16_T c1_pktLen, char_T
  c1_errStr_data[56], int32_T c1_errStr_sizes[2], real_T *c1_b_replyId)
{
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_replyCmd[18];
  int32_T c1_i14;
  static char_T c1_cv8[45] = { 'U', 'S', 'R', 'P', '2', ' ', 'p', 'a', 'c', 'k',
    'e', 't', ' ', 'r', 'e', 'c', 'e', 'i', 'v', 'e', 'd', ' ', 'w', 'i', 't',
    'h', 'o', 'u', 't', ' ', 'a', ' ', 'v', 'a', 'l', 'i', 'd', ' ', 'h', 'e',
    'a', 'd', 'e', 'r', '.' };

  real_T c1_parsedBytes;
  int32_T c1_fidx;
  boolean_T c1_exitg1;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_cf;
  real_T c1_val;
  int32_T c1_i15;
  int32_T c1_tmp_sizes;
  int32_T c1_loop_ub;
  int32_T c1_i16;
  int32_T c1_tmp_data[8];
  int32_T c1_b_tmp_data[8];
  int32_T c1_c_tmp_data[66];
  uint16_T c1_u10;
  static char_T c1_cv9[56] = { 'U', 'S', 'R', 'P', '2', ' ', 'p', 'a', 'c', 'k',
    'e', 't', ' ', 'r', 'e', 'c', 'e', 'i', 'v', 'e', 'd', ' ', 'w', 'i', 't',
    'h', ' ', 'a', 'n', ' ', 'i', 'n', 'c', 'o', 'r', 'r', 'e', 'c', 't', ' ',
    'n', 'u', 'm', 'b', 'e', 'r', ' ', 'o', 'f', ' ', 'b', 'y', 't', 'e', 's',
    '.' };

  char_T c1_cv10[40];
  static char_T c1_cv11[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  char_T c1_b_errStr_data[40];
  static char_T c1_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c1_u[23];
  const mxArray *c1_y = NULL;
  char_T c1_u_data[40];
  const mxArray *c1_b_y = NULL;
  char_T c1_b_u[23];
  const mxArray *c1_c_y = NULL;
  char_T c1_b_u_data[40];
  const mxArray *c1_d_y = NULL;
  boolean_T c1_guard3 = FALSE;
  boolean_T c1_guard4 = FALSE;
  char_T c1_c_u[23];
  const mxArray *c1_e_y = NULL;
  char_T c1_c_u_data[40];
  const mxArray *c1_f_y = NULL;
  boolean_T c1_ok;
  boolean_T c1_guard1 = FALSE;
  boolean_T c1_guard2 = FALSE;
  static char_T c1_cv12[41] = { 'B', 'o', 'a', 'r', 'd', ' ', 'r', 'e', 'p', 'o',
    'r', 't', 'e', 'd', ' ', 'a', ' ', 's', 't', 'a', 'r', 't', ' ', 's', 't',
    'r', 'e', 'a', 'm', 'i', 'n', 'g', ' ', 'f', 'a', 'i', 'l', 'u', 'r', 'e',
    '.' };

  static char_T c1_cv13[40] = { 'B', 'o', 'a', 'r', 'd', ' ', 'r', 'e', 'p', 'o',
    'r', 't', 'e', 'd', ' ', 'a', ' ', 's', 't', 'o', 'p', ' ', 's', 't', 'r',
    'e', 'a', 'm', 'i', 'n', 'g', ' ', 'f', 'a', 'i', 'l', 'u', 'r', 'e', '.' };

  static char_T c1_cv14[45] = { 'B', 'o', 'a', 'r', 'd', ' ', 'r', 'e', 'p', 'o',
    'r', 't', 'e', 'd', ' ', 'a', ' ', 'd', 'a', 'u', 'g', 'h', 't', 'e', 'r',
    'b', 'o', 'a', 'r', 'd', ' ', 'r', 'e', 's', 'e', 't', ' ', 'f', 'a', 'i',
    'l', 'u', 'r', 'e', '.' };

  static char_T c1_cv15[56] = { 'B', 'o', 'a', 'r', 'd', ' ', 'r', 'e', 'p', 'o',
    'r', 't', 'e', 'd', ' ', 'a', ' ', 'f', 'r', 'e', 'q', 'u', 'e', 'n', 'c',
    'y', ' ', 'o', 'f', 'f', 's', 'e', 't', ' ', 'c', 'o', 'n', 'f', 'i', 'g',
    'u', 'r', 'a', 't', 'i', 'o', 'n', ' ', 'f', 'a', 'i', 'l', 'u', 'r', 'e',
    '.' };

  static char_T c1_cv16[39] = { 'B', 'o', 'a', 'r', 'd', ' ', 'r', 'e', 'p', 'o',
    'r', 't', 'e', 'd', ' ', 'a', ' ', 'c', 'o', 'n', 'f', 'i', 'g', 'u', 'r',
    'a', 't', 'i', 'o', 'n', ' ', 'f', 'a', 'i', 'l', 'u', 'r', 'e', '.' };

  const mxArray *c1_g_y = NULL;
  char_T c1_d_u[23];
  const mxArray *c1_h_y = NULL;
  char_T c1_d_u_data[40];
  *c1_b_replyId = 255.0;
  c1_USRP2CmdDef(chartInstance, USRP2Opcodes_EOP, c1_replyCmd);
  c1_errStr_sizes[0] = 1;
  c1_errStr_sizes[1] = 0;
  if (c1_pktLen < 4) {
    c1_errStr_sizes[0] = 1;
    c1_errStr_sizes[1] = 45;
    for (c1_i14 = 0; c1_i14 < 45; c1_i14++) {
      c1_errStr_data[c1_i14] = c1_cv8[c1_i14];
    }
  } else {
    c1_b_USRP2CmdDef(chartInstance, c1_pkt[0], c1_replyCmd);
    c1_parsedBytes = 0.0;
    c1_fidx = 0;
    c1_exitg1 = 0U;
    while ((c1_exitg1 == 0U) && (c1_fidx + 1 <= 18)) {
      c1_cf = c1_replyCmd[c1_fidx];
      if (c1_replyCmd[c1_fidx].fsize == 0.0) {
        c1_exitg1 = 1U;
      } else {
        c1_val = (c1_replyCmd[c1_fidx].offset + c1_replyCmd[c1_fidx].fsize) -
          1.0;
        if (c1_replyCmd[c1_fidx].offset > c1_val) {
          c1_i14 = 1;
          c1_i15 = 0;
        } else {
          c1_i14 = sf_mex_lw_bounds_check((int32_T)c1_replyCmd[c1_fidx].offset,
            1, 255);
          c1_i15 = sf_mex_lw_bounds_check((int32_T)c1_val, 1, 255);
        }

        c1_tmp_sizes = (int32_T)c1_replyCmd[c1_fidx].fsize;
        c1_loop_ub = (int32_T)c1_replyCmd[c1_fidx].fsize - 1;
        for (c1_i16 = 0; c1_i16 <= c1_loop_ub; c1_i16++) {
          c1_tmp_data[c1_i16] = 1 + c1_i16;
        }

        c1_loop_ub = c1_tmp_sizes - 1;
        for (c1_i16 = 0; c1_i16 <= c1_loop_ub; c1_i16++) {
          c1_b_tmp_data[c1_i16] = c1_tmp_data[c1_i16];
        }

        sf_mex_lw_size_eq_check_1d(c1_tmp_sizes, (c1_i15 - c1_i14) + 1);
        c1_tmp_sizes = c1_i15 - c1_i14;
        c1_loop_ub = c1_i15 - c1_i14;
        for (c1_i15 = 0; c1_i15 <= c1_loop_ub; c1_i15++) {
          c1_c_tmp_data[c1_i15] = c1_i14 + c1_i15;
        }

        for (c1_i14 = 0; c1_i14 <= c1_tmp_sizes; c1_i14++) {
          c1_cf.bytes[c1_b_tmp_data[c1_i14] - 1] = c1_pkt[c1_c_tmp_data[c1_i14]
            - 1];
        }

        c1_replyCmd[c1_fidx] = c1_cf;
        c1_parsedBytes += c1_cf.fsize;
        c1_fidx++;
      }
    }

    if (c1_parsedBytes != (real_T)c1_pktLen) {
      c1_val = (real_T)c1_pktLen - c1_parsedBytes;
      c1_val = c1_val < 0.0 ? muDoubleScalarCeil(c1_val - 0.5) :
        muDoubleScalarFloor(c1_val + 0.5);
      if (c1_val < 65536.0) {
        if (c1_val >= 0.0) {
          c1_u10 = (uint16_T)c1_val;
        } else {
          c1_u10 = 0U;
        }
      } else if (c1_val >= 65536.0) {
        c1_u10 = MAX_uint16_T;
      } else {
        c1_u10 = 0U;
      }

      if ((c1_u10 != 4) || (c1_pkt[sf_mex_lw_bounds_check((int32_T)
            (c1_parsedBytes + 1.0), 1, 255) - 1] != 0) ||
          (c1_pkt[sf_mex_lw_bounds_check((int32_T)(c1_parsedBytes + 2.0), 1, 255)
           - 1] != 4) || (c1_pkt[sf_mex_lw_bounds_check((int32_T)(c1_parsedBytes
             + 3.0), 1, 255) - 1] != 0) || (c1_pkt[sf_mex_lw_bounds_check
           ((int32_T)(c1_parsedBytes + 4.0), 1, 255) - 1] != 0)) {
        c1_errStr_sizes[0] = 1;
        c1_errStr_sizes[1] = 56;
        for (c1_i14 = 0; c1_i14 < 56; c1_i14++) {
          c1_errStr_data[c1_i14] = c1_cv9[c1_i14];
        }
      }
    }
  }

  if (c1_errStr_sizes[1] == 0) {
    c1_fidx = 0;
    c1_parsedBytes = 0.0;
    if (c1_replyCmd[0].fsize == 0.0) {
      c1_cv10[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Opcode;
      for (c1_i14 = 0; c1_i14 < 39; c1_i14++) {
        c1_cv10[c1_i14 + 1] = c1_cv11[c1_i14];
      }

      c1_fidx = 40;
      for (c1_i14 = 0; c1_i14 < 40; c1_i14++) {
        c1_b_errStr_data[c1_i14] = c1_cv10[c1_i14];
      }

      for (c1_i14 = 0; c1_i14 < 23; c1_i14++) {
        c1_u[c1_i14] = c1_varargin_1[c1_i14];
      }

      c1_y = NULL;
      sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 23));
      for (c1_i14 = 0; c1_i14 < 40; c1_i14++) {
        c1_u_data[c1_i14] = c1_b_errStr_data[c1_i14];
      }

      c1_b_y = NULL;
      sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u_data, 10, 0U, 1U, 0U, 2, 1,
        40));
      sf_mex_call("error", 0U, 2U, 14, c1_y, 14, c1_b_y);
    } else {
      c1_parsedBytes = c1_USRP2UnpackFieldVal(chartInstance, c1_replyCmd
        [(int32_T)USRP2CmdFields_Opcode - 1].dtype, c1_replyCmd[0].bytes);
    }

    c1_errStr_sizes[0] = 1;
    c1_errStr_sizes[1] = c1_fidx;
    c1_loop_ub = c1_fidx - 1;
    for (c1_i14 = 0; c1_i14 <= c1_loop_ub; c1_i14++) {
      c1_errStr_data[c1_i14] = c1_b_errStr_data[c1_i14];
    }

    if (c1_fidx == 0) {
      c1_fidx = 0;
      *c1_b_replyId = 0.0;
      if (c1_replyCmd[2].fsize == 0.0) {
        c1_cv10[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_ReplyId;
        for (c1_i14 = 0; c1_i14 < 39; c1_i14++) {
          c1_cv10[c1_i14 + 1] = c1_cv11[c1_i14];
        }

        c1_fidx = 40;
        for (c1_i14 = 0; c1_i14 < 40; c1_i14++) {
          c1_b_errStr_data[c1_i14] = c1_cv10[c1_i14];
        }

        for (c1_i14 = 0; c1_i14 < 23; c1_i14++) {
          c1_b_u[c1_i14] = c1_varargin_1[c1_i14];
        }

        c1_c_y = NULL;
        sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1,
          23));
        for (c1_i14 = 0; c1_i14 < 40; c1_i14++) {
          c1_b_u_data[c1_i14] = c1_b_errStr_data[c1_i14];
        }

        c1_d_y = NULL;
        sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_b_u_data, 10, 0U, 1U, 0U, 2,
          1, 40));
        sf_mex_call("error", 0U, 2U, 14, c1_c_y, 14, c1_d_y);
      } else {
        *c1_b_replyId = c1_USRP2UnpackFieldVal(chartInstance, c1_replyCmd
          [(int32_T)USRP2CmdFields_ReplyId - 1].dtype, c1_replyCmd[2].bytes);
      }

      c1_errStr_sizes[0] = 1;
      c1_errStr_sizes[1] = c1_fidx;
      c1_loop_ub = c1_fidx - 1;
      for (c1_i14 = 0; c1_i14 <= c1_loop_ub; c1_i14++) {
        c1_errStr_data[c1_i14] = c1_b_errStr_data[c1_i14];
      }

      if (c1_fidx == 0) {
        c1_guard3 = FALSE;
        c1_guard4 = FALSE;
        switch ((int32_T)c1_parsedBytes) {
         case 129:
          c1_guard3 = TRUE;
          break;

         case 137:
          c1_guard3 = TRUE;
          break;

         case 132:
          c1_guard4 = TRUE;
          break;

         case 133:
          c1_guard4 = TRUE;
          break;

         default:
          c1_val = 0.0;
          if (c1_replyCmd[3].fsize == 0.0) {
            for (c1_i14 = 0; c1_i14 < 23; c1_i14++) {
              c1_d_u[c1_i14] = c1_varargin_1[c1_i14];
            }

            c1_g_y = NULL;
            sf_mex_assign(&c1_g_y, sf_mex_create("y", c1_d_u, 10, 0U, 1U, 0U, 2,
              1, 23));
            c1_cv10[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Ok;
            for (c1_i14 = 0; c1_i14 < 39; c1_i14++) {
              c1_cv10[c1_i14 + 1] = c1_cv11[c1_i14];
            }

            for (c1_i14 = 0; c1_i14 < 40; c1_i14++) {
              c1_d_u_data[c1_i14] = c1_cv10[c1_i14];
            }

            c1_h_y = NULL;
            sf_mex_assign(&c1_h_y, sf_mex_create("y", c1_d_u_data, 10, 0U, 1U,
              0U, 2, 1, 40));
            sf_mex_call("error", 0U, 2U, 14, c1_g_y, 14, c1_h_y);
          } else {
            c1_val = c1_USRP2UnpackFieldVal(chartInstance, c1_replyCmd[(int32_T)
              USRP2CmdFields_Ok - 1].dtype, c1_replyCmd[3].bytes);
          }

          c1_ok = (c1_val != 0.0);
          break;
        }

        if (c1_guard4 == TRUE) {
          c1_val = 0.0;
          if (c1_replyCmd[4].fsize == 0.0) {
            for (c1_i14 = 0; c1_i14 < 23; c1_i14++) {
              c1_c_u[c1_i14] = c1_varargin_1[c1_i14];
            }

            c1_e_y = NULL;
            sf_mex_assign(&c1_e_y, sf_mex_create("y", c1_c_u, 10, 0U, 1U, 0U, 2,
              1, 23));
            c1_cv10[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_ConfigOk;
            for (c1_i14 = 0; c1_i14 < 39; c1_i14++) {
              c1_cv10[c1_i14 + 1] = c1_cv11[c1_i14];
            }

            for (c1_i14 = 0; c1_i14 < 40; c1_i14++) {
              c1_c_u_data[c1_i14] = c1_cv10[c1_i14];
            }

            c1_f_y = NULL;
            sf_mex_assign(&c1_f_y, sf_mex_create("y", c1_c_u_data, 10, 0U, 1U,
              0U, 2, 1, 40));
            sf_mex_call("error", 0U, 2U, 14, c1_e_y, 14, c1_f_y);
          } else {
            c1_val = c1_USRP2UnpackFieldVal(chartInstance, c1_replyCmd[(int32_T)
              USRP2CmdFields_ConfigOk - 1].dtype, c1_replyCmd[4].bytes);
          }

          c1_ok = (c1_val != 0.0);
        }

        if (c1_guard3 == TRUE) {
          c1_ok = TRUE;
        }

        if (!c1_ok) {
          c1_guard1 = FALSE;
          c1_guard2 = FALSE;
          switch ((int32_T)c1_parsedBytes) {
           case 132:
            c1_guard1 = TRUE;
            break;

           case 133:
            c1_guard1 = TRUE;
            break;

           case 134:
            c1_errStr_sizes[0] = 1;
            c1_errStr_sizes[1] = 41;
            for (c1_i14 = 0; c1_i14 < 41; c1_i14++) {
              c1_errStr_data[c1_i14] = c1_cv12[c1_i14];
            }
            break;

           case 135:
            c1_errStr_sizes[0] = 1;
            c1_errStr_sizes[1] = 40;
            for (c1_i14 = 0; c1_i14 < 40; c1_i14++) {
              c1_errStr_data[c1_i14] = c1_cv13[c1_i14];
            }
            break;

           case 14:
            c1_guard2 = TRUE;
            break;

           case 13:
            c1_guard2 = TRUE;
            break;

           case 143:
            c1_errStr_sizes[0] = 1;
            c1_errStr_sizes[1] = 45;
            for (c1_i14 = 0; c1_i14 < 45; c1_i14++) {
              c1_errStr_data[c1_i14] = c1_cv14[c1_i14];
            }
            break;
          }

          if (c1_guard2 == TRUE) {
            c1_errStr_sizes[0] = 1;
            c1_errStr_sizes[1] = 56;
            for (c1_i14 = 0; c1_i14 < 56; c1_i14++) {
              c1_errStr_data[c1_i14] = c1_cv15[c1_i14];
            }
          }

          if (c1_guard1 == TRUE) {
            c1_errStr_sizes[0] = 1;
            c1_errStr_sizes[1] = 39;
            for (c1_i14 = 0; c1_i14 < 39; c1_i14++) {
              c1_errStr_data[c1_i14] = c1_cv16[c1_i14];
            }
          }
        }
      }
    }
  }
}

static real_T c1_USRP2UnpackFieldVal(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_USRP2FieldDtypes c1_dtype, uint8_T c1_bytes[16])
{
  real_T c1_val;
  int32_T c1_j;
  uint8_T c1_x[2];
  uint16_T c1_u16;
  uint8_T c1_b_x[4];
  uint32_T c1_u32;
  real_T c1_y;
  const mxArray *c1_b_y = NULL;
  char_T c1_u[32];
  const mxArray *c1_c_y = NULL;
  char_T c1_b_u[37];
  static char_T c1_varargin_1[32] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'U', 'n', 'k', 'n', 'o', 'w', 'n', 'F',
    'i', 'e', 'l', 'd', 'D', 't', 'y', 'p', 'e' };

  static char_T c1_varargin_2[37] = { 'U', 'n', 'k', 'n', 'o', 'w', 'n', ' ',
    'U', 'S', 'R', 'P', '2', ' ', 'd', 'a', 't', 'a', 't', 'y', 'p', 'e', ' ',
    's', 'p', 'e', 'c', 'i', 'f', 'i', 'c', 'a', 't', 'i', 'o', 'n', '.' };

  switch (c1_dtype) {
   case USRP2FieldDtypes_usrp2_uint8_T:
    c1_val = (real_T)c1_bytes[0];
    break;

   case USRP2FieldDtypes_usrp2_uint16_T:
    for (c1_j = 0; c1_j < 2; c1_j++) {
      c1_x[c1_j] = c1_bytes[1 - c1_j];
    }

    memcpy((void *)&c1_u16, (void *)&c1_x[0], 2U);
    c1_val = (real_T)c1_u16;
    break;

   case USRP2FieldDtypes_usrp2_uint32_T:
    for (c1_j = 0; c1_j < 4; c1_j++) {
      c1_b_x[c1_j] = c1_bytes[3 - c1_j];
    }

    memcpy((void *)&c1_u32, (void *)&c1_b_x[0], 4U);
    c1_val = (real_T)c1_u32;
    break;

   case USRP2FieldDtypes_usrp2_sfix16_En7_T:
    c1_y = 0.0;
    for (c1_j = 1; c1_j > -1; c1_j += -1) {
      c1_y = c1_y * 256.0 + (real_T)c1_bytes[1 - c1_j];
    }

    c1_val = c1_y / 128.0;
    break;

   case USRP2FieldDtypes_usrp2_sfix64_En20_T:
    c1_y = 0.0;
    for (c1_j = 7; c1_j > -1; c1_j += -1) {
      c1_y = c1_y * 256.0 + (real_T)c1_bytes[7 - c1_j];
    }

    c1_val = c1_y / 1.048576E+6;
    break;

   default:
    c1_val = 1.0;
    for (c1_j = 0; c1_j < 32; c1_j++) {
      c1_u[c1_j] = c1_varargin_1[c1_j];
    }

    c1_b_y = NULL;
    sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 32));
    for (c1_j = 0; c1_j < 37; c1_j++) {
      c1_b_u[c1_j] = c1_varargin_2[c1_j];
    }

    c1_c_y = NULL;
    sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1, 37));
    sf_mex_call("error", 0U, 2U, 14, c1_b_y, 14, c1_c_y);
    break;
  }

  return c1_val;
}

static void c1_d_USRP2RuntimeControl(SFc1_commsdrhwInstanceStruct *chartInstance,
  real_T c1_varargin_3, real_T *c1_pktLength, uint8_T c1_pkt[255], uint8_T
  *c1_b_replyId, real_T *c1_varargout_1_ValidMask, real_T *c1_varargout_1_Fc,
  real_T *c1_varargout_1_Gain, real_T *c1_varargout_1_DecimInterp, real_T
  *c1_varargout_1_ScaleI, real_T *c1_varargout_1_ScaleQ)
{
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_cmdDef[18];
  int32_T c1_i17;
  static char_T c1_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c1_u[23];
  const mxArray *c1_y = NULL;
  char_T c1_b_u[40];
  static char_T c1_cv17[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  const mxArray *c1_b_y = NULL;
  char_T c1_c_u[23];
  const mxArray *c1_c_y = NULL;
  char_T c1_d_u[40];
  const mxArray *c1_d_y = NULL;
  chartInstance->c1_lastCF_not_empty = TRUE;
  chartInstance->c1_lastG_not_empty = TRUE;
  chartInstance->c1_lastDI_not_empty = TRUE;
  chartInstance->c1_lastI_not_empty = TRUE;
  chartInstance->c1_lastQ_not_empty = TRUE;
  c1_USRP2CmdDef(chartInstance, USRP2Opcodes_ConfigTx, c1_cmdDef);
  *c1_varargout_1_ValidMask = 0.0;
  *c1_varargout_1_Gain = chartInstance->c1_lastG;
  *c1_varargout_1_DecimInterp = chartInstance->c1_lastDI;
  *c1_varargout_1_ScaleI = chartInstance->c1_lastI;
  *c1_varargout_1_ScaleQ = chartInstance->c1_lastQ;
  *c1_varargout_1_Fc = c1_varargin_3;
  if (c1_varargin_3 != chartInstance->c1_lastCF) {
    *c1_varargout_1_ValidMask = 2.0;
    if (c1_cmdDef[sf_mex_lw_bounds_check((int32_T)USRP2CmdFields_CenterFreq, 1,
         18) - 1].fsize == 0.0) {
      for (c1_i17 = 0; c1_i17 < 23; c1_i17++) {
        c1_u[c1_i17] = c1_varargin_1[c1_i17];
      }

      c1_y = NULL;
      sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 23));
      c1_b_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_CenterFreq;
      for (c1_i17 = 0; c1_i17 < 39; c1_i17++) {
        c1_b_u[c1_i17 + 1] = c1_cv17[c1_i17];
      }

      c1_b_y = NULL;
      sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
      sf_mex_call("error", 0U, 2U, 14, c1_y, 14, c1_b_y);
    } else {
      c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[(int32_T)
                           USRP2CmdFields_CenterFreq - 1].dtype, c1_varargin_3,
                           c1_cmdDef[sf_mex_lw_bounds_check((int32_T)
        USRP2CmdFields_CenterFreq, 1, 18) - 1].bytes);
    }
  }

  if (*c1_varargout_1_ValidMask != 0.0) {
    if (c1_cmdDef[sf_mex_lw_bounds_check((int32_T)USRP2CmdFields_Valid, 1, 18) -
        1].fsize == 0.0) {
      for (c1_i17 = 0; c1_i17 < 23; c1_i17++) {
        c1_c_u[c1_i17] = c1_varargin_1[c1_i17];
      }

      c1_c_y = NULL;
      sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_c_u, 10, 0U, 1U, 0U, 2, 1, 23));
      c1_d_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Valid;
      for (c1_i17 = 0; c1_i17 < 39; c1_i17++) {
        c1_d_u[c1_i17 + 1] = c1_cv17[c1_i17];
      }

      c1_d_y = NULL;
      sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_d_u, 10, 0U, 1U, 0U, 2, 1, 40));
      sf_mex_call("error", 0U, 2U, 14, c1_c_y, 14, c1_d_y);
    } else {
      c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[(int32_T)
                           USRP2CmdFields_Valid - 1].dtype,
                           *c1_varargout_1_ValidMask,
                           c1_cmdDef[sf_mex_lw_bounds_check((int32_T)
        USRP2CmdFields_Valid, 1, 18) - 1].bytes);
    }

    c1_USRP2Cmd2Pkt(chartInstance, c1_cmdDef, c1_pkt, c1_pktLength);
  } else {
    *c1_pktLength = 0.0;
    for (c1_i17 = 0; c1_i17 < 255; c1_i17++) {
      c1_pkt[c1_i17] = 0U;
    }
  }

  chartInstance->c1_lastCF = c1_varargin_3;
  chartInstance->c1_lastG = *c1_varargout_1_Gain;
  chartInstance->c1_lastDI = *c1_varargout_1_DecimInterp;
  chartInstance->c1_lastI = *c1_varargout_1_ScaleI;
  chartInstance->c1_lastQ = *c1_varargout_1_ScaleQ;
  *c1_b_replyId = c1_pkt[2];
}

static void c1_e_USRP2RuntimeControl(SFc1_commsdrhwInstanceStruct *chartInstance,
  real_T c1_varargin_3, real_T *c1_pktLength, uint8_T c1_pkt[255], uint8_T
  *c1_b_replyId, real_T *c1_varargout_1_ValidMask, real_T *c1_varargout_1_Fc,
  real_T *c1_varargout_1_Gain, real_T *c1_varargout_1_DecimInterp, real_T
  *c1_varargout_1_ScaleI, real_T *c1_varargout_1_ScaleQ)
{
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_cmdDef[18];
  int32_T c1_i18;
  static char_T c1_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c1_u[23];
  const mxArray *c1_y = NULL;
  char_T c1_b_u[40];
  static char_T c1_cv18[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  const mxArray *c1_b_y = NULL;
  char_T c1_c_u[23];
  const mxArray *c1_c_y = NULL;
  char_T c1_d_u[40];
  const mxArray *c1_d_y = NULL;
  chartInstance->c1_lastCF_not_empty = TRUE;
  chartInstance->c1_lastG_not_empty = TRUE;
  chartInstance->c1_lastDI_not_empty = TRUE;
  chartInstance->c1_lastI_not_empty = TRUE;
  chartInstance->c1_lastQ_not_empty = TRUE;
  c1_USRP2CmdDef(chartInstance, USRP2Opcodes_ConfigTx, c1_cmdDef);
  *c1_varargout_1_ValidMask = 0.0;
  *c1_varargout_1_Fc = chartInstance->c1_lastCF;
  *c1_varargout_1_DecimInterp = chartInstance->c1_lastDI;
  *c1_varargout_1_ScaleI = chartInstance->c1_lastI;
  *c1_varargout_1_ScaleQ = chartInstance->c1_lastQ;
  *c1_varargout_1_Gain = c1_varargin_3;
  if (c1_varargin_3 != chartInstance->c1_lastG) {
    *c1_varargout_1_ValidMask = 1.0;
    if (c1_cmdDef[sf_mex_lw_bounds_check((int32_T)USRP2CmdFields_Gain, 1, 18) -
        1].fsize == 0.0) {
      for (c1_i18 = 0; c1_i18 < 23; c1_i18++) {
        c1_u[c1_i18] = c1_varargin_1[c1_i18];
      }

      c1_y = NULL;
      sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 23));
      c1_b_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Gain;
      for (c1_i18 = 0; c1_i18 < 39; c1_i18++) {
        c1_b_u[c1_i18 + 1] = c1_cv18[c1_i18];
      }

      c1_b_y = NULL;
      sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
      sf_mex_call("error", 0U, 2U, 14, c1_y, 14, c1_b_y);
    } else {
      c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[(int32_T)USRP2CmdFields_Gain
                           - 1].dtype, c1_varargin_3,
                           c1_cmdDef[sf_mex_lw_bounds_check((int32_T)
        USRP2CmdFields_Gain, 1, 18) - 1].bytes);
    }
  }

  if (*c1_varargout_1_ValidMask != 0.0) {
    if (c1_cmdDef[sf_mex_lw_bounds_check((int32_T)USRP2CmdFields_Valid, 1, 18) -
        1].fsize == 0.0) {
      for (c1_i18 = 0; c1_i18 < 23; c1_i18++) {
        c1_c_u[c1_i18] = c1_varargin_1[c1_i18];
      }

      c1_c_y = NULL;
      sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_c_u, 10, 0U, 1U, 0U, 2, 1, 23));
      c1_d_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Valid;
      for (c1_i18 = 0; c1_i18 < 39; c1_i18++) {
        c1_d_u[c1_i18 + 1] = c1_cv18[c1_i18];
      }

      c1_d_y = NULL;
      sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_d_u, 10, 0U, 1U, 0U, 2, 1, 40));
      sf_mex_call("error", 0U, 2U, 14, c1_c_y, 14, c1_d_y);
    } else {
      c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[(int32_T)
                           USRP2CmdFields_Valid - 1].dtype, 1.0,
                           c1_cmdDef[sf_mex_lw_bounds_check((int32_T)
        USRP2CmdFields_Valid, 1, 18) - 1].bytes);
    }

    c1_USRP2Cmd2Pkt(chartInstance, c1_cmdDef, c1_pkt, c1_pktLength);
  } else {
    *c1_pktLength = 0.0;
    for (c1_i18 = 0; c1_i18 < 255; c1_i18++) {
      c1_pkt[c1_i18] = 0U;
    }
  }

  chartInstance->c1_lastCF = *c1_varargout_1_Fc;
  chartInstance->c1_lastG = c1_varargin_3;
  chartInstance->c1_lastDI = *c1_varargout_1_DecimInterp;
  chartInstance->c1_lastI = *c1_varargout_1_ScaleI;
  chartInstance->c1_lastQ = *c1_varargout_1_ScaleQ;
  *c1_b_replyId = c1_pkt[2];
}

static void c1_f_USRP2RuntimeControl(SFc1_commsdrhwInstanceStruct *chartInstance,
  real_T c1_varargin_3, real_T *c1_pktLength, uint8_T c1_pkt[255], uint8_T
  *c1_b_replyId, real_T *c1_varargout_1_ValidMask, real_T *c1_varargout_1_Fc,
  real_T *c1_varargout_1_Gain, real_T *c1_varargout_1_DecimInterp, real_T
  *c1_varargout_1_ScaleI, real_T *c1_varargout_1_ScaleQ)
{
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_cmdDef[18];
  int32_T c1_i19;
  static char_T c1_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c1_u[23];
  const mxArray *c1_y = NULL;
  char_T c1_b_u[40];
  static char_T c1_cv19[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  const mxArray *c1_b_y = NULL;
  char_T c1_c_u[23];
  const mxArray *c1_c_y = NULL;
  char_T c1_d_u[40];
  const mxArray *c1_d_y = NULL;
  chartInstance->c1_lastCF_not_empty = TRUE;
  chartInstance->c1_lastG_not_empty = TRUE;
  chartInstance->c1_lastDI_not_empty = TRUE;
  chartInstance->c1_lastI_not_empty = TRUE;
  chartInstance->c1_lastQ_not_empty = TRUE;
  c1_USRP2CmdDef(chartInstance, USRP2Opcodes_ConfigTx, c1_cmdDef);
  *c1_varargout_1_ValidMask = 0.0;
  *c1_varargout_1_Fc = chartInstance->c1_lastCF;
  *c1_varargout_1_Gain = chartInstance->c1_lastG;
  *c1_varargout_1_ScaleI = chartInstance->c1_lastI;
  *c1_varargout_1_ScaleQ = chartInstance->c1_lastQ;
  *c1_varargout_1_DecimInterp = c1_varargin_3;
  if (c1_varargin_3 != chartInstance->c1_lastDI) {
    *c1_varargout_1_ValidMask = 4.0;
    if (c1_cmdDef[sf_mex_lw_bounds_check((int32_T)USRP2CmdFields_Decimation, 1,
         18) - 1].fsize == 0.0) {
      for (c1_i19 = 0; c1_i19 < 23; c1_i19++) {
        c1_u[c1_i19] = c1_varargin_1[c1_i19];
      }

      c1_y = NULL;
      sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 23));
      c1_b_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Decimation;
      for (c1_i19 = 0; c1_i19 < 39; c1_i19++) {
        c1_b_u[c1_i19 + 1] = c1_cv19[c1_i19];
      }

      c1_b_y = NULL;
      sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
      sf_mex_call("error", 0U, 2U, 14, c1_y, 14, c1_b_y);
    } else {
      c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[(int32_T)
                           USRP2CmdFields_Decimation - 1].dtype, c1_varargin_3,
                           c1_cmdDef[sf_mex_lw_bounds_check((int32_T)
        USRP2CmdFields_Decimation, 1, 18) - 1].bytes);
    }
  }

  if (*c1_varargout_1_ValidMask != 0.0) {
    if (c1_cmdDef[sf_mex_lw_bounds_check((int32_T)USRP2CmdFields_Valid, 1, 18) -
        1].fsize == 0.0) {
      for (c1_i19 = 0; c1_i19 < 23; c1_i19++) {
        c1_c_u[c1_i19] = c1_varargin_1[c1_i19];
      }

      c1_c_y = NULL;
      sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_c_u, 10, 0U, 1U, 0U, 2, 1, 23));
      c1_d_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Valid;
      for (c1_i19 = 0; c1_i19 < 39; c1_i19++) {
        c1_d_u[c1_i19 + 1] = c1_cv19[c1_i19];
      }

      c1_d_y = NULL;
      sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_d_u, 10, 0U, 1U, 0U, 2, 1, 40));
      sf_mex_call("error", 0U, 2U, 14, c1_c_y, 14, c1_d_y);
    } else {
      c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[(int32_T)
                           USRP2CmdFields_Valid - 1].dtype,
                           *c1_varargout_1_ValidMask,
                           c1_cmdDef[sf_mex_lw_bounds_check((int32_T)
        USRP2CmdFields_Valid, 1, 18) - 1].bytes);
    }

    c1_USRP2Cmd2Pkt(chartInstance, c1_cmdDef, c1_pkt, c1_pktLength);
  } else {
    *c1_pktLength = 0.0;
    for (c1_i19 = 0; c1_i19 < 255; c1_i19++) {
      c1_pkt[c1_i19] = 0U;
    }
  }

  chartInstance->c1_lastCF = *c1_varargout_1_Fc;
  chartInstance->c1_lastG = *c1_varargout_1_Gain;
  chartInstance->c1_lastDI = c1_varargin_3;
  chartInstance->c1_lastI = *c1_varargout_1_ScaleI;
  chartInstance->c1_lastQ = *c1_varargout_1_ScaleQ;
  *c1_b_replyId = c1_pkt[2];
}

static uint16_T c1_VRTGetDataStream(SFc1_commsdrhwInstanceStruct *chartInstance)
{
  return 359U;
}

static uint8_T c1_b_VRTGetDataStream(SFc1_commsdrhwInstanceStruct *chartInstance)
{
  return 0U;
}

static void c1_Update(SFc1_commsdrhwInstanceStruct *chartInstance, uint8_T
                      c1_U0[255], real_T c1_U1)
{
  char_T *c1_sErr;

  /* System object Update function: dsp.UDPSender */
  c1_sErr = GetErrorBuffer(&chartInstance->c1_c_NetworkLib[0U]);
  LibUpdate_Network(&chartInstance->c1_c_NetworkLib[0U], &c1_U0[0], (int32_T)
                    c1_U1);
  if (*c1_sErr != 0) {
    PrintError(c1_sErr);
  }
}

static void c1_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_packet, const char_T *c1_identifier, uint8_T c1_y_data[8000],
  int32_T c1_y_sizes[2])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_packet), &c1_thisId,
                        c1_y_data, c1_y_sizes);
  sf_mex_destroy(&c1_packet);
}

static void c1_b_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint8_T c1_y_data
  [8000], int32_T c1_y_sizes[2])
{
  int32_T c1_i20;
  static int16_T c1_iv1[2] = { 8000, 1 };

  uint32_T c1_uv3[2];
  static boolean_T c1_bv0[2] = { TRUE, FALSE };

  boolean_T c1_bv1[2];
  int32_T c1_tmp_sizes[2];
  uint8_T c1_tmp_data[8000];
  int32_T c1_loop_ub;
  for (c1_i20 = 0; c1_i20 < 2; c1_i20++) {
    c1_uv3[c1_i20] = (uint32_T)c1_iv1[c1_i20];
  }

  for (c1_i20 = 0; c1_i20 < 2; c1_i20++) {
    c1_bv1[c1_i20] = c1_bv0[c1_i20];
  }

  sf_mex_import_vs(c1_parentId, sf_mex_dup(c1_u), c1_tmp_data, 1, 3, 0U, 1, 0U,
                   2, c1_bv1, c1_uv3, c1_tmp_sizes);
  c1_y_sizes[0] = c1_tmp_sizes[0];
  c1_y_sizes[1] = 1;
  c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
  for (c1_i20 = 0; c1_i20 <= c1_loop_ub; c1_i20++) {
    c1_y_data[c1_i20] = c1_tmp_data[c1_i20];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_c_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_d_NetworkLib, const char_T *c1_identifier, real_T c1_y[137])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_d_NetworkLib), &c1_thisId,
                        c1_y);
  sf_mex_destroy(&c1_d_NetworkLib);
}

static void c1_d_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[137])
{
  real_T c1_dv2[137];
  int32_T c1_i21;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv2, 1, 0, 0U, 1, 0U, 1, 137);
  for (c1_i21 = 0; c1_i21 < 137; c1_i21++) {
    c1_y[c1_i21] = c1_dv2[c1_i21];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_e_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_d_NetworkLib, const char_T *c1_identifier, real_T c1_y[137])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_d_NetworkLib), &c1_thisId,
                        c1_y);
  sf_mex_destroy(&c1_d_NetworkLib);
}

static void c1_f_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[137])
{
  real_T c1_dv3[137];
  int32_T c1_i22;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv3, 1, 0, 0U, 1, 0U, 1, 137);
  for (c1_i22 = 0; c1_i22 < 137; c1_i22++) {
    c1_y[c1_i22] = c1_dv3[c1_i22];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_g_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_d_NetworkLib, const char_T *c1_identifier, real_T c1_y[137])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_d_NetworkLib), &c1_thisId,
                        c1_y);
  sf_mex_destroy(&c1_d_NetworkLib);
}

static void c1_h_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[137])
{
  real_T c1_dv4[137];
  int32_T c1_i23;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv4, 1, 0, 0U, 1, 0U, 1, 137);
  for (c1_i23 = 0; c1_i23 < 137; c1_i23++) {
    c1_y[c1_i23] = c1_dv4[c1_i23];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_i_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_b_Tx, const char_T *c1_identifier, char_T c1_y_datatype[5],
  uint8_T *c1_y_hasTrailer, uint32_T *c1_y_trailer, uint8_T
  *c1_y_stream_hasStreamID, uint32_T *c1_y_stream_streamID, uint8_T
  *c1_y_stream_hasClassID, uint32_T c1_y_stream_classID[2], uint8_T
  *c1_y_stream_packetType, uint8_T *c1_y_stream_TSI, uint8_T *c1_y_stream_TSF,
  uint8_T *c1_y_stream_packetCount, uint16_T *c1_y_stream_packetSize)
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_Tx), &c1_thisId,
                        c1_y_datatype, c1_y_hasTrailer, c1_y_trailer,
                        c1_y_stream_hasStreamID, c1_y_stream_streamID,
                        c1_y_stream_hasClassID, c1_y_stream_classID,
                        c1_y_stream_packetType, c1_y_stream_TSI, c1_y_stream_TSF,
                        c1_y_stream_packetCount, c1_y_stream_packetSize);
  sf_mex_destroy(&c1_b_Tx);
}

static void c1_j_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, char_T
  c1_y_datatype[5], uint8_T *c1_y_hasTrailer, uint32_T *c1_y_trailer, uint8_T
  *c1_y_stream_hasStreamID, uint32_T *c1_y_stream_streamID, uint8_T
  *c1_y_stream_hasClassID, uint32_T c1_y_stream_classID[2], uint8_T
  *c1_y_stream_packetType, uint8_T *c1_y_stream_TSI, uint8_T *c1_y_stream_TSF,
  uint8_T *c1_y_stream_packetCount, uint16_T *c1_y_stream_packetSize)
{
  emlrtMsgIdentifier c1_thisId;
  static const char * c1_fieldNames[4] = { "datatype", "hasTrailer", "trailer",
    "stream" };

  c1_thisId.fParent = c1_parentId;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_Tx_not_empty = FALSE;
  } else {
    chartInstance->c1_Tx_not_empty = TRUE;
    sf_mex_check_struct(c1_parentId, c1_u, 4, c1_fieldNames, 0U, 0);
    c1_thisId.fIdentifier = "datatype";
    c1_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u,
      "datatype", "datatype", 0)), &c1_thisId, c1_y_datatype);
    c1_thisId.fIdentifier = "hasTrailer";
    *c1_y_hasTrailer = c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup
      (sf_mex_getfield(c1_u, "hasTrailer", "hasTrailer", 0)), &c1_thisId);
    c1_thisId.fIdentifier = "trailer";
    *c1_y_trailer = c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup
      (sf_mex_getfield(c1_u, "trailer", "trailer", 0)), &c1_thisId);
    c1_thisId.fIdentifier = "stream";
    c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u,
      "stream", "stream", 0)), &c1_thisId, c1_y_stream_hasStreamID,
                          c1_y_stream_streamID, c1_y_stream_hasClassID,
                          c1_y_stream_classID, c1_y_stream_packetType,
                          c1_y_stream_TSI, c1_y_stream_TSF,
                          c1_y_stream_packetCount, c1_y_stream_packetSize);
  }

  sf_mex_destroy(&c1_u);
}

static void c1_k_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y[5])
{
  char_T c1_cv20[5];
  int32_T c1_i24;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_cv20, 1, 10, 0U, 1, 0U, 2, 1,
                5);
  for (c1_i24 = 0; c1_i24 < 5; c1_i24++) {
    c1_y[c1_i24] = c1_cv20[c1_i24];
  }

  sf_mex_destroy(&c1_u);
}

static uint8_T c1_l_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u11;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u11, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u11;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static uint32_T c1_m_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint32_T c1_y;
  uint32_T c1_u12;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u12, 1, 7, 0U, 0, 0U, 0);
  c1_y = c1_u12;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_n_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint8_T
  *c1_y_hasStreamID, uint32_T *c1_y_streamID, uint8_T *c1_y_hasClassID, uint32_T
  c1_y_classID[2], uint8_T *c1_y_packetType, uint8_T *c1_y_TSI, uint8_T
  *c1_y_TSF, uint8_T *c1_y_packetCount, uint16_T *c1_y_packetSize)
{
  emlrtMsgIdentifier c1_thisId;
  static const char * c1_fieldNames[9] = { "hasStreamID", "streamID",
    "hasClassID", "classID", "packetType", "TSI", "TSF", "packetCount",
    "packetSize" };

  c1_thisId.fParent = c1_parentId;
  sf_mex_check_struct(c1_parentId, c1_u, 9, c1_fieldNames, 0U, 0);
  c1_thisId.fIdentifier = "hasStreamID";
  *c1_y_hasStreamID = c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c1_u, "hasStreamID", "hasStreamID", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "streamID";
  *c1_y_streamID = c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c1_u, "streamID", "streamID", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "hasClassID";
  *c1_y_hasClassID = c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c1_u, "hasClassID", "hasClassID", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "classID";
  c1_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_u,
    "classID", "classID", 0)), &c1_thisId, c1_y_classID);
  c1_thisId.fIdentifier = "packetType";
  *c1_y_packetType = c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c1_u, "packetType", "packetType", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "TSI";
  *c1_y_TSI = c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "TSI", "TSI", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "TSF";
  *c1_y_TSF = c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_u, "TSF", "TSF", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "packetCount";
  *c1_y_packetCount = c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c1_u, "packetCount", "packetCount", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "packetSize";
  *c1_y_packetSize = c1_p_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c1_u, "packetSize", "packetSize", 0)), &c1_thisId);
  sf_mex_destroy(&c1_u);
}

static void c1_o_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint32_T c1_y[2])
{
  uint32_T c1_uv4[2];
  int32_T c1_i25;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_uv4, 1, 7, 0U, 1, 0U, 2, 1, 2);
  for (c1_i25 = 0; c1_i25 < 2; c1_i25++) {
    c1_y[c1_i25] = c1_uv4[c1_i25];
  }

  sf_mex_destroy(&c1_u);
}

static uint16_T c1_p_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint16_T c1_y;
  uint16_T c1_u13;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u13, 1, 5, 0U, 0, 0U, 0);
  c1_y = c1_u13;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_q_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_c_Y0, const char_T *c1_identifier, uint8_T c1_y[255])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_c_Y0), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_c_Y0);
}

static void c1_r_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint8_T c1_y[255])
{
  uint8_T c1_uv5[255];
  int32_T c1_i26;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_uv5, 1, 3, 0U, 1, 0U, 2, 255,
                1);
  for (c1_i26 = 0; c1_i26 < 255; c1_i26++) {
    c1_y[c1_i26] = c1_uv5[c1_i26];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_s_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_c_Y0, const char_T *c1_identifier, uint8_T c1_y[255])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_t_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_c_Y0), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_c_Y0);
}

static void c1_t_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint8_T c1_y[255])
{
  uint8_T c1_uv6[255];
  int32_T c1_i27;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_uv6, 1, 3, 0U, 1, 0U, 2, 255,
                1);
  for (c1_i27 = 0; c1_i27 < 255; c1_i27++) {
    c1_y[c1_i27] = c1_uv6[c1_i27];
  }

  sf_mex_destroy(&c1_u);
}

static uint16_T c1_u_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c1_c_Y1, const char_T *c1_identifier)
{
  uint16_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_v_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_c_Y1), &c1_thisId);
  sf_mex_destroy(&c1_c_Y1);
  return c1_y;
}

static uint16_T c1_v_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint16_T c1_y;
  uint16_T c1_u14;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u14, 1, 5, 0U, 0, 0U, 0);
  c1_y = c1_u14;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static uint16_T c1_w_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c1_c_Y1, const char_T *c1_identifier)
{
  uint16_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_x_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_c_Y1), &c1_thisId);
  sf_mex_destroy(&c1_c_Y1);
  return c1_y;
}

static uint16_T c1_x_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint16_T c1_y;
  uint16_T c1_u15;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u15, 1, 5, 0U, 0, 0U, 0);
  c1_y = c1_u15;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_y_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_ctrlReceiver, const char_T *c1_identifier)
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_ab_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_ctrlReceiver), &c1_thisId);
  sf_mex_destroy(&c1_ctrlReceiver);
}

static void c1_ab_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_ctrlReceiver_not_empty = FALSE;
  } else {
    chartInstance->c1_ctrlReceiver_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), NULL, 1, 11, 0U, 1, 0U, 2, 0, 0);
  }

  sf_mex_destroy(&c1_u);
}

static void c1_bb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_ctrlReceiverBlocking, const char_T *c1_identifier)
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_cb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_ctrlReceiverBlocking),
    &c1_thisId);
  sf_mex_destroy(&c1_ctrlReceiverBlocking);
}

static void c1_cb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_ctrlReceiverBlocking_not_empty = FALSE;
  } else {
    chartInstance->c1_ctrlReceiverBlocking_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), NULL, 1, 11, 0U, 1, 0U, 2, 0, 0);
  }

  sf_mex_destroy(&c1_u);
}

static void c1_db_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_ctrlSender, const char_T *c1_identifier)
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_eb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_ctrlSender), &c1_thisId);
  sf_mex_destroy(&c1_ctrlSender);
}

static void c1_eb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_ctrlSender_not_empty = FALSE;
  } else {
    chartInstance->c1_ctrlSender_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), NULL, 1, 11, 0U, 1, 0U, 2, 0, 0);
  }

  sf_mex_destroy(&c1_u);
}

static real_T c1_fb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_b_lastCF, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_gb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_lastCF),
    &c1_thisId);
  sf_mex_destroy(&c1_b_lastCF);
  return c1_y;
}

static real_T c1_gb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d3;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_lastCF_not_empty = FALSE;
  } else {
    chartInstance->c1_lastCF_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d3, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d3;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static real_T c1_hb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_b_lastDI, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_ib_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_lastDI),
    &c1_thisId);
  sf_mex_destroy(&c1_b_lastDI);
  return c1_y;
}

static real_T c1_ib_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d4;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_lastDI_not_empty = FALSE;
  } else {
    chartInstance->c1_lastDI_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d4, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d4;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static real_T c1_jb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_b_lastG, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_kb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_lastG),
    &c1_thisId);
  sf_mex_destroy(&c1_b_lastG);
  return c1_y;
}

static real_T c1_kb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d5;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_lastG_not_empty = FALSE;
  } else {
    chartInstance->c1_lastG_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d5, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d5;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static real_T c1_lb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_b_lastI, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_mb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_lastI),
    &c1_thisId);
  sf_mex_destroy(&c1_b_lastI);
  return c1_y;
}

static real_T c1_mb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d6;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_lastI_not_empty = FALSE;
  } else {
    chartInstance->c1_lastI_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d6, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d6;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static real_T c1_nb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_b_lastQ, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_ob_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_lastQ),
    &c1_thisId);
  sf_mex_destroy(&c1_b_lastQ);
  return c1_y;
}

static real_T c1_ob_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d7;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_lastQ_not_empty = FALSE;
  } else {
    chartInstance->c1_lastQ_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d7, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d7;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static real_T c1_pb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_b_replyId, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_qb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_replyId),
    &c1_thisId);
  sf_mex_destroy(&c1_b_replyId);
  return c1_y;
}

static real_T c1_qb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d8;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_replyId_not_empty = FALSE;
  } else {
    chartInstance->c1_replyId_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d8, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d8;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_rb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_b_replyQueue, const char_T *c1_identifier,
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_y[255])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_sb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_replyQueue), &c1_thisId,
    c1_y);
  sf_mex_destroy(&c1_b_replyQueue);
}

static void c1_sb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_y[255])
{
  int32_T c1_i28;
  uint32_T c1_uv7[2];
  emlrtMsgIdentifier c1_thisId;
  static const char * c1_fieldNames[6] = { "ValidMask", "Fc", "Gain",
    "DecimInterp", "ScaleI", "ScaleQ" };

  c1_sgyjHZtUMVZuM1aKBgGok1D (*c1_r4)[255];
  for (c1_i28 = 0; c1_i28 < 2; c1_i28++) {
    c1_uv7[c1_i28] = 1U + 254U * (uint32_T)c1_i28;
  }

  c1_thisId.fParent = c1_parentId;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_replyQueue_not_empty = FALSE;
  } else {
    chartInstance->c1_replyQueue_not_empty = TRUE;
    sf_mex_check_struct(c1_parentId, c1_u, 6, c1_fieldNames, 2U, c1_uv7);
    c1_r4 = (c1_sgyjHZtUMVZuM1aKBgGok1D (*)[255])c1_y;
    for (c1_i28 = 0; c1_i28 < 255; c1_i28++) {
      c1_thisId.fIdentifier = "ValidMask";
      (*c1_r4)[c1_i28].ValidMask = c1_tb_emlrt_marshallIn(chartInstance,
        sf_mex_dup(sf_mex_getfield(c1_u, "ValidMask", "ValidMask", c1_i28)),
        &c1_thisId);
      c1_thisId.fIdentifier = "Fc";
      (*c1_r4)[c1_i28].Fc = c1_tb_emlrt_marshallIn(chartInstance, sf_mex_dup
        (sf_mex_getfield(c1_u, "Fc", "Fc", c1_i28)), &c1_thisId);
      c1_thisId.fIdentifier = "Gain";
      (*c1_r4)[c1_i28].Gain = c1_tb_emlrt_marshallIn(chartInstance, sf_mex_dup
        (sf_mex_getfield(c1_u, "Gain", "Gain", c1_i28)), &c1_thisId);
      c1_thisId.fIdentifier = "DecimInterp";
      (*c1_r4)[c1_i28].DecimInterp = c1_tb_emlrt_marshallIn(chartInstance,
        sf_mex_dup(sf_mex_getfield(c1_u, "DecimInterp", "DecimInterp", c1_i28)),
        &c1_thisId);
      c1_thisId.fIdentifier = "ScaleI";
      (*c1_r4)[c1_i28].ScaleI = c1_tb_emlrt_marshallIn(chartInstance, sf_mex_dup
        (sf_mex_getfield(c1_u, "ScaleI", "ScaleI", c1_i28)), &c1_thisId);
      c1_thisId.fIdentifier = "ScaleQ";
      (*c1_r4)[c1_i28].ScaleQ = c1_tb_emlrt_marshallIn(chartInstance, sf_mex_dup
        (sf_mex_getfield(c1_u, "ScaleQ", "ScaleQ", c1_i28)), &c1_thisId);
    }
  }

  sf_mex_destroy(&c1_u);
}

static real_T c1_tb_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d9;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d9, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d9;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static uint8_T c1_ub_emlrt_marshallIn(SFc1_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_commsdrhw, const char_T
  *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_commsdrhw), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_commsdrhw);
  return c1_y;
}

static real_T c1_l_SendConfig(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_b_replyQueue[255], real_T c1_centerFreq, real_T
  c1_gain, real_T c1_interpolation, real_T c1_scaleI, real_T c1_scaleQ)
{
  real_T c1_repliesOutstanding;
  real_T c1_currCfg_ScaleQ;
  real_T c1_currCfg_ScaleI;
  real_T c1_currCfg_DecimInterp;
  real_T c1_currCfg_Gain;
  real_T c1_currCfg_Fc;
  real_T c1_currCfg_ValidMask;
  uint8_T c1_b_replyId;
  uint8_T c1_ctrlData[255];
  real_T c1_ctrlLength;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_cmdDef[18];
  int32_T c1_i29;
  static char_T c1_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c1_u[23];
  const mxArray *c1_y = NULL;
  char_T c1_b_u[40];
  static char_T c1_cv21[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  const mxArray *c1_b_y = NULL;
  char_T c1_c_u[23];
  const mxArray *c1_c_y = NULL;
  char_T c1_d_u[40];
  const mxArray *c1_d_y = NULL;
  char_T c1_e_u[23];
  const mxArray *c1_e_y = NULL;
  char_T c1_f_u[40];
  const mxArray *c1_f_y = NULL;
  c1_USRP2RuntimeControl(chartInstance, c1_centerFreq, &c1_ctrlLength,
    c1_ctrlData, &c1_b_replyId, &c1_currCfg_ValidMask, &c1_currCfg_Fc,
    &c1_currCfg_Gain, &c1_currCfg_DecimInterp, &c1_currCfg_ScaleI,
    &c1_currCfg_ScaleQ);
  c1_repliesOutstanding = 0.0;
  c1_l_addToQueue(chartInstance, c1_ctrlData, c1_ctrlLength, c1_b_replyQueue,
                  c1_b_replyId, c1_currCfg_ValidMask, c1_currCfg_Fc,
                  c1_currCfg_Gain, c1_currCfg_DecimInterp, c1_currCfg_ScaleI,
                  c1_currCfg_ScaleQ, &c1_repliesOutstanding);
  c1_b_USRP2RuntimeControl(chartInstance, c1_gain, &c1_ctrlLength, c1_ctrlData,
    &c1_b_replyId, &c1_currCfg_ValidMask, &c1_currCfg_Fc, &c1_currCfg_Gain,
    &c1_currCfg_DecimInterp, &c1_currCfg_ScaleI, &c1_currCfg_ScaleQ);
  c1_l_addToQueue(chartInstance, c1_ctrlData, c1_ctrlLength, c1_b_replyQueue,
                  c1_b_replyId, c1_currCfg_ValidMask, c1_currCfg_Fc,
                  c1_currCfg_Gain, c1_currCfg_DecimInterp, c1_currCfg_ScaleI,
                  c1_currCfg_ScaleQ, &c1_repliesOutstanding);
  c1_c_USRP2RuntimeControl(chartInstance, c1_interpolation, &c1_ctrlLength,
    c1_ctrlData, &c1_b_replyId, &c1_currCfg_ValidMask, &c1_currCfg_Fc,
    &c1_currCfg_Gain, &c1_currCfg_DecimInterp, &c1_currCfg_ScaleI,
    &c1_currCfg_ScaleQ);
  c1_l_addToQueue(chartInstance, c1_ctrlData, c1_ctrlLength, c1_b_replyQueue,
                  c1_b_replyId, c1_currCfg_ValidMask, c1_currCfg_Fc,
                  c1_currCfg_Gain, c1_currCfg_DecimInterp, c1_currCfg_ScaleI,
                  c1_currCfg_ScaleQ, &c1_repliesOutstanding);
  chartInstance->c1_lastCF_not_empty = TRUE;
  chartInstance->c1_lastG_not_empty = TRUE;
  chartInstance->c1_lastDI_not_empty = TRUE;
  chartInstance->c1_lastI_not_empty = TRUE;
  chartInstance->c1_lastQ_not_empty = TRUE;
  c1_USRP2CmdDef(chartInstance, USRP2Opcodes_ConfigTx, c1_cmdDef);
  c1_currCfg_Fc = chartInstance->c1_lastCF;
  c1_currCfg_Gain = chartInstance->c1_lastG;
  c1_currCfg_DecimInterp = chartInstance->c1_lastDI;
  if (c1_cmdDef[sf_mex_lw_bounds_check((int32_T)USRP2CmdFields_ScaleI, 1, 18) -
      1].fsize == 0.0) {
    for (c1_i29 = 0; c1_i29 < 23; c1_i29++) {
      c1_u[c1_i29] = c1_varargin_1[c1_i29];
    }

    c1_y = NULL;
    sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c1_b_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_ScaleI;
    for (c1_i29 = 0; c1_i29 < 39; c1_i29++) {
      c1_b_u[c1_i29 + 1] = c1_cv21[c1_i29];
    }

    c1_b_y = NULL;
    sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c1_y, 14, c1_b_y);
  } else {
    c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[(int32_T)USRP2CmdFields_ScaleI
                         - 1].dtype, c1_scaleI, c1_cmdDef[sf_mex_lw_bounds_check
                         ((int32_T)USRP2CmdFields_ScaleI, 1, 18) - 1].bytes);
  }

  if (c1_cmdDef[sf_mex_lw_bounds_check((int32_T)USRP2CmdFields_ScaleQ, 1, 18) -
      1].fsize == 0.0) {
    for (c1_i29 = 0; c1_i29 < 23; c1_i29++) {
      c1_c_u[c1_i29] = c1_varargin_1[c1_i29];
    }

    c1_c_y = NULL;
    sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_c_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c1_d_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_ScaleQ;
    for (c1_i29 = 0; c1_i29 < 39; c1_i29++) {
      c1_d_u[c1_i29 + 1] = c1_cv21[c1_i29];
    }

    c1_d_y = NULL;
    sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_d_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c1_c_y, 14, c1_d_y);
  } else {
    c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[(int32_T)USRP2CmdFields_ScaleQ
                         - 1].dtype, c1_scaleQ, c1_cmdDef[sf_mex_lw_bounds_check
                         ((int32_T)USRP2CmdFields_ScaleQ, 1, 18) - 1].bytes);
  }

  if (c1_cmdDef[sf_mex_lw_bounds_check((int32_T)USRP2CmdFields_Valid, 1, 18) - 1]
      .fsize == 0.0) {
    for (c1_i29 = 0; c1_i29 < 23; c1_i29++) {
      c1_e_u[c1_i29] = c1_varargin_1[c1_i29];
    }

    c1_e_y = NULL;
    sf_mex_assign(&c1_e_y, sf_mex_create("y", c1_e_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c1_f_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Valid;
    for (c1_i29 = 0; c1_i29 < 39; c1_i29++) {
      c1_f_u[c1_i29 + 1] = c1_cv21[c1_i29];
    }

    c1_f_y = NULL;
    sf_mex_assign(&c1_f_y, sf_mex_create("y", c1_f_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c1_e_y, 14, c1_f_y);
  } else {
    c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[(int32_T)USRP2CmdFields_Valid
                         - 1].dtype, 8.0, c1_cmdDef[sf_mex_lw_bounds_check
                         ((int32_T)USRP2CmdFields_Valid, 1, 18) - 1].bytes);
  }

  c1_USRP2Cmd2Pkt(chartInstance, c1_cmdDef, c1_ctrlData, &c1_ctrlLength);
  chartInstance->c1_lastCF = c1_currCfg_Fc;
  chartInstance->c1_lastG = c1_currCfg_Gain;
  chartInstance->c1_lastDI = c1_currCfg_DecimInterp;
  chartInstance->c1_lastI = c1_scaleI;
  chartInstance->c1_lastQ = c1_scaleQ;
  c1_l_addToQueue(chartInstance, c1_ctrlData, c1_ctrlLength, c1_b_replyQueue,
                  c1_ctrlData[2], 8.0, c1_currCfg_Fc, c1_currCfg_Gain,
                  c1_currCfg_DecimInterp, c1_scaleI, c1_scaleQ,
                  &c1_repliesOutstanding);
  return c1_repliesOutstanding;
}

static void c1_l_addToQueue(SFc1_commsdrhwInstanceStruct *chartInstance, uint8_T
  c1_ctrlData[255], real_T c1_ctrlLength, c1_sgyjHZtUMVZuM1aKBgGok1D
  c1_b_replyQueue[255], uint8_T c1_b_replyId, real_T c1_currCfg_ValidMask,
  real_T c1_currCfg_Fc, real_T c1_currCfg_Gain, real_T c1_currCfg_DecimInterp,
  real_T c1_currCfg_ScaleI, real_T c1_currCfg_ScaleQ, real_T
  *c1_repliesOutstanding)
{
  int32_T c1_i30;
  uint8_T c1_b_ctrlData[255];
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_expl_temp;
  if (c1_ctrlLength > 0.0) {
    for (c1_i30 = 0; c1_i30 < 255; c1_i30++) {
      c1_b_ctrlData[c1_i30] = c1_ctrlData[c1_i30];
    }

    c1_Update(chartInstance, c1_b_ctrlData, c1_ctrlLength);
    c1_expl_temp.ValidMask = c1_currCfg_ValidMask;
    c1_expl_temp.Fc = c1_currCfg_Fc;
    c1_expl_temp.Gain = c1_currCfg_Gain;
    c1_expl_temp.DecimInterp = c1_currCfg_DecimInterp;
    c1_expl_temp.ScaleI = c1_currCfg_ScaleI;
    c1_expl_temp.ScaleQ = c1_currCfg_ScaleQ;
    c1_b_replyQueue[sf_mex_lw_bounds_check((int32_T)c1_b_replyId, 1, 255) - 1] =
      c1_expl_temp;
    (*c1_repliesOutstanding)++;
  }
}

static boolean_T c1_l_ReceiveReply(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_b_replyQueue[255])
{
  boolean_T c1_replyProcessed;
  char_T *c1_sErr;
  int32_T c1_samplesRead;
  int32_T c1_i31;
  uint8_T c1_uv8[255];
  real_T c1_b_replyId;
  int32_T c1_errStr_sizes[2];
  char_T c1_errStr_data[56];
  int32_T c1_tmp_sizes[2];
  int32_T c1_loop_ub;
  char_T c1_tmp_data[169];
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_expl_temp;
  char_T c1_b_errStr_data[170];
  static char_T c1_cv22[31] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's', ':', 'U',
    'S', 'R', 'P', '2', 'R', 'e', 'c', 'e', 'i', 'v', 'e', 'r', ':', 'R', 'e',
    'p', 'l', 'y', 'E', 'r', 'r' };

  char_T c1_u[31];
  const mxArray *c1_y = NULL;
  char_T c1_u_data[170];
  const mxArray *c1_b_y = NULL;
  int32_T c1_errStr_sizes_idx_1;
  char_T c1_c_errStr_data[170];
  char_T c1_d_errStr_data[170];
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_b_expl_temp;
  static char_T c1_cv23[33] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's', ':', 'U',
    'S', 'R', 'P', '2', 'R', 'e', 'c', 'e', 'i', 'v', 'e', 'r', ':', 'N', 'o',
    'R', 'e', 'p', 'l', 'y', 'E', 'r', 'r' };

  char_T c1_b_u[33];
  const mxArray *c1_c_y = NULL;
  static char_T c1_errMsg[175] = { 'B', 'o', 'a', 'r', 'd', ' ', 'd', 'i', 'd',
    ' ', 'n', 'o', 't', ' ', 'r', 'e', 'p', 'l', 'y', ' ', 't', 'o', ' ', 'a',
    ' ', 'h', 'o', 's', 't', ' ', 'q', 'u', 'e', 'r', 'y', ' ', 'o', 'r', ' ',
    'c', 'o', 'n', 'f', 'i', 'g', 'u', 'r', 'a', 't', 'i', 'o', 'n', '.', ' ',
    'C', 'a', 'n', 'n', 'o', 't', ' ', 'r', 'u', 'n', ' ', 's', 'i', 'm', 'u',
    'l', 'a', 't', 'i', 'o', 'n', '.', ' ', ' ', 'P', 'l', 'e', 'a', 's', 'e',
    ' ', 'e', 'n', 's', 'u', 'r', 'e', ' ', 'y', 'o', 'u', ' ', 'h', 'a', 'v',
    'e', ' ', 'a', ' ', 'c', 'o', 'n', 'n', 'e', 'c', 't', 'i', 'o', 'n', ' ',
    'b', 'y', ' ', 'o', 'p', 'e', 'n', 'i', 'n', 'g', ' ', 't', 'h', 'e', ' ',
    'b', 'l', 'o', 'c', 'k', ' ', 'm', 'a', 's', 'k', ' ', 'a', 'n', 'd', ' ',
    'e', 'x', 'a', 'm', 'i', 'n', 'i', 'n', 'g', ' ', 't', 'h', 'e', ' ', 'H',
    'a', 'r', 'd', 'w', 'a', 'r', 'e', ' ', 's', 'e', 'c', 't', 'i', 'o', 'n',
    '.' };

  char_T c1_c_u[175];
  const mxArray *c1_d_y = NULL;
  static char_T c1_cv24[176] = { 'B', 'o', 'a', 'r', 'd', ' ', 'd', 'i', 'd',
    ' ', 'n', 'o', 't', ' ', 'r', 'e', 'p', 'l', 'y', ' ', 't', 'o', ' ', 'a',
    ' ', 'h', 'o', 's', 't', ' ', 'q', 'u', 'e', 'r', 'y', ' ', 'o', 'r', ' ',
    'c', 'o', 'n', 'f', 'i', 'g', 'u', 'r', 'a', 't', 'i', 'o', 'n', '.', ' ',
    'C', 'a', 'n', 'n', 'o', 't', ' ', 'r', 'u', 'n', ' ', 's', 'i', 'm', 'u',
    'l', 'a', 't', 'i', 'o', 'n', '.', ' ', ' ', 'P', 'l', 'e', 'a', 's', 'e',
    ' ', 'e', 'n', 's', 'u', 'r', 'e', ' ', 'y', 'o', 'u', ' ', 'h', 'a', 'v',
    'e', ' ', 'a', ' ', 'c', 'o', 'n', 'n', 'e', 'c', 't', 'i', 'o', 'n', ' ',
    'b', 'y', ' ', 'o', 'p', 'e', 'n', 'i', 'n', 'g', ' ', 't', 'h', 'e', ' ',
    'b', 'l', 'o', 'c', 'k', ' ', 'm', 'a', 's', 'k', ' ', 'a', 'n', 'd', ' ',
    'e', 'x', 'a', 'm', 'i', 'n', 'i', 'n', 'g', ' ', 't', 'h', 'e', ' ', 'H',
    'a', 'r', 'd', 'w', 'a', 'r', 'e', ' ', 's', 'e', 'c', 't', 'i', 'o', 'n',
    '.', '\x00' };

  char_T c1_cv25[176];
  c1_replyProcessed = FALSE;

  /* System object Outputs function: dsp.UDPReceiver */
  c1_sErr = GetErrorBuffer(&chartInstance->c1_b_NetworkLib[0U]);
  c1_samplesRead = 255;
  LibOutputs_Network(&chartInstance->c1_b_NetworkLib[0U],
                     &chartInstance->c1_b_Y0[0], &(&c1_samplesRead)[0U]);
  if (*c1_sErr != 0) {
    PrintError(c1_sErr);
  }

  chartInstance->c1_b_Y1 = (uint16_T)c1_samplesRead;
  for (c1_i31 = 0; c1_i31 < 255; c1_i31++) {
    c1_uv8[c1_i31] = chartInstance->c1_b_Y0[c1_i31];
  }

  if (chartInstance->c1_b_Y1 > 0) {
    c1_USRP2RuntimeControlReplies(chartInstance, c1_uv8, chartInstance->c1_b_Y1,
      c1_errStr_data, c1_errStr_sizes, &c1_b_replyId);
    if (!(c1_errStr_sizes[1] == 0)) {
      c1_tmp_sizes[0] = 1;
      c1_tmp_sizes[1] = c1_errStr_sizes[1];
      c1_loop_ub = c1_errStr_sizes[0] * c1_errStr_sizes[1] - 1;
      for (c1_i31 = 0; c1_i31 <= c1_loop_ub; c1_i31++) {
        c1_tmp_data[c1_i31] = c1_errStr_data[c1_i31];
      }

      c1_expl_temp = c1_b_replyQueue[sf_mex_lw_bounds_check((int32_T)
        c1_b_replyId, 1, 255) - 1];
      c1_l_CheckConfig(chartInstance, c1_tmp_data, c1_tmp_sizes,
                       c1_expl_temp.ValidMask, c1_expl_temp.Fc,
                       c1_expl_temp.Gain, c1_expl_temp.DecimInterp,
                       c1_expl_temp.ScaleI, c1_expl_temp.ScaleQ);
      c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
      for (c1_i31 = 0; c1_i31 <= c1_loop_ub; c1_i31++) {
        c1_b_errStr_data[c1_i31] = c1_tmp_data[c1_i31];
      }

      for (c1_i31 = 0; c1_i31 < 31; c1_i31++) {
        c1_u[c1_i31] = c1_cv22[c1_i31];
      }

      c1_y = NULL;
      sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 31));
      c1_loop_ub = c1_tmp_sizes[1] - 1;
      for (c1_i31 = 0; c1_i31 <= c1_loop_ub; c1_i31++) {
        c1_u_data[c1_i31] = c1_b_errStr_data[c1_i31];
      }

      c1_b_y = NULL;
      sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u_data, 10, 0U, 1U, 0U, 2, 1,
        c1_tmp_sizes[1]));
      sf_mex_call("warning", 0U, 2U, 14, c1_y, 14, c1_b_y);
      c1_errStr_sizes_idx_1 = c1_tmp_sizes[1] + 1;
      c1_loop_ub = c1_tmp_sizes[1] - 1;
      for (c1_i31 = 0; c1_i31 <= c1_loop_ub; c1_i31++) {
        c1_c_errStr_data[c1_i31] = c1_b_errStr_data[c1_i31];
      }

      c1_c_errStr_data[c1_tmp_sizes[1]] = '\x00';
      c1_loop_ub = c1_errStr_sizes_idx_1 - 1;
      for (c1_i31 = 0; c1_i31 <= c1_loop_ub; c1_i31++) {
        c1_b_errStr_data[c1_i31] = c1_c_errStr_data[c1_i31];
      }

      c1_loop_ub = c1_errStr_sizes_idx_1 - 1;
      for (c1_i31 = 0; c1_i31 <= c1_loop_ub; c1_i31++) {
        c1_d_errStr_data[c1_i31] = c1_b_errStr_data[c1_i31];
      }

      PrintError(&c1_d_errStr_data[0]);
    }

    c1_b_expl_temp.ValidMask = 0.0;
    c1_b_expl_temp.Fc = 0.0;
    c1_b_expl_temp.Gain = 0.0;
    c1_b_expl_temp.DecimInterp = 0.0;
    c1_b_expl_temp.ScaleI = 0.0;
    c1_b_expl_temp.ScaleQ = 0.0;
    c1_b_replyQueue[sf_mex_lw_bounds_check((int32_T)c1_b_replyId, 1, 255) - 1] =
      c1_b_expl_temp;
    c1_replyProcessed = TRUE;
  } else {
    for (c1_i31 = 0; c1_i31 < 33; c1_i31++) {
      c1_b_u[c1_i31] = c1_cv23[c1_i31];
    }

    c1_c_y = NULL;
    sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1, 33));
    for (c1_i31 = 0; c1_i31 < 175; c1_i31++) {
      c1_c_u[c1_i31] = c1_errMsg[c1_i31];
    }

    c1_d_y = NULL;
    sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_c_u, 10, 0U, 1U, 0U, 2, 1, 175));
    sf_mex_call("error", 0U, 2U, 14, c1_c_y, 14, c1_d_y);
    for (c1_i31 = 0; c1_i31 < 176; c1_i31++) {
      c1_cv25[c1_i31] = c1_cv24[c1_i31];
    }

    PrintError(c1_cv25);
  }

  return c1_replyProcessed;
}

static void c1_l_CheckConfig(SFc1_commsdrhwInstanceStruct *chartInstance, char_T
  c1_errStr_data[169], int32_T c1_errStr_sizes[2], real_T c1_cfgEntry_ValidMask,
  real_T c1_cfgEntry_Fc, real_T c1_cfgEntry_Gain, real_T c1_cfgEntry_DecimInterp,
  real_T c1_cfgEntry_ScaleI, real_T c1_cfgEntry_ScaleQ)
{
  real_T c1_d10;
  uint8_T c1_validMask;
  int32_T c1_i32;
  static char_T c1_cv26[4] = { '%', 's', '\\', 'n' };

  char_T c1_u[4];
  const mxArray *c1_y = NULL;
  int32_T c1_cgMsg_sizes_idx_1;
  int32_T c1_loop_ub;
  char_T c1_b_errStr_data[169];
  char_T c1_u_data[169];
  const mxArray *c1_b_y = NULL;
  const mxArray *c1_simMsg = NULL;
  char_T c1_cgMsg_data[169];
  static char_T c1_cv27[32] = { '%', 's', ' ', ' ', ' ', 'I', 'n', 'v', 'a', 'l',
    'i', 'd', ' ', 'g', 'a', 'i', 'n', ' ', 'v', 'a', 'l', 'u', 'e', ':', ' ',
    '%', '6', '.', '5', 'g', '\\', 'n' };

  char_T c1_b_u[32];
  const mxArray *c1_c_y = NULL;
  real_T c1_c_u;
  const mxArray *c1_d_y = NULL;
  static char_T c1_cv28[21] = { ' ', ' ', 'I', 'n', 'v', 'a', 'l', 'i', 'd', ' ',
    'g', 'a', 'i', 'n', ' ', 'v', 'a', 'l', 'u', 'e', '.' };

  static char_T c1_cv29[44] = { '%', 's', ' ', ' ', ' ', 'I', 'n', 'v', 'a', 'l',
    'i', 'd', ' ', 'c', 'e', 'n', 't', 'e', 'r', ' ', 'f', 'r', 'e', 'q', 'u',
    'e', 'n', 'c', 'y', ' ', 'v', 'a', 'l', 'u', 'e', ':', ' ', '%', '6', '.',
    '5', 'g', '\\', 'n' };

  char_T c1_d_u[44];
  const mxArray *c1_e_y = NULL;
  real_T c1_e_u;
  const mxArray *c1_f_y = NULL;
  int32_T c1_b_cgMsg_sizes_idx_1;
  static char_T c1_cv30[33] = { ' ', ' ', 'I', 'n', 'v', 'a', 'l', 'i', 'd', ' ',
    'c', 'e', 'n', 't', 'e', 'r', ' ', 'f', 'r', 'e', 'q', 'u', 'e', 'n', 'c',
    'y', ' ', 'v', 'a', 'l', 'u', 'e', '.' };

  static char_T c1_cv31[38] = { '%', 's', ' ', ' ', ' ', 'I', 'n', 'v', 'a', 'l',
    'i', 'd', ' ', 'i', 'n', 't', 'e', 'r', 'p', 'o', 'l', 'a', 't', 'i', 'o',
    'n', ' ', 'v', 'a', 'l', 'u', 'e', ':', ' ', '%', 'd', '\\', 'n' };

  char_T c1_f_u[38];
  const mxArray *c1_g_y = NULL;
  real_T c1_g_u;
  const mxArray *c1_h_y = NULL;
  static char_T c1_cv32[30] = { ' ', ' ', 'I', 'n', 'v', 'a', 'l', 'i', 'd', ' ',
    'i', 'n', 't', 'e', 'r', 'p', 'o', 'l', 'a', 't', 'i', 'o', 'n', ' ', 'v',
    'a', 'l', 'u', 'e', '.' };

  static char_T c1_cv33[41] = { '%', 's', ' ', ' ', ' ', 'I', 'n', 'v', 'a', 'l',
    'i', 'd', ' ', 'I', '/', 'Q', ' ', 's', 'c', 'a', 'l', 'i', 'n', 'g', ' ',
    'v', 'a', 'l', 'u', 'e', 's', ':', ' ', '%', 'd', ',', ' ', '%', 'd', '\\',
    'n' };

  char_T c1_h_u[41];
  const mxArray *c1_i_y = NULL;
  real_T c1_i_u;
  const mxArray *c1_j_y = NULL;
  real_T c1_j_u;
  const mxArray *c1_k_y = NULL;
  static char_T c1_cv34[29] = { ' ', ' ', 'I', 'n', 'v', 'a', 'l', 'i', 'd', ' ',
    'I', '/', 'Q', ' ', 's', 'c', 'a', 'l', 'i', 'n', 'g', ' ', 'v', 'a', 'l',
    'u', 'e', 's', '.' };

  c1_d10 = c1_cfgEntry_ValidMask;
  c1_d10 = c1_d10 < 0.0 ? muDoubleScalarCeil(c1_d10 - 0.5) : muDoubleScalarFloor
    (c1_d10 + 0.5);
  if (c1_d10 < 256.0) {
    if (c1_d10 >= 0.0) {
      c1_validMask = (uint8_T)c1_d10;
    } else {
      c1_validMask = 0U;
    }
  } else if (c1_d10 >= 256.0) {
    c1_validMask = MAX_uint8_T;
  } else {
    c1_validMask = 0U;
  }

  for (c1_i32 = 0; c1_i32 < 4; c1_i32++) {
    c1_u[c1_i32] = c1_cv26[c1_i32];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 4));
  c1_cgMsg_sizes_idx_1 = c1_errStr_sizes[1];
  c1_loop_ub = c1_errStr_sizes[1] - 1;
  for (c1_i32 = 0; c1_i32 <= c1_loop_ub; c1_i32++) {
    c1_b_errStr_data[c1_i32] = c1_errStr_data[c1_errStr_sizes[0] * c1_i32];
  }

  c1_loop_ub = c1_cgMsg_sizes_idx_1 - 1;
  for (c1_i32 = 0; c1_i32 <= c1_loop_ub; c1_i32++) {
    c1_u_data[c1_i32] = c1_b_errStr_data[c1_i32];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u_data, 10, 0U, 1U, 0U, 2, 1,
    c1_cgMsg_sizes_idx_1));
  sf_mex_assign(&c1_simMsg, sf_mex_call("sprintf", 1U, 2U, 14, c1_y, 14, c1_b_y));
  c1_cgMsg_sizes_idx_1 = c1_errStr_sizes[1];
  c1_loop_ub = c1_errStr_sizes[1] - 1;
  for (c1_i32 = 0; c1_i32 <= c1_loop_ub; c1_i32++) {
    c1_cgMsg_data[c1_i32] = c1_errStr_data[c1_errStr_sizes[0] * c1_i32];
  }

  if ((c1_validMask & 1) != 0) {
    for (c1_i32 = 0; c1_i32 < 32; c1_i32++) {
      c1_b_u[c1_i32] = c1_cv27[c1_i32];
    }

    c1_c_y = NULL;
    sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1, 32));
    c1_c_u = c1_cfgEntry_Gain;
    c1_d_y = NULL;
    sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_u, 0, 0U, 0U, 0U, 0));
    sf_mex_assign(&c1_simMsg, sf_mex_call("sprintf", 1U, 3U, 14, c1_c_y, 14,
      sf_mex_dup(c1_simMsg), 14, c1_d_y));
    c1_cgMsg_sizes_idx_1 = c1_errStr_sizes[1] + 21;
    c1_loop_ub = c1_errStr_sizes[1] - 1;
    for (c1_i32 = 0; c1_i32 <= c1_loop_ub; c1_i32++) {
      c1_cgMsg_data[c1_i32] = c1_errStr_data[c1_errStr_sizes[0] * c1_i32];
    }

    for (c1_i32 = 0; c1_i32 < 21; c1_i32++) {
      c1_cgMsg_data[c1_i32 + c1_errStr_sizes[1]] = c1_cv28[c1_i32];
    }
  }

  if ((c1_validMask & 2) != 0) {
    for (c1_i32 = 0; c1_i32 < 44; c1_i32++) {
      c1_d_u[c1_i32] = c1_cv29[c1_i32];
    }

    c1_e_y = NULL;
    sf_mex_assign(&c1_e_y, sf_mex_create("y", c1_d_u, 10, 0U, 1U, 0U, 2, 1, 44));
    c1_e_u = c1_cfgEntry_Fc;
    c1_f_y = NULL;
    sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_e_u, 0, 0U, 0U, 0U, 0));
    sf_mex_assign(&c1_simMsg, sf_mex_call("sprintf", 1U, 3U, 14, c1_e_y, 14,
      sf_mex_dup(c1_simMsg), 14, c1_f_y));
    c1_b_cgMsg_sizes_idx_1 = c1_cgMsg_sizes_idx_1 + 33;
    c1_loop_ub = c1_cgMsg_sizes_idx_1 - 1;
    for (c1_i32 = 0; c1_i32 <= c1_loop_ub; c1_i32++) {
      c1_b_errStr_data[c1_i32] = c1_cgMsg_data[c1_i32];
    }

    for (c1_i32 = 0; c1_i32 < 33; c1_i32++) {
      c1_b_errStr_data[c1_i32 + c1_cgMsg_sizes_idx_1] = c1_cv30[c1_i32];
    }

    c1_cgMsg_sizes_idx_1 = c1_b_cgMsg_sizes_idx_1;
    c1_loop_ub = c1_b_cgMsg_sizes_idx_1 - 1;
    for (c1_i32 = 0; c1_i32 <= c1_loop_ub; c1_i32++) {
      c1_cgMsg_data[c1_i32] = c1_b_errStr_data[c1_i32];
    }
  }

  if ((c1_validMask & 4) != 0) {
    for (c1_i32 = 0; c1_i32 < 38; c1_i32++) {
      c1_f_u[c1_i32] = c1_cv31[c1_i32];
    }

    c1_g_y = NULL;
    sf_mex_assign(&c1_g_y, sf_mex_create("y", c1_f_u, 10, 0U, 1U, 0U, 2, 1, 38));
    c1_g_u = c1_cfgEntry_DecimInterp;
    c1_h_y = NULL;
    sf_mex_assign(&c1_h_y, sf_mex_create("y", &c1_g_u, 0, 0U, 0U, 0U, 0));
    sf_mex_assign(&c1_simMsg, sf_mex_call("sprintf", 1U, 3U, 14, c1_g_y, 14,
      sf_mex_dup(c1_simMsg), 14, c1_h_y));
    c1_b_cgMsg_sizes_idx_1 = c1_cgMsg_sizes_idx_1 + 30;
    c1_loop_ub = c1_cgMsg_sizes_idx_1 - 1;
    for (c1_i32 = 0; c1_i32 <= c1_loop_ub; c1_i32++) {
      c1_b_errStr_data[c1_i32] = c1_cgMsg_data[c1_i32];
    }

    for (c1_i32 = 0; c1_i32 < 30; c1_i32++) {
      c1_b_errStr_data[c1_i32 + c1_cgMsg_sizes_idx_1] = c1_cv32[c1_i32];
    }

    c1_cgMsg_sizes_idx_1 = c1_b_cgMsg_sizes_idx_1;
    c1_loop_ub = c1_b_cgMsg_sizes_idx_1 - 1;
    for (c1_i32 = 0; c1_i32 <= c1_loop_ub; c1_i32++) {
      c1_cgMsg_data[c1_i32] = c1_b_errStr_data[c1_i32];
    }
  }

  if ((c1_validMask & 8) != 0) {
    for (c1_i32 = 0; c1_i32 < 41; c1_i32++) {
      c1_h_u[c1_i32] = c1_cv33[c1_i32];
    }

    c1_i_y = NULL;
    sf_mex_assign(&c1_i_y, sf_mex_create("y", c1_h_u, 10, 0U, 1U, 0U, 2, 1, 41));
    c1_i_u = c1_cfgEntry_ScaleI;
    c1_j_y = NULL;
    sf_mex_assign(&c1_j_y, sf_mex_create("y", &c1_i_u, 0, 0U, 0U, 0U, 0));
    c1_j_u = c1_cfgEntry_ScaleQ;
    c1_k_y = NULL;
    sf_mex_assign(&c1_k_y, sf_mex_create("y", &c1_j_u, 0, 0U, 0U, 0U, 0));
    sf_mex_call("sprintf", 0U, 4U, 14, c1_i_y, 14, sf_mex_dup(c1_simMsg), 14,
                c1_j_y, 14, c1_k_y);
    c1_b_cgMsg_sizes_idx_1 = c1_cgMsg_sizes_idx_1 + 29;
    c1_loop_ub = c1_cgMsg_sizes_idx_1 - 1;
    for (c1_i32 = 0; c1_i32 <= c1_loop_ub; c1_i32++) {
      c1_b_errStr_data[c1_i32] = c1_cgMsg_data[c1_i32];
    }

    for (c1_i32 = 0; c1_i32 < 29; c1_i32++) {
      c1_b_errStr_data[c1_i32 + c1_cgMsg_sizes_idx_1] = c1_cv34[c1_i32];
    }

    c1_cgMsg_sizes_idx_1 = c1_b_cgMsg_sizes_idx_1;
    c1_loop_ub = c1_b_cgMsg_sizes_idx_1 - 1;
    for (c1_i32 = 0; c1_i32 <= c1_loop_ub; c1_i32++) {
      c1_cgMsg_data[c1_i32] = c1_b_errStr_data[c1_i32];
    }
  }

  c1_errStr_sizes[0] = 1;
  c1_errStr_sizes[1] = c1_cgMsg_sizes_idx_1;
  c1_loop_ub = c1_cgMsg_sizes_idx_1 - 1;
  for (c1_i32 = 0; c1_i32 <= c1_loop_ub; c1_i32++) {
    c1_errStr_data[c1_errStr_sizes[0] * c1_i32] = c1_cgMsg_data[c1_i32];
  }

  sf_mex_destroy(&c1_simMsg);
}

static real_T c1_b_l_SendConfig(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_b_replyQueue[255], real_T c1_centerFreq, real_T
  c1_gain, real_T c1_interpolation, real_T c1_scaleI, real_T c1_scaleQ)
{
  real_T c1_repliesOutstanding;
  real_T c1_currCfg_ScaleQ;
  real_T c1_currCfg_ScaleI;
  real_T c1_currCfg_DecimInterp;
  real_T c1_currCfg_Gain;
  real_T c1_currCfg_Fc;
  real_T c1_currCfg_ValidMask;
  uint8_T c1_b_replyId;
  uint8_T c1_ctrlData[255];
  real_T c1_ctrlLength;
  c1_s7P91ApZ2CkwDPZE5FamWSB c1_cmdDef[18];
  int32_T c1_b_currCfg_ValidMask;
  int32_T c1_i33;
  static char_T c1_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c1_u[23];
  const mxArray *c1_y = NULL;
  char_T c1_b_u[40];
  static char_T c1_cv35[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  const mxArray *c1_b_y = NULL;
  char_T c1_c_u[23];
  const mxArray *c1_c_y = NULL;
  char_T c1_d_u[40];
  const mxArray *c1_d_y = NULL;
  char_T c1_e_u[23];
  const mxArray *c1_e_y = NULL;
  char_T c1_f_u[40];
  const mxArray *c1_f_y = NULL;
  c1_d_USRP2RuntimeControl(chartInstance, c1_centerFreq, &c1_ctrlLength,
    c1_ctrlData, &c1_b_replyId, &c1_currCfg_ValidMask, &c1_currCfg_Fc,
    &c1_currCfg_Gain, &c1_currCfg_DecimInterp, &c1_currCfg_ScaleI,
    &c1_currCfg_ScaleQ);
  c1_repliesOutstanding = 0.0;
  c1_l_addToQueue(chartInstance, c1_ctrlData, c1_ctrlLength, c1_b_replyQueue,
                  c1_b_replyId, c1_currCfg_ValidMask, c1_currCfg_Fc,
                  c1_currCfg_Gain, c1_currCfg_DecimInterp, c1_currCfg_ScaleI,
                  c1_currCfg_ScaleQ, &c1_repliesOutstanding);
  c1_e_USRP2RuntimeControl(chartInstance, c1_gain, &c1_ctrlLength, c1_ctrlData,
    &c1_b_replyId, &c1_currCfg_ValidMask, &c1_currCfg_Fc, &c1_currCfg_Gain,
    &c1_currCfg_DecimInterp, &c1_currCfg_ScaleI, &c1_currCfg_ScaleQ);
  c1_l_addToQueue(chartInstance, c1_ctrlData, c1_ctrlLength, c1_b_replyQueue,
                  c1_b_replyId, c1_currCfg_ValidMask, c1_currCfg_Fc,
                  c1_currCfg_Gain, c1_currCfg_DecimInterp, c1_currCfg_ScaleI,
                  c1_currCfg_ScaleQ, &c1_repliesOutstanding);
  c1_f_USRP2RuntimeControl(chartInstance, c1_interpolation, &c1_ctrlLength,
    c1_ctrlData, &c1_b_replyId, &c1_currCfg_ValidMask, &c1_currCfg_Fc,
    &c1_currCfg_Gain, &c1_currCfg_DecimInterp, &c1_currCfg_ScaleI,
    &c1_currCfg_ScaleQ);
  c1_l_addToQueue(chartInstance, c1_ctrlData, c1_ctrlLength, c1_b_replyQueue,
                  c1_b_replyId, c1_currCfg_ValidMask, c1_currCfg_Fc,
                  c1_currCfg_Gain, c1_currCfg_DecimInterp, c1_currCfg_ScaleI,
                  c1_currCfg_ScaleQ, &c1_repliesOutstanding);
  chartInstance->c1_lastCF_not_empty = TRUE;
  chartInstance->c1_lastG_not_empty = TRUE;
  chartInstance->c1_lastDI_not_empty = TRUE;
  chartInstance->c1_lastI_not_empty = TRUE;
  chartInstance->c1_lastQ_not_empty = TRUE;
  c1_USRP2CmdDef(chartInstance, USRP2Opcodes_ConfigTx, c1_cmdDef);
  c1_b_currCfg_ValidMask = 0;
  c1_currCfg_Fc = chartInstance->c1_lastCF;
  c1_currCfg_Gain = chartInstance->c1_lastG;
  c1_currCfg_DecimInterp = chartInstance->c1_lastDI;
  if ((c1_scaleI != chartInstance->c1_lastI) || (c1_scaleQ !=
       chartInstance->c1_lastQ)) {
    c1_b_currCfg_ValidMask = 8;
    if (c1_cmdDef[sf_mex_lw_bounds_check((int32_T)USRP2CmdFields_ScaleI, 1, 18)
        - 1].fsize == 0.0) {
      for (c1_i33 = 0; c1_i33 < 23; c1_i33++) {
        c1_u[c1_i33] = c1_varargin_1[c1_i33];
      }

      c1_y = NULL;
      sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 23));
      c1_b_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_ScaleI;
      for (c1_i33 = 0; c1_i33 < 39; c1_i33++) {
        c1_b_u[c1_i33 + 1] = c1_cv35[c1_i33];
      }

      c1_b_y = NULL;
      sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
      sf_mex_call("error", 0U, 2U, 14, c1_y, 14, c1_b_y);
    } else {
      c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[(int32_T)
                           USRP2CmdFields_ScaleI - 1].dtype, c1_scaleI,
                           c1_cmdDef[sf_mex_lw_bounds_check((int32_T)
        USRP2CmdFields_ScaleI, 1, 18) - 1].bytes);
    }

    if (c1_cmdDef[sf_mex_lw_bounds_check((int32_T)USRP2CmdFields_ScaleQ, 1, 18)
        - 1].fsize == 0.0) {
      for (c1_i33 = 0; c1_i33 < 23; c1_i33++) {
        c1_c_u[c1_i33] = c1_varargin_1[c1_i33];
      }

      c1_c_y = NULL;
      sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_c_u, 10, 0U, 1U, 0U, 2, 1, 23));
      c1_d_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_ScaleQ;
      for (c1_i33 = 0; c1_i33 < 39; c1_i33++) {
        c1_d_u[c1_i33 + 1] = c1_cv35[c1_i33];
      }

      c1_d_y = NULL;
      sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_d_u, 10, 0U, 1U, 0U, 2, 1, 40));
      sf_mex_call("error", 0U, 2U, 14, c1_c_y, 14, c1_d_y);
    } else {
      c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[(int32_T)
                           USRP2CmdFields_ScaleQ - 1].dtype, c1_scaleQ,
                           c1_cmdDef[sf_mex_lw_bounds_check((int32_T)
        USRP2CmdFields_ScaleQ, 1, 18) - 1].bytes);
    }
  }

  if (c1_b_currCfg_ValidMask != 0) {
    if (c1_cmdDef[sf_mex_lw_bounds_check((int32_T)USRP2CmdFields_Valid, 1, 18) -
        1].fsize == 0.0) {
      for (c1_i33 = 0; c1_i33 < 23; c1_i33++) {
        c1_e_u[c1_i33] = c1_varargin_1[c1_i33];
      }

      c1_e_y = NULL;
      sf_mex_assign(&c1_e_y, sf_mex_create("y", c1_e_u, 10, 0U, 1U, 0U, 2, 1, 23));
      c1_f_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Valid;
      for (c1_i33 = 0; c1_i33 < 39; c1_i33++) {
        c1_f_u[c1_i33 + 1] = c1_cv35[c1_i33];
      }

      c1_f_y = NULL;
      sf_mex_assign(&c1_f_y, sf_mex_create("y", c1_f_u, 10, 0U, 1U, 0U, 2, 1, 40));
      sf_mex_call("error", 0U, 2U, 14, c1_e_y, 14, c1_f_y);
    } else {
      c1_USRP2PackFieldVal(chartInstance, c1_cmdDef[(int32_T)
                           USRP2CmdFields_Valid - 1].dtype, (real_T)
                           c1_b_currCfg_ValidMask,
                           c1_cmdDef[sf_mex_lw_bounds_check((int32_T)
        USRP2CmdFields_Valid, 1, 18) - 1].bytes);
    }

    c1_USRP2Cmd2Pkt(chartInstance, c1_cmdDef, c1_ctrlData, &c1_ctrlLength);
  } else {
    c1_ctrlLength = 0.0;
    for (c1_i33 = 0; c1_i33 < 255; c1_i33++) {
      c1_ctrlData[c1_i33] = 0U;
    }
  }

  chartInstance->c1_lastCF = c1_currCfg_Fc;
  chartInstance->c1_lastG = c1_currCfg_Gain;
  chartInstance->c1_lastDI = c1_currCfg_DecimInterp;
  chartInstance->c1_lastI = c1_scaleI;
  chartInstance->c1_lastQ = c1_scaleQ;
  c1_l_addToQueue(chartInstance, c1_ctrlData, c1_ctrlLength, c1_b_replyQueue,
                  c1_ctrlData[2], (real_T)c1_b_currCfg_ValidMask, c1_currCfg_Fc,
                  c1_currCfg_Gain, c1_currCfg_DecimInterp, c1_scaleI, c1_scaleQ,
                  &c1_repliesOutstanding);
  return c1_repliesOutstanding;
}

static boolean_T c1_b_l_ReceiveReply(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_b_replyQueue[255])
{
  boolean_T c1_replyProcessed;
  char_T *c1_sErr;
  int32_T c1_samplesRead;
  int32_T c1_i34;
  uint8_T c1_uv9[255];
  real_T c1_b_replyId;
  int32_T c1_errStr_sizes[2];
  char_T c1_errStr_data[56];
  int32_T c1_tmp_sizes[2];
  int32_T c1_loop_ub;
  char_T c1_tmp_data[169];
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_expl_temp;
  char_T c1_b_errStr_data[170];
  static char_T c1_cv36[31] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's', ':', 'U',
    'S', 'R', 'P', '2', 'R', 'e', 'c', 'e', 'i', 'v', 'e', 'r', ':', 'R', 'e',
    'p', 'l', 'y', 'E', 'r', 'r' };

  char_T c1_u[31];
  const mxArray *c1_y = NULL;
  char_T c1_u_data[170];
  const mxArray *c1_b_y = NULL;
  int32_T c1_errStr_sizes_idx_1;
  char_T c1_c_errStr_data[170];
  char_T c1_d_errStr_data[170];
  c1_sgyjHZtUMVZuM1aKBgGok1D c1_b_expl_temp;
  c1_replyProcessed = FALSE;

  /* System object Outputs function: dsp.UDPReceiver */
  c1_sErr = GetErrorBuffer(&chartInstance->c1_NetworkLib[0U]);
  c1_samplesRead = 255;
  LibOutputs_Network(&chartInstance->c1_NetworkLib[0U], &chartInstance->c1_Y0[0],
                     &(&c1_samplesRead)[0U]);
  if (*c1_sErr != 0) {
    PrintError(c1_sErr);
  }

  chartInstance->c1_Y1 = (uint16_T)c1_samplesRead;
  for (c1_i34 = 0; c1_i34 < 255; c1_i34++) {
    c1_uv9[c1_i34] = chartInstance->c1_Y0[c1_i34];
  }

  if (chartInstance->c1_Y1 > 0) {
    c1_USRP2RuntimeControlReplies(chartInstance, c1_uv9, chartInstance->c1_Y1,
      c1_errStr_data, c1_errStr_sizes, &c1_b_replyId);
    if (!(c1_errStr_sizes[1] == 0)) {
      c1_tmp_sizes[0] = 1;
      c1_tmp_sizes[1] = c1_errStr_sizes[1];
      c1_loop_ub = c1_errStr_sizes[0] * c1_errStr_sizes[1] - 1;
      for (c1_i34 = 0; c1_i34 <= c1_loop_ub; c1_i34++) {
        c1_tmp_data[c1_i34] = c1_errStr_data[c1_i34];
      }

      c1_expl_temp = c1_b_replyQueue[sf_mex_lw_bounds_check((int32_T)
        c1_b_replyId, 1, 255) - 1];
      c1_l_CheckConfig(chartInstance, c1_tmp_data, c1_tmp_sizes,
                       c1_expl_temp.ValidMask, c1_expl_temp.Fc,
                       c1_expl_temp.Gain, c1_expl_temp.DecimInterp,
                       c1_expl_temp.ScaleI, c1_expl_temp.ScaleQ);
      c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
      for (c1_i34 = 0; c1_i34 <= c1_loop_ub; c1_i34++) {
        c1_b_errStr_data[c1_i34] = c1_tmp_data[c1_i34];
      }

      for (c1_i34 = 0; c1_i34 < 31; c1_i34++) {
        c1_u[c1_i34] = c1_cv36[c1_i34];
      }

      c1_y = NULL;
      sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 31));
      c1_loop_ub = c1_tmp_sizes[1] - 1;
      for (c1_i34 = 0; c1_i34 <= c1_loop_ub; c1_i34++) {
        c1_u_data[c1_i34] = c1_b_errStr_data[c1_i34];
      }

      c1_b_y = NULL;
      sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u_data, 10, 0U, 1U, 0U, 2, 1,
        c1_tmp_sizes[1]));
      sf_mex_call("warning", 0U, 2U, 14, c1_y, 14, c1_b_y);
      c1_errStr_sizes_idx_1 = c1_tmp_sizes[1] + 1;
      c1_loop_ub = c1_tmp_sizes[1] - 1;
      for (c1_i34 = 0; c1_i34 <= c1_loop_ub; c1_i34++) {
        c1_c_errStr_data[c1_i34] = c1_b_errStr_data[c1_i34];
      }

      c1_c_errStr_data[c1_tmp_sizes[1]] = '\x00';
      c1_loop_ub = c1_errStr_sizes_idx_1 - 1;
      for (c1_i34 = 0; c1_i34 <= c1_loop_ub; c1_i34++) {
        c1_b_errStr_data[c1_i34] = c1_c_errStr_data[c1_i34];
      }

      c1_loop_ub = c1_errStr_sizes_idx_1 - 1;
      for (c1_i34 = 0; c1_i34 <= c1_loop_ub; c1_i34++) {
        c1_d_errStr_data[c1_i34] = c1_b_errStr_data[c1_i34];
      }

      PrintError(&c1_d_errStr_data[0]);
    }

    c1_b_expl_temp.ValidMask = 0.0;
    c1_b_expl_temp.Fc = 0.0;
    c1_b_expl_temp.Gain = 0.0;
    c1_b_expl_temp.DecimInterp = 0.0;
    c1_b_expl_temp.ScaleI = 0.0;
    c1_b_expl_temp.ScaleQ = 0.0;
    c1_b_replyQueue[sf_mex_lw_bounds_check((int32_T)c1_b_replyId, 1, 255) - 1] =
      c1_b_expl_temp;
    c1_replyProcessed = TRUE;
  }

  return c1_replyProcessed;
}

static void c1_VRTEncoder(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_s69xIfXV5nXp8sDnVHzDOMB *c1_S, creal_T c1_data[358], uint8_T
  c1_packet_data[1436], int32_T c1_packet_sizes[1])
{
  int32_T c1_i;
  int32_T c1_i35;
  real_T c1_d11;
  int16_T c1_i36;
  int16_T c1_b_data[716];
  uint8_T c1_payload[1432];
  uint8_T c1_tmp;
  c1_s6AmiQ3Zcve7MnsJ9ypFbFH c1_r5;
  uint8_T c1_packet[4];
  c1_i = 0;
  for (c1_i35 = 0; c1_i35 < 358; c1_i35++) {
    c1_d11 = c1_data[c1_i35].re * 32767.0;
    c1_d11 = c1_d11 < 0.0 ? muDoubleScalarCeil(c1_d11 - 0.5) :
      muDoubleScalarFloor(c1_d11 + 0.5);
    if (c1_d11 < 32768.0) {
      if (c1_d11 >= -32768.0) {
        c1_i36 = (int16_T)c1_d11;
      } else {
        c1_i36 = MIN_int16_T;
      }
    } else if (c1_d11 >= 32768.0) {
      c1_i36 = MAX_int16_T;
    } else {
      c1_i36 = 0;
    }

    c1_b_data[c1_i] = c1_i36;
    c1_i += 2;
  }

  c1_i = 0;
  for (c1_i35 = 0; c1_i35 < 358; c1_i35++) {
    c1_d11 = c1_data[c1_i35].im * 32767.0;
    c1_d11 = c1_d11 < 0.0 ? muDoubleScalarCeil(c1_d11 - 0.5) :
      muDoubleScalarFloor(c1_d11 + 0.5);
    if (c1_d11 < 32768.0) {
      if (c1_d11 >= -32768.0) {
        c1_i36 = (int16_T)c1_d11;
      } else {
        c1_i36 = MIN_int16_T;
      }
    } else if (c1_d11 >= 32768.0) {
      c1_i36 = MAX_int16_T;
    } else {
      c1_i36 = 0;
    }

    c1_b_data[c1_i + 1] = c1_i36;
    c1_i += 2;
  }

  memcpy((void *)&c1_payload[0], (void *)&c1_b_data[0], 1432U);
  for (c1_i = 0; c1_i < 1432; c1_i += 2) {
    c1_tmp = c1_payload[c1_i];
    c1_payload[c1_i] = c1_payload[sf_mex_lw_bounds_check(c1_i + 2, 1, 1432) - 1];
    c1_payload[sf_mex_lw_bounds_check(c1_i + 2, 1, 1432) - 1] = c1_tmp;
  }

  c1_VRTSetDataStream(chartInstance, c1_S, 358.0);
  c1_VRTGetDataStream(chartInstance);
  c1_b_VRTGetDataStream(chartInstance);
  c1_r5 = c1_S->stream;
  c1_writeHeader(chartInstance, &c1_r5, 0U, c1_packet);
  c1_S->stream = c1_r5;
  c1_packet_sizes[0] = 1436;
  for (c1_i = 0; c1_i < 4; c1_i++) {
    c1_packet_data[c1_i] = c1_packet[c1_i];
  }

  for (c1_i = 0; c1_i < 1432; c1_i++) {
    c1_packet_data[c1_i + 4] = c1_payload[c1_i];
  }
}

static void c1_VRTSetDataStream(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_s69xIfXV5nXp8sDnVHzDOMB *c1_S, real_T c1_value)
{
  c1_s6AmiQ3Zcve7MnsJ9ypFbFH c1_b_S;
  c1_b_S = c1_S->stream;
  c1_b_S.packetSize = 358U;
  c1_b_S.packetSize = 359U;
  c1_S->stream = c1_b_S;
}

static void c1_writeHeader(SFc1_commsdrhwInstanceStruct *chartInstance,
  c1_s6AmiQ3Zcve7MnsJ9ypFbFH *c1_S, uint8_T c1_h1, uint8_T c1_packet[4])
{
  int32_T c1_i37;
  uint8_T c1_x;
  for (c1_i37 = 0; c1_i37 < 4; c1_i37++) {
    c1_packet[c1_i37] = 0U;
  }

  c1_packet[0] = 0U;
  c1_packet[1] = 0U;
  c1_packet[1] = c1_S->packetCount;
  c1_i37 = (int32_T)((uint32_T)c1_S->packetCount + 1U);
  if ((uint32_T)c1_i37 > 255U) {
    c1_i37 = 255;
  }

  c1_x = (uint8_T)c1_i37;
  c1_S->packetCount = (uint8_T)((uint32_T)c1_x - (uint32_T)((c1_x >> 4) << 4));
  c1_packet[2] = 1U;
  c1_packet[3] = 103U;
}

static void init_dsm_address_info(SFc1_commsdrhwInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c1_commsdrhw_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3739052727U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2312256368U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1547676040U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(219142879U);
}

mxArray *sf_c1_commsdrhw_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(2770505361U);
    pr[1] = (double)(3943138798U);
    pr[2] = (double)(3255647527U);
    pr[3] = (double)(3235203117U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(358);
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

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(1));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(12);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(8000);
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

static const mxArray *sf_get_sim_state_info_c1_commsdrhw(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[5],T\"packet\",},{M[4],M[0],T\"NetworkLib\",},{M[4],M[0],T\"NetworkLib\",},{M[4],M[0],T\"NetworkLib\",},{M[4],M[0],T\"Tx\",S'l','i','p'{{M1x2[167 169],M[0],}}},{M[4],M[0],T\"Y0\",},{M[4],M[0],T\"Y0\",},{M[4],M[0],T\"Y1\",},{M[4],M[0],T\"Y1\",},{M[4],M[0],T\"ctrlReceiver\",S'l','i','p'{{M1x2[181 193],M[0],}}}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[4],M[0],T\"ctrlReceiverBlocking\",S'l','i','p'{{M1x2[194 214],M[0],}}},{M[4],M[0],T\"ctrlSender\",S'l','i','p'{{M1x2[170 180],M[0],}}},{M[4],M[0],T\"lastCF\",S'l','i','p'{{M1x2[1766 1772],M[1],T\"/usr/local/MATLAB/R2011a/toolbox/comm/commutilities/USRP2RuntimeControl.m\"}}},{M[4],M[0],T\"lastDI\",S'l','i','p'{{M1x2[1779 1785],M[1],T\"/usr/local/MATLAB/R2011a/toolbox/comm/commutilities/USRP2RuntimeControl.m\"}}},{M[4],M[0],T\"lastG\",S'l','i','p'{{M1x2[1773 1778],M[1],T\"/usr/local/MATLAB/R2011a/toolbox/comm/commutilities/USRP2RuntimeControl.m\"}}},{M[4],M[0],T\"lastI\",S'l','i','p'{{M1x2[1786 1791],M[1],T\"/usr/local/MATLAB/R2011a/toolbox/comm/commutilities/USRP2RuntimeControl.m\"}}},{M[4],M[0],T\"lastQ\",S'l','i','p'{{M1x2[1792 1797],M[1],T\"/usr/local/MATLAB/R2011a/toolbox/comm/commutilities/USRP2RuntimeControl.m\"}}},{M[4],M[0],T\"replyId\",S'l','i','p'{{M1x2[1180 1187],M[1],T\"/usr/local/MATLAB/R2011a/toolbox/comm/commutilities/private/USRP2Cmd2Pkt.m\"}}},{M[4],M[0],T\"replyQueue\",S'l','i','p'{{M1x2[215 225],M[0],}}},{M[8],M[0],T\"is_active_c1_commsdrhw\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 20, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_commsdrhw_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void sf_opaque_initialize_c1_commsdrhw(void *chartInstanceVar)
{
  initialize_params_c1_commsdrhw((SFc1_commsdrhwInstanceStruct*)
    chartInstanceVar);
  initialize_c1_commsdrhw((SFc1_commsdrhwInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_commsdrhw(void *chartInstanceVar)
{
  enable_c1_commsdrhw((SFc1_commsdrhwInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_commsdrhw(void *chartInstanceVar)
{
  disable_c1_commsdrhw((SFc1_commsdrhwInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_commsdrhw(void *chartInstanceVar)
{
  sf_c1_commsdrhw((SFc1_commsdrhwInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_commsdrhw(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_commsdrhw((SFc1_commsdrhwInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_commsdrhw();/* state var info */
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

extern void sf_internal_set_sim_state_c1_commsdrhw(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_commsdrhw();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_commsdrhw((SFc1_commsdrhwInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_commsdrhw(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_commsdrhw(S);
}

static void sf_opaque_set_sim_state_c1_commsdrhw(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c1_commsdrhw(S, st);
}

static void sf_opaque_terminate_c1_commsdrhw(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_commsdrhwInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c1_commsdrhw((SFc1_commsdrhwInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_commsdrhw((SFc1_commsdrhwInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_commsdrhw(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_commsdrhw((SFc1_commsdrhwInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_commsdrhw(SimStruct *S)
{
  /* Actual parameters from chart:
     HOST_CONTROL_PORT USRP2_CONTROL_PORT USRP2_IP_NUM
   */
  const char_T *rtParamNames[] = { "p1", "p2", "p3" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for HOST_CONTROL_PORT*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);

  /* registration for USRP2_CONTROL_PORT*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_DOUBLE);

  /* registration for USRP2_IP_NUM*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_DOUBLE);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"commsdrhw","DemoUSRPTX",1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"commsdrhw","DemoUSRPTX",1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"commsdrhw","DemoUSRPTX",
      1,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"commsdrhw","DemoUSRPTX",1,4);
      sf_mark_chart_reusable_outputs(S,"commsdrhw","DemoUSRPTX",1,1);
    }

    sf_set_rtw_dwork_info(S,"commsdrhw","DemoUSRPTX",1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(746889091U));
  ssSetChecksum1(S,(561506370U));
  ssSetChecksum2(S,(3699483879U));
  ssSetChecksum3(S,(249772405U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c1_commsdrhw(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "commsdrhw", "DemoUSRPTX",1);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_commsdrhw(SimStruct *S)
{
  SFc1_commsdrhwInstanceStruct *chartInstance;
  chartInstance = (SFc1_commsdrhwInstanceStruct *)malloc(sizeof
    (SFc1_commsdrhwInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_commsdrhwInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_commsdrhw;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_commsdrhw;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_commsdrhw;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_commsdrhw;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_commsdrhw;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_commsdrhw;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_commsdrhw;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_commsdrhw;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_commsdrhw;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_commsdrhw;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_commsdrhw;
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

void c1_commsdrhw_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_commsdrhw(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_commsdrhw(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_commsdrhw(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_commsdrhw_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
