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
	Instruction *head,*temp,*temp1;
	int regs[2048];
	int *mem=malloc(14*sizeof(int));
	head = ReadInstructionList(stdin);
	temp = head;
	int i=0;
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}

	while(temp->next!=NULL) {
		temp=temp->next;
	}
	
	if(temp->opcode!=7)
			{
				while(temp->opcode!=7){
				temp->critical=0;
				temp=temp->prev;
				}		
			}

	
	for (i=0;i<2048;i++)
		regs[i]=0;
	for(i=0;i<sizeof(mem);i++)
		mem[i]=0;
				
		while(temp!=NULL) {
		
			if(temp->opcode==0) {
						if(regs[temp->field2]==1) {
							temp->critical ='c';
							regs[temp->field2]=0;
						}
					}
					
			  else if(temp->opcode==1) {
						if(regs[temp->field3]==1) {
							regs[temp->field1]=1;
							mem[temp->field1+temp->field2]=1;
							temp->critical='c';
							regs[temp->field3]=0;
						}	
					}
											
			else if(temp->opcode==2) {
					 if(mem[temp->field2+temp->field3]==1) {
							regs[temp->field1]=1;
							temp->critical='c';
						}		
				}
				
			else if(temp->opcode==3||temp->opcode==4||temp->opcode==5||temp->opcode==6) {
				 if(regs[temp->field3]==1) {
						regs[temp->field1]=1;
						regs[temp->field2]=1;
						temp->critical ='c';
						regs[temp->field3]=0;
						}
					}
		
		else if(temp->opcode==7) {
					regs[temp->field1]=1;
					mem[temp->field1+temp->field2]=1;
					temp->critical ='c';
				}		
						
		temp=temp->prev;			
	}

	temp=head;
	
	while(temp!=NULL) {
		if(temp->critical=='c') {
		PrintInstruction(stdout,temp);
		}
		temp=temp->next;
	}
	
	free(mem);
	
	temp=head;
	while(temp!=NULL) { 
			temp=temp->next;
			free (head);
			head=temp;
		}
		
	return EXIT_SUCCESS;
}

