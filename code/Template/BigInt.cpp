#include <iostream>
#include <vector>

class BigInt : std::vector<int> {
  public:
	void _helper() {
		while (!empty() && !back()) pop_back();
		if (empty()) return;
		for (int i = 1; i < size(); ++i) {
			(*this)[i] += (*this)[i - 1] / 10;
			(*this)[i - 1] %= 10;
		}
		while (back() >= 10) {
			push_back(back() / 10);
			(*this)[size() - 2] %= 10;
		}
	}

	BigInt(int x = 0) {
		push_back(x);
		_helper();
	}
	BigInt(int x, int l) {
		resize(l);
		for (BigInt::iterator it = begin(); it != end(); ++it) {
			*it = x;
		}
	}
	~BigInt() {}

	friend std::istream &operator>>(std::istream &in, BigInt &n) {
		std::string s;
		n.clear();
		in >> s;
		for (int i = s.length() - 1; i >= 0; --i) {
			n.push_back(s[i] - '0');
		}
		n._helper();
		return in;
	}

	friend std::ostream &operator<<(std::ostream &out, BigInt x) {
		for (int i = x.size() - 1; ~i; --i) out << x[i];
		return out;
	}

	bool operator<(BigInt x) {
		if (size() != x.size()) return size() < x.size();
		for (int i = size() - 1; ~i; --i) {
			if ((*this)[i] != x[i]) return (*this)[i] < x[i];
		}
		return false;
	}

	bool operator>(BigInt x) {
		if (size() != x.size()) return size() > x.size();
		for (int i = size() - 1; ~i; --i) {
			if ((*this)[i] != x[i]) return (*this)[i] > x[i];
		}
		return false;
	}

	bool operator==(BigInt x) {
		if (size() != x.size()) return false;
		for (int i = size() - 1; ~i; --i) {
			if ((*this)[i] != x[i]) return false;
		}
		return true;
	}

	bool operator!=(BigInt x) { return !(*this == x); }
	bool operator<=(BigInt x) { return *this < x || *this == x; }
	bool operator>=(BigInt x) { return *this > x || *this == x; }

	BigInt operator+(BigInt x) {
		BigInt ans = *this;
		if (x.size() > size()) ans.resize(x.size());
		for (int i = 0; i < x.size(); ++i) {
			ans[i] += x[i];
		}
		ans._helper();
		return ans;
	}

	BigInt operator-(BigInt x) {
		BigInt ans = *this;
		if (ans < x) ans.swap(ans);
		for (int i = 0; i != x.size(); ans[i] -= x[i], ++i) {
			if (ans[i] < x[i]) {
				int j = i + 1;
				while (!ans[j]) ++j;
				while (j > i) {
					--ans[j];
					ans[--j] += 10;
				}
			}
		}
		ans._helper();
		return ans;
	}

	BigInt operator*(BigInt x) {
		BigInt ans;
		ans.resize(size() + x.size());
		for (int i = 0; i < size(); ++i) {
			for (int j = 0; j < x.size(); ++j) {
				ans[i + j] += (*this)[i] * x[j];
			}
		}
		ans._helper();
		return ans;
	}

	BigInt operator/(BigInt x) {
		if (x == 0) {
			throw std::invalid_argument("Divisor cannot be zero");
		}
		BigInt ans, a = *this;
		for (int i = a.size() - x.size() + 1; a >= x; --i) {
			BigInt d(0, i);
			d.back() = 1;
			BigInt c = x * d;
			while (a >= c) {
				a -= c;
				ans += d;
			}
		}
		ans._helper();
		return ans;
	}

	BigInt operator%(BigInt x) {
		if (x == 0) {
			throw std::invalid_argument("Divisor cannot be zero");
		}
		if (*this < x) return *this;
		BigInt ans = *this;
		for (int i = ans.size() - x.size() + 1; ans >= x; --i) {
			BigInt d(0, i);
			d.back() = 1;
			BigInt c = x * d;
			while (ans >= c) {
				ans -= c;
			}
		}
		ans._helper();
		return ans;
	}

	BigInt operator+=(BigInt x) { return *this = *this + x; }
	BigInt operator-=(BigInt x) { return *this = *this - x; }
	BigInt operator*=(BigInt x) { return *this = *this * x; }
	BigInt operator/=(BigInt x) { return *this = *this / x; }
	BigInt operator%=(BigInt x) { return *this = *this % x; }
};