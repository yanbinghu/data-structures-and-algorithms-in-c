#include<stdio.h>
typedef int ElementType;
void swap(ElementType *a,ElementType *b)
{
    ElementType temp = *a;
    *a = *b;
    *b = temp;
}

/*打印数组内容*/
void printArr(ElementType arr[],int len)
{
	if(NULL == arr)
		return;
	int i = 0 ;
	while(i < len)
	{
		printf("%d ",arr[i]);
		i++;
	}
	printf("\n");
}

/*调整位置i的元素到合适的位置
父节点i
左孩子节点2 * i + 1
右孩子节点2 * i + 2
*/
void adjust_ele(ElementType arr[],int i,int length)
{
    int child;
    ElementType temp;
    for(temp = arr[i];2*i+1 < length;i = child)
    {
        child = 2 * i +1;
        
        /*找到较大的儿子*/
        if(child != length-1 && arr[child+1] > arr[child])
            child+=1;
        /*如果空穴元素小于该儿子，则空穴下滑*/
        if(temp < arr[child])
           arr[i] = arr[child];
        else
         break;
    }
    /*将i位置的元素放到正确的位置*/
    arr[i] = temp;
}
void heap_sort(ElementType arr[],int length)
{
    int i = 0;
    /*构建堆*/
    for(i = length /2;i >= 0;i--)
    {
        adjust_ele(arr,i,length);
        printArr(arr,length);
    }
    for(i = length-1;i > 0;i--)
    {
        /*填充i位置的空穴*/
        swap(&arr[0],&arr[i]);
        
        /*每次都处理堆顶元素*/
        adjust_ele(arr,0,i);
        printArr(arr,length);
    }
}

int main(void)
{
    /*创建数组*/
	ElementType arr[] = {1,10,8,5,7,15,35};
	int len = sizeof(arr)/sizeof(ElementType);
	printf("before sort:");
	printArr(arr,len);

	heap_sort(arr,len);
	printf("after  sort:");
	printArr(arr,len);

	return 0;
}
