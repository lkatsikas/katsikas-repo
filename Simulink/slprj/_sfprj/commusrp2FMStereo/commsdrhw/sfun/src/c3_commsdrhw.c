/* Include files */

#include "blascompat32.h"
#include "commsdrhw_sfun.h"
#include "c3_commsdrhw.h"
#include <string.h>
#include "mwmathutil.h"

/* Type Definitions */

/* Named Constants */
#define c3_b_USRP2_CONTROL_PORT        (32768.0)
#define c3_b_HOST_CONTROL_PORT         (30002.0)
#define c3_b_USRP2_DATA_PORT           (32769.0)
#define c3_b_HOST_DATA_PORT            (30000.0)
#define c3_b_frameLength               (358.0)
#define c3_b_outputDatatype            (3.0)

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void initialize_c3_commsdrhw(SFc3_commsdrhwInstanceStruct *chartInstance);
static void initialize_params_c3_commsdrhw(SFc3_commsdrhwInstanceStruct
  *chartInstance);
static void enable_c3_commsdrhw(SFc3_commsdrhwInstanceStruct *chartInstance);
static void disable_c3_commsdrhw(SFc3_commsdrhwInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c3_commsdrhw(SFc3_commsdrhwInstanceStruct
  *chartInstance);
static void set_sim_state_c3_commsdrhw(SFc3_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c3_st);
static void finalize_c3_commsdrhw(SFc3_commsdrhwInstanceStruct *chartInstance);
static void sf_c3_commsdrhw(SFc3_commsdrhwInstanceStruct *chartInstance);
static void c3_chartstep_c3_commsdrhw(SFc3_commsdrhwInstanceStruct
  *chartInstance);
static void initSimStructsc3_commsdrhw(SFc3_commsdrhwInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber);
static void c3_VRTDecoder(SFc3_commsdrhwInstanceStruct *chartInstance, char_T
  c3_S_datatype[5], uint8_T *c3_S_hasTrailer, uint32_T *c3_S_trailer, uint8_T
  *c3_S_stream_hasStreamID, uint32_T *c3_S_stream_streamID, uint8_T
  *c3_S_stream_hasClassID, uint32_T c3_S_stream_classID[2], uint8_T
  *c3_S_stream_packetType, uint8_T *c3_S_stream_TSI, uint8_T *c3_S_stream_TSF,
  uint8_T *c3_S_stream_packetCount, uint16_T *c3_S_stream_packetSize);
static void c3_USRP2CmdDef(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_USRP2Opcodes c3_cmd, c3_s7P91ApZ2CkwDPZE5FamWSB c3_cmdDef[18]);
static void c3_l_fdef(SFc3_commsdrhwInstanceStruct *chartInstance, real_T
                      c3_offset, real_T c3_fsize, c3_USRP2FieldDtypes c3_dtype,
                      real_T *c3_s_offset, real_T *c3_s_fsize,
                      c3_USRP2FieldDtypes *c3_s_dtype, uint8_T c3_s_bytes[16]);
static void c3_b_l_fdef(SFc3_commsdrhwInstanceStruct *chartInstance, real_T
  c3_offset, real_T c3_fsize, c3_USRP2FieldDtypes c3_dtype, real_T c3_val,
  real_T *c3_s_offset, real_T *c3_s_fsize, c3_USRP2FieldDtypes *c3_s_dtype,
  uint8_T c3_s_bytes[16]);
static void c3_USRP2PackFieldVal(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_USRP2FieldDtypes c3_dtype, real_T c3_val, uint8_T c3_bytes[16]);
static void c3_USRP2Cmd2Pkt(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_cmdDef[18], uint8_T c3_pkt[255], real_T
  *c3_pktLen);
static void c3_USRP2RuntimeControl(SFc3_commsdrhwInstanceStruct *chartInstance,
  real_T c3_varargin_3, real_T *c3_pktLength, uint8_T c3_pkt[255], uint8_T
  *c3_b_replyId, real_T *c3_varargout_1_ValidMask, real_T *c3_varargout_1_Fc,
  real_T *c3_varargout_1_Gain, real_T *c3_varargout_1_DecimInterp, real_T
  *c3_varargout_1_ScaleI, real_T *c3_varargout_1_ScaleQ);
static void c3_b_USRP2RuntimeControl(SFc3_commsdrhwInstanceStruct *chartInstance,
  real_T c3_varargin_3, real_T *c3_pktLength, uint8_T c3_pkt[255], uint8_T
  *c3_b_replyId, real_T *c3_varargout_1_ValidMask, real_T *c3_varargout_1_Fc,
  real_T *c3_varargout_1_Gain, real_T *c3_varargout_1_DecimInterp, real_T
  *c3_varargout_1_ScaleI, real_T *c3_varargout_1_ScaleQ);
static void c3_c_USRP2RuntimeControl(SFc3_commsdrhwInstanceStruct *chartInstance,
  real_T c3_varargin_3, real_T *c3_pktLength, uint8_T c3_pkt[255], uint8_T
  *c3_b_replyId, real_T *c3_varargout_1_ValidMask, real_T *c3_varargout_1_Fc,
  real_T *c3_varargout_1_Gain, real_T *c3_varargout_1_DecimInterp, real_T
  *c3_varargout_1_ScaleI, real_T *c3_varargout_1_ScaleQ);
static void c3_b_USRP2CmdDef(SFc3_commsdrhwInstanceStruct *chartInstance,
  uint8_T c3_cmd, c3_s7P91ApZ2CkwDPZE5FamWSB c3_cmdDef[18]);
static void c3_USRP2RuntimeControlReplies(SFc3_commsdrhwInstanceStruct
  *chartInstance, uint8_T c3_pkt[255], uint16_T c3_pktLen, char_T
  c3_errStr_data[56], int32_T c3_errStr_sizes[2], real_T *c3_b_replyId);
static real_T c3_USRP2UnpackFieldVal(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_USRP2FieldDtypes c3_dtype, uint8_T c3_bytes[16]);
static void c3_d_USRP2RuntimeControl(SFc3_commsdrhwInstanceStruct *chartInstance,
  real_T *c3_pktLength, uint8_T c3_pkt[255]);
static void c3_e_USRP2RuntimeControl(SFc3_commsdrhwInstanceStruct *chartInstance,
  real_T c3_varargin_3, real_T *c3_pktLength, uint8_T c3_pkt[255], uint8_T
  *c3_b_replyId, real_T *c3_varargout_1_ValidMask, real_T *c3_varargout_1_Fc,
  real_T *c3_varargout_1_Gain, real_T *c3_varargout_1_DecimInterp, real_T
  *c3_varargout_1_ScaleI, real_T *c3_varargout_1_ScaleQ);
static void c3_f_USRP2RuntimeControl(SFc3_commsdrhwInstanceStruct *chartInstance,
  real_T c3_varargin_3, real_T *c3_pktLength, uint8_T c3_pkt[255], uint8_T
  *c3_b_replyId, real_T *c3_varargout_1_ValidMask, real_T *c3_varargout_1_Fc,
  real_T *c3_varargout_1_Gain, real_T *c3_varargout_1_DecimInterp, real_T
  *c3_varargout_1_ScaleI, real_T *c3_varargout_1_ScaleQ);
static void c3_g_USRP2RuntimeControl(SFc3_commsdrhwInstanceStruct *chartInstance,
  real_T c3_varargin_3, real_T *c3_pktLength, uint8_T c3_pkt[255], uint8_T
  *c3_b_replyId, real_T *c3_varargout_1_ValidMask, real_T *c3_varargout_1_Fc,
  real_T *c3_varargout_1_Gain, real_T *c3_varargout_1_DecimInterp, real_T
  *c3_varargout_1_ScaleI, real_T *c3_varargout_1_ScaleQ);
static real_T c3_length(SFc3_commsdrhwInstanceStruct *chartInstance, uint8_T
  c3_x_data[1464], int32_T c3_x_sizes[1]);
static void c3_VRTGetDataStream(SFc3_commsdrhwInstanceStruct *chartInstance,
  char_T c3_S_datatype[5], char_T c3_value[5]);
static boolean_T c3_eml_strcmp(SFc3_commsdrhwInstanceStruct *chartInstance,
  char_T c3_b[5]);
static void c3_typecast(SFc3_commsdrhwInstanceStruct *chartInstance, uint8_T
  c3_x_data[732], int32_T c3_x_sizes[1], int16_T c3_y_data[133956], int32_T
  c3_y_sizes[2]);
static void c3_Update(SFc3_commsdrhwInstanceStruct *chartInstance, uint8_T
                      c3_U0[255], real_T c3_U1);
static void c3_b_Update(SFc3_commsdrhwInstanceStruct *chartInstance, uint8_T
  c3_U0[4], real_T c3_U1);
static void c3_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_data, const char_T *c3_identifier, creal32_T c3_y[358]);
static void c3_b_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, creal32_T c3_y[358]);
static real_T c3_c_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_dataLength, const char_T *c3_identifier);
static real_T c3_d_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static uint8_T c3_e_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_overrun, const char_T *c3_identifier);
static uint8_T c3_f_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_g_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_e_NetworkLib, const char_T *c3_identifier, real_T c3_y[137]);
static void c3_h_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[137]);
static void c3_i_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_e_NetworkLib, const char_T *c3_identifier, real_T c3_y[137]);
static void c3_j_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[137]);
static void c3_k_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_e_NetworkLib, const char_T *c3_identifier, real_T c3_y[137]);
static void c3_l_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[137]);
static void c3_m_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_e_NetworkLib, const char_T *c3_identifier, real_T c3_y[137]);
static void c3_n_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[137]);
static void c3_o_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_Recv, const char_T *c3_identifier, char_T c3_y_datatype[5],
  uint8_T *c3_y_hasTrailer, uint32_T *c3_y_trailer, uint8_T
  *c3_y_stream_hasStreamID, uint32_T *c3_y_stream_streamID, uint8_T
  *c3_y_stream_hasClassID, uint32_T c3_y_stream_classID[2], uint8_T
  *c3_y_stream_packetType, uint8_T *c3_y_stream_TSI, uint8_T *c3_y_stream_TSF,
  uint8_T *c3_y_stream_packetCount, uint16_T *c3_y_stream_packetSize);
static void c3_p_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, char_T
  c3_y_datatype[5], uint8_T *c3_y_hasTrailer, uint32_T *c3_y_trailer, uint8_T
  *c3_y_stream_hasStreamID, uint32_T *c3_y_stream_streamID, uint8_T
  *c3_y_stream_hasClassID, uint32_T c3_y_stream_classID[2], uint8_T
  *c3_y_stream_packetType, uint8_T *c3_y_stream_TSI, uint8_T *c3_y_stream_TSF,
  uint8_T *c3_y_stream_packetCount, uint16_T *c3_y_stream_packetSize);
static void c3_q_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, char_T c3_y[5]);
static uint32_T c3_r_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_s_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T
  *c3_y_hasStreamID, uint32_T *c3_y_streamID, uint8_T *c3_y_hasClassID, uint32_T
  c3_y_classID[2], uint8_T *c3_y_packetType, uint8_T *c3_y_TSI, uint8_T
  *c3_y_TSF, uint8_T *c3_y_packetCount, uint16_T *c3_y_packetSize);
static void c3_t_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint32_T c3_y[2]);
static uint16_T c3_u_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_v_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_c_Y0, const char_T *c3_identifier, uint8_T c3_y[255]);
static void c3_w_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_y[255]);
static void c3_x_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_c_Y0, const char_T *c3_identifier, uint8_T c3_y[255]);
static void c3_y_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_y[255]);
static uint16_T c3_ab_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c3_c_Y1, const char_T *c3_identifier);
static uint16_T c3_bb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static uint16_T c3_cb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c3_c_Y1, const char_T *c3_identifier);
static uint16_T c3_db_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_eb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_ctrlReceiver, const char_T *c3_identifier);
static void c3_fb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_gb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_ctrlReceiverBlocking, const char_T *c3_identifier);
static void c3_hb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_ib_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_ctrlSender, const char_T *c3_identifier);
static void c3_jb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static real_T c3_kb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_dataLength, const char_T *c3_identifier);
static real_T c3_lb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_mb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_dataSender, const char_T *c3_identifier);
static void c3_nb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_ob_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_imagData, const char_T *c3_identifier, uint8_T c3_y_data[732],
  int32_T c3_y_sizes[1]);
static void c3_pb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_y_data
  [732], int32_T c3_y_sizes[1]);
static real_T c3_qb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_lastCF, const char_T *c3_identifier);
static real_T c3_rb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static real_T c3_sb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_lastDI, const char_T *c3_identifier);
static real_T c3_tb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static real_T c3_ub_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_lastG, const char_T *c3_identifier);
static real_T c3_vb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static real_T c3_wb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_lastI, const char_T *c3_identifier);
static real_T c3_xb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static real_T c3_yb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_lastQ, const char_T *c3_identifier);
static real_T c3_ac_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_bc_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_realData, const char_T *c3_identifier, uint8_T c3_y_data[732],
  int32_T c3_y_sizes[1]);
static void c3_cc_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_y_data
  [732], int32_T c3_y_sizes[1]);
static real_T c3_dc_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_replyId, const char_T *c3_identifier);
static real_T c3_ec_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_fc_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_replyQueue, const char_T *c3_identifier,
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_y[255]);
static void c3_gc_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_y[255]);
static real_T c3_l_SendConfig(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_b_replyQueue[255], real_T c3_centerFreq, real_T
  c3_gain, real_T c3_decimation);
static void c3_l_addToQueue(SFc3_commsdrhwInstanceStruct *chartInstance, uint8_T
  c3_ctrlData[255], real_T c3_ctrlLength, c3_sgyjHZtUMVZuM1aKBgGok1D
  c3_b_replyQueue[255], uint8_T c3_b_replyId, real_T c3_currCfg_ValidMask,
  real_T c3_currCfg_Fc, real_T c3_currCfg_Gain, real_T c3_currCfg_DecimInterp,
  real_T c3_currCfg_ScaleI, real_T c3_currCfg_ScaleQ, real_T
  *c3_repliesOutstanding);
static boolean_T c3_l_ReceiveReply(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_b_replyQueue[255]);
static void c3_l_CheckConfig(SFc3_commsdrhwInstanceStruct *chartInstance, char_T
  c3_errStr_data[166], int32_T c3_errStr_sizes[2], real_T c3_cfgEntry_ValidMask,
  real_T c3_cfgEntry_Fc, real_T c3_cfgEntry_Gain, real_T c3_cfgEntry_DecimInterp,
  real_T c3_cfgEntry_ScaleI, real_T c3_cfgEntry_ScaleQ);
static void c3_b_l_SendConfig(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_b_replyQueue[255], real_T c3_centerFreq, real_T
  c3_gain, real_T c3_decimation);
static boolean_T c3_b_l_ReceiveReply(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_b_replyQueue[255]);
static void c3_b_VRTDecoder(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_s69xIfXV5nXp8sDnVHzDOMB *c3_S, uint8_T c3_packet_data[1464], int32_T
  c3_packet_sizes[1], cint16_T c3_data_data[366], int32_T c3_data_sizes[1],
  real_T *c3_b_dataLength, char_T c3_err_data[24], int32_T c3_err_sizes[2]);
static void c3_readCommonBits(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_s69xIfXV5nXp8sDnVHzDOMB *c3_S, uint8_T c3_hdr[4], uint8_T c3_packet_data
  [1464], int32_T c3_packet_sizes[1], boolean_T c3_hasStreamID, uint8_T
  c3_hasTrailer, char_T c3_err_data[22], int32_T c3_err_sizes[2], uint16_T
  *c3_len, uint8_T c3_payload_data[1464], int32_T c3_payload_sizes[1]);
static void c3_extractPayload(SFc3_commsdrhwInstanceStruct *chartInstance,
  uint16_T c3_S_packetSize, uint8_T c3_packet_data[1464], int32_T
  c3_packet_sizes[1], real_T c3_len, uint8_T c3_hasTrailer, char_T c3_err_data
  [22], int32_T c3_err_sizes[2], uint8_T c3_payload_data[1464], int32_T
  c3_payload_sizes[1], uint16_T *c3_b_len);
static void c3_readIFDataPacket(SFc3_commsdrhwInstanceStruct *chartInstance,
  char_T c3_S_datatype[5], uint8_T c3_payload_data[1464], int32_T
  c3_payload_sizes[1], char_T c3_err_data[24], int32_T c3_err_sizes[2], cint16_T
  c3_data_data[366], int32_T c3_data_sizes[1]);
