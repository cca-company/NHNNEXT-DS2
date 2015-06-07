#include "stdafx.h"
#include "RedBlackTree.h"


RedBlackTree::RedBlackTree()
{
	nil = new Node(0);
	nil->color = BLACK;
	root = nil;
}


RedBlackTree::~RedBlackTree()
{
	while (root != nil)
	{
		Delete(root);
	}
}


/************************************************************
					인터페이스 함수
	* insert / delete
	* validity check
	* search
	* minimum / maximum
************************************************************/

void RedBlackTree::Insert(Node* newNode)
{
	if (newNode == nullptr) return;
	Node* parentNode = nil;
	Node* curNode = root;

	// check position for inserting new node
	while (curNode != nil)
	{
		parentNode = curNode;
		if (newNode->key < curNode->key)
		{
			curNode = curNode->leftChild;
		}
		else
		{
			curNode = curNode->rightChild;
		}
	}

	// initialize new node
	newNode->parent = parentNode;
	newNode->leftChild = nil;
	newNode->rightChild = nil;
	newNode->color = RED;

	// update parentNode or root
	if (parentNode == nil)
		root = newNode;
	else if (newNode->key < parentNode->key)
		parentNode->leftChild = newNode;
	else
		parentNode->rightChild = newNode;

	InsertFixup(newNode);
}


void RedBlackTree::Delete(Node* delNode)
{
	if (delNode == nullptr) return;
	Node* fixupNode;
	Node* successor;
	Node* leftChild = delNode->leftChild;
	Node* rightChild = delNode->rightChild;
	Color erasedColor = delNode->color;

	// child가 1개 이하인 경우
	if (leftChild == nil) 
	{
		fixupNode = rightChild;
		TransPlant(delNode, fixupNode);
	}
	else if (rightChild == nil)
	{
		fixupNode = leftChild;
		TransPlant(delNode, fixupNode);
	}
	else // child가 2개인 경우
	{
		successor = Minimum(rightChild);
		erasedColor = successor->color;
		fixupNode = successor->rightChild;

		if (successor->parent == delNode)	// 교체 노드가 삭제 노드의 자식 노드인 경우
		{
			fixupNode->parent = successor;
		}
		else
		{
			TransPlant(successor, fixupNode);
			successor->rightChild = rightChild;
			successor->rightChild->parent = successor;
		}
		TransPlant(delNode, successor);
		successor->leftChild = leftChild;
		successor->leftChild->parent = successor;
		successor->color = delNode->color;
	}

	if (erasedColor == BLACK)
	{
		DeleteFixup(fixupNode);
	}

	free(delNode);
}


Node* RedBlackTree::Search(int key)
{
	Node* currentNode = root;
	while (currentNode != nil && currentNode->key != key)
	{
		if (currentNode->key > key)
			currentNode = currentNode->leftChild;
		else
			currentNode = currentNode->rightChild;
	}

	if (currentNode == nil) 
		return nullptr;
	else 
		return currentNode;
}

int RedBlackTree::CheckBlackHeight()
{
	return CheckBlackHeight(root);
}

int RedBlackTree::CheckBlackHeight(Node* checkNode)
{
	if (checkNode == nil)
	{
		return 1;
	}

	int leftHeight,rightHeight;
	leftHeight = CheckBlackHeight(checkNode->leftChild);
	rightHeight = CheckBlackHeight(checkNode->rightChild);

	if (leftHeight == rightHeight && leftHeight != 0)
	{
		return (checkNode->color == BLACK) ? leftHeight+1 : leftHeight;
	}
	else
	{
		return 0;
	}
}


Node* RedBlackTree::Minimum()
{
	return Minimum(root);
}

Node* RedBlackTree::Minimum(Node* rootNode)
{
	Node* currentNode = rootNode;
	while (currentNode->leftChild != nil)
	{
		currentNode = currentNode->leftChild;
	}
	return currentNode;
}


/************************************************************
					내부 사용 함수(protected)
	* insert작업에 사용되는 함수(insertFixup)
	* delete작업에 사용되는 함수(deleteFixup,transplant)
	* 회전 함수(left/right rotate)
************************************************************/

