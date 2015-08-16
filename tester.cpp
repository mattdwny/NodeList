#include <iostream>
#include "NodeList.h"


int main(int argc, char *argv[])
{
	NodeList<int> dll;

	dll.push_back(0); //1 3 8 10 5 7 9 4 6 0
	dll.push_front(1);
	dll.insert(1, 2);
	dll.insert(1, 3);
	dll.insert(3, 4);
	dll.insert(3, 5);
	dll.erase(2);
	dll.insert(4, 6);
	dll.insert(3, 7);
	dll.insert(2, 8);
	dll.insert(5, 9);
	dll.insert(3, 10);
	for(int i = 0; i < 10; ++i)
	{
		std::cout << dll.front() << std::endl;
		dll.pop_front();
	}

	std::cout << dll.size() << ':' << dll.empty() << std::endl;
	int i;
	std::cin >> i;
}