#include "include/node.h"


using namespace std;



int main(int argc, char * argv[])
{


string circuit_path;
string output_path;

if(argc!=3)
{
	cout<<"Format Error; ./program [cell.lib] [input_circuit] [output_file_path]"<<endl;
	return 0;
}

// argv[0] is your program name
//lib_path =argv[1];
circuit_path =argv[1];
output_path =argv[2];

vector<node> circuit;
vector<string> input;
vector<string> output;
vector<string> wire;
parse_circuit( circuit_path ,circuit ,input ,output ,wire );
//cout <<"asd"<<endl;
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
for(int i=0;i<circuit.size();++i)
{
	cout << circuit[i].type << " "<< circuit[i].name << " " ;
	for(int j=0;j<circuit[i].input.size();++j)
		cout << circuit[i].input[j] <<" ";
	cout <<circuit[i].out <<endl;
}

return 0;
}
