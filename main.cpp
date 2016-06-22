#include "include/node.h"


using namespace std;



int main(int argc, char * argv[])
{


	string circuit_path;
	string output_path;
	vector<node*> tree_out;
	vector<node*> input_node;
	vector<vector<node*> > total_path;
	if(argc!=3)
	{
		cout<<"Format Error; ./program [cell.lib] [input_circuit] [output_file_path]"<<endl;
		return 0;
	}
	
	// argv[0] is your program name
	//lib_path =argv[1];
	circuit_path =argv[1];
	output_path =argv[2];
	
	vector<node*> circuit;
	vector<string> input;
	vector<string> output;
	vector<string> wire;
	parse_circuit( circuit_path ,circuit ,input ,output ,wire );
	debug_parser(circuit, input, output, wire);
	tree_out = generate_tree(circuit, input, output, input_node);
	//traverse_tree(tree_out);
	total_path = generate_path(tree_out);


	return_condition* test;
	clear_visited(circuit);
	for(int i = 0; i < total_path.size(); i++)
	{
		print( total_path[i], circuit , 1);
		test=set_input(total_path[i], total_path[i][0], total_path[i].size() - 1, 0, 0, input_node, circuit);
		for(int k = 0; k < total_path[i].size(); k++)
		{
			cout << total_path[i][k]->name << "[" << total_path[i][k]->out << "]" << "(" << total_path[i][k]->delay  << ")"<< " -> ";
		}
		cout << endl;
		cout<<" outcome: "<<test->valid<<endl;

		for(int j=0; j < input_node.size(); j++)
		{
			cout << input_node[j]->Y <<" ";
		}
		cout << endl << endl;
		clear_circuit(circuit);
	}

	
	
	//print_input(input_node);
	//print_circuit(circuit);
	
	return 0;
}
