#include "include/node.h"

bool node_judge(node* current)
{
	int critical;
	if(current->fix == 0)
		critical=0;
	else
		critical=1;
	
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
		if(current->left->delay == current->right->delay)
		{
			if(current->left->Y == 1 && current->right->Y == 1)
			{
			    	
				current->A_tf =1;
				current->B_tf =1;
				if(critical == 0 && current->A_tf == 1)
				{
					current->A =1;
					current->B =1;
					current->Y =0;
				    current->delay = current->left->delay+1;
					return true;
				}
				else if(critical == 1 && current->B_tf == 1)
				{
					current->A =1;
					current->B =1;
				    current->Y =0;
				    current->delay = current->right->delay+1;
					return true;
				}
				else
				{
					return false;
				}
				
			}
			else if(current->left->Y == 0 && current->right->Y == 1)
			{
				
				current->A_tf =1;
				current->B_tf =0;
				if(critical == 0 && current->A_tf == 1)
				{
					current->A =0;
					current->B =1;
					current->Y =1;
				    current->delay = current->left->delay+1;
					return true;
				}
				else 
				{
					return false;
				}
			}
			else if(current->left->Y == 1 && current->right->Y == 0)
			{
				
				current->A_tf =0;
				current->B_tf =1;
				if(critical == 1 && current->B_tf == 1)
				{
					current->A =1;
					current->B =0;
				    current->Y =1;
				    current->delay = current->right->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(current->left->Y == 0 && current->right->Y == 0)
			{

				current->A_tf =1;
				current->B_tf =1;
				if(critical == 0 && current->A_tf == 1)
				{
					current->A =0;
					current->B =0;
					current->Y =1;
				    current->delay = current->left->delay+1;
					return true;
				}
				else if(critical == 1 && current->B_tf == 1)
				{
					current->A =0;
					current->B =0;
				    current->Y =1;
				    current->delay = current->right->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		
		
		else if( current->left->delay < current->right->delay)
		{
			if(current->left->Y == 1 && current->right->Y == 1)
			{
				
				current->A_tf =0;
				current->B_tf =1;
				if(critical == 1 && current->B_tf == 1)
				{
					current->A =1;
					current->B =1;
				    current->Y =0;
				    current->delay = current->right->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(current->left->Y == 0 && current->right->Y == 1)
			{
			
				current->A_tf =1;
				current->B_tf =0;
				if(critical == 0 && current->A_tf == 1)
				{
					current->A =0;
					current->B =1;
					current->Y =1;
				    current->delay = current->left->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(current->left->Y == 1 && current->right->Y == 0)
			{
				
				current->A_tf =0;
				current->B_tf =1;
				if(critical == 1 && current->B_tf == 1)
				{
					current->A =1;
					current->B =0;
				    current->Y =1;
				    current->delay = current->right->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(current->left->Y == 0 && current->right->Y == 0)
			{
				
				current->A_tf =1;
				current->B_tf =0;
				if(critical == 0 && current->A_tf == 1)
				{
					current->A =0;
					current->B =0;
					current->Y =1;
				    current->delay = current->left->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
		}
        else if( current->left->delay > current->right->delay)
		{
			if(current->left->Y == 1 && current->right->Y == 1)
			{
				
				current->A_tf =1;
				current->B_tf =0;
				if(critical == 0 && current->A_tf == 1)
				{
					current->A =1;
					current->B =1;
					current->Y =0;
				    current->delay = current->left->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(current->left->Y == 0 && current->right->Y == 1)
			{
				
				current->A_tf =1;
				current->B_tf =0;
				if(critical == 0 && current->A_tf == 1)
				{
					current->A =0;
					current->B =1;
					current->Y =1;
				    current->delay = current->left->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(current->left->Y == 1 && current->right->Y == 0)
			{
				
				current->A_tf =0;
				current->B_tf =1;
				if(critical == 1 && current->B_tf == 1)
				{
					current->A =1;
					current->B =0;
				    current->Y =1;
				    current->delay = current->right->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(current->left->Y == 0 && current->right->Y == 0)
			{
				current->A_tf =0;
				current->B_tf =1;
				if(critical == 1 && current->B_tf == 1)
				{
					current->A =0;
					current->B =0;
				    current->Y =1;
				    current->delay = current->right->delay+1;
					return true;
				}
				else
				{
					return false;
				}
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
				
				current->A_tf =1;
				current->B_tf =1;
				if(critical == 0 && current->A_tf == 1)
				{
					current->A =1;
					current->B =1;
					current->Y =0;
				    current->delay = current->left->delay+1;
					return true;
				}
				else if(critical == 1 && current->B_tf == 1)
				{
					current->A =1;
					current->B =1;
				    current->Y =0;
				    current->delay = current->right->delay+1;
					return true;
				}
				else
				{
					return false;
				}
				
			}
			else if(current->left->Y == 0 && current->right->Y == 1)
			{
				
				current->A_tf =0;
				current->B_tf =1;
				if(critical == 1 && current->B_tf == 1)
				{
					current->A =0;
					current->B =1;
				    current->Y =0;
				    current->delay = current->right->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(current->left->Y == 1 && current->right->Y == 0)
			{
				
				current->A_tf =1;
				current->B_tf =0;
				if(critical == 0 && current->A_tf == 1)
				{
					current->A =1;
					current->B =0;
					current->Y =0;
				    current->delay = current->left->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(current->left->Y == 0 && current->right->Y == 0)
			{
				
				current->A_tf =1;
				current->B_tf =1;
				if(critical == 0 && current->A_tf == 1)
				{
					current->A =0;
					current->B =0;
					current->Y =1;
				    current->delay = current->left->delay+1;
					return true;
				}
				else if(critical == 1 && current->B_tf == 1)
				{
					current->A =0;
					current->B =0;
				    current->Y =1;
				    current->delay = current->right->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		
		
		else if( current->left->delay < current->right->delay)
		{
			if(current->left->Y == 1 && current->right->Y == 1)
			{
				
				current->A_tf =1;
				current->B_tf =0;
				if(critical == 0 && current->A_tf == 1)
				{
					current->A =1;
					current->B =1;
					current->Y =0;
				    current->delay = current->left->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(current->left->Y == 0 && current->right->Y == 1)
			{
				
				current->A_tf =0;
				current->B_tf =1;
				if(critical == 1 && current->B_tf == 1)
				{
					current->A =0;
					current->B =1;
				    current->Y =0;
				    current->delay = current->right->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(current->left->Y == 1 && current->right->Y == 0)
			{
				
				current->A_tf =1;
				current->B_tf =0;
				if(critical == 0 && current->A_tf == 1)
				{
					current->A =1;
					current->B =0;
					current->Y =0;
				    current->delay = current->left->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(current->left->Y == 0 && current->right->Y == 0)
			{
				
				current->A_tf =0;
				current->B_tf =1;
				if(critical == 1 && current->B_tf == 1)
				{
					current->A =0;
					current->B =0;
				    current->Y =1;
				    current->delay = current->right->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
		}
        else if( current->left->delay > current->right->delay)
		{
			if(current->left->Y == 1 && current->right->Y == 1)
			{
				
				current->A_tf =0;
				current->B_tf =1;
				if(critical == 1 && current->B_tf == 1)
				{
					current->A =1;
					current->B =1;
				    current->Y =0;
				    current->delay = current->right->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(current->left->Y == 0 && current->right->Y == 1)
			{
				
				current->A_tf =0;
				current->B_tf =1;
				if(critical == 1 && current->B_tf == 1)
				{
					current->A =0;
					current->B =1;
				    current->Y =0;
				    current->delay = current->right->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(current->left->Y == 1 && current->right->Y == 0)
			{
				
				current->A_tf =1;
				current->B_tf =0;
				if(critical == 0 && current->A_tf == 1)
				{
					current->A =1;
					current->B =0;
					current->Y =0;
				    current->delay = current->left->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(current->left->Y == 0 && current->right->Y == 0)
			{
				
				current->A_tf =1;
				current->B_tf =0;
				if(critical == 0 && current->A_tf == 1)
				{
					current->A =0;
					current->B =0;
					current->Y =1;
				    current->delay = current->left->delay+1;
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
}