#include "mpi.h"
#include <cstdio>
using namespace std;

int main(int argc,char* argv[])
{
	char processorName[BUFSIZ];
	int  nameLength;

	MPI_Init(&argc, &argv);

	MPI_Get_processor_name(processorName, &nameLength);

	printf("Processor adı %s\n",processorName);

	MPI_Finalize();

	return 0;
}
