#include<stdio.h>
#include<string.h>
#include<strings.h>
#include"common.h"

void search_low_card(int out_cards[8][15],int my_cards[8][15],int use_joker_flag){
  /*
    低い方から探して,最初に見つけたカードを一枚out_cardsにのせる。
    use_joker_flagが1のとき,カードが見つからなければ,jokerを一枚out_cardsにのせる。
  */
  int i,j,find_flag=0;

  clear_table(out_cards);                  //テーブルをクリア
  for(j=1;j<14&&find_flag==0;j++){        //低い方からさがし
    for(i=0;i<4&&find_flag==0;i++){
      if(my_cards[i][j]==1){              //カードを見つけたら               
        find_flag=1;                      //フラグを立て
        out_cards[i][j]=my_cards[i][j];   //out_cardsにのせ,ループを抜ける。
      }
    }
  }
  if(find_flag==0&&use_joker_flag==1){       //見つからなかったとき
    out_cards[0][14]=2;                  //ジョーカーをのせる
  }
}

void make_info_table(int info_table[8][15],int my_cards[8][15]){
  int i,j;
  clear_table(info_table);
  for(i=1;i<=13;i++){
    info_table[4][i]=my_cards[0][i]+my_cards[1][i]+my_cards[2][i]+my_cards[3][i];
  }
  for(i=13;i>=1;i--){
    for(j=0;j<=3;j++){
      if(my_cards[j][i]==1)info_table[j][i]=info_table[j][i+1]+1;
      else if(my_cards[j][i]==0)info_table[j][i]=0;
    }
  }
  for(i=1;i<=13;i++){
    for(j=0;j<=3;j++){
      if(info_table[j][i]==2)info_table[j][i]=1;
    }
  }
} 

int search_low_pair(int dst_cards[8][15],int info_table[8][15],int my_cards[8][15]){
  int i,j;
  clear_table(dst_cards);
  for(i=1;i<=13;i++){
    if(info_table[4][i]>=2) break;
  }
  if(i<=13){
    for(j=0;j<=3;j++) dst_cards[j][i]=my_cards[j][i];
    return 1;
  }
  else return 0;
}

int search_low_kaidan(int dst_cards[8][15],int info_table[8][15]){
  int i,j,max=0,i1,j1;
  clear_table(dst_cards);
  for(i=0;i<=3;i++){
    for(j=1;j<=13;j++){
      if(info_table[i][j]>max){
	max=info_table[i][j];
	i1=i;
	j1=j;
      }    
    }
  }
  if(max!=0){
    for(j=j1;j<=j1+max-1;j++){dst_cards[i1][j]=1;}
    return 1;
  }
  else return 0;
}

