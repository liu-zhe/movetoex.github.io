int gcdEx(int x, int y, int& d, int& a, int& b) {
	if (!y) d = x, a = 1, b = 0;
	else gcdEx(y, x % y, d, b, a), b -= a * (x / y);
}