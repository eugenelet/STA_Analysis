#include "include/node.h"

void debug_parser(vector<node*> circuit,
	vector<string> input,
	vector<string> output,
	vector<string> wire)
{
	cout <<" input:" <<endl;
	for(int i=0;i<input.size();++i)
	{
		cout<<input[i]<<" ";
	}
	cout<<endl;
	cout <<" output:" <<endl;
	for(int i=0;i<output.size();++i)
	{
		cout<<output[i]<<" ";
	}
	cout<<endl;
	cout <<" wire:" <<endl;
	for(int i=0;i<wire.size();++i)
	{
		cout<<wire[i]<<" ";
	}
	cout << endl;
	cout << "node:" <<endl;
	cout << circuit.size() << endl;
	for(int i=0;i<circuit.size();++i)
	{
		cout << circuit[i]->type << " "<< circuit[i]->name << " " ;
		for(int j=0;j<circuit[i]->input.size();++j)
			cout << circuit[i]->input[j] <<" ";
		cout <<circuit[i]->out <<endl;
	}
}

void print_path(vector<vector<node*> > total_path)
{
	for(int i = 0; i < total_path.size(); i++)
	{
		for(int j = 0; j < total_path[i].size(); j++)
		{
			cout << total_path[i][j]->out << " ( " << total_path[i][j]->type << " ) <- ";
		}
		cout << endl;
	}
}

vector<vector<node*> > generate_path(vector<node*> tree_out)
{
	vector<vector<node*> > total_path;
	for(int i = 0 ; i < tree_out.size(); i++)
	{
		node* currentNode;
		stack<node*> stack;
		if(tree_out[i]->input.size() == 2){
			vector<node*> path;
			path.push_back(tree_out[i]);
			tree_out[i]->path.push(path);
		}
		
		stack.push(tree_out[i]);
		vector<node*> path_from_out;
		while(!stack.empty())
		{
			currentNode = stack.top();
			stack.pop();
			path_from_out.push_back(currentNode);
			if(currentNode->input.size() == 2){
				vector<node*> path_till_now = path_from_out;
				currentNode->left->path.push(path_till_now);				
				currentNode->right->path.push(path_till_now);				
			}
			if(currentNode->input.size() == 0)
			{
				vector<node*> single_path = path_from_out;
				total_path.push_back(single_path);
				if((currentNode->left == NULL) && (currentNode->right == NULL))
				{
					if(!stack.empty())
					{
						if(!stack.top()->path.empty())
						{	
							path_from_out = stack.top()->path.top();
							stack.top()->path.pop();
						}
					}
				}
				continue;
			}
			for(int k = 0; k < currentNode->input.size(); k++)
			{
					if((k == 0) && (currentNode->left != NULL))
					{
						stack.push(currentNode->left);
							
					}
					else if((k == 1) && (currentNode->right != NULL))
					{
						stack.push(currentNode->right);
					}
					
			}
		}
	}

	print_path(total_path);
	return total_path;
}

void traverse_tree(vector<node*> tree_out)
{
	cout << tree_out.size() << endl;
	for(int i = 0 ; i < tree_out.size(); i++)
	{
		node* currentNode;
		list<node*> queue;
		queue.push_back(tree_out[i]);
		//cout << tree_out[i]->name << endl;
		//cout << queue.size();
		while(!queue.empty())
		{
			currentNode = queue.front();
			queue.pop_front();
			cout << "CELL: " << currentNode->name << endl;
			cout << currentNode->out << endl;
			for(int k = 0; k < currentNode->input.size(); k++)
			{
				if((k == 0) && (currentNode->left != NULL))
				{
					queue.push_back(currentNode->left);
						
				}
				else if((k == 1) && (currentNode->right != NULL))
				{
					queue.push_back(currentNode->right);
				}
			}
		}
		cout << endl;
	}

}
