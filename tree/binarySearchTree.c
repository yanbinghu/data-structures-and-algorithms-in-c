#include<stdio.h>
#include<stdlib.h>
#define ElementType int
#define SUCCESS 0
#define FAILURE -1
typedef struct Tree_Node
{
	ElementType value;
	struct Tree_Node *left;
	struct Tree_Node *right;
}TreeNode;

/*将value插入到树中*/
TreeNode *insertTree(ElementType value,TreeNode *tree)
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

/*查找值为value的节点*/
TreeNode *findTree(ElementType value,TreeNode *tree)
{
	if(NULL == tree)
	{
		/*最后一层还没有找到*/
		return NULL;
	}
	/*从左子树查找*/
	if(value < tree->value)
	{
		return findTree(value,tree->left);
	}
	/*从右边子树查找*/
	else if(value > tree->value)
	{
		return findTree(value,tree->right);
	}
    /*找到值*/
	else
		return tree;

}

/*找到一棵树中最小的节点*/
TreeNode *findMin(TreeNode *tree)
{
	if(NULL == tree)
		return NULL;
	else if(NULL == tree->left)
		return tree;
	else
		return findMin(tree->left);
}
TreeNode *deleteTree(ElementType value,TreeNode *tree)
{
    TreeNode *tempNode = NULL;;
	if(NULL == tree)
	{
		printf("not fount \n");
		return NULL;
	}
	/*比当前节点值小，从左子树查找并删除*/
	else if(value < tree->value)
	{
		tree->left = deleteTree(value,tree->left);
	}
	/*比当前节点值大，从右子树查找并删除*/
	else if(value > tree->value)
	{
		tree->right = deleteTree(value,tree->right);
	}
	/*等于当前节点值，并且当前节点有左右子树*/
	else if(NULL != tree->left  && NULL != tree->right)
	{
        /*用右子树的最小值代替该节点，并且递归删除该最小值节点*/
        tempNode = findMin(tree->right);
        tree->value = tempNode->value;
        tree->right = deleteTree(tree->value,tree->right);
	}
    /*要删除的节点只有一个子节点或没有子节点*/
    else
    {
        tempNode = tree; 
        /*要删除节点有右孩子*/
        if(NULL == tree->left)
            tree=tree->right;
        /*要删除节点有左孩子*/
        else if(NULL == tree->right)
            tree = tree->left;
        free(tempNode);
        tempNode = NULL;
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
int main(void)
{
	int a[] = {10,5,19,4,8,13,24};
	TreeNode *tree = NULL;
	for(int i = 0;i < 7;i++)
	{
		tree = insertTree(a[i],tree);
	}
    TreeNode *temp = NULL;
    temp = findTree(13,tree);
    if(NULL != temp)
        printf("find %d\n",temp->value);
    printf("前序遍历结果：");
    preOrder(tree);
    printf("\n");

    printf("中序遍历结果：");
    inOrder(tree);
    printf("\n");

    printf("后序遍历结果：");
    postOrder(tree);
    printf("\n");
    
    deleteTree(13,tree);
    
    inOrder(tree);
    printf("\n");

    deleteTree(19,tree);
    
    inOrder(tree);
    printf("\n");
    return 0;
}
