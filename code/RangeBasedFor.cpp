#include <iostream>
#include <map>

using namespace std;

map<string, int> m;

int main() {
	m["qwq"] = 12;
	m["qaq"] = 21;
	m["orz"] = 233;
	for (auto [key, val] : m) {
		cout << key << '=' << val << endl;
	}
	return 0;
}