/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Fall 2015                                *
 *  Author: Ulrich Kremer                    *
 *  Student Version                          *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"


int main()
{
	Instruction *head,*temp;				//use temp to traverse the code
	int regs[2048];							//array to mark which registers are used in the ILOC
	int *mem=malloc(14*sizeof(int));		//array to mark which memory is used. Helps identfying critical statements
	head = ReadInstructionList(stdin);		
	temp = head;							//point to head
	int i=0;								//use as array index
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}

	while(temp->next!=NULL) {				//go to the end
		temp=temp->next;
	}
	
	if(temp->opcode!=7)						//if end statement is not an output, mark those statements dead and move to the first outputai from bottom.
			{
				while(temp->opcode!=7){
				temp->critical=0;
				temp=temp->prev;
				}		
			}

	
	for (i=0;i<2048;i++) 				//initialize arrays
		regs[i]=0;
	for(i=0;i<sizeof(mem);i++)
		mem[i]=0;
				
		while(temp!=NULL) {										//traverse the code
		
			if(temp->opcode==0) {								//LOADI
						if(regs[temp->field2]==1) {				//If the register loaded in is previously used, then this statement is critical
							temp->critical ='c';
							regs[temp->field2]=0;				//mark the register not important now
						}
					}
					
			  else if(temp->opcode==1) {						//LOADAI
						if(regs[temp->field3]==1) {				// if the register loaded is used previously 
							regs[temp->field1]=1;				// mark the other register important
							mem[temp->field1+temp->field2]=1;	//mark the memory being used in this instruction 
							temp->critical='c';					//mark it critical
							regs[temp->field3]=0;				//once the dependencies are identified, mark the dependent reg unimportant
						}	
					}
											
			else if(temp->opcode==2) {						 	//STOREAI
					 if(mem[temp->field2+temp->field3]==1) { 	//For store, see if memory we are storing in important. If not, it isnt critical
							regs[temp->field1]=1;			 	//mark the register 
							temp->critical='c';					//mark it critical
						}		
				}
				
			else if(temp->opcode==3||temp->opcode==4||temp->opcode==5||temp->opcode==6) { 	//ADD, SUB, MUL, DIV
				 if(regs[temp->field3]==1) {												//If the result register is important, others are imp
						regs[temp->field1]=1;		
						regs[temp->field2]=1;
						temp->critical ='c';
						regs[temp->field3]=0;												// mark it uncritical
						}
					}
		
		else if(temp->opcode==7) {															//OUTPUTAI
					regs[temp->field1]=1;													//mark the register outputted to
					mem[temp->field1+temp->field2]=1;										// mark the memory stored to
					temp->critical ='c';
				}		
						
		temp=temp->prev;			
	}

	temp=head;
	
	while(temp!=NULL) {					//print the critical instructions
		if(temp->critical=='c') {
		PrintInstruction(stdout,temp);
		}
		temp=temp->next;
	}
	
	free(mem);							//free the mem array
	
	temp=head;
	while(temp!=NULL) { 				//free the whole list
			temp=temp->next;
			free (head);
			head=temp;
		}
		
	return EXIT_SUCCESS;
}

