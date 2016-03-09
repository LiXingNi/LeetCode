#include <iostream>
using namespace std;

//1.   stupid wap , changes value in listNode, time: 164ms
/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution {
public:
	ListNode* insertionSortList(ListNode* head) {
		if (head == NULL) return head;
		ListNode * root = head;
		ListNode * p = root->next;
		while (p != NULL)
		{
			ListNode * curr = root;
			while (curr != p)
			{
				if (p->val >= curr->val)
				{
					curr = curr->next;
				}
				else
					break;
			}
			if (curr != p)
			{
				int val = p->val;
				while (curr != p->next)
				{
					int i = curr->val;
					curr->val = val;
					val = i;
					curr = curr->next;
				}
			}
			p = p->next;
		}
		return head;
	}
};
//2. change list node  . time :84ms
/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution {
public:
	ListNode* insertionSortList(ListNode* head) {
		if (head == NULL) return head;
		ListNode * root = head;
		ListNode * pprev = root;
		ListNode * p = root->next;
		while (p != NULL)
		{
			ListNode * curr = root;
			ListNode * prev = NULL;
			ListNode * mid;
			while (curr != p && p->val >= curr->val)
			{
				prev = curr;
				curr = curr->next;
			}
			if (curr != p)
			{
				pprev->next = p->next;
				mid = pprev;
				p->next = curr;
				if (prev != NULL)
					prev->next = p;
				else
					root = p;
				p = mid;
			}
			pprev = p;
			p = p->next;
		}
		return root;
	}
};



//3. best way : when there is a reverse number, then find the location for the number. time : 32ms
/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution {
public:
	ListNode* insertionSortList(ListNode* head) {
		if (head == NULL) return head;
		ListNode * root = new ListNode(0);
		root->next = head;

		ListNode * curr = head;
		ListNode * prev = root;
		while (curr)
		{
			if (curr->next && curr->val > curr->next->val)
			{
				while (prev->next && prev->next->val <= curr->next->val) prev = prev->next;

				ListNode * tmp = prev->next;
				prev->next = curr->next;
				curr->next = curr->next->next;
				prev->next->next = tmp;
				prev = root;
			}
			else curr = curr->next;
		}
		head = root->next;
		delete root;
		return head;
	}
};