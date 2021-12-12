#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main(void){
  int u=0,v=0;
  int i,j; //forループ用
  int p;
  int MAX=-1000; //グラフの最大頂点を確保
  int MAX_FRE; //次数の最大値
  int MAX_FRE_I; //次数が最大となる頂点番号
  int flag=0;
  char fname[128];
  FILE *fp;

  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname)-1] = '\0';
  fflush(stdin);

  fp=fopen(fname,"r");
  while((fscanf(fp, "%d %d", &u,&v)!=-1)){//最大頂点を確保
    if(MAX<u){MAX=u;}
    if(MAX<v){MAX=v;}
  }

  int **Adj;
  Adj=(int **)malloc(sizeof(int*)*(MAX+1));
  for(i=0;i<MAX+1;i++){
    Adj[i]=(int *)malloc(sizeof(int)*(MAX+1));
  }

  for(i=0;i<MAX+1;i++){
    for(j=0;j<MAX+1;j++){
      Adj[i][j]=0;
    }
  }
  fseek(fp, 0L, SEEK_SET);//ファイルの先頭に戻る
  while((fscanf(fp, "%d %d", &u,&v)!=-1)){//グラフを2次元配列で確保
    Adj[u][v]=1;
    Adj[v][u]=1;
  }

  fclose(fp);

  int **F; //結び直した後のグラフを2次元配列で確保
  F=(int **)malloc(sizeof(int*)*(MAX+1));
  for(i=0;i<MAX+1;i++){
    F[i]=(int *)malloc(sizeof(int)*(MAX+1));
  }

  for(i=0;i<MAX+1;i++){
    for(j=0;j<MAX+1;j++){
      F[i][j]=0;
    }
  }

  int *FRE=(int*)malloc((MAX+1)*sizeof(int));//各頂点の次数を確保
  for(i=0;i<MAX+1;i++){
    FRE[i]=0;
    for(j=0;j<MAX+1;j++){
      if(Adj[i][j]==1){
        FRE[i]+=1;
      }
    }
  }

  srand(time(NULL));

  //ファイルへ書き込む
  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname)-1] = '\0';
  fflush(stdin);

  fp=fopen(fname,"w");
  if(fp==NULL){ //もどファイルを開けなかったら
    printf("errer\n");
    return 0;
  }
  else{//次数が最大の頂点からつなぎ直す
    MAX_FRE=0;//最大次数
    for(i=0;i<MAX+1;i++){//最初の1回
      if(FRE[i]>MAX_FRE){//最大の次数となる頂点番号MAX_FRE_Iを取り出す
        MAX_FRE_I=i;
        MAX_FRE=FRE[i];
        flag=1;
      }
    }
    while(flag!=0){
      p=rand()%(MAX+1); //結ばれる頂点
      while(FRE[p]==0 || p==MAX_FRE_I || F[MAX_FRE_I][p]==1 || F[p][MAX_FRE_I]==1){//この場合やり直す
        p=rand()%(MAX+1);
      }
      fprintf(fp,"%d %d\n",MAX_FRE_I,p);
      F[MAX_FRE_I][p]=1;
      F[p][MAX_FRE_I]=1;
      FRE[MAX_FRE_I]--;
      FRE[p]--;
      MAX_FRE=0;
      flag=0;
      for(i=0;i<MAX+1;i++){
        if(FRE[i]>MAX_FRE){
          MAX_FRE_I=i;
          MAX_FRE=FRE[i];
          flag=1;
        }
      }
    }
  }
  fclose(fp);
  for(i=0;i<MAX+1;i++){
    free(Adj[i]);
    free(F[i]);
  }
  free(Adj);
  free(F);
  free(FRE);

  return 0;
}
