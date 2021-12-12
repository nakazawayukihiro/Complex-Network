#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define inf 1000000

void enqueue(int *Q, int a, int *tail, int *head,int N);
int dequeue(int *Q,int *tail, int *head, int N);
void bfs(int *Q, int *tail, int *head, int N, int v0, int *color, int *d,int **Adj);

int main(void){
  int head,tail;//キューを使うため
  int v0;//幅優先探索の始点
  int u,v;
  int i,j;
  int count=0;
  int MAX=-1000; //グラフの最大頂点
  char fname[128]; //ファイル名
  double length; //平均頂点間距離
  FILE *fp;
  int **Adj;//グラフを2次元配列で表現
  int *d,*color,*Q; //幅優先探索に使用
  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname)-1] = '\0';
  fflush(stdin);

  fp=fopen(fname,"r");
  while((fscanf(fp, "%d %d", &u,&v)!=-1)){//グラフの最大頂点を確保
    if(MAX<u){MAX=u;}
    if(MAX<v){MAX=v;}
  }

  //諸処の配列を確保する
  d=(int*)malloc((MAX+1)*sizeof(int));
  color=(int*)malloc((MAX+1)*sizeof(int));
  Q=(int*)malloc((MAX+1)*sizeof(int));

  Adj=(int **)malloc(sizeof(int*)*(MAX+1));
  for(i=0;i<MAX+1;i++){
    Adj[i]=(int *)malloc(sizeof(int)*(MAX+1));
  }

  for(i=0;i<MAX+1;i++){
    for(j=0;j<MAX+1;j++){
      Adj[i][j]=0;
    }
  }

  fseek(fp, 0L, SEEK_SET);
  while((fscanf(fp, "%d %d", &u,&v)!=-1)){
    Adj[u][v]=1;
    Adj[v][u]=1;
  }

  fclose(fp);

  for(v0=0;v0<MAX+1;v0++){
    head=0;tail=0;
    bfs(Q,&tail,&head,MAX+1,v0,color,d,Adj);//幅優先探索
    for(u=0;u<MAX+1;u++){
      if(d[u]!=MAX+1 && u>v0){
        count+=d[u];//d_i,jを全てたす
      }
    }
  }

  length=2*(double)count/((double)(MAX+1)*(double)MAX);//平均頂点間距離を求める
  printf("%f\n",length);
  for(i=0;i<MAX+1;i++){
    free(Adj[i]);
  }
  free(Adj);
  free(d);
  free(color);
  free(Q);
  return 0;
}

void enqueue(int *Q,int a,int *tail,int *head,int N){
  Q[*tail]=a;
  *tail=*tail+1;
  if(*tail>=N){
	   *tail=0;
  }
  if(*tail==*head){
    // printf("error: overflow\n");
  }
}

int dequeue(int *Q, int *tail, int *head, int N){
  int a;
  if(*head==*tail){
     // printf("error: underflow\n");
	   return -1;
  }
  else{
	   a=Q[*head];
	   *head=*head + 1;
	   if(*head>=N){
	      *head = 0;
	   }
     return a;
  }
}

void bfs(int *Q, int *tail, int *head, int N, int v0, int *color, int *d,  int **Adj){
  int v, u;
  int count=0;
  for(v=0;v<N;v++){
	  if(v!=v0){
	    color[v]=0; //white = 0, gray = 1, black = 2で表す
	    d[v]=N;
	  }
  }
  enqueue(Q,v0,tail,head,N);
  color[v0]=1;
  d[v0]=0;

  while(count==0){
	  u=dequeue(Q,tail,head,N);
    if(u==-1){count=1;}
    else{
	    for(v=0;v<N;v++){
        if(Adj[u][v]==1){
          if(color[v]==0){
            color[v]=1;
		        d[v]=d[u]+1;
		        enqueue(Q,v,tail,head,N);
		       }
	       }
	    }
	    color[u]=2;
    }
  }
}
