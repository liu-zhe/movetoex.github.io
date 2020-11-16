inline int qgcd(int a, int b) {
	int i, j;
	if (a == 0 || b == 0) return a | b;
	for (i = 0; 0 == (a & 1); ++i) a >>= 1;
	for (j = 0; 0 == (b & 1); ++j) b >>= 1;
	if (j < i) i = j;
	while (1) {
		if (a < b) {
			a ^= b, b ^= a, a ^= b;
		}
		if (0 == (a -= b)) return b << i;
		while (0 == (a & 1)) a >>= 1;
	}
}