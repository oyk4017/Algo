#include <string>
#include <vector>

using namespace std;

struct Node {
	int num;
	int x;
	int y;
	Node* left;
	Node* right;
};

vector<vector<int>> answer{ {},{} };  //초기화 반드시 필요 -> []인덱스사용하기 위해서

void Insert_Node(Node* parent, Node* child) {

	if (child->x > parent->x) { //오른쪽
		if (parent->right == NULL)
			parent->right = child;
		else
			Insert_Node(parent->right, child);
	}
	else { //왼쪽
		if (parent->left == NULL)
			parent->left = child;
		else
			Insert_Node(parent->left, child);
	}
}

void preorder(Node* node) {

	if (node == NULL) return;
	answer[0].push_back(node->num);
	preorder(node->left);
	preorder(node->right);
}

void postorder(Node* node) {

	if (node == NULL) return;
	postorder(node->left);
	postorder(node->right);
	answer[1].push_back(node->num);

}
vector<vector<int>> solution(vector<vector<int>> nodeinfo) {

	vector<Node> tree;

	for (int i = 0; i < nodeinfo.size(); i++) {
		tree.push_back({ i + 1, nodeinfo[i][0], nodeinfo[i][1] }); //num, x, y
	}

	for (int i = 0; i<tree.size() - 1; i++) {
		for (int j = 0; j<tree.size() - 1; j++) {
			if (tree[j].y < tree[j + 1].y) {
				Node temp = tree[j];
				tree[j] = tree[j + 1];
				tree[j + 1] = temp;
				continue;
			}
		}
	}

	Node* root = &tree[0];

	for (int i = 1; i < nodeinfo.size(); i++) {
		Insert_Node(root, &tree[i]);
	}

	preorder(root);
	postorder(root);

	return answer;
}