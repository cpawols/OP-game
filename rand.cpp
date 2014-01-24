#include <iostream>
#include <random>

int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);
 
	for (int n=0; n<30; ++n)
		std::cout << dis(gen) << ' ';
	std::cout << '\n';
	return 0;
}