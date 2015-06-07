#pragma once

enum Color{
	RED,
	BLACK,
};

struct Node{
	int key;
	Color color;
	Node* parent;
	Node* leftChild;
	Node* rightChild;

	Node(int _key){
		key = _key;
	}
};

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	void Insert(Node* newNode);
	void Delete(Node* delNode);
	Node* Search(int key);
	Node* Minimum();
	int CheckBlackHeight();

protected:
	void InsertFixup(Node* fixupNode);
	void LeftRotate(Node* fixupNode);
	void RightRotate(Node* fixupNode);
	void DeleteFixup(Node* fixupNode);
	void TransPlant(Node* oldNode, Node* plantNode);

	Node* Minimum(Node* rootNode);
	int CheckBlackHeight(Node* checnNode);

protected:
	Node* root;
	Node* nil;
};

