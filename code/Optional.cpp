#include <functional>
#include <iostream>
#include <optional>
#include <string>

// optional 可用作可能失败的工厂的返回类型
std::optional<std::string> create(bool b) {
	if (b)
		return "Godzilla";
	else
		return {};
}

// 能用 std::nullopt 创建任何（空的） std::optional
auto create2(bool b) {
	return b ? std::optional<std::string>{ "Godzilla" } : std::nullopt;
}

// std::reference_wrapper 可用于返回引用
auto create_ref(bool b) {
	static std::string value = "Godzilla";
	return b ? std::optional<std::reference_wrapper<std::string>>{ value }
			 : std::nullopt;
}

int main() {
	std::cout << "create(false) returned "
			  << create(false).value_or("empty") << '\n';

	// 返回 optional 的工厂函数可用作 while 和 if 的条件
	if (auto str = create2(true)) {
		std::cout << "create2(true) returned " << *str << '\n';
	}

	if (auto str = create_ref(true)) {
		// 用 get() 访问 reference_wrapper 的值
		std::cout << "create_ref(true) returned " << str->get() << '\n';
		str->get() = "Mothra";
		std::cout << "modifying it changed it to " << str->get() << '\n';
	}
}