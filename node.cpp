#include "include/node.h"

node::node()
{
	visited = false;
	visited_path = false;
	left = NULL;
	right = NULL;
	delay = -1;
	A=0;
	B=0;
	Y=0;
	fix=-1;
	A_tf=-1;
	B_tf=-1;
	hierarchy = -1;
	input_count = 0;
	valid = false;
}

return_condition::return_condition()
{
	valid = true;
	input_count = 0;
}