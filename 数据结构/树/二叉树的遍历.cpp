#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e6 + 10;

struct node
{
	int v;
	node *l;
	node *r;
	node():l(NULL), r(NULL){}
	node(int x, node *left, node *right):v(x), l(left), r(right){}
	~node()
	{
		if (l) delete l;
		if (r) delete r;
	}
	void pre_order()
	{
		printf("%c  ", v);
		if (l) l->pre_order();
		if (r) r->pre_order();
	}
	void in_order()
	{
		if (l) l->in_order();
		printf("%c  ", v);
		if (r) r->in_order();
	}
	void post_order()
	{
		if (l) l->post_order();
		if (r) r->post_order();
		printf("%c  ", v);
	}
};

class BT
{
	node *root;
public:
	BT():root(NULL){}
	~BT()
	{
		if (root)
		{
			if (root->l) delete root->l;
			if (root->r) delete root->r;
			delete root;
		}
	}
	void set_tree(int x, BT *left, BT *right)
	{
		if (root || left == right)
			return ;
		root = new node(x, left->root, right->root);
		left->root = right->root = NULL;
	}
	void pre_order()	//先序遍历
	{
		if (!root) return ;
		root->pre_order();
		printf("\n\n");
 	}
	void in_order()	//中序遍历
	{
		if (!root) return ;
		root->in_order();
		printf("\n\n");
	}
	void post_order()	//后序遍历
	{
		if (!root) return ;
		root->post_order();
		printf("\n\n");
	}
	void level_order(vector<int > & cnt)	//层次遍历
	{
		if (!root) return ;
		queue<pair<node*, int> > q;
		q.push(make_pair(root, 1));
		while (!q.empty())
		{
		    pair<node*, int> t = q.front();
			q.pop();
			++cnt[0];
			cnt[2] = max(cnt[2], t.second);
			if (!t.first->l && !t.first->r) ++cnt[1];
			if (t.first->l) q.push(make_pair(t.first->l, t.second+1));
			if (t.first->r) q.push(make_pair(t.first->r, t.second+1));
		}
	}
	void exchange()	//交换左右子树
	{
		if (root)
		{
			node *t = root->l;
			root->l = root->r;
			root->r = t;
		}
	}

} a, b, x, y, z;

int main()
{
	y.set_tree('E', &a, &b);
	z.set_tree('F', &a, &b);
	x.set_tree('C', &y, &z);
	y.set_tree('D', &a, &b);
	z.set_tree('B', &y, &x);
	printf("先序遍历：");
	z.pre_order();
	printf("\n中序遍历：");
    z.in_order();
	printf("\n后序遍历：");
	z.post_order();
	vector<int> cnt(3);
	z.level_order(cnt);
	printf("\n层次遍历求结点个数、非叶子节点个数、树的深度：\n");
	for (int i = 0; i < cnt.size(); ++i)
		printf("%d\n", cnt[i]);
	z.exchange();
	printf("\n交换左右子树后的先序遍历：");
	z.pre_order();

	return 0;
}


