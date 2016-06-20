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
	