static void init_dsm_address_info(SFc3_commsdrhwInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c3_commsdrhw(SFc3_commsdrhwInstanceStruct *chartInstance)
{
  char_T *c3_sErr;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c3_Recv_not_empty = FALSE;
  chartInstance->c3_ctrlSender_not_empty = FALSE;
  chartInstance->c3_ctrlReceiver_not_empty = FALSE;
  chartInstance->c3_dataSender_not_empty = FALSE;
  chartInstance->c3_replyQueue_not_empty = FALSE;
  chartInstance->c3_ctrlReceiverBlocking_not_empty = FALSE;
  chartInstance->c3_realData_not_empty = FALSE;
  chartInstance->c3_imagData_not_empty = FALSE;
  chartInstance->c3_dataLength_not_empty = FALSE;
  chartInstance->c3_lastCF_not_empty = FALSE;
  chartInstance->c3_lastG_not_empty = FALSE;
  chartInstance->c3_lastDI_not_empty = FALSE;
  chartInstance->c3_lastI_not_empty = FALSE;
  chartInstance->c3_lastQ_not_empty = FALSE;
  chartInstance->c3_replyId_not_empty = FALSE;
  chartInstance->c3_is_active_c3_commsdrhw = 0U;
  if (!ssIsExternalSim(chartInstance->S)) {
    c3_sErr = GetErrorBuffer(&chartInstance->c3_NetworkLib[0U]);
    CreateUDPInterface(&chartInstance->c3_NetworkLib[0U]);
    if (*c3_sErr == 0) {
      LibCreate_Network(&chartInstance->c3_NetworkLib[0U], 0, "0.0.0.0", 30002,
                        "192.168.10.255", -1, 8192, 1, 0);
    }

    if (*c3_sErr == 0) {
      LibStart(&chartInstance->c3_NetworkLib[0U]);
    }

    if (*c3_sErr != 0) {
      DestroyUDPInterface(&chartInstance->c3_NetworkLib[0U]);
      if (*c3_sErr != 0) {
        PrintError(c3_sErr);
      }
    }
  }

  if (!ssIsExternalSim(chartInstance->S)) {
    c3_sErr = GetErrorBuffer(&chartInstance->c3_b_NetworkLib[0U]);
    CreateUDPInterface(&chartInstance->c3_b_NetworkLib[0U]);
    if (*c3_sErr == 0) {
      LibCreate_Network(&chartInstance->c3_b_NetworkLib[0U], 0, "0.0.0.0", 30002,
                        "192.168.10.255", -1, 8192, 1, 100);
    }

    if (*c3_sErr == 0) {
      LibStart(&chartInstance->c3_b_NetworkLib[0U]);
    }

    if (*c3_sErr != 0) {
      DestroyUDPInterface(&chartInstance->c3_b_NetworkLib[0U]);
      if (*c3_sErr != 0) {
        PrintError(c3_sErr);
      }
    }
  }

  if (!ssIsExternalSim(chartInstance->S)) {
    c3_sErr = GetErrorBuffer(&chartInstance->c3_c_NetworkLib[0U]);
    CreateUDPInterface(&chartInstance->c3_c_NetworkLib[0U]);
    if (*c3_sErr == 0) {
      LibCreate_Network(&chartInstance->c3_c_NetworkLib[0U], 1, "0.0.0.0", 30002,
                        "192.168.10.255", 32768, 8192, 1, 0);
    }

    if (*c3_sErr == 0) {
      LibStart(&chartInstance->c3_c_NetworkLib[0U]);
    }

    if (*c3_sErr != 0) {
      DestroyUDPInterface(&chartInstance->c3_c_NetworkLib[0U]);
      if (*c3_sErr != 0) {
        PrintError(c3_sErr);
      }
    }
  }

  if (!ssIsExternalSim(chartInstance->S)) {
    c3_sErr = GetErrorBuffer(&chartInstance->c3_d_NetworkLib[0U]);
    CreateUDPInterface(&chartInstance->c3_d_NetworkLib[0U]);
    if (*c3_sErr == 0) {
      LibCreate_Network(&chartInstance->c3_d_NetworkLib[0U], 1, "0.0.0.0", 30000,
                        "192.168.10.255", 32769, 8192, 1, 0);
    }

    if (*c3_sErr == 0) {
      LibStart(&chartInstance->c3_d_NetworkLib[0U]);
    }

    if (*c3_sErr != 0) {
      DestroyUDPInterface(&chartInstance->c3_d_NetworkLib[0U]);
      if (*c3_sErr != 0) {
        PrintError(c3_sErr);
      }
    }
  }

  chartInstance->c3_replyId = 1.0;
  chartInstance->c3_lastCF = 0.0;
  chartInstance->c3_lastG = 0.0;
  chartInstance->c3_lastDI = 0.0;
  chartInstance->c3_lastI = 0.0;
  chartInstance->c3_lastQ = 0.0;
}

static void initialize_params_c3_commsdrhw(SFc3_commsdrhwInstanceStruct
  *chartInstance)
{
  real_T c3_d0;
  real_T c3_d1;
  real_T c3_d2;
  real_T c3_d3;
  real_T c3_dv0[14];
  int32_T c3_i0;
  real_T c3_d4;
  real_T c3_d5;
  sf_set_error_prefix_string(
    "Error evaluating data 'HOST_DATA_PORT' in the parent workspace.\n");
  sf_mex_import_named("HOST_DATA_PORT", sf_mex_get_sfun_param(chartInstance->S,
    1, 0), &c3_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_HOST_DATA_PORT = c3_d0;
  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  sf_set_error_prefix_string(
    "Error evaluating data 'USRP2_DATA_PORT' in the parent workspace.\n");
  sf_mex_import_named("USRP2_DATA_PORT", sf_mex_get_sfun_param(chartInstance->S,
    3, 0), &c3_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_USRP2_DATA_PORT = c3_d1;
  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  sf_set_error_prefix_string(
    "Error evaluating data 'HOST_CONTROL_PORT' in the parent workspace.\n");
  sf_mex_import_named("HOST_CONTROL_PORT", sf_mex_get_sfun_param
                      (chartInstance->S, 0, 0), &c3_d2, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_HOST_CONTROL_PORT = c3_d2;
  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  sf_set_error_prefix_string(
    "Error evaluating data 'USRP2_CONTROL_PORT' in the parent workspace.\n");
  sf_mex_import_named("USRP2_CONTROL_PORT", sf_mex_get_sfun_param
                      (chartInstance->S, 2, 0), &c3_d3, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_USRP2_CONTROL_PORT = c3_d3;
  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  sf_set_error_prefix_string(
    "Error evaluating data 'USRP2_IP_NUM' in the parent workspace.\n");
  sf_mex_import_named("USRP2_IP_NUM", sf_mex_get_sfun_param(chartInstance->S, 4,
    0), c3_dv0, 0, 0, 0U, 1, 0U, 2, 1, 14);
  for (c3_i0 = 0; c3_i0 < 14; c3_i0++) {
    chartInstance->c3_USRP2_IP_NUM[c3_i0] = c3_dv0[c3_i0];
  }

  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  sf_set_error_prefix_string(
    "Error evaluating data 'frameLength' in the parent workspace.\n");
  sf_mex_import_named("frameLength", sf_mex_get_sfun_param(chartInstance->S, 5,
    0), &c3_d4, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_frameLength = c3_d4;
  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
  sf_set_error_prefix_string(
    "Error evaluating data 'outputDatatype' in the parent workspace.\n");
  sf_mex_import_named("outputDatatype", sf_mex_get_sfun_param(chartInstance->S,
    6, 0), &c3_d5, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_outputDatatype = c3_d5;
  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
}

static void enable_c3_commsdrhw(SFc3_commsdrhwInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c3_commsdrhw(SFc3_commsdrhwInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static const mxArray *get_sim_state_c3_commsdrhw(SFc3_commsdrhwInstanceStruct
  *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  int32_T c3_i1;
  creal32_T c3_u[358];
  const mxArray *c3_b_y = NULL;
  real_T c3_b_u;
  const mxArray *c3_c_y = NULL;
  uint8_T c3_c_u;
  const mxArray *c3_d_y = NULL;
  real_T c3_d_u[137];
  const mxArray *c3_e_y = NULL;
  real_T c3_e_u[137];
  const mxArray *c3_f_y = NULL;
  real_T c3_f_u[137];
  const mxArray *c3_g_y = NULL;
  real_T c3_g_u[137];
  const mxArray *c3_h_y = NULL;
  char_T c3_u_datatype[5];
  uint8_T c3_u_hasTrailer;
  uint32_T c3_u_trailer;
  uint8_T c3_u_stream_hasStreamID;
  uint32_T c3_u_stream_streamID;
  uint8_T c3_u_stream_hasClassID;
  uint32_T c3_u_stream_classID[2];
  uint8_T c3_u_stream_packetType;
  uint8_T c3_u_stream_TSI;
  uint8_T c3_u_stream_TSF;
  uint8_T c3_u_stream_packetCount;
  uint16_T c3_u_stream_packetSize;
  const mxArray *c3_i_y = NULL;
  char_T c3_h_u[5];
  const mxArray *c3_j_y = NULL;
  uint8_T c3_i_u;
  const mxArray *c3_k_y = NULL;
  uint32_T c3_j_u;
  const mxArray *c3_l_y = NULL;
  const mxArray *c3_m_y = NULL;
  uint8_T c3_k_u;
  const mxArray *c3_n_y = NULL;
  uint32_T c3_l_u;
  const mxArray *c3_o_y = NULL;
  uint8_T c3_m_u;
  const mxArray *c3_p_y = NULL;
  uint32_T c3_n_u[2];
  const mxArray *c3_q_y = NULL;
  uint8_T c3_o_u;
  const mxArray *c3_r_y = NULL;
  uint8_T c3_p_u;
  const mxArray *c3_s_y = NULL;
  uint8_T c3_q_u;
  const mxArray *c3_t_y = NULL;
  uint8_T c3_r_u;
  const mxArray *c3_u_y = NULL;
  uint16_T c3_s_u;
  const mxArray *c3_v_y = NULL;
  uint8_T c3_t_u[255];
  const mxArray *c3_w_y = NULL;
  uint8_T c3_u_u[255];
  const mxArray *c3_x_y = NULL;
  uint16_T c3_v_u;
  const mxArray *c3_y_y = NULL;
  uint16_T c3_w_u;
  const mxArray *c3_ab_y = NULL;
  const mxArray *c3_bb_y = NULL;
  const mxArray *c3_cb_y = NULL;
  const mxArray *c3_db_y = NULL;
  real_T c3_x_u;
  const mxArray *c3_eb_y = NULL;
  const mxArray *c3_fb_y = NULL;
  int32_T c3_loop_ub;
  uint8_T c3_u_data[732];
  const mxArray *c3_gb_y = NULL;
  real_T c3_y_u;
  const mxArray *c3_hb_y = NULL;
  real_T c3_ab_u;
  const mxArray *c3_ib_y = NULL;
  real_T c3_bb_u;
  const mxArray *c3_jb_y = NULL;
  real_T c3_cb_u;
  const mxArray *c3_kb_y = NULL;
  real_T c3_db_u;
  const mxArray *c3_lb_y = NULL;
  uint8_T c3_b_u_data[732];
  const mxArray *c3_mb_y = NULL;
  real_T c3_eb_u;
  const mxArray *c3_nb_y = NULL;
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_fb_u[255];
  const mxArray *c3_ob_y = NULL;
  int32_T c3_iv0[2];
  c3_sgyjHZtUMVZuM1aKBgGok1D *c3_r0;
  real_T c3_gb_u;
  const mxArray *c3_pb_y = NULL;
  real_T c3_hb_u;
  const mxArray *c3_qb_y = NULL;
  real_T c3_ib_u;
  const mxArray *c3_rb_y = NULL;
  real_T c3_jb_u;
  const mxArray *c3_sb_y = NULL;
  real_T c3_kb_u;
  const mxArray *c3_tb_y = NULL;
  real_T c3_lb_u;
  const mxArray *c3_ub_y = NULL;
  uint8_T c3_mb_u;
  const mxArray *c3_vb_y = NULL;
  real_T *c3_b_dataLength;
  uint8_T *c3_overrun;
  creal32_T (*c3_data)[358];
  c3_overrun = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c3_b_dataLength = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c3_data = (creal32_T (*)[358])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellarray(27));
  for (c3_i1 = 0; c3_i1 < 358; c3_i1++) {
    c3_u[c3_i1] = (*c3_data)[c3_i1];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_u, 1, 1U, 1U, 0U, 2, 358, 1));
  sf_mex_setcell(c3_y, 0, c3_b_y);
  c3_b_u = *c3_b_dataLength;
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", &c3_b_u, 0, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 1, c3_c_y);
  c3_c_u = *c3_overrun;
  c3_d_y = NULL;
  sf_mex_assign(&c3_d_y, sf_mex_create("y", &c3_c_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 2, c3_d_y);
  for (c3_i1 = 0; c3_i1 < 137; c3_i1++) {
    c3_d_u[c3_i1] = chartInstance->c3_NetworkLib[c3_i1];
  }

  c3_e_y = NULL;
  sf_mex_assign(&c3_e_y, sf_mex_create("y", c3_d_u, 0, 0U, 1U, 0U, 1, 137));
  sf_mex_setcell(c3_y, 3, c3_e_y);
  for (c3_i1 = 0; c3_i1 < 137; c3_i1++) {
    c3_e_u[c3_i1] = chartInstance->c3_b_NetworkLib[c3_i1];
  }

  c3_f_y = NULL;
  sf_mex_assign(&c3_f_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 1, 137));
  sf_mex_setcell(c3_y, 4, c3_f_y);
  for (c3_i1 = 0; c3_i1 < 137; c3_i1++) {
    c3_f_u[c3_i1] = chartInstance->c3_c_NetworkLib[c3_i1];
  }

  c3_g_y = NULL;
  sf_mex_assign(&c3_g_y, sf_mex_create("y", c3_f_u, 0, 0U, 1U, 0U, 1, 137));
  sf_mex_setcell(c3_y, 5, c3_g_y);
  for (c3_i1 = 0; c3_i1 < 137; c3_i1++) {
    c3_g_u[c3_i1] = chartInstance->c3_d_NetworkLib[c3_i1];
  }

  c3_h_y = NULL;
  sf_mex_assign(&c3_h_y, sf_mex_create("y", c3_g_u, 0, 0U, 1U, 0U, 1, 137));
  sf_mex_setcell(c3_y, 6, c3_h_y);
  for (c3_i1 = 0; c3_i1 < 5; c3_i1++) {
    c3_u_datatype[c3_i1] = chartInstance->c3_Recv.datatype[c3_i1];
  }

  c3_u_hasTrailer = chartInstance->c3_Recv.hasTrailer;
  c3_u_trailer = chartInstance->c3_Recv.trailer;
  c3_u_stream_hasStreamID = chartInstance->c3_Recv.stream.hasStreamID;
  c3_u_stream_streamID = chartInstance->c3_Recv.stream.streamID;
  c3_u_stream_hasClassID = chartInstance->c3_Recv.stream.hasClassID;
  for (c3_i1 = 0; c3_i1 < 2; c3_i1++) {
    c3_u_stream_classID[c3_i1] = chartInstance->c3_Recv.stream.classID[c3_i1];
  }

  c3_u_stream_packetType = chartInstance->c3_Recv.stream.packetType;
  c3_u_stream_TSI = chartInstance->c3_Recv.stream.TSI;
  c3_u_stream_TSF = chartInstance->c3_Recv.stream.TSF;
  c3_u_stream_packetCount = chartInstance->c3_Recv.stream.packetCount;
  c3_u_stream_packetSize = chartInstance->c3_Recv.stream.packetSize;
  c3_i_y = NULL;
  if (!chartInstance->c3_Recv_not_empty) {
    sf_mex_assign(&c3_i_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c3_i_y, sf_mex_createstruct("structure", 2, 1, 1));
    for (c3_i1 = 0; c3_i1 < 5; c3_i1++) {
      c3_h_u[c3_i1] = c3_u_datatype[c3_i1];
    }

    c3_j_y = NULL;
    sf_mex_assign(&c3_j_y, sf_mex_create("y", c3_h_u, 10, 0U, 1U, 0U, 2, 1, 5));
    sf_mex_addfield(c3_i_y, c3_j_y, "datatype", "datatype", 0);
    c3_i_u = c3_u_hasTrailer;
    c3_k_y = NULL;
    sf_mex_assign(&c3_k_y, sf_mex_create("y", &c3_i_u, 3, 0U, 0U, 0U, 0));
    sf_mex_addfield(c3_i_y, c3_k_y, "hasTrailer", "hasTrailer", 0);
    c3_j_u = c3_u_trailer;
    c3_l_y = NULL;
    sf_mex_assign(&c3_l_y, sf_mex_create("y", &c3_j_u, 7, 0U, 0U, 0U, 0));
    sf_mex_addfield(c3_i_y, c3_l_y, "trailer", "trailer", 0);
    c3_m_y = NULL;
    sf_mex_assign(&c3_m_y, sf_mex_createstruct("structure", 2, 1, 1));
    c3_k_u = c3_u_stream_hasStreamID;
    c3_n_y = NULL;
    sf_mex_assign(&c3_n_y, sf_mex_create("y", &c3_k_u, 3, 0U, 0U, 0U, 0));
    sf_mex_addfield(c3_m_y, c3_n_y, "hasStreamID", "hasStreamID", 0);
    c3_l_u = c3_u_stream_streamID;
    c3_o_y = NULL;
    sf_mex_assign(&c3_o_y, sf_mex_create("y", &c3_l_u, 7, 0U, 0U, 0U, 0));
    sf_mex_addfield(c3_m_y, c3_o_y, "streamID", "streamID", 0);
    c3_m_u = c3_u_stream_hasClassID;
    c3_p_y = NULL;
    sf_mex_assign(&c3_p_y, sf_mex_create("y", &c3_m_u, 3, 0U, 0U, 0U, 0));
    sf_mex_addfield(c3_m_y, c3_p_y, "hasClassID", "hasClassID", 0);
    for (c3_i1 = 0; c3_i1 < 2; c3_i1++) {
      c3_n_u[c3_i1] = c3_u_stream_classID[c3_i1];
    }

    c3_q_y = NULL;
    sf_mex_assign(&c3_q_y, sf_mex_create("y", c3_n_u, 7, 0U, 1U, 0U, 2, 1, 2));
    sf_mex_addfield(c3_m_y, c3_q_y, "classID", "classID", 0);
    c3_o_u = c3_u_stream_packetType;
    c3_r_y = NULL;
    sf_mex_assign(&c3_r_y, sf_mex_create("y", &c3_o_u, 3, 0U, 0U, 0U, 0));
    sf_mex_addfield(c3_m_y, c3_r_y, "packetType", "packetType", 0);
    c3_p_u = c3_u_stream_TSI;
    c3_s_y = NULL;
    sf_mex_assign(&c3_s_y, sf_mex_create("y", &c3_p_u, 3, 0U, 0U, 0U, 0));
    sf_mex_addfield(c3_m_y, c3_s_y, "TSI", "TSI", 0);
    c3_q_u = c3_u_stream_TSF;
    c3_t_y = NULL;
    sf_mex_assign(&c3_t_y, sf_mex_create("y", &c3_q_u, 3, 0U, 0U, 0U, 0));
    sf_mex_addfield(c3_m_y, c3_t_y, "TSF", "TSF", 0);
    c3_r_u = c3_u_stream_packetCount;
    c3_u_y = NULL;
    sf_mex_assign(&c3_u_y, sf_mex_create("y", &c3_r_u, 3, 0U, 0U, 0U, 0));
    sf_mex_addfield(c3_m_y, c3_u_y, "packetCount", "packetCount", 0);
    c3_s_u = c3_u_stream_packetSize;
    c3_v_y = NULL;
    sf_mex_assign(&c3_v_y, sf_mex_create("y", &c3_s_u, 5, 0U, 0U, 0U, 0));
    sf_mex_addfield(c3_m_y, c3_v_y, "packetSize", "packetSize", 0);
    sf_mex_addfield(c3_i_y, c3_m_y, "stream", "stream", 0);
  }

  sf_mex_setcell(c3_y, 7, c3_i_y);
  for (c3_i1 = 0; c3_i1 < 255; c3_i1++) {
    c3_t_u[c3_i1] = chartInstance->c3_Y0[c3_i1];
  }

  c3_w_y = NULL;
  sf_mex_assign(&c3_w_y, sf_mex_create("y", c3_t_u, 3, 0U, 1U, 0U, 2, 255, 1));
  sf_mex_setcell(c3_y, 8, c3_w_y);
  for (c3_i1 = 0; c3_i1 < 255; c3_i1++) {
    c3_u_u[c3_i1] = chartInstance->c3_b_Y0[c3_i1];
  }

  c3_x_y = NULL;
  sf_mex_assign(&c3_x_y, sf_mex_create("y", c3_u_u, 3, 0U, 1U, 0U, 2, 255, 1));
  sf_mex_setcell(c3_y, 9, c3_x_y);
  c3_v_u = chartInstance->c3_Y1;
  c3_y_y = NULL;
  sf_mex_assign(&c3_y_y, sf_mex_create("y", &c3_v_u, 5, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 10, c3_y_y);
  c3_w_u = chartInstance->c3_b_Y1;
  c3_ab_y = NULL;
  sf_mex_assign(&c3_ab_y, sf_mex_create("y", &c3_w_u, 5, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 11, c3_ab_y);
  c3_bb_y = NULL;
  if (!chartInstance->c3_ctrlReceiver_not_empty) {
    sf_mex_assign(&c3_bb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c3_bb_y, sf_mex_call("dsp.UDPReceiver", 1U, 4U, 15,
      "LocalIPPort", 6, 30002.0, 15, "RemoteIPAddress", 15, "192.168.10.255"));
  }

  sf_mex_setcell(c3_y, 12, c3_bb_y);
  c3_cb_y = NULL;
  if (!chartInstance->c3_ctrlReceiverBlocking_not_empty) {
    sf_mex_assign(&c3_cb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c3_cb_y, sf_mex_call("dsp.UDPReceiver", 1U, 4U, 15,
      "LocalIPPort", 6, 30002.0, 15, "RemoteIPAddress", 15, "192.168.10.255"));
  }

  sf_mex_setcell(c3_y, 13, c3_cb_y);
  c3_db_y = NULL;
  if (!chartInstance->c3_ctrlSender_not_empty) {
    sf_mex_assign(&c3_db_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c3_db_y, sf_mex_call("dsp.UDPSender", 1U, 8U, 15,
      "RemoteIPAddress", 15, "192.168.10.255", 15, "RemoteIPPort", 6, 32768.0,
      15, "LocalIPPortSource", 15, "Property", 15, "LocalIPPort", 6, 30002.0));
  }

  sf_mex_setcell(c3_y, 14, c3_db_y);
  c3_x_u = chartInstance->c3_dataLength;
  c3_eb_y = NULL;
  if (!chartInstance->c3_dataLength_not_empty) {
    sf_mex_assign(&c3_eb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c3_eb_y, sf_mex_create("y", &c3_x_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c3_y, 15, c3_eb_y);
  c3_fb_y = NULL;
  if (!chartInstance->c3_dataSender_not_empty) {
    sf_mex_assign(&c3_fb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c3_fb_y, sf_mex_call("dsp.UDPSender", 1U, 8U, 15,
      "RemoteIPAddress", 15, "192.168.10.255", 15, "RemoteIPPort", 6, 32769.0,
      15, "LocalIPPortSource", 15, "Property", 15, "LocalIPPort", 6, 30000.0));
  }

  sf_mex_setcell(c3_y, 16, c3_fb_y);
  c3_loop_ub = chartInstance->c3_imagData_sizes - 1;
  for (c3_i1 = 0; c3_i1 <= c3_loop_ub; c3_i1++) {
    c3_u_data[c3_i1] = chartInstance->c3_imagData_data[c3_i1];
  }

  c3_gb_y = NULL;
  if (!chartInstance->c3_imagData_not_empty) {
    sf_mex_assign(&c3_gb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c3_gb_y, sf_mex_create("y", c3_u_data, 3, 0U, 1U, 0U, 1,
      chartInstance->c3_imagData_sizes));
  }

  sf_mex_setcell(c3_y, 17, c3_gb_y);
  c3_y_u = chartInstance->c3_lastCF;
  c3_hb_y = NULL;
  if (!chartInstance->c3_lastCF_not_empty) {
    sf_mex_assign(&c3_hb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c3_hb_y, sf_mex_create("y", &c3_y_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c3_y, 18, c3_hb_y);
  c3_ab_u = chartInstance->c3_lastDI;
  c3_ib_y = NULL;
  if (!chartInstance->c3_lastDI_not_empty) {
    sf_mex_assign(&c3_ib_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c3_ib_y, sf_mex_create("y", &c3_ab_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c3_y, 19, c3_ib_y);
  c3_bb_u = chartInstance->c3_lastG;
  c3_jb_y = NULL;
  if (!chartInstance->c3_lastG_not_empty) {
    sf_mex_assign(&c3_jb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c3_jb_y, sf_mex_create("y", &c3_bb_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c3_y, 20, c3_jb_y);
  c3_cb_u = chartInstance->c3_lastI;
  c3_kb_y = NULL;
  if (!chartInstance->c3_lastI_not_empty) {
    sf_mex_assign(&c3_kb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c3_kb_y, sf_mex_create("y", &c3_cb_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c3_y, 21, c3_kb_y);
  c3_db_u = chartInstance->c3_lastQ;
  c3_lb_y = NULL;
  if (!chartInstance->c3_lastQ_not_empty) {
    sf_mex_assign(&c3_lb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c3_lb_y, sf_mex_create("y", &c3_db_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c3_y, 22, c3_lb_y);
  c3_loop_ub = chartInstance->c3_realData_sizes - 1;
  for (c3_i1 = 0; c3_i1 <= c3_loop_ub; c3_i1++) {
    c3_b_u_data[c3_i1] = chartInstance->c3_realData_data[c3_i1];
  }

  c3_mb_y = NULL;
  if (!chartInstance->c3_realData_not_empty) {
    sf_mex_assign(&c3_mb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c3_mb_y, sf_mex_create("y", c3_b_u_data, 3, 0U, 1U, 0U, 1,
      chartInstance->c3_realData_sizes));
  }

  sf_mex_setcell(c3_y, 23, c3_mb_y);
  c3_eb_u = chartInstance->c3_replyId;
  c3_nb_y = NULL;
  if (!chartInstance->c3_replyId_not_empty) {
    sf_mex_assign(&c3_nb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c3_nb_y, sf_mex_create("y", &c3_eb_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c3_y, 24, c3_nb_y);
  for (c3_i1 = 0; c3_i1 < 255; c3_i1++) {
    c3_fb_u[c3_i1] = chartInstance->c3_replyQueue[c3_i1];
  }

  c3_ob_y = NULL;
  if (!chartInstance->c3_replyQueue_not_empty) {
    sf_mex_assign(&c3_ob_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    for (c3_i1 = 0; c3_i1 < 2; c3_i1++) {
      c3_iv0[c3_i1] = 1 + 254 * c3_i1;
    }

    sf_mex_assign(&c3_ob_y, sf_mex_createstructarray("structure", 2, c3_iv0));
    for (c3_i1 = 0; c3_i1 < 255; c3_i1++) {
      c3_r0 = &c3_fb_u[c3_i1];
      c3_gb_u = c3_r0->ValidMask;
      c3_pb_y = NULL;
      sf_mex_assign(&c3_pb_y, sf_mex_create("y", &c3_gb_u, 0, 0U, 0U, 0U, 0));
      sf_mex_addfield(c3_ob_y, c3_pb_y, "ValidMask", "ValidMask", c3_i1);
      c3_hb_u = c3_r0->Fc;
      c3_qb_y = NULL;
      sf_mex_assign(&c3_qb_y, sf_mex_create("y", &c3_hb_u, 0, 0U, 0U, 0U, 0));
      sf_mex_addfield(c3_ob_y, c3_qb_y, "Fc", "Fc", c3_i1);
      c3_ib_u = c3_r0->Gain;
      c3_rb_y = NULL;
      sf_mex_assign(&c3_rb_y, sf_mex_create("y", &c3_ib_u, 0, 0U, 0U, 0U, 0));
      sf_mex_addfield(c3_ob_y, c3_rb_y, "Gain", "Gain", c3_i1);
      c3_jb_u = c3_r0->DecimInterp;
      c3_sb_y = NULL;
      sf_mex_assign(&c3_sb_y, sf_mex_create("y", &c3_jb_u, 0, 0U, 0U, 0U, 0));
      sf_mex_addfield(c3_ob_y, c3_sb_y, "DecimInterp", "DecimInterp", c3_i1);
      c3_kb_u = c3_r0->ScaleI;
      c3_tb_y = NULL;
      sf_mex_assign(&c3_tb_y, sf_mex_create("y", &c3_kb_u, 0, 0U, 0U, 0U, 0));
      sf_mex_addfield(c3_ob_y, c3_tb_y, "ScaleI", "ScaleI", c3_i1);
      c3_lb_u = c3_r0->ScaleQ;
      c3_ub_y = NULL;
      sf_mex_assign(&c3_ub_y, sf_mex_create("y", &c3_lb_u, 0, 0U, 0U, 0U, 0));
      sf_mex_addfield(c3_ob_y, c3_ub_y, "ScaleQ", "ScaleQ", c3_i1);
    }
  }

  sf_mex_setcell(c3_y, 25, c3_ob_y);
  c3_mb_u = chartInstance->c3_is_active_c3_commsdrhw;
  c3_vb_y = NULL;
  sf_mex_assign(&c3_vb_y, sf_mex_create("y", &c3_mb_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 26, c3_vb_y);
  sf_mex_assign(&c3_st, c3_y);
  return c3_st;
}

static void set_sim_state_c3_commsdrhw(SFc3_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c3_st)
{
  const mxArray *c3_u;
  creal32_T c3_fcv0[358];
  int32_T c3_tmp_sizes;
  real_T c3_dv1[137];
  uint16_T c3_u0;
  uint8_T c3_u1;
  uint8_T c3_u2;
  uint8_T c3_u3;
  uint8_T c3_u4;
  uint32_T c3_uv0[2];
  uint8_T c3_u5;
  uint32_T c3_u6;
  uint8_T c3_u7;
  uint32_T c3_u8;
  uint8_T c3_u9;
  char_T c3_cv0[5];
  uint8_T c3_uv1[255];
  uint8_T c3_tmp_data[732];
  int32_T c3_loop_ub;
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_rv0[255];
  real_T *c3_b_dataLength;
  uint8_T *c3_overrun;
  creal32_T (*c3_data)[358];
  c3_overrun = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c3_b_dataLength = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c3_data = (creal32_T (*)[358])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_u = sf_mex_dup(c3_st);
  c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 0)), "data",
                      c3_fcv0);
  for (c3_tmp_sizes = 0; c3_tmp_sizes < 358; c3_tmp_sizes++) {
    (*c3_data)[c3_tmp_sizes] = c3_fcv0[c3_tmp_sizes];
  }

  *c3_b_dataLength = c3_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_u, 1)), "dataLength");
  *c3_overrun = c3_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c3_u, 2)), "overrun");
  c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 3)),
                        "NetworkLib", c3_dv1);
  for (c3_tmp_sizes = 0; c3_tmp_sizes < 137; c3_tmp_sizes++) {
    chartInstance->c3_NetworkLib[c3_tmp_sizes] = c3_dv1[c3_tmp_sizes];
  }

  c3_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 4)),
                        "NetworkLib", c3_dv1);
  for (c3_tmp_sizes = 0; c3_tmp_sizes < 137; c3_tmp_sizes++) {
    chartInstance->c3_b_NetworkLib[c3_tmp_sizes] = c3_dv1[c3_tmp_sizes];
  }

  c3_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 5)),
                        "NetworkLib", c3_dv1);
  for (c3_tmp_sizes = 0; c3_tmp_sizes < 137; c3_tmp_sizes++) {
    chartInstance->c3_c_NetworkLib[c3_tmp_sizes] = c3_dv1[c3_tmp_sizes];
  }

  c3_m_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 6)),
                        "NetworkLib", c3_dv1);
  for (c3_tmp_sizes = 0; c3_tmp_sizes < 137; c3_tmp_sizes++) {
    chartInstance->c3_d_NetworkLib[c3_tmp_sizes] = c3_dv1[c3_tmp_sizes];
  }

  c3_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 7)),
                        "Recv", c3_cv0, &c3_u9, &c3_u8, &c3_u7, &c3_u6, &c3_u5,
                        c3_uv0, &c3_u4, &c3_u3, &c3_u2, &c3_u1, &c3_u0);
  chartInstance->c3_Recv.stream.packetSize = c3_u0;
  chartInstance->c3_Recv.stream.packetCount = c3_u1;
  chartInstance->c3_Recv.stream.TSF = c3_u2;
  chartInstance->c3_Recv.stream.TSI = c3_u3;
  chartInstance->c3_Recv.stream.packetType = c3_u4;
  for (c3_tmp_sizes = 0; c3_tmp_sizes < 2; c3_tmp_sizes++) {
    chartInstance->c3_Recv.stream.classID[c3_tmp_sizes] = c3_uv0[c3_tmp_sizes];
  }

  chartInstance->c3_Recv.stream.hasClassID = c3_u5;
  chartInstance->c3_Recv.stream.streamID = c3_u6;
  chartInstance->c3_Recv.stream.hasStreamID = c3_u7;
  chartInstance->c3_Recv.trailer = c3_u8;
  chartInstance->c3_Recv.hasTrailer = c3_u9;
  for (c3_tmp_sizes = 0; c3_tmp_sizes < 5; c3_tmp_sizes++) {
    chartInstance->c3_Recv.datatype[c3_tmp_sizes] = c3_cv0[c3_tmp_sizes];
  }

  c3_v_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 8)), "Y0",
                        c3_uv1);
  for (c3_tmp_sizes = 0; c3_tmp_sizes < 255; c3_tmp_sizes++) {
    chartInstance->c3_Y0[c3_tmp_sizes] = c3_uv1[c3_tmp_sizes];
  }

  c3_x_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 9)), "Y0",
                        c3_uv1);
  for (c3_tmp_sizes = 0; c3_tmp_sizes < 255; c3_tmp_sizes++) {
    chartInstance->c3_b_Y0[c3_tmp_sizes] = c3_uv1[c3_tmp_sizes];
  }

  chartInstance->c3_Y1 = c3_ab_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_u, 10)), "Y1");
  chartInstance->c3_b_Y1 = c3_cb_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_u, 11)), "Y1");
  c3_eb_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 12)),
    "ctrlReceiver");
  c3_gb_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 13)),
    "ctrlReceiverBlocking");
  c3_ib_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 14)),
    "ctrlSender");
  chartInstance->c3_dataLength = c3_kb_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_u, 15)), "dataLength");
  c3_mb_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 16)),
    "dataSender");
  c3_ob_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 17)),
    "imagData", c3_tmp_data, &c3_tmp_sizes);
  chartInstance->c3_imagData_sizes = c3_tmp_sizes;
  c3_loop_ub = c3_tmp_sizes - 1;
  for (c3_tmp_sizes = 0; c3_tmp_sizes <= c3_loop_ub; c3_tmp_sizes++) {
    chartInstance->c3_imagData_data[c3_tmp_sizes] = c3_tmp_data[c3_tmp_sizes];
  }

  chartInstance->c3_lastCF = c3_qb_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_u, 18)), "lastCF");
  chartInstance->c3_lastDI = c3_sb_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_u, 19)), "lastDI");
  chartInstance->c3_lastG = c3_ub_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_u, 20)), "lastG");
  chartInstance->c3_lastI = c3_wb_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_u, 21)), "lastI");
  chartInstance->c3_lastQ = c3_yb_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_u, 22)), "lastQ");
  c3_bc_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 23)),
    "realData", c3_tmp_data, &c3_tmp_sizes);
  chartInstance->c3_realData_sizes = c3_tmp_sizes;
  c3_loop_ub = c3_tmp_sizes - 1;
  for (c3_tmp_sizes = 0; c3_tmp_sizes <= c3_loop_ub; c3_tmp_sizes++) {
    chartInstance->c3_realData_data[c3_tmp_sizes] = c3_tmp_data[c3_tmp_sizes];
  }

  chartInstance->c3_replyId = c3_dc_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_u, 24)), "replyId");
  c3_fc_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 25)),
    "replyQueue", c3_rv0);
  for (c3_tmp_sizes = 0; c3_tmp_sizes < 255; c3_tmp_sizes++) {
    chartInstance->c3_replyQueue[c3_tmp_sizes] = c3_rv0[c3_tmp_sizes];
  }

  chartInstance->c3_is_active_c3_commsdrhw = c3_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_u, 26)), "is_active_c3_commsdrhw");
  sf_mex_destroy(&c3_u);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_commsdrhw(SFc3_commsdrhwInstanceStruct *chartInstance)
{
  char_T *c3_sErr;

  /* System object Terminate function: dsp.UDPSender */
  c3_sErr = GetErrorBuffer(&chartInstance->c3_d_NetworkLib[0U]);
  LibTerminate(&chartInstance->c3_d_NetworkLib[0U]);
  if (*c3_sErr != 0) {
    PrintError(c3_sErr);
  }

  LibDestroy(&chartInstance->c3_d_NetworkLib[0U], 1);
  DestroyUDPInterface(&chartInstance->c3_d_NetworkLib[0U]);

  /* System object Terminate function: dsp.UDPSender */
  c3_sErr = GetErrorBuffer(&chartInstance->c3_c_NetworkLib[0U]);
  LibTerminate(&chartInstance->c3_c_NetworkLib[0U]);
  if (*c3_sErr != 0) {
    PrintError(c3_sErr);
  }

  LibDestroy(&chartInstance->c3_c_NetworkLib[0U], 1);
  DestroyUDPInterface(&chartInstance->c3_c_NetworkLib[0U]);

  /* System object Terminate function: dsp.UDPReceiver */
  c3_sErr = GetErrorBuffer(&chartInstance->c3_b_NetworkLib[0U]);
  LibTerminate(&chartInstance->c3_b_NetworkLib[0U]);
  if (*c3_sErr != 0) {
    PrintError(c3_sErr);
  }

  LibDestroy(&chartInstance->c3_b_NetworkLib[0U], 0);
  DestroyUDPInterface(&chartInstance->c3_b_NetworkLib[0U]);

  /* System object Terminate function: dsp.UDPReceiver */
  c3_sErr = GetErrorBuffer(&chartInstance->c3_NetworkLib[0U]);
  LibTerminate(&chartInstance->c3_NetworkLib[0U]);
  if (*c3_sErr != 0) {
    PrintError(c3_sErr);
  }

  LibDestroy(&chartInstance->c3_NetworkLib[0U], 0);
  DestroyUDPInterface(&chartInstance->c3_NetworkLib[0U]);
}

static void sf_c3_commsdrhw(SFc3_commsdrhwInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  c3_chartstep_c3_commsdrhw(chartInstance);
}

static void c3_chartstep_c3_commsdrhw(SFc3_commsdrhwInstanceStruct
  *chartInstance)
{
  int32_T c3_msg_sizes_idx_1;
  int32_T c3_loop_ub;
  int32_T c3_i2;
  uint8_T c3_packet_data[1464];
  real_T c3_centerFreq;
  real_T c3_gain;
  real_T c3_decimation;
  char_T *c3_sErr;
  int32_T c3_samplesRead;
  int32_T c3_b_samplesRead;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_cmdDef[18];
  real_T c3_pktLength;
  uint8_T c3_pkt[255];
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_b_replyQueue[255];
  uint8_T c3_uv2[4];
  uint8_T c3_overrun;
  int32_T c3_b_dataLength;
  int32_T c3_packet[1];
  c3_s69xIfXV5nXp8sDnVHzDOMB c3_b_Recv;
  int32_T c3_err_sizes[2];
  char_T c3_err_data[24];
  cint16_T c3_out_data[366];
  char_T c3_msg_data[25];
  char_T c3_b_msg_data[25];
  static char_T c3_msg[35] = { 'R', 'e', 'c', 'e', 'i', 'v', 'e', 'd', ' ', 'i',
    'n', 'c', 'o', 'r', 'r', 'e', 'c', 't', ' ', 'a', 'm', 'o', 'u', 'n', 't',
    ' ', 'o', 'f', ' ', 'd', 'a', 't', 'a', '.', '\x00' };

  char_T c3_b_msg[35];
  cint16_T c3_a[358];
  real_T *c3_c_dataLength;
  uint8_T *c3_b_overrun;
  real_T *c3_b_centerFreq;
  real_T *c3_b_gain;
  real_T *c3_b_decimation;
  creal32_T (*c3_data)[358];
  int32_T (*c3_packet_sizes)[2];
  uint8_T (*c3_b_packet_data)[1464];
  c3_b_overrun = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c3_c_dataLength = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c3_b_decimation = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c3_b_gain = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c3_b_centerFreq = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c3_data = (creal32_T (*)[358])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_packet_sizes = (int32_T (*)[2])ssGetCurrentInputPortDimensions_wrapper
    (chartInstance->S, 0);
  c3_b_packet_data = (uint8_T (*)[1464])ssGetInputPortSignal(chartInstance->S, 0);
  c3_msg_sizes_idx_1 = (*c3_packet_sizes)[0];
  c3_loop_ub = (*c3_packet_sizes)[0] * (*c3_packet_sizes)[1] - 1;
  for (c3_i2 = 0; c3_i2 <= c3_loop_ub; c3_i2++) {
    c3_packet_data[c3_i2] = (*c3_b_packet_data)[c3_i2];
  }

  c3_centerFreq = *c3_b_centerFreq;
  c3_gain = *c3_b_gain;
  c3_decimation = *c3_b_decimation;
  if (!chartInstance->c3_Recv_not_empty) {
    c3_VRTDecoder(chartInstance, chartInstance->c3_Recv.datatype,
                  &chartInstance->c3_Recv.hasTrailer,
                  &chartInstance->c3_Recv.trailer,
                  &chartInstance->c3_Recv.stream.hasStreamID,
                  &chartInstance->c3_Recv.stream.streamID,
                  &chartInstance->c3_Recv.stream.hasClassID,
                  chartInstance->c3_Recv.stream.classID,
                  &chartInstance->c3_Recv.stream.packetType,
                  &chartInstance->c3_Recv.stream.TSI,
                  &chartInstance->c3_Recv.stream.TSF,
                  &chartInstance->c3_Recv.stream.packetCount,
                  &chartInstance->c3_Recv.stream.packetSize);
    chartInstance->c3_Recv_not_empty = TRUE;
    for (c3_i2 = 0; c3_i2 < 255; c3_i2++) {
      chartInstance->c3_replyQueue[c3_i2].ValidMask = 0.0;
      chartInstance->c3_replyQueue[c3_i2].Fc = 0.0;
      chartInstance->c3_replyQueue[c3_i2].Gain = 0.0;
      chartInstance->c3_replyQueue[c3_i2].DecimInterp = 0.0;
      chartInstance->c3_replyQueue[c3_i2].ScaleI = 0.0;
      chartInstance->c3_replyQueue[c3_i2].ScaleQ = 0.0;
    }

    chartInstance->c3_replyQueue_not_empty = TRUE;
    chartInstance->c3_ctrlSender_not_empty = TRUE;
    chartInstance->c3_dataSender_not_empty = TRUE;
    chartInstance->c3_ctrlReceiver_not_empty = TRUE;

    /* System object Outputs function: dsp.UDPReceiver */
    c3_sErr = GetErrorBuffer(&chartInstance->c3_NetworkLib[0U]);
    c3_samplesRead = 255;
    LibOutputs_Network(&chartInstance->c3_NetworkLib[0U], &chartInstance->c3_Y0
                       [0], &(&c3_samplesRead)[0U]);
    if (*c3_sErr != 0) {
      PrintError(c3_sErr);
    }

    chartInstance->c3_Y1 = (uint16_T)c3_samplesRead;
    chartInstance->c3_ctrlReceiverBlocking_not_empty = TRUE;

    /* System object Outputs function: dsp.UDPReceiver */
    c3_sErr = GetErrorBuffer(&chartInstance->c3_b_NetworkLib[0U]);
    c3_b_samplesRead = 255;
    LibOutputs_Network(&chartInstance->c3_b_NetworkLib[0U],
                       &chartInstance->c3_b_Y0[0], &(&c3_b_samplesRead)[0U]);
    if (*c3_sErr != 0) {
      PrintError(c3_sErr);
    }

    chartInstance->c3_b_Y1 = (uint16_T)c3_b_samplesRead;
    c3_USRP2CmdDef(chartInstance, USRP2Opcodes_GetDboardInfo, c3_cmdDef);
    c3_USRP2Cmd2Pkt(chartInstance, c3_cmdDef, c3_pkt, &c3_pktLength);
    c3_Update(chartInstance, c3_pkt, c3_pktLength);
    for (c3_i2 = 0; c3_i2 < 255; c3_i2++) {
      c3_b_replyQueue[c3_i2] = chartInstance->c3_replyQueue[c3_i2];
    }

    c3_centerFreq = c3_l_SendConfig(chartInstance, c3_b_replyQueue,
      c3_centerFreq, c3_gain, c3_decimation);
    for (c3_i2 = 0; c3_i2 < 255; c3_i2++) {
      chartInstance->c3_replyQueue[c3_i2] = c3_b_replyQueue[c3_i2];
    }

    c3_gain = 1.0;
    while (c3_gain <= c3_centerFreq) {
      for (c3_i2 = 0; c3_i2 < 255; c3_i2++) {
        c3_b_replyQueue[c3_i2] = chartInstance->c3_replyQueue[c3_i2];
      }

      c3_l_ReceiveReply(chartInstance, c3_b_replyQueue);
      for (c3_i2 = 0; c3_i2 < 255; c3_i2++) {
        chartInstance->c3_replyQueue[c3_i2] = c3_b_replyQueue[c3_i2];
      }

      c3_gain++;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    for (c3_i2 = 0; c3_i2 < 4; c3_i2++) {
      c3_uv2[c3_i2] = 0U;
    }

    c3_b_Update(chartInstance, c3_uv2, 4.0);
    c3_d_USRP2RuntimeControl(chartInstance, &c3_centerFreq, c3_pkt);
    c3_Update(chartInstance, c3_pkt, c3_centerFreq);
    for (c3_i2 = 0; c3_i2 < 255; c3_i2++) {
      c3_b_replyQueue[c3_i2] = chartInstance->c3_replyQueue[c3_i2];
    }

    c3_l_ReceiveReply(chartInstance, c3_b_replyQueue);
    for (c3_i2 = 0; c3_i2 < 255; c3_i2++) {
      chartInstance->c3_replyQueue[c3_i2] = c3_b_replyQueue[c3_i2];
    }
  } else {
    c3_b_l_SendConfig(chartInstance, chartInstance->c3_replyQueue,
                      *c3_b_centerFreq, *c3_b_gain, *c3_b_decimation);
  }

  for (c3_i2 = 0; c3_i2 < 255; c3_i2++) {
    c3_b_replyQueue[c3_i2] = chartInstance->c3_replyQueue[c3_i2];
  }

  c3_b_l_ReceiveReply(chartInstance, c3_b_replyQueue);
  for (c3_i2 = 0; c3_i2 < 255; c3_i2++) {
    chartInstance->c3_replyQueue[c3_i2] = c3_b_replyQueue[c3_i2];
  }

  c3_overrun = 0U;
  c3_b_dataLength = 0;
  c3_packet[0] = c3_msg_sizes_idx_1;
  if (c3_length(chartInstance, c3_packet_data, c3_packet) > 4.0) {
    c3_b_Recv = chartInstance->c3_Recv;
    c3_packet[0] = c3_msg_sizes_idx_1;
    c3_b_VRTDecoder(chartInstance, &c3_b_Recv, c3_packet_data, c3_packet,
                    c3_out_data, &c3_msg_sizes_idx_1, &c3_centerFreq,
                    c3_err_data, c3_err_sizes);
    chartInstance->c3_Recv = c3_b_Recv;
    if (!(c3_err_sizes[1] == 0)) {
      c3_msg_sizes_idx_1 = c3_err_sizes[1] + 1;
      c3_loop_ub = c3_err_sizes[1] - 1;
      for (c3_i2 = 0; c3_i2 <= c3_loop_ub; c3_i2++) {
        c3_msg_data[c3_i2] = c3_err_data[c3_err_sizes[0] * c3_i2];
      }

      c3_msg_data[c3_err_sizes[1]] = '\x00';
      c3_loop_ub = c3_msg_sizes_idx_1 - 1;
      for (c3_i2 = 0; c3_i2 <= c3_loop_ub; c3_i2++) {
        c3_b_msg_data[c3_i2] = c3_msg_data[c3_i2];
      }

      PrintError(&c3_b_msg_data[0]);
      c3_overrun = 1U;
    }

    if (c3_centerFreq != c3_b_frameLength) {
      for (c3_i2 = 0; c3_i2 < 35; c3_i2++) {
        c3_b_msg[c3_i2] = c3_msg[c3_i2];
      }

      PrintError(c3_b_msg);
      for (c3_i2 = 0; c3_i2 < 358; c3_i2++) {
        (*c3_data)[c3_i2].re = 0.0F;
        (*c3_data)[c3_i2].im = 0.0F;
      }
    } else {
      c3_b_dataLength = (int32_T)c3_b_frameLength;
      for (c3_i2 = 0; c3_i2 < 358; c3_i2++) {
        c3_a[c3_i2] = c3_out_data[c3_i2];
        (*c3_data)[c3_i2].re = 3.05185094E-5F * (real32_T)c3_a[c3_i2].re;
        (*c3_data)[c3_i2].im = 3.05185094E-5F * (real32_T)c3_a[c3_i2].im;
      }
    }
  } else {
    for (c3_i2 = 0; c3_i2 < 358; c3_i2++) {
      (*c3_data)[c3_i2].re = 0.0F;
      (*c3_data)[c3_i2].im = 0.0F;
    }
  }

  *c3_c_dataLength = (real_T)c3_b_dataLength;
  *c3_b_overrun = c3_overrun;
}

static void initSimStructsc3_commsdrhw(SFc3_commsdrhwInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber)
{
}

const mxArray *sf_c3_commsdrhw_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  sf_mex_assign(&c3_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1));
  return c3_nameCaptureInfo;
}

