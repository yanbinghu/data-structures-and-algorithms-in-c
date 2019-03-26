---
title: 如何用栈实现表达式求值
date: 2019-3-24 16:00:00
comments: true
categories: 数据结构与算法
tags: [C,数据结构与算法,栈]

---
## 前言
假如要你实现一个可以识别表达式的简易计算器，你会怎么实现？例如用户输入：
```
3 + 5 * (2 - 4)
```
可以直接得出计算结果：-7。对于人类来说，我们很容易计算出来，因为我们从左往右看，看到后面括号时，知道括号内的计算优先级最高，因此可以先计算括号内的，然后反过来计算乘法，最后计算加法，得到最终结果。
<!--more-->
## 后缀表达式
而对于计算机来说，实际也可以采用类似的顺序，先记录存储3为a，然后存储5为b，计算2-4结果存入c，再然后计算b*c存储d，最终计算a+d得到最终结果。而这种计算过程的操作顺序可描述如下(把操作符号放在操作数后面)：
```
3 5 2 4 - * +
```
这种记法叫做后缀或逆波兰记法（而我们平常见到的叫中缀记法），它的特点是**不需要用括号就能表示出整个表达式哪部分运算先进行，也就是说不需要考虑优先级，这非常符合计算机的处理方式。**这种记法很容易使用我们前面介绍的栈来求值，但是前提是需要将中缀表达式先转换为后缀表达式。对于这种转换，我们也可以使用前面介绍的[栈-C语言实现](https://www.yanbinghu.com/2019/03/16/31765.html)或者将要介绍的树来完成，因篇幅有限，本文不准备介绍。

接下来将会介绍如何利用中缀表达式进行求值。
## 利用栈实现中缀表达式求值
前面也说到，所谓中缀表达式，就是我们能看到的正常表达式，中缀表达式求值，也就是直接对输入的表达式进行求值。为简单起见，我们这里假设**只涉及加减乘除和小括号，并且操作数都是正整数，不涉及更加复杂的数据或运算。**

计算思路：
+ 使用两个栈，stack0用于存储操作数，stack1用于存储操作符
+ 从左往右扫描，遇到操作数入栈stack0
+ 遇到操作符时，如果优先级低于或等于栈顶操作符优先级，则从stack1弹出两个元素进行计算，并压入stack0，继续与栈顶操作符的比较优先级
+ 如果遇到操作符高于栈顶操作符优先级，则直接入栈stack1
+ 遇到左括号，直接入栈stack1，遇到右括号，则直接出栈并计算，直到遇到左括号

上面的思路可能看起来不是很明确，我们举一个简单的例子，假如要对下面的表达式求值：
```
6 * (2 + 3 )* 8 + 5
```
我们从左往右开始扫描。首先遇到操作数‘6’，和操作符‘*’，分别入栈
stack0:

|栈顶|||||
|--|--|--|--|--|
|6|||||

stack1:

|栈顶|||||
|--|--|--|--|--|
|*|||||

继续往后扫描，遇到‘(’直接入栈，‘2’入栈，栈顶是左括号，’+‘入栈，‘3’入栈
stack0:

|||栈顶|||
|--|--|--|--|--|
|6|2|3|||

stack1:

|||栈顶|||
|--|--|--|--|--|
|*|(|+|||

继续往后扫描，遇到右括号，它与栈顶操作符‘+’相比，优先级要高，因此，将‘+’出栈，弹出两个操作数‘3’,‘2’，计算结果得到‘5’，并入栈：

stack0:

||栈顶||||
|--|--|--|--|--|
|6|5||||

stack1:

||栈顶||||
|--|--|--|--|--|
|*|(||||

继续出栈，直到遇到左括号
stack0:

||栈顶||||
|--|--|--|--|--|
|6|5||||

stack1:

|栈顶|||||
|--|--|--|--|--|
|*|||||

继续往后扫描，遇到操作符‘*’,优先级与栈顶‘*’优先级相同，因此弹出操作数并计算得到30入栈，最后‘*’入栈

stack0:

|栈顶|||||
|--|--|--|--|--|
|30|||||

stack1:

|栈顶|||||
|--|--|--|--|--|
|*|||||

继续扫描，‘8’入栈，操作符‘+’优先级小于‘*’，弹出操作数计算得到结果‘240’，并将其入栈，最后‘+’也入栈

stack0:

|栈顶|||||
|--|--|--|--|--|
|240|||||

stack1:

|栈顶|||||
|--|--|--|--|--|
|+|||||

最后‘5’入栈，发现操作符栈不为空，弹出操作符‘+’和两个操作数，并进行计算，得到‘245’，入栈，得到最终结果。

|栈顶|||||
|--|--|--|--|--|
|245|||||

stack1:

||||||
|--|--|--|--|--|
||||||

## 代码实现
```c
#include<stdio.h>
#include<ctype.h>
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
	{
		printf("stack is empty");
		    return FAILURE;
	}
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
    return s->topOfStack == - 1;
}

/*用于记录符号的优先级，这里浪费了一些内存，可以优化*/
static char priority[128] = {0};
void priorityInit()
{
    /*初始化优先级，值越小，优先级越高*/
    priority['+'] = 4;
    priority['-'] = 4;
    priority['*'] = 3;
    priority['/'] = 3;
    priority['('] = 1;
    priority[')'] = 1;


}
/*比较运算符的优先级,op1优先级大于op2时，返回大于0的值*/
int priorityCompare(char op1,char op2)
{
    return priority[op2] - priority[op1];
}
/*出栈操作符和操作数进行计算*/
int calcOp(StackInfo_st *nums,StackInfo_st *ops,int nowOp)
{
    int a ,b,op;
    stack_pop(ops,&op);
    printf("op %c is <= %c\n",nowOp,op);
    printf("get op from stack %c\n",op);
    if(SUCCESS != stack_pop(nums,&b))
    {
        printf("pop failed\n");
        return -1;
    }
    if(SUCCESS != stack_pop(nums,&a))
    {
        printf("pop failed\n");
        return 0;
    }
    printf("get b from stack %d\n",b);

    printf("get a from stack %d\n",a);
    switch(op)
    {
        case '+':
        {
            printf("push %d into stack\n",a+b);
            stack_push(nums,a+b);
            break;
        }
        case '-':
        {
            stack_push(nums,a-b);
            break;
        }
        case '*':
        {
            printf("push %d into stack\n",a*b);
            stack_push(nums,a*b);
            break;
        }
        case '/':
        {
            printf("push %d into stack\n",a/b);
            stack_push(nums,a/b);
            break;
        }
    }
    return 1;
}
int calc(const char* exp,int *result)
{
    if(NULL == exp || NULL == result)
        return FAILURE;
    /*创建栈，用于保存数*/
    StackInfo_st nums;
    nums.topOfStack = TOP_OF_STACK;
    
    /*用于保存操作符*/
    StackInfo_st ops;
    ops.topOfStack = TOP_OF_STACK;
    int index = 0;
    /*用于标记，判断上一个是否为数字*/
    int flag = 0;
    int temp = 0;
    int op ;
    while(0 != *exp)
    {   
        /*如果是数字*/
        if(isdigit(*exp))
        {
        	printf("char is %c\n",*exp);
         	/*如果上一个还是数字，则取出栈顶数据*/
        	if(1 == flag)
       		{
            
            	stack_pop(&nums,&temp);
            	printf("pop from stack num %d\n",temp);
       		 }
        	else
        		temp = 0;
        	flag = 1;
        	temp = 10 * temp + *exp-'0';
        	printf("push %d to stack\n",temp);
        	stack_push(&nums,temp);
        }
        /*如果是操作符*/
        else if('/' == *exp || '*' == *exp || '+' == *exp || '-' == *exp)
        {
            flag = 0;
            printf("OP is %c\n",*exp);
            while((ops.topOfStack > TOP_OF_STACK )&&(SUCCESS == stack_top(&ops,&op))&&'(' != op && ')'!=op&&(priorityCompare(*exp,op) < 0))
            {
                calcOp(&nums, &ops,*exp);
            }
            printf("push %c to stack ops\n",*exp);
            stack_push(&ops,*exp);
        }
        /*左括号直接入栈*/
        else if('(' == *exp )
        {
            printf("push ( to stack ops\n");
            flag = 0;
            stack_push(&ops,*exp);
        }
        /*右括号，计算*/
        else if(')' ==*exp )
        {
            printf("deal with  ) in ops\n");
            flag = 0;
            /*右括号时，不断计算，直到遇见左括号*/
            while(SUCCESS == stack_top(&ops,&op) && '(' != op)
            {
                calcOp(&nums, &ops,*exp);
            }
            stack_pop(&ops,&op);
        }
        else
        {
            flag=0;
        }
        printf("flag is %d\n\n",flag);
        exp++;
    }
    /*计算剩余两个栈的内容*/
    while((!stack_is_empty(&ops)) && (!stack_is_empty(&nums)))
    {
        if(!calcOp(&nums, &ops,0))
        printf("exp is error\n");
    }
    stack_pop(&nums,&temp);
    /*如果栈中还有内容，说明表达式错误*/
    if((!stack_is_empty(&ops)) || (!stack_is_empty(&nums)))
    	printf("\n\nexp is ok\n\n");
    
    if(SUCCESS == stack_pop(&nums,&temp))
        printf("result is %d\n",temp);
	*result = temp;
    return 0;
}
int main(int argc ,char *argv[])
{

    int result;
    priorityInit();
    char exp[] = "6 * (2 + 3 * 3)* 8 + 5";
    calc(exp,&result);
    printf("result is %d\n",result);
    return 0;
}
```

## 总结
本文介绍了利用栈对中缀表达式进行求值，而代码实现还有很多不足之处，例如对表达式的正确性校验不足，只能处理正整数等等，欢迎在此基础上完善补充。尽管如此，整个过程对使用栈进行中缀表达式的求值做了一个较为完整的介绍，因此具有一定的参考性。

