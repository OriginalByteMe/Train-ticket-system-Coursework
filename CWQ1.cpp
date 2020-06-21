#include <stdio.h>
void occurrence (const int a[],int frequency[],int size);
int main()
{
    int arr1[50], fr1[50];
    int n;


       printf("\n\nCount frequency of each element of an array:\n");
       printf("------------------------------------------------\n");

       printf("Input the number of elements to be stored in the array :");
       scanf("%d",&n);

       printf("Input %d elements in the array :\n",n);
       for(int i=0;i<n;i++)
            {
	      printf("element - %d : ",i);
	      scanf("%d",&arr1[i]);
		  fr1[i] = -1;
          printf("\nfr1[i] = %d", fr1[i]);
	    }
        
        
        //occurrence(arr1,fr1,n);
        printf("\nThe frequency of all elements of array : \n");
        for(int i=0; i<n; i++)
        {
            if(fr1[i]!=0)
            {
                printf("%d occurs %d times\n", arr1[i], fr1[i]);
            }
        }
 
 return 0;
}

void occurrence (const int a[],int frequency[],int size){
    int ctr;
    for (int i=0; i<size;i++){
        ctr=1;
        for(int j=i+1; j<size;j++){
            if(a[i]==a[j]){
                ctr++;
                frequency[j]=0;
        
            }
        }
        if(frequency[i]!=0){
            frequency[i] = ctr;
        }
    }
    return;
}

