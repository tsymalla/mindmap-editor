#include "graph.hpp"
#include <iostream>

Graph _graph;

int main()
{
	_graph.addRootVertex("Test");

	auto node = _graph.getRootVertexByName("Test");
	auto test2 = node->addSibling("Test2");
	test2->addSibling("Test2.1");
	test2->addSibling("Test2.2");
	test2->addSibling("Test2.3");

	auto test3 = node->addSibling("Test3");
	auto test31 = test3->addSibling("Test3.1");
	test3->addSibling("Test3.2");
	test31->addSibling("Test3.1.1");
	test31->addSibling("Test3.1.2");

	std::cout << _graph << std::endl;
	std::cin.get();
	return 0;
}