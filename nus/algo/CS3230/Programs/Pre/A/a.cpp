#include <stdio.h>

int t, n, x, y;

int main() {
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        scanf("%d %d %d", &n, &x, &y);

        int prev = x, sum = x;
        for (int j = 2; j <= n; j++) {
            prev += y;
            sum += prev;
        }

        printf("%d\n", sum);
    }

    return 0;
}
