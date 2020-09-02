#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct BST {
	int x;
	int y;
	int index;
	BST* left;
	BST* right;
};

vector<int> postidx(const BST* tree, vector<int>& post) {
	if (tree->left != NULL)	postidx(tree->left, post);
	if (tree->right != NULL) postidx(tree->right, post);
	post.push_back(tree->index);

	return post;
}
vector<int> preidx(const BST* tree, vector<int>& pre) {
	pre.push_back(tree->index);
	if (tree->left != NULL)	preidx(tree->left, pre);
	if (tree->right != NULL) preidx(tree->right, pre);
	return pre;
}

bool pred(vector<int> a, vector<int> b) {
	if (a[1] == b[1])
		return a[0] < b[0];
	else
		return a[1] > b[1];
}
vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	vector<vector<int>> answer;
	for (int i = 0; i < nodeinfo.size(); i++)
		nodeinfo[i].push_back(i + 1);

	sort(nodeinfo.begin(), nodeinfo.end(), pred);
	BST tree = { nodeinfo[0][0] ,nodeinfo[0][1],nodeinfo[0][2],NULL,NULL };
	BST* walker;
	for (int i = 1; i < nodeinfo.size(); i++) {
		walker = &tree;
		while (1) {
			if (walker->x > nodeinfo[i][0]) {
				if (walker->left == NULL) {
					walker->left = new BST{ nodeinfo[i][0],nodeinfo[i][1] ,nodeinfo[i][2],NULL,NULL };
					break;
				}
				else
					walker = walker->left;
			}
			else {
				if (walker->right == NULL) {
					walker->right = new BST{ nodeinfo[i][0],nodeinfo[i][1] ,nodeinfo[i][2],NULL,NULL };
					break;
				}
				else
					walker = walker->right;
			}
		}
	}
	vector<int> pre;
	vector<int> post;
	answer.push_back(preidx(&tree, pre));
	answer.push_back(postidx(&tree, post));

	return answer;
}