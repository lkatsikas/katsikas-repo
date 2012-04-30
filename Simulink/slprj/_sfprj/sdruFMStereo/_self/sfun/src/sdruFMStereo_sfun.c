/* Include files */

#include "sdruFMStereo_sfun.h"
#include "c2_sdruFMStereo.h"
#include "c4_sdruFMStereo.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void sdruFMStereo_initializer(void)
{
}

void sdruFMStereo_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_sdruFMStereo_method_dispatcher(SimStruct *simstructPtr, unsigned
  int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==2) {
    c2_sdruFMStereo_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==4) {
    c4_sdruFMStereo_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_sdruFMStereo_process_check_sum_call( int nlhs, mxArray * plhs[],
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
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1513573446U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1777940559U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3841813796U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3832130420U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2714050370U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1589114477U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1794850700U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3432844462U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 2:
        {
          extern void sf_c2_sdruFMStereo_get_check_sum(mxArray *plhs[]);
          sf_c2_sdruFMStereo_get_check_sum(plhs);
          break;
        }

       case 4:
        {
          extern void sf_c4_sdruFMStereo_get_check_sum(mxArray *plhs[]);
          sf_c4_sdruFMStereo_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(731375052U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(461736548U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4058955150U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1924596090U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1478619445U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1870460987U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2262126266U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3960856569U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_sdruFMStereo_autoinheritance_info( int nlhs, mxArray * plhs[],
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
        extern mxArray *sf_c2_sdruFMStereo_get_autoinheritance_info(void);
        plhs[0] = sf_c2_sdruFMStereo_get_autoinheritance_info();
        break;
      }

     case 4:
      {
        extern mxArray *sf_c4_sdruFMStereo_get_autoinheritance_info(void);
        plhs[0] = sf_c4_sdruFMStereo_get_autoinheritance_info();
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

unsigned int sf_sdruFMStereo_get_eml_resolved_functions_info( int nlhs, mxArray *
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
        extern const mxArray *sf_c2_sdruFMStereo_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_sdruFMStereo_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 4:
      {
        extern const mxArray *sf_c4_sdruFMStereo_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c4_sdruFMStereo_get_eml_resolved_functions_info();
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

void sdruFMStereo_register_exported_symbols(SimStruct* S)
{
}
