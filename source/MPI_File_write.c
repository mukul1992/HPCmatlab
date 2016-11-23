
#include "mex.h"
#include "mpi.h"
#include <string.h>
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	MPI_Status status;
	MPI_File fh;
	if(nrhs!=5) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","5 inputs required.");
	}
	if(nlhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","1 output required.");
	}
	memcpy(&fh,mxGetData(prhs[0]),sizeof(MPI_File));
	
	plhs[0]=mxCreateDoubleScalar((double)MPI_File_write(	fh,  /*file handle*/
													mxGetData(prhs[1]), /*buff*/
													(int)mxGetScalar(prhs[2]),  /*count*/
													*((MPI_Datatype *)mxGetData(prhs[3])),  /*datatype*/
													&status /*status*/
												));

    memcpy(mxGetData(prhs[0]),&fh,sizeof(MPI_File));

    *((int *)mxGetData(mxGetField(prhs[4],0,"count_lo")))=status.count_lo;
    *((int *)mxGetData(mxGetField(prhs[4],0,"count_hi_and_cancelled")))=status.count_hi_and_cancelled;
    *((int *)mxGetData(mxGetField(prhs[4],0,"MPI_SOURCE")))=status.MPI_SOURCE;
    *((int *)mxGetData(mxGetField(prhs[4],0,"MPI_TAG")))=status.MPI_TAG;
    *((int *)mxGetData(mxGetField(prhs[4],0,"MPI_ERROR")))=status.MPI_ERROR;
	
	nlhs=1;
	return; 
}
