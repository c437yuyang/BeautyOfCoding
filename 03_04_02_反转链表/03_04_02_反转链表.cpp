#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <climits>
#include <cassert>


struct ListNode
{
	int val;
	struct ListNode *pNext;
};

ListNode* ReverseList(ListNode* pHead)
{
	if (pHead == nullptr || pHead->pNext == nullptr)
		return pHead;

	ListNode *pPrev = nullptr;
	ListNode *pCur = pHead;
	while (pCur != nullptr)
	{
		ListNode *next = pCur->pNext;
		pCur->pNext = pPrev;
		pPrev = pCur;
		pCur = next;
	}
	return pPrev;
}

int main()
{
	ListNode *head = new ListNode{ 0,nullptr };
	head->pNext = new ListNode{ 1,nullptr };
	head->pNext->pNext = new ListNode{ 2,nullptr };
	head->pNext->pNext->pNext = new ListNode{ 3,nullptr };

	auto head1 = ReverseList(head);

	return 0;
}