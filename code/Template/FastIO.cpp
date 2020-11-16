#include <cstdio>

#define BUF_SIZE 10000000

namespace FastIO {
int pos = 0;
char wbuf[BUF_SIZE];
inline void flush() {
	fwrite(wbuf, 1, pos, stdout);
	pos = 0;
}
inline int getchar() {
	static char buf[BUF_SIZE];
	static int len = 0, pos = 0;
	if (pos == len)
		pos = 0, len = fread(buf, 1, BUF_SIZE, stdin);
	return pos == len ? EOF : buf[pos++];
}
inline int get_uint() {
	int c = getchar(), x = 0;
	while (c <= 32) c = getchar();
	for (; '0' <= c && c <= '9'; c = getchar()) x = x * 10 + c - '0';
	return x;
}
inline int get_int() {
	int s = 1, c = getchar(), x = 0;
	while (c <= 32) c = getchar();
	if (c == '-') s = -1, c = getchar();
	for (; '0' <= c && c <= '9'; c = getchar()) x = x * 10 + c - '0';
	return x * s;
}
inline void get_string(char *s) {
	int c = getchar();
	while (c <= 32) c = getchar();
	for (; c > 32; c = getchar()) *s++ = c;
	*s = 0;
}
inline void putchar(int x) {
	if (pos == BUF_SIZE) flush();
	wbuf[pos++] = x;
}
inline void put_int(int x) {
	if (x < 0) putchar('-'), x = -x;
	char s[24];
	int n = 0;
	while (x || !n) s[n++] = '0' + x % 10, x /= 10;
	while (n--) putchar(s[n]);
	putchar('\n');
}
inline void put_string(const char *s) {
	while (*s) putchar(*s++);
}
} // namespace FastIO

int main() {
    FastIO::put_int(FastIO::get_int() + FastIO::get_int());
    FastIO::flush();
    return 0;
}