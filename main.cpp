#include "include/node.h"


using namespace std;



int main(int argc, char * argv[])
{


	string circuit_path;
	string output_path;
	vector<node*> tree_out;
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
	tree_out = generate_tree(circuit, input, output);
	traverse_tree(tree_out);
	
	return 0;
}
