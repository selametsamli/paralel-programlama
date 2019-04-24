#include "mpi.h"
#include <iostream>
using namespace std;


int main(int argc, char* argv[]){
    int myRank,size;

    double a[100],b[100];

    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD,&size);

    MPI_Comm_rank(MPI_COMM_WORLD,&myRank);

    if(size != 2){
      cout<<"CPU sayısı 2'den farklı!\n";
	    MPI_Abort(MPI_COMM_WORLD, 99);
    }

    if(myRank == 0){
        MPI_Recv(b, 100, MPI_DOUBLE, 1, 19, MPI_COMM_WORLD, &status);
        cout<<"Rank ("<<myRank<<") mesajı aldı.\n";

        MPI_Send(a, 100, MPI_DOUBLE, 1, 17, MPI_COMM_WORLD);
        cout<<"Rank ("<<myRank<<") mesayı yolladı.\n";
    }else{
        MPI_Recv(b, 100, MPI_DOUBLE, 0, 17, MPI_COMM_WORLD, &status);
        cout<<"Rank ("<<myRank<<") mesajı aldı.\n";

        MPI_Send(a, 100, MPI_DOUBLE, 0, 19, MPI_COMM_WORLD );
        cout<<"Rank ("<<myRank<<") mesajı yolladı.\n";
    }

    MPI_Finalize();

    return 0;
}
