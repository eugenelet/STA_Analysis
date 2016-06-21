#include "include/node.h"

node::node()
{
	visited = false;
	visited_path = false;
	left = NULL;
	right = NULL;
	delay = -1;
}