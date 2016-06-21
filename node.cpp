#include "include/node.h"

node::node()
{
	visited = false;
	visited_path = false;
	left = NULL;
	right = NULL;
	delay = -1;
	 A=-1;
	 B=-1;
	 Y=-1;
	 fix=-1;
	 A_tf=-1;
	 B_tf=-1;
	hierarchy = -1;
}

return_condition::return_condition()
{
	set_valid = true;
	input_count = 0;
}