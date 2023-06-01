//partner pk38, kaiyiyu2

#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

//this program stores sparse matrices into a linked list, by reading them from a file. This is done in
//load tuples, which calls set_tuple and in turn add_node/remove_node. Add and remove node are both recursive functions,
//traversing through the list to add or delete a node from the ordered list while keeping the rest of the 
//structure intact. The program also saves matrices to a file, through save_tuple, and adds two matrices together
//using add_tuples. The matrices are then removed from memory using destroy_tuples

//headers for helper functions
void add_node(sp_tuples_node **head, int newrow, int newcol, double newdata, sp_tuples* matrix);
void remove_node(sp_tuples_node **head, int oldrow, int oldcol, sp_tuples* matrix);


sp_tuples * load_tuples(char* input_file)
{
    //open file and read dimensions of matrix
    FILE * matrix_file = fopen(input_file,"r");
    int nrows,ncols;
    char newline;
    fscanf(matrix_file, "%d %d%c", &nrows, &ncols, &newline);

    //create sp tuples item and assign dimensions
    sp_tuples * matrix_object = malloc(sizeof(sp_tuples));
    matrix_object->m = nrows;
    matrix_object->n = ncols;
    matrix_object->nz = 0;
    matrix_object->tuples_head = NULL;
    
    int x,y;
    double value;
    

    //read file line by line and update matrix with new information
    while(fscanf(matrix_file,"%d %d %lf%c", &x,&y,&value,&newline) != EOF){
	set_tuples(matrix_object,x,y,value);
    }    

    //close file and return
    fclose(matrix_file);    
    return matrix_object;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    //traverse through list until node with row/col found, then return value
    sp_tuples_node * head = mat_t->tuples_head;
    while(head != NULL){
	if(head->row == row && head->col == col){
		return head->value;
	}
	head = head->next;
    }
    //if end of node reached but no node found, means value is 0
    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    if (value == 0){
	//remove node
	remove_node(&(mat_t->tuples_head),row,col,mat_t);
    } else {
	//add node
	add_node(&(mat_t->tuples_head),row,col,value,mat_t);
    }
    return;
}
void add_node(sp_tuples_node **head, int newrow, int newcol, double newdata, sp_tuples* matrix){
    sp_tuples_node *current = *head;
    
    //insert new node, update list
    if (current == NULL || (newrow < (current->row)) || (newrow == current->row && newcol < current->col)){
	sp_tuples_node *temp = (sp_tuples_node*) malloc(sizeof(sp_tuples_node));
	temp->row = newrow;
	temp->col = newcol;
	temp->value = newdata;
	temp->next = current;
	*head = temp;
	//update non-zero values
	matrix->nz = (matrix->nz) + 1;
	return;
    }

    //replace data if node already exists
    if (newrow == (current->row) && newcol == (current->col)){
	current->value = newdata;
	return;
    }
    
    //traverse the remaining list
    return add_node(&(current->next),newrow,newcol,newdata,matrix);
    
}

void remove_node(sp_tuples_node **head, int oldrow, int oldcol, sp_tuples* matrix){
    
    sp_tuples_node *current = *head;

    //empty list or matching node not found
    if (current == NULL || (oldrow < (current->row)) || ((oldrow == current->row) && (oldcol < current->col))){
	return;
    }
    //current node is match, update ptr and delete node
    if (oldrow == (current->row) && oldcol == (current->col)){
	*head = current->next;
	free(current);
	(matrix->nz) = (matrix->nz) - 1;
	return;
    }

    //traverse remaining list
    return remove_node(&(current->next), oldrow, oldcol, matrix);
}


void save_tuples(char * file_name, sp_tuples * mat_t)
{
	//open file, update dimensions
	FILE * matrix_file = fopen(file_name,"w+");
	sp_tuples_node * headp = mat_t->tuples_head;
	fprintf(matrix_file,"%d %d\n",mat_t->m,mat_t->n);

	//read through linked list node by node and read contents to file
	int counter = mat_t->nz;
	while(counter > 0){
		fprintf(matrix_file,"%d %d %lf\n",headp->row,headp->col,headp->value);
		headp = headp->next;
		counter--;

	}
	//close file
	fclose(matrix_file);
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    //if matrices have different dimensions return null
    if(matA->m != matB->m || matA->n != matB->n){
	return NULL;
    }
    //if same dimension initialize matrix with dimensions and initial nz = 0
    sp_tuples * matC  = malloc(sizeof(sp_tuples));
    matC->m = matA->m;
    matC->n = matA->n;
    matC->nz = 0;
    matC->tuples_head = NULL;
    
    //traverse linked list of matrix A and add to C
    sp_tuples_node * headp = matA->tuples_head;
    while(headp != NULL){
	int row = headp->row;
	int col = headp->col;
	set_tuples(matC, row, col,gv_tuples(matC,row,col)+gv_tuples(matA,row,col));
	headp = headp->next;
    }

    //traverse linked list of matrix B and add to C
    headp = matB->tuples_head;
    while(headp != NULL){
	int row = headp->row;
	int col = headp->col;
	set_tuples(matC, row, col,gv_tuples(matC,row,col)+gv_tuples(matB,row,col));
	headp = headp->next;
    }

    return matC;
    
    
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    //if incorrect dimensions, return invalid
    if(matA->n != matB->m){
	return NULL;
    }

    //if proper dimension initialize matrix with dimensions and initial nz = 0
    sp_tuples * matC  = malloc(sizeof(sp_tuples));
    matC->m = matA->m;
    matC->n = matB->n;
    matC->nz = 0;
    matC->tuples_head = NULL;

    //traverse through A
    sp_tuples_node * headp = matA->tuples_head;
    while(headp != NULL){
	int iA = headp->row;
	int jA = headp->col;
	//traverse through matrix B and multiply with those rows in B that are equal to the columns in A
        sp_tuples_node * headB = matB->tuples_head;
        while(headB != NULL){
		int iB = headB->row;
		int jB = headB->col;
		if(iB == jA){
			set_tuples(matC, iA, jB,gv_tuples(matC,iA,jB)+(gv_tuples(matA,iA,jA)*gv_tuples(matB,iB,jB)));
		}
		headB = headB->next;
	    }
	headp = headp->next;
    }

    return matC;

}


	
void destroy_tuples(sp_tuples * mat_t){
    sp_tuples_node * head = mat_t->tuples_head;
    sp_tuples_node * temp;

    //iterate through nodes and free them one by one from memory
    while(head != NULL){
	temp = head->next;
        free(head);
        head = temp;
    }
    //free matrix from memory
    free(mat_t);
    return;
} 