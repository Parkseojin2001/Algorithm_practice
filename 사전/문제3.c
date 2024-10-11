# include <stdio.h>
# include <stdlib.h>

int binary_search(int start, int end, char *answer);

int main() {
	int a, b, num;// a, b 값, Y/N의 갯수
	char answer[1000];
	int result;

	scanf("%d %d %d", &a, &b, &num);

	scanf("%s", answer);

	result = binary_search(a, b, answer);
	printf("%d\n", result);

	return 0;
}

int binary_search(int start, int end, char *answer) {
	int mid;
	int result, i = 0;

	while(1) {
		mid = (start + end) / 2;

		if (start == end) {
			result = mid;
			break;
		}

		if (answer[i] == 'Y') {
			start = mid + 1;
		}
		else {
			end = mid;
		}
		i++;
	}

	return result;
}
