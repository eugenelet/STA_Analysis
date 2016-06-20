#include "include/node.h"

vector<node*> generate_tree(vector<node*> circuit, vector<string> input, vector<string> output)
{
	vector<node*> out_nodes;
	for(int i = 0; i < output.size(); i++){
		for(int j = 0; j < circuit.size(); j++)
		{
			//cout << circuit[j]->name << endl;
			if(output[i] == circuit[j]->out)
			{
				out_nodes.push_back(circuit[j]);
			}
		}
	}

	for(int i = 0; i < out_nodes.size(); i++){
		node* currentNode;
		list<node*> queue;
		queue.push_back(out_nodes[i]);
		while(!queue.empty())
		{
			currentNode = queue.front();
			queue.pop_front();
			currentNode->visited = true;
			for(int k = 0; k < currentNode->input.size(); k++)
			{
				if(k == 0)
				{
					int l = 0;
					for(; l < circuit.size(); l++)
					{
						if(currentNode->input[k] == circuit[l]->out)
						{
							currentNode->left = circuit[l];
							//multiple fan-out point
							if(!currentNode->left->visited){
								queue.push_back(circuit[l]);
								break;
							}
							else
								break;
								
						}
						if( l == circuit.size() ) // node is an input
						{
							node* dummyNode = new node;
							dummyNode->name = currentNode->input[k];
							dummyNode->type = "INPUT";
							dummyNode->out = currentNode->input[k];
							currentNode->left = dummyNode;
						}
							
					}
				}
				else if(k == 1)
				{
					int l = 0;
					for(; l < circuit.size(); l++)
					{
						if(currentNode->input[k] == circuit[l]->out)
						{
							currentNode->right = circuit[l];
							//multiple fan-out point
							if(!currentNode->right->visited){
								queue.push_back(circuit[l]);
								break;
							}
							else
								break;
						}
						if( l == circuit.size() ) //node is an input
						{
							node* dummyNode = new node;
							dummyNode->name = currentNode->input[k];
							dummyNode->type = "INPUT";
							dummyNode->out = currentNode->input[k];
							currentNode->right = dummyNode;
						}
							
					}
				}
			}
		}
	}

	return out_nodes;
}