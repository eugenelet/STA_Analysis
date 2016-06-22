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
void print_input(vector<node*> input_node);
void print_circuit(vector<node*> circuit);
bool node_judge(node* current);
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
	int hierarchy;
	stack<vector<node*> > path;
	vector<node*> SAT_input;
	stack<node*> BFS_stack;

	//Left input value
	bool A;
	//Right input value
	bool B;
	//Output value
	bool Y;

	// FIX: Defines critical path 
	// -1: Not set
	// 	0: A is critical path
	// 	1: B is critical path
	int fix;

	//True False value of A and B
	int A_tf;
	int B_tf;
};


class return_condition
{
public:
	return_condition();
	bool valid;
	unsigned int input_count;
};