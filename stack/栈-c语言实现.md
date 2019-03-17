---
title: 栈-c语言实现
comments: true
categories: 数据结构与算法
tags:
  - C
  - 数据结构与算法
  - 栈
abbrlink: 31765
date: 2019-03-16 18:00:00
---
## 前言
栈是一种应用广泛的数据结构，例如函数的调用就需要使用栈，其实我们在介绍《[快速排序优化详解](https://www.yanbinghu.com/2019/02/21/28355.html)》的时候也使用到了栈结构。栈最鲜明的特点就是后进先出，一桶羽毛球就是类似这样的结构，最晚放进去的，可以最先拿出来。本文将介绍的是如何自己实现一个栈结构。
<!--more-->
## 栈的操作
栈的常见操作有出栈(POP)，从栈中弹出一个元素；入栈(PUSH)，将一个元素压入栈中，访问栈顶元素(TOP)，判断栈是否为空等。

## 栈的实现
栈是较容易实现的抽象数据结构之一。我们可以选择数组或者链表来实现，它们各有特点，前者容量有限且固定，但操作简单，而后者容量理论上不受限，但是操作并不如数组方便，每次入栈要进行内存申请，出栈要释放内存，稍有不慎便造成内存泄露。本文对两种实现都做介绍。

## 数组实现栈
用数组实现栈是比较容易的。这个时候的栈其实更像是访问受限的数组，数组可以通过下标访问，查找，插入等，但是栈只能从栈顶，或者说数组的末尾进行操作。我们只需要一个指针记录栈顶即可。有人可能问了，既然这里栈是访问受限的数组，为什么不直接使用数组呢？所谓能力越大，责任越大，而你暴露的越多，风险也越大就是如此。

我们来看一下数组实现栈的时候，栈的操作都是怎么实现的呢？

#### 定义栈
用数组实现栈时是很容易定义的，只要定一个固定长度的数组即可，然后使用一个指针或者数组下标标记栈顶（topOfStack），栈为空时，它是-1：
```c
#define STACK_SIZE 64 /*栈大小*/
#define TOP_OF_STACK -1 /*栈顶位置*/
typedef int ElementType /*栈元素类型*/
typedef struct StackInfo
{
    int topOfStack; /*记录栈顶位置*/
    ElementType stack[STACK_SIZE]; /*栈数组，也可以使用动态数组实现*/
}StackInfo_st;

/*创建栈*/
StackInfo_st stack;
stack.topOfStack = TOP_OF_STACK;
```
#### 入栈
入栈操作也很简单，只需要先将topOfStack加1，然后将元素放入数组即可。当然特别要注意检查此时栈是否已满。
topOfStack = -1

||||
|--|--||
||||

将1入栈，此时topOfStack = 0，

|topOfStack|||
|--|--||
|1|||

代码实现：
```c
#define SUCCESS 0
#define FAILURE -1
/*入栈，0表示成，非0表示出错*/
int stack_push(StackInfo_st *s, ElementType value)
{
    if(stack_is_full(s))
        return FAILURE;
    /*先增加topOfStack，再赋值*/
    s->topOfStack++;
    s->stack[s->topOfStack] = value;
    return SUCCESS;
}
```
#### 出栈或访问栈顶元素
与入栈相反，先访问元素，然后将topOfStack减1，但是此时要注意检查栈是否已空。访问栈顶元素可直接使用下标访问，而不用将topOfStack减1。
```c
/*出栈*/
int stack_pop(StackInfo_st *s,ElementType *value)
{
    /*首先判断栈是否为空*/
    if(stack_is_empty(s))
        return FAILURE;
    *value = s->stack[s->topOfStack];
    s->topOfStack--;
    return SUCCESS;
}
/*访问栈顶元素*/
int stack_top(StackInfo_st *s,ElementType *value);
{
    /*首先判断栈是否为空*/
    if(stack_is_empty(s))
        return FAILURE;
    *value = s->stack[s->topOfStack];
    return SUCCESS;
}
```
#### 判断栈是否满
只要判断topOfStack与数组大小-1的大小即可。
```c
/*判断栈是否已满，满返回1，未满返回0*/
int stack_is_full(StackInfo_st *s)
{
    return s->topOfStack == STACK_SIZE - 1;
}
```
#### 判断栈是否为空
只需要判断topOfStack是否小于等于-1即可。
```c
/*判断栈是否为空，空返回1，非空返回0*/
int stack_is_empty(StackInfo_st *s)
{
    return s->topOfStack ==  - 1;
}
```
#### 完整可运行代码
```c
#include<stdio.h>

#define STACK_SIZE 64 /*栈大小*/
#define TOP_OF_STACK -1 /*栈顶位置*/
typedef int ElementType; /*栈元素类型*/

#define SUCCESS 0
#define FAILURE -1

/*定义栈结构*/
typedef struct StackInfo
{
    int topOfStack; /*记录栈顶位置*/
    ElementType stack[STACK_SIZE]; /*栈数组，也可以使用动态数组实现*/
}StackInfo_st;


/*函数声明*/
int stack_push(StackInfo_st *s,ElementType value);
int stack_pop(StackInfo_st *s,ElementType *value);
int stack_top(StackInfo_st *s,ElementType *value);
int stack_is_full(StackInfo_st *s);
int stack_is_empty(StackInfo_st *s);


/*入栈，0表示成，非0表示出错*/
int stack_push(StackInfo_st *s,ElementType value)
{
    if(stack_is_full(s))
        return FAILURE;
    /*先增加topOfStack，再赋值*/
    s->topOfStack++;
    s->stack[s->topOfStack] = value;
    return SUCCESS;
}

/*出栈*/
int stack_pop(StackInfo_st *s,ElementType *value)
{
    /*首先判断栈是否为空*/
    if(stack_is_empty(s))
        return FAILURE;
    *value = s->stack[s->topOfStack];
    s->topOfStack--;
    return SUCCESS;
}

/*访问栈顶元素*/
int stack_top(StackInfo_st *s,ElementType *value)
{
    /*首先判断栈是否为空*/
    if(stack_is_empty(s))
        return FAILURE;
    *value = s->stack[s->topOfStack];
    return SUCCESS;
}

/*判断栈是否已满，满返回1，未满返回0*/
int stack_is_full(StackInfo_st *s)
{
    return s->topOfStack == STACK_SIZE - 1;
}

/*判断栈是否为空，空返回1，非空返回0*/
int stack_is_empty(StackInfo_st *s)
{
    return s->topOfStack ==  - 1;
}
int main(void)
{
    
    /*创建栈*/
    StackInfo_st stack;
    stack.topOfStack = TOP_OF_STACK;
    
    /*如果栈为空，则压入元素1*/
    if(stack_is_empty(&stack))
    {
        printf("push value 1\n");
        stack_push(&stack,1);
    }
    
    /*访问栈顶元素*/
    int topVal;
    stack_top(&stack, &topVal);
    printf("top value %d\n",topVal);
    
    /*出栈*/
    int popVal;
    stack_pop(&stack, &popVal);
    printf("pop value %d\n",popVal);
	int i = 0;
	while(SUCCESS == stack_push(&stack,i))
    {
		i++;
    }
    printf("stack is full,topOfStack is %d\n",stack.topOfStack);
    
    return 0;
}
```
运行结果：
```
push value 1
top value 1
pop value 1
stack is full,topOfStack is 63
```
## 链表实现栈
与数组实现栈不一样的地方是，链式栈可以动态扩容，基本没有长度限制（受限于内存）。另外，它在入栈以及出栈的时候需要申请或者释放内存。
#### 创建栈
创建栈很容易，只需要声明一个头指针即可，它的next指针指向栈顶，初始时为空：
```c
/*定义栈结构*/
typedef struct StackInfo
{
    ElementType value; /*记录栈顶位置*/
    struct StackInfo *next; /*指向栈的下一个元素*/
}StackInfo_st;

/*创建栈，外部释放内存*/
StackInfo_st *createStack(void)
{
	StackInfo_st *stack = malloc(sizeof(StackInfo_st));
    if(NULL == stack)
	{
		printf("malloc failed\n");
		return NULL;
	} 
        /*stack-next为栈顶指针*/
	stack->next = NULL;
	return stack;
}
```

#### 入栈
入栈只需要为新的元素申请内存空间，并将栈顶指针指向新的节点即可。
![入栈操作](https://github.com/yanbinghu/BlogImages/raw/master/articles/%E6%A0%88-C%E8%AF%AD%E8%A8%80%E5%AE%9E%E7%8E%B0/stack_push.png)
```c
/*入栈，0表示成，非0表示出错*/
int stack_push(StackInfo_st *s,ElementType value)
{
	StackInfo_st *temp = malloc(sizeof(StackInfo_st));
	if(NULL == temp)
	{
		printf("malloc failed\n");
		return FAILURE;
	}
    /*将新的节点添加s->next前，使得s->next永远指向栈顶*/
	temp->value = value;
  	temp->next = s->next;
	s->next = temp;
    return SUCCESS;
}
```

#### 出栈或访问栈顶元素
出栈时，将栈顶指针指向下下个节点，返回元素值，并释放栈顶指针下个节点的内存。而访问栈顶元素只需要返回栈顶指针指向节点的元素值即可。
![出栈](https://github.com/yanbinghu/BlogImages/raw/master/articles/%E6%A0%88-C%E8%AF%AD%E8%A8%80%E5%AE%9E%E7%8E%B0/stack_pop.png)
```c
/*出栈*/
int stack_pop(StackInfo_st *s,ElementType *value)
{
    /*首先判断栈是否为空*/
    if(stack_is_empty(s))
        return FAILURE;

    /*找出栈顶元素*/
	*value = s->next->value;
    StackInfo_st *temp = s->next;
    s->next = s->next->next;
	
    /*释放栈顶节点内存*/
    free(temp);
	temp = NULL;
    
    return SUCCESS;
}
/*访问栈顶元素*/
int stack_top(StackInfo_st *s,ElementType *value)
{
    /*首先判断栈是否为空*/
    if(stack_is_empty(s))
        return FAILURE;
    *value = s->next->value;
    return SUCCESS;
}
```

#### 判断栈是否为空
判断栈空也很简单，只需要判断栈顶指针是否为空即可。
```c
/*判断栈是否为空，空返回1，未空返回0*/
int stack_is_empty(StackInfo_st *s)
{
    /*栈顶指针为空，则栈为空*/
    return s->next == NULL;
}
```
## 完整可运行代码
```c
#include<stdio.h>
#include<stdlib.h>
typedef int ElementType; /*栈元素类型*/

#define SUCCESS 0
#define FAILURE -1

/*定义栈结构*/
typedef struct StackInfo
{
    ElementType value; /*记录栈顶位置*/
    struct StackInfo *next; /*指向栈的下一个元素*/
}StackInfo_st;


/*函数声明*/
StackInfo_st *createStack(void);
int stack_push(StackInfo_st *s,ElementType value);
int stack_pop(StackInfo_st *s,ElementType *value);
int stack_top(StackInfo_st *s,ElementType *value);
int stack_is_empty(StackInfo_st *s);

/*创建栈，外部释放内存*/
StackInfo_st *createStack(void)
{
	StackInfo_st *stack = malloc(sizeof(StackInfo_st));
    if(NULL == stack)
	{
		printf("malloc failed\n");
		return NULL;
	} 
	stack->next = NULL;
	return stack;
}
/*入栈，0表示成，非0表示出错*/
int stack_push(StackInfo_st *s,ElementType value)
{
	StackInfo_st *temp = malloc(sizeof(StackInfo_st));
	if(NULL == temp)
	{
		printf("malloc failed\n");
		return FAILURE;
	}
    /*将新的节点添加s->next前，使得s->next永远指向栈顶*/
	temp->value = value;
  	temp->next = s->next;
	s->next = temp;
    return SUCCESS;
}

/*出栈*/
int stack_pop(StackInfo_st *s,ElementType *value)
{
    /*首先判断栈是否为空*/
    if(stack_is_empty(s))
        return FAILURE;

    /*找出栈顶元素*/
	*value = s->next->value;
    StackInfo_st *temp = s->next;
    s->next = s->next->next;
	
    /*释放栈顶节点内存*/
    free(temp);
	temp = NULL;
    
    return SUCCESS;
}
/*访问栈顶元素*/
int stack_top(StackInfo_st *s,ElementType *value)
{
    /*首先判断栈是否为空*/
    if(stack_is_empty(s))
        return FAILURE;
    *value = s->next->value;
    return SUCCESS;
}

/*判断栈是否为空，空返回1，未空返回0*/
int stack_is_empty(StackInfo_st *s)
{
    /*栈顶指针为空，则栈为空*/
    return s->next == NULL;
}

int main(void)
{
    
    /*创建栈*/
    StackInfo_st *stack = createStack();
    
    /*如果栈为空，则压入元素1*/
    if(stack_is_empty(stack))
    {
        printf("push value 1\n");
        stack_push(stack,1);
    }
    
    /*访问栈顶元素*/
    int topVal;
    stack_top(stack, &topVal);
    printf("top value %d\n",topVal);
    
    /*出栈*/
    int popVal;
    stack_pop(stack, &popVal);
    printf("pop value %d\n",popVal);
	int i = 0;
	while(SUCCESS == stack_push(stack,i) && i < 5)
    {
		i++;
    }
    printf("top if stack value is %d\n",stack->next->value);
    /*最后记得将栈内存都释放，可自己尝试实现*/
    return 0;
}
```
运行结果：
```
push value 1
top value 1
pop value 1
top if stack value is 5
```
## 总结
本文介绍了栈的基本操作以及栈的基本实现。后面将会介绍一些栈的具体应用。

## 思考
还记得如何使用查看链表内容吗？参考《[GDB调试指南-变量查看](https://www.yanbinghu.com/2019/03/10/50132.html)》。
