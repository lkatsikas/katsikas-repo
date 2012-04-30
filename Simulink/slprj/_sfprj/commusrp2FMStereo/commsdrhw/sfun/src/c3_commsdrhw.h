#ifndef __c3_commsdrhw_h__
#define __c3_commsdrhw_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_sgyjHZtUMVZuM1aKBgGok1D
#define struct_sgyjHZtUMVZuM1aKBgGok1D

typedef struct sgyjHZtUMVZuM1aKBgGok1D
{
  real_T ValidMask;
  real_T Fc;
  real_T Gain;
  real_T DecimInterp;
  real_T ScaleI;
  real_T ScaleQ;
} c3_sgyjHZtUMVZuM1aKBgGok1D;

#else

typedef struct sgyjHZtUMVZuM1aKBgGok1D c3_sgyjHZtUMVZuM1aKBgGok1D;

#endif

#ifndef enum_USRP2Opcodes
#define enum_USRP2Opcodes

typedef enum USRP2Opcodes
{
  USRP2Opcodes_EOP,
  USRP2Opcodes_GetBoardInfo,
  USRP2Opcodes_GetBoardInfoReply = 129,
  USRP2Opcodes_ConfigRx = 4,
  USRP2Opcodes_ConfigRxReply = 132,
  USRP2Opcodes_ConfigTx = 5,
  USRP2Opcodes_ConfigTxReply = 133,
  USRP2Opcodes_StartRxStreaming = 6,
  USRP2Opcodes_StartRxStreamingReply = 134,
  USRP2Opcodes_StopRxStreaming = 7,
  USRP2Opcodes_StopRxStreamingReply = 135,
  USRP2Opcodes_GetDboardInfo = 9,
  USRP2Opcodes_GetDboardInfoReply = 137,
  USRP2Opcodes_SetTxLoOffset = 13,
  USRP2Opcodes_SetTxLoOffsetReply = 141,
  USRP2Opcodes_SetRxLoOffset = 14,
  USRP2Opcodes_SetRxLoOffsetReply = 142,
  USRP2Opcodes_ResetDb = 15,
  USRP2Opcodes_ResetDbReply = 143,
  USRP2Opcodes_ReplyOffset = 128
} c3_USRP2Opcodes;

#else

typedef enum USRP2Opcodes c3_USRP2Opcodes;

#endif

#ifndef enum_USRP2FieldDtypes
#define enum_USRP2FieldDtypes

typedef enum USRP2FieldDtypes
{
  USRP2FieldDtypes_usrp2_uint8_T,
  USRP2FieldDtypes_usrp2_uint16_T,
  USRP2FieldDtypes_usrp2_uint32_T,
  USRP2FieldDtypes_usrp2_sfix64_En20_T,
  USRP2FieldDtypes_usrp2_sfix16_En7_T,
  USRP2FieldDtypes_usrp2_byteArray_T = 7
} c3_USRP2FieldDtypes;

#else

typedef enum USRP2FieldDtypes c3_USRP2FieldDtypes;

#endif

#ifndef enum_USRP2CmdFields
#define enum_USRP2CmdFields

typedef enum USRP2CmdFields
{
  USRP2CmdFields_Opcode = 1,
  USRP2CmdFields_Length,
  USRP2CmdFields_ReplyId,
  USRP2CmdFields_Ok,
  USRP2CmdFields_MacAddr,
  USRP2CmdFields_HwRev,
  USRP2CmdFields_FpgaMd5Lo,
  USRP2CmdFields_FpgaMd5Hi,
  USRP2CmdFields_FirmwareMd5Lo,
  USRP2CmdFields_FirmwareMd5Hi,
  USRP2CmdFields_Valid = 5,
  USRP2CmdFields_Gain,
  USRP2CmdFields_CenterFreq,
  USRP2CmdFields_Decimation,
  USRP2CmdFields_ScaleI,
  USRP2CmdFields_ScaleQ,
  USRP2CmdFields_Interpolation = 8,
  USRP2CmdFields_ConfigOk = 5,
  USRP2CmdFields_SpectrumInverted,
  USRP2CmdFields_BasebandFreq,
  USRP2CmdFields_DdcFreq,
  USRP2CmdFields_ResidualFreq,
  USRP2CmdFields_DucFreq = 8,
  USRP2CmdFields_ItemsPerFrame = 5,
  USRP2CmdFields_TimeInt,
  USRP2CmdFields_TimeFrac,
  USRP2CmdFields_TxDbId = 5,
  USRP2CmdFields_TxFreqMin,
  USRP2CmdFields_TxFreqMax,
  USRP2CmdFields_TxGainMin,
  USRP2CmdFields_TxGainMax,
  USRP2CmdFields_TxGainStepSize,
  USRP2CmdFields_TxDbReserved,
  USRP2CmdFields_RxDbId,
  USRP2CmdFields_RxFreqMin,
  USRP2CmdFields_RxFreqMax,
  USRP2CmdFields_RxGainMin,
  USRP2CmdFields_RxGainMax,
  USRP2CmdFields_RxGainStepSize,
  USRP2CmdFields_RxDbReserved,
  USRP2CmdFields_FreqOffset = 5,
  USRP2CmdFields_Address = 5,
  USRP2CmdFields_Data
} c3_USRP2CmdFields;

