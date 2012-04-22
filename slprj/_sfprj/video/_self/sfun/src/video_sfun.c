/* Include files */

#include "video_sfun.h"
#include "c1_video.h"
#include "c2_video.h"
#include "c3_video.h"
#include "c4_video.h"
#include "c5_video.h"
#include "c6_video.h"
#include "c13_video.h"
#include "c14_video.h"
#include "c15_video.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _videoMachineNumber_;
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void video_initializer(void)
{
}

void video_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_video_method_dispatcher(SimStruct *simstructPtr, unsigned int
  chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_video_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_video_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==3) {
    c3_video_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==4) {
    c4_video_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==5) {
    c5_video_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==6) {
    c6_video_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==13) {
    c13_video_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==14) {
    c14_video_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==15) {
    c15_video_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_video_process_check_sum_call( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4237379966U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1671280467U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2857025349U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3798999474U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(290422687U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1299667995U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4084914094U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1650490756U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_video_get_check_sum(mxArray *plhs[]);
          sf_c1_video_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_video_get_check_sum(mxArray *plhs[]);
          sf_c2_video_get_check_sum(plhs);
          break;
        }

       case 3:
        {
          extern void sf_c3_video_get_check_sum(mxArray *plhs[]);
          sf_c3_video_get_check_sum(plhs);
          break;
        }

       case 4:
        {
          extern void sf_c4_video_get_check_sum(mxArray *plhs[]);
          sf_c4_video_get_check_sum(plhs);
          break;
        }

       case 5:
        {
          extern void sf_c5_video_get_check_sum(mxArray *plhs[]);
          sf_c5_video_get_check_sum(plhs);
          break;
        }

       case 6:
        {
          extern void sf_c6_video_get_check_sum(mxArray *plhs[]);
          sf_c6_video_get_check_sum(plhs);
          break;
        }

       case 13:
        {
          extern void sf_c13_video_get_check_sum(mxArray *plhs[]);
          sf_c13_video_get_check_sum(plhs);
          break;
        }

       case 14:
        {
          extern void sf_c14_video_get_check_sum(mxArray *plhs[]);
          sf_c14_video_get_check_sum(plhs);
          break;
        }

       case 15:
        {
          extern void sf_c15_video_get_check_sum(mxArray *plhs[]);
          sf_c15_video_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3691397736U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2228706418U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(148782436U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4073970181U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3833200744U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2233658109U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4096804587U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1230319128U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_video_autoinheritance_info( int nlhs, mxArray * plhs[], int nrhs,
  const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  if (nrhs<2 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern mxArray *sf_c1_video_get_autoinheritance_info(void);
        plhs[0] = sf_c1_video_get_autoinheritance_info();
        break;
      }

     case 2:
      {
        extern mxArray *sf_c2_video_get_autoinheritance_info(void);
        plhs[0] = sf_c2_video_get_autoinheritance_info();
        break;
      }

     case 3:
      {
        extern mxArray *sf_c3_video_get_autoinheritance_info(void);
        plhs[0] = sf_c3_video_get_autoinheritance_info();
        break;
      }

     case 4:
      {
        extern mxArray *sf_c4_video_get_autoinheritance_info(void);
        plhs[0] = sf_c4_video_get_autoinheritance_info();
        break;
      }

     case 5:
      {
        extern mxArray *sf_c5_video_get_autoinheritance_info(void);
        plhs[0] = sf_c5_video_get_autoinheritance_info();
        break;
      }

     case 6:
      {
        extern mxArray *sf_c6_video_get_autoinheritance_info(void);
        plhs[0] = sf_c6_video_get_autoinheritance_info();
        break;
      }

     case 13:
      {
        extern mxArray *sf_c13_video_get_autoinheritance_info(void);
        plhs[0] = sf_c13_video_get_autoinheritance_info();
        break;
      }

     case 14:
      {
        extern mxArray *sf_c14_video_get_autoinheritance_info(void);
        plhs[0] = sf_c14_video_get_autoinheritance_info();
        break;
      }

     case 15:
      {
        extern mxArray *sf_c15_video_get_autoinheritance_info(void);
        plhs[0] = sf_c15_video_get_autoinheritance_info();
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_video_get_eml_resolved_functions_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern const mxArray *sf_c1_video_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_video_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray *sf_c2_video_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_video_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 3:
      {
        extern const mxArray *sf_c3_video_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c3_video_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 4:
      {
        extern const mxArray *sf_c4_video_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c4_video_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 5:
      {
        extern const mxArray *sf_c5_video_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c5_video_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 6:
      {
        extern const mxArray *sf_c6_video_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c6_video_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 13:
      {
        extern const mxArray *sf_c13_video_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c13_video_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 14:
      {
        extern const mxArray *sf_c14_video_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c14_video_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 15:
      {
        extern const mxArray *sf_c15_video_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c15_video_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

void video_debug_initialize(void)
{
  _videoMachineNumber_ = sf_debug_initialize_machine("video","sfun",0,9,0,0,0);
  sf_debug_set_machine_event_thresholds(_videoMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(_videoMachineNumber_,0);
}

void video_register_exported_symbols(SimStruct* S)
{
}
