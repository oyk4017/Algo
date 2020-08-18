#include <iostream>

using namespace std;

int T, N;
int map[12][12];
int dx[4] = { 0,-1,0,1 };
int dy[4] = { -1,0,1,0 };
int core_x[12];
int core_y[12];
int core_idx = 0;
int core_count = 0;

int DFS(int core_count, int total) {
		if (core_count == core_idx) {
			//전선 길이 합 최소
			//아직
			return total;
		}
		int temp_dx = core_x[core_count];
		int temp_dy = core_y[core_count];
		int line_count = 0;
		for (int i = 0; i < 4; i++) {
			while (true) {	
				if (map[temp_dy+dy[i]][temp_dx+dx[i]] != 0) {
					//체크한 것들 풀기
					for (int j = 0; j < line_count; j++) {
						map[temp_dy][temp_dx] = 0;
						temp_dy -= dy[i];
						temp_dx -= dx[i];
					}
					line_count = 0;
					break;
				}
				temp_dx += dx[i];
				temp_dy += dy[i];
				if (temp_dx >= 0 && temp_dx < N && temp_dy >= 0 && temp_dy < N) {
					line_count++;
					map[temp_dy][temp_dx] = 1;
				}
				else break; //map을 벗어나면
			}
			if (line_count != 0) {
				core_count++; //전원 연결된 코어
				DFS(core_count + 1, line_count + total);
			}
			for (int j = 0; j < line_count; j++) { //선 풀기
				map[temp_dy][temp_dx] = 0;
				temp_dy -= dy[i];
				temp_dx -= dx[i];
			}
			line_count = 0;
		}
		return total;
}

int main() {

	cin >> T >> N;
	for (int i = 0; i < T; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				cin >> map[j][k];
				if (map[j][k] == 1 && j != 0 && k != 0 && j!=N-1 && k !=N-1) {
					core_x[core_idx] = k;
					core_y[core_idx++] = j;
				}
			}
		}
		
		cout << DFS(0, 0) << endl;
	}
	return 0;
}