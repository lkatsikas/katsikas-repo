/* Include files */

#include "YCbCrTesting_sfun.h"
#include "c2_YCbCrTesting.h"
#include "c4_YCbCrTesting.h"
#include "c5_YCbCrTesting.h"
#include "c6_YCbCrTesting.h"
#include "c13_YCbCrTesting.h"
#include "c15_YCbCrTesting.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _YCbCrTestingMachineNumber_;
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void YCbCrTesting_initializer(void)
{
}

void YCbCrTesting_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_YCbCrTesting_method_dispatcher(SimStruct *simstructPtr, unsigned
  int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==2) {
    c2_YCbCrTesting_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==4) {
    c4_YCbCrTesting_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==5) {
    c5_YCbCrTesting_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==6) {
    c6_YCbCrTesting_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==13) {
    c13_YCbCrTesting_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==15) {
    c15_YCbCrTesting_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_YCbCrTesting_process_check_sum_call( int nlhs, mxArray * plhs[],
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
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(422176724U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3823637066U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2514570165U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3366125728U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3457526966U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3559771143U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2600815405U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(423227561U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 2:
        {
          extern void sf_c2_YCbCrTesting_get_check_sum(mxArray *plhs[]);
          sf_c2_YCbCrTesting_get_check_sum(plhs);
          break;
        }

       case 4:
        {
          extern void sf_c4_YCbCrTesting_get_check_sum(mxArray *plhs[]);
          sf_c4_YCbCrTesting_get_check_sum(plhs);
          break;
        }

       case 5:
        {
          extern void sf_c5_YCbCrTesting_get_check_sum(mxArray *plhs[]);
          sf_c5_YCbCrTesting_get_check_sum(plhs);
          break;
        }

       case 6:
        {
          extern void sf_c6_YCbCrTesting_get_check_sum(mxArray *plhs[]);
          sf_c6_YCbCrTesting_get_check_sum(plhs);
          break;
        }

       case 13:
        {
          extern void sf_c13_YCbCrTesting_get_check_sum(mxArray *plhs[]);
          sf_c13_YCbCrTesting_get_check_sum(plhs);
          break;
        }

       case 15:
        {
          extern void sf_c15_YCbCrTesting_get_check_sum(mxArray *plhs[]);
          sf_c15_YCbCrTesting_get_check_sum(plhs);
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
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2518464097U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1775132932U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(725611008U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2560840213U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_YCbCrTesting_autoinheritance_info( int nlhs, mxArray * plhs[],
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
        extern mxArray *sf_c2_YCbCrTesting_get_autoinheritance_info(void);
        plhs[0] = sf_c2_YCbCrTesting_get_autoinheritance_info();
        break;
      }

     case 4:
      {
        extern mxArray *sf_c4_YCbCrTesting_get_autoinheritance_info(void);
        plhs[0] = sf_c4_YCbCrTesting_get_autoinheritance_info();
        break;
      }

     case 5:
      {
        extern mxArray *sf_c5_YCbCrTesting_get_autoinheritance_info(void);
        plhs[0] = sf_c5_YCbCrTesting_get_autoinheritance_info();
        break;
      }

     case 6:
      {
        extern mxArray *sf_c6_YCbCrTesting_get_autoinheritance_info(void);
        plhs[0] = sf_c6_YCbCrTesting_get_autoinheritance_info();
        break;
      }

     case 13:
      {
        extern mxArray *sf_c13_YCbCrTesting_get_autoinheritance_info(void);
        plhs[0] = sf_c13_YCbCrTesting_get_autoinheritance_info();
        break;
      }

     case 15:
      {
        extern mxArray *sf_c15_YCbCrTesting_get_autoinheritance_info(void);
        plhs[0] = sf_c15_YCbCrTesting_get_autoinheritance_info();
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

unsigned int sf_YCbCrTesting_get_eml_resolved_functions_info( int nlhs, mxArray *
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
     case 2:
      {
        extern const mxArray *sf_c2_YCbCrTesting_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_YCbCrTesting_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 4:
      {
        extern const mxArray *sf_c4_YCbCrTesting_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c4_YCbCrTesting_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 5:
      {
        extern const mxArray *sf_c5_YCbCrTesting_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c5_YCbCrTesting_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 6:
      {
        extern const mxArray *sf_c6_YCbCrTesting_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c6_YCbCrTesting_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 13:
      {
        extern const mxArray
          *sf_c13_YCbCrTesting_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c13_YCbCrTesting_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 15:
      {
        extern const mxArray
          *sf_c15_YCbCrTesting_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c15_YCbCrTesting_get_eml_resolved_functions_info();
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

void YCbCrTesting_debug_initialize(void)
{
  _YCbCrTestingMachineNumber_ = sf_debug_initialize_machine("YCbCrTesting",
    "sfun",0,6,0,0,0);
  sf_debug_set_machine_event_thresholds(_YCbCrTestingMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(_YCbCrTestingMachineNumber_,0);
}

void YCbCrTesting_register_exported_symbols(SimStruct* S)
{
}
