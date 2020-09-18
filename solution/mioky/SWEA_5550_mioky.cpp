/* [SWEA] 5550
* Completed!
*
* Memory : 12,684 KB
* Time   : 84 ms
*/

#include <iostream>
#include <string>

using namespace std;

int max_count = 1;

bool check(string str) {
	string frog = "croak";
	int end_count = 0;

	while (str.length()) {
		int idx = 0;
		int _count = 1;
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == frog[idx]) {
				idx++;
				str.erase(str.begin() + i);
				i--;
				if (idx == 5) {
					end_count++;
					break;
				}
				continue;
			}
			if (str[i] == 'c') {
				_count++;

			}
		}
		if (idx != 5) return false;
		max_count = max_count < _count ? _count : max_count;
	}
	return true;
}

int main() {
	//freopen("Input.txt", "r", stdin
	/*ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);*/
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		string str;
		max_count = 1;
		cin >> str;
		if (!check(str))  printf("#%d %d\n", t, -1);
		else printf("#%d %d\n", t, max_count);

	}

	return 0;
}