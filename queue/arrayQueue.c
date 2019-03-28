//arrayQueue.c
#include <stdio.h>
#include <string.h>
typedef int ElementType;

/*为测试，将容量值定为较小值5*/
#define MAX_SIZE 5

/*定义队列结构*/
typedef struct QueueInfo
{
    int front; //队头位置
    int rear;  //队尾位置
    ElementType queueArr[MAX_SIZE];//队列数组
}QueueInfo;

#define SUCCESS 0
#define FAILURE 1
#define FALSE 0
#define TRUE 1

/*判断队列是否已满*/
int queue_is_full(QueueInfo *queue)
{
    if((queue->rear + 2) % MAX_SIZE == queue->front)
    {
        printf("queue is full\n");
        return TRUE;
    }
    else 
        return FALSE;
}
/*判断队列是否为满*/
int queue_is_empty(QueueInfo *queue)
{
    if((queue->rear + 1) % MAX_SIZE == queue->front)
    {
        printf("queue is empty\n");
        return TRUE;
    }
    else 
        return FALSE;
}

/*出队*/
int queue_delete(QueueInfo *queue,ElementType *value)
{
    if(queue_is_empty(queue))
        return FAILURE;
    
    *value = queue->queueArr[queue->front];
    printf("get  value from front %d  is %d\n",queue->front,*value);
    queue->front = (queue->front + 1) % MAX_SIZE;
    return SUCCESS;
}

/*入队*/
int queue_insert(QueueInfo *queue,ElementType value)
{
    if(queue_is_full(queue))
        return FAILURE;
    
    queue->rear = (queue->rear + 1) % MAX_SIZE;
    queue->queueArr[queue->rear] = value;
    printf("insert %d  to %d\n",value,queue->rear);
    return SUCCESS;
}
int main(void)
{
    /*队列初始化*/
    QueueInfo queue;
    memset(&queue,0,sizeof(queue));
    queue.front = 1;
    queue.rear = 0;

    /*入队6个数据，最后两个入队失败*/
    queue_insert(&queue,5);
    queue_insert(&queue,4);
    queue_insert(&queue,3);
    queue_insert(&queue,2);
    queue_insert(&queue,1);
    queue_insert(&queue,0);

    /*出队6个数据，最后两个出队失败*/
    ElementType a = 0;
    queue_delete(&queue,&a);
    queue_delete(&queue,&a);
    queue_delete(&queue,&a);
    queue_delete(&queue,&a);
    queue_delete(&queue,&a);
    queue_delete(&queue,&a);
    return 0;
}
