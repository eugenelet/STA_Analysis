#include "include/node.h"

uint64_t pow2(int base)
{
	current_val = 2;
	if(base == 0)
	{
		return 1;
	}
	else
	{
		for(int i = 0; i < base; i++)
		{
			current_val *= 2;
		}
	}
	return current_val;
}

void clear_visited(vector<node*> circuit)
{
	for(int i = 0; i < circuit.size(); i++)
	{
		circuit[i]->visited = false;
	}
}


return_condition* set_input(vector<node*> path, node* current_node, int hierarchy,
						 unsigned int input_count, int path_loc, vector<node*> input, vector<node*> circuit)
{
	//Reaches input
	if(current_node->input.size() == 0){
		//input not set not set
		if(current_node->hierarchy == -1)
		{
			current_node->hierarchy = 0;
			return_condition* current_outcome  = new return_condition;
			current_outcome->valid = true;
			return current_outcome;
		}
		// input already set
		else if(current_node->hierarchy == 0)
		{
			return_condition* current_outcome = new return_condition;
			current_outcome->valid = false;
			return current_outcome;
		}
	}


	//return from lower hierarchy
	return_condition* outcome_from_child = new return_condition;

	//recurse from output to input
	if(path_loc < path.size())
	{
		path_loc++;
		outcome_from_child = set_input(path, path[path_loc], hierarchy-1, 0, path_loc, input, circuit);
	}

	//good return proceed with other node (non-critical node)
	if(outcome_from_child->valid)
	{
		//A BFS from current_node towards input for SAT
		//All nodes in BFS is stored on current_node (node on critical path) Stored on BFS_stack first
		//SAT_input stores all input nodes that satifies current gate input settings (excludes SAT_input of child node)

		clear_visited(circuit);//for BFS

		stack<node*> BFS_stack;
		vector<node*> SAT_input;
		if(current_node->BFS_vector.size() == 0)
		{
			node* BFS_current_node;
			list<node*> queue;
			queue.push_back(current_node);

			while(!queue.empty())
			{
				BFS_current_node = queue.front();
				queue.pop_front();
				BFS_current_node->visited == true;
				BFS_stack.push(BFS_current_node);

				//Input node has 0 input size
				if((BFS_current_node->input.size() == 0) && !BFS_current_node->visited)
				{
					SAT_input.push_back(current_node);
				}

				for(int i = 0; i < BFS_current_node->input.size(); i++)
				{
					if((i == 0) && (BFS_current_node->left != NULL) && !BFS_current_node->visited)
					{
						queue.push_back(BFS_current_node->left);
					}
					else if((i == 1) && (BFS_current_node->right != NULL) && !BFS_current_node->visited)
					{
						queue.push_back(BFS_current_node->right);
					}
				}
			}
		}
			
		current_node->BFS_stack = BFS_stack;
		current_node->SAT_input = SAT_input;//not done yet

		vector<node*> valid_SAT_input;
		for(int i=0;i<SAT_input.size();i++)
		{
			//input not on critical path not set yet
			if(SAT_input[i]->hierarchy == -1)
			{
				//set input node's hierarchy to hierarchy on the head of BFS
				SAT_input[i]->hierarchy = hierarchy;
				
				valid_SAT_input.push_back( input_pointer_vector[i] );
			}
		}
	
		

		//left with controllable inputs
		current_node->SAT_input = valid_SAT_input;
		
		
		//Generate binary inputs
		int input_count_bin = input_count;

		
		//try all combinations
		while(1)
		{
			
			//convert to base 2 and set input
			for(int i = 0; i < current_node->SAT_input.size(); i++)
			{
				current_node->SAT_input[i] = input_count_bin % 2;
				input_count_bin >>= 1;
			}
			
			
			//Check every node on BFS for "delay" and "output"
			//Match w/ table
			node* current_BFS_node;
			for(int j = 0; j < BFS_stack.size(); j++)
			{
				current_BFS_node = BFS_stack.top();
				BFS_stack.pop();
				//visit from INPUT to OUTPUT
				if(current_node->type == "NOT1")
				{
					current_node->delay = current_node->left->delay + 1;
					current_node->Y= ~current_node->left->Y;
				}
				else if(current_node->type = "NAND2")
				{
					node *min_delay_node, *max_delay_node;
					if(current_node->left->delay > current_node->right->delay)
					{
						min_delay_node = current_node->right;
					}
					else
					{
						min_delay_node = current_node->left;
					}

					if(min_delay_node->Y == 0)//controlling
					{
						current_node->delay = min_delay_node->delay + 1;
						current_node->Y = 1;
					}
					else
					{
						current_node->delay = max_delay_node->delay + 1;
						current_node->Y = ~(current_node->left->Y & current_node->right->Y);//output of NAND
					}
					//還沒考慮同時記得考慮
				}
				else if(current_node->type = "NOR2")
				{
					node *min_delay_node, *max_delay_node;
					if(current_node->left->delay > current_node->right->delay)
					{
						min_delay_node = current_node->right;
					}
					else
					{
						min_delay_node = current_node->left;
					}

					if(min_delay_node->Y == 1)//controlling
					{
						current_node->delay = min_delay_node->delay + 1;
						current_node->Y = 0;
					}
					else{
						current_node->delay = max_delay_node->delay + 1;
						current_node->Y = ~(current_node->left->Y | current_node->right->Y);//output of NOR
					}
					//還沒考慮同時記得考慮
				}
			}
			
			
			//Check if current combination of input satifies current node (critical node)
			if(node_judge(current_node))
			{
				return_condition* current_outcome = new return_condition;
				current_outcome->valid = true;
				current_outcome->input_count = input_count;
				return current_outcome;
			}
		
			//use next set of inputs
			input_count++;
			
		
			//If all combinations tried, jump to lower hierarchy
			return_condition* next_input_set;

			//All input combinations tried, reset lower hierarchy
			if( input_count == pow2(input.size()) )
			{
				path_loc++;
				next_input_set = set_input(path, path[path_loc], hierarchy-1, input_count, path_loc, input, circuit);
				if(!next_input_set->valid)
				{
					return_condition* current_outcome  = new return_condition;
					current_outcome->valid = false;
					return current_outcome;//return to higher hierarchy, report failure
				}
				else 
				{
					//SUCCESS, start with new set of inputs
					input_count = 0;
				}
			}
		}
	}
	
	//Lower hierarchy tried all combinations and fail
	else
	{
		return_condition* current_outcome = new return_condition;
		current_outcome->valid = false;
		return current_outcome;
	}
}