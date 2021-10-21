#include "algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define IS_POSITIVE(X) ((X)>0.00001)

/*Algorithm3*/
struct division* algorithm3(struct spmat *A, int *k, int M){
    int i,NumOfGroups,ind,count=0;
    int *arr,*arr1;
    struct group_g *g,*curr_g,*g1, *g2, *single_group;
    struct LinkedList *P,*O,*temp,*currlink, *currlink1,*currlink2,*singelton;
    struct gdiv *temp_division;
    struct division *division;
    division=(struct division *)malloc(sizeof(struct division));
    for(i=0;i<A->n;i++){
        if(k[i]>0){
            count++;
        }
    }
    arr=(int *)malloc(sizeof(int)*count);
    ind=0;
    NumOfGroups=0;
    O=NULL;
    for(i=0;i<A->n;i++){
        if (k[i]>0){
            arr[ind]=i;
            ind++;
        }
        else{
            singelton=(struct LinkedList *)malloc(sizeof(struct LinkedList));
            arr1=(int *)malloc(sizeof(int));
            arr1[0]=i;
            single_group=(struct group_g *)malloc(sizeof(struct group_g));
            single_group->g=arr1;
            single_group->n=1;
            singelton->arr=single_group;
            singelton->next=O;
            O=singelton;
            NumOfGroups++;

        }
    }
    g=(group_g *)malloc (sizeof(group_g));
    g->g=arr;
    g->n=count;
    P= (struct LinkedList *)malloc(sizeof(struct LinkedList));
    P->arr=g;
    P->next=NULL;

    while (P!=NULL){
        temp=P;
        curr_g=P->arr;
        P=P->next;
        free(temp);
        temp_division=algorithm2(A,curr_g,k,M);
        g1=temp_division->g1;
        g2=temp_division->g2;
        if (g1==NULL ||g2==NULL){
            currlink= (struct LinkedList *)malloc(sizeof(struct LinkedList));
            currlink->arr=curr_g;
            currlink->next=O;
            O=currlink;
            NumOfGroups++;
        }
        else{
            currlink1 = (struct LinkedList *)malloc(sizeof(struct LinkedList));
            currlink1->arr = g1;
            currlink2 = (struct LinkedList *)malloc(sizeof(struct LinkedList));
            currlink2->arr = g2;
            if (g1->n==1) {
                currlink1->next = O;
                O = currlink1;
                NumOfGroups++;
            }
            else {
                currlink1->next = P;
                P= currlink1;
            }
            if (g2->n==1) {
                currlink2->next = O;
                O = currlink2;
                NumOfGroups++;
            }
            else {
                currlink2->next = P;
                P= currlink2;
            }
        }
    }
    division->NumOfGroups=NumOfGroups;
    division->final_division=O;
    /*free(arr);*/
    ll_free(P);
    free(temp_division);
    return division;
}

/*Algorithm 2*/
struct gdiv* algorithm2 (struct spmat *A,struct group_g *g, int *k, int M){
    int i,g1size,g2size,g1point,g2point;
    double *s, *vector;
    double eigen,temp;
    struct group_g *g1, *g2;
    struct gdiv* division;

    vector=(double*)malloc(sizeof(double)*g->n);
    /*creating vector b0*/
    srand(time(NULL));
    for(i = 0; i < g->n; i++){
        vector[i] = (double) rand() / RAND_MAX;
    }
    /* Normalize vector*/
    vectorNorm(g->n, vector);
    eigen=powerIteration(A,g,vector,k,M);
    division=(gdiv *)malloc(sizeof(gdiv));
    if (!(IS_POSITIVE(eigen))){
        division->g1=g;
        division->g2=NULL;
        free(vector);
        return division;
    }
    s=(double *)malloc(sizeof(double)*g->n);
    for (i=0;i<g->n;i++){
        if (IS_POSITIVE(vector[i])){
            s[i]=1;
        }
        else{
            s[i]=-1;
        }
    }
    algorithm4 (A,g,s,k,M);
    temp=mult_stbs(A,g,k, M,s);
    if (!(IS_POSITIVE(temp))){
        division->g1=g;
        division->g2=NULL;
        free(s);
        free(vector);
        return division;
    }
    g1size=0;
    for(i=0;i<g->n;i++){
        if (s[i]==1){
            g1size++;
        }
    }
    g2size=(g->n)-g1size;
    g1=(group_g *)malloc (sizeof(group_g));
    g2=(group_g *)malloc (sizeof(group_g));
    g1->g=(int *)malloc(sizeof(int)*g1size);
    g2->g=(int *)malloc(sizeof(int)*g2size);
    g1point=0;
    g2point=0;
    for(i=0;i<g->n;i++){
        if (s[i]==1){
            g1->g[g1point]=g->g[i];
            g1point++;
        }
        else{
            g2->g[g2point]=g->g[i];
            g2point++;
        }
    }
    g1->n=g1size;
    g2->n=g2size;
    division->g1=g1;
    division->g2=g2;
    gr_free(g);
    free(vector);
    free(s);
    return division;
}