static void c3_VRTDecoder(SFc3_commsdrhwInstanceStruct *chartInstance, char_T
  c3_S_datatype[5], uint8_T *c3_S_hasTrailer, uint32_T *c3_S_trailer, uint8_T
  *c3_S_stream_hasStreamID, uint32_T *c3_S_stream_streamID, uint8_T
  *c3_S_stream_hasClassID, uint32_T c3_S_stream_classID[2], uint8_T
  *c3_S_stream_packetType, uint8_T *c3_S_stream_TSI, uint8_T *c3_S_stream_TSF,
  uint8_T *c3_S_stream_packetCount, uint16_T *c3_S_stream_packetSize)
{
  int32_T c3_i3;
  static char_T c3_value[5] = { 'i', 'n', 't', '1', '6' };

  *c3_S_hasTrailer = 0U;
  *c3_S_trailer = 0U;
  *c3_S_stream_hasStreamID = 0U;
  *c3_S_stream_streamID = 0U;
  *c3_S_stream_hasClassID = 0U;
  for (c3_i3 = 0; c3_i3 < 2; c3_i3++) {
    c3_S_stream_classID[c3_i3] = 0U;
  }

  *c3_S_stream_packetType = 0U;
  *c3_S_stream_TSI = 0U;
  *c3_S_stream_TSF = 0U;
  *c3_S_stream_packetCount = 0U;
  *c3_S_stream_packetSize = 0U;
  for (c3_i3 = 0; c3_i3 < 5; c3_i3++) {
    c3_S_datatype[c3_i3] = c3_value[c3_i3];
  }
}

static void c3_USRP2CmdDef(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_USRP2Opcodes c3_cmd, c3_s7P91ApZ2CkwDPZE5FamWSB c3_cmdDef[18])
{
  int32_T c3_i4;
  static c3_s7P91ApZ2CkwDPZE5FamWSB c3_r1 = { 0.0, 0.0,
    USRP2FieldDtypes_usrp2_uint8_T, { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
      0U, 0U, 0U, 0U, 0U } };

  c3_s7P91ApZ2CkwDPZE5FamWSB c3_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_b_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_c_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_d_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_e_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_f_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_g_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_h_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_i_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_j_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_k_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_l_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_m_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_n_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_o_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_p_expl_temp;
  for (c3_i4 = 0; c3_i4 < 18; c3_i4++) {
    c3_cmdDef[c3_i4] = c3_r1;
  }

  c3_b_l_fdef(chartInstance, 1.0, 1.0, USRP2FieldDtypes_usrp2_uint8_T, (real_T)
              (int32_T)c3_cmd, &c3_cmdDef[(int32_T)USRP2CmdFields_Opcode - 1].
              offset, &c3_cmdDef[(int32_T)USRP2CmdFields_Opcode - 1].fsize,
              &c3_cmdDef[(int32_T)USRP2CmdFields_Opcode - 1].dtype, c3_cmdDef
              [(int32_T)USRP2CmdFields_Opcode - 1].bytes);
  c3_l_fdef(chartInstance, 2.0, 1.0, USRP2FieldDtypes_usrp2_uint8_T, &c3_cmdDef
            [(int32_T)USRP2CmdFields_Length - 1].offset, &c3_cmdDef[(int32_T)
            USRP2CmdFields_Length - 1].fsize, &c3_cmdDef[(int32_T)
            USRP2CmdFields_Length - 1].dtype, c3_cmdDef[(int32_T)
            USRP2CmdFields_Length - 1].bytes);
  c3_expl_temp.offset = 3.0;
  c3_expl_temp.fsize = 1.0;
  c3_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint8_T;
  for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
    c3_expl_temp.bytes[c3_i4] = 0U;
  }

  c3_cmdDef[(int32_T)USRP2CmdFields_ReplyId - 1] = c3_expl_temp;
  c3_b_expl_temp.offset = 4.0;
  c3_b_expl_temp.fsize = 1.0;
  c3_b_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint8_T;
  for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
    c3_b_expl_temp.bytes[c3_i4] = 0U;
  }

  c3_cmdDef[(int32_T)USRP2CmdFields_Ok - 1] = c3_b_expl_temp;
  switch ((int32_T)c3_cmd) {
   case 129:
    c3_c_expl_temp.offset = 5.0;
    c3_c_expl_temp.fsize = 6.0;
    c3_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_c_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_MacAddr - 1] = c3_c_expl_temp;
    c3_d_expl_temp.offset = 11.0;
    c3_d_expl_temp.fsize = 2.0;
    c3_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_d_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_HwRev - 1] = c3_d_expl_temp;
    c3_e_expl_temp.offset = 13.0;
    c3_e_expl_temp.fsize = 8.0;
    c3_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_e_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_FpgaMd5Lo - 1] = c3_e_expl_temp;
    c3_f_expl_temp.offset = 21.0;
    c3_f_expl_temp.fsize = 8.0;
    c3_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_f_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_FpgaMd5Hi - 1] = c3_f_expl_temp;
    c3_g_expl_temp.offset = 29.0;
    c3_g_expl_temp.fsize = 8.0;
    c3_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_g_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_FirmwareMd5Lo - 1] = c3_g_expl_temp;
    c3_h_expl_temp.offset = 37.0;
    c3_h_expl_temp.fsize = 8.0;
    c3_h_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_h_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_FirmwareMd5Hi - 1] = c3_h_expl_temp;
    break;

   case 4:
    c3_c_expl_temp.offset = 5.0;
    c3_c_expl_temp.fsize = 2.0;
    c3_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_c_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_Valid - 1] = c3_c_expl_temp;
    c3_d_expl_temp.offset = 7.0;
    c3_d_expl_temp.fsize = 2.0;
    c3_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_d_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_Gain - 1] = c3_d_expl_temp;
    c3_e_expl_temp.offset = 9.0;
    c3_e_expl_temp.fsize = 8.0;
    c3_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_e_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_CenterFreq - 1] = c3_e_expl_temp;
    c3_f_expl_temp.offset = 17.0;
    c3_f_expl_temp.fsize = 4.0;
    c3_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_f_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_Decimation - 1] = c3_f_expl_temp;
    c3_g_expl_temp.offset = 21.0;
    c3_g_expl_temp.fsize = 2.0;
    c3_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_g_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_ScaleI - 1] = c3_g_expl_temp;
    c3_h_expl_temp.offset = 23.0;
    c3_h_expl_temp.fsize = 2.0;
    c3_h_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_h_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_ScaleQ - 1] = c3_h_expl_temp;
    break;

   case 132:
    c3_c_expl_temp.offset = 5.0;
    c3_c_expl_temp.fsize = 2.0;
    c3_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_c_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_ConfigOk - 1] = c3_c_expl_temp;
    c3_d_expl_temp.offset = 7.0;
    c3_d_expl_temp.fsize = 2.0;
    c3_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_d_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_SpectrumInverted - 1] = c3_d_expl_temp;
    c3_e_expl_temp.offset = 9.0;
    c3_e_expl_temp.fsize = 8.0;
    c3_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_e_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_BasebandFreq - 1] = c3_e_expl_temp;
    c3_f_expl_temp.offset = 17.0;
    c3_f_expl_temp.fsize = 8.0;
    c3_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_f_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_DdcFreq - 1] = c3_f_expl_temp;
    c3_g_expl_temp.offset = 25.0;
    c3_g_expl_temp.fsize = 8.0;
    c3_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_g_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_ResidualFreq - 1] = c3_g_expl_temp;
    break;

   case 5:
    c3_c_expl_temp.offset = 5.0;
    c3_c_expl_temp.fsize = 2.0;
    c3_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_c_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_Valid - 1] = c3_c_expl_temp;
    c3_d_expl_temp.offset = 7.0;
    c3_d_expl_temp.fsize = 2.0;
    c3_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_d_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_Gain - 1] = c3_d_expl_temp;
    c3_e_expl_temp.offset = 9.0;
    c3_e_expl_temp.fsize = 8.0;
    c3_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_e_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_CenterFreq - 1] = c3_e_expl_temp;
    c3_f_expl_temp.offset = 17.0;
    c3_f_expl_temp.fsize = 4.0;
    c3_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_f_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_Interpolation - 1] = c3_f_expl_temp;
    c3_g_expl_temp.offset = 21.0;
    c3_g_expl_temp.fsize = 2.0;
    c3_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_g_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_ScaleI - 1] = c3_g_expl_temp;
    c3_h_expl_temp.offset = 23.0;
    c3_h_expl_temp.fsize = 2.0;
    c3_h_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_h_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_ScaleQ - 1] = c3_h_expl_temp;
    break;

   case 133:
    c3_c_expl_temp.offset = 5.0;
    c3_c_expl_temp.fsize = 2.0;
    c3_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_c_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_ConfigOk - 1] = c3_c_expl_temp;
    c3_d_expl_temp.offset = 7.0;
    c3_d_expl_temp.fsize = 2.0;
    c3_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_d_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_SpectrumInverted - 1] = c3_d_expl_temp;
    c3_e_expl_temp.offset = 9.0;
    c3_e_expl_temp.fsize = 8.0;
    c3_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_e_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_BasebandFreq - 1] = c3_e_expl_temp;
    c3_f_expl_temp.offset = 17.0;
    c3_f_expl_temp.fsize = 8.0;
    c3_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_f_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_DucFreq - 1] = c3_f_expl_temp;
    c3_g_expl_temp.offset = 25.0;
    c3_g_expl_temp.fsize = 8.0;
    c3_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_g_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_ResidualFreq - 1] = c3_g_expl_temp;
    break;

   case 6:
    c3_c_expl_temp.offset = 5.0;
    c3_c_expl_temp.fsize = 4.0;
    c3_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_c_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_ItemsPerFrame - 1] = c3_c_expl_temp;
    c3_d_expl_temp.offset = 9.0;
    c3_d_expl_temp.fsize = 4.0;
    c3_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_d_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_TimeInt - 1] = c3_d_expl_temp;
    c3_e_expl_temp.offset = 13.0;
    c3_e_expl_temp.fsize = 4.0;
    c3_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_e_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_TimeFrac - 1] = c3_e_expl_temp;
    break;

   case 137:
    c3_c_expl_temp.offset = 5.0;
    c3_c_expl_temp.fsize = 4.0;
    c3_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_c_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_TxDbId - 1] = c3_c_expl_temp;
    c3_d_expl_temp.offset = 9.0;
    c3_d_expl_temp.fsize = 8.0;
    c3_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_d_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_TxFreqMin - 1] = c3_d_expl_temp;
    c3_e_expl_temp.offset = 17.0;
    c3_e_expl_temp.fsize = 8.0;
    c3_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_e_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_TxFreqMax - 1] = c3_e_expl_temp;
    c3_f_expl_temp.offset = 25.0;
    c3_f_expl_temp.fsize = 2.0;
    c3_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_f_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_TxGainMin - 1] = c3_f_expl_temp;
    c3_g_expl_temp.offset = 27.0;
    c3_g_expl_temp.fsize = 2.0;
    c3_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_g_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_TxGainMax - 1] = c3_g_expl_temp;
    c3_h_expl_temp.offset = 29.0;
    c3_h_expl_temp.fsize = 2.0;
    c3_h_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_h_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_TxGainStepSize - 1] = c3_h_expl_temp;
    c3_i_expl_temp.offset = 31.0;
    c3_i_expl_temp.fsize = 2.0;
    c3_i_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_i_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_TxDbReserved - 1] = c3_i_expl_temp;
    c3_j_expl_temp.offset = 33.0;
    c3_j_expl_temp.fsize = 4.0;
    c3_j_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_j_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_RxDbId - 1] = c3_j_expl_temp;
    c3_k_expl_temp.offset = 37.0;
    c3_k_expl_temp.fsize = 8.0;
    c3_k_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_k_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_RxFreqMin - 1] = c3_k_expl_temp;
    c3_l_expl_temp.offset = 45.0;
    c3_l_expl_temp.fsize = 8.0;
    c3_l_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_l_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_RxFreqMax - 1] = c3_l_expl_temp;
    c3_m_expl_temp.offset = 53.0;
    c3_m_expl_temp.fsize = 2.0;
    c3_m_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_m_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_RxGainMin - 1] = c3_m_expl_temp;
    c3_n_expl_temp.offset = 55.0;
    c3_n_expl_temp.fsize = 2.0;
    c3_n_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_n_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_RxGainMax - 1] = c3_n_expl_temp;
    c3_o_expl_temp.offset = 57.0;
    c3_o_expl_temp.fsize = 2.0;
    c3_o_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_o_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_RxGainStepSize - 1] = c3_o_expl_temp;
    c3_p_expl_temp.offset = 59.0;
    c3_p_expl_temp.fsize = 2.0;
    c3_p_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_p_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_RxDbReserved - 1] = c3_p_expl_temp;
    break;

   case 14:
    c3_c_expl_temp.offset = 5.0;
    c3_c_expl_temp.fsize = 8.0;
    c3_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_c_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_FreqOffset - 1] = c3_c_expl_temp;
    break;

   case 13:
    c3_c_expl_temp.offset = 5.0;
    c3_c_expl_temp.fsize = 8.0;
    c3_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i4 = 0; c3_i4 < 16; c3_i4++) {
      c3_c_expl_temp.bytes[c3_i4] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_FreqOffset - 1] = c3_c_expl_temp;
    break;
  }
}

static void c3_l_fdef(SFc3_commsdrhwInstanceStruct *chartInstance, real_T
                      c3_offset, real_T c3_fsize, c3_USRP2FieldDtypes c3_dtype,
                      real_T *c3_s_offset, real_T *c3_s_fsize,
                      c3_USRP2FieldDtypes *c3_s_dtype, uint8_T c3_s_bytes[16])
{
  int32_T c3_i5;
  *c3_s_offset = c3_offset;
  *c3_s_fsize = c3_fsize;
  *c3_s_dtype = c3_dtype;
  for (c3_i5 = 0; c3_i5 < 16; c3_i5++) {
    c3_s_bytes[c3_i5] = 0U;
  }
}

static void c3_b_l_fdef(SFc3_commsdrhwInstanceStruct *chartInstance, real_T
  c3_offset, real_T c3_fsize, c3_USRP2FieldDtypes c3_dtype, real_T c3_val,
  real_T *c3_s_offset, real_T *c3_s_fsize, c3_USRP2FieldDtypes *c3_s_dtype,
  uint8_T c3_s_bytes[16])
{
  *c3_s_offset = 1.0;
  *c3_s_fsize = 1.0;
  *c3_s_dtype = c3_dtype;
  c3_USRP2PackFieldVal(chartInstance, c3_dtype, c3_val, c3_s_bytes);
}

static void c3_USRP2PackFieldVal(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_USRP2FieldDtypes c3_dtype, real_T c3_val, uint8_T c3_bytes[16])
{
  int32_T c3_i6;
  real_T c3_d6;
  uint8_T c3_leBytes;
  uint16_T c3_x;
  uint8_T c3_b_leBytes[2];
  uint32_T c3_b_x;
  uint8_T c3_c_leBytes[4];
  real_T c3_y;
  uint8_T c3_d_leBytes[8];
  static char_T c3_cv1[30] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's', ':', 'U',
    'S', 'R', 'P', '2', ':', 'U', 'n', 'p', 'a', 'c', 'k', 'a', 'b', 'l', 'e',
    'D', 't', 'y', 'p', 'e' };

  char_T c3_u[30];
  const mxArray *c3_b_y = NULL;
  static char_T c3_cv2[30] = { 'T', 'h', 'e', ' ', 'd', 'a', 't', 'a', 't', 'y',
    'p', 'e', ' ', 'c', 'a', 'n', 'n', 'o', 't', ' ', 'b', 'e', ' ', 'p', 'a',
    'c', 'k', 'e', 'd', '.' };

  char_T c3_b_u[30];
  const mxArray *c3_c_y = NULL;
  const mxArray *c3_d_y = NULL;
  char_T c3_c_u[32];
  const mxArray *c3_e_y = NULL;
  char_T c3_d_u[37];
  static char_T c3_cv3[32] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's', ':', 'U',
    'S', 'R', 'P', '2', ':', 'U', 'n', 'k', 'n', 'o', 'w', 'n', 'F', 'i', 'e',
    'l', 'd', 'D', 't', 'y', 'p', 'e' };

  static char_T c3_cv4[37] = { 'U', 'n', 'k', 'n', 'o', 'w', 'n', ' ', 'U', 'S',
    'R', 'P', '2', ' ', 'd', 'a', 't', 'a', 't', 'y', 'p', 'e', ' ', 's', 'p',
    'e', 'c', 'i', 'f', 'i', 'c', 'a', 't', 'i', 'o', 'n', '.' };

  for (c3_i6 = 0; c3_i6 < 16; c3_i6++) {
    c3_bytes[c3_i6] = 0U;
  }

  switch (c3_dtype) {
   case USRP2FieldDtypes_usrp2_uint8_T:
    c3_d6 = c3_val;
    c3_d6 = c3_d6 < 0.0 ? muDoubleScalarCeil(c3_d6 - 0.5) : muDoubleScalarFloor
      (c3_d6 + 0.5);
    if (c3_d6 < 256.0) {
      if (c3_d6 >= 0.0) {
        c3_leBytes = (uint8_T)c3_d6;
      } else {
        c3_leBytes = 0U;
      }
    } else if (c3_d6 >= 256.0) {
      c3_leBytes = MAX_uint8_T;
    } else {
      c3_leBytes = 0U;
    }

    c3_bytes[0] = c3_leBytes;
    break;

   case USRP2FieldDtypes_usrp2_uint16_T:
    c3_d6 = c3_val;
    c3_d6 = c3_d6 < 0.0 ? muDoubleScalarCeil(c3_d6 - 0.5) : muDoubleScalarFloor
      (c3_d6 + 0.5);
    if (c3_d6 < 65536.0) {
      if (c3_d6 >= 0.0) {
        c3_x = (uint16_T)c3_d6;
      } else {
        c3_x = 0U;
      }
    } else if (c3_d6 >= 65536.0) {
      c3_x = MAX_uint16_T;
    } else {
      c3_x = 0U;
    }

    memcpy((void *)&c3_b_leBytes[0], (void *)&c3_x, 2U);
    for (c3_i6 = 0; c3_i6 < 2; c3_i6++) {
      c3_bytes[c3_i6] = c3_b_leBytes[1 - c3_i6];
    }
    break;

   case USRP2FieldDtypes_usrp2_uint32_T:
    c3_d6 = c3_val;
    c3_d6 = c3_d6 < 0.0 ? muDoubleScalarCeil(c3_d6 - 0.5) : muDoubleScalarFloor
      (c3_d6 + 0.5);
    if (c3_d6 < 4.294967296E+9) {
      if (c3_d6 >= 0.0) {
        c3_b_x = (uint32_T)c3_d6;
      } else {
        c3_b_x = 0U;
      }
    } else if (c3_d6 >= 4.294967296E+9) {
      c3_b_x = MAX_uint32_T;
    } else {
      c3_b_x = 0U;
    }

    memcpy((void *)&c3_c_leBytes[0], (void *)&c3_b_x, 4U);
    for (c3_i6 = 0; c3_i6 < 4; c3_i6++) {
      c3_bytes[c3_i6] = c3_c_leBytes[3 - c3_i6];
    }
    break;

   case USRP2FieldDtypes_usrp2_sfix16_En7_T:
    c3_y = muDoubleScalarFloor(c3_val * 128.0);
    for (c3_i6 = 0; c3_i6 < 2; c3_i6++) {
      c3_d6 = c3_y - muDoubleScalarFloor(c3_y / 256.0) * 256.0;
      c3_d6 = c3_d6 < 0.0 ? muDoubleScalarCeil(c3_d6 - 0.5) :
        muDoubleScalarFloor(c3_d6 + 0.5);
      if (c3_d6 < 256.0) {
        if (c3_d6 >= 0.0) {
          c3_leBytes = (uint8_T)c3_d6;
        } else {
          c3_leBytes = 0U;
        }
      } else if (c3_d6 >= 256.0) {
        c3_leBytes = MAX_uint8_T;
      } else {
        c3_leBytes = 0U;
      }

      c3_y = (c3_y - (real_T)c3_leBytes) / 256.0;
      c3_b_leBytes[c3_i6] = c3_leBytes;
    }

    for (c3_i6 = 0; c3_i6 < 2; c3_i6++) {
      c3_bytes[c3_i6] = c3_b_leBytes[1 - c3_i6];
    }
    break;

   case USRP2FieldDtypes_usrp2_sfix64_En20_T:
    c3_y = muDoubleScalarFloor(c3_val * 1.048576E+6);
    for (c3_i6 = 0; c3_i6 < 8; c3_i6++) {
      c3_d6 = c3_y - muDoubleScalarFloor(c3_y / 256.0) * 256.0;
      c3_d6 = c3_d6 < 0.0 ? muDoubleScalarCeil(c3_d6 - 0.5) :
        muDoubleScalarFloor(c3_d6 + 0.5);
      if (c3_d6 < 256.0) {
        if (c3_d6 >= 0.0) {
          c3_leBytes = (uint8_T)c3_d6;
        } else {
          c3_leBytes = 0U;
        }
      } else if (c3_d6 >= 256.0) {
        c3_leBytes = MAX_uint8_T;
      } else {
        c3_leBytes = 0U;
      }

      c3_y = (c3_y - (real_T)c3_leBytes) / 256.0;
      c3_d_leBytes[c3_i6] = c3_leBytes;
    }

    for (c3_i6 = 0; c3_i6 < 8; c3_i6++) {
      c3_bytes[c3_i6] = c3_d_leBytes[7 - c3_i6];
    }
    break;

   case USRP2FieldDtypes_usrp2_byteArray_T:
    for (c3_i6 = 0; c3_i6 < 30; c3_i6++) {
      c3_u[c3_i6] = c3_cv1[c3_i6];
    }

    c3_b_y = NULL;
    sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 30));
    for (c3_i6 = 0; c3_i6 < 30; c3_i6++) {
      c3_b_u[c3_i6] = c3_cv2[c3_i6];
    }

    c3_c_y = NULL;
    sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 30));
    sf_mex_call("error", 0U, 2U, 14, c3_b_y, 14, c3_c_y);
    break;

   default:
    for (c3_i6 = 0; c3_i6 < 32; c3_i6++) {
      c3_c_u[c3_i6] = c3_cv3[c3_i6];
    }

    c3_d_y = NULL;
    sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_c_u, 10, 0U, 1U, 0U, 2, 1, 32));
    for (c3_i6 = 0; c3_i6 < 37; c3_i6++) {
      c3_d_u[c3_i6] = c3_cv4[c3_i6];
    }

    c3_e_y = NULL;
    sf_mex_assign(&c3_e_y, sf_mex_create("y", c3_d_u, 10, 0U, 1U, 0U, 2, 1, 37));
    sf_mex_call("error", 0U, 2U, 14, c3_d_y, 14, c3_e_y);
    break;
  }
}

static void c3_USRP2Cmd2Pkt(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_cmdDef[18], uint8_T c3_pkt[255], real_T
  *c3_pktLen)
{
  int32_T c3_fidx;
  real_T c3_bidx;
  uint8_T c3_lf_bytes[16];
  int32_T c3_tmp_sizes;
  int32_T c3_i7;
  int32_T c3_loop_ub;
  int32_T c3_tmp_data[66];
  int32_T c3_b_tmp_data[8];
  static uint8_T c3_uv3[4] = { 0U, 4U, 0U, 0U };

  *c3_pktLen = 0.0;
  for (c3_fidx = 0; c3_fidx < 255; c3_fidx++) {
    c3_pkt[c3_fidx] = 0U;
  }

  c3_fidx = 0;
  while ((c3_fidx + 1 <= 18) && (!(c3_cmdDef[c3_fidx].fsize == 0.0))) {
    for (c3_bidx = 1.0; c3_bidx <= c3_cmdDef[c3_fidx].fsize; c3_bidx++) {
      c3_pkt[(int32_T)((c3_cmdDef[c3_fidx].offset + c3_bidx) - 1.0) - 1] =
        c3_cmdDef[c3_fidx].bytes[(int32_T)c3_bidx - 1];
    }

    *c3_pktLen += c3_cmdDef[c3_fidx].fsize;
    c3_fidx++;
  }

  c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[1].dtype, *c3_pktLen,
                       c3_lf_bytes);
  if (1.0 > c3_cmdDef[1].fsize) {
    c3_tmp_sizes = 0;
  } else {
    c3_tmp_sizes = (int32_T)c3_cmdDef[1].fsize;
  }

  c3_bidx = (c3_cmdDef[1].offset + c3_cmdDef[1].fsize) - 1.0;
  if (c3_cmdDef[1].offset > c3_bidx) {
    c3_fidx = 1;
    c3_i7 = 0;
  } else {
    c3_fidx = (int32_T)c3_cmdDef[1].offset;
    c3_i7 = (int32_T)c3_bidx;
  }

  c3_loop_ub = c3_i7 - c3_fidx;
  for (c3_i7 = 0; c3_i7 <= c3_loop_ub; c3_i7++) {
    c3_tmp_data[c3_i7] = c3_fidx + c3_i7;
  }

  c3_loop_ub = c3_tmp_sizes - 1;
  for (c3_fidx = 0; c3_fidx <= c3_loop_ub; c3_fidx++) {
    c3_b_tmp_data[c3_fidx] = 1 + c3_fidx;
  }

  c3_loop_ub = c3_tmp_sizes - 1;
  for (c3_fidx = 0; c3_fidx <= c3_loop_ub; c3_fidx++) {
    c3_pkt[c3_tmp_data[c3_fidx] - 1] = c3_lf_bytes[c3_b_tmp_data[c3_fidx] - 1];
  }

  chartInstance->c3_replyId_not_empty = TRUE;
  chartInstance->c3_replyId++;
  if (chartInstance->c3_replyId == 255.0) {
    chartInstance->c3_replyId = 1.0;
  }

  c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[2].dtype,
                       chartInstance->c3_replyId, c3_lf_bytes);
  if (1.0 > c3_cmdDef[2].fsize) {
    c3_tmp_sizes = 0;
  } else {
    c3_tmp_sizes = (int32_T)c3_cmdDef[2].fsize;
  }

  c3_bidx = (c3_cmdDef[2].offset + c3_cmdDef[2].fsize) - 1.0;
  if (c3_cmdDef[2].offset > c3_bidx) {
    c3_fidx = 1;
    c3_i7 = 0;
  } else {
    c3_fidx = (int32_T)c3_cmdDef[2].offset;
    c3_i7 = (int32_T)c3_bidx;
  }

  c3_loop_ub = c3_i7 - c3_fidx;
  for (c3_i7 = 0; c3_i7 <= c3_loop_ub; c3_i7++) {
    c3_tmp_data[c3_i7] = c3_fidx + c3_i7;
  }

  c3_loop_ub = c3_tmp_sizes - 1;
  for (c3_fidx = 0; c3_fidx <= c3_loop_ub; c3_fidx++) {
    c3_b_tmp_data[c3_fidx] = 1 + c3_fidx;
  }

  c3_loop_ub = c3_tmp_sizes - 1;
  for (c3_fidx = 0; c3_fidx <= c3_loop_ub; c3_fidx++) {
    c3_pkt[c3_tmp_data[c3_fidx] - 1] = c3_lf_bytes[c3_b_tmp_data[c3_fidx] - 1];
  }

  for (c3_fidx = 0; c3_fidx < 4; c3_fidx++) {
    c3_pkt[(int32_T)(*c3_pktLen + (1.0 + (real_T)c3_fidx)) - 1] = c3_uv3[c3_fidx];
  }

  *c3_pktLen += 4.0;
}

