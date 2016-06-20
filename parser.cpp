#include "include/node.h"

void read_line_as_token(const string &line, vector<string> &tokens)
{
	tokens.clear();
	string token;
	for(int g=0;g<line.size();g++)
	{
		if(line[g]=='(' || line[g]==')' || line[g]==',' || line[g]=='=' || line[g]==' ' || line[g]==';' || line[g]==']' \
		|| line[g]=='[' || line[g]=='/')
		{
			if(token.size()!=0 &&token[0]!=' ')
			{
				tokens.push_back(token);
				token.clear();
			}	
		}
		else
		{
			token.push_back(line[g]);
		}
	}
	if(token.size()!=0 && token[0]!=' ')
	tokens.push_back(token);
}
void parse_circuit(const string  &circuit_path ,vector<node> &circuit ,vector<string> &input ,
vector<string> &output ,vector<string> &wire )
{
	//cout<<"/////"<<endl;
	int keep=0;
	string tname;
	ifstream in(circuit_path.c_str(), ios::in);
	while(!in.eof())
	{
		vector<string> tokens;
		string line;
		getline(in,line);		
		read_line_as_token(line,tokens);		
			// collect data here
			if(tokens.size() == 0)
				continue;
			//cout<<"/////"<<endl;
			//cout << tokens[0] <<endl;
		if(tokens[0] == "input" ||  tokens[0] == "output" || tokens[0] == "wire")
		    keep =1 ;  
		//cout<<"/////"<<endl;
		if(tokens[0] == "NOT1" || tokens[0] == "NOR2" || tokens[0] == "NAND2" )
			keep = 0;
		if(keep == 2 && tname =="input")
		{
			for(int i=1;i<tokens.size();++i)
			{
				//cout << i << ":"<<tokens[i] << " ";
				input.push_back(tokens[i]);
			}
				//cout <<endl;
		}
	    else if(keep == 2 && tname =="output")
		{
			for(int i=0;i<tokens.size();++i)
				output.push_back(tokens[i]);
		}
		else if(keep == 2 && tname =="wire")
		{
			for(int i=0;i<tokens.size();++i)
				wire.push_back(tokens[i]);
		}
		
		if(keep == 1 && tokens[0] == "input")
		{
			for(int i=1;i<tokens.size();++i)
			{
				//cout << tokens[i] << " ";
			    input.push_back(tokens[i]);
			}
			//cout<<endl;
			tname ="input";
			++keep;
		}
		else if(keep == 1 && tokens[0] == "output")
		{
			for(int i=1;i<tokens.size();++i)
				output.push_back(tokens[i]);
			tname ="output";
			++keep;
		}
		else if(keep == 1 && tokens[0] == "wire")
		{
			for(int i=1;i<tokens.size();++i)
				wire.push_back(tokens[i]);
			tname ="wire";
			++keep;
		}
		
		
		if(tokens[0]=="NOT1")
		{
			node temp;
			temp.type = tokens[0];
			temp.name = tokens[1];
			temp.out = tokens[5];
			temp.input.push_back(tokens[3]);
			circuit.push_back(temp);
		}
		else if(tokens[0]=="NAND2")
		{
			node temp;
			temp.type = tokens[0];
			temp.name = tokens[1];
			temp.out = tokens[7];
			temp.input.push_back(tokens[3]);
			temp.input.push_back(tokens[5]);
			circuit.push_back(temp);
		}
		else if(tokens[0]=="NOR2")
		{
			node temp;
			temp.type = tokens[0];
			temp.name = tokens[1];
			temp.out = tokens[7];
			temp.input.push_back(tokens[3]);
			temp.input.push_back(tokens[5]);
			circuit.push_back(temp);
		}

		
	}
	in.close();
}