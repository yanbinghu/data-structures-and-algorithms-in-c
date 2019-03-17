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
