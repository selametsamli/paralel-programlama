#include "mpi.h"
#include <iostream>
using namespace std;

#define TAG1 53
#define TAG2 34

#define SIZE 10000

int main(int argc, char* argv[]){
	int myRank,size;

	int a[SIZE],
	    b[SIZE];

	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD,&size);

	MPI_Comm_rank(MPI_COMM_WORLD,&myRank);

	if(size != 2 ){
		cout<<"Number of CPUs must be 2 !\n";
		MPI_Abort(MPI_COMM_WORLD, 99);
	}

	if(myRank == 0){
		for(int i=0;i<SIZE;i++)
			a[i]=i;

		MPI_Send(a, SIZE, MPI_INT, 1, TAG1, MPI_COMM_WORLD);
		cout<<"Master Node sent the buffer a to the Processor 1 succesfully.\n";

		MPI_Recv(b, SIZE, MPI_INT, 1, TAG2, MPI_COMM_WORLD, &status);
		cout<<"Master Node received the buffer b from the Processor 1 succesfully.\n";

		cout<<"10th element of the buffer b at Master Node is "<<b[9]<<endl;
	}else{
		for(int i=0;i<SIZE;i++)
			b[i]=i*i;

		MPI_Recv(a, SIZE, MPI_INT, 0, TAG1, MPI_COMM_WORLD, &status);
		cout<<"Processor 1 received the buffer a from the Master Node succesfully.\n";

		MPI_Send(b, SIZE, MPI_INT, 0, TAG2, MPI_COMM_WORLD);
		cout<<"Processor 1 sent the buffer b to the Master Node succesfully.\n";

		cout<<"10th element of the buffer a at Processor 1 is "<<a[9]<<endl;
	}

	MPI_Finalize();

	return 0;
}
