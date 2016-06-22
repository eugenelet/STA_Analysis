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
class return_condition;

void parse_circuit(const string  &circuit_path ,vector<node*> &circuit ,vector<string> &input ,
vector<string> &output ,vector<string> &wire );
void debug_parser(vector<node*> circuit, vector<string> input, vector<string> output, vector<string> wire);
vector<node*> generate_tree(vector<node*> &circuit, vector<string> input, vector<string> output, vector<node*> &input_node);
void traverse_tree(vector<node*> tree_out);
vector<vector<node*> > generate_path(vector<node*> tree_out);
void print_input(vector<node*> input_node);
void print_circuit(vector<node*> circuit);
bool node_judge(node* current);
void print( vector<node*> path,vector<node*> &circuit ,int rf);
//return_condition* set_input(vector<node*> path, node* current_node, int hierarchy,
//						 unsigned int input_count, int path_loc, vector<node*> input, vector<node*> circuit);
void clear_visited(vector<node*> circuit);
void clear_circuit(vector<node*> circuit);
bool SAT_check(vector<node*> path);
bool node_judge_for_every_cell(node* current);
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
	vector<node*> BFS_vector;
	unsigned int input_count;
	bool valid;

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