static void c3_USRP2RuntimeControl(SFc3_commsdrhwInstanceStruct *chartInstance,
  real_T c3_varargin_3, real_T *c3_pktLength, uint8_T c3_pkt[255], uint8_T
  *c3_b_replyId, real_T *c3_varargout_1_ValidMask, real_T *c3_varargout_1_Fc,
  real_T *c3_varargout_1_Gain, real_T *c3_varargout_1_DecimInterp, real_T
  *c3_varargout_1_ScaleI, real_T *c3_varargout_1_ScaleQ)
{
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_cmdDef[18];
  int32_T c3_i8;
  static char_T c3_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c3_u[23];
  const mxArray *c3_y = NULL;
  char_T c3_b_u[40];
  static char_T c3_cv5[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  const mxArray *c3_b_y = NULL;
  char_T c3_c_u[23];
  const mxArray *c3_c_y = NULL;
  char_T c3_d_u[40];
  const mxArray *c3_d_y = NULL;
  chartInstance->c3_lastCF_not_empty = TRUE;
  chartInstance->c3_lastG_not_empty = TRUE;
  chartInstance->c3_lastDI_not_empty = TRUE;
  chartInstance->c3_lastI_not_empty = TRUE;
  chartInstance->c3_lastQ_not_empty = TRUE;
  c3_USRP2CmdDef(chartInstance, USRP2Opcodes_ConfigRx, c3_cmdDef);
  *c3_varargout_1_Gain = chartInstance->c3_lastG;
  *c3_varargout_1_DecimInterp = chartInstance->c3_lastDI;
  *c3_varargout_1_ScaleI = chartInstance->c3_lastI;
  *c3_varargout_1_ScaleQ = chartInstance->c3_lastQ;
  *c3_varargout_1_Fc = c3_varargin_3;
  *c3_varargout_1_ValidMask = 2.0;
  if (c3_cmdDef[(int32_T)USRP2CmdFields_CenterFreq - 1].fsize == 0.0) {
    for (c3_i8 = 0; c3_i8 < 23; c3_i8++) {
      c3_u[c3_i8] = c3_varargin_1[c3_i8];
    }

    c3_y = NULL;
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c3_b_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_CenterFreq;
    for (c3_i8 = 0; c3_i8 < 39; c3_i8++) {
      c3_b_u[c3_i8 + 1] = c3_cv5[c3_i8];
    }

    c3_b_y = NULL;
    sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c3_y, 14, c3_b_y);
  } else {
    c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)
                         USRP2CmdFields_CenterFreq - 1].dtype, c3_varargin_3,
                         c3_cmdDef[(int32_T)USRP2CmdFields_CenterFreq - 1].bytes);
  }

  if (c3_cmdDef[(int32_T)USRP2CmdFields_Valid - 1].fsize == 0.0) {
    for (c3_i8 = 0; c3_i8 < 23; c3_i8++) {
      c3_c_u[c3_i8] = c3_varargin_1[c3_i8];
    }

    c3_c_y = NULL;
    sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_c_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c3_d_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Valid;
    for (c3_i8 = 0; c3_i8 < 39; c3_i8++) {
      c3_d_u[c3_i8 + 1] = c3_cv5[c3_i8];
    }

    c3_d_y = NULL;
    sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_d_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c3_c_y, 14, c3_d_y);
  } else {
    c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)USRP2CmdFields_Valid
                         - 1].dtype, 2.0, c3_cmdDef[(int32_T)
                         USRP2CmdFields_Valid - 1].bytes);
  }

  c3_USRP2Cmd2Pkt(chartInstance, c3_cmdDef, c3_pkt, c3_pktLength);
  chartInstance->c3_lastCF = c3_varargin_3;
  chartInstance->c3_lastG = *c3_varargout_1_Gain;
  chartInstance->c3_lastDI = *c3_varargout_1_DecimInterp;
  chartInstance->c3_lastI = *c3_varargout_1_ScaleI;
  chartInstance->c3_lastQ = *c3_varargout_1_ScaleQ;
  *c3_b_replyId = c3_pkt[2];
}

static void c3_b_USRP2RuntimeControl(SFc3_commsdrhwInstanceStruct *chartInstance,
  real_T c3_varargin_3, real_T *c3_pktLength, uint8_T c3_pkt[255], uint8_T
  *c3_b_replyId, real_T *c3_varargout_1_ValidMask, real_T *c3_varargout_1_Fc,
  real_T *c3_varargout_1_Gain, real_T *c3_varargout_1_DecimInterp, real_T
  *c3_varargout_1_ScaleI, real_T *c3_varargout_1_ScaleQ)
{
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_cmdDef[18];
  int32_T c3_i9;
  static char_T c3_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c3_u[23];
  const mxArray *c3_y = NULL;
  char_T c3_b_u[40];
  static char_T c3_cv6[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  const mxArray *c3_b_y = NULL;
  char_T c3_c_u[23];
  const mxArray *c3_c_y = NULL;
  char_T c3_d_u[40];
  const mxArray *c3_d_y = NULL;
  chartInstance->c3_lastCF_not_empty = TRUE;
  chartInstance->c3_lastG_not_empty = TRUE;
  chartInstance->c3_lastDI_not_empty = TRUE;
  chartInstance->c3_lastI_not_empty = TRUE;
  chartInstance->c3_lastQ_not_empty = TRUE;
  c3_USRP2CmdDef(chartInstance, USRP2Opcodes_ConfigRx, c3_cmdDef);
  *c3_varargout_1_Fc = chartInstance->c3_lastCF;
  *c3_varargout_1_DecimInterp = chartInstance->c3_lastDI;
  *c3_varargout_1_ScaleI = chartInstance->c3_lastI;
  *c3_varargout_1_ScaleQ = chartInstance->c3_lastQ;
  *c3_varargout_1_Gain = c3_varargin_3;
  *c3_varargout_1_ValidMask = 1.0;
  if (c3_cmdDef[(int32_T)USRP2CmdFields_Gain - 1].fsize == 0.0) {
    for (c3_i9 = 0; c3_i9 < 23; c3_i9++) {
      c3_u[c3_i9] = c3_varargin_1[c3_i9];
    }

    c3_y = NULL;
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c3_b_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Gain;
    for (c3_i9 = 0; c3_i9 < 39; c3_i9++) {
      c3_b_u[c3_i9 + 1] = c3_cv6[c3_i9];
    }

    c3_b_y = NULL;
    sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c3_y, 14, c3_b_y);
  } else {
    c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)USRP2CmdFields_Gain -
                         1].dtype, c3_varargin_3, c3_cmdDef[(int32_T)
                         USRP2CmdFields_Gain - 1].bytes);
  }

  if (c3_cmdDef[(int32_T)USRP2CmdFields_Valid - 1].fsize == 0.0) {
    for (c3_i9 = 0; c3_i9 < 23; c3_i9++) {
      c3_c_u[c3_i9] = c3_varargin_1[c3_i9];
    }

    c3_c_y = NULL;
    sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_c_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c3_d_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Valid;
    for (c3_i9 = 0; c3_i9 < 39; c3_i9++) {
      c3_d_u[c3_i9 + 1] = c3_cv6[c3_i9];
    }

    c3_d_y = NULL;
    sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_d_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c3_c_y, 14, c3_d_y);
  } else {
    c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)USRP2CmdFields_Valid
                         - 1].dtype, 1.0, c3_cmdDef[(int32_T)
                         USRP2CmdFields_Valid - 1].bytes);
  }

  c3_USRP2Cmd2Pkt(chartInstance, c3_cmdDef, c3_pkt, c3_pktLength);
  chartInstance->c3_lastCF = *c3_varargout_1_Fc;
  chartInstance->c3_lastG = c3_varargin_3;
  chartInstance->c3_lastDI = *c3_varargout_1_DecimInterp;
  chartInstance->c3_lastI = *c3_varargout_1_ScaleI;
  chartInstance->c3_lastQ = *c3_varargout_1_ScaleQ;
  *c3_b_replyId = c3_pkt[2];
}

static void c3_c_USRP2RuntimeControl(SFc3_commsdrhwInstanceStruct *chartInstance,
  real_T c3_varargin_3, real_T *c3_pktLength, uint8_T c3_pkt[255], uint8_T
  *c3_b_replyId, real_T *c3_varargout_1_ValidMask, real_T *c3_varargout_1_Fc,
  real_T *c3_varargout_1_Gain, real_T *c3_varargout_1_DecimInterp, real_T
  *c3_varargout_1_ScaleI, real_T *c3_varargout_1_ScaleQ)
{
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_cmdDef[18];
  int32_T c3_i10;
  static char_T c3_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c3_u[23];
  const mxArray *c3_y = NULL;
  char_T c3_b_u[40];
  static char_T c3_cv7[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  const mxArray *c3_b_y = NULL;
  char_T c3_c_u[23];
  const mxArray *c3_c_y = NULL;
  char_T c3_d_u[40];
  const mxArray *c3_d_y = NULL;
  chartInstance->c3_lastCF_not_empty = TRUE;
  chartInstance->c3_lastG_not_empty = TRUE;
  chartInstance->c3_lastDI_not_empty = TRUE;
  chartInstance->c3_lastI_not_empty = TRUE;
  chartInstance->c3_lastQ_not_empty = TRUE;
  c3_USRP2CmdDef(chartInstance, USRP2Opcodes_ConfigRx, c3_cmdDef);
  *c3_varargout_1_Fc = chartInstance->c3_lastCF;
  *c3_varargout_1_Gain = chartInstance->c3_lastG;
  *c3_varargout_1_ScaleI = chartInstance->c3_lastI;
  *c3_varargout_1_ScaleQ = chartInstance->c3_lastQ;
  *c3_varargout_1_DecimInterp = c3_varargin_3;
  *c3_varargout_1_ValidMask = 4.0;
  if (c3_cmdDef[(int32_T)USRP2CmdFields_Decimation - 1].fsize == 0.0) {
    for (c3_i10 = 0; c3_i10 < 23; c3_i10++) {
      c3_u[c3_i10] = c3_varargin_1[c3_i10];
    }

    c3_y = NULL;
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c3_b_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Decimation;
    for (c3_i10 = 0; c3_i10 < 39; c3_i10++) {
      c3_b_u[c3_i10 + 1] = c3_cv7[c3_i10];
    }

    c3_b_y = NULL;
    sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c3_y, 14, c3_b_y);
  } else {
    c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)
                         USRP2CmdFields_Decimation - 1].dtype, c3_varargin_3,
                         c3_cmdDef[(int32_T)USRP2CmdFields_Decimation - 1].bytes);
  }

  if (c3_cmdDef[(int32_T)USRP2CmdFields_Valid - 1].fsize == 0.0) {
    for (c3_i10 = 0; c3_i10 < 23; c3_i10++) {
      c3_c_u[c3_i10] = c3_varargin_1[c3_i10];
    }

    c3_c_y = NULL;
    sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_c_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c3_d_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Valid;
    for (c3_i10 = 0; c3_i10 < 39; c3_i10++) {
      c3_d_u[c3_i10 + 1] = c3_cv7[c3_i10];
    }

    c3_d_y = NULL;
    sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_d_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c3_c_y, 14, c3_d_y);
  } else {
    c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)USRP2CmdFields_Valid
                         - 1].dtype, 4.0, c3_cmdDef[(int32_T)
                         USRP2CmdFields_Valid - 1].bytes);
  }

  c3_USRP2Cmd2Pkt(chartInstance, c3_cmdDef, c3_pkt, c3_pktLength);
  chartInstance->c3_lastCF = *c3_varargout_1_Fc;
  chartInstance->c3_lastG = *c3_varargout_1_Gain;
  chartInstance->c3_lastDI = c3_varargin_3;
  chartInstance->c3_lastI = *c3_varargout_1_ScaleI;
  chartInstance->c3_lastQ = *c3_varargout_1_ScaleQ;
  *c3_b_replyId = c3_pkt[2];
}

static void c3_b_USRP2CmdDef(SFc3_commsdrhwInstanceStruct *chartInstance,
  uint8_T c3_cmd, c3_s7P91ApZ2CkwDPZE5FamWSB c3_cmdDef[18])
{
  int32_T c3_i11;
  static c3_s7P91ApZ2CkwDPZE5FamWSB c3_r2 = { 0.0, 0.0,
    USRP2FieldDtypes_usrp2_uint8_T, { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
      0U, 0U, 0U, 0U, 0U } };

  c3_s7P91ApZ2CkwDPZE5FamWSB c3_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_b_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_c_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_d_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_e_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_f_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_g_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_h_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_i_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_j_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_k_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_l_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_m_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_n_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_o_expl_temp;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_p_expl_temp;
  for (c3_i11 = 0; c3_i11 < 18; c3_i11++) {
    c3_cmdDef[c3_i11] = c3_r2;
  }

  c3_b_l_fdef(chartInstance, 1.0, 1.0, USRP2FieldDtypes_usrp2_uint8_T, (real_T)
              c3_cmd, &c3_cmdDef[(int32_T)USRP2CmdFields_Opcode - 1].offset,
              &c3_cmdDef[(int32_T)USRP2CmdFields_Opcode - 1].fsize, &c3_cmdDef
              [(int32_T)USRP2CmdFields_Opcode - 1].dtype, c3_cmdDef[(int32_T)
              USRP2CmdFields_Opcode - 1].bytes);
  c3_l_fdef(chartInstance, 2.0, 1.0, USRP2FieldDtypes_usrp2_uint8_T, &c3_cmdDef
            [(int32_T)USRP2CmdFields_Length - 1].offset, &c3_cmdDef[(int32_T)
            USRP2CmdFields_Length - 1].fsize, &c3_cmdDef[(int32_T)
            USRP2CmdFields_Length - 1].dtype, c3_cmdDef[(int32_T)
            USRP2CmdFields_Length - 1].bytes);
  c3_expl_temp.offset = 3.0;
  c3_expl_temp.fsize = 1.0;
  c3_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint8_T;
  for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
    c3_expl_temp.bytes[c3_i11] = 0U;
  }

  c3_cmdDef[(int32_T)USRP2CmdFields_ReplyId - 1] = c3_expl_temp;
  c3_b_expl_temp.offset = 4.0;
  c3_b_expl_temp.fsize = 1.0;
  c3_b_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint8_T;
  for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
    c3_b_expl_temp.bytes[c3_i11] = 0U;
  }

  c3_cmdDef[(int32_T)USRP2CmdFields_Ok - 1] = c3_b_expl_temp;
  switch (c3_cmd) {
   case 129:
    c3_c_expl_temp.offset = 5.0;
    c3_c_expl_temp.fsize = 6.0;
    c3_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_c_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_MacAddr - 1] = c3_c_expl_temp;
    c3_d_expl_temp.offset = 11.0;
    c3_d_expl_temp.fsize = 2.0;
    c3_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_d_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_HwRev - 1] = c3_d_expl_temp;
    c3_e_expl_temp.offset = 13.0;
    c3_e_expl_temp.fsize = 8.0;
    c3_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_e_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_FpgaMd5Lo - 1] = c3_e_expl_temp;
    c3_f_expl_temp.offset = 21.0;
    c3_f_expl_temp.fsize = 8.0;
    c3_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_f_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_FpgaMd5Hi - 1] = c3_f_expl_temp;
    c3_g_expl_temp.offset = 29.0;
    c3_g_expl_temp.fsize = 8.0;
    c3_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_g_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_FirmwareMd5Lo - 1] = c3_g_expl_temp;
    c3_h_expl_temp.offset = 37.0;
    c3_h_expl_temp.fsize = 8.0;
    c3_h_expl_temp.dtype = USRP2FieldDtypes_usrp2_byteArray_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_h_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_FirmwareMd5Hi - 1] = c3_h_expl_temp;
    break;

   case 4:
    c3_c_expl_temp.offset = 5.0;
    c3_c_expl_temp.fsize = 2.0;
    c3_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_c_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_Valid - 1] = c3_c_expl_temp;
    c3_d_expl_temp.offset = 7.0;
    c3_d_expl_temp.fsize = 2.0;
    c3_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_d_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_Gain - 1] = c3_d_expl_temp;
    c3_e_expl_temp.offset = 9.0;
    c3_e_expl_temp.fsize = 8.0;
    c3_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_e_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_CenterFreq - 1] = c3_e_expl_temp;
    c3_f_expl_temp.offset = 17.0;
    c3_f_expl_temp.fsize = 4.0;
    c3_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_f_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_Decimation - 1] = c3_f_expl_temp;
    c3_g_expl_temp.offset = 21.0;
    c3_g_expl_temp.fsize = 2.0;
    c3_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_g_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_ScaleI - 1] = c3_g_expl_temp;
    c3_h_expl_temp.offset = 23.0;
    c3_h_expl_temp.fsize = 2.0;
    c3_h_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_h_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_ScaleQ - 1] = c3_h_expl_temp;
    break;

   case 132:
    c3_c_expl_temp.offset = 5.0;
    c3_c_expl_temp.fsize = 2.0;
    c3_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_c_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_ConfigOk - 1] = c3_c_expl_temp;
    c3_d_expl_temp.offset = 7.0;
    c3_d_expl_temp.fsize = 2.0;
    c3_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_d_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_SpectrumInverted - 1] = c3_d_expl_temp;
    c3_e_expl_temp.offset = 9.0;
    c3_e_expl_temp.fsize = 8.0;
    c3_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_e_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_BasebandFreq - 1] = c3_e_expl_temp;
    c3_f_expl_temp.offset = 17.0;
    c3_f_expl_temp.fsize = 8.0;
    c3_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_f_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_DdcFreq - 1] = c3_f_expl_temp;
    c3_g_expl_temp.offset = 25.0;
    c3_g_expl_temp.fsize = 8.0;
    c3_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_g_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_ResidualFreq - 1] = c3_g_expl_temp;
    break;

   case 5:
    c3_c_expl_temp.offset = 5.0;
    c3_c_expl_temp.fsize = 2.0;
    c3_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_c_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_Valid - 1] = c3_c_expl_temp;
    c3_d_expl_temp.offset = 7.0;
    c3_d_expl_temp.fsize = 2.0;
    c3_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_d_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_Gain - 1] = c3_d_expl_temp;
    c3_e_expl_temp.offset = 9.0;
    c3_e_expl_temp.fsize = 8.0;
    c3_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_e_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_CenterFreq - 1] = c3_e_expl_temp;
    c3_f_expl_temp.offset = 17.0;
    c3_f_expl_temp.fsize = 4.0;
    c3_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_f_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_Interpolation - 1] = c3_f_expl_temp;
    c3_g_expl_temp.offset = 21.0;
    c3_g_expl_temp.fsize = 2.0;
    c3_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_g_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_ScaleI - 1] = c3_g_expl_temp;
    c3_h_expl_temp.offset = 23.0;
    c3_h_expl_temp.fsize = 2.0;
    c3_h_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_h_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_ScaleQ - 1] = c3_h_expl_temp;
    break;

   case 133:
    c3_c_expl_temp.offset = 5.0;
    c3_c_expl_temp.fsize = 2.0;
    c3_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_c_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_ConfigOk - 1] = c3_c_expl_temp;
    c3_d_expl_temp.offset = 7.0;
    c3_d_expl_temp.fsize = 2.0;
    c3_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_d_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_SpectrumInverted - 1] = c3_d_expl_temp;
    c3_e_expl_temp.offset = 9.0;
    c3_e_expl_temp.fsize = 8.0;
    c3_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_e_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_BasebandFreq - 1] = c3_e_expl_temp;
    c3_f_expl_temp.offset = 17.0;
    c3_f_expl_temp.fsize = 8.0;
    c3_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_f_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_DucFreq - 1] = c3_f_expl_temp;
    c3_g_expl_temp.offset = 25.0;
    c3_g_expl_temp.fsize = 8.0;
    c3_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_g_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_ResidualFreq - 1] = c3_g_expl_temp;
    break;

   case 6:
    c3_c_expl_temp.offset = 5.0;
    c3_c_expl_temp.fsize = 4.0;
    c3_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_c_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_ItemsPerFrame - 1] = c3_c_expl_temp;
    c3_d_expl_temp.offset = 9.0;
    c3_d_expl_temp.fsize = 4.0;
    c3_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_d_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_TimeInt - 1] = c3_d_expl_temp;
    c3_e_expl_temp.offset = 13.0;
    c3_e_expl_temp.fsize = 4.0;
    c3_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_e_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_TimeFrac - 1] = c3_e_expl_temp;
    break;

   case 137:
    c3_c_expl_temp.offset = 5.0;
    c3_c_expl_temp.fsize = 4.0;
    c3_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_c_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_TxDbId - 1] = c3_c_expl_temp;
    c3_d_expl_temp.offset = 9.0;
    c3_d_expl_temp.fsize = 8.0;
    c3_d_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_d_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_TxFreqMin - 1] = c3_d_expl_temp;
    c3_e_expl_temp.offset = 17.0;
    c3_e_expl_temp.fsize = 8.0;
    c3_e_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_e_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_TxFreqMax - 1] = c3_e_expl_temp;
    c3_f_expl_temp.offset = 25.0;
    c3_f_expl_temp.fsize = 2.0;
    c3_f_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_f_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_TxGainMin - 1] = c3_f_expl_temp;
    c3_g_expl_temp.offset = 27.0;
    c3_g_expl_temp.fsize = 2.0;
    c3_g_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_g_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_TxGainMax - 1] = c3_g_expl_temp;
    c3_h_expl_temp.offset = 29.0;
    c3_h_expl_temp.fsize = 2.0;
    c3_h_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_h_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_TxGainStepSize - 1] = c3_h_expl_temp;
    c3_i_expl_temp.offset = 31.0;
    c3_i_expl_temp.fsize = 2.0;
    c3_i_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_i_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_TxDbReserved - 1] = c3_i_expl_temp;
    c3_j_expl_temp.offset = 33.0;
    c3_j_expl_temp.fsize = 4.0;
    c3_j_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint32_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_j_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_RxDbId - 1] = c3_j_expl_temp;
    c3_k_expl_temp.offset = 37.0;
    c3_k_expl_temp.fsize = 8.0;
    c3_k_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_k_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_RxFreqMin - 1] = c3_k_expl_temp;
    c3_l_expl_temp.offset = 45.0;
    c3_l_expl_temp.fsize = 8.0;
    c3_l_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_l_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_RxFreqMax - 1] = c3_l_expl_temp;
    c3_m_expl_temp.offset = 53.0;
    c3_m_expl_temp.fsize = 2.0;
    c3_m_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_m_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_RxGainMin - 1] = c3_m_expl_temp;
    c3_n_expl_temp.offset = 55.0;
    c3_n_expl_temp.fsize = 2.0;
    c3_n_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_n_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_RxGainMax - 1] = c3_n_expl_temp;
    c3_o_expl_temp.offset = 57.0;
    c3_o_expl_temp.fsize = 2.0;
    c3_o_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix16_En7_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_o_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_RxGainStepSize - 1] = c3_o_expl_temp;
    c3_p_expl_temp.offset = 59.0;
    c3_p_expl_temp.fsize = 2.0;
    c3_p_expl_temp.dtype = USRP2FieldDtypes_usrp2_uint16_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_p_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_RxDbReserved - 1] = c3_p_expl_temp;
    break;

   case 14:
    c3_c_expl_temp.offset = 5.0;
    c3_c_expl_temp.fsize = 8.0;
    c3_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_c_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_FreqOffset - 1] = c3_c_expl_temp;
    break;

   case 13:
    c3_c_expl_temp.offset = 5.0;
    c3_c_expl_temp.fsize = 8.0;
    c3_c_expl_temp.dtype = USRP2FieldDtypes_usrp2_sfix64_En20_T;
    for (c3_i11 = 0; c3_i11 < 16; c3_i11++) {
      c3_c_expl_temp.bytes[c3_i11] = 0U;
    }

    c3_cmdDef[(int32_T)USRP2CmdFields_FreqOffset - 1] = c3_c_expl_temp;
    break;
  }
}

