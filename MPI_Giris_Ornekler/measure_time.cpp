#include "mpi.h"
#include <cstdio>
#include <iostream>
using namespace std;

int main(int argc,char* argv[]){
	char processorName[BUFSIZ];
	int  nameLength,rank,size;

	double startTime,endTime;

	MPI_Init(&argc,&argv);

	startTime=MPI_Wtime();

	MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Get_processor_name(processorName, &nameLength);

	printf("Processor %s is (%d of %d)\n",processorName,rank,size);

	endTime=MPI_Wtime();

	if(rank==0){
		cout<<"BUFSIZ: "<<BUFSIZ<<endl;
		printf("%f saniyede (%s) isimli process \n",(endTime-startTime),processorName);
	}
	MPI_Finalize();

	return 0;
}
