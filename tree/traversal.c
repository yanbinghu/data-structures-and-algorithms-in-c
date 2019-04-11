#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*定义树节点*/
typedef struct Tree_Node
{
    int value;   //节点值
    struct Tree_Node *left; //左节点
    struct Tree_Node *right; //右节点
}TreeNode;
typedef TreeNode *ElementType;
/*为测试，将容量值定为较小值5*/
#define MAX_SIZE 64
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
/*判断队列是否为空*/
int queue_is_empty(QueueInfo *queue)
{
    if((queue->rear + 1) % MAX_SIZE == queue->front)
    {
        //printf("queue is empty\n");
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
   // printf("get  value from front %d  is %p\n",queue->front,*value);
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
   // printf("insert %d  to %d\n",value,queue->rear);
    return SUCCESS;
}
void init_queue(QueueInfo *queue)
{
    memset(queue,0,sizeof(QueueInfo));
    queue->front = 1;
    queue->rear = 0;
}
/*将value插入到树中*/
TreeNode *insertTree(int value,TreeNode *tree)
{
    if(NULL == tree)
	{
        /*创建一个节点*/
        tree = malloc(sizeof(TreeNode));
        if(NULL == tree)
        {
            printf("malloc failed\n"); 
            return NULL;
        }
        else
        {
            /*将节点信息存储在此叶子节点中*/
            printf("insert %d to tree\n",value);
            tree->value = value;
            tree->left = NULL;
            tree->right = NULL;
		
        }
	}
	/*比当前节点小，则插入到左子树*/
	else if(value < tree->value)
	{
		tree->left = insertTree(value,tree->left);
	}
	/*比当前节点大，则插入到右子树*/
	else if(value > tree->value)
	{	
		tree->right = insertTree(value,tree->right);
	}
	return tree;
}
/*前序遍历*/
void preOrder(TreeNode *tree)
{
    if(NULL == tree)
        return;
    printf("%d ",tree->value);
    preOrder(tree->left);
    preOrder(tree->right);
}
/*中序遍历*/
void inOrder(TreeNode *tree)
{
    if(NULL == tree)
        return; 
    inOrder(tree->left);
    printf("%d ",tree->value);
    inOrder(tree->right);
}

/*后序遍历*/
void postOrder(TreeNode *tree)
{
    if(NULL == tree)
        return;
    postOrder(tree->left);
    postOrder(tree->right);
    printf("%d ",tree->value);
}

/*层次遍历*/
void PrintNodeByLevel(TreeNode* root) 
{
    if(NULL == root)
         return;
    /*初始化队列*/
    QueueInfo queue;
    init_queue(&queue);
    TreeNode *node = NULL;
    
    /*头节点入队*/
    queue_insert(&queue,root);
    do 
    {
        queue_delete(&queue,&node);
        if (node) 
        {
            printf("%d ",node->value);
            if (node->left)
                queue_insert(&queue,node->left);
            if (node->right)
                queue_insert(&queue,node->right);
        }
    } while (!queue_is_empty(&queue));
}

/**
 * leetcode 94题
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* inorderTraversal(TreeNode* root, int* returnSize) {
    if(NULL == root || NULL == returnSize)
    {
        *returnSize = 0;
        return NULL;
    }
    int numleft = 0;
    int numRight = 0;
    
    /*递归计算左右子树，并将左右子树的返回结果存储在最终结果里*/
    int *left=inorderTraversal(root->left,&numleft);
    int *right=inorderTraversal(root->right,&numRight);
    int *array = malloc(sizeof(int)*(numleft+numRight+1));
    if(NULL == array)
        return NULL;
    if(left)
        memcpy(array,left,sizeof(int)*numleft);
    
    array[numleft] = root->value;
    
    if(right)
        memcpy(array+numleft+1,right,sizeof(int)*numRight);
    
    *returnSize = numleft+numRight+1;
    free(left);
    left = NULL;
    free(right);
    right = NULL;
    return array;
    
}

int main(void)
{
    int a[] = {10,5,19,4,8,13,24};
	TreeNode *tree = NULL;
	for(int i = 0;i < 7;i++)
	{
		tree = insertTree(a[i],tree);
	}
    printf("\n层次遍历：");
	PrintNodeByLevel(tree);

    printf("\n前序遍历：");
    preOrder(tree);
  
    printf("\n后序遍历：");
    postOrder(tree);
 
    printf("\n中序遍历：");
    inOrder(tree);
    printf("\n中序遍历：");
    int size = 0;
    int *ret = inorderTraversal(tree,&size);
    
    int i = 0;
    while(i < size)
    {
        printf("%d ",ret[i]);
        i++;
    }
    printf("\n");
	return 0;
}
