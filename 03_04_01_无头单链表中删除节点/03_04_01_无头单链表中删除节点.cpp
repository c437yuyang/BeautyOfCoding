#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <climits>
#include <cassert>

struct ListNode
{
	int val;
	ListNode* pNext;
};

void DeleteNode(ListNode *pNode) 
{
	ListNode *pNext = pNode->pNext;
	int pNextValSave = pNext->val;
	pNode->pNext = pNext->pNext;
	pNode->val = pNextValSave;
	delete pNext;
}


int main()
{
	ListNode *head = new ListNode{ 0,nullptr };
	head->pNext = new ListNode{ 1,nullptr };
	ListNode *deletenode = head->pNext;
	head->pNext->pNext = new ListNode{ 2,nullptr };
	head->pNext->pNext->pNext = new ListNode{ 3,nullptr };

	DeleteNode(deletenode);


	return 0;
}