static void c3_USRP2RuntimeControlReplies(SFc3_commsdrhwInstanceStruct
  *chartInstance, uint8_T c3_pkt[255], uint16_T c3_pktLen, char_T
  c3_errStr_data[56], int32_T c3_errStr_sizes[2], real_T *c3_b_replyId)
{
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_replyCmd[18];
  int32_T c3_i12;
  static char_T c3_cv8[45] = { 'U', 'S', 'R', 'P', '2', ' ', 'p', 'a', 'c', 'k',
    'e', 't', ' ', 'r', 'e', 'c', 'e', 'i', 'v', 'e', 'd', ' ', 'w', 'i', 't',
    'h', 'o', 'u', 't', ' ', 'a', ' ', 'v', 'a', 'l', 'i', 'd', ' ', 'h', 'e',
    'a', 'd', 'e', 'r', '.' };

  real_T c3_parsedBytes;
  int32_T c3_fidx;
  boolean_T c3_exitg1;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_cf;
  real_T c3_val;
  int32_T c3_i13;
  int32_T c3_loop_ub;
  int32_T c3_tmp_sizes;
  int32_T c3_tmp_data[8];
  int32_T c3_b_tmp_data[66];
  uint16_T c3_u10;
  static char_T c3_cv9[56] = { 'U', 'S', 'R', 'P', '2', ' ', 'p', 'a', 'c', 'k',
    'e', 't', ' ', 'r', 'e', 'c', 'e', 'i', 'v', 'e', 'd', ' ', 'w', 'i', 't',
    'h', ' ', 'a', 'n', ' ', 'i', 'n', 'c', 'o', 'r', 'r', 'e', 'c', 't', ' ',
    'n', 'u', 'm', 'b', 'e', 'r', ' ', 'o', 'f', ' ', 'b', 'y', 't', 'e', 's',
    '.' };

  char_T c3_cv10[40];
  static char_T c3_cv11[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  char_T c3_b_errStr_data[40];
  static char_T c3_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c3_u[23];
  const mxArray *c3_y = NULL;
  char_T c3_u_data[40];
  const mxArray *c3_b_y = NULL;
  char_T c3_b_u[23];
  const mxArray *c3_c_y = NULL;
  char_T c3_b_u_data[40];
  const mxArray *c3_d_y = NULL;
  boolean_T c3_guard3 = FALSE;
  boolean_T c3_guard4 = FALSE;
  char_T c3_c_u[23];
  const mxArray *c3_e_y = NULL;
  char_T c3_c_u_data[40];
  const mxArray *c3_f_y = NULL;
  boolean_T c3_ok;
  boolean_T c3_guard1 = FALSE;
  boolean_T c3_guard2 = FALSE;
  static char_T c3_cv12[41] = { 'B', 'o', 'a', 'r', 'd', ' ', 'r', 'e', 'p', 'o',
    'r', 't', 'e', 'd', ' ', 'a', ' ', 's', 't', 'a', 'r', 't', ' ', 's', 't',
    'r', 'e', 'a', 'm', 'i', 'n', 'g', ' ', 'f', 'a', 'i', 'l', 'u', 'r', 'e',
    '.' };

  static char_T c3_cv13[40] = { 'B', 'o', 'a', 'r', 'd', ' ', 'r', 'e', 'p', 'o',
    'r', 't', 'e', 'd', ' ', 'a', ' ', 's', 't', 'o', 'p', ' ', 's', 't', 'r',
    'e', 'a', 'm', 'i', 'n', 'g', ' ', 'f', 'a', 'i', 'l', 'u', 'r', 'e', '.' };

  static char_T c3_cv14[45] = { 'B', 'o', 'a', 'r', 'd', ' ', 'r', 'e', 'p', 'o',
    'r', 't', 'e', 'd', ' ', 'a', ' ', 'd', 'a', 'u', 'g', 'h', 't', 'e', 'r',
    'b', 'o', 'a', 'r', 'd', ' ', 'r', 'e', 's', 'e', 't', ' ', 'f', 'a', 'i',
    'l', 'u', 'r', 'e', '.' };

  static char_T c3_cv15[56] = { 'B', 'o', 'a', 'r', 'd', ' ', 'r', 'e', 'p', 'o',
    'r', 't', 'e', 'd', ' ', 'a', ' ', 'f', 'r', 'e', 'q', 'u', 'e', 'n', 'c',
    'y', ' ', 'o', 'f', 'f', 's', 'e', 't', ' ', 'c', 'o', 'n', 'f', 'i', 'g',
    'u', 'r', 'a', 't', 'i', 'o', 'n', ' ', 'f', 'a', 'i', 'l', 'u', 'r', 'e',
    '.' };

  static char_T c3_cv16[39] = { 'B', 'o', 'a', 'r', 'd', ' ', 'r', 'e', 'p', 'o',
    'r', 't', 'e', 'd', ' ', 'a', ' ', 'c', 'o', 'n', 'f', 'i', 'g', 'u', 'r',
    'a', 't', 'i', 'o', 'n', ' ', 'f', 'a', 'i', 'l', 'u', 'r', 'e', '.' };

  const mxArray *c3_g_y = NULL;
  char_T c3_d_u[23];
  const mxArray *c3_h_y = NULL;
  char_T c3_d_u_data[40];
  *c3_b_replyId = 255.0;
  c3_USRP2CmdDef(chartInstance, USRP2Opcodes_EOP, c3_replyCmd);
  c3_errStr_sizes[0] = 1;
  c3_errStr_sizes[1] = 0;
  if (c3_pktLen < 4) {
    c3_errStr_sizes[0] = 1;
    c3_errStr_sizes[1] = 45;
    for (c3_i12 = 0; c3_i12 < 45; c3_i12++) {
      c3_errStr_data[c3_i12] = c3_cv8[c3_i12];
    }
  } else {
    c3_b_USRP2CmdDef(chartInstance, c3_pkt[0], c3_replyCmd);
    c3_parsedBytes = 0.0;
    c3_fidx = 0;
    c3_exitg1 = 0U;
    while ((c3_exitg1 == 0U) && (c3_fidx + 1 <= 18)) {
      c3_cf = c3_replyCmd[c3_fidx];
      if (c3_replyCmd[c3_fidx].fsize == 0.0) {
        c3_exitg1 = 1U;
      } else {
        c3_val = (c3_replyCmd[c3_fidx].offset + c3_replyCmd[c3_fidx].fsize) -
          1.0;
        if (c3_replyCmd[c3_fidx].offset > c3_val) {
          c3_i12 = 1;
          c3_i13 = 0;
        } else {
          c3_i12 = (int32_T)c3_replyCmd[c3_fidx].offset;
          c3_i13 = (int32_T)c3_val;
        }

        c3_loop_ub = (int32_T)c3_replyCmd[c3_fidx].fsize - 1;
        for (c3_tmp_sizes = 0; c3_tmp_sizes <= c3_loop_ub; c3_tmp_sizes++) {
          c3_tmp_data[c3_tmp_sizes] = 1 + c3_tmp_sizes;
        }

        c3_tmp_sizes = c3_i13 - c3_i12;
        c3_loop_ub = c3_i13 - c3_i12;
        for (c3_i13 = 0; c3_i13 <= c3_loop_ub; c3_i13++) {
          c3_b_tmp_data[c3_i13] = c3_i12 + c3_i13;
        }

        for (c3_i12 = 0; c3_i12 <= c3_tmp_sizes; c3_i12++) {
          c3_cf.bytes[c3_tmp_data[c3_i12] - 1] = c3_pkt[c3_b_tmp_data[c3_i12] -
            1];
        }

        c3_replyCmd[c3_fidx] = c3_cf;
        c3_parsedBytes += c3_cf.fsize;
        c3_fidx++;
      }
    }

    if (c3_parsedBytes != (real_T)c3_pktLen) {
      c3_val = (real_T)c3_pktLen - c3_parsedBytes;
      c3_val = c3_val < 0.0 ? muDoubleScalarCeil(c3_val - 0.5) :
        muDoubleScalarFloor(c3_val + 0.5);
      if (c3_val < 65536.0) {
        if (c3_val >= 0.0) {
          c3_u10 = (uint16_T)c3_val;
        } else {
          c3_u10 = 0U;
        }
      } else if (c3_val >= 65536.0) {
        c3_u10 = MAX_uint16_T;
      } else {
        c3_u10 = 0U;
      }

      if ((c3_u10 != 4) || (c3_pkt[(int32_T)(c3_parsedBytes + 1.0) - 1] != 0) ||
          (c3_pkt[(int32_T)(c3_parsedBytes + 2.0) - 1] != 4) || (c3_pkt[(int32_T)
           (c3_parsedBytes + 3.0) - 1] != 0) || (c3_pkt[(int32_T)(c3_parsedBytes
            + 4.0) - 1] != 0)) {
        c3_errStr_sizes[0] = 1;
        c3_errStr_sizes[1] = 56;
        for (c3_i12 = 0; c3_i12 < 56; c3_i12++) {
          c3_errStr_data[c3_i12] = c3_cv9[c3_i12];
        }
      }
    }
  }

  if (c3_errStr_sizes[1] == 0) {
    c3_tmp_sizes = 0;
    c3_parsedBytes = 0.0;
    if (c3_replyCmd[0].fsize == 0.0) {
      c3_cv10[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Opcode;
      for (c3_i12 = 0; c3_i12 < 39; c3_i12++) {
        c3_cv10[c3_i12 + 1] = c3_cv11[c3_i12];
      }

      c3_tmp_sizes = 40;
      for (c3_i12 = 0; c3_i12 < 40; c3_i12++) {
        c3_b_errStr_data[c3_i12] = c3_cv10[c3_i12];
      }

      for (c3_i12 = 0; c3_i12 < 23; c3_i12++) {
        c3_u[c3_i12] = c3_varargin_1[c3_i12];
      }

      c3_y = NULL;
      sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 23));
      for (c3_i12 = 0; c3_i12 < 40; c3_i12++) {
        c3_u_data[c3_i12] = c3_b_errStr_data[c3_i12];
      }

      c3_b_y = NULL;
      sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_u_data, 10, 0U, 1U, 0U, 2, 1,
        40));
      sf_mex_call("error", 0U, 2U, 14, c3_y, 14, c3_b_y);
    } else {
      c3_parsedBytes = c3_USRP2UnpackFieldVal(chartInstance, c3_replyCmd
        [(int32_T)USRP2CmdFields_Opcode - 1].dtype, c3_replyCmd[0].bytes);
    }

    c3_errStr_sizes[0] = 1;
    c3_errStr_sizes[1] = c3_tmp_sizes;
    c3_loop_ub = c3_tmp_sizes - 1;
    for (c3_i12 = 0; c3_i12 <= c3_loop_ub; c3_i12++) {
      c3_errStr_data[c3_i12] = c3_b_errStr_data[c3_i12];
    }

    if (c3_tmp_sizes == 0) {
      c3_tmp_sizes = 0;
      *c3_b_replyId = 0.0;
      if (c3_replyCmd[2].fsize == 0.0) {
        c3_cv10[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_ReplyId;
        for (c3_i12 = 0; c3_i12 < 39; c3_i12++) {
          c3_cv10[c3_i12 + 1] = c3_cv11[c3_i12];
        }

        c3_tmp_sizes = 40;
        for (c3_i12 = 0; c3_i12 < 40; c3_i12++) {
          c3_b_errStr_data[c3_i12] = c3_cv10[c3_i12];
        }

        for (c3_i12 = 0; c3_i12 < 23; c3_i12++) {
          c3_b_u[c3_i12] = c3_varargin_1[c3_i12];
        }

        c3_c_y = NULL;
        sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1,
          23));
        for (c3_i12 = 0; c3_i12 < 40; c3_i12++) {
          c3_b_u_data[c3_i12] = c3_b_errStr_data[c3_i12];
        }

        c3_d_y = NULL;
        sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_b_u_data, 10, 0U, 1U, 0U, 2,
          1, 40));
        sf_mex_call("error", 0U, 2U, 14, c3_c_y, 14, c3_d_y);
      } else {
        *c3_b_replyId = c3_USRP2UnpackFieldVal(chartInstance, c3_replyCmd
          [(int32_T)USRP2CmdFields_ReplyId - 1].dtype, c3_replyCmd[2].bytes);
      }

      c3_errStr_sizes[0] = 1;
      c3_errStr_sizes[1] = c3_tmp_sizes;
      c3_loop_ub = c3_tmp_sizes - 1;
      for (c3_i12 = 0; c3_i12 <= c3_loop_ub; c3_i12++) {
        c3_errStr_data[c3_i12] = c3_b_errStr_data[c3_i12];
      }

      if (c3_tmp_sizes == 0) {
        c3_guard3 = FALSE;
        c3_guard4 = FALSE;
        switch ((int32_T)c3_parsedBytes) {
         case 129:
          c3_guard3 = TRUE;
          break;

         case 137:
          c3_guard3 = TRUE;
          break;

         case 132:
          c3_guard4 = TRUE;
          break;

         case 133:
          c3_guard4 = TRUE;
          break;

         default:
          c3_val = 0.0;
          if (c3_replyCmd[3].fsize == 0.0) {
            for (c3_i12 = 0; c3_i12 < 23; c3_i12++) {
              c3_d_u[c3_i12] = c3_varargin_1[c3_i12];
            }

            c3_g_y = NULL;
            sf_mex_assign(&c3_g_y, sf_mex_create("y", c3_d_u, 10, 0U, 1U, 0U, 2,
              1, 23));
            c3_cv10[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Ok;
            for (c3_i12 = 0; c3_i12 < 39; c3_i12++) {
              c3_cv10[c3_i12 + 1] = c3_cv11[c3_i12];
            }

            for (c3_i12 = 0; c3_i12 < 40; c3_i12++) {
              c3_d_u_data[c3_i12] = c3_cv10[c3_i12];
            }

            c3_h_y = NULL;
            sf_mex_assign(&c3_h_y, sf_mex_create("y", c3_d_u_data, 10, 0U, 1U,
              0U, 2, 1, 40));
            sf_mex_call("error", 0U, 2U, 14, c3_g_y, 14, c3_h_y);
          } else {
            c3_val = c3_USRP2UnpackFieldVal(chartInstance, c3_replyCmd[(int32_T)
              USRP2CmdFields_Ok - 1].dtype, c3_replyCmd[3].bytes);
          }

          c3_ok = (c3_val != 0.0);
          break;
        }

        if (c3_guard4 == TRUE) {
          c3_val = 0.0;
          if (c3_replyCmd[4].fsize == 0.0) {
            for (c3_i12 = 0; c3_i12 < 23; c3_i12++) {
              c3_c_u[c3_i12] = c3_varargin_1[c3_i12];
            }

            c3_e_y = NULL;
            sf_mex_assign(&c3_e_y, sf_mex_create("y", c3_c_u, 10, 0U, 1U, 0U, 2,
              1, 23));
            c3_cv10[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_ConfigOk;
            for (c3_i12 = 0; c3_i12 < 39; c3_i12++) {
              c3_cv10[c3_i12 + 1] = c3_cv11[c3_i12];
            }

            for (c3_i12 = 0; c3_i12 < 40; c3_i12++) {
              c3_c_u_data[c3_i12] = c3_cv10[c3_i12];
            }

            c3_f_y = NULL;
            sf_mex_assign(&c3_f_y, sf_mex_create("y", c3_c_u_data, 10, 0U, 1U,
              0U, 2, 1, 40));
            sf_mex_call("error", 0U, 2U, 14, c3_e_y, 14, c3_f_y);
          } else {
            c3_val = c3_USRP2UnpackFieldVal(chartInstance, c3_replyCmd[(int32_T)
              USRP2CmdFields_ConfigOk - 1].dtype, c3_replyCmd[4].bytes);
          }

          c3_ok = (c3_val != 0.0);
        }

        if (c3_guard3 == TRUE) {
          c3_ok = TRUE;
        }

        if (!c3_ok) {
          c3_guard1 = FALSE;
          c3_guard2 = FALSE;
          switch ((int32_T)c3_parsedBytes) {
           case 132:
            c3_guard1 = TRUE;
            break;

           case 133:
            c3_guard1 = TRUE;
            break;

           case 134:
            c3_errStr_sizes[0] = 1;
            c3_errStr_sizes[1] = 41;
            for (c3_i12 = 0; c3_i12 < 41; c3_i12++) {
              c3_errStr_data[c3_i12] = c3_cv12[c3_i12];
            }
            break;

           case 135:
            c3_errStr_sizes[0] = 1;
            c3_errStr_sizes[1] = 40;
            for (c3_i12 = 0; c3_i12 < 40; c3_i12++) {
              c3_errStr_data[c3_i12] = c3_cv13[c3_i12];
            }
            break;

           case 14:
            c3_guard2 = TRUE;
            break;

           case 13:
            c3_guard2 = TRUE;
            break;

           case 143:
            c3_errStr_sizes[0] = 1;
            c3_errStr_sizes[1] = 45;
            for (c3_i12 = 0; c3_i12 < 45; c3_i12++) {
              c3_errStr_data[c3_i12] = c3_cv14[c3_i12];
            }
            break;
          }

          if (c3_guard2 == TRUE) {
            c3_errStr_sizes[0] = 1;
            c3_errStr_sizes[1] = 56;
            for (c3_i12 = 0; c3_i12 < 56; c3_i12++) {
              c3_errStr_data[c3_i12] = c3_cv15[c3_i12];
            }
          }

          if (c3_guard1 == TRUE) {
            c3_errStr_sizes[0] = 1;
            c3_errStr_sizes[1] = 39;
            for (c3_i12 = 0; c3_i12 < 39; c3_i12++) {
              c3_errStr_data[c3_i12] = c3_cv16[c3_i12];
            }
          }
        }
      }
    }
  }
}

static real_T c3_USRP2UnpackFieldVal(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_USRP2FieldDtypes c3_dtype, uint8_T c3_bytes[16])
{
  real_T c3_val;
  int32_T c3_j;
  uint8_T c3_x[2];
  uint16_T c3_u16;
  uint8_T c3_b_x[4];
  uint32_T c3_u32;
  real_T c3_y;
  const mxArray *c3_b_y = NULL;
  char_T c3_u[32];
  const mxArray *c3_c_y = NULL;
  char_T c3_b_u[37];
  static char_T c3_varargin_1[32] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'U', 'n', 'k', 'n', 'o', 'w', 'n', 'F',
    'i', 'e', 'l', 'd', 'D', 't', 'y', 'p', 'e' };

  static char_T c3_varargin_2[37] = { 'U', 'n', 'k', 'n', 'o', 'w', 'n', ' ',
    'U', 'S', 'R', 'P', '2', ' ', 'd', 'a', 't', 'a', 't', 'y', 'p', 'e', ' ',
    's', 'p', 'e', 'c', 'i', 'f', 'i', 'c', 'a', 't', 'i', 'o', 'n', '.' };

  switch (c3_dtype) {
   case USRP2FieldDtypes_usrp2_uint8_T:
    c3_val = (real_T)c3_bytes[0];
    break;

   case USRP2FieldDtypes_usrp2_uint16_T:
    for (c3_j = 0; c3_j < 2; c3_j++) {
      c3_x[c3_j] = c3_bytes[1 - c3_j];
    }

    memcpy((void *)&c3_u16, (void *)&c3_x[0], 2U);
    c3_val = (real_T)c3_u16;
    break;

   case USRP2FieldDtypes_usrp2_uint32_T:
    for (c3_j = 0; c3_j < 4; c3_j++) {
      c3_b_x[c3_j] = c3_bytes[3 - c3_j];
    }

    memcpy((void *)&c3_u32, (void *)&c3_b_x[0], 4U);
    c3_val = (real_T)c3_u32;
    break;

   case USRP2FieldDtypes_usrp2_sfix16_En7_T:
    c3_y = 0.0;
    for (c3_j = 1; c3_j > -1; c3_j += -1) {
      c3_y = c3_y * 256.0 + (real_T)c3_bytes[1 - c3_j];
    }

    c3_val = c3_y / 128.0;
    break;

   case USRP2FieldDtypes_usrp2_sfix64_En20_T:
    c3_y = 0.0;
    for (c3_j = 7; c3_j > -1; c3_j += -1) {
      c3_y = c3_y * 256.0 + (real_T)c3_bytes[7 - c3_j];
    }

    c3_val = c3_y / 1.048576E+6;
    break;

   default:
    c3_val = 1.0;
    for (c3_j = 0; c3_j < 32; c3_j++) {
      c3_u[c3_j] = c3_varargin_1[c3_j];
    }

    c3_b_y = NULL;
    sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 32));
    for (c3_j = 0; c3_j < 37; c3_j++) {
      c3_b_u[c3_j] = c3_varargin_2[c3_j];
    }

    c3_c_y = NULL;
    sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 37));
    sf_mex_call("error", 0U, 2U, 14, c3_b_y, 14, c3_c_y);
    break;
  }

  return c3_val;
}

static void c3_d_USRP2RuntimeControl(SFc3_commsdrhwInstanceStruct *chartInstance,
  real_T *c3_pktLength, uint8_T c3_pkt[255])
{
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_cmdDef[18];
  int32_T c3_i14;
  static char_T c3_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c3_u[23];
  const mxArray *c3_y = NULL;
  char_T c3_b_u[40];
  static char_T c3_cv17[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  const mxArray *c3_b_y = NULL;
  char_T c3_c_u[23];
  const mxArray *c3_c_y = NULL;
  char_T c3_d_u[40];
  const mxArray *c3_d_y = NULL;
  char_T c3_e_u[23];
  const mxArray *c3_e_y = NULL;
  char_T c3_f_u[40];
  const mxArray *c3_f_y = NULL;
  c3_USRP2CmdDef(chartInstance, USRP2Opcodes_StartRxStreaming, c3_cmdDef);
  if (c3_cmdDef[(int32_T)USRP2CmdFields_ItemsPerFrame - 1].fsize == 0.0) {
    for (c3_i14 = 0; c3_i14 < 23; c3_i14++) {
      c3_u[c3_i14] = c3_varargin_1[c3_i14];
    }

    c3_y = NULL;
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c3_b_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_ItemsPerFrame;
    for (c3_i14 = 0; c3_i14 < 39; c3_i14++) {
      c3_b_u[c3_i14 + 1] = c3_cv17[c3_i14];
    }

    c3_b_y = NULL;
    sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c3_y, 14, c3_b_y);
  } else {
    c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)
                         USRP2CmdFields_ItemsPerFrame - 1].dtype,
                         c3_b_frameLength, c3_cmdDef[(int32_T)
                         USRP2CmdFields_ItemsPerFrame - 1].bytes);
  }

  if (c3_cmdDef[(int32_T)USRP2CmdFields_TimeInt - 1].fsize == 0.0) {
    for (c3_i14 = 0; c3_i14 < 23; c3_i14++) {
      c3_c_u[c3_i14] = c3_varargin_1[c3_i14];
    }

    c3_c_y = NULL;
    sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_c_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c3_d_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_TimeInt;
    for (c3_i14 = 0; c3_i14 < 39; c3_i14++) {
      c3_d_u[c3_i14 + 1] = c3_cv17[c3_i14];
    }

    c3_d_y = NULL;
    sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_d_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c3_c_y, 14, c3_d_y);
  } else {
    c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)
                         USRP2CmdFields_TimeInt - 1].dtype, 4.294967295E+9,
                         c3_cmdDef[(int32_T)USRP2CmdFields_TimeInt - 1].bytes);
  }

  if (c3_cmdDef[(int32_T)USRP2CmdFields_TimeFrac - 1].fsize == 0.0) {
    for (c3_i14 = 0; c3_i14 < 23; c3_i14++) {
      c3_e_u[c3_i14] = c3_varargin_1[c3_i14];
    }

    c3_e_y = NULL;
    sf_mex_assign(&c3_e_y, sf_mex_create("y", c3_e_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c3_f_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_TimeFrac;
    for (c3_i14 = 0; c3_i14 < 39; c3_i14++) {
      c3_f_u[c3_i14 + 1] = c3_cv17[c3_i14];
    }

    c3_f_y = NULL;
    sf_mex_assign(&c3_f_y, sf_mex_create("y", c3_f_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c3_e_y, 14, c3_f_y);
  } else {
    c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)
                         USRP2CmdFields_TimeFrac - 1].dtype, 4.294967295E+9,
                         c3_cmdDef[(int32_T)USRP2CmdFields_TimeFrac - 1].bytes);
  }

  c3_USRP2Cmd2Pkt(chartInstance, c3_cmdDef, c3_pkt, c3_pktLength);
}

static void c3_e_USRP2RuntimeControl(SFc3_commsdrhwInstanceStruct *chartInstance,
  real_T c3_varargin_3, real_T *c3_pktLength, uint8_T c3_pkt[255], uint8_T
  *c3_b_replyId, real_T *c3_varargout_1_ValidMask, real_T *c3_varargout_1_Fc,
  real_T *c3_varargout_1_Gain, real_T *c3_varargout_1_DecimInterp, real_T
  *c3_varargout_1_ScaleI, real_T *c3_varargout_1_ScaleQ)
{
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_cmdDef[18];
  int32_T c3_i15;
  static char_T c3_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c3_u[23];
  const mxArray *c3_y = NULL;
  char_T c3_b_u[40];
  static char_T c3_cv18[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  const mxArray *c3_b_y = NULL;
  char_T c3_c_u[23];
  const mxArray *c3_c_y = NULL;
  char_T c3_d_u[40];
  const mxArray *c3_d_y = NULL;
  chartInstance->c3_lastCF_not_empty = TRUE;
  chartInstance->c3_lastG_not_empty = TRUE;
  chartInstance->c3_lastDI_not_empty = TRUE;
  chartInstance->c3_lastI_not_empty = TRUE;
  chartInstance->c3_lastQ_not_empty = TRUE;
  c3_USRP2CmdDef(chartInstance, USRP2Opcodes_ConfigRx, c3_cmdDef);
  *c3_varargout_1_ValidMask = 0.0;
  *c3_varargout_1_Gain = chartInstance->c3_lastG;
  *c3_varargout_1_DecimInterp = chartInstance->c3_lastDI;
  *c3_varargout_1_ScaleI = chartInstance->c3_lastI;
  *c3_varargout_1_ScaleQ = chartInstance->c3_lastQ;
  *c3_varargout_1_Fc = c3_varargin_3;
  if (c3_varargin_3 != chartInstance->c3_lastCF) {
    *c3_varargout_1_ValidMask = 2.0;
    if (c3_cmdDef[(int32_T)USRP2CmdFields_CenterFreq - 1].fsize == 0.0) {
      for (c3_i15 = 0; c3_i15 < 23; c3_i15++) {
        c3_u[c3_i15] = c3_varargin_1[c3_i15];
      }

      c3_y = NULL;
      sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 23));
      c3_b_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_CenterFreq;
      for (c3_i15 = 0; c3_i15 < 39; c3_i15++) {
        c3_b_u[c3_i15 + 1] = c3_cv18[c3_i15];
      }

      c3_b_y = NULL;
      sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
      sf_mex_call("error", 0U, 2U, 14, c3_y, 14, c3_b_y);
    } else {
      c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)
                           USRP2CmdFields_CenterFreq - 1].dtype, c3_varargin_3,
                           c3_cmdDef[(int32_T)USRP2CmdFields_CenterFreq - 1].
                           bytes);
    }
  }

  if (*c3_varargout_1_ValidMask != 0.0) {
    if (c3_cmdDef[(int32_T)USRP2CmdFields_Valid - 1].fsize == 0.0) {
      for (c3_i15 = 0; c3_i15 < 23; c3_i15++) {
        c3_c_u[c3_i15] = c3_varargin_1[c3_i15];
      }

      c3_c_y = NULL;
      sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_c_u, 10, 0U, 1U, 0U, 2, 1, 23));
      c3_d_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Valid;
      for (c3_i15 = 0; c3_i15 < 39; c3_i15++) {
        c3_d_u[c3_i15 + 1] = c3_cv18[c3_i15];
      }

      c3_d_y = NULL;
      sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_d_u, 10, 0U, 1U, 0U, 2, 1, 40));
      sf_mex_call("error", 0U, 2U, 14, c3_c_y, 14, c3_d_y);
    } else {
      c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)
                           USRP2CmdFields_Valid - 1].dtype,
                           *c3_varargout_1_ValidMask, c3_cmdDef[(int32_T)
                           USRP2CmdFields_Valid - 1].bytes);
    }

    c3_USRP2Cmd2Pkt(chartInstance, c3_cmdDef, c3_pkt, c3_pktLength);
  } else {
    *c3_pktLength = 0.0;
    for (c3_i15 = 0; c3_i15 < 255; c3_i15++) {
      c3_pkt[c3_i15] = 0U;
    }
  }

  chartInstance->c3_lastCF = c3_varargin_3;
  chartInstance->c3_lastG = *c3_varargout_1_Gain;
  chartInstance->c3_lastDI = *c3_varargout_1_DecimInterp;
  chartInstance->c3_lastI = *c3_varargout_1_ScaleI;
  chartInstance->c3_lastQ = *c3_varargout_1_ScaleQ;
  *c3_b_replyId = c3_pkt[2];
}

static void c3_f_USRP2RuntimeControl(SFc3_commsdrhwInstanceStruct *chartInstance,
  real_T c3_varargin_3, real_T *c3_pktLength, uint8_T c3_pkt[255], uint8_T
  *c3_b_replyId, real_T *c3_varargout_1_ValidMask, real_T *c3_varargout_1_Fc,
  real_T *c3_varargout_1_Gain, real_T *c3_varargout_1_DecimInterp, real_T
  *c3_varargout_1_ScaleI, real_T *c3_varargout_1_ScaleQ)
{
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_cmdDef[18];
  int32_T c3_i16;
  static char_T c3_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c3_u[23];
  const mxArray *c3_y = NULL;
  char_T c3_b_u[40];
  static char_T c3_cv19[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  const mxArray *c3_b_y = NULL;
  char_T c3_c_u[23];
  const mxArray *c3_c_y = NULL;
  char_T c3_d_u[40];
  const mxArray *c3_d_y = NULL;
  chartInstance->c3_lastCF_not_empty = TRUE;
  chartInstance->c3_lastG_not_empty = TRUE;
  chartInstance->c3_lastDI_not_empty = TRUE;
  chartInstance->c3_lastI_not_empty = TRUE;
  chartInstance->c3_lastQ_not_empty = TRUE;
  c3_USRP2CmdDef(chartInstance, USRP2Opcodes_ConfigRx, c3_cmdDef);
  *c3_varargout_1_ValidMask = 0.0;
  *c3_varargout_1_Fc = chartInstance->c3_lastCF;
  *c3_varargout_1_DecimInterp = chartInstance->c3_lastDI;
  *c3_varargout_1_ScaleI = chartInstance->c3_lastI;
  *c3_varargout_1_ScaleQ = chartInstance->c3_lastQ;
  *c3_varargout_1_Gain = c3_varargin_3;
  if (c3_varargin_3 != chartInstance->c3_lastG) {
    *c3_varargout_1_ValidMask = 1.0;
    if (c3_cmdDef[(int32_T)USRP2CmdFields_Gain - 1].fsize == 0.0) {
      for (c3_i16 = 0; c3_i16 < 23; c3_i16++) {
        c3_u[c3_i16] = c3_varargin_1[c3_i16];
      }

      c3_y = NULL;
      sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 23));
      c3_b_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Gain;
      for (c3_i16 = 0; c3_i16 < 39; c3_i16++) {
        c3_b_u[c3_i16 + 1] = c3_cv19[c3_i16];
      }

      c3_b_y = NULL;
      sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
      sf_mex_call("error", 0U, 2U, 14, c3_y, 14, c3_b_y);
    } else {
      c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)USRP2CmdFields_Gain
                           - 1].dtype, c3_varargin_3, c3_cmdDef[(int32_T)
                           USRP2CmdFields_Gain - 1].bytes);
    }
  }

  if (*c3_varargout_1_ValidMask != 0.0) {
    if (c3_cmdDef[(int32_T)USRP2CmdFields_Valid - 1].fsize == 0.0) {
      for (c3_i16 = 0; c3_i16 < 23; c3_i16++) {
        c3_c_u[c3_i16] = c3_varargin_1[c3_i16];
      }

      c3_c_y = NULL;
      sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_c_u, 10, 0U, 1U, 0U, 2, 1, 23));
      c3_d_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Valid;
      for (c3_i16 = 0; c3_i16 < 39; c3_i16++) {
        c3_d_u[c3_i16 + 1] = c3_cv19[c3_i16];
      }

      c3_d_y = NULL;
      sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_d_u, 10, 0U, 1U, 0U, 2, 1, 40));
      sf_mex_call("error", 0U, 2U, 14, c3_c_y, 14, c3_d_y);
    } else {
      c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)
                           USRP2CmdFields_Valid - 1].dtype, 1.0, c3_cmdDef
                           [(int32_T)USRP2CmdFields_Valid - 1].bytes);
    }

    c3_USRP2Cmd2Pkt(chartInstance, c3_cmdDef, c3_pkt, c3_pktLength);
  } else {
    *c3_pktLength = 0.0;
    for (c3_i16 = 0; c3_i16 < 255; c3_i16++) {
      c3_pkt[c3_i16] = 0U;
    }
  }

  chartInstance->c3_lastCF = *c3_varargout_1_Fc;
  chartInstance->c3_lastG = c3_varargin_3;
  chartInstance->c3_lastDI = *c3_varargout_1_DecimInterp;
  chartInstance->c3_lastI = *c3_varargout_1_ScaleI;
  chartInstance->c3_lastQ = *c3_varargout_1_ScaleQ;
  *c3_b_replyId = c3_pkt[2];
}

static void c3_g_USRP2RuntimeControl(SFc3_commsdrhwInstanceStruct *chartInstance,
  real_T c3_varargin_3, real_T *c3_pktLength, uint8_T c3_pkt[255], uint8_T
  *c3_b_replyId, real_T *c3_varargout_1_ValidMask, real_T *c3_varargout_1_Fc,
  real_T *c3_varargout_1_Gain, real_T *c3_varargout_1_DecimInterp, real_T
  *c3_varargout_1_ScaleI, real_T *c3_varargout_1_ScaleQ)
{
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_cmdDef[18];
  int32_T c3_i17;
  static char_T c3_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c3_u[23];
  const mxArray *c3_y = NULL;
  char_T c3_b_u[40];
  static char_T c3_cv20[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  const mxArray *c3_b_y = NULL;
  char_T c3_c_u[23];
  const mxArray *c3_c_y = NULL;
  char_T c3_d_u[40];
  const mxArray *c3_d_y = NULL;
  chartInstance->c3_lastCF_not_empty = TRUE;
  chartInstance->c3_lastG_not_empty = TRUE;
  chartInstance->c3_lastDI_not_empty = TRUE;
  chartInstance->c3_lastI_not_empty = TRUE;
  chartInstance->c3_lastQ_not_empty = TRUE;
  c3_USRP2CmdDef(chartInstance, USRP2Opcodes_ConfigRx, c3_cmdDef);
  *c3_varargout_1_ValidMask = 0.0;
  *c3_varargout_1_Fc = chartInstance->c3_lastCF;
  *c3_varargout_1_Gain = chartInstance->c3_lastG;
  *c3_varargout_1_ScaleI = chartInstance->c3_lastI;
  *c3_varargout_1_ScaleQ = chartInstance->c3_lastQ;
  *c3_varargout_1_DecimInterp = c3_varargin_3;
  if (c3_varargin_3 != chartInstance->c3_lastDI) {
    *c3_varargout_1_ValidMask = 4.0;
    if (c3_cmdDef[(int32_T)USRP2CmdFields_Decimation - 1].fsize == 0.0) {
      for (c3_i17 = 0; c3_i17 < 23; c3_i17++) {
        c3_u[c3_i17] = c3_varargin_1[c3_i17];
      }

      c3_y = NULL;
      sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 23));
      c3_b_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Decimation;
      for (c3_i17 = 0; c3_i17 < 39; c3_i17++) {
        c3_b_u[c3_i17 + 1] = c3_cv20[c3_i17];
      }

      c3_b_y = NULL;
      sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
      sf_mex_call("error", 0U, 2U, 14, c3_y, 14, c3_b_y);
    } else {
      c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)
                           USRP2CmdFields_Decimation - 1].dtype, c3_varargin_3,
                           c3_cmdDef[(int32_T)USRP2CmdFields_Decimation - 1].
                           bytes);
    }
  }

  if (*c3_varargout_1_ValidMask != 0.0) {
    if (c3_cmdDef[(int32_T)USRP2CmdFields_Valid - 1].fsize == 0.0) {
      for (c3_i17 = 0; c3_i17 < 23; c3_i17++) {
        c3_c_u[c3_i17] = c3_varargin_1[c3_i17];
      }

      c3_c_y = NULL;
      sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_c_u, 10, 0U, 1U, 0U, 2, 1, 23));
      c3_d_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Valid;
      for (c3_i17 = 0; c3_i17 < 39; c3_i17++) {
        c3_d_u[c3_i17 + 1] = c3_cv20[c3_i17];
      }

      c3_d_y = NULL;
      sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_d_u, 10, 0U, 1U, 0U, 2, 1, 40));
      sf_mex_call("error", 0U, 2U, 14, c3_c_y, 14, c3_d_y);
    } else {
      c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)
                           USRP2CmdFields_Valid - 1].dtype,
                           *c3_varargout_1_ValidMask, c3_cmdDef[(int32_T)
                           USRP2CmdFields_Valid - 1].bytes);
    }

    c3_USRP2Cmd2Pkt(chartInstance, c3_cmdDef, c3_pkt, c3_pktLength);
  } else {
    *c3_pktLength = 0.0;
    for (c3_i17 = 0; c3_i17 < 255; c3_i17++) {
      c3_pkt[c3_i17] = 0U;
    }
  }

  chartInstance->c3_lastCF = *c3_varargout_1_Fc;
  chartInstance->c3_lastG = *c3_varargout_1_Gain;
  chartInstance->c3_lastDI = c3_varargin_3;
  chartInstance->c3_lastI = *c3_varargout_1_ScaleI;
  chartInstance->c3_lastQ = *c3_varargout_1_ScaleQ;
  *c3_b_replyId = c3_pkt[2];
}

static real_T c3_length(SFc3_commsdrhwInstanceStruct *chartInstance, uint8_T
  c3_x_data[1464], int32_T c3_x_sizes[1])
{
  real_T c3_n;
  if (c3_x_sizes[0] == 0) {
    c3_n = 0.0;
  } else if (c3_x_sizes[0] > 1) {
    c3_n = (real_T)c3_x_sizes[0];
  } else {
    c3_n = 1.0;
  }

  return c3_n;
}

static void c3_VRTGetDataStream(SFc3_commsdrhwInstanceStruct *chartInstance,
  char_T c3_S_datatype[5], char_T c3_value[5])
{
  int32_T c3_i18;
  for (c3_i18 = 0; c3_i18 < 5; c3_i18++) {
    c3_value[c3_i18] = c3_S_datatype[c3_i18];
  }
}

static boolean_T c3_eml_strcmp(SFc3_commsdrhwInstanceStruct *chartInstance,
  char_T c3_b[5])
{
  boolean_T c3_bool;
  int32_T c3_k;
  int32_T c3_exitg1;
  static char_T c3_cv21[5] = { 'i', 'n', 't', '1', '6' };

  c3_bool = FALSE;
  c3_k = 0;
  do {
    c3_exitg1 = 0U;
    if (c3_k + 1 <= 5) {
      if (c3_cv21[c3_k] != c3_b[c3_k]) {
        c3_exitg1 = 1U;
      } else {
        c3_k++;
      }
    } else {
      c3_bool = TRUE;
      c3_exitg1 = 1U;
    }
  } while (c3_exitg1 == 0U);

  return c3_bool;
}

