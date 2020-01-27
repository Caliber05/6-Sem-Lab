#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	int rank,size,N,M,A[20],B[20],c[10],temp[10],i,sum=0,len;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank == 0)
	{
		N=size;

		printf("Enter size of array: \n");
		scanf("%d",&len);
		printf("Enter %d values\n",len);
		for(i=0;i<len;i++)
			scanf("%d",&A[i]);
		M=len/N;
	}

	MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(A,M,MPI_INT,c,M,MPI_INT,0,MPI_COMM_WORLD);
	temp[0]=c[0];
	for(i=1;i<M;i++)
	{
		temp[i]=temp[i-1]+c[i];
	}
	
	MPI_Gather(temp,M,MPI_INT,B,M,MPI_INT,0,MPI_COMM_WORLD);

	if(rank == 0)
	{
	printf("The result gathered in root\n");
	for(i=0;i<len;i++)
		printf("%d\t",B[i]);	
	}
	printf("\n");
	MPI_Finalize();
	return 0;
}
