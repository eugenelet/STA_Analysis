#include "include/node.h"

uint64_t pow2(int base)
{
	uint64_t current_val = 1;
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

void clear_circuit(vector<node*> circuit)
{
	for(int i = 0; i < circuit.size(); i++)
	{
		circuit[i]->SAT_input.clear();
		circuit[i]->BFS_vector.clear();
		circuit[i]->input_count = 0;
		circuit[i]->valid = false;
	}
}



bool SAT_check(vector<node*> path)
{
	//point node to input (start from input)
	int path_count = path.size() - 1;
	node* current_node = path[path_count];

	current_node->valid = true;
	current_node->hierarchy = 0;

	//skip over input
	path_count--;


	//only terminate at path output
	do
	{
		current_node = path[path_count];
		current_node->hierarchy = path.size() - path_count - 1;
		//A BFS from current_node towards input for SAT
		//All nodes in BFS is stored on current_node (node on critical path) Stored on BFS_vector first
		//SAT_input stores all input nodes that satifies current gate input settings (excludes SAT_input of child node)

		vector<node*> BFS_vector;
		vector<node*> SAT_input;
		if(current_node->BFS_vector.size() == 0)
		{
			int current_hierarchy = path.size() - path_count - 1;
			node* BFS_current_node;
			list<node*> queue;
			queue.push_back(current_node);

			while(!queue.empty())
			{
				BFS_current_node = queue.front();
				queue.pop_front();
				BFS_current_node->visited = true;
				BFS_current_node->hierarchy = current_hierarchy;
				BFS_vector.push_back(BFS_current_node);

				//Input node has 0 input size && not set: hierarchy == -1
				if( BFS_current_node->input.size() == 0 )
				{
					SAT_input.push_back(BFS_current_node);
				}

				for(int i = 0; i < BFS_current_node->input.size(); i++)
				{
					if((i == 0) && (BFS_current_node->left != NULL) && !BFS_current_node->left->visited &&
						 ((BFS_current_node->left->hierarchy == -1) || (BFS_current_node->left->hierarchy == current_hierarchy)) )
					{
						queue.push_back(BFS_current_node->left);
					}
					else if((i == 1) && (BFS_current_node->right != NULL) && !BFS_current_node->right->visited &&
						 ((BFS_current_node->right->hierarchy == -1) || (BFS_current_node->right->hierarchy == current_hierarchy)))
					{
						queue.push_back(BFS_current_node->right);
					}
				}
			}
			current_node->BFS_vector = BFS_vector;
			clear_visited(BFS_vector);//for BFS
			//for(int i = 0; i < BFS_vector.size(); i++)
			//{
			//	cout << BFS_vector[i]->out << "(" << BFS_vector[i]->name << ")" << endl << endl;
			//}
		}
		//ELSE: current_node->BFS_vector already set


		//left with controllable inputs
		if(current_node->SAT_input.size() == 0)
		{
			current_node->SAT_input = SAT_input;
		}
		//ELSE: current_node->SAT_input already set
		
		//try all combinations
		while( current_node->input_count < pow2(current_node->SAT_input.size()) )
		{
			
			//Generate binary inputs
			int input_count_bin = current_node->input_count;

			//convert to base 2 and set input
			for(int i = 0; i < current_node->SAT_input.size(); i++)
			{
				current_node->SAT_input[i]->Y = input_count_bin % 2;
				input_count_bin >>= 1;
			}
			
			
			//Check every node on BFS for "delay" and "output"
			//Match w/ table
			for(int j = current_node->BFS_vector.size() - 1; j >= 0; j--)
			{
				node_judge_for_every_cell(current_node->BFS_vector[j]);
			}
			
			
			//Check if current combination of input satifies current node (critical node)
			//if TRUE, break LOOP and proceed with next node (done below)
			if(node_judge(current_node))
			{
				current_node->valid = true;
				break;
			}

			//FAIL!!!

			//turn current node FALSE
			current_node->valid = false;
			//current input combination fail, use next set of inputs
			current_node->input_count++;
			
		}

		//valid SAT, proceed with next node
		if(current_node->valid)
		{
			path_count--;

			//current node valid and reached the output node
			if(path_count < 0)
			{
				return true;
			}
		}

		//FAIL
		else if( (current_node->input_count == pow2(current_node->SAT_input.size())) )
		{
			//reset to 0 for next combinations
			current_node->input_count = 0;

			//Generate binary inputs
			int input_count_bin = current_node->input_count;

			//convert to base 2 and set input
			for(int i = 0; i < current_node->SAT_input.size(); i++)
			{
				current_node->SAT_input[i]->Y = input_count_bin % 2;
				input_count_bin >>= 1;
			}

			//backtrace to input
			path_count++;

			//Already beyond INPUT nodes, FALSE PATH!
			if(path_count == (path.size() - 1))
			{
				return false;
			}

			//try next combination of input
			path[path_count]->input_count++;
			path[path_count]->valid = false;

		}

	}
	while(current_node != path[0]);//reaches output node

	//if TRUE PATH, should return inside
	return false;

}


