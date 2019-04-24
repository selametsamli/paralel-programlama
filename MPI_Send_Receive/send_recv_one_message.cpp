#include "mpi.h"
#include <iostream>
using namespace std;

#define TAG 53

int main(int argc, char* argv[]){
	int myRank,size;

	int a[100];

	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD,&size);

	MPI_Comm_rank(MPI_COMM_WORLD,&myRank);

	if(size != 2 ){
		cout<<"Hataa 2 den fazla işlemci !\n";
		MPI_Abort(MPI_COMM_WORLD, 99);
	}

	if(myRank == 0){
		for(int i=0;i<100;i++)
                    a[i]=i;

		MPI_Send(a, 100, MPI_INT, 1, TAG, MPI_COMM_WORLD);
		cout<<"Process 0 send\n";
	}else{
		MPI_Recv(a, 100, MPI_INT, 0, TAG, MPI_COMM_WORLD, &status );
		cout<<"Process 1: recv\n";
		cout<<"a adli dizinin 1 nolu process deki 2. elemani : "<<a[1]<<endl;
	}

	MPI_Finalize();

	return 0;
}
