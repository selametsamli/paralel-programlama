#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc,char* argv[]){
  MPI_Init(&argc,&argv);

  cout<<"Hello World\n";

	MPI_Finalize();

	return 0;
}
