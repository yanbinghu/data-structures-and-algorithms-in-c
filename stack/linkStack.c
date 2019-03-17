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
