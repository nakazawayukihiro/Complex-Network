#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main(void){
  int u,v;
  int i;
  int MAX=-1000;
  char fname[128];
  FILE *fp;
  int *D;
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
  D=(int *)malloc(sizeof(int)*(MAX+1));

  for(i=0;i<MAX+1;i++){
    C[i]=0;
    D[i]=0;
  }
  fseek(fp, 0L, SEEK_SET);
  while((fscanf(fp, "%d %d", &u,&v)!=-1)){
    C[u]++;
    C[v]++;
  }

  for(i=0;i<MAX+1;i++){
    D[C[i]]++;
  }


  for(i=0;i<MAX+1;i++){
    if(D[i]>0){
      printf("%i,%f\n",i,(double)D[i]/(double)(MAX+1));
    }
  }
  free(C);
  free(D);
  return 0;
}
