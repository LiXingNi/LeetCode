#include "rb_tree.h"

NodePtr nil(new Node(0, Black, 0));  //哨兵


int RBTree::osBackRank(NodePtr x)  //os tree NEW ADD ***************
{
	int r = x->right->size;
	NodePtr y = x;
	while (y != root)
	{
		if (y->parent->left == y)
			r += y->parent->right->size + 1;
		y = y->parent;
	}
	return r;
}


int RBTree::osRank(NodePtr x)	//os tree NEW ADD ***************
{
	int r = x->left->size + 1;
	NodePtr y = x;
	while (y != root)
	{
		if (y->parent->right == y)
			r += y->parent->left->size + 1;
		y = y->parent;
	}
	return r;
}

NodePtr RBTree::osSelect(int i)	//os tree NEW ADD ***************
{
	NodePtr x = root;
	int r = x->left->size + 1;
	while (r != i)
	{
		if (i < r)
			x = x->left;
		else
		{
			x = x->right;
			i -= r;
		}
		r = x->left->size + 1;
	}
	return x;
}

NodePtr RBTree::search(int val)
{
	NodePtr x = root;

	while (x != nil && x->key != val)
	{
		if (x->key > val)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

void RBTree::erase(int val)
{
	NodePtr x = root;
	while (x != nil && x->key != val)
	{
		//删除沿树递减 size 域
		--x->size;				//os tree NEW ADD ***************
		if (val < x->key)
			x = x->left;
		else
			x = x->right;
	}
	if (x == nil)
		return;
	eraseNode(x);
}



void RBTree::bFTree()
{
	queue<NodePtr> que;
	que.push(root);
	while (!que.empty())
	{
		NodePtr x = que.front();
		que.pop();
		if (x == nil)
		{
			cout << "nil" << endl;
		}
		else
		{
			cout << x->key << "\t" << (x->color ? "Red" : "Black")  << "\t" << x->size << endl;	//os tree NEW ADD ***************
			que.push(x->left);
			que.push(x->right);
		}

	}
}

void RBTree::orderTree(NodePtr z)
{
	if (z == nil)
		return;
	orderTree(z->left);
	cout << z->key << (z->color ? "\tRed" : "\tBlack") << endl;
	orderTree(z->right);
}

NodePtr RBTree::tMin(NodePtr x)
{
	while (x->left != nil) x = x->left;
	return x;
}

NodePtr RBTree::tMax(NodePtr x)
{
	while (x->right != nil) x = x->right;
	return x;
}

void RBTree::eraseFixUp(NodePtr z)
{
	while (z != root && z->color == Black)
	{
		NodePtr pt = z->parent;
		if (z == pt->left)
		{
			NodePtr br = pt->right;
			if (br->color == Red) //case1
			{
				pt->color = Red;
				br->color = Black;
				leftRotate(pt);
			}
			else  //br->color == Black
			{
				if (br->left->color == Black && br->right->color == Black)  //case2
				{
					br->color = Red;
					z = pt;
				}
				else if (br->left->color == Red && br->right->color == Black) //case3
				{
					br->left->color = Black;
					br->color = Red;
					rightRotate(br);
				}
				else //case4
				{
					br->color = pt->color;
					pt->color = Black;
					br->right->color = Black;
					leftRotate(pt);
					z = root;
				}
			}
		}
		else
		{
			NodePtr br = pt->left;
			if (br->color == Red) //case1
			{
				br->color = Black;
				pt->color = Red;
				rightRotate(pt);
			}
			else
			{
				if (br->left->color == Black && br->right->color == Black) // case2
				{
					br->color = Red;
					z = pt;
				}
				else if (br->left->color == Black) // case3
				{
					br->color = Red;
					br->right->color = Black;
					leftRotate(br);
				}
				else
				{
					br->color = pt->color;
					pt->color = Black;
					br->left->color = Black;
					rightRotate(pt);
					z = root;
				}
			}
		}
	}
	z->color = Black;
}

NodePtr RBTree::eraseNode(NodePtr z)
{
	NodePtr y, x;
	if (z->left == nil || z->right == nil)
		y = z;
	else
		y = tMin(z->right);

	if (y->left != nil)
		x = y->left;
	else
		x = y->right;

	if (x != nil)
		x->parent = y->parent;

	if (y->parent == nil)
		root = x;
	else
	{
		if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
	}

	if (y != z)
		z->key = y->key;
	if (y->color == Black)
		eraseFixUp(x);
	return y;
}




NodePtr RBTree::insert(int val)
{
	NodePtr z(new Node(val));   //Red
	NodePtr x = root, y = nil;
	while (x != nil)
	{
		++x->size;	//os tree NEW ADD ***************
		y = x;
		if (val <= x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if (y == nil)
		root = z;
	else
	{
		if (val <= y->key)
			y->left = z;
		else
			y->right = z;
	}

	z->color = Red;
	z->left = nil;
	z->right = nil;

	insertFixUp(z);
	return z;
}

void RBTree::insertFixUp(NodePtr z)
{
	while (z->parent->color == Red) //不用判断 z->parent != nil ，因为 nil->color = Black
	{
		NodePtr pt = z->parent;
		if (pt == pt->parent->left) //父亲位于祖父的左子树
		{
			NodePtr uc = pt->parent->right;
			if (uc->color == Red) //case1
			{
				uc->color = Black;
				pt->color = Black;
				pt->parent->color = Red;
				z = pt->parent;
			}
			else
			{
				if (z == pt->right) //case2
				{
					z = pt;
					leftRotate(z);
					pt = z->parent;
				}
				//case3
				pt->color = Black;
				pt->parent->color = Red;
				rightRotate(pt->parent);
			}
		}
		else  //父亲位于祖父的右子树
		{
			NodePtr uc = pt->parent->left;
			if (uc->color == Red) //case1
			{
				uc->color = Black;
				pt->color = Black;
				pt->parent->color = Red;
				z = pt->parent;
			}
			else
			{
				if (z == pt->left) //case2
				{
					z = pt;
					rightRotate(z);
					pt = z->parent;
				}
				pt->color = Black;
				pt->parent->color = Red;
				leftRotate(pt->parent);
			}
		}
	}
	root->color = Black;
}


void RBTree::rightRotate(NodePtr x)
{
	NodePtr y = x->left;
	x->left = y->right;
	if (y->right != nil)
		y->right->parent = x;
	NodePtr p = x->parent;
	if (p == nil)
		root = y;
	else
	{
		if (p->left == x)
			p->left = y;
		else
			p->right = y;
	}
	y->parent = p;
	x->parent = y;
	y->right = x;

	//调整 size 域
	y->size = x->size;			//os tree NEW ADD ***************
	x->size = x->left->size + x->right->size + 1;		//os tree NEW ADD ***************
}

void RBTree::leftRotate(NodePtr x)
{
	NodePtr y = x->right;
	x->right = y->left;
	if (y->left != nil)
		y->left->parent = x;
	NodePtr p = x->parent;
	if (p == nil) //根的节点
		root = y;
	else
	{
		if (x == p->left)
			p->left = y;
		else
			p->right = y;
	}
	y->parent = p;
	x->parent = y;
	y->left = x;

	//调整 size 域
	y->size = x->size;		//os tree NEW ADD ***************
	x->size = x->left->size + x->right->size + 1;		//os tree NEW ADD ***************
}	