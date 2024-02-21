#include<stdio.h>
#include<math.h>

float absolute(float x) {
    if (x < 0.0)
        x *= -1;
    
    return x;
}

float compute_min_loss(float a, float b, float c) {
	int ca = round(a);
	int cb = round(b);
	int cc = round(c);

	float da, db, dc;
	while (ca + cb <= cc) {
		da = absolute(a - ca - 1) - absolute(a - ca);
		db = absolute(b - cb - 1) - absolute(b - cb);
		dc = absolute(c - cc + 1) - absolute(c - cc);

		if (da <= db && da <= dc)
			ca++;
		else if (db <= da && db <= dc)
			cb++;
		else
			cc--;
	}

// 	printf("%d %d %d\n", ca, cb, cc);
	return absolute(a - ca) + absolute(b - cb) + absolute(c - cc);
}

int main() {
	int n;
	float k;
	scanf("%d %f", &n, &k);

	float a, b, c, sum = 0;

	for (int i = 0; i < n; i++) {
		scanf("%f %f %f", &a, &b, &c);

		sum += compute_min_loss(a, b, c);
	}

	if (sum <= k) {
		printf("YES");
	}
	else {
		printf("NO");
	}

	return 0;
}

