#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>
#include <queue>
#include <list>
#include <stack>

using namespace std;

class node;

void parse_circuit(const string  &circuit_path ,vector<node*> &circuit ,vector<string> &input ,
vector<string> &output ,vector<string> &wire );
void debug_parser(vector<node*> circuit, vector<string> input, vector<string> output, vector<string> wire);
vector<node*> generate_tree(vector<node*> &circuit, vector<string> input, vector<string> output, vector<node*> &input_node);
void traverse_tree(vector<node*> tree_out);
vector<vector<node*> > generate_path(vector<node*> tree_out);
void print( vector<node*> path,vector<node*> &circuit ,int rf);
void print_input(vector<node*> input_node);
void print_circuit(vector<node*> circuit);

class node
{
public:
	node();
	string name;
	string type;
	string out;
	vector<string> input;
	node* left;
	node* right;
	vector<node*> parent;
	bool visited;
	bool visited_path;
	int delay;
	stack<vector<node*> > path;
	int A;
	int B;
	int Y;
	int fix;
	
};
