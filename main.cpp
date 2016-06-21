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
	/*print (total_path[2],circuit,1);
	for(int i=0;i<circuit.size();++i)
	{
		cout << circuit[i]->name <<" "<<circuit[i]->type <<" fix="<<circuit[i]->fix <<" A="<<circuit[i]->A\
		<<" B="<<circuit[i]->B <<" Y="<<circuit[i]->Y <<endl;
		for(int j=0;j<circuit[i]->parent.size();++j)
			cout<<" parant:" << circuit[i]->parent[j]->name<<endl;
	}*/
	node U1;
	node U2;
	node U3;
	U1.name = "U1";
	//U1.type = "NAND2";
	U1.left=&U2;
	U1.right=&U3;
	U1.fix=1;
	//U2.delay=1;
	//U2.Y=0;
	//U3.delay=1;
	//U3.Y=1;
	node* pot=&U1;
	bool jj;
    for(int i=0;i<2;++i)
	{
		if(i==0)
			U1.type = "NAND2";
		if(i==1)
			U1.type = "NOR2";
		for(int j=0;j<3;++j)
		{
			if(j==0)
			{
				U2.delay=1;
				U3.delay=1;
			}
			if(j==1)
			{
				U2.delay=1;
				U3.delay=2;
			}
			if(j==2)
			{
				U2.delay=2;
				U3.delay=1;
			}
			for(int k=0;k<4;++k)
			{
				if(k==0)
				{
					U2.Y=1;
					U3.Y=1;
				}
				if(k==1)
				{
					U2.Y=1;
					U3.Y=0;
				}
				if(k==2)
				{
					U2.Y=0;
					U3.Y=1;
				}
				if(k==3)
				{
					U2.Y=0;
					U3.Y=0;
				}
				jj=node_judge(pot);
				cout<<"critical "<<U1.fix<<endl;
	            cout<<" A delay: "<<U2.delay<<" value: "<<U2.Y<<endl;
	            cout<<" B delay: "<<U3.delay<<" value: "<<U3.Y<<endl;
	            cout<< "tyep: "<< U1.type<<" A: "<< U1.A <<" B: "<< U1.B<<" Y: "<< U1.Y<<" delay: "<<U1.delay<<endl;
	            cout<< "resault: "<< jj<<endl<<endl;
				
			}
		}
	}
	            for(int i=0;i<2;++i)
				{
					U1.type="NOT1";
					U2.delay=0;
					if(i==0)
						U2.Y=0;
					if(i==1)
						U2.Y=1;
					jj=node_judge(pot);
					cout<<"critical "<<U1.fix<<endl;
	                cout<<" A delay: "<<U2.delay<<" value: "<<U2.Y<<endl;
	                //cout<<" B delay: "<<U3.delay<<" value: "<<U3.Y<<endl;
	                cout<< "tyep: "<< U1.type<<" A: "<< U1.A <<" Y: "<< U1.Y<<" delay: "<<U1.delay<<endl;
	                cout<< "resault: "<< jj<<endl<<endl;
				}
	            
	
	//cout<<"/////"<<endl;
	
     //bool jj=node_judge(pot);
	
	
	print_input(input_node);
	print_circuit(circuit);
	
	return 0;
}
