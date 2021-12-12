#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main(void){
  int u,v;
  int i,j;
  int MAX=-1000;
  char fname[128];
  FILE *fp;
  int **Adj;
  int D;
  int *C;


  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname)-1] = '\0';
  fflush(stdin);

  fp=fopen(fname,"r");
  while((fscanf(fp, "%d %d", &u,&v)!=-1)){
    if(MAX<u){MAX=u;}
    if(MAX<v){MAX=v;}
  }

  C=(int *)malloc(sizeof(int)*(MAX+1));
  Adj=(int **)malloc(sizeof(int*)*(MAX+1));
  for(i=0;i<MAX+1;i++){
    Adj[i]=(int *)malloc(sizeof(int)*(MAX+1));
  }

  for(i=0;i<MAX+1;i++){
    C[i]=0;
    for(j=0;j<MAX+1;j++){
      Adj[i][j]=0;
    }
  }
  fseek(fp, 0L, SEEK_SET);
  while((fscanf(fp, "%d %d", &u,&v)!=-1)){
    Adj[u][v]=1;
    Adj[v][u]=1;
  }

  for(i=0;i<MAX+1;i++){
    D=0;
    for(j=0;j<MAX+1;j++){
      if(Adj[i][j]==1){
        D++;
      }
    }
    C[D]=C[D]+1;
  }


  for(i=0;i<MAX+1;i++){
    if(C[i]>0){
      printf("%i,%f\n",i,(double)C[i]/(double)(MAX+1));
    }
  }
  free(C);
  for(i=0;i<MAX+1;i++){
    free(Adj[i]);
  }
  free(Adj);
  return 0;
}
