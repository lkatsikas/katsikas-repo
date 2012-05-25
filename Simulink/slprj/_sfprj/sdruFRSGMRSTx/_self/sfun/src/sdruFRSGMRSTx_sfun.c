/* Include files */

#include "sdruFRSGMRSTx_sfun.h"
#include "c2_sdruFRSGMRSTx.h"
#include "c3_sdruFRSGMRSTx.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _sdruFRSGMRSTxMachineNumber_;
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void sdruFRSGMRSTx_initializer(void)
{
}

void sdruFRSGMRSTx_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_sdruFRSGMRSTx_method_dispatcher(SimStruct *simstructPtr,
  unsigned int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==2) {
    c2_sdruFRSGMRSTx_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==3) {
    c3_sdruFRSGMRSTx_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_sdruFRSGMRSTx_process_check_sum_call( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
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
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(53077464U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2944718932U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(559672861U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(568972956U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3093764907U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4196555273U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3265700099U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2599788092U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 2:
        {
          extern void sf_c2_sdruFRSGMRSTx_get_check_sum(mxArray *plhs[]);
          sf_c2_sdruFRSGMRSTx_get_check_sum(plhs);
          break;
        }

       case 3:
        {
          extern void sf_c3_sdruFRSGMRSTx_get_check_sum(mxArray *plhs[]);
          sf_c3_sdruFRSGMRSTx_get_check_sum(plhs);
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
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(82597001U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2707259780U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1458019938U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2049809827U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_sdruFRSGMRSTx_autoinheritance_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
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
     case 2:
      {
        extern mxArray *sf_c2_sdruFRSGMRSTx_get_autoinheritance_info(void);
        plhs[0] = sf_c2_sdruFRSGMRSTx_get_autoinheritance_info();
        break;
      }

     case 3:
      {
        extern mxArray *sf_c3_sdruFRSGMRSTx_get_autoinheritance_info(void);
        plhs[0] = sf_c3_sdruFRSGMRSTx_get_autoinheritance_info();
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

unsigned int sf_sdruFRSGMRSTx_get_eml_resolved_functions_info( int nlhs, mxArray
  * plhs[], int nrhs, const mxArray * prhs[] )
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
     case 2:
      {
        extern const mxArray
          *sf_c2_sdruFRSGMRSTx_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_sdruFRSGMRSTx_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 3:
      {
        extern const mxArray
          *sf_c3_sdruFRSGMRSTx_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c3_sdruFRSGMRSTx_get_eml_resolved_functions_info();
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

void sdruFRSGMRSTx_debug_initialize(void)
{
  _sdruFRSGMRSTxMachineNumber_ = sf_debug_initialize_machine("sdruFRSGMRSTx",
    "sfun",0,2,0,0,0);
  sf_debug_set_machine_event_thresholds(_sdruFRSGMRSTxMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(_sdruFRSGMRSTxMachineNumber_,0);
}

void sdruFRSGMRSTx_register_exported_symbols(SimStruct* S)
{
}
