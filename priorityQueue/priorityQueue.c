#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef int ElementType;
typedef struct HeapStruct
{
    int capacity;   //最大元素数量
    int size;    //堆元素数量
    ElementType *eles;  //堆元素数组
}PriorityQueue;

#define  true  1
#define  false  0
#define  SUCCESS 0
#define  FAILURE 1
PriorityQueue *init_PQ(int maxEleNum)
{
    PriorityQueue *pq = NULL;
    
    /*检查输入大小的合法性*/
    if(maxEleNum <= 0 )
        return NULL;
    pq = malloc(sizeof(PriorityQueue));
    if(NULL == pq)
    {
        printf("malloc failed\n");
        return NULL;
    }
    /*下标为0的位置保留，不作使用*/
    pq->eles = malloc((maxEleNum + 1)*sizeof(ElementType));
    if(NULL == pq->eles)
    {
        printf("malloc failed\n");
        free(pq);
        return NULL;
    }
    
    /*初始化成员*/
    memset(pq->eles,0,(maxEleNum + 1)*sizeof(ElementType));
    pq->capacity = maxEleNum;
    pq->size = 0;
    return pq;
}
/*判断优先队列是否满*/
int pq_is_full(PriorityQueue *pq)
{
    if(NULL == pq)
        return false;
    if(pq->capacity == pq->size)
        return true;
    else
        return false;
}
/*判断优先队列是否为空*/
int pq_is_empty(PriorityQueue *pq)
{
    if(NULL == pq)
        return false;
    if(0 == pq->size)
        return true;
    else
        return false;
}
int insert_pq(ElementType value,PriorityQueue *pq)
{
    int i =0;
    
    /*确保优先队列没有满*/
    if(pq_is_full(pq))
    {
        printf("priorityQueue is full\n");
        return FAILURE;
    }
    printf("insert %d\n",value);
    /*不断和父节点探测比较，直到找到属于它的位置*/
    for(i = pq->size+1;pq->eles[i/2] > value && i > 1;i/=2)
    {
        pq->eles[i] = pq->eles[i/2];
    }
    pq->eles[i] = value;
    pq->size++;
    return SUCCESS;
}
int find_min(PriorityQueue *pq,ElementType *value)
{
    if(pq_is_empty(pq))
    {
        printf("priorityQueue is empty\n");
        return FAILURE;
    }
    /*0处的元素作为哨兵没有使用*/
    *value = pq->eles[1];
    return SUCCESS;
}
int delete_min(PriorityQueue *pq,ElementType *min)
{
    int i = 1;
    int minChild =0;
    if(pq_is_empty(pq))
    {
        printf("priorityqueue is empty\n");
        return FAILURE;
    }
    /*取得最小值*/
    *min = pq->eles[1];
    
    /*暂时取出最后的元素*/
    ElementType last = pq->eles[pq->size];
    pq->size--;
    if(0 == pq->size)
    {
        pq->eles[i] = 0;
        return SUCCESS;
    }
    /*不断将空穴下滑*/
    for(i = 1;i * 2 <= pq->size;i = minChild)
    {
        minChild = i * 2;
        /*找到更小的孩子*/
        if(minChild != pq->size && pq->eles[minChild+1] < pq->eles[minChild])
            minChild+=1;
            
        /*如果最后一个元素比空穴处的小儿子大，则继续下滑空穴，将该孩子上滤*/
        if(last >pq->eles[minChild])
            pq->eles[i] = pq->eles[minChild];
        /*否则说明last放的位置不会破坏堆性质，则直接退出循环*/
        else
            break;
    }
    
    /*将最后的元素放在空穴位置*/
    pq->eles[i] = last;
    return SUCCESS;
}
/*销毁队列，按照与申请内存时相反的顺序释放内存*/
int destory_pq(PriorityQueue *pq)
{
    if(NULL == pq)
    {
        return FAILURE;
    }
    free(pq->eles);
    pq->eles = NULL;
    free(pq);
    pq = NULL;
    printf("destory pq success\n");
    return SUCCESS;
}
int main(void)
{
    /*创建可以容纳6个元素的优先队列*/
    PriorityQueue *pq = init_PQ(6);
    
    int arr[]={3,4,5,6,8,2,9,10};
    int i =0;
    /*试图插入多余6个的数据，最后两个会由于队列满而无法插入*/
    for(i = 0;i < 8;i++)
    {
        insert_pq(arr[i],pq);
    }
    
    /*遍历队列数组内容*/
    printf("the arr value is:");
    for(i=0;i < pq->size;i++)
    {
        printf(" %d",pq->eles[i+1]);
    }
    printf("\n");
    printf("pq size is %d\n",pq->size);
    ElementType min;
    int size = pq->size;
    /*每次都从堆顶取元素*/
    for(i=0;i < size ;i++)
    {
        if(SUCCESS == find_min(pq,&min))
        {
            printf("the min is %d\n",min);
            delete_min(pq,&min);
        }
    }
    
    /*销毁优先队列*/
    destory_pq(pq);
    return 0;
}
