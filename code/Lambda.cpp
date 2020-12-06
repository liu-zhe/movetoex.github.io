#include <iostream>
#include <functional>

using namespace std;

int main() {
	int a = 2, b = 3;
	std::function<int(int, int)> add = [](int a, int b) -> int {
		return a + b;
	};
	cout << add(a, b) << endl;
	return 0;
}
