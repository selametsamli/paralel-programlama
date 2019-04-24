#include <mpi.h>
#include <iostream>//cout, cin
#include <cstdlib>//srand, rand
#include <ctime>//time(0)
using namespace std;

int MaksimumBul(int*,int);

int main(int argc, char *argv[]){
	srand((unsigned int)time(0));

	//ADIM 1 -> Degiskenleri Deklare Et
	int myRank,size,diziBoyutu,kismiBoyut,lokalMaksimum,globalMaksimum;

	int *diziPtr,*kismiDiziPtr;

	MPI_Status status;

	//ADIM 2 -> MPI Ortamini Ilklendir
	MPI_Init(&argc,&argv);

	//ADIM 3-> Herkes rankini ve size i ogrensin
	MPI_Comm_rank(MPI_COMM_WORLD,&myRank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	//ADIM 4 -> Dizi boyutunu ogren, dizinin icini doldur
	if(myRank==0){
		cout<<"Lutfen dizi boyutunu giriniz: ";
		cin>>diziBoyutu;

		if((diziBoyutu%size)==0){
			kismiBoyut=diziBoyutu/size;

			diziPtr=new int[diziBoyutu];//Yok etmeyi unutma

			for(int i=0;i<diziBoyutu;i++)
				diziPtr[i]=rand()%2019;

			//Kismi dizi boyutunu diger bilgisayarlara ilet
			for(int i=1;i<size;i++)
				MPI_Send(&kismiBoyut,1,MPI_INT,i,25,MPI_COMM_WORLD);

			//Veriyi blok dagitim ile paylastir
			for(int i=1;i<size;i++)
				MPI_Send(&diziPtr[i*kismiBoyut],kismiBoyut,MPI_INT,i,34,MPI_COMM_WORLD);

			globalMaksimum=MaksimumBul(diziPtr,kismiBoyut);

			for(int i=1;i<size;i++){

				MPI_Recv(&lokalMaksimum,1,MPI_INT,i,43,MPI_COMM_WORLD,&status);
				if(lokalMaksimum>globalMaksimum)
					globalMaksimum=lokalMaksimum;
			}

			cout<<"Dizinin Maksimumu: "<<globalMaksimum<<endl;

			delete [] diziPtr;
		}
		else{
			cout<<"Dizi islemcilere esit paylastirilamiyor!\n";
			MPI_Abort(MPI_COMM_WORLD,25);
		}
	}
	else{
		MPI_Recv(&kismiBoyut,1,MPI_INT,0,25,MPI_COMM_WORLD,&status);

		kismiDiziPtr=new int[kismiBoyut];//Yok Etmeyi Unutma

		MPI_Recv(kismiDiziPtr,kismiBoyut,MPI_INT,0,34,MPI_COMM_WORLD,&status);

		lokalMaksimum=MaksimumBul(kismiDiziPtr,kismiBoyut);

		MPI_Send(&lokalMaksimum,1,MPI_INT,0,43,MPI_COMM_WORLD);

		delete [] kismiDiziPtr;
	}

	MPI_Finalize();

	return 0;
}


int MaksimumBul(int *diziPtr,int boyut){

	int maksimum=diziPtr[0];
	for(int i=1;i<boyut;i++)
		if(diziPtr[i]>maksimum)
			maksimum=diziPtr[i];

	return maksimum;
}
