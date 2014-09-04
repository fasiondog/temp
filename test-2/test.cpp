#include <string>
#include <iostream>
#include <vector>

using namespace std;


int test() {
	int i = 0;
	auto f = [=]()mutable->int { return ++i; };
	return f();
}

int main() {
    vector<string> str_vec;
	str_vec.push_back("string1");
	str_vec.push_back("string2");
	str_vec.push_back("string3");
	
	for (int i = 0; i < str_vec.size(); ++i) {
		//f(i, str_vec[i]);
		auto fu = [&]() { cout << i << " " << str_vec[i] << endl; };
		fu();
	}
	
	for (int i = 0; i < 5; ++i) {
	    cout << i << " " << test() << endl;
	}
}
