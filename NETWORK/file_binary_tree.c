#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	char word[20];
	struct Node* left;
	struct Node* right;
}Node;

typedef struct BinarySearchTree
{
	struct Node* root;
};
/* root varies depending on Alphabets. */
void insert( BinarySearchTree** root, const char* word )
{
	Node* new_node = NULL;
	
}

int main(int argc, char* argv[])
{
	

}
