#include<cstdio>
#include<queue>
#include <iostream>
using namespace std;

#define MAX_SIZE 8
#define MAX_SIZE2 64

int N, M;
int map[MAX_SIZE][MAX_SIZE];
int empty_idx, wall_idx, vir_idx, copy_idx, copy_vir_idx = 0;
int vir_x[MAX_SIZE2], vir_y[MAX_SIZE2];
int empty_x[MAX_SIZE2], empty_y[MAX_SIZE2];
int copy_map[MAX_SIZE][MAX_SIZE];
int dx[4] = { 0,-1,0,1 };
int dy[4] = { -1,0,1,0 };
int _min = MAX_SIZE2+1;

void BFS() {
	copy_vir_idx = vir_idx;
	for (int vir = 0; vir < copy_vir_idx; vir++) {
		for (int i = 0; i < 4; i++) {
			int mov_dx = vir_x[vir] + dx[i];
			int mov_dy = vir_y[vir] + dy[i];
			if (copy_map[mov_dy][mov_dx] == 2 || copy_map[mov_dy][mov_dx] == 1 || mov_dy < 0 || mov_dy >= N || mov_dx < 0 || mov_dx >= M)
				continue;
			copy_map[mov_dy][mov_dx] = 2;
			vir_x[copy_vir_idx] = mov_dx;
			vir_y[copy_vir_idx++] = mov_dy;

		}
	}
	if (_min > copy_vir_idx)
		_min = copy_vir_idx;
}

void copy() {
	for (int m = 0; m<N; m++) //copy
		for (int n = 0; n<M; n++)
			copy_map[m][n] = map[m][n];
}
int main() {

	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 0) {
				empty_y[empty_idx] = i;
				empty_x[empty_idx++] = j;
			}
			else if (map[i][j] == 1)
				wall_idx++;
			else {
				vir_y[vir_idx] = i;
				vir_x[vir_idx++] = j;
			}
		}
	}
	for (int i = 0; i < empty_idx-2; i++) {
		for (int j = i + 1; j < empty_idx - 1; j++) {
			for (int k = j + 1; k < empty_idx; k++) {
				copy();
				copy_map[empty_y[i]][empty_x[i]] = 1;
				copy_map[empty_y[j]][empty_x[j]] = 1;
				copy_map[empty_y[k]][empty_x[k]] = 1;
				BFS();
				copy_idx++;
			}
		}
	}
	printf("%d", N*M - wall_idx - 3 - _min);
	return 0;
}