/* Include files */

#include "commdvbc_sfun.h"
#include "c1_commdvbc.h"
#include "c2_commdvbc.h"
#include "c3_commdvbc.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _commdvbcMachineNumber_;
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void commdvbc_initializer(void)
{
}

void commdvbc_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_commdvbc_method_dispatcher(SimStruct *simstructPtr, unsigned int
  chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_commdvbc_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_commdvbc_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==3) {
    c3_commdvbc_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_commdvbc_process_check_sum_call( int nlhs, mxArray * plhs[], int
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
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3067579588U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2555757095U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1155747442U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1669071179U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(628740583U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2932202479U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1713931957U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2835529295U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_commdvbc_get_check_sum(mxArray *plhs[]);
          sf_c1_commdvbc_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_commdvbc_get_check_sum(mxArray *plhs[]);
          sf_c2_commdvbc_get_check_sum(plhs);
          break;
        }

       case 3:
        {
          extern void sf_c3_commdvbc_get_check_sum(mxArray *plhs[]);
          sf_c3_commdvbc_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3876857910U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1565137894U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3264760630U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2650443385U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3001951465U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3897704402U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3836516707U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3951473629U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_commdvbc_autoinheritance_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(aiChksum, "n9SIKzyWtphHcXne8I19BC") == 0) {
          extern mxArray *sf_c1_commdvbc_get_autoinheritance_info(void);
          plhs[0] = sf_c1_commdvbc_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "74y3jalsvAqtgtg364imCG") == 0) {
          extern mxArray *sf_c2_commdvbc_get_autoinheritance_info(void);
          plhs[0] = sf_c2_commdvbc_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 3:
      {
        if (strcmp(aiChksum, "Jmu6MHmRrzrkeXPC1X7CCG") == 0) {
          extern mxArray *sf_c3_commdvbc_get_autoinheritance_info(void);
          plhs[0] = sf_c3_commdvbc_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
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

unsigned int sf_commdvbc_get_eml_resolved_functions_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
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
        extern const mxArray *sf_c1_commdvbc_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_commdvbc_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray *sf_c2_commdvbc_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_commdvbc_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 3:
      {
        extern const mxArray *sf_c3_commdvbc_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c3_commdvbc_get_eml_resolved_functions_info();
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

void commdvbc_debug_initialize(void)
{
  _commdvbcMachineNumber_ = sf_debug_initialize_machine("commdvbc","sfun",0,3,0,
    0,0);
  sf_debug_set_machine_event_thresholds(_commdvbcMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(_commdvbcMachineNumber_,0);
}

void commdvbc_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_commdvbc_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("commdvbc",
      "commdvbc");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_commdvbc_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
