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

void traverse_tree(vector<node*> tree_out)
{
	//cout << tree_out.size();
	for(int i = 0 ; i < tree_out.size(); i++)
	{
		node* currentNode;
		list<node*> queue;
		queue.push_back(tree_out[i]);
		cout << tree_out[i]->name << endl;
		cout << queue.size();
		while(!queue.empty())
		{
			currentNode = queue.front();
			queue.pop_front();
			cout << currentNode->out << " -> ";
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
