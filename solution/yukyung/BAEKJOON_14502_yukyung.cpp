
#include <stdio.h>
#include <queue>
using namespace std;

typedef struct PAIR {
   int x;
   int y;
}pair_t;

int map[9][9] = { 0 };
int copymap[9][9] = { 0 };
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int _max = 0;
int N, M;

int virus() {
   queue<pair_t> q;
   for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
         copymap[i][j] = map[i][j];
         if (map[i][j] == 2) {
            pair_t vir;
            vir.x = i;
            vir.y = j;
            q.push(vir);
         }
      }
   }

   while (!q.empty()) { // BFS
      pair_t vir = q.front();
      q.pop();
      int curx = vir.x;
      int cury = vir.y;
      for (int i = 0; i < 4; i++) {
         int movx = curx + dx[i];
         int movy = cury + dy[i];
         if (movx < 0 || movx >= N || movy < 0 || movy >= M || copymap[movx][movy]) continue;
         pair_t temp;
         temp.x = movx;
         temp.y = movy;
         q.push(temp);
         copymap[movx][movy] = 2;
      }
   }

   int result = 0;

   for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
         if (copymap[i][j] == 0) {
            result++;
         }
      }
   }

   return result;
}

void start(int curx, int cury, int wall) {
   if (wall == 3) { // return condition
      int res = virus(); // conut all spreaded virus, return
      if (res > _max) {
         _max = res;
      }
      return;
   }

   for (int i = curx; i < N; i++) { // second, third wall
      for (int j = 0; j < M; j++) {
         if (!map[i][j]) {
            map[i][j] = 1;
            start(i, j, wall + 1);
            map[i][j] = 0;
         }
      }
   }

}

int main(){
    //freopen("input.txt", "r", stdin);
   scanf("%d %d", &N, &M);

   for (int i = 0; i < N; i++)
      for (int j = 0; j < M; j++)
         scanf("%d", &map[i][j]);

   for (int i = 0; i < N; i++) { // first wall
      for (int j = 0; j < M; j++) {
         if (!map[i][j]) {
            map[i][j] = 1;
            start(i, j, 1);
            map[i][j] = 0;
         }
      }
   }

   printf("%d\n", _max);

   return 0;
}
