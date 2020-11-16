#include <iostream>

using namespace std;

float InvSqrt(float x) {
	float xhalf = 0.5f * x;
	int i = *(int*)&x;
	i = 0x5f3759df - (i >> 1);
	x = *(float*)&i;
	x = x * (1.5f - xhalf * x * x);
	return x;
}

int main() {
    double x;
    cin >> x;
    cout << (1 / InvSqrt(x));
    return 0;
}