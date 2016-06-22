#include "include/node.h"

uint64_t pow2(int base)
{
	uint64_t current_val = 2;
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
	if(current_node->input.size() == 0)
	{
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

	path[path_loc]->hierarchy = hierarchy;
	path_loc++;

	//recurse from output to input
	if(path_loc < path.size())
	{
		outcome_from_child = set_input(path, path[path_loc], hierarchy-1, input_count, path_loc, input, circuit);
	}

	//good return proceed with other node (non-critical node)
	if(outcome_from_child->valid)
	{
		//A BFS from current_node towards input for SAT
		//All nodes in BFS is stored on current_node (node on critical path) Stored on BFS_vector first
		//SAT_input stores all input nodes that satifies current gate input settings (excludes SAT_input of child node)


		vector<node*> BFS_vector;
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
				BFS_current_node->visited = true;
				BFS_vector.push_back(BFS_current_node);


				//Input node has 0 input size && not set: hierarchy == 0
				if((BFS_current_node->input.size() == 0) && (BFS_current_node->hierarchy  == -1) )
				{
					SAT_input.push_back(current_node);
					BFS_current_node->hierarchy = hierarchy;
				}

				for(int i = 0; i < BFS_current_node->input.size(); i++)
				{
					if((i == 0) && (BFS_current_node->left != NULL) && !BFS_current_node->left->visited &&
						 (BFS_current_node->left->hierarchy  == -1))
					{
						BFS_current_node->left->hierarchy = hierarchy;
						queue.push_back(BFS_current_node->left);
					}
					else if((i == 1) && (BFS_current_node->right != NULL) && !BFS_current_node->right->visited &&
						 (BFS_current_node->right->hierarchy  == -1))
					{
						BFS_current_node->right->hierarchy = hierarchy;
						queue.push_back(BFS_current_node->right);
					}
				}
			}
			current_node->BFS_vector = BFS_vector;
			clear_visited(BFS_vector);//for BFS
		}
		else
		{
			BFS_vector = current_node->BFS_vector;
		}

			

		//vector<node*> valid_SAT_input;
		//for(int i=0;i<SAT_input.size();i++)
		//{
		//	//input not on critical path not set yet
		//	if(SAT_input[i]->hierarchy == -1)
		//	{
		//		//set input node's hierarchy to hierarchy on the head of BFS
		//		SAT_input[i]->hierarchy = hierarchy;
		//		
		//		valid_SAT_input.push_back( SAT_input[i] );
		//	}
		//}
	
		

		//left with controllable inputs
		if(current_node->SAT_input.size() == 0)
		{
			current_node->SAT_input = SAT_input;
		}
		
		
		//Generate binary inputs
		int input_count_bin = input_count;

		
		//try all combinations
		while(1)
		{
			
			//convert to base 2 and set input
			for(int i = 0; i < current_node->SAT_input.size(); i++)
			{
				current_node->SAT_input[i]->Y = input_count_bin % 2;
				input_count_bin >>= 1;
			}
			
			
			//Check every node on BFS for "delay" and "output"
			//Match w/ table
			node* current_BFS_node;
			for(int j = BFS_vector.size() - 1; j >= 0; j--)
			{
				current_BFS_node = BFS_vector[j];
				//visit from INPUT to OUTPUT
				if(current_BFS_node->type == "NOT1")
				{
					current_BFS_node->delay = current_BFS_node->left->delay + 1;
					current_BFS_node->Y= ~current_BFS_node->left->Y;
				}
				else if(current_BFS_node->type == "NAND2")
				{
					node *min_delay_node, *max_delay_node;
					if(current_BFS_node->left->delay > current_BFS_node->right->delay)
					{
						min_delay_node = current_BFS_node->right;
					}
					else
					{
						min_delay_node = current_BFS_node->left;
					}

					if(min_delay_node->Y == 0)//controlling
					{
						current_BFS_node->delay = min_delay_node->delay + 1;
						current_BFS_node->Y = 1;
					}
					else
					{
						current_BFS_node->delay = max_delay_node->delay + 1;
						current_BFS_node->Y = ~(current_BFS_node->left->Y & current_BFS_node->right->Y);//output of NAND
					}
					//還沒考慮同時記得考慮
				}
				else if(current_BFS_node->type == "NOR2")
				{
					node *min_delay_node, *max_delay_node;
					if(current_BFS_node->left->delay > current_BFS_node->right->delay)
					{
						min_delay_node = current_BFS_node->right;
					}
					else
					{
						min_delay_node = current_BFS_node->left;
					}

					if(min_delay_node->Y == 1)//controlling
					{
						current_BFS_node->delay = min_delay_node->delay + 1;
						current_BFS_node->Y = 0;
					}
					else{
						current_BFS_node->delay = max_delay_node->delay + 1;
						current_BFS_node->Y = ~(current_BFS_node->left->Y | current_BFS_node->right->Y);//output of NOR
					}
					//還沒考慮同時記得考慮
				}
			}
			
			
			//Check if current combination of input satifies current node (critical node)
			if(node_judge(current_node))
			{
				cout << "TESTTTT" << endl;
				return_condition* current_outcome = new return_condition;
				current_outcome->valid = true;
				current_outcome->input_count = input_count;
				return current_outcome;
			}
		
			//use next set of inputs
			cout <<  "INPUT_COUNT: "<< input_count << endl;
			cout << "HIERARCHY: " << hierarchy << endl;
			input_count++;
			
		
			//If all combinations tried, jump to lower hierarchy
			return_condition* next_input_set;

			//All input combinations tried, reset lower hierarchy
			if( input_count == pow2(SAT_input.size()) )
			{
				path_loc++;
				if(path_loc < path.size())
				{
					next_input_set = set_input(path, path[path_loc], hierarchy-1, input_count, path_loc, input, circuit);
				}
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