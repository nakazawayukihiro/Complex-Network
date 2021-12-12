#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main(int argc, char** argv){
  int n,k;//頂点数と次数
  double p;//つなぎ替え確率
  int i,j;//forループ用
  int ran_n;//乱数(整数)
  double ran_0_1;//乱数(0~1)
  double ran_0_1_cp;//乱数(0~1)
  char fname[128];//ファイル名
  int **Adj;
  int **Adj_cp;
  FILE *fp;
  if (argc < 7){
		printf("コマンドライン引数を正しく指定してください\n");
		return 0;
	}
  if(strcmp(argv[1], "-n") == 0){
		n=atoi(argv[2]);
	}
  else{
		printf("サポートされていないコマンドライン引数です\n");
    return 0;
	}
	if(strcmp(argv[3], "-k") == 0){
		k=atoi(argv[4]);
	}
  else{
		printf("サポートされていないコマンドライン引数です\n");
    return 0;
	}
  if(strcmp(argv[5], "-p") == 0){
		p=atof(argv[6]);
	}
  else{
		printf("サポートされていないコマンドライン引数です\n");
    return 0;
	}

  Adj=(int **)malloc(sizeof(int*)*(n));
  for(i=0;i<n;i++){
    Adj[i]=(int *)malloc(sizeof(int)*(n));
  }
  Adj_cp=(int **)malloc(sizeof(int*)*(n));
  for(i=0;i<n;i++){
    Adj_cp[i]=(int *)malloc(sizeof(int)*(n));
  }

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      Adj[i][j]=0;
      Adj_cp[i][j]=0;
    }
  }

  for(i=0;i<n;i++){
    for(j=0;j<=(k/2);j++){//その頂点から右側に繫がっているもののみを見れば良い
      if(j!=0){
        Adj[i][(i+j)%n]=1;
        Adj[(i+j)%n][i]=1;
      }
    }
  }

  srand(time(NULL));
  for(i=0;i<n;i++){
    for(j=0;j<=(k/2);j++){//その頂点から右側に繫がっているもののみを見れば良い
      if(j!=0){
        ran_0_1=(double)rand()/RAND_MAX;
        if(ran_0_1<=p){//pを下回ったのでリワイヤリングを実行
          ran_0_1_cp=(double)rand()/RAND_MAX;
          if(ran_0_1_cp<=0.5){//iの頂点を固定してリワイヤリング
            ran_n=rand()%n;
            while(Adj[i][ran_n]==1 || Adj[ran_n][i]==1 || Adj_cp[i][ran_n]==1 || Adj_cp[ran_n][i]==1 || ran_n==i){
              ran_n=rand()%n;
            }
            Adj_cp[i][ran_n]=1;
            Adj_cp[ran_n][i]=1;
          }
          else{//ran_nの頂点を固定してリワイヤリング
            ran_n=rand()%n;
            while(Adj[(i+j)%n][ran_n]==1 || Adj[ran_n][(i+j)%n]==1 || Adj_cp[(i+j)%k][ran_n]==1 || Adj_cp[ran_n][(i+k)%k]==1 || ran_n==(i+j)%n){
              ran_n=rand()%n;
            }
            Adj_cp[ran_n][(i+j)%n]=1;
            Adj_cp[(i+j)%n][ran_n]=1;
          }
        }
        else{
          Adj_cp[i][(i+j)%n]=1;Adj_cp[(i+j)%n][i]=1;
        }
      }
    }
  }

  //ファイルに書き込む
  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname)-1] = '\0';
  fflush(stdin);

  fp=fopen(fname,"w");

  if(fp==NULL){
    printf("error\n");
    return 0;
  }
  else{
    for(i=0;i<n;i++){
      for(j=0;j<n;j++){
        if(Adj_cp[i][j]==1){
          if(i<j){
            fprintf(fp,"%d %d\n",i,j);
          }
        }
      }
    }
  }

  fclose(fp);
  for(i=0;i<n;i++){
    free(Adj[i]);
    free(Adj_cp[i]);
  }
  free(Adj);
  free(Adj_cp);
  return 0;
}
