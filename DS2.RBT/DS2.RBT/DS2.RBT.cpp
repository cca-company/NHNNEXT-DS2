// DS2.RBT.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "RedBlackTree.h"

RedBlackTree* RBT = new RedBlackTree();
int testArr[10] = { 8, 2, 5, 10, 9, 1, 7, 6, 3, 4 };

void TestRBTInsert()
{
	for (int i = 0; i < 10; ++i)
	{
		RBT->Insert(new Node(testArr[i]));
		printf("insert : %d / black height : %d \n", testArr[i], RBT->CheckBlackHeight());
	}
}
void TestRBTDelete()
{
	for (int i = 0; i < 10; ++i)
	{
		Node* delNode = RBT->Search(testArr[i]);
		RBT->Delete(delNode);
		printf("delete : %d / black height : %d \n", testArr[i], RBT->CheckBlackHeight());
	}
}

int _tmain(int argc, _TCHAR* argv[])
{

	TestRBTInsert();
	TestRBTDelete();
	free(RBT);

	getchar();
	return 0;
}
