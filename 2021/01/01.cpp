#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int count_increase(auto begin, auto end, int length)
{
	return std::inner_product(begin, end-length, begin+length, 0, std::plus<>(), std::less<>());
}

std::vector<int> load_input()
{
	std::ifstream file("input.txt");
	std::istream_iterator<int> it(file);
	return {it, {}};
}

int main()
{
	auto v = load_input();

	std::cout << count_increase(v.begin(), v.end(), 1) << std::endl;
	std::cout << count_increase(v.begin(), v.end(), 3) << std::endl;

	return 0;
}
