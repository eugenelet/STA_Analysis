#include "include/node.h"

node::node()
{
	visited = false;
	visited_path = false;
	left = NULL;
	right = NULL;
	delay = -1;
	hierarchy = -1;
}

return_condition::return_condition()
{
	set_valid = true;
	input_count = 0;
}