static void c3_typecast(SFc3_commsdrhwInstanceStruct *chartInstance, uint8_T
  c3_x_data[732], int32_T c3_x_sizes[1], int16_T c3_y_data[133956], int32_T
  c3_y_sizes[2])
{
  real_T c3_outlen;
  int32_T c3_i19;
  static char_T c3_cv22[45] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T', 'L',
    'A', 'B', ':', 't', 'y', 'p', 'e', 'c', 'a', 's', 't', 'c', '_', 'n', 'o',
    't', 'E', 'n', 'o', 'u', 'g', 'h', 'I', 'n', 'p', 'u', 't', 'E', 'l', 'e',
    'm', 'e', 'n', 't', 's' };

  char_T c3_u[45];
  const mxArray *c3_y = NULL;
  real_T c3_outsize_idx_0;
  c3_outlen = (real_T)c3_x_sizes[0] / 2.0;
  if (!(muDoubleScalarFloor(c3_outlen) == c3_outlen)) {
    for (c3_i19 = 0; c3_i19 < 45; c3_i19++) {
      c3_u[c3_i19] = c3_cv22[c3_i19];
    }

    c3_y = NULL;
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 45));
    sf_mex_call("error", 0U, 1U, 14, sf_mex_call("message", 1U, 1U, 14, c3_y));
  }

  if (c3_x_sizes[0] > 1) {
    c3_outsize_idx_0 = c3_outlen;
    c3_outlen = 1.0;
  } else {
    c3_outsize_idx_0 = 1.0;
  }

  c3_y_sizes[0] = (int32_T)c3_outsize_idx_0;
  c3_y_sizes[1] = (int32_T)c3_outlen;
  memcpy((void *)&c3_y_data[0], (void *)&c3_x_data[0], (uint32_T)c3_x_sizes[0]);
}

static void c3_Update(SFc3_commsdrhwInstanceStruct *chartInstance, uint8_T
                      c3_U0[255], real_T c3_U1)
{
  char_T *c3_sErr;

  /* System object Update function: dsp.UDPSender */
  c3_sErr = GetErrorBuffer(&chartInstance->c3_c_NetworkLib[0U]);
  LibUpdate_Network(&chartInstance->c3_c_NetworkLib[0U], &c3_U0[0], (int32_T)
                    c3_U1);
  if (*c3_sErr != 0) {
    PrintError(c3_sErr);
  }
}

static void c3_b_Update(SFc3_commsdrhwInstanceStruct *chartInstance, uint8_T
  c3_U0[4], real_T c3_U1)
{
  char_T *c3_sErr;

  /* System object Update function: dsp.UDPSender */
  c3_sErr = GetErrorBuffer(&chartInstance->c3_d_NetworkLib[0U]);
  LibUpdate_Network(&chartInstance->c3_d_NetworkLib[0U], &c3_U0[0], (int32_T)
                    c3_U1);
  if (*c3_sErr != 0) {
    PrintError(c3_sErr);
  }
}

static void c3_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_data, const char_T *c3_identifier, creal32_T c3_y[358])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_data), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_data);
}

static void c3_b_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, creal32_T c3_y[358])
{
  creal32_T c3_fcv1[358];
  int32_T c3_i20;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_fcv1, 1, 1, 1U, 1, 0U, 2, 358,
                1);
  for (c3_i20 = 0; c3_i20 < 358; c3_i20++) {
    c3_y[c3_i20] = c3_fcv1[c3_i20];
  }

  sf_mex_destroy(&c3_u);
}

static real_T c3_c_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_dataLength, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_dataLength),
    &c3_thisId);
  sf_mex_destroy(&c3_b_dataLength);
  return c3_y;
}

static real_T c3_d_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d7;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d7, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d7;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static uint8_T c3_e_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_overrun, const char_T *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_overrun), &c3_thisId);
  sf_mex_destroy(&c3_overrun);
  return c3_y;
}

static uint8_T c3_f_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u11;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u11, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u11;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_g_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_e_NetworkLib, const char_T *c3_identifier, real_T c3_y[137])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_e_NetworkLib), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_e_NetworkLib);
}

static void c3_h_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[137])
{
  real_T c3_dv2[137];
  int32_T c3_i21;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv2, 1, 0, 0U, 1, 0U, 1, 137);
  for (c3_i21 = 0; c3_i21 < 137; c3_i21++) {
    c3_y[c3_i21] = c3_dv2[c3_i21];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_i_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_e_NetworkLib, const char_T *c3_identifier, real_T c3_y[137])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_e_NetworkLib), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_e_NetworkLib);
}

static void c3_j_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[137])
{
  real_T c3_dv3[137];
  int32_T c3_i22;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv3, 1, 0, 0U, 1, 0U, 1, 137);
  for (c3_i22 = 0; c3_i22 < 137; c3_i22++) {
    c3_y[c3_i22] = c3_dv3[c3_i22];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_k_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_e_NetworkLib, const char_T *c3_identifier, real_T c3_y[137])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_e_NetworkLib), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_e_NetworkLib);
}

static void c3_l_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[137])
{
  real_T c3_dv4[137];
  int32_T c3_i23;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv4, 1, 0, 0U, 1, 0U, 1, 137);
  for (c3_i23 = 0; c3_i23 < 137; c3_i23++) {
    c3_y[c3_i23] = c3_dv4[c3_i23];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_m_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_e_NetworkLib, const char_T *c3_identifier, real_T c3_y[137])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_e_NetworkLib), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_e_NetworkLib);
}

static void c3_n_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[137])
{
  real_T c3_dv5[137];
  int32_T c3_i24;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv5, 1, 0, 0U, 1, 0U, 1, 137);
  for (c3_i24 = 0; c3_i24 < 137; c3_i24++) {
    c3_y[c3_i24] = c3_dv5[c3_i24];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_o_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_Recv, const char_T *c3_identifier, char_T c3_y_datatype[5],
  uint8_T *c3_y_hasTrailer, uint32_T *c3_y_trailer, uint8_T
  *c3_y_stream_hasStreamID, uint32_T *c3_y_stream_streamID, uint8_T
  *c3_y_stream_hasClassID, uint32_T c3_y_stream_classID[2], uint8_T
  *c3_y_stream_packetType, uint8_T *c3_y_stream_TSI, uint8_T *c3_y_stream_TSF,
  uint8_T *c3_y_stream_packetCount, uint16_T *c3_y_stream_packetSize)
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_Recv), &c3_thisId,
                        c3_y_datatype, c3_y_hasTrailer, c3_y_trailer,
                        c3_y_stream_hasStreamID, c3_y_stream_streamID,
                        c3_y_stream_hasClassID, c3_y_stream_classID,
                        c3_y_stream_packetType, c3_y_stream_TSI, c3_y_stream_TSF,
                        c3_y_stream_packetCount, c3_y_stream_packetSize);
  sf_mex_destroy(&c3_b_Recv);
}

static void c3_p_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, char_T
  c3_y_datatype[5], uint8_T *c3_y_hasTrailer, uint32_T *c3_y_trailer, uint8_T
  *c3_y_stream_hasStreamID, uint32_T *c3_y_stream_streamID, uint8_T
  *c3_y_stream_hasClassID, uint32_T c3_y_stream_classID[2], uint8_T
  *c3_y_stream_packetType, uint8_T *c3_y_stream_TSI, uint8_T *c3_y_stream_TSF,
  uint8_T *c3_y_stream_packetCount, uint16_T *c3_y_stream_packetSize)
{
  emlrtMsgIdentifier c3_thisId;
  static const char * c3_fieldNames[4] = { "datatype", "hasTrailer", "trailer",
    "stream" };

  c3_thisId.fParent = c3_parentId;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_Recv_not_empty = FALSE;
  } else {
    chartInstance->c3_Recv_not_empty = TRUE;
    sf_mex_check_struct(c3_parentId, c3_u, 4, c3_fieldNames, 0U, 0);
    c3_thisId.fIdentifier = "datatype";
    c3_q_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c3_u,
      "datatype", "datatype", 0)), &c3_thisId, c3_y_datatype);
    c3_thisId.fIdentifier = "hasTrailer";
    *c3_y_hasTrailer = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup
      (sf_mex_getfield(c3_u, "hasTrailer", "hasTrailer", 0)), &c3_thisId);
    c3_thisId.fIdentifier = "trailer";
    *c3_y_trailer = c3_r_emlrt_marshallIn(chartInstance, sf_mex_dup
      (sf_mex_getfield(c3_u, "trailer", "trailer", 0)), &c3_thisId);
    c3_thisId.fIdentifier = "stream";
    c3_s_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c3_u,
      "stream", "stream", 0)), &c3_thisId, c3_y_stream_hasStreamID,
                          c3_y_stream_streamID, c3_y_stream_hasClassID,
                          c3_y_stream_classID, c3_y_stream_packetType,
                          c3_y_stream_TSI, c3_y_stream_TSF,
                          c3_y_stream_packetCount, c3_y_stream_packetSize);
  }

  sf_mex_destroy(&c3_u);
}

static void c3_q_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, char_T c3_y[5])
{
  char_T c3_cv23[5];
  int32_T c3_i25;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_cv23, 1, 10, 0U, 1, 0U, 2, 1,
                5);
  for (c3_i25 = 0; c3_i25 < 5; c3_i25++) {
    c3_y[c3_i25] = c3_cv23[c3_i25];
  }

  sf_mex_destroy(&c3_u);
}

static uint32_T c3_r_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint32_T c3_y;
  uint32_T c3_u12;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u12, 1, 7, 0U, 0, 0U, 0);
  c3_y = c3_u12;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_s_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T
  *c3_y_hasStreamID, uint32_T *c3_y_streamID, uint8_T *c3_y_hasClassID, uint32_T
  c3_y_classID[2], uint8_T *c3_y_packetType, uint8_T *c3_y_TSI, uint8_T
  *c3_y_TSF, uint8_T *c3_y_packetCount, uint16_T *c3_y_packetSize)
{
  emlrtMsgIdentifier c3_thisId;
  static const char * c3_fieldNames[9] = { "hasStreamID", "streamID",
    "hasClassID", "classID", "packetType", "TSI", "TSF", "packetCount",
    "packetSize" };

  c3_thisId.fParent = c3_parentId;
  sf_mex_check_struct(c3_parentId, c3_u, 9, c3_fieldNames, 0U, 0);
  c3_thisId.fIdentifier = "hasStreamID";
  *c3_y_hasStreamID = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c3_u, "hasStreamID", "hasStreamID", 0)), &c3_thisId);
  c3_thisId.fIdentifier = "streamID";
  *c3_y_streamID = c3_r_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c3_u, "streamID", "streamID", 0)), &c3_thisId);
  c3_thisId.fIdentifier = "hasClassID";
  *c3_y_hasClassID = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c3_u, "hasClassID", "hasClassID", 0)), &c3_thisId);
  c3_thisId.fIdentifier = "classID";
  c3_t_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c3_u,
    "classID", "classID", 0)), &c3_thisId, c3_y_classID);
  c3_thisId.fIdentifier = "packetType";
  *c3_y_packetType = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c3_u, "packetType", "packetType", 0)), &c3_thisId);
  c3_thisId.fIdentifier = "TSI";
  *c3_y_TSI = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c3_u, "TSI", "TSI", 0)), &c3_thisId);
  c3_thisId.fIdentifier = "TSF";
  *c3_y_TSF = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c3_u, "TSF", "TSF", 0)), &c3_thisId);
  c3_thisId.fIdentifier = "packetCount";
  *c3_y_packetCount = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c3_u, "packetCount", "packetCount", 0)), &c3_thisId);
  c3_thisId.fIdentifier = "packetSize";
  *c3_y_packetSize = c3_u_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c3_u, "packetSize", "packetSize", 0)), &c3_thisId);
  sf_mex_destroy(&c3_u);
}

static void c3_t_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint32_T c3_y[2])
{
  uint32_T c3_uv4[2];
  int32_T c3_i26;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_uv4, 1, 7, 0U, 1, 0U, 2, 1, 2);
  for (c3_i26 = 0; c3_i26 < 2; c3_i26++) {
    c3_y[c3_i26] = c3_uv4[c3_i26];
  }

  sf_mex_destroy(&c3_u);
}

static uint16_T c3_u_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint16_T c3_y;
  uint16_T c3_u13;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u13, 1, 5, 0U, 0, 0U, 0);
  c3_y = c3_u13;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_v_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_c_Y0, const char_T *c3_identifier, uint8_T c3_y[255])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_w_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Y0), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Y0);
}

static void c3_w_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_y[255])
{
  uint8_T c3_uv5[255];
  int32_T c3_i27;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_uv5, 1, 3, 0U, 1, 0U, 2, 255,
                1);
  for (c3_i27 = 0; c3_i27 < 255; c3_i27++) {
    c3_y[c3_i27] = c3_uv5[c3_i27];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_x_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_c_Y0, const char_T *c3_identifier, uint8_T c3_y[255])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Y0), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Y0);
}

static void c3_y_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_y[255])
{
  uint8_T c3_uv6[255];
  int32_T c3_i28;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_uv6, 1, 3, 0U, 1, 0U, 2, 255,
                1);
  for (c3_i28 = 0; c3_i28 < 255; c3_i28++) {
    c3_y[c3_i28] = c3_uv6[c3_i28];
  }

  sf_mex_destroy(&c3_u);
}

static uint16_T c3_ab_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c3_c_Y1, const char_T *c3_identifier)
{
  uint16_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_bb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Y1), &c3_thisId);
  sf_mex_destroy(&c3_c_Y1);
  return c3_y;
}

static uint16_T c3_bb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint16_T c3_y;
  uint16_T c3_u14;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u14, 1, 5, 0U, 0, 0U, 0);
  c3_y = c3_u14;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static uint16_T c3_cb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c3_c_Y1, const char_T *c3_identifier)
{
  uint16_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_db_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Y1), &c3_thisId);
  sf_mex_destroy(&c3_c_Y1);
  return c3_y;
}

static uint16_T c3_db_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint16_T c3_y;
  uint16_T c3_u15;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u15, 1, 5, 0U, 0, 0U, 0);
  c3_y = c3_u15;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_eb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_ctrlReceiver, const char_T *c3_identifier)
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_fb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_ctrlReceiver), &c3_thisId);
  sf_mex_destroy(&c3_ctrlReceiver);
}

static void c3_fb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_ctrlReceiver_not_empty = FALSE;
  } else {
    chartInstance->c3_ctrlReceiver_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), NULL, 1, 11, 0U, 1, 0U, 2, 0, 0);
  }

  sf_mex_destroy(&c3_u);
}

static void c3_gb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_ctrlReceiverBlocking, const char_T *c3_identifier)
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_hb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_ctrlReceiverBlocking),
    &c3_thisId);
  sf_mex_destroy(&c3_ctrlReceiverBlocking);
}

static void c3_hb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_ctrlReceiverBlocking_not_empty = FALSE;
  } else {
    chartInstance->c3_ctrlReceiverBlocking_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), NULL, 1, 11, 0U, 1, 0U, 2, 0, 0);
  }

  sf_mex_destroy(&c3_u);
}

static void c3_ib_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_ctrlSender, const char_T *c3_identifier)
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_jb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_ctrlSender), &c3_thisId);
  sf_mex_destroy(&c3_ctrlSender);
}

static void c3_jb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_ctrlSender_not_empty = FALSE;
  } else {
    chartInstance->c3_ctrlSender_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), NULL, 1, 11, 0U, 1, 0U, 2, 0, 0);
  }

  sf_mex_destroy(&c3_u);
}

static real_T c3_kb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_dataLength, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_lb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_dataLength),
    &c3_thisId);
  sf_mex_destroy(&c3_b_dataLength);
  return c3_y;
}

static real_T c3_lb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d8;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_dataLength_not_empty = FALSE;
  } else {
    chartInstance->c3_dataLength_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d8, 1, 0, 0U, 0, 0U, 0);
    c3_y = c3_d8;
  }

  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_mb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_dataSender, const char_T *c3_identifier)
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_nb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_dataSender), &c3_thisId);
  sf_mex_destroy(&c3_dataSender);
}

static void c3_nb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_dataSender_not_empty = FALSE;
  } else {
    chartInstance->c3_dataSender_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), NULL, 1, 11, 0U, 1, 0U, 2, 0, 0);
  }

  sf_mex_destroy(&c3_u);
}

static void c3_ob_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_imagData, const char_T *c3_identifier, uint8_T c3_y_data[732],
  int32_T c3_y_sizes[1])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_pb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_imagData), &c3_thisId,
    c3_y_data, c3_y_sizes);
  sf_mex_destroy(&c3_imagData);
}

static void c3_pb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_y_data
  [732], int32_T c3_y_sizes[1])
{
  uint32_T c3_uv7[1];
  boolean_T c3_bv0[1];
  int32_T c3_tmp_sizes;
  uint8_T c3_tmp_data[732];
  int32_T c3_loop_ub;
  int32_T c3_i29;
  c3_uv7[0] = 732U;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_imagData_not_empty = FALSE;
  } else {
    chartInstance->c3_imagData_not_empty = TRUE;
    c3_bv0[0] = TRUE;
    sf_mex_import_vs(c3_parentId, sf_mex_dup(c3_u), c3_tmp_data, 1, 3, 0U, 1, 0U,
                     1, c3_bv0, c3_uv7, &c3_tmp_sizes);
    c3_y_sizes[0] = c3_tmp_sizes;
    c3_loop_ub = c3_tmp_sizes - 1;
    for (c3_i29 = 0; c3_i29 <= c3_loop_ub; c3_i29++) {
      c3_y_data[c3_i29] = c3_tmp_data[c3_i29];
    }
  }

  sf_mex_destroy(&c3_u);
}

static real_T c3_qb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_lastCF, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_rb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_lastCF),
    &c3_thisId);
  sf_mex_destroy(&c3_b_lastCF);
  return c3_y;
}

static real_T c3_rb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d9;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_lastCF_not_empty = FALSE;
  } else {
    chartInstance->c3_lastCF_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d9, 1, 0, 0U, 0, 0U, 0);
    c3_y = c3_d9;
  }

  sf_mex_destroy(&c3_u);
  return c3_y;
}

static real_T c3_sb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_lastDI, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_tb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_lastDI),
    &c3_thisId);
  sf_mex_destroy(&c3_b_lastDI);
  return c3_y;
}

static real_T c3_tb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d10;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_lastDI_not_empty = FALSE;
  } else {
    chartInstance->c3_lastDI_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d10, 1, 0, 0U, 0, 0U, 0);
    c3_y = c3_d10;
  }

  sf_mex_destroy(&c3_u);
  return c3_y;
}

static real_T c3_ub_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_lastG, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_vb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_lastG),
    &c3_thisId);
  sf_mex_destroy(&c3_b_lastG);
  return c3_y;
}

static real_T c3_vb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d11;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_lastG_not_empty = FALSE;
  } else {
    chartInstance->c3_lastG_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d11, 1, 0, 0U, 0, 0U, 0);
    c3_y = c3_d11;
  }

  sf_mex_destroy(&c3_u);
  return c3_y;
}

static real_T c3_wb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_lastI, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_xb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_lastI),
    &c3_thisId);
  sf_mex_destroy(&c3_b_lastI);
  return c3_y;
}

static real_T c3_xb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d12;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_lastI_not_empty = FALSE;
  } else {
    chartInstance->c3_lastI_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d12, 1, 0, 0U, 0, 0U, 0);
    c3_y = c3_d12;
  }

  sf_mex_destroy(&c3_u);
  return c3_y;
}

static real_T c3_yb_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_lastQ, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_ac_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_lastQ),
    &c3_thisId);
  sf_mex_destroy(&c3_b_lastQ);
  return c3_y;
}

static real_T c3_ac_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d13;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_lastQ_not_empty = FALSE;
  } else {
    chartInstance->c3_lastQ_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d13, 1, 0, 0U, 0, 0U, 0);
    c3_y = c3_d13;
  }

  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_bc_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_realData, const char_T *c3_identifier, uint8_T c3_y_data[732],
  int32_T c3_y_sizes[1])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_cc_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_realData), &c3_thisId,
    c3_y_data, c3_y_sizes);
  sf_mex_destroy(&c3_realData);
}

static void c3_cc_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_y_data
  [732], int32_T c3_y_sizes[1])
{
  uint32_T c3_uv8[1];
  boolean_T c3_bv1[1];
  int32_T c3_tmp_sizes;
  uint8_T c3_tmp_data[732];
  int32_T c3_loop_ub;
  int32_T c3_i30;
  c3_uv8[0] = 732U;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_realData_not_empty = FALSE;
  } else {
    chartInstance->c3_realData_not_empty = TRUE;
    c3_bv1[0] = TRUE;
    sf_mex_import_vs(c3_parentId, sf_mex_dup(c3_u), c3_tmp_data, 1, 3, 0U, 1, 0U,
                     1, c3_bv1, c3_uv8, &c3_tmp_sizes);
    c3_y_sizes[0] = c3_tmp_sizes;
    c3_loop_ub = c3_tmp_sizes - 1;
    for (c3_i30 = 0; c3_i30 <= c3_loop_ub; c3_i30++) {
      c3_y_data[c3_i30] = c3_tmp_data[c3_i30];
    }
  }

  sf_mex_destroy(&c3_u);
}

static real_T c3_dc_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_replyId, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_ec_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_replyId),
    &c3_thisId);
  sf_mex_destroy(&c3_b_replyId);
  return c3_y;
}

static real_T c3_ec_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d14;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_replyId_not_empty = FALSE;
  } else {
    chartInstance->c3_replyId_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d14, 1, 0, 0U, 0, 0U, 0);
    c3_y = c3_d14;
  }

  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_fc_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_b_replyQueue, const char_T *c3_identifier,
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_y[255])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_gc_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_replyQueue), &c3_thisId,
    c3_y);
  sf_mex_destroy(&c3_b_replyQueue);
}

static void c3_gc_emlrt_marshallIn(SFc3_commsdrhwInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_y[255])
{
  int32_T c3_i31;
  uint32_T c3_uv9[2];
  emlrtMsgIdentifier c3_thisId;
  static const char * c3_fieldNames[6] = { "ValidMask", "Fc", "Gain",
    "DecimInterp", "ScaleI", "ScaleQ" };

  c3_sgyjHZtUMVZuM1aKBgGok1D (*c3_r3)[255];
  for (c3_i31 = 0; c3_i31 < 2; c3_i31++) {
    c3_uv9[c3_i31] = 1U + 254U * (uint32_T)c3_i31;
  }

  c3_thisId.fParent = c3_parentId;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_replyQueue_not_empty = FALSE;
  } else {
    chartInstance->c3_replyQueue_not_empty = TRUE;
    sf_mex_check_struct(c3_parentId, c3_u, 6, c3_fieldNames, 2U, c3_uv9);
    c3_r3 = (c3_sgyjHZtUMVZuM1aKBgGok1D (*)[255])c3_y;
    for (c3_i31 = 0; c3_i31 < 255; c3_i31++) {
      c3_thisId.fIdentifier = "ValidMask";
      (*c3_r3)[c3_i31].ValidMask = c3_d_emlrt_marshallIn(chartInstance,
        sf_mex_dup(sf_mex_getfield(c3_u, "ValidMask", "ValidMask", c3_i31)),
        &c3_thisId);
      c3_thisId.fIdentifier = "Fc";
      (*c3_r3)[c3_i31].Fc = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup
        (sf_mex_getfield(c3_u, "Fc", "Fc", c3_i31)), &c3_thisId);
      c3_thisId.fIdentifier = "Gain";
      (*c3_r3)[c3_i31].Gain = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup
        (sf_mex_getfield(c3_u, "Gain", "Gain", c3_i31)), &c3_thisId);
      c3_thisId.fIdentifier = "DecimInterp";
      (*c3_r3)[c3_i31].DecimInterp = c3_d_emlrt_marshallIn(chartInstance,
        sf_mex_dup(sf_mex_getfield(c3_u, "DecimInterp", "DecimInterp", c3_i31)),
        &c3_thisId);
      c3_thisId.fIdentifier = "ScaleI";
      (*c3_r3)[c3_i31].ScaleI = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup
        (sf_mex_getfield(c3_u, "ScaleI", "ScaleI", c3_i31)), &c3_thisId);
      c3_thisId.fIdentifier = "ScaleQ";
      (*c3_r3)[c3_i31].ScaleQ = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup
        (sf_mex_getfield(c3_u, "ScaleQ", "ScaleQ", c3_i31)), &c3_thisId);
    }
  }

  sf_mex_destroy(&c3_u);
}

static real_T c3_l_SendConfig(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_b_replyQueue[255], real_T c3_centerFreq, real_T
  c3_gain, real_T c3_decimation)
{
  real_T c3_repliesOutstanding;
  real_T c3_currCfg_ScaleQ;
  real_T c3_currCfg_ScaleI;
  real_T c3_currCfg_DecimInterp;
  real_T c3_currCfg_Gain;
  real_T c3_currCfg_Fc;
  real_T c3_currCfg_ValidMask;
  uint8_T c3_b_replyId;
  uint8_T c3_ctrlData[255];
  real_T c3_ctrlLength;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_cmdDef[18];
  int32_T c3_i32;
  static char_T c3_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c3_u[23];
  const mxArray *c3_y = NULL;
  char_T c3_b_u[40];
  static char_T c3_cv24[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  const mxArray *c3_b_y = NULL;
  char_T c3_c_u[23];
  const mxArray *c3_c_y = NULL;
  char_T c3_d_u[40];
  const mxArray *c3_d_y = NULL;
  char_T c3_e_u[23];
  const mxArray *c3_e_y = NULL;
  char_T c3_f_u[40];
  const mxArray *c3_f_y = NULL;
  c3_USRP2RuntimeControl(chartInstance, c3_centerFreq, &c3_ctrlLength,
    c3_ctrlData, &c3_b_replyId, &c3_currCfg_ValidMask, &c3_currCfg_Fc,
    &c3_currCfg_Gain, &c3_currCfg_DecimInterp, &c3_currCfg_ScaleI,
    &c3_currCfg_ScaleQ);
  c3_repliesOutstanding = 0.0;
  c3_l_addToQueue(chartInstance, c3_ctrlData, c3_ctrlLength, c3_b_replyQueue,
                  c3_b_replyId, c3_currCfg_ValidMask, c3_currCfg_Fc,
                  c3_currCfg_Gain, c3_currCfg_DecimInterp, c3_currCfg_ScaleI,
                  c3_currCfg_ScaleQ, &c3_repliesOutstanding);
  c3_b_USRP2RuntimeControl(chartInstance, c3_gain, &c3_ctrlLength, c3_ctrlData,
    &c3_b_replyId, &c3_currCfg_ValidMask, &c3_currCfg_Fc, &c3_currCfg_Gain,
    &c3_currCfg_DecimInterp, &c3_currCfg_ScaleI, &c3_currCfg_ScaleQ);
  c3_l_addToQueue(chartInstance, c3_ctrlData, c3_ctrlLength, c3_b_replyQueue,
                  c3_b_replyId, c3_currCfg_ValidMask, c3_currCfg_Fc,
                  c3_currCfg_Gain, c3_currCfg_DecimInterp, c3_currCfg_ScaleI,
                  c3_currCfg_ScaleQ, &c3_repliesOutstanding);
  c3_c_USRP2RuntimeControl(chartInstance, c3_decimation, &c3_ctrlLength,
    c3_ctrlData, &c3_b_replyId, &c3_currCfg_ValidMask, &c3_currCfg_Fc,
    &c3_currCfg_Gain, &c3_currCfg_DecimInterp, &c3_currCfg_ScaleI,
    &c3_currCfg_ScaleQ);
  c3_l_addToQueue(chartInstance, c3_ctrlData, c3_ctrlLength, c3_b_replyQueue,
                  c3_b_replyId, c3_currCfg_ValidMask, c3_currCfg_Fc,
                  c3_currCfg_Gain, c3_currCfg_DecimInterp, c3_currCfg_ScaleI,
                  c3_currCfg_ScaleQ, &c3_repliesOutstanding);
  chartInstance->c3_lastCF_not_empty = TRUE;
  chartInstance->c3_lastG_not_empty = TRUE;
  chartInstance->c3_lastDI_not_empty = TRUE;
  chartInstance->c3_lastI_not_empty = TRUE;
  chartInstance->c3_lastQ_not_empty = TRUE;
  c3_USRP2CmdDef(chartInstance, USRP2Opcodes_ConfigRx, c3_cmdDef);
  c3_currCfg_Fc = chartInstance->c3_lastCF;
  c3_currCfg_Gain = chartInstance->c3_lastG;
  c3_currCfg_DecimInterp = chartInstance->c3_lastDI;
  if (c3_cmdDef[(int32_T)USRP2CmdFields_ScaleI - 1].fsize == 0.0) {
    for (c3_i32 = 0; c3_i32 < 23; c3_i32++) {
      c3_u[c3_i32] = c3_varargin_1[c3_i32];
    }

    c3_y = NULL;
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c3_b_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_ScaleI;
    for (c3_i32 = 0; c3_i32 < 39; c3_i32++) {
      c3_b_u[c3_i32 + 1] = c3_cv24[c3_i32];
    }

    c3_b_y = NULL;
    sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c3_y, 14, c3_b_y);
  } else {
    c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)USRP2CmdFields_ScaleI
                         - 1].dtype, 1024.0, c3_cmdDef[(int32_T)
                         USRP2CmdFields_ScaleI - 1].bytes);
  }

  if (c3_cmdDef[(int32_T)USRP2CmdFields_ScaleQ - 1].fsize == 0.0) {
    for (c3_i32 = 0; c3_i32 < 23; c3_i32++) {
      c3_c_u[c3_i32] = c3_varargin_1[c3_i32];
    }

    c3_c_y = NULL;
    sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_c_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c3_d_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_ScaleQ;
    for (c3_i32 = 0; c3_i32 < 39; c3_i32++) {
      c3_d_u[c3_i32 + 1] = c3_cv24[c3_i32];
    }

    c3_d_y = NULL;
    sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_d_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c3_c_y, 14, c3_d_y);
  } else {
    c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)USRP2CmdFields_ScaleQ
                         - 1].dtype, 1024.0, c3_cmdDef[(int32_T)
                         USRP2CmdFields_ScaleQ - 1].bytes);
  }

  if (c3_cmdDef[(int32_T)USRP2CmdFields_Valid - 1].fsize == 0.0) {
    for (c3_i32 = 0; c3_i32 < 23; c3_i32++) {
      c3_e_u[c3_i32] = c3_varargin_1[c3_i32];
    }

    c3_e_y = NULL;
    sf_mex_assign(&c3_e_y, sf_mex_create("y", c3_e_u, 10, 0U, 1U, 0U, 2, 1, 23));
    c3_f_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Valid;
    for (c3_i32 = 0; c3_i32 < 39; c3_i32++) {
      c3_f_u[c3_i32 + 1] = c3_cv24[c3_i32];
    }

    c3_f_y = NULL;
    sf_mex_assign(&c3_f_y, sf_mex_create("y", c3_f_u, 10, 0U, 1U, 0U, 2, 1, 40));
    sf_mex_call("error", 0U, 2U, 14, c3_e_y, 14, c3_f_y);
  } else {
    c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)USRP2CmdFields_Valid
                         - 1].dtype, 8.0, c3_cmdDef[(int32_T)
                         USRP2CmdFields_Valid - 1].bytes);
  }

  c3_USRP2Cmd2Pkt(chartInstance, c3_cmdDef, c3_ctrlData, &c3_ctrlLength);
  chartInstance->c3_lastCF = c3_currCfg_Fc;
  chartInstance->c3_lastG = c3_currCfg_Gain;
  chartInstance->c3_lastDI = c3_currCfg_DecimInterp;
  chartInstance->c3_lastI = 1024.0;
  chartInstance->c3_lastQ = 1024.0;
  c3_l_addToQueue(chartInstance, c3_ctrlData, c3_ctrlLength, c3_b_replyQueue,
                  c3_ctrlData[2], 8.0, c3_currCfg_Fc, c3_currCfg_Gain,
                  c3_currCfg_DecimInterp, 1024.0, 1024.0, &c3_repliesOutstanding);
  return c3_repliesOutstanding;
}

