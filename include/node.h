#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

struct node;

void parse_circuit(const string  &circuit_path ,vector<node*> &circuit ,vector<string> &input ,
vector<string> &output ,vector<string> &wire );
void debug_parser(vector<node*> circuit, vector<string> input, vector<string> output, vector<string> wire);

typedef struct node
{
	string name;
	string type;
	string out;
	vector<string> input;
	node* left;
	node* right;
	vector<node*> parent;
}node;