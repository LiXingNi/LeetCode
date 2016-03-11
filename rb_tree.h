#include <iostream>
#include <memory>
#include <queue>
using namespace std;

class Node;
typedef shared_ptr<Node>  NodePtr;
typedef bool	Color;
const bool Red = true;
const bool Black = false;

struct Node
{
	int key;
	bool color;
	NodePtr left;
	NodePtr right;
	NodePtr parent;

	Node(int i = 0,Color c = Red) :key(i), color(c){};
};

const NodePtr nil(new Node(0,Black));  //из╠Ь

struct RBTree
{
	NodePtr root;
public:
	RBTree() :root(nil){}
	void leftRotate(NodePtr x);
	void rightRotate(NodePtr x);
	void insert(int val);
	void insertFixUp(NodePtr x);
	void eraseFixUp(NodePtr x);
	NodePtr eraseNode(NodePtr z);
	void erase(int val);

	NodePtr tMax(NodePtr x);
	NodePtr tMin(NodePtr x);
	NodePtr search(int val);
	void orderTree(NodePtr);
	void bFTree();
};