static void c3_l_addToQueue(SFc3_commsdrhwInstanceStruct *chartInstance, uint8_T
  c3_ctrlData[255], real_T c3_ctrlLength, c3_sgyjHZtUMVZuM1aKBgGok1D
  c3_b_replyQueue[255], uint8_T c3_b_replyId, real_T c3_currCfg_ValidMask,
  real_T c3_currCfg_Fc, real_T c3_currCfg_Gain, real_T c3_currCfg_DecimInterp,
  real_T c3_currCfg_ScaleI, real_T c3_currCfg_ScaleQ, real_T
  *c3_repliesOutstanding)
{
  int32_T c3_i33;
  uint8_T c3_b_ctrlData[255];
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_expl_temp;
  if (c3_ctrlLength > 0.0) {
    for (c3_i33 = 0; c3_i33 < 255; c3_i33++) {
      c3_b_ctrlData[c3_i33] = c3_ctrlData[c3_i33];
    }

    c3_Update(chartInstance, c3_b_ctrlData, c3_ctrlLength);
    c3_expl_temp.ValidMask = c3_currCfg_ValidMask;
    c3_expl_temp.Fc = c3_currCfg_Fc;
    c3_expl_temp.Gain = c3_currCfg_Gain;
    c3_expl_temp.DecimInterp = c3_currCfg_DecimInterp;
    c3_expl_temp.ScaleI = c3_currCfg_ScaleI;
    c3_expl_temp.ScaleQ = c3_currCfg_ScaleQ;
    c3_b_replyQueue[c3_b_replyId - 1] = c3_expl_temp;
    (*c3_repliesOutstanding)++;
  }
}

static boolean_T c3_l_ReceiveReply(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_b_replyQueue[255])
{
  boolean_T c3_replyProcessed;
  char_T *c3_sErr;
  int32_T c3_samplesRead;
  int32_T c3_i34;
  uint8_T c3_uv10[255];
  real_T c3_b_replyId;
  int32_T c3_errStr_sizes[2];
  char_T c3_errStr_data[56];
  int32_T c3_tmp_sizes[2];
  int32_T c3_loop_ub;
  char_T c3_tmp_data[166];
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_expl_temp;
  char_T c3_b_errStr_data[167];
  static char_T c3_cv25[31] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's', ':', 'U',
    'S', 'R', 'P', '2', 'R', 'e', 'c', 'e', 'i', 'v', 'e', 'r', ':', 'R', 'e',
    'p', 'l', 'y', 'E', 'r', 'r' };

  char_T c3_u[31];
  const mxArray *c3_y = NULL;
  char_T c3_u_data[167];
  const mxArray *c3_b_y = NULL;
  int32_T c3_errStr_sizes_idx_1;
  char_T c3_c_errStr_data[167];
  char_T c3_d_errStr_data[167];
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_b_expl_temp;
  static char_T c3_cv26[33] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's', ':', 'U',
    'S', 'R', 'P', '2', 'R', 'e', 'c', 'e', 'i', 'v', 'e', 'r', ':', 'N', 'o',
    'R', 'e', 'p', 'l', 'y', 'E', 'r', 'r' };

  char_T c3_b_u[33];
  const mxArray *c3_c_y = NULL;
  static char_T c3_errMsg[175] = { 'B', 'o', 'a', 'r', 'd', ' ', 'd', 'i', 'd',
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

  char_T c3_c_u[175];
  const mxArray *c3_d_y = NULL;
  static char_T c3_cv27[176] = { 'B', 'o', 'a', 'r', 'd', ' ', 'd', 'i', 'd',
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

  char_T c3_cv28[176];
  c3_replyProcessed = FALSE;

  /* System object Outputs function: dsp.UDPReceiver */
  c3_sErr = GetErrorBuffer(&chartInstance->c3_b_NetworkLib[0U]);
  c3_samplesRead = 255;
  LibOutputs_Network(&chartInstance->c3_b_NetworkLib[0U],
                     &chartInstance->c3_b_Y0[0], &(&c3_samplesRead)[0U]);
  if (*c3_sErr != 0) {
    PrintError(c3_sErr);
  }

  chartInstance->c3_b_Y1 = (uint16_T)c3_samplesRead;
  for (c3_i34 = 0; c3_i34 < 255; c3_i34++) {
    c3_uv10[c3_i34] = chartInstance->c3_b_Y0[c3_i34];
  }

  if (chartInstance->c3_b_Y1 > 0) {
    c3_USRP2RuntimeControlReplies(chartInstance, c3_uv10, chartInstance->c3_b_Y1,
      c3_errStr_data, c3_errStr_sizes, &c3_b_replyId);
    if (!(c3_errStr_sizes[1] == 0)) {
      c3_tmp_sizes[0] = 1;
      c3_tmp_sizes[1] = c3_errStr_sizes[1];
      c3_loop_ub = c3_errStr_sizes[0] * c3_errStr_sizes[1] - 1;
      for (c3_i34 = 0; c3_i34 <= c3_loop_ub; c3_i34++) {
        c3_tmp_data[c3_i34] = c3_errStr_data[c3_i34];
      }

      c3_expl_temp = c3_b_replyQueue[(int32_T)c3_b_replyId - 1];
      c3_l_CheckConfig(chartInstance, c3_tmp_data, c3_tmp_sizes,
                       c3_expl_temp.ValidMask, c3_expl_temp.Fc,
                       c3_expl_temp.Gain, c3_expl_temp.DecimInterp,
                       c3_expl_temp.ScaleI, c3_expl_temp.ScaleQ);
      c3_loop_ub = c3_tmp_sizes[0] * c3_tmp_sizes[1] - 1;
      for (c3_i34 = 0; c3_i34 <= c3_loop_ub; c3_i34++) {
        c3_b_errStr_data[c3_i34] = c3_tmp_data[c3_i34];
      }

      for (c3_i34 = 0; c3_i34 < 31; c3_i34++) {
        c3_u[c3_i34] = c3_cv25[c3_i34];
      }

      c3_y = NULL;
      sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 31));
      c3_loop_ub = c3_tmp_sizes[1] - 1;
      for (c3_i34 = 0; c3_i34 <= c3_loop_ub; c3_i34++) {
        c3_u_data[c3_i34] = c3_b_errStr_data[c3_i34];
      }

      c3_b_y = NULL;
      sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_u_data, 10, 0U, 1U, 0U, 2, 1,
        c3_tmp_sizes[1]));
      sf_mex_call("warning", 0U, 2U, 14, c3_y, 14, c3_b_y);
      c3_errStr_sizes_idx_1 = c3_tmp_sizes[1] + 1;
      c3_loop_ub = c3_tmp_sizes[1] - 1;
      for (c3_i34 = 0; c3_i34 <= c3_loop_ub; c3_i34++) {
        c3_c_errStr_data[c3_i34] = c3_b_errStr_data[c3_i34];
      }

      c3_c_errStr_data[c3_tmp_sizes[1]] = '\x00';
      c3_loop_ub = c3_errStr_sizes_idx_1 - 1;
      for (c3_i34 = 0; c3_i34 <= c3_loop_ub; c3_i34++) {
        c3_b_errStr_data[c3_i34] = c3_c_errStr_data[c3_i34];
      }

      c3_loop_ub = c3_errStr_sizes_idx_1 - 1;
      for (c3_i34 = 0; c3_i34 <= c3_loop_ub; c3_i34++) {
        c3_d_errStr_data[c3_i34] = c3_b_errStr_data[c3_i34];
      }

      PrintError(&c3_d_errStr_data[0]);
    }

    c3_b_expl_temp.ValidMask = 0.0;
    c3_b_expl_temp.Fc = 0.0;
    c3_b_expl_temp.Gain = 0.0;
    c3_b_expl_temp.DecimInterp = 0.0;
    c3_b_expl_temp.ScaleI = 0.0;
    c3_b_expl_temp.ScaleQ = 0.0;
    c3_b_replyQueue[(int32_T)c3_b_replyId - 1] = c3_b_expl_temp;
    c3_replyProcessed = TRUE;
  } else {
    for (c3_i34 = 0; c3_i34 < 33; c3_i34++) {
      c3_b_u[c3_i34] = c3_cv26[c3_i34];
    }

    c3_c_y = NULL;
    sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 33));
    for (c3_i34 = 0; c3_i34 < 175; c3_i34++) {
      c3_c_u[c3_i34] = c3_errMsg[c3_i34];
    }

    c3_d_y = NULL;
    sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_c_u, 10, 0U, 1U, 0U, 2, 1, 175));
    sf_mex_call("error", 0U, 2U, 14, c3_c_y, 14, c3_d_y);
    for (c3_i34 = 0; c3_i34 < 176; c3_i34++) {
      c3_cv28[c3_i34] = c3_cv27[c3_i34];
    }

    PrintError(c3_cv28);
  }

  return c3_replyProcessed;
}

static void c3_l_CheckConfig(SFc3_commsdrhwInstanceStruct *chartInstance, char_T
  c3_errStr_data[166], int32_T c3_errStr_sizes[2], real_T c3_cfgEntry_ValidMask,
  real_T c3_cfgEntry_Fc, real_T c3_cfgEntry_Gain, real_T c3_cfgEntry_DecimInterp,
  real_T c3_cfgEntry_ScaleI, real_T c3_cfgEntry_ScaleQ)
{
  real_T c3_d15;
  uint8_T c3_validMask;
  int32_T c3_i35;
  static char_T c3_cv29[4] = { '%', 's', '\\', 'n' };

  char_T c3_u[4];
  const mxArray *c3_y = NULL;
  int32_T c3_cgMsg_sizes_idx_1;
  int32_T c3_loop_ub;
  char_T c3_b_errStr_data[166];
  char_T c3_u_data[166];
  const mxArray *c3_b_y = NULL;
  const mxArray *c3_simMsg = NULL;
  char_T c3_cgMsg_data[166];
  static char_T c3_cv30[32] = { '%', 's', ' ', ' ', ' ', 'I', 'n', 'v', 'a', 'l',
    'i', 'd', ' ', 'g', 'a', 'i', 'n', ' ', 'v', 'a', 'l', 'u', 'e', ':', ' ',
    '%', '6', '.', '5', 'g', '\\', 'n' };

  char_T c3_b_u[32];
  const mxArray *c3_c_y = NULL;
  real_T c3_c_u;
  const mxArray *c3_d_y = NULL;
  static char_T c3_cv31[21] = { ' ', ' ', 'I', 'n', 'v', 'a', 'l', 'i', 'd', ' ',
    'g', 'a', 'i', 'n', ' ', 'v', 'a', 'l', 'u', 'e', '.' };

  static char_T c3_cv32[44] = { '%', 's', ' ', ' ', ' ', 'I', 'n', 'v', 'a', 'l',
    'i', 'd', ' ', 'c', 'e', 'n', 't', 'e', 'r', ' ', 'f', 'r', 'e', 'q', 'u',
    'e', 'n', 'c', 'y', ' ', 'v', 'a', 'l', 'u', 'e', ':', ' ', '%', '6', '.',
    '5', 'g', '\\', 'n' };

  char_T c3_d_u[44];
  const mxArray *c3_e_y = NULL;
  real_T c3_e_u;
  const mxArray *c3_f_y = NULL;
  int32_T c3_b_cgMsg_sizes_idx_1;
  static char_T c3_cv33[33] = { ' ', ' ', 'I', 'n', 'v', 'a', 'l', 'i', 'd', ' ',
    'c', 'e', 'n', 't', 'e', 'r', ' ', 'f', 'r', 'e', 'q', 'u', 'e', 'n', 'c',
    'y', ' ', 'v', 'a', 'l', 'u', 'e', '.' };

  static char_T c3_cv34[35] = { '%', 's', ' ', ' ', ' ', 'I', 'n', 'v', 'a', 'l',
    'i', 'd', ' ', 'd', 'e', 'c', 'i', 'm', 'a', 't', 'i', 'o', 'n', ' ', 'v',
    'a', 'l', 'u', 'e', ':', ' ', '%', 'd', '\\', 'n' };

  char_T c3_f_u[35];
  const mxArray *c3_g_y = NULL;
  real_T c3_g_u;
  const mxArray *c3_h_y = NULL;
  static char_T c3_cv35[27] = { ' ', ' ', 'I', 'n', 'v', 'a', 'l', 'i', 'd', ' ',
    'd', 'e', 'c', 'i', 'm', 'a', 't', 'i', 'o', 'n', ' ', 'v', 'a', 'l', 'u',
    'e', '.' };

  static char_T c3_cv36[41] = { '%', 's', ' ', ' ', ' ', 'I', 'n', 'v', 'a', 'l',
    'i', 'd', ' ', 'I', '/', 'Q', ' ', 's', 'c', 'a', 'l', 'i', 'n', 'g', ' ',
    'v', 'a', 'l', 'u', 'e', 's', ':', ' ', '%', 'd', ',', ' ', '%', 'd', '\\',
    'n' };

  char_T c3_h_u[41];
  const mxArray *c3_i_y = NULL;
  real_T c3_i_u;
  const mxArray *c3_j_y = NULL;
  real_T c3_j_u;
  const mxArray *c3_k_y = NULL;
  static char_T c3_cv37[29] = { ' ', ' ', 'I', 'n', 'v', 'a', 'l', 'i', 'd', ' ',
    'I', '/', 'Q', ' ', 's', 'c', 'a', 'l', 'i', 'n', 'g', ' ', 'v', 'a', 'l',
    'u', 'e', 's', '.' };

  c3_d15 = c3_cfgEntry_ValidMask;
  c3_d15 = c3_d15 < 0.0 ? muDoubleScalarCeil(c3_d15 - 0.5) : muDoubleScalarFloor
    (c3_d15 + 0.5);
  if (c3_d15 < 256.0) {
    if (c3_d15 >= 0.0) {
      c3_validMask = (uint8_T)c3_d15;
    } else {
      c3_validMask = 0U;
    }
  } else if (c3_d15 >= 256.0) {
    c3_validMask = MAX_uint8_T;
  } else {
    c3_validMask = 0U;
  }

  for (c3_i35 = 0; c3_i35 < 4; c3_i35++) {
    c3_u[c3_i35] = c3_cv29[c3_i35];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 4));
  c3_cgMsg_sizes_idx_1 = c3_errStr_sizes[1];
  c3_loop_ub = c3_errStr_sizes[1] - 1;
  for (c3_i35 = 0; c3_i35 <= c3_loop_ub; c3_i35++) {
    c3_b_errStr_data[c3_i35] = c3_errStr_data[c3_errStr_sizes[0] * c3_i35];
  }

  c3_loop_ub = c3_cgMsg_sizes_idx_1 - 1;
  for (c3_i35 = 0; c3_i35 <= c3_loop_ub; c3_i35++) {
    c3_u_data[c3_i35] = c3_b_errStr_data[c3_i35];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_u_data, 10, 0U, 1U, 0U, 2, 1,
    c3_cgMsg_sizes_idx_1));
  sf_mex_assign(&c3_simMsg, sf_mex_call("sprintf", 1U, 2U, 14, c3_y, 14, c3_b_y));
  c3_cgMsg_sizes_idx_1 = c3_errStr_sizes[1];
  c3_loop_ub = c3_errStr_sizes[1] - 1;
  for (c3_i35 = 0; c3_i35 <= c3_loop_ub; c3_i35++) {
    c3_cgMsg_data[c3_i35] = c3_errStr_data[c3_errStr_sizes[0] * c3_i35];
  }

  if ((c3_validMask & 1) != 0) {
    for (c3_i35 = 0; c3_i35 < 32; c3_i35++) {
      c3_b_u[c3_i35] = c3_cv30[c3_i35];
    }

    c3_c_y = NULL;
    sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 32));
    c3_c_u = c3_cfgEntry_Gain;
    c3_d_y = NULL;
    sf_mex_assign(&c3_d_y, sf_mex_create("y", &c3_c_u, 0, 0U, 0U, 0U, 0));
    sf_mex_assign(&c3_simMsg, sf_mex_call("sprintf", 1U, 3U, 14, c3_c_y, 14,
      sf_mex_dup(c3_simMsg), 14, c3_d_y));
    c3_cgMsg_sizes_idx_1 = c3_errStr_sizes[1] + 21;
    c3_loop_ub = c3_errStr_sizes[1] - 1;
    for (c3_i35 = 0; c3_i35 <= c3_loop_ub; c3_i35++) {
      c3_cgMsg_data[c3_i35] = c3_errStr_data[c3_errStr_sizes[0] * c3_i35];
    }

    for (c3_i35 = 0; c3_i35 < 21; c3_i35++) {
      c3_cgMsg_data[c3_i35 + c3_errStr_sizes[1]] = c3_cv31[c3_i35];
    }
  }

  if ((c3_validMask & 2) != 0) {
    for (c3_i35 = 0; c3_i35 < 44; c3_i35++) {
      c3_d_u[c3_i35] = c3_cv32[c3_i35];
    }

    c3_e_y = NULL;
    sf_mex_assign(&c3_e_y, sf_mex_create("y", c3_d_u, 10, 0U, 1U, 0U, 2, 1, 44));
    c3_e_u = c3_cfgEntry_Fc;
    c3_f_y = NULL;
    sf_mex_assign(&c3_f_y, sf_mex_create("y", &c3_e_u, 0, 0U, 0U, 0U, 0));
    sf_mex_assign(&c3_simMsg, sf_mex_call("sprintf", 1U, 3U, 14, c3_e_y, 14,
      sf_mex_dup(c3_simMsg), 14, c3_f_y));
    c3_b_cgMsg_sizes_idx_1 = c3_cgMsg_sizes_idx_1 + 33;
    c3_loop_ub = c3_cgMsg_sizes_idx_1 - 1;
    for (c3_i35 = 0; c3_i35 <= c3_loop_ub; c3_i35++) {
      c3_b_errStr_data[c3_i35] = c3_cgMsg_data[c3_i35];
    }

    for (c3_i35 = 0; c3_i35 < 33; c3_i35++) {
      c3_b_errStr_data[c3_i35 + c3_cgMsg_sizes_idx_1] = c3_cv33[c3_i35];
    }

    c3_cgMsg_sizes_idx_1 = c3_b_cgMsg_sizes_idx_1;
    c3_loop_ub = c3_b_cgMsg_sizes_idx_1 - 1;
    for (c3_i35 = 0; c3_i35 <= c3_loop_ub; c3_i35++) {
      c3_cgMsg_data[c3_i35] = c3_b_errStr_data[c3_i35];
    }
  }

  if ((c3_validMask & 4) != 0) {
    for (c3_i35 = 0; c3_i35 < 35; c3_i35++) {
      c3_f_u[c3_i35] = c3_cv34[c3_i35];
    }

    c3_g_y = NULL;
    sf_mex_assign(&c3_g_y, sf_mex_create("y", c3_f_u, 10, 0U, 1U, 0U, 2, 1, 35));
    c3_g_u = c3_cfgEntry_DecimInterp;
    c3_h_y = NULL;
    sf_mex_assign(&c3_h_y, sf_mex_create("y", &c3_g_u, 0, 0U, 0U, 0U, 0));
    sf_mex_assign(&c3_simMsg, sf_mex_call("sprintf", 1U, 3U, 14, c3_g_y, 14,
      sf_mex_dup(c3_simMsg), 14, c3_h_y));
    c3_b_cgMsg_sizes_idx_1 = c3_cgMsg_sizes_idx_1 + 27;
    c3_loop_ub = c3_cgMsg_sizes_idx_1 - 1;
    for (c3_i35 = 0; c3_i35 <= c3_loop_ub; c3_i35++) {
      c3_b_errStr_data[c3_i35] = c3_cgMsg_data[c3_i35];
    }

    for (c3_i35 = 0; c3_i35 < 27; c3_i35++) {
      c3_b_errStr_data[c3_i35 + c3_cgMsg_sizes_idx_1] = c3_cv35[c3_i35];
    }

    c3_cgMsg_sizes_idx_1 = c3_b_cgMsg_sizes_idx_1;
    c3_loop_ub = c3_b_cgMsg_sizes_idx_1 - 1;
    for (c3_i35 = 0; c3_i35 <= c3_loop_ub; c3_i35++) {
      c3_cgMsg_data[c3_i35] = c3_b_errStr_data[c3_i35];
    }
  }

  if ((c3_validMask & 8) != 0) {
    for (c3_i35 = 0; c3_i35 < 41; c3_i35++) {
      c3_h_u[c3_i35] = c3_cv36[c3_i35];
    }

    c3_i_y = NULL;
    sf_mex_assign(&c3_i_y, sf_mex_create("y", c3_h_u, 10, 0U, 1U, 0U, 2, 1, 41));
    c3_i_u = c3_cfgEntry_ScaleI;
    c3_j_y = NULL;
    sf_mex_assign(&c3_j_y, sf_mex_create("y", &c3_i_u, 0, 0U, 0U, 0U, 0));
    c3_j_u = c3_cfgEntry_ScaleQ;
    c3_k_y = NULL;
    sf_mex_assign(&c3_k_y, sf_mex_create("y", &c3_j_u, 0, 0U, 0U, 0U, 0));
    sf_mex_call("sprintf", 0U, 4U, 14, c3_i_y, 14, sf_mex_dup(c3_simMsg), 14,
                c3_j_y, 14, c3_k_y);
    c3_b_cgMsg_sizes_idx_1 = c3_cgMsg_sizes_idx_1 + 29;
    c3_loop_ub = c3_cgMsg_sizes_idx_1 - 1;
    for (c3_i35 = 0; c3_i35 <= c3_loop_ub; c3_i35++) {
      c3_b_errStr_data[c3_i35] = c3_cgMsg_data[c3_i35];
    }

    for (c3_i35 = 0; c3_i35 < 29; c3_i35++) {
      c3_b_errStr_data[c3_i35 + c3_cgMsg_sizes_idx_1] = c3_cv37[c3_i35];
    }

    c3_cgMsg_sizes_idx_1 = c3_b_cgMsg_sizes_idx_1;
    c3_loop_ub = c3_b_cgMsg_sizes_idx_1 - 1;
    for (c3_i35 = 0; c3_i35 <= c3_loop_ub; c3_i35++) {
      c3_cgMsg_data[c3_i35] = c3_b_errStr_data[c3_i35];
    }
  }

  c3_errStr_sizes[0] = 1;
  c3_errStr_sizes[1] = c3_cgMsg_sizes_idx_1;
  c3_loop_ub = c3_cgMsg_sizes_idx_1 - 1;
  for (c3_i35 = 0; c3_i35 <= c3_loop_ub; c3_i35++) {
    c3_errStr_data[c3_errStr_sizes[0] * c3_i35] = c3_cgMsg_data[c3_i35];
  }

  sf_mex_destroy(&c3_simMsg);
}

static void c3_b_l_SendConfig(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_b_replyQueue[255], real_T c3_centerFreq, real_T
  c3_gain, real_T c3_decimation)
{
  real_T c3_currCfg_ScaleQ;
  real_T c3_currCfg_ScaleI;
  real_T c3_currCfg_DecimInterp;
  real_T c3_currCfg_Gain;
  real_T c3_currCfg_Fc;
  real_T c3_currCfg_ValidMask;
  uint8_T c3_b_replyId;
  uint8_T c3_ctrlData[255];
  real_T c3_ctrlLength;
  real_T c3_repliesOutstanding;
  c3_s7P91ApZ2CkwDPZE5FamWSB c3_cmdDef[18];
  int32_T c3_b_currCfg_ValidMask;
  int32_T c3_i36;
  static char_T c3_varargin_1[23] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's',
    ':', 'U', 'S', 'R', 'P', '2', ':', 'B', 'a', 'd', 'F', 'i', 'e', 'l', 'd' };

  char_T c3_u[23];
  const mxArray *c3_y = NULL;
  char_T c3_b_u[40];
  static char_T c3_cv38[39] = { ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'a', ' ',
    'v', 'a', 'l', 'i', 'd', ' ', 'f', 'i', 'e', 'l', 'd', ' ', 'f', 'o', 'r',
    ' ', 't', 'h', 'i', 's', ' ', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '.' };

  const mxArray *c3_b_y = NULL;
  char_T c3_c_u[23];
  const mxArray *c3_c_y = NULL;
  char_T c3_d_u[40];
  const mxArray *c3_d_y = NULL;
  char_T c3_e_u[23];
  const mxArray *c3_e_y = NULL;
  char_T c3_f_u[40];
  const mxArray *c3_f_y = NULL;
  c3_e_USRP2RuntimeControl(chartInstance, c3_centerFreq, &c3_ctrlLength,
    c3_ctrlData, &c3_b_replyId, &c3_currCfg_ValidMask, &c3_currCfg_Fc,
    &c3_currCfg_Gain, &c3_currCfg_DecimInterp, &c3_currCfg_ScaleI,
    &c3_currCfg_ScaleQ);
  c3_repliesOutstanding = 0.0;
  c3_l_addToQueue(chartInstance, c3_ctrlData, c3_ctrlLength, c3_b_replyQueue,
                  c3_b_replyId, c3_currCfg_ValidMask, c3_currCfg_Fc,
                  c3_currCfg_Gain, c3_currCfg_DecimInterp, c3_currCfg_ScaleI,
                  c3_currCfg_ScaleQ, &c3_repliesOutstanding);
  c3_f_USRP2RuntimeControl(chartInstance, c3_gain, &c3_ctrlLength, c3_ctrlData,
    &c3_b_replyId, &c3_currCfg_ValidMask, &c3_currCfg_Fc, &c3_currCfg_Gain,
    &c3_currCfg_DecimInterp, &c3_currCfg_ScaleI, &c3_currCfg_ScaleQ);
  c3_l_addToQueue(chartInstance, c3_ctrlData, c3_ctrlLength, c3_b_replyQueue,
                  c3_b_replyId, c3_currCfg_ValidMask, c3_currCfg_Fc,
                  c3_currCfg_Gain, c3_currCfg_DecimInterp, c3_currCfg_ScaleI,
                  c3_currCfg_ScaleQ, &c3_repliesOutstanding);
  c3_g_USRP2RuntimeControl(chartInstance, c3_decimation, &c3_ctrlLength,
    c3_ctrlData, &c3_b_replyId, &c3_currCfg_ValidMask, &c3_currCfg_Fc,
    &c3_currCfg_Gain, &c3_currCfg_DecimInterp, &c3_currCfg_ScaleI,
    &c3_currCfg_ScaleQ);
  c3_l_addToQueue(chartInstance, c3_ctrlData, c3_ctrlLength, c3_b_replyQueue,
                  c3_b_replyId, c3_currCfg_ValidMask, c3_currCfg_Fc,
                  c3_currCfg_Gain, c3_currCfg_DecimInterp, c3_currCfg_ScaleI,
                  c3_currCfg_ScaleQ, &c3_repliesOutstanding);
  chartInstance->c3_lastCF_not_empty = TRUE;
  chartInstance->c3_lastG_not_empty = TRUE;
  chartInstance->c3_lastDI_not_empty = TRUE;
  chartInstance->c3_lastI_not_empty = TRUE;
  chartInstance->c3_lastQ_not_empty = TRUE;
  c3_USRP2CmdDef(chartInstance, USRP2Opcodes_ConfigRx, c3_cmdDef);
  c3_b_currCfg_ValidMask = 0;
  c3_currCfg_Fc = chartInstance->c3_lastCF;
  c3_currCfg_Gain = chartInstance->c3_lastG;
  c3_currCfg_DecimInterp = chartInstance->c3_lastDI;
  if ((1024.0 != chartInstance->c3_lastI) || (1024.0 != chartInstance->c3_lastQ))
  {
    c3_b_currCfg_ValidMask = 8;
    if (c3_cmdDef[(int32_T)USRP2CmdFields_ScaleI - 1].fsize == 0.0) {
      for (c3_i36 = 0; c3_i36 < 23; c3_i36++) {
        c3_u[c3_i36] = c3_varargin_1[c3_i36];
      }

      c3_y = NULL;
      sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 23));
      c3_b_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_ScaleI;
      for (c3_i36 = 0; c3_i36 < 39; c3_i36++) {
        c3_b_u[c3_i36 + 1] = c3_cv38[c3_i36];
      }

      c3_b_y = NULL;
      sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 40));
      sf_mex_call("error", 0U, 2U, 14, c3_y, 14, c3_b_y);
    } else {
      c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)
                           USRP2CmdFields_ScaleI - 1].dtype, 1024.0, c3_cmdDef
                           [(int32_T)USRP2CmdFields_ScaleI - 1].bytes);
    }

    if (c3_cmdDef[(int32_T)USRP2CmdFields_ScaleQ - 1].fsize == 0.0) {
      for (c3_i36 = 0; c3_i36 < 23; c3_i36++) {
        c3_c_u[c3_i36] = c3_varargin_1[c3_i36];
      }

      c3_c_y = NULL;
      sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_c_u, 10, 0U, 1U, 0U, 2, 1, 23));
      c3_d_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_ScaleQ;
      for (c3_i36 = 0; c3_i36 < 39; c3_i36++) {
        c3_d_u[c3_i36 + 1] = c3_cv38[c3_i36];
      }

      c3_d_y = NULL;
      sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_d_u, 10, 0U, 1U, 0U, 2, 1, 40));
      sf_mex_call("error", 0U, 2U, 14, c3_c_y, 14, c3_d_y);
    } else {
      c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)
                           USRP2CmdFields_ScaleQ - 1].dtype, 1024.0, c3_cmdDef
                           [(int32_T)USRP2CmdFields_ScaleQ - 1].bytes);
    }
  }

  if (c3_b_currCfg_ValidMask != 0) {
    if (c3_cmdDef[(int32_T)USRP2CmdFields_Valid - 1].fsize == 0.0) {
      for (c3_i36 = 0; c3_i36 < 23; c3_i36++) {
        c3_e_u[c3_i36] = c3_varargin_1[c3_i36];
      }

      c3_e_y = NULL;
      sf_mex_assign(&c3_e_y, sf_mex_create("y", c3_e_u, 10, 0U, 1U, 0U, 2, 1, 23));
      c3_f_u[0] = (char_T)(int8_T)(int32_T)USRP2CmdFields_Valid;
      for (c3_i36 = 0; c3_i36 < 39; c3_i36++) {
        c3_f_u[c3_i36 + 1] = c3_cv38[c3_i36];
      }

      c3_f_y = NULL;
      sf_mex_assign(&c3_f_y, sf_mex_create("y", c3_f_u, 10, 0U, 1U, 0U, 2, 1, 40));
      sf_mex_call("error", 0U, 2U, 14, c3_e_y, 14, c3_f_y);
    } else {
      c3_USRP2PackFieldVal(chartInstance, c3_cmdDef[(int32_T)
                           USRP2CmdFields_Valid - 1].dtype, (real_T)
                           c3_b_currCfg_ValidMask, c3_cmdDef[(int32_T)
                           USRP2CmdFields_Valid - 1].bytes);
    }

    c3_USRP2Cmd2Pkt(chartInstance, c3_cmdDef, c3_ctrlData, &c3_ctrlLength);
  } else {
    c3_ctrlLength = 0.0;
    for (c3_i36 = 0; c3_i36 < 255; c3_i36++) {
      c3_ctrlData[c3_i36] = 0U;
    }
  }

  chartInstance->c3_lastCF = c3_currCfg_Fc;
  chartInstance->c3_lastG = c3_currCfg_Gain;
  chartInstance->c3_lastDI = c3_currCfg_DecimInterp;
  chartInstance->c3_lastI = 1024.0;
  chartInstance->c3_lastQ = 1024.0;
  c3_l_addToQueue(chartInstance, c3_ctrlData, c3_ctrlLength, c3_b_replyQueue,
                  c3_ctrlData[2], (real_T)c3_b_currCfg_ValidMask, c3_currCfg_Fc,
                  c3_currCfg_Gain, c3_currCfg_DecimInterp, 1024.0, 1024.0,
                  &c3_repliesOutstanding);
}

