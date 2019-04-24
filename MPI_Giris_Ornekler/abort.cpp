#include "mpi.h"
#include <cstdio>
#include <iostream>
using namespace std;

int main(int argc,char* argv[]){
	char processorName[BUFSIZ];
	int nameLength,rank,size,returnCode;

	returnCode = MPI_Init(&argc,&argv);

	if(returnCode != MPI_SUCCESS){
		cout<<"MPI programı başlatılırken hata oluştu. \n";

		MPI_Abort(MPI_COMM_WORLD, returnCode);
	}

	MPI_Comm_size(MPI_COMM_WORLD,&size);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(size != 4 ){
		cout<<"CPU sayısı 4 den fazla olmamalıdır\n";
		MPI_Abort(MPI_COMM_WORLD, 99);
	}

	MPI_Get_processor_name(processorName, &nameLength);
	printf("Processor adı: %s \n",processorName);

	MPI_Finalize();

	return 0;
}
