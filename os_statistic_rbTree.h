#include <iostream>
#include <memory>
#include <queue>
using namespace std;

class Node;
typedef shared_ptr<Node>  NodePtr;
typedef bool	Color;
const bool Red = true;
const bool Black = false;

extern NodePtr nil;

struct Node
{
	int size;	//os tree NEW ADD ***************
	int key;
	bool color;
	NodePtr left;
	NodePtr right;
	NodePtr parent;

	//os tree NEW ADD ***************
	Node(int i = 0,Color c = Red,int s = 1) :key(i), color(c),size(s),left(nil),right(nil),parent(nil){};
};



struct RBTree
{
	NodePtr root;
public:
	RBTree() :root(nil){}
	void leftRotate(NodePtr x);
	void rightRotate(NodePtr x);
	NodePtr insert(int val);
	void insertFixUp(NodePtr x);
	void eraseFixUp(NodePtr x);
	NodePtr eraseNode(NodePtr z);
	void erase(int val);

	NodePtr tMax(NodePtr x);
	NodePtr tMin(NodePtr x);
	NodePtr search(int val);
	void orderTree(NodePtr);
	void bFTree();

	//os tree NEW ADD ***************
	NodePtr osSelect(int);		//查找给定序列中第i小的数
	int osRank(NodePtr);		//给定顶点在中序遍历中所处位置
	int osBackRank(NodePtr);	//给定顶点在中序遍历中有多少个顶点位于其之后
	
};


//os tree NEW ADD ***************
inline int reversePariCount(vector<int> & vec) //使用顺序统计树来统计逆序对的数量
{
	RBTree tree;
	int count = 0;
	for (auto val : vec)
	{
		NodePtr curr = tree.insert(val);
		count += tree.osBackRank(curr);
	}
	return count;
}




