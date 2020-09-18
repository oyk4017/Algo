/* [SWEA] 5550
* Completed!
*
* Memory : 12,544 KB
* Time   : 8 ms
*/
#include<cstdio>
#define MAX_SIZE 2501

int main() {
	freopen("Input.txt", "r", stdin);
	int T;
	char frog[MAX_SIZE];
	
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int min_count = 0;
		int count[5] = { 0, };
		scanf("%s", &frog);
		for (int i = 0; frog[i]; i++) {
			if (min_count < count[0] - count[4])
				min_count = count[0] - count[4];
			switch (frog[i]) {
			case 'c':
				count[0]++;
				break;
			case 'r':
				count[1]++;
				if (count[0] < count[1]) { //c보다 r이 먼저나오면 -1
					min_count = -1;
					frog[i + 1] = 0;
				}
				break;
			case 'o':
				count[2]++;
				if (count[1] < count[2]) {
					min_count = -1;
					frog[i + 1] = 0;
				}
				break;
			case 'a':
				count[3]++;
				if (count[2] < count[3]) {
					min_count = -1;
					frog[i + 1] = 0;
				}
				break;
			case 'k':	
				count[4]++;
				if (count[3] < count[4]) {
					min_count = -1;
					frog[i + 1] = 0;
				}
				break;				
			}
		}
		for (int i = 0; i < 4; i++) { //문자 갯수가 맞는지
			if (count[i] != count[i + 1]) {
				min_count = -1;
				break;
			}
		}
		printf("#%d %d\n", t, min_count);
	}

	return 0;
}