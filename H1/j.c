#include<stdio.h>
void sort( int num[], int n )
{
     int i, j, temp;  //be sure that the temp variable is the same "type" as the array
     int k=0;
     for ( i = 0; i < n - 1; i ++ ) 
     {
          for ( j = i + 1; j < n ;j ++ )
          {
               if( num[ i ] < num[ j ] )         //sorting into descending order
               {
                       temp = num[ i ];   //swapping
                       num[ i ] = num[ j ];
                       num[ j ] = temp; 
                }           
                k++;
          }
     }
     printf("%d\n",k);
}

int main(void){



	int n = 10;
	//int a[10] = {6661,94,0,-34,2321,1123,1, 5, 25,-4};
	int a[10] = {10,9,8,7,6,5,4,3,2,1};
	//int a[100];
	
	/*printf("Anna taulukon koko: ");
	scanf("%d",&n);
	
	for(int i=0;i<n;i++){
		printf("Anna luku: ");
		scanf("%d",&a[i]);
	}*/
	printf("#########################\n");
	printf("Ennen:\n");
	for(int p=0;p<n;p++){
		printf("%d\n",a[p]);
	}
	printf("#########################\n");
	
	
	
	sort(a,n);

	printf("\n");
	printf("#########################\n");
	printf("Tulokset:\n");
	for(int p=0;p<n;p++){
		printf("%d\n",a[p]);
	}
	printf("#########################\n");
	return 0;
	


}
