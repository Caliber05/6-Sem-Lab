#include "mpi.h"
#include <stdio.h>

int main(int argc,char*argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int res;
	int a = 6;
	int b = 4;
	
	if (rank == 0) {
		res = a + b;
		printf("Process %d added: %d\n", rank, res);
	} else if (rank == 1) {
		res = a - b;
		printf("Process %d substracted: %d\n", rank, res);
	} else if (rank == 2) {
		res = a * b;
		printf("Process %d multiplied: %d\n", rank, res);
	} else if (rank == 3) {
		res = a / b;
		printf("Process %d divided : %d\n", rank, res);
	}

	MPI_Finalize();

	return 0;
}