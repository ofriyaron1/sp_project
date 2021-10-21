#include <stdio.h>
#include <stdlib.h>
#include "spmat.h"
#include "algorithms.h"

#define IS_POSITIVE(X) ((X)>0.00001)

int main(int argc, char* argv[]) {
    FILE *input, *output;
    int nodes,M,i,temp,count,j,group_size;
    struct spmat *A;
    int *k,*row_i;
    struct group_g *arr;
    struct LinkedList *temp1;
    struct division *division;

    if(argc<3){
        fprintf( stderr, "There are missing arguments");
    }
    input=fopen(argv[1],"r");
    if (input==NULL){
        printf("\nNo file found \n");
        exit(-1);
    }
    M=0;
    fread(&nodes, sizeof(int),1,input); /* get num of nodes.*/
    if (nodes>0){
        k=(int *)malloc(sizeof(int)*nodes);
    }
    for(i=0;i<nodes;i++){
        fread(&k[i],sizeof(int),1,input);
        temp=*(k+i);
        if (IS_POSITIVE(temp)){
            M+=temp;
            fseek(input,temp*sizeof(int),SEEK_CUR);
            /*for(j=0;j<temp;j++){
                fread(&runtemp,sizeof(int),1,input);
            }*/
        }
    }
    rewind(input);
    fread(&temp, sizeof(int), 1, input);
    A=spmat_allocate_array(nodes,M);
    count=0;
    /*create the sparse matrix*/
    for (i=0;i<nodes;i++){
        A->rowptr[i]=count;
        fread(&temp, sizeof(int), 1, input);
        if (IS_POSITIVE(k[i])) {
            row_i = (int *) malloc(sizeof(int) * k[i]);
            for (j = 0; j < k[i]; j++) {
                fread(&row_i[j], sizeof(int), 1, input);
            }
            add_row(A, row_i, k[i], count);
            count += k[i];
            free(row_i);
        }
    }
    A->rowptr[A->n]=M;
    division=algorithm3 (A,k, M);
    /*Create the Output File*/
    output=fopen(argv[2],"wb");
    if (output==NULL){
        printf("\nNo output found \n");
        exit(-1);
    }
    fwrite(&division->NumOfGroups,sizeof(int),1,output);
    temp1=division->final_division;
    while (temp1!=NULL){
        arr=temp1->arr;
        group_size=arr->n;
        fwrite(&group_size,sizeof(int),1,output);
        fwrite(arr->g,sizeof(int),group_size,output);
        temp1=temp1->next;
    }
    free(k);
    sp_free(A);
    division_free(division);
    fclose(input);
    fclose(output);
    return 0;
}
