#include <initializer_list>
#include <iostream>
#include <vector>

template <class T>
struct S {
	std::vector<T> v;
	S(std::initializer_list<T> l) : v(l) {
		std::cout << "constructed with a " << l.size() << "-element list\n";
	}
	void append(std::initializer_list<T> l) {
		v.insert(v.end(), l.begin(), l.end());
	}
	std::pair<const T *, std::size_t> c_arr() const { return { &v[0], v.size() }; }
};

template <typename T>
void templated_fn(T) {}

int main() {
	S<int> s = { 1, 2, 3, 4, 5 };
	s.append({ 6, 7, 8 });

	std::cout << "The vector size is now " << s.c_arr().second << " ints:\n";

	for (auto n : s.v) {
		std::cout << n << ' ';
    }
	std::cout << '\n';

	std::cout << "Range-for over brace-init-list: \n";

	for (int x : { -1, -2, -3 }) {
		std::cout << x << ' ';
    }
	std::cout << '\n';
	return 0;
}