#include "include/node.h"

//give a current node, set the output value and output delay
bool node_judge_for_every_cell(node* current)
{
	
	if(current->type == "NOT1")
	{
		if(current->left->Y == 0)
		{
			current->A =0;
			current->Y =1;
		}
		else
		{
			current->A =1;
			current->Y =0;
		}
		current->delay = current->left->delay+1;
		return true;
	}
	
	//NAND2
	else if(current->type == "NAND2")    
	{
		//equal timing
		if(current->left->delay == current->right->delay)
		{
			if(current->left->Y == 1 && current->right->Y == 1)
			{   					
					current->A =1;
					current->B =1;
					current->Y =0;
				    current->delay = current->left->delay+1;
				
			}
			else if(current->left->Y == 0 && current->right->Y == 1)
			{
				
					current->A =0;
					current->B =1;
					current->Y =1;
				    current->delay = current->left->delay+1;
			}
			else if(current->left->Y == 1 && current->right->Y == 0)
			{
				
					current->A =1;
					current->B =0;
				    current->Y =1;
				    current->delay = current->right->delay+1;
			
			}
			else if(current->left->Y == 0 && current->right->Y == 0)
			{
					current->A =0;
					current->B =0;
					current->Y =1;
				    current->delay = current->left->delay+1;
			}
		}
		
		//left timing short
		else if( current->left->delay < current->right->delay)
		{
			if(current->left->Y == 1 && current->right->Y == 1)
			{
					current->A =1;
					current->B =1;
				    current->Y =0;
				    current->delay = current->right->delay+1;
			}
			else if(current->left->Y == 0 && current->right->Y == 1)
			{
					current->A =0;
					current->B =1;
					current->Y =1;
				    current->delay = current->left->delay+1;
			}
			else if(current->left->Y == 1 && current->right->Y == 0)
			{
					current->A =1;
					current->B =0;
				    current->Y =1;
				    current->delay = current->right->delay+1;
			}
				
			else if(current->left->Y == 0 && current->right->Y == 0)
			{
					current->A =0;
					current->B =0;
					current->Y =1;
				    current->delay = current->left->delay+1;		
			}
		}
        else if( current->left->delay > current->right->delay)
		{
			if(current->left->Y == 1 && current->right->Y == 1)
			{
					current->A =1;
					current->B =1;
					current->Y =0;
				    current->delay = current->left->delay+1;
			}
			else if(current->left->Y == 0 && current->right->Y == 1)
			{
					current->A =0;
					current->B =1;
					current->Y =1;
				    current->delay = current->left->delay+1;
			}
			else if(current->left->Y == 1 && current->right->Y == 0)
			{
					current->A =1;
					current->B =0;
				    current->Y =1;
				    current->delay = current->right->delay+1;
			}
			else if(current->left->Y == 0 && current->right->Y == 0)
			{
					current->A =0;
					current->B =0;
				    current->Y =1;
				    current->delay = current->right->delay+1;
			}
		}
	}
	
	
	//NOR2
	else if(current->type == "NOR2")    
	{
		if(current->left->delay == current->right->delay)
		{
			if(current->left->Y == 1 && current->right->Y == 1)
			{
					current->A =1;
					current->B =1;
					current->Y =0;
				    current->delay = current->left->delay+1;
			}
			else if(current->left->Y == 0 && current->right->Y == 1)
			{
					current->A =0;
					current->B =1;
				    current->Y =0;
				    current->delay = current->right->delay+1;
			}
			else if(current->left->Y == 1 && current->right->Y == 0)
			{
					current->A =1;
					current->B =0;
					current->Y =0;
				    current->delay = current->left->delay+1;
			}
			else if(current->left->Y == 0 && current->right->Y == 0)
			{
					current->A =0;
					current->B =0;
					current->Y =1;
				    current->delay = current->left->delay+1;
			}
		}
		
		
		else if( current->left->delay < current->right->delay)
		{
			if(current->left->Y == 1 && current->right->Y == 1)
			{
					current->A =1;
					current->B =1;
					current->Y =0;
				    current->delay = current->left->delay+1;
			}
			else if(current->left->Y == 0 && current->right->Y == 1)
			{
					current->A =0;
					current->B =1;
				    current->Y =0;
				    current->delay = current->right->delay+1;
			}
			else if(current->left->Y == 1 && current->right->Y == 0)
			{
					current->A =1;
					current->B =0;
					current->Y =0;
				    current->delay = current->left->delay+1;
			}
			else if(current->left->Y == 0 && current->right->Y == 0)
			{
					current->A =0;
					current->B =0;
				    current->Y =1;
				    current->delay = current->right->delay+1;
			
			}
		}
        else if( current->left->delay > current->right->delay)
		{
			if(current->left->Y == 1 && current->right->Y == 1)
			{
					current->A =1;
					current->B =1;
				    current->Y =0;
				    current->delay = current->right->delay+1;
			}
			else if(current->left->Y == 0 && current->right->Y == 1)
			{
				
					current->A =0;
					current->B =1;
				    current->Y =0;
				    current->delay = current->right->delay+1;
			}
			else if(current->left->Y == 1 && current->right->Y == 0)
			{
					current->A =1;
					current->B =0;
					current->Y =0;
				    current->delay = current->left->delay+1;
			}
			else if(current->left->Y == 0 && current->right->Y == 0)
			{
					current->A =0;
					current->B =0;
					current->Y =1;
				    current->delay = current->left->delay+1;
			}
		}
	}
}