/*Algorithm 4*/
void algorithm4 (struct spmat *A,struct group_g *g,double *s, int *k, int M) {
    int i, j, move_vertex, best_improve;
    double max_score, max_improve, deltaQ;
    int *indices, *unmoved;
    double *improve,*score, *x;

    improve= (double *) malloc(sizeof(double) * (g->n));
    indices= (int *) malloc(sizeof(int) * (g->n));
    x=(double *)malloc(sizeof(double)*g->n);
    score = (double *) malloc(sizeof(double) * ((g->n)));
    B_mult(A,g,s,k,M,x);
    for (i = 0; i < g->n; i++){
        score[i]=-2*(s[i]*x[i]+(pow(k[i],2))/(double )M);
    }
    do{
        unmoved= (int *) malloc (sizeof(int)*(g->n));
        for (i=0;i<(g->n);i++){
            unmoved[i]=1;
        }
        for (i = 0; i < g->n; i++) {
            move_vertex = argmax_score(score, unmoved, g->n);
            max_score = score[move_vertex];
            s[move_vertex] = s[move_vertex] * (-1);
            indices[i] = move_vertex;
            if (i == 0) {
                improve[i] = max_score;
            } else {
                improve[i] = improve[i - 1] + max_score;
            }
            unmoved[move_vertex] = 0;
            Score_Update(move_vertex, A, g, s, score, k, M);
        }
        /*Find the maximum improvement of s and update s accordingly*/
        max_improve = improve[0];
        best_improve = 0;
        for (i = 1; i < g->n; i++) {
            if (IS_POSITIVE(improve[i] - max_improve)) {
                max_improve = improve[i];
                best_improve =i;
            }
        }
        for (i = g->n-1; i > best_improve; i--) {
            j=indices[i];
            s[j] = s[j] * (-1);
            Score_Update(j,A,g,s,score,k,M);
        }
        if (best_improve == (g->n)-1) {
            deltaQ = 0;
        } else {
            deltaQ = improve[best_improve];
        }
        free(unmoved);
    }while(deltaQ>0);
    free(x);
    free(indices);
    free(improve);
    free(score);
}

void Score_Update(int move_vertex,spmat *A,struct group_g *g,double *s,double *score, int *k, int M) {
    int j, l, found,temp_ver,stop;
    double Bg_ik;
    found = 0;
    stop= -1 ;
    for (j = 0; j < g->n; j++) {
        if (j == move_vertex) {
            score[j] = score[j] * (-1);
        } else {
            for (l = A->rowptr[j]; l < A->rowptr[j + 1] && stop==-1; l++) {
                temp_ver=A->colind[l];
                if ( temp_ver== move_vertex) {
                    found = 1;
                }
                else if (temp_ver>move_vertex){
                    stop=1;
                }
            }
            if (found == 1) {
                Bg_ik = 1 - k[j] * k[move_vertex] / (double) M;
            } else {
                Bg_ik = -k[j] * k[move_vertex] / (double) M;
            }
            score[j] = score[j] - 4 * s[j] * s[move_vertex] * Bg_ik;
        }
    }
}

int argmax_score (double *arr,int *unmoved, int n){
    int i,j,argmax,first_unmoved=-1;
    double max_arr;
    for(i=0;i<n && first_unmoved==-1;i++){
        if (unmoved[i]==1){
            first_unmoved=i;
        }
    }
    argmax=first_unmoved;
    max_arr=arr[first_unmoved];
    for (j=first_unmoved+1;j<n;j++){
        if (unmoved[j]==1) {
            if (IS_POSITIVE(arr[j] - max_arr)) {
                argmax = j;
                max_arr=arr[j];
            }
        }
    }
    return argmax;
}

/*Computing Modularity*/
double mult_stbs(struct spmat *A,struct group_g *g, int *k, int M, double *s){
    int i;
    double temp;
    double *result=(double *)malloc(sizeof(double)*g->n);
    Bhat_mult(A,g,s, k,M,result);
    temp=0;
    for (i=0;i<g->n;i++) {
        temp += result[i] * s[i];
    }
    free(result);
    return temp;
}