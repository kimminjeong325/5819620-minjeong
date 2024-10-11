#include<stdio.h>
#include<stdlib.h>

typedef struct tree_node
{
	int data;
	struct tree_node* right, * left;
}TreeNode;

typedef struct thread_node {

	int data;
	struct thread_node* left;
	struct thread_node* right;
	int leftThread;
	int rightThread;

}ThreadNode;

TreeNode* new_node(int key)
{
	TreeNode* temp = malloc(sizeof(TreeNode));
	if (temp == NULL) {
		printf("메모리 할당 실패!\n");
		exit(1);
	}
	temp->data = key;
	temp->right = temp->left = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* root, int key) {
	if (root == NULL)
		return new_node(key);
	if (root->data == key)return root;
	else if (root->data > key)root->left = insert_node(root->left, key);
	else root->right = insert_node(root->right, key);

	return root;
}

TreeNode* GenerateBinaryTree(int inputData[], int size)
{
	TreeNode* root = NULL;
	for (int i = 0; i < size; i++)
	{
		root = insert_node(root, inputData[i]);
	}
	return root;
}

void BinaryTreeInOrder(TreeNode* root)
{
	if (root != NULL) {
		BinaryTreeInOrder(root->left);
		printf("%d ", root->data);
		BinaryTreeInOrder(root->right);
	}
}

ThreadNode* new_thread_node(int key) {
	ThreadNode* temp = (ThreadNode*)malloc(sizeof(ThreadNode));
	if (temp == NULL) {
		printf("메모리 할당 실패\n");
		exit(1);
	}
	temp->data = key;
	temp->left = temp->right = NULL;
	temp->leftThread = temp->rightThread = 1;
	return temp;
}

ThreadNode* insert_threaded(ThreadNode* root, int key) {
	ThreadNode* parent = NULL;
	ThreadNode* current = root;

	while (current != NULL) {
		if (key == current->data) {
			return root;
		}

		parent = current;

		if (key < current->data) {
			if (current->leftThread == 0)
				current = current->left;
			else
				break;
		}
		else {
			if (current->rightThread == 0)
				current = current->right;
			else
				break;
		}
	}

	ThreadNode* newNode = new_thread_node(key);

	if (parent == NULL) {

		return newNode;
	}
	else if (key < parent->data) {

		newNode->left = parent->left;
		newNode->right = parent;
		parent->left = newNode;
		parent->leftThread = 0;
	}
	else {
		newNode->right = parent->right;
		newNode->left = parent;
		parent->right = newNode;
		parent->rightThread = 0;
	}

	return root;
}

ThreadNode* GenerateThreadTree(int inputData[], int size) {
	ThreadNode* root = NULL;
	for (int i = 0; i < size; i++) {
		root = insert_threaded(root, inputData[i]);
	}
	return root;
}

void ThreadTreeInOrder(ThreadNode* root) {
	if (root == NULL)
		return;

	ThreadNode* current = root;
	while (current->leftThread == 0)
		current = current->left;

	while (current != NULL) {
		printf("%d ", current->data);


		if (current->rightThread == 1)
			current = current->right;
		else {

			current = current->right;
			while (current != NULL && current->leftThread == 0)
				current = current->left;
		}
	}
}
int main()
{
	int inputData[] = { 4,1,9,13,15,3,6,14,7,10,12,2,5,8,11 };
	int size = sizeof(inputData) / sizeof(inputData[0]);

	TreeNode* root = GenerateBinaryTree(inputData, size);
	printf("Binary tree inorder: ");
	BinaryTreeInOrder(root);
	printf("\n");

	ThreadNode* troot = GenerateThreadTree(inputData, size);
	printf("Thread tree inorder: ");
	ThreadTreeInOrder(troot);

	free(root);
	free(troot);
	return 0;
}
