#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main(void){
  int u,v;
  int i,j,k; //forループ用
  int MAX=-1000; //頂点の最大値を確保
  char fname[128]; //ファイル名
  double cluster=0; //クラスタ係数
  FILE *fp;
  int **Adj; //グラフの二次配列
  int C,D;

  //ファイル読み込み
  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname)-1] = '\0';
  fflush(stdin);

  fp=fopen(fname,"r");
  while((fscanf(fp, "%d %d", &u,&v)!=-1)){//最大の頂点を取り出す。
    if(MAX<u){MAX=u;}
    if(MAX<v){MAX=v;}
  }

  //2グラフを2次配列で表現
  Adj=(int **)malloc(sizeof(int*)*(MAX+1));
  for(i=0;i<MAX+1;i++){
    Adj[i]=(int *)malloc(sizeof(int)*(MAX+1));
  }

  for(i=0;i<MAX+1;i++){//初期化
    for(j=0;j<MAX+1;j++){
      Adj[i][j]=0;
    }
  }
  fseek(fp, 0L, SEEK_SET);//ファイルの先頭に戻る
  while((fscanf(fp, "%d %d", &u,&v)!=-1)){
    Adj[u][v]=1;
    Adj[v][u]=1;
  }

  for(i=0;i<MAX+1;i++){
    C=0; //三角構造の数
    D=0; //次数
    for(j=0;j<MAX+1;j++){
      if(Adj[i][j]==1){//枝が存在する
        D++;
        for(k=0;k<MAX+1;k++){
          if(Adj[i][k]==1 && Adj[j][k]==1){//三角形が存在する
            C++;
          }
        }
      }
    }
    C=C/2;
    // printf("%d %d\n",C,D);
    if(D>1){ //各頂点のクラスター係数の合計
      cluster+=2*(double)C/(D*(D-1));
    }
  }
  cluster=cluster/(MAX+1);//クラスタ係数
  printf("%f\n",cluster);

  for(i=0;i<MAX+1;i++){
    free(Adj[i]);
  }
  free(Adj);
  return 0;
}