static boolean_T c3_b_l_ReceiveReply(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_b_replyQueue[255])
{
  boolean_T c3_replyProcessed;
  char_T *c3_sErr;
  int32_T c3_samplesRead;
  int32_T c3_i37;
  uint8_T c3_uv11[255];
  real_T c3_b_replyId;
  int32_T c3_errStr_sizes[2];
  char_T c3_errStr_data[56];
  int32_T c3_tmp_sizes[2];
  int32_T c3_loop_ub;
  char_T c3_tmp_data[166];
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_expl_temp;
  char_T c3_b_errStr_data[167];
  static char_T c3_cv39[31] = { 'c', 'o', 'm', 'm', 'b', 'l', 'k', 's', ':', 'U',
    'S', 'R', 'P', '2', 'R', 'e', 'c', 'e', 'i', 'v', 'e', 'r', ':', 'R', 'e',
    'p', 'l', 'y', 'E', 'r', 'r' };

  char_T c3_u[31];
  const mxArray *c3_y = NULL;
  char_T c3_u_data[167];
  const mxArray *c3_b_y = NULL;
  int32_T c3_errStr_sizes_idx_1;
  char_T c3_c_errStr_data[167];
  char_T c3_d_errStr_data[167];
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_b_expl_temp;
  c3_replyProcessed = FALSE;

  /* System object Outputs function: dsp.UDPReceiver */
  c3_sErr = GetErrorBuffer(&chartInstance->c3_NetworkLib[0U]);
  c3_samplesRead = 255;
  LibOutputs_Network(&chartInstance->c3_NetworkLib[0U], &chartInstance->c3_Y0[0],
                     &(&c3_samplesRead)[0U]);
  if (*c3_sErr != 0) {
    PrintError(c3_sErr);
  }

  chartInstance->c3_Y1 = (uint16_T)c3_samplesRead;
  for (c3_i37 = 0; c3_i37 < 255; c3_i37++) {
    c3_uv11[c3_i37] = chartInstance->c3_Y0[c3_i37];
  }

  if (chartInstance->c3_Y1 > 0) {
    c3_USRP2RuntimeControlReplies(chartInstance, c3_uv11, chartInstance->c3_Y1,
      c3_errStr_data, c3_errStr_sizes, &c3_b_replyId);
    if (!(c3_errStr_sizes[1] == 0)) {
      c3_tmp_sizes[0] = 1;
      c3_tmp_sizes[1] = c3_errStr_sizes[1];
      c3_loop_ub = c3_errStr_sizes[0] * c3_errStr_sizes[1] - 1;
      for (c3_i37 = 0; c3_i37 <= c3_loop_ub; c3_i37++) {
        c3_tmp_data[c3_i37] = c3_errStr_data[c3_i37];
      }

      c3_expl_temp = c3_b_replyQueue[(int32_T)c3_b_replyId - 1];
      c3_l_CheckConfig(chartInstance, c3_tmp_data, c3_tmp_sizes,
                       c3_expl_temp.ValidMask, c3_expl_temp.Fc,
                       c3_expl_temp.Gain, c3_expl_temp.DecimInterp,
                       c3_expl_temp.ScaleI, c3_expl_temp.ScaleQ);
      c3_loop_ub = c3_tmp_sizes[0] * c3_tmp_sizes[1] - 1;
      for (c3_i37 = 0; c3_i37 <= c3_loop_ub; c3_i37++) {
        c3_b_errStr_data[c3_i37] = c3_tmp_data[c3_i37];
      }

      for (c3_i37 = 0; c3_i37 < 31; c3_i37++) {
        c3_u[c3_i37] = c3_cv39[c3_i37];
      }

      c3_y = NULL;
      sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 31));
      c3_loop_ub = c3_tmp_sizes[1] - 1;
      for (c3_i37 = 0; c3_i37 <= c3_loop_ub; c3_i37++) {
        c3_u_data[c3_i37] = c3_b_errStr_data[c3_i37];
      }

      c3_b_y = NULL;
      sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_u_data, 10, 0U, 1U, 0U, 2, 1,
        c3_tmp_sizes[1]));
      sf_mex_call("warning", 0U, 2U, 14, c3_y, 14, c3_b_y);
      c3_errStr_sizes_idx_1 = c3_tmp_sizes[1] + 1;
      c3_loop_ub = c3_tmp_sizes[1] - 1;
      for (c3_i37 = 0; c3_i37 <= c3_loop_ub; c3_i37++) {
        c3_c_errStr_data[c3_i37] = c3_b_errStr_data[c3_i37];
      }

      c3_c_errStr_data[c3_tmp_sizes[1]] = '\x00';
      c3_loop_ub = c3_errStr_sizes_idx_1 - 1;
      for (c3_i37 = 0; c3_i37 <= c3_loop_ub; c3_i37++) {
        c3_b_errStr_data[c3_i37] = c3_c_errStr_data[c3_i37];
      }

      c3_loop_ub = c3_errStr_sizes_idx_1 - 1;
      for (c3_i37 = 0; c3_i37 <= c3_loop_ub; c3_i37++) {
        c3_d_errStr_data[c3_i37] = c3_b_errStr_data[c3_i37];
      }

      PrintError(&c3_d_errStr_data[0]);
    }

    c3_b_expl_temp.ValidMask = 0.0;
    c3_b_expl_temp.Fc = 0.0;
    c3_b_expl_temp.Gain = 0.0;
    c3_b_expl_temp.DecimInterp = 0.0;
    c3_b_expl_temp.ScaleI = 0.0;
    c3_b_expl_temp.ScaleQ = 0.0;
    c3_b_replyQueue[(int32_T)c3_b_replyId - 1] = c3_b_expl_temp;
    c3_replyProcessed = TRUE;
  }

  return c3_replyProcessed;
}

static void c3_b_VRTDecoder(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_s69xIfXV5nXp8sDnVHzDOMB *c3_S, uint8_T c3_packet_data[1464], int32_T
  c3_packet_sizes[1], cint16_T c3_data_data[366], int32_T c3_data_sizes[1],
  real_T *c3_b_dataLength, char_T c3_err_data[24], int32_T c3_err_sizes[2])
{
  uint8_T c3_packetType;
  boolean_T c3_match;
  int32_T c3_i38;
  static char_T c3_cv40[21] = { 'I', 'n', 'c', 'o', 'r', 'r', 'e', 'c', 't', ' ',
    'p', 'a', 'c', 'k', 'e', 't', ' ', 't', 'y', 'p', 'e' };

  int32_T c3_b_err_sizes[2];
  uint8_T c3_packet[4];
  int32_T c3_payload_sizes;
  uint8_T c3_payload_data[1464];
  uint16_T c3_len;
  char_T c3_b_err_data[22];
  int32_T c3_loop_ub;
  c3_data_sizes[0] = 1;
  c3_data_data[0].re = 0;
  c3_data_data[0].im = 0;
  *c3_b_dataLength = 0.0;
  c3_packetType = (uint8_T)((uint32_T)c3_packet_data[0] >> 4);
  if ((c3_packetType == 0) || (c3_packetType == 1)) {
    c3_match = TRUE;
  } else {
    c3_match = FALSE;
  }

  if (!c3_match) {
    c3_err_sizes[0] = 1;
    c3_err_sizes[1] = 21;
    for (c3_i38 = 0; c3_i38 < 21; c3_i38++) {
      c3_err_data[c3_i38] = c3_cv40[c3_i38];
    }
  } else {
    c3_b_err_sizes[0] = 1;
    c3_b_err_sizes[1] = 0;
    for (c3_i38 = 0; c3_i38 < 4; c3_i38++) {
      c3_packet[c3_i38] = c3_packet_data[c3_i38];
    }

    c3_readCommonBits(chartInstance, c3_S, c3_packet, c3_packet_data,
                      c3_packet_sizes, c3_packetType == 1, (c3_packet_data[0] &
      4) != 0, c3_b_err_data, c3_b_err_sizes, &c3_len, c3_payload_data,
                      &c3_payload_sizes);
    c3_err_sizes[0] = 1;
    c3_err_sizes[1] = c3_b_err_sizes[1];
    c3_loop_ub = c3_b_err_sizes[0] * c3_b_err_sizes[1] - 1;
    for (c3_i38 = 0; c3_i38 <= c3_loop_ub; c3_i38++) {
      c3_err_data[c3_i38] = c3_b_err_data[c3_i38];
    }

    c3_readIFDataPacket(chartInstance, c3_S->datatype, c3_payload_data,
                        *(int32_T (*)[1])&c3_payload_sizes, c3_err_data,
                        c3_err_sizes, c3_data_data, c3_data_sizes);
    if (c3_data_sizes[0] != 0) {
      if (c3_data_sizes[0] > 1) {
        *c3_b_dataLength = (real_T)c3_data_sizes[0];
      } else {
        *c3_b_dataLength = 1.0;
      }
    }
  }
}

static void c3_readCommonBits(SFc3_commsdrhwInstanceStruct *chartInstance,
  c3_s69xIfXV5nXp8sDnVHzDOMB *c3_S, uint8_T c3_hdr[4], uint8_T c3_packet_data
  [1464], int32_T c3_packet_sizes[1], boolean_T c3_hasStreamID, uint8_T
  c3_hasTrailer, char_T c3_err_data[22], int32_T c3_err_sizes[2], uint16_T
  *c3_len, uint8_T c3_payload_data[1464], int32_T c3_payload_sizes[1])
{
  int32_T c3_b_len;
  uint8_T c3_newPacketCount;
  int32_T c3_c_len;
  static char_T c3_cv41[22] = { 'I', 'n', 'c', 'o', 'r', 'r', 'e', 'c', 't', ' ',
    'p', 'a', 'c', 'k', 'e', 't', ' ', 'c', 'o', 'u', 'n', 't' };

  c3_s6AmiQ3Zcve7MnsJ9ypFbFH c3_b_S;
  uint8_T c3_streamID[4];
  uint32_T c3_sid;
  uint8_T c3_pkt[8];
  uint32_T c3_classID[2];
  uint8_T c3_x[2];
  uint16_T c3_y;
  c3_b_len = 3;
  c3_newPacketCount = (uint8_T)(c3_hdr[1] & 15);
  if (c3_S->stream.packetCount != c3_newPacketCount) {
    c3_err_sizes[0] = 1;
    c3_err_sizes[1] = 22;
    for (c3_c_len = 0; c3_c_len < 22; c3_c_len++) {
      c3_err_data[c3_err_sizes[0] * c3_c_len] = c3_cv41[c3_c_len];
    }
  }

  c3_newPacketCount++;
  c3_b_S = c3_S->stream;
  c3_b_S.packetCount = (uint8_T)((uint32_T)c3_newPacketCount - (uint32_T)
    ((c3_newPacketCount >> 4) << 4));
  c3_S->stream = c3_b_S;
  c3_b_S = c3_S->stream;
  c3_b_S.packetSize = (uint16_T)((c3_hdr[2] << 8) + c3_hdr[3]);
  c3_S->stream = c3_b_S;
  if (c3_hasStreamID) {
    c3_b_S = c3_S->stream;
    for (c3_c_len = 0; c3_c_len < 4; c3_c_len++) {
      c3_streamID[c3_c_len] = 0U;
      c3_streamID[c3_c_len] = c3_packet_data[c3_c_len + 4];
    }

    memcpy((void *)&c3_sid, (void *)&c3_streamID[0], 4U);
    c3_b_S.streamID = c3_sid;
    c3_S->stream = c3_b_S;
    c3_b_len = 7;
  }

  c3_c_len = c3_b_len + 1;
  c3_b_S = c3_S->stream;
  if ((c3_hdr[0] & 8) != 0) {
    for (c3_c_len = 0; c3_c_len < 8; c3_c_len++) {
      c3_pkt[c3_c_len] = 0U;
      c3_pkt[c3_c_len] = c3_packet_data[(c3_c_len + c3_b_len) + 1];
    }

    memcpy((void *)&c3_classID[0], (void *)&c3_pkt[0], 8U);
    for (c3_c_len = 0; c3_c_len < 2; c3_c_len++) {
      c3_b_S.classID[c3_c_len] = c3_classID[c3_c_len];
      c3_x[c3_c_len] = c3_packet_data[(c3_c_len + c3_b_len) + 5];
    }

    c3_b_S.hasClassID = 1U;
    memcpy((void *)&c3_y, (void *)&c3_x[0], 2U);
    for (c3_c_len = 0; c3_c_len < 2; c3_c_len++) {
      c3_x[c3_c_len] = c3_packet_data[(c3_c_len + c3_b_len) + 7];
    }

    memcpy((void *)&c3_y, (void *)&c3_x[0], 2U);
    c3_c_len = c3_b_len + 9;
  }

  c3_S->stream = c3_b_S;
  c3_newPacketCount = (uint8_T)((uint32_T)c3_hdr[1] >> 6);
  c3_b_S = c3_S->stream;
  c3_b_S.TSI = c3_newPacketCount;
  if (c3_newPacketCount != 0) {
    c3_c_len += 4;
  }

  c3_S->stream = c3_b_S;
  c3_newPacketCount = (uint8_T)((int32_T)((uint32_T)c3_hdr[1] >> 4) & 3);
  c3_b_S = c3_S->stream;
  c3_b_S.TSF = c3_newPacketCount;
  if (c3_newPacketCount != 0) {
    c3_c_len += 8;
  }

  c3_S->stream = c3_b_S;
  c3_extractPayload(chartInstance, c3_S->stream.packetSize, c3_packet_data,
                    c3_packet_sizes, (real_T)c3_c_len, c3_hasTrailer,
                    c3_err_data, c3_err_sizes, c3_payload_data, c3_payload_sizes,
                    c3_len);
}

static void c3_extractPayload(SFc3_commsdrhwInstanceStruct *chartInstance,
  uint16_T c3_S_packetSize, uint8_T c3_packet_data[1464], int32_T
  c3_packet_sizes[1], real_T c3_len, uint8_T c3_hasTrailer, char_T c3_err_data
  [22], int32_T c3_err_sizes[2], uint8_T c3_payload_data[1464], int32_T
  c3_payload_sizes[1], uint16_T *c3_b_len)
{
  uint16_T c3_u16;
  real_T c3_d16;
  uint16_T c3_payloadSize;
  int32_T c3_q0;
  uint32_T c3_qY;
  int32_T c3_i39;
  int32_T c3_b_packet_sizes;
  int32_T c3_loop_ub;
  uint8_T c3_b_packet_data[1464];
  static char_T c3_cv42[22] = { 'i', 'n', 'c', 'o', 'r', 'r', 'e', 'c', 't', ' ',
    'p', 'a', 'y', 'l', 'o', 'a', 'd', ' ', 's', 'i', 'z', 'e' };

  uint16_T c3_u17;
  if (c3_S_packetSize > 16383) {
    c3_u16 = MAX_uint16_T;
  } else {
    c3_u16 = (uint16_T)(c3_S_packetSize << 2);
  }

  c3_d16 = (real_T)c3_u16 - c3_len;
  c3_d16 = c3_d16 < 0.0 ? muDoubleScalarCeil(c3_d16 - 0.5) : muDoubleScalarFloor
    (c3_d16 + 0.5);
  if (c3_d16 < 65536.0) {
    if (c3_d16 >= 0.0) {
      c3_payloadSize = (uint16_T)c3_d16;
    } else {
      c3_payloadSize = 0U;
    }
  } else if (c3_d16 >= 65536.0) {
    c3_payloadSize = MAX_uint16_T;
  } else {
    c3_payloadSize = 0U;
  }

  if (c3_hasTrailer != 0) {
    c3_q0 = c3_payloadSize;
    c3_qY = (uint32_T)c3_q0 - 4U;
    if (c3_qY > (uint32_T)c3_q0) {
      c3_qY = 0U;
    }

    c3_q0 = (int32_T)c3_qY;
    c3_payloadSize = (uint16_T)c3_q0;
  }

  c3_d16 = c3_len + 1.0;
  if (c3_d16 > (real_T)c3_packet_sizes[0]) {
    c3_q0 = 0;
    c3_i39 = 0;
  } else {
    c3_q0 = (int32_T)c3_d16 - 1;
    c3_i39 = c3_packet_sizes[0];
  }

  c3_b_packet_sizes = c3_i39 - c3_q0;
  c3_loop_ub = (c3_i39 - c3_q0) - 1;
  for (c3_i39 = 0; c3_i39 <= c3_loop_ub; c3_i39++) {
    c3_b_packet_data[c3_i39] = c3_packet_data[c3_q0 + c3_i39];
  }

  if (c3_length(chartInstance, c3_b_packet_data, *(int32_T (*)[1])&
                c3_b_packet_sizes) < (real_T)c3_payloadSize) {
    c3_err_sizes[0] = 1;
    c3_err_sizes[1] = 22;
    for (c3_q0 = 0; c3_q0 < 22; c3_q0++) {
      c3_err_data[c3_err_sizes[0] * c3_q0] = c3_cv42[c3_q0];
    }
  }

  c3_u16 = (uint16_T)(c3_len + 1.0);
  c3_d16 = c3_len + (real_T)c3_payloadSize;
  c3_d16 = c3_d16 < 0.0 ? muDoubleScalarCeil(c3_d16 - 0.5) : muDoubleScalarFloor
    (c3_d16 + 0.5);
  if (c3_d16 < 65536.0) {
    if (c3_d16 >= 0.0) {
      c3_u17 = (uint16_T)c3_d16;
    } else {
      c3_u17 = 0U;
    }
  } else if (c3_d16 >= 65536.0) {
    c3_u17 = MAX_uint16_T;
  } else {
    c3_u17 = 0U;
  }

  if (c3_u16 > c3_u17) {
    c3_q0 = 0;
    c3_i39 = 0;
  } else {
    c3_q0 = c3_u16 - 1;
    c3_i39 = c3_u17;
  }

  c3_payload_sizes[0] = c3_i39 - c3_q0;
  c3_loop_ub = (c3_i39 - c3_q0) - 1;
  for (c3_i39 = 0; c3_i39 <= c3_loop_ub; c3_i39++) {
    c3_payload_data[c3_i39] = c3_packet_data[c3_q0 + c3_i39];
  }

  c3_d16 = c3_len + (real_T)c3_payloadSize;
  c3_d16 = c3_d16 < 0.0 ? muDoubleScalarCeil(c3_d16 - 0.5) : muDoubleScalarFloor
    (c3_d16 + 0.5);
  if (c3_d16 < 65536.0) {
    if (c3_d16 >= 0.0) {
      *c3_b_len = (uint16_T)c3_d16;
    } else {
      *c3_b_len = 0U;
    }
  } else if (c3_d16 >= 65536.0) {
    *c3_b_len = MAX_uint16_T;
  } else {
    *c3_b_len = 0U;
  }
}

static void c3_readIFDataPacket(SFc3_commsdrhwInstanceStruct *chartInstance,
  char_T c3_S_datatype[5], uint8_T c3_payload_data[1464], int32_T
  c3_payload_sizes[1], char_T c3_err_data[24], int32_T c3_err_sizes[2], cint16_T
  c3_data_data[366], int32_T c3_data_sizes[1])
{
  char_T c3_cv43[5];
  const mxArray *c3_y = NULL;
  int32_T c3_i;
  static char_T c3_cv44[24] = { 'D', 'a', 't', 'a', ' ', 'l', 'e', 'n', 'g', 't',
    'h', ' ', 'c', 'h', 'a', 'n', 'g', 'e', 'd', ' ', 's', 'i', 'z', 'e' };

  real_T c3_loop_ub;
  int32_T c3_b_loop_ub;
  uint8_T c3_tmp_data[732];
  int32_T c3_tmp_sizes[2];
  static int16_T c3_b_tmp_data[133956];
  static int16_T c3_c_tmp_data[133956];
  if (!chartInstance->c3_dataLength_not_empty) {
    chartInstance->c3_dataLength = c3_length(chartInstance, c3_payload_data,
      c3_payload_sizes);
    chartInstance->c3_dataLength_not_empty = TRUE;
    chartInstance->c3_imagData_sizes = (int32_T)(chartInstance->c3_dataLength /
      2.0);
    chartInstance->c3_imagData_not_empty = !(chartInstance->c3_imagData_sizes ==
      0);
    chartInstance->c3_realData_sizes = (int32_T)(chartInstance->c3_dataLength /
      2.0);
    chartInstance->c3_realData_not_empty = !(chartInstance->c3_realData_sizes ==
      0);
  }

  c3_VRTGetDataStream(chartInstance, c3_S_datatype, c3_cv43);
  if (!c3_eml_strcmp(chartInstance, c3_cv43)) {
    c3_y = NULL;
    sf_mex_assign(&c3_y, sf_mex_create("y", "Assertion failed.", 15, 0U, 0U, 0U,
      2, 1, strlen("Assertion failed.")));
    sf_mex_call("error", 0U, 1U, 14, c3_y);
  }

  if (chartInstance->c3_dataLength != c3_length(chartInstance, c3_payload_data,
       c3_payload_sizes)) {
    c3_err_sizes[0] = 1;
    c3_err_sizes[1] = 24;
    for (c3_i = 0; c3_i < 24; c3_i++) {
      c3_err_data[c3_err_sizes[0] * c3_i] = c3_cv44[c3_i];
    }
  } else {
    c3_loop_ub = chartInstance->c3_dataLength / 2.0;
    for (c3_i = 1; (real_T)c3_i <= c3_loop_ub; c3_i += 2) {
      chartInstance->c3_realData_data[c3_i - 1] = c3_payload_data[(c3_i << 1) -
        1];
      chartInstance->c3_realData_data[c3_i] = c3_payload_data[(c3_i << 1) - 2];
      chartInstance->c3_imagData_data[c3_i - 1] = c3_payload_data[(c3_i << 1) +
        1];
      chartInstance->c3_imagData_data[c3_i] = c3_payload_data[c3_i << 1];
    }
  }

  c3_data_sizes[0] = (int32_T)(chartInstance->c3_dataLength / 4.0);
  c3_b_loop_ub = chartInstance->c3_realData_sizes - 1;
  for (c3_i = 0; c3_i <= c3_b_loop_ub; c3_i++) {
    c3_tmp_data[c3_i] = chartInstance->c3_realData_data[c3_i];
  }

  c3_typecast(chartInstance, c3_tmp_data, *(int32_T (*)[1])&
              chartInstance->c3_realData_sizes, c3_b_tmp_data, c3_tmp_sizes);
  c3_b_loop_ub = chartInstance->c3_imagData_sizes - 1;
  for (c3_i = 0; c3_i <= c3_b_loop_ub; c3_i++) {
    c3_tmp_data[c3_i] = chartInstance->c3_imagData_data[c3_i];
  }

  c3_typecast(chartInstance, c3_tmp_data, *(int32_T (*)[1])&
              chartInstance->c3_imagData_sizes, c3_c_tmp_data, c3_tmp_sizes);
  c3_i = c3_data_sizes[0];
  c3_b_loop_ub = c3_i - 1;
  for (c3_i = 0; c3_i <= c3_b_loop_ub; c3_i++) {
    c3_data_data[c3_i].re = c3_b_tmp_data[c3_i];
    c3_data_data[c3_i].im = c3_c_tmp_data[c3_i];
  }
}

static void init_dsm_address_info(SFc3_commsdrhwInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c3_commsdrhw_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3152968291U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1632219104U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(290140706U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(183418228U);
}

mxArray *sf_c3_commsdrhw_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(47011992U);
    pr[1] = (double)(1592725255U);
    pr[2] = (double)(3537084365U);
    pr[3] = (double)(1459900086U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1464);
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

    mxArray *mxData = mxCreateStructMatrix(1,7,3,dataFields);

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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(14);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c3_commsdrhw(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[5],T\"data\",},{M[1],M[22],T\"dataLength\",},{M[1],M[23],T\"overrun\",},{M[4],M[0],T\"NetworkLib\",},{M[4],M[0],T\"NetworkLib\",},{M[4],M[0],T\"NetworkLib\",},{M[4],M[0],T\"NetworkLib\",},{M[4],M[0],T\"Recv\",S'l','i','p'{{M1x2[247 251],M[0],}}},{M[4],M[0],T\"Y0\",},{M[4],M[0],T\"Y0\",}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[4],M[0],T\"Y1\",},{M[4],M[0],T\"Y1\",},{M[4],M[0],T\"ctrlReceiver\",S'l','i','p'{{M1x2[263 275],M[0],}}},{M[4],M[0],T\"ctrlReceiverBlocking\",S'l','i','p'{{M1x2[298 318],M[0],}}},{M[4],M[0],T\"ctrlSender\",S'l','i','p'{{M1x2[252 262],M[0],}}},{M[4],M[0],T\"dataLength\",S'l','i','p'{{M1x2[6154 6164],M[1],T\"/usr/local/MATLAB/R2011a/toolbox/comm/commutilities/VRTDecoder.m\"}}},{M[4],M[0],T\"dataSender\",S'l','i','p'{{M1x2[276 286],M[0],}}},{M[4],M[0],T\"imagData\",S'l','i','p'{{M1x2[6145 6153],M[1],T\"/usr/local/MATLAB/R2011a/toolbox/comm/commutilities/VRTDecoder.m\"}}},{M[4],M[0],T\"lastCF\",S'l','i','p'{{M1x2[1766 1772],M[1],T\"/usr/local/MATLAB/R2011a/toolbox/comm/commutilities/USRP2RuntimeControl.m\"}}},{M[4],M[0],T\"lastDI\",S'l','i','p'{{M1x2[1779 1785],M[1],T\"/usr/local/MATLAB/R2011a/toolbox/comm/commutilities/USRP2RuntimeControl.m\"}}}}",
    "100 S1x7'type','srcId','name','auxInfo'{{M[4],M[0],T\"lastG\",S'l','i','p'{{M1x2[1773 1778],M[1],T\"/usr/local/MATLAB/R2011a/toolbox/comm/commutilities/USRP2RuntimeControl.m\"}}},{M[4],M[0],T\"lastI\",S'l','i','p'{{M1x2[1786 1791],M[1],T\"/usr/local/MATLAB/R2011a/toolbox/comm/commutilities/USRP2RuntimeControl.m\"}}},{M[4],M[0],T\"lastQ\",S'l','i','p'{{M1x2[1792 1797],M[1],T\"/usr/local/MATLAB/R2011a/toolbox/comm/commutilities/USRP2RuntimeControl.m\"}}},{M[4],M[0],T\"realData\",S'l','i','p'{{M1x2[6136 6144],M[1],T\"/usr/local/MATLAB/R2011a/toolbox/comm/commutilities/VRTDecoder.m\"}}},{M[4],M[0],T\"replyId\",S'l','i','p'{{M1x2[1180 1187],M[1],T\"/usr/local/MATLAB/R2011a/toolbox/comm/commutilities/private/USRP2Cmd2Pkt.m\"}}},{M[4],M[0],T\"replyQueue\",S'l','i','p'{{M1x2[287 297],M[0],}}},{M[8],M[0],T\"is_active_c3_commsdrhw\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 27, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_commsdrhw_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void sf_opaque_initialize_c3_commsdrhw(void *chartInstanceVar)
{
  initialize_params_c3_commsdrhw((SFc3_commsdrhwInstanceStruct*)
    chartInstanceVar);
  initialize_c3_commsdrhw((SFc3_commsdrhwInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c3_commsdrhw(void *chartInstanceVar)
{
  enable_c3_commsdrhw((SFc3_commsdrhwInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_commsdrhw(void *chartInstanceVar)
{
  disable_c3_commsdrhw((SFc3_commsdrhwInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_commsdrhw(void *chartInstanceVar)
{
  sf_c3_commsdrhw((SFc3_commsdrhwInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c3_commsdrhw(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_commsdrhw((SFc3_commsdrhwInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_commsdrhw();/* state var info */
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

extern void sf_internal_set_sim_state_c3_commsdrhw(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_commsdrhw();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_commsdrhw((SFc3_commsdrhwInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c3_commsdrhw(SimStruct* S)
{
  return sf_internal_get_sim_state_c3_commsdrhw(S);
}

static void sf_opaque_set_sim_state_c3_commsdrhw(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c3_commsdrhw(S, st);
}

static void sf_opaque_terminate_c3_commsdrhw(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_commsdrhwInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c3_commsdrhw((SFc3_commsdrhwInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_commsdrhw((SFc3_commsdrhwInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_commsdrhw(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_commsdrhw((SFc3_commsdrhwInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_commsdrhw(SimStruct *S)
{
  /* Actual parameters from chart:
     HOST_CONTROL_PORT HOST_DATA_PORT USRP2_CONTROL_PORT USRP2_DATA_PORT USRP2_IP_NUM frameLength outputDatatype
   */
  const char_T *rtParamNames[] = { "p1", "p2", "p3", "p4", "p5", "p6", "p7" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for HOST_CONTROL_PORT*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);

  /* registration for HOST_DATA_PORT*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_DOUBLE);

  /* registration for USRP2_CONTROL_PORT*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_DOUBLE);

  /* registration for USRP2_DATA_PORT*/
  ssRegDlgParamAsRunTimeParam(S, 3, 3, rtParamNames[3], SS_DOUBLE);

  /* registration for USRP2_IP_NUM*/
  ssRegDlgParamAsRunTimeParam(S, 4, 4, rtParamNames[4], SS_DOUBLE);

  /* registration for frameLength*/
  ssRegDlgParamAsRunTimeParam(S, 5, 5, rtParamNames[5], SS_DOUBLE);

  /* registration for outputDatatype*/
  ssRegDlgParamAsRunTimeParam(S, 6, 6, rtParamNames[6], SS_DOUBLE);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"commsdrhw","commusrp2FMStereo",3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"commsdrhw","commusrp2FMStereo",3,
                "RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"commsdrhw",
      "commusrp2FMStereo",3,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"commsdrhw","commusrp2FMStereo",3,4);
      sf_mark_chart_reusable_outputs(S,"commsdrhw","commusrp2FMStereo",3,3);
    }

    sf_set_rtw_dwork_info(S,"commsdrhw","commusrp2FMStereo",3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2089097003U));
  ssSetChecksum1(S,(4265813242U));
  ssSetChecksum2(S,(2796970572U));
  ssSetChecksum3(S,(3720174553U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c3_commsdrhw(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "commsdrhw", "commusrp2FMStereo",3);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_commsdrhw(SimStruct *S)
{
  SFc3_commsdrhwInstanceStruct *chartInstance;
  chartInstance = (SFc3_commsdrhwInstanceStruct *)malloc(sizeof
    (SFc3_commsdrhwInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_commsdrhwInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_commsdrhw;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c3_commsdrhw;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_commsdrhw;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_commsdrhw;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_commsdrhw;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c3_commsdrhw;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c3_commsdrhw;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c3_commsdrhw;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_commsdrhw;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_commsdrhw;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_commsdrhw;
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

void c3_commsdrhw_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_commsdrhw(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_commsdrhw(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_commsdrhw(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_commsdrhw_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
