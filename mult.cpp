/*********************************************************************
cpMap

  X = cpMap(w)
  Returns the matrix packing of the cross product operator. 
  Given vectors W and V, cross(W)*V=W×V, then the corss(W) can be expressed as follow, 
  cross(W) = [0 -w3 w2;w3 0 -w1; -w2 w1 0].


  Output
  X = [0 -w3 w2;w3 0 -w1; -w2 w1 0], this is the matrix packing of 
  the cross product operator, X = cross(W). 

  Input
  w = [w1; w2; w3], this is the given vector, w.


  Name: Matthew and Yunsik
 ********************************************************************/
#include <matrix.h>
#include <mex.h>   

/* Definitions to keep compatibility with earlier versions of ML */
#ifndef MWSIZE_MAX
typedef int mwSize;
typedef int mwIndex;
typedef int mwSignedIndex;

#if (defined(_LP64) || defined(_WIN64)) && !defined(MX_COMPAT_32)
/* Currently 2^48 based on hardware limitations */
# define MWSIZE_MAX    281474976710655UL
# define MWINDEX_MAX   281474976710655UL
# define MWSINDEX_MAX  281474976710655L
# define MWSINDEX_MIN -281474976710655L
#else
# define MWSIZE_MAX    2147483647UL
# define MWINDEX_MAX   2147483647UL
# define MWSINDEX_MAX  2147483647L
# define MWSINDEX_MIN -2147483647L
#endif
#define MWSIZE_MIN    0UL
#define MWINDEX_MIN   0UL
#endif

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{

//declare variables
    mxArray *a_in_m, *c_out_m;
    const mwSize *dims;
    double *a, *c;
    int dimx, dimy, numdims;
    int i,j;

//associate inputs
    a_in_m = mxDuplicateArray(prhs[0]);

//figure out dimensions
    dims = mxGetDimensions(prhs[0]);
    numdims = mxGetNumberOfDimensions(prhs[0]);
    dimy = (int)dims[0]; 
    dimx = (int)dims[1];
    
    mexPrintf("c_out_m = [%d]\n",dimy);

//associate outputs
    c_out_m = plhs[0] = mxCreateDoubleMatrix(3,3,mxREAL);
    
//associate pointers
    a = mxGetPr(a_in_m);
    c = mxGetPr(c_out_m);

//do something
    for(i=0;i<dimy;i++)
    {
        for(j=0;j<3;j++)
        {
            mexPrintf("element[%d][%d] = %f\n",i,j,a[i*dimy+j]);
            mexPrintf("c_out_m = [%d]\n",i*dimy+j);
            //calculates the crossproduct operator
            if(i == j)    //Set diagonal elements
            {
                c[i*dimy+j] = 0;
            }
            else if( i == 0 && j == 1)
            {
                c[i*dimy+j] = -a[3*dimy+1];
            }
            else if( i == 0 && j == 2)
            {
                c[i*dimy+j] = a[2*dimy+1];
            }
            else if( i == 1 && j == 0)
            {
                c[i*dimy+j] = a[3*dimy+1];
            }
            else if( i == 1 && j == 2)
            {
                c[i*dimy+j] = -a[1*dimy+1];
            }
            else if( i == 2 && j == 0)
            {
                c[i*dimy+j] = -a[2*dimy+1];
            }
            else if( i == 2 && j == 1)
            {
                c[i*dimy+j] = a[1*dimy+1];
            }
            else
            {}
            
        }
    }

    return;
}