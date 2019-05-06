#include <stdio.h>
#include <stdlib.h>

#define MAX_STR 10
#define SOURCE_FILE "source.txt" //最原始文件，需要保留
#define SRC_FILE "src.txt"       //需要分类的文件
#define BIT_1_FILE "bit1.txt"
#define BIT_0_FILE "bit0.txt"
#define INT_BIT_NUM  32
/*
FILE *src   源数据文件指针
FILE *fpBit1 存储要处理的比特位为1的数据
FILE *fpBit0 存储要处理的比特位为0的数据
int bit     要处理的比特位
返回值
0：选择比特位为0的数据继续处理
1：选择比特位为1的数据继续处理
-1：出错
*/
int splitByBit(FILE *src,FILE *fpBit1,FILE *fpBit0,int bit,int *nums)
{
    /*入参检查*/
    if(NULL == src || NULL == fpBit1 || NULL == fpBit0 || NULL == nums)
    {
        printf("input para is NULL");
        return -1;
    }
    /*bit位检查*/
    if(bit < 0 || bit > INT_BIT_NUM )
    {
        printf("the bit is wrong");
        return -1;
    }
    char string[MAX_STR] = {0};
    int mask = 1<< bit;
    int bit0num = 0;
    int bit1num = 0;
    int num = 0;
    //printf("mask is %x\n",mask);
    /*循环读取源数据*/
    while(fgets(string, MAX_STR, src ) != NULL)
    {
        num = atoi(string);
        //printf("%d&%d %d\n",num,mask, num&mask);
        /*根据比特位的值，将数据写到不同的位置，注意优先级问题*/
        if(0 == (num&mask))
        {
            //printf("bit 0 %d\n",num);
            fprintf(fpBit0, "%d\n", num);
            bit0num++;
        }
        else
        {
            //printf("bit 1 %d\n",num);
            fprintf(fpBit1, "%d\n", num);
            bit1num++;
        }
    }
    //printf("bit0num:%d,bit1num:%d\n",bit0num,bit1num);
    if(bit0num > bit1num)
    {
        /*说明比特位为1的数少*/
        *nums = bit1num;
        return 1;
    }
    else
    {
        *nums = bit0num;
        return 0;
    }
}
/***
 *关闭所有文件描述符
 *
 * **/
void closeAllFile(FILE **src,FILE **bit0,FILE **bit1)
{
    if(NULL != src && NULL != *src)
    {
        fclose(*src);
        *src = NULL;
    }        
    if(NULL != bit1 && NULL != *bit1)
    {
        fclose(*bit1);
        *bit1 = NULL;
    }        
    if(NULL != bit0 && NULL != *bit0)
    {
        fclose(*bit0);
        *bit0 = NULL;
    }        
}
int findNum(int *findNum)
{
    int loop = 0;
    /*打开最原始文件*/
    FILE *src = fopen(SOURCE_FILE,"r");
    if(NULL == src)
    {
        printf("failed to open %s",SOURCE_FILE);
        return -1;
    }
    FILE *bit1 = NULL;
    FILE *bit0 = NULL;
       int num = 0;
    int bitNums = 0; //得到比特位的数字数量
    int findBit = 0; //当前得到的比特位
    for(loop = 0; loop < INT_BIT_NUM;loop++)
    {
        /*第一次循环不会打开，保留源文件*/
        if(NULL == src)
        {
            src = fopen(SRC_FILE,"r");
        }
        if(NULL == src)
        {
            return -1;
        }

        /**打开失败时，注意关闭所有打开的文件描述符**/
        bit1 = fopen(BIT_1_FILE,"w+");
        if(NULL == bit1)
        {
            closeAllFile(&src,&bit1,&bit0);
            printf("failed to open %s",BIT_1_FILE);
            return -1;
        }
        bit0 = fopen(BIT_0_FILE,"w+");
        if(NULL == bit0)
        {
            closeAllFile(&src,&bit1,&bit0);
            printf("failed to open %s",BIT_0_FILE);
            return -1;
        }
        findBit = splitByBit(src,bit1,bit0,loop,&bitNums);
        if(-1 == findBit)
        {
            printf("process error\n");
            closeAllFile(&src,&bit1,&bit0);
            return -1;
        }
        closeAllFile(&src,&bit1,&bit0);
        //printf("find bit %d\n",findBit);
        /*将某比特位数量少的文件重命名为新的src.txt，以便进行下一次处理*/
        if(1 == findBit)
        {
            rename(BIT_1_FILE,SRC_FILE);
            num |=  (1 << loop);
            printf("mv bit1 file to src file\n");
        }
        else
        {
            printf("mv bit0 file to src file\n");
            rename(BIT_0_FILE,SRC_FILE);
        }
        
        /*如果某个文件数量为0，则没有必要继续寻找下去*/
        if(0 == bitNums)
        {
            printf("no need to continue\n");
            break;
        }
    }
    *findNum = num;
    return 0;
}
int main(void)
{
    int num = 0;
    findNum(&num);
    printf("final num is %d or 0x%x\n",num,num);
    return 0;
}
