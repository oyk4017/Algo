#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_SIZE 100
using namespace std;

struct pos {
	int mul;
	int y;
	int x;
};

int map[MAX_SIZE][MAX_SIZE];
int T, n;

void group(int cur_y, int cur_x, vector<pos> &v) {
	int count_x = 1;
	int count_y = 1;

	for (int j = cur_x; j < n; j++) {
		if (map[cur_y][j + 1] == 0 || j == n - 1) { //다음으로 내려가야할 때
			for (int k = cur_y + 1; k < n; k++) {
				if (k >= n || map[k][j] == 0) { //내려갈 곳이 없거나 끝이면
					v.push_back({ ((count_x)*(count_y) << 10) + count_y, count_y,count_x });
					for (int a = cur_y; a < cur_y + count_y; a++) { //용기들 체크
						for (int b = cur_x; b < cur_x + count_x; b++)
							map[a][b] = 0;
					}
					return;
				}
				count_y++; //내려갈 곳이 있으면
			}
		}
		count_x++;
	}
}

void scan1(vector<pos>& v) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] != 0) {
				group(i, j, v);
			}
		}
	}
	for (int i = 0; i < v.size() - 1; i++) {
		for (int j = 0; j < v.size() - 1; j++) {
			if (v[j].mul > v[j + 1].mul) {
				pos temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
			}
		}
	}
}

int main() {

	scanf("%d", &T);
	for (int i = 1; i <= T; i++) {
		vector<pos> v;
		scanf("%d", &n);
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				scanf("%1d", &map[j][k]);
			}
		}
		scan1(v);
		printf("#%d %d ", i, v.size());
		for (int j = 0; j < v.size(); j++)
			printf("%d %d ", v[j].y, v[j].x);
		printf("\n");
	}

	return 0;
}