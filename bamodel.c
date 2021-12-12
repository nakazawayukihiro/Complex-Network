#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>

int main(int argc, char** argv){
  int n,m,l;//最終的な頂点数と最初の頂点数、新たな頂点の次数
  int i,j,k;//forループ用
  unsigned int total;//全頂点の次数の和
  double ran_0_1;//乱数(0~1)
  char fname[128];//ファイル名
  short int *Adj;
  short int *FRE;
  unsigned int *a;
  double count;//次数分布の累和のために使う
  int flag=0,flag2=0;//while文の判定のため
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
	if(strcmp(argv[3], "-m") == 0){
		m=atoi(argv[4]);
	}
  else{
		printf("サポートされていないコマンドライン引数です\n");
    return 0;
	}
  if(strcmp(argv[5], "-l") == 0){
		l=atoi(argv[6]);
	}
  else{
		printf("サポートされていないコマンドライン引数です\n");
    return 0;
	}

  total=m*(m-1);
  FRE=(short int *)malloc(sizeof(short int)*(n));
  Adj=(short int *)malloc(sizeof(short int)*(n));
  a=(unsigned int *)malloc(sizeof(unsigned int)*(l));
  for(i=0;i<m;i++){
    Adj[i]=0;
  }

  for(i=0;i<m;i++){//初期は完全グラフなので次数は頂点数-1
    FRE[i]=(m-1);
  }

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
    for(i=0;i<m;i++){
      for(j=0;j<m;j++){
        if(i<j){//初期状態
          fprintf(fp,"%d %d\n",i,j);
        }
      }
    }
    srand(time(NULL));
    for(i=m;i<n;i++){
      for(j=0;j<l;j++){
        flag=0;
        while(flag==0){//枝を付け替える
          ran_0_1=(double)rand()/RAND_MAX;
          count=0;k=0;flag2=0;
          while(flag2==0){
            count+=((double)FRE[k]/(double)total);
            k++;
            if(count>ran_0_1){flag2=1;}
          }
          k--;//この時のkの頂点につなげる
          if(Adj[k]==0){//重複が無ければ
            fprintf(fp,"%d %d\n",i,k);
            // if(i%10000==0){
            //   printf("%d %d\n",i,k);
            // }
            a[j]=k;
            Adj[k]=1;
            flag=1;
          }
          else{flag=0;}
        }
      }
      FRE[i]=l;//追加した頂点の次数はlでこれを入れる
      total+=(l*2);//次数の合計は2*l増える
      for(j=0;j<l;j++){//次数を増やす
        FRE[a[j]]+=1;
      }
      for(j=0;j<=i;j++){//初期化
        Adj[j]=0;
      }
    }
  }

  fclose(fp);
  free(Adj);
  free(FRE);
  free(a);
  return 0;
}
