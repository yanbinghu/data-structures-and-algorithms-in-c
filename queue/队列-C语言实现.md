
---
title: 队列-c语言实现
date: 2019-3-28 20:00:00
comments: true
categories: 数据结构与算法
tags: [C,数据结构与算法,队列]

---
原文地址：[队列-c语言实现](https://www.yanbinghu.com/2019/03/28/13055.html)
## 前言
队列是一种先进先出的数据结构，也是常见的数据结构之一。日常生活中的排队买东西就是一种典型的队列，而在购票系统也需要一个队列处理用户的购票请求，当然这里的队列就复杂多了。本文介绍队列的基本概念和实现。
<!--more-->
## 队列常见操作
队列最常见的操作是入队和出队，拿排队买东西来说，入队就是新来一个人排在队伍后面，而出队就是一个人已经结账离开。

## 队列基本实现考虑
与实现栈不同，它需要两个指针，一个指向队头，一个指向队尾，这样才能方便地进行入队或出队操作，因此队列的实现要比栈难一些。在说明如何实现一个队列之前，先看实现一个队列可能需要注意哪些问题。

假如我们使用数组按照实现栈的方式来实现队列。并且队列中的数据如下：

|0|1|2|3|4|
|--|--|--|--|--|
|10|11|12|13|14|
|front||||rear|

这个时候从队头front处删除一个数据，这是很容易的。

|0|1|2|3|4|
|--|--|--|--|--|
||11|12|13|14|
||front|||rear|


但是如果要入队一个数据呢？这个时候发现队尾已经没有空间了，为了插入一个元素，必须将所有元素都往队头移动，这似乎很符合我们排队的习惯，前面一个人走了，后面的人都往前一个位置。**但是在数组中，将所有的元素都往队头移动的开销是不容忽略的！**

有人可能已经注意到了，原来删除的地方还有一个空位呢，不如把新的元素加入到这里，然后将尾指针rear指向该处即可。没错，这就相当于**把该数组当成了一个循环数组**，即可以看成数组尾部和头部是连着的。这个时候就变成了下面的情况：

|0|1|2|3|4|
|--|--|--|--|--|
|15|11|12|13|14|
|rear|front||||

此时，队列是满的，rear指向下标0处，而front指向下标1处。如果这个时候删除这五个元素，就变成下面的情况：

|0|1|2|3|4|
|--|--|--|--|--|
| | | | | |
|rear|front||||

我们发现队列为空时，rear指向下标0处，而front指向下标1处，与队列满时是一样的，这样的话，如何区分队列是空还是满呢？

很明显，队列为空时与队列满时元素数量是不一样的，我们可以通过**判断队列中元素的数量是否已达上限，来判断队列是否为空。**

还有一种方法，就是使得**队列满时，不占满整个数组，而保留一个空位。这样的情况下，队列满时，两个指针相隔2**：

|0|1|2|3|4|
|--|--|--|--|--|
|15||12|13|14|
|rear||front|||

队列空时：

|0|1|2|3|4|
|--|--|--|--|--|
||||||
|rear|front||||

两个指针相隔1。那么就可以通过指针的间隔来判断队列是否为空了。

这里就说明了队列实现需要考虑的两个问题：
+ 如何高效地将元素入队
+ 如何判断队列为空或队列为满

当然了，如果你使用链表实现队列，那么入队也完全不需要搬移数据。
## 实现
队列的实现有多种方式可以选择，例如：
+ 静态数组，容量固定，操作简便，效率高
+ 动态数组，容量可自定义，操作简便，因为涉及内存的申请与释放，因此实现比静态数组稍微复杂一点点
+ 链表，容量理论上只受限于内存，实现也较为复杂
+ 其他

因篇幅有限，本文只选择一种实现进行说明。


本文的代码实现采用了静态数组的方式实现一个队列，并且为了避免数据频繁搬移，使用了前面介绍的循环队列；为了测试队满的情况，将队列的容量设置成了很小的值，另外，也通过保留一个空位的方式来解决队空和队满无法区分的问题。

队列的主要定义或操作解释如下。
+ 队列结构定义，定义一个结构体，包含存储队头位置和队尾位以及队列数组
+ 队列初始化，初始时，队尾值为0，队头值为1，两者差值为1
+ 队列是否为空，队尾和队头差值并取模为1时，表明队列为空
+ 队列是否已满，队尾和队头差值取模为2时，表明队列满
+ 入队，入队前检查队列是否已满，如未满，队尾加1取模，并赋值
+ 出队，出队前检查队列是否为空，如不空，则取值，并加1取模

## 代码
完整可运行代码实现如下：
```c
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
    else return FALSE;
}
/*判断队列是否为满*/
int queue_is_empty(QueueInfo *queue)
{
    if((queue->rear + 1) % MAX_SIZE == queue->front)
    {
        printf("queue is empty\n");
        return TRUE;
    }
    else return FALSE;
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

```
编译：
```
$ gcc  -o arrayQueue arrayQueue.c
```
运行结果：
```
insert 5  to 1
insert 4  to 2
insert 3  to 3
insert 2  to 4
queue is full
queue is full
get  value from front 1  is 5
get  value from front 2  is 4
get  value from front 3  is 3
get  value from front 4  is 2
queue is empty
queue is empty
```

## 总结
与《[栈的实现](https://www.yanbinghu.com/2019/03/16/31765.html)》相比，队列的数组实现相对来说稍微复杂一点，因为它需要考虑队空和对满的区别，以及考虑数据搬移的性能影响，但是从实现本身来看，代码并不复杂。关于队列的动态数组和链表实现可自己尝试。
