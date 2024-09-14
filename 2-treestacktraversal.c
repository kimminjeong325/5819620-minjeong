#include<stdio.h>
#include<stdlib.h>

#define STACK_SIZE 100
typedef struct TreeNode
{
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;


typedef struct
{
    TreeNode* data[STACK_SIZE];
    int top;
}StackType;

void Init(StackType* s)
{
    s->top = -1;
}


int IsEmpty(StackType* s)
{
    return (s->top == -1);
}


int IsFull(StackType* s)
{
    return (s->top >= STACK_SIZE - 1);
}


void Push(StackType* s, TreeNode* p)
{
    if (IsFull(s))
    {
        printf("the stack is full\n");
        exit(1);
    }
    else
    {
        s->data[++(s->top)] = p;
        printf("push(%d)", p->data);
    }
}


TreeNode* Pop(StackType* s)
{
    if (IsEmpty(s))
    {
        printf("the stack is empty\n");
        exit(1);
    }
    else
    {
        TreeNode* node = s->data[(s->top)--];
        if (node == NULL)
        {
            printf("Error: Popped a NULL node\n");
            exit(1);
        }
        printf("pop(%d)", node->data);
        return node;
    }
}

TreeNode* Peek(StackType* s)
{
    if (IsEmpty(s))
    {
        printf("Stack is empty\n");
        exit(1);
    }
    return s->data[s->top];
}

void PlaceNode(TreeNode* node, int direction, int data)
{
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == 0)
    {
        node->left = newNode;
    }
    else if (direction == 1)
    {
        node->right = newNode;
    }
}

void GenerateLinkTree(TreeNode* root)
{
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);

    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);

    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);

    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);

    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);

    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);

    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}


void visit(TreeNode* node)
{
    printf("visit(%d)\n", node->data);
}

void LinkPreOrder(TreeNode* root)
{
    StackType stack;
    Init(&stack);
    TreeNode* current = root;

    if (current != NULL)
    {
        Push(&stack, current);
    }

    while (!IsEmpty(&stack))
    {
        current = Pop(&stack);
        visit(current);

        if (current->right != NULL)
        {
            Push(&stack, current->right);
        }
        if (current->left != NULL)
        {
            Push(&stack, current->left);
        }
    }
    printf("\n");
}
void LinkInOrder(TreeNode* root)
{
    StackType stack;
    Init(&stack);
    TreeNode* current = root;

    while (current != NULL || !IsEmpty(&stack))
    {

        while (current != NULL)
        {
            Push(&stack, current);
            current = current->left;
        }


        current = Pop(&stack);
        if (current == NULL)
        {
            printf("Error: Current node is NULL during visit\n");
            exit(1);
        }
        visit(current);


        current = current->right;
    }
    printf("\n");
}

void LinkPostOrder(TreeNode* root)
{
    if (root == NULL)
        return;

    StackType stack;
    Init(&stack);

    TreeNode* lastVisited = NULL;
    TreeNode* current = root;

    while (current != NULL || !IsEmpty(&stack))
    {
     
        while (current != NULL)
        {
            Push(&stack, current);
            current = current->left;
        }

       
        TreeNode* top = Peek(&stack);  
        if (top->right != NULL && top->right != lastVisited)
        {
           
            current = top->right;
        }
        else
        {
            
            top = Pop(&stack);  
            visit(top);
            lastVisited = top;
        }
    }
    printf("\n");
}


void LinkOrders(TreeNode* root)
{
    LinkPreOrder(root);
    LinkInOrder(root);
    LinkPostOrder(root);
}
int main()
{

    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));

    root->data = 1;
    root->left = NULL;
    root->right = NULL;


    GenerateLinkTree(root);
    LinkOrders(root);
    return 0;
}
