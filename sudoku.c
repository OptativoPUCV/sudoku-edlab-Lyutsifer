#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          fscanf (file, "%d", &n->sudo[i][j]);
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int i, j, k;
    
    //Linear check
    for (i=0; i<9; i++){
      //Create an array, it saves numbers to compare
      for (j=0; j<9; j++){ 
        if (n->sudo[i][j] == 0) continue;

        for (k=0; k<9; k++){

            if (n->sudo[i][j] == n->sudo[i][k] && j != k){
              return 0;
            }
            if (n->sudo[i][j] == n->sudo[k][j] && i != k){
              return 0;
            }
        }
        k= 3*(i/3) + (j/3);
        for(int p=0;p<9;p++){
            int x= 3*(k/3) + (p/3) ;
            int d= 3*(k%3) + (p%3) ;
            if (n->sudo[i][j] == n->sudo[x][d] && (i!=x && j!=d)){
              return 0;
            }
        }        
      }
    }
  return 1;
}


List* get_adj_nodes(Node* n){
    //List* list=createList();
    int f;
    int g;
    int numero;
    List* list=createList();

    for( f=0 ; f<9 ;f++ )
    {
      for( g=0 ; g<9 ; g++ )
      {
        if(n->sudo[f][g]==0)
        {
          for( numero=1 ; numero<10 ; numero++)
          {
            n->sudo[f][g]=numero;
            if(is_valid(n))
            {
              Node* nuevo=copy(n);
              pushBack(list, nuevo);
            }          
          }
        n->sudo[f][g]=0;
        return list;
        }
      }
    }
    
  return list;
}

//Perfect
int is_final(Node* n){
    int i,j;
    for (i=0; i<9; i++){
        for (j=0; j<9; j++){
          if (n->sudo[i][j]==0) return 0;
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack *s = createStack();
  push(s,initial);
  while (get_size(s) != 0){
      Node * h= top(s);
      pop(s); 
      //n = top(s)
      if (is_final(h) == 1) return h;
      List * adj = get_adj_nodes(h); 
      Node * aux= first(adj);
      while (aux){
        push(s,aux);
        aux= next(adj);
      }
  }
  return NULL;
} 



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/