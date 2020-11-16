#include <iostream>
#include <functional>

using namespace std;

int main() {
	int a, b;
	std::function<int(int, int)> add = [](int a, int b) -> int {
		return a + b;
	};
	cin >> a >> b;
	cout << add(a, b) << endl;
	return 0;
}
