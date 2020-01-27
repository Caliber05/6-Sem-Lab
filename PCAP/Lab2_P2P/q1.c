#include"mpi.h"
#include<stdio.h>

int main(int argc,char *argv[])
{

	int rank,size,n,i;
	char x[10];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;
	if(rank==0)
	{
		n=size;
		printf("Enter a word in master process:");
		for(i=0;i<n;i++)
		{
			scanf("%c",&x[i]);
			MPI_Ssend(&x[i],1,MPI_INT,1,1,MPI_COMM_WORLD);
			fprintf(stdout,"I have send %c from process 0\n",x[i]);
			
		}
		fflush(stdout);
	}
	else
	{
		n=size;
		
		for(i=0;i<n;i++)
		{
			MPI_Recv(&x[i],1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
			fprintf(stdout,"I have received %c in process 1\n",x[i]);
		}
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}