#else

typedef enum USRP2CmdFields c3_USRP2CmdFields;

#endif

#ifndef struct_s6AmiQ3Zcve7MnsJ9ypFbFH
#define struct_s6AmiQ3Zcve7MnsJ9ypFbFH

typedef struct s6AmiQ3Zcve7MnsJ9ypFbFH
{
  uint8_T hasStreamID;
  uint32_T streamID;
  uint8_T hasClassID;
  uint32_T classID[2];
  uint8_T packetType;
  uint8_T TSI;
  uint8_T TSF;
  uint8_T packetCount;
  uint16_T packetSize;
} c3_s6AmiQ3Zcve7MnsJ9ypFbFH;

#else

typedef struct s6AmiQ3Zcve7MnsJ9ypFbFH c3_s6AmiQ3Zcve7MnsJ9ypFbFH;

#endif

#ifndef struct_s69xIfXV5nXp8sDnVHzDOMB
#define struct_s69xIfXV5nXp8sDnVHzDOMB

typedef struct s69xIfXV5nXp8sDnVHzDOMB
{
  char_T datatype[5];
  uint8_T hasTrailer;
  uint32_T trailer;
  c3_s6AmiQ3Zcve7MnsJ9ypFbFH stream;
} c3_s69xIfXV5nXp8sDnVHzDOMB;

#else

typedef struct s69xIfXV5nXp8sDnVHzDOMB c3_s69xIfXV5nXp8sDnVHzDOMB;

#endif

#ifndef struct_s7P91ApZ2CkwDPZE5FamWSB
#define struct_s7P91ApZ2CkwDPZE5FamWSB

typedef struct s7P91ApZ2CkwDPZE5FamWSB
{
  real_T offset;
  real_T fsize;
  c3_USRP2FieldDtypes dtype;
  uint8_T bytes[16];
} c3_s7P91ApZ2CkwDPZE5FamWSB;

#else

typedef struct s7P91ApZ2CkwDPZE5FamWSB c3_s7P91ApZ2CkwDPZE5FamWSB;

#endif

typedef struct {
  c3_s69xIfXV5nXp8sDnVHzDOMB c3_Recv;
  c3_sgyjHZtUMVZuM1aKBgGok1D c3_replyQueue[255];
  SimStruct *S;
  real_T c3_HOST_CONTROL_PORT;
  real_T c3_HOST_DATA_PORT;
  real_T c3_NetworkLib[137];
  real_T c3_USRP2_CONTROL_PORT;
  real_T c3_USRP2_DATA_PORT;
  real_T c3_USRP2_IP_NUM[14];
  real_T c3_b_NetworkLib[137];
  real_T c3_c_NetworkLib[137];
  real_T c3_d_NetworkLib[137];
  real_T c3_dataLength;
  real_T c3_frameLength;
  real_T c3_lastCF;
  real_T c3_lastDI;
  real_T c3_lastG;
  real_T c3_lastI;
  real_T c3_lastQ;
  real_T c3_outputDatatype;
  real_T c3_replyId;
  int32_T c3_imagData_sizes;
  int32_T c3_realData_sizes;
  uint16_T c3_Y1;
  uint16_T c3_b_Y1;
  boolean_T c3_Recv_not_empty;
  boolean_T c3_ctrlReceiverBlocking_not_empty;
  boolean_T c3_ctrlReceiver_not_empty;
  boolean_T c3_ctrlSender_not_empty;
  boolean_T c3_dataLength_not_empty;
  boolean_T c3_dataSender_not_empty;
  boolean_T c3_imagData_not_empty;
  boolean_T c3_lastCF_not_empty;
  boolean_T c3_lastDI_not_empty;
  boolean_T c3_lastG_not_empty;
  boolean_T c3_lastI_not_empty;
  boolean_T c3_lastQ_not_empty;
  boolean_T c3_realData_not_empty;
  boolean_T c3_replyId_not_empty;
  boolean_T c3_replyQueue_not_empty;
  uint8_T c3_Y0[255];
  uint8_T c3_b_Y0[255];
  uint8_T c3_imagData_data[732];
  uint8_T c3_is_active_c3_commsdrhw;
  uint8_T c3_realData_data[732];
  ChartInfoStruct chartInfo;
} SFc3_commsdrhwInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c3_commsdrhw_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c3_commsdrhw_get_check_sum(mxArray *plhs[]);
extern void c3_commsdrhw_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
