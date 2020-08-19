#include<iostream>
#include <cstdio>
using namespace std;
#define MAX_SIZE 100

int T, N;
int map[MAX_SIZE][MAX_SIZE];
int visit[MAX_SIZE][MAX_SIZE] = { false };
int dx[4] = { 0,-1,0,1 };
int dy[4] = { -1,0,1,0 };
int min_time;

void DFS(int cur_x, int cur_y, int cur_time) {
	if (cur_x == N - 1 && cur_y == N - 1) { //도착
		if(min_time > cur_time)
			min_time = cur_time;
		return;
	}
	for (int i = 0; i < 4; i++) {
		int mov_x = cur_x + dx[i]; //이동 위치
		int mov_y = cur_y + dy[i];
		if (mov_x < 0 || mov_x >= N || mov_y < 0 || mov_y >= N || visit[mov_y][mov_x]) //범위를 벗어나면
			continue;
		visit[cur_y][cur_x] = true;
		DFS(mov_x, mov_y, cur_time + map[mov_y][mov_x]);
		visit[cur_y][cur_x] = false;
	}
}
int main() {
	scanf("%1d", &T);
	scanf("%1d", &N);
	for (int i = 1; i <= T; i++) {
		min_time = 1e9;
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				scanf("%1d", &map[j][k]);
			}
		}
		DFS(0, 0, 0);
		printf("#%d %d", i, min_time);
	}
	return 0;
}