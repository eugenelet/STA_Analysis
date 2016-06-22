#include "include/node.h"

void print( vector<node*> path,vector<node*> &circuit ,int rf)
{
	int jr=rf;
	node* track;
	for(int i=0;i<circuit.size();++i)
	{
		circuit[i]->A=0;
		circuit[i]->B=0;
		circuit[i]->Y=0;
		circuit[i]->fix=-1;
		circuit[i]->hierarchy = -1;
		circuit[i]->delay = 0;
		if(circuit[i]->name == path[0]->name)
			track = circuit[i];
	}
	for(int i=0;i<path.size();i++)
	{
		track->Y=jr;
		for(int j=0;j<track->parent.size();++j)
		{
			if(track->parent[j]->left->name == track->name)
			{
				track->parent[j]->A =jr;
				track->parent[j]->fix =0;
			}
				
			else if(track->parent[j]->right->name == track->name)
			{
				track->parent[j]->B =jr;
				track->parent[j]->fix =1;
			}
			
			//cout << track->parent[j]->name <<" A" << track->parent[j]->A <<" B" << track->parent[j]->B\
             //     << " fix" << track->parent[j]->fix <<endl;			
		}
		if(track->input.size() == 0)
		{
			break;
		}	
		if(jr == 1)
			jr=0;
		else
			jr=1;
		if(track->type == "NOT1")
		{
			track = track->left;
		}	
		else if(path[i+1]->name == track->left->name)
		{
			track = track->left;
		}
		else if(path[i+1]->name == track->right->name)
		{
			track = track->right;
		}
		
	}
		
	
}
