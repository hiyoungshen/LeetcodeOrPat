#pragma warning(disable:4996)
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 105;

int n;
int a, b, c, d;
int num[105];

void dfs(int sum, int cnt) {
	if (cnt == 1) {
		for (b = 2; b <= 100; b++)
			if (sum - num[b] >= 1) {
				dfs(sum - num[b], cnt + 1);
			}
	}
	else if (cnt == 2) {
		for (c = b; c <= 100; c++)
			if (sum - num[c] >= 1)
				dfs(sum - num[c], cnt + 1);
	}
	else {
		for (d = c; d <= 100; d++)
			if (sum == num[d])
				printf("Cube = %d, Triple = (%d,%d,%d)\n", a, b, c, d);
	}
}

int main() {
	for (int i = 2; i <= 100; i++) {
		num[i] = i * i * i;
	}

	scanf("%d", &n);
	for (a = 2; a <= n; a++)
		dfs(num[a], 1);
}