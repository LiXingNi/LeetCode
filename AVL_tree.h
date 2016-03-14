#ifndef NOTE_HELP_T2_H_
#define NOTE_HELP_T2_H_

#include <memory>
#include <queue>
using namespace std;

class Node;
typedef shared_ptr<Node> NodePtr;

extern NodePtr nil;

struct Node
{
	int height;
	int key;
	NodePtr left;
	NodePtr right;
	NodePtr parent;
	Node(int k = 0,int h = 1) :key(k), height(h),left(nil),right(nil),parent(nil){}
};

NodePtr nil(new Node(0, 0));

struct AVLTree
{
	NodePtr root;
	AVLTree() :root(nil){}
	NodePtr insert(int);
	void adjustTree(NodePtr);
	void leftRotate(NodePtr);
	void rightRotate(NodePtr);
	void bfTree();
};


void AVLTree::bfTree()
{
	queue<NodePtr> que;
	que.push(root);
	while (!que.empty())
	{
		NodePtr q = que.front();
		que.pop();
		if (q == nil)
		{
			cout << "nil ";
		}
		else
		{
			cout << q->key << " ";
			que.push(q->left);
			que.push(q->right);
		}
	}
}


NodePtr AVLTree::insert(int val)
{
	shared_ptr<Node> curr(new Node(val));
	shared_ptr<Node> y(nil), x(root);
	while (x != nil)
	{
		y = x;
		x->height += 1;
		if (curr->key < x->key)
			x = x->left;
		else					// curr->key >= x->key
			x = x->right;
	}

	curr->parent = y;
	if (y == nil)
	{
		root = curr;
	}
	else
	{
		if (curr->key < y->key)
			y->left = curr;
		else
			y->right = curr;
	
		adjustTree(curr);
	}
	return curr;
}


void AVLTree::leftRotate(NodePtr x)
{
	NodePtr y = x->right;
	x->right = y->left;
	if (y->left != nil)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == nil)
		root = y;
	else
	{
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	x->parent = y;
	y->left = x;

	x->height = max(x->left->height, x->right->height) + 1;
	y->height = max(y->left->height, y->right->height) + 1;

	//while (x != root)
	//{
	//	x->height = max(x->left->height, x->right->height) + 1;
	//	x = x->parent;
	//}
}

void AVLTree::rightRotate(NodePtr x)
{
	NodePtr y = x->left;
	x->left = y->right;
	if (y->right != nil)
		y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == nil)
		root = y;
	else
	{
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	x->parent = y;
	y->right = x;

	x->height = max(x->left->height, x->right->height) + 1;
	y->height = max(y->left->height, y->right->height) + 1;
}


void AVLTree::adjustTree(NodePtr x)
{
	
	if (x->parent == nil || x->parent->parent == nil)
		return;

	NodePtr pparent = x->parent->parent;

	if (pparent != root)
	{
		x = x->parent;
		pparent = pparent->parent;
	}

	//�����߶Ȳ��2���򵱼����е���
	if (abs(pparent->left->height - pparent->right->height) >= 2)
	{
		//������
		if (x->parent == pparent->left)
		{
			if (x == x->parent->right) //��������
				leftRotate(x->parent);
			rightRotate(pparent);

		}
		else //������
		{
			if (x == x->parent->left) //��������
				rightRotate(x->parent);
			leftRotate(pparent);
		}
	}
	adjustTree(pparent);
	return;
}





#endif