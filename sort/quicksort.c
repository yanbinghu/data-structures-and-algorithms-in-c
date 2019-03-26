#include <stdlib.h>
#include <stdio.h>
#include <time.h>
/*使用快速排序的区间大小临界值，可根据实际情况选择*/
#define MAX_THRESH 4
typedef int ElementType;
/*元素交换*/
void swap(ElementType *a,ElementType *b)
{
    ElementType temp = *a;
    *a = *b;
    *b = temp;
}
/*插入排序*/
void insertSort(ElementType A[],int N)
{
    /*优化后的插入排序*/
	int j = 0;
	int p = 0;
	int temp = 0;
	for(p = 1;p<N;p++)
	{
	    temp = A[p];
	    for(j = p;j>0 && A[j-1] > temp;j--)
	    {
	        A[j] = A[j-1];
	    }
	    A[j] = temp;
	}

}
/*三数中值法选择基准*/
ElementType medianPivot(ElementType A[],int left,int right)
{
    int center = (left + right)/2 ;
    /*对三数进行排序*/
    if(A[left] > A[center])
        swap(&A[left],&A[center]);
    if(A[left] > A[right])
        swap(&A[left],&A[right]);
    if(A[center] > A[right])
        swap(&A[center],&A[right]);
    
    /*交换中值和倒数第二个元素*/    
    swap(&A[center],&A[right-1]);
    return A[right-1];
}

/*分区操作*/
int partition(ElementType A[],int left,int right)
{
   
    int i = left;
    int j = right-1;
    /*获取基准值*/
    ElementType pivot = medianPivot(A,left,right);
    for(;;)
    {
        /*i j分别向右和向左移动，为什么不直接先i++？*/
        while(A[++i] < pivot)
        {}
        while(A[--j] > pivot)
        {}
        
        if(i < j)
        {
            swap(&A[i],&A[j]);
        }
        /*交错时停止*/
        else
        {
            break;
        }

    }
    /*交换基准元素和i指向的元素*/
    swap(&A[i],&A[right-1]);
    return i;
    
}


void Qsort(ElementType A[],int left,int right)
{
    int i = 0;
    register ElementType *arr = A;
    if(right-left >= MAX_THRESH)
    {
        /*分割操作*/
    	i = partition(arr,left,right);
        /*递归*/
		Qsort(arr,left,i-1);
		Qsort(arr,i+1,right);
    }
    else
    {
        /*数据量较小时，使用插入排序*/
        insertSort(arr+left,right-left+1);
    }
}
/*打印数组内容*/
void printArray(ElementType A[],int n)
{
	if(n > 100)
	{
		printf("too much，will not print\n");
		return;
	}
    int i = 0;
    while(i < n)
    {
        printf("%d ",A[i]);
        i++;
    }
    printf("\n");
}
int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        printf("usage:qsort num\n");
        return -1;
    }
    int len = atoi(argv[1]);
    printf("sort for %d numbers\n",len);
    /*随机产生输入数量的数据*/
    int *A = malloc(sizeof(int)*len);
    int i = 0;
    srand(time(NULL));
    while(i < len)
    {
       A[i] = rand();
       i++;
    }
    printf("before sort:");
    printArray(A,len);
    /*对数据进行排序*/
    Qsort(A,0,len-1);
    printf("after  sort:");
    printArray(A,len);
    return 0;
}