void RedBlackTree::InsertFixup(Node* fixupNode)
{
	while (fixupNode->parent->color == RED)	// parent = child = RED (violation!)
	{
		Node* parentNode = fixupNode->parent;
		Node* grandParentNode = parentNode->parent;
		Node* uncleNode = nullptr;

		if (parentNode == grandParentNode->leftChild) // parentNode = leftChild && uncleNode = rightChild
		{
			uncleNode = grandParentNode->rightChild;
			if (uncleNode->color == RED) // case1 : parent = child = uncle = RED
			{
				parentNode->color = BLACK;
				uncleNode->color = BLACK;
				grandParentNode->color = RED;
				fixupNode = grandParentNode;
			}
			else
			{
				if (fixupNode == parentNode->rightChild) // case3 : uncle = BLACK && leftRotate
				{
					fixupNode = parentNode;
					LeftRotate(fixupNode);
				}
				// case2 : 
				fixupNode->parent->color = BLACK;
				fixupNode->parent->parent->color = RED;
				RightRotate(fixupNode->parent->parent);
			}
		}
		else // parentNode = rightChild && uncleNode = leftChild
		{
			uncleNode = grandParentNode->leftChild;

			if (uncleNode->color == RED) // case1
			{
				parentNode->color = BLACK;
				uncleNode->color = BLACK;
				grandParentNode->color = RED;
				fixupNode = grandParentNode;
			}
			else
			{
				if (fixupNode == parentNode->leftChild) // case3
				{
					fixupNode = parentNode;
					RightRotate(fixupNode);
				}
				// case2
				fixupNode->parent->color = BLACK;
				fixupNode->parent->parent->color = RED;
				LeftRotate(fixupNode->parent->parent);
			}
		}
	}

	root->color = BLACK;
}


void RedBlackTree::DeleteFixup(Node* fixupNode)
{
	while (fixupNode != root && fixupNode->color == BLACK)
	{
		Node* parentNode = fixupNode->parent;
		Node* siblingNode;

		if (fixupNode == parentNode->leftChild)
		{
			siblingNode = parentNode->rightChild;

			if (siblingNode->color == RED) // case1 : sibling = red -> sibling = black으로 변경
			{
				siblingNode->color = BLACK;
				parentNode->color = RED;
				LeftRotate(parentNode);
				siblingNode = parentNode->rightChild;
			}

			if (siblingNode->leftChild->color == BLACK && siblingNode->rightChild->color == BLACK)
			{ // case2 : sibling = black, 자식 노드 전부 black -> sibling의 black height 감소
				siblingNode->color = RED;
				fixupNode = parentNode;
			}
			else
			{
				if (siblingNode->rightChild->color == BLACK) // case3 : right child가 black인 경우 -> case4로 변경
				{
					siblingNode->leftChild->color = BLACK;
					siblingNode->color = RED;
					RightRotate(siblingNode);
					siblingNode = parentNode->rightChild;
				}

				// case4 : right child가 red인 경우 -> fixupNode경로의 black height 증가 -> delete완료
				siblingNode->color = parentNode->color;
				parentNode->color = BLACK;
				siblingNode->rightChild->color = BLACK;
				LeftRotate(parentNode);
				fixupNode = root;
			}
		}
		else // 좌우반전
		{
			siblingNode = parentNode->leftChild;

			if (siblingNode->color == RED) // case1
			{
				siblingNode->color = BLACK;
				parentNode->color = RED;
				RightRotate(parentNode);
				siblingNode = parentNode->leftChild;
			}

			if (siblingNode->rightChild->color == BLACK && siblingNode->leftChild->color == BLACK)
			{ // case2
				siblingNode->color = RED;
				fixupNode = parentNode;
			}
			else
			{
				if (siblingNode->leftChild->color == BLACK) // case3
				{
					siblingNode->rightChild->color = BLACK;
					siblingNode->color = RED;
					LeftRotate(siblingNode);
					siblingNode = parentNode->leftChild;
				}

				// case4
				siblingNode->color = parentNode->color;
				parentNode->color = BLACK;
				siblingNode->leftChild->color = BLACK;
				RightRotate(parentNode);
				fixupNode = root;
			}

		}
	}
	fixupNode->color = BLACK;
}


void RedBlackTree::TransPlant(Node* oldNode, Node* plantNode)
{
	if (oldNode->parent == nil)
		root = plantNode;
	else if (oldNode == oldNode->parent->leftChild)
		oldNode->parent->leftChild = plantNode;
	else
		oldNode->parent->rightChild = plantNode;
	plantNode->parent = oldNode->parent;
}



void RedBlackTree::LeftRotate(Node* fixupNode)
{
	Node* rightChild = fixupNode->rightChild;
	Node* parentNode = fixupNode->parent;

	if (fixupNode == parentNode->leftChild)
		parentNode->leftChild = rightChild;
	else
		parentNode->rightChild = rightChild;

	fixupNode->rightChild = rightChild->leftChild;
	fixupNode->parent = rightChild;
	rightChild->parent = parentNode;
	rightChild->leftChild = fixupNode;
	if (fixupNode == root) root = rightChild;
}

void RedBlackTree::RightRotate(Node* fixupNode)
{
	Node* leftChild = fixupNode->leftChild;
	Node* parentNode = fixupNode->parent;

	if (fixupNode == parentNode->leftChild)
		parentNode->leftChild = leftChild;
	else
		parentNode->rightChild = leftChild;

	fixupNode->leftChild = leftChild->rightChild;
	fixupNode->parent = leftChild;
	leftChild->parent = parentNode;
	leftChild->rightChild = fixupNode;
	if (fixupNode == root) root = leftChild;
}