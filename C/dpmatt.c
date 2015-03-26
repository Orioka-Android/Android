//// DPマッチング 
//// (C) Toru Nakata, toru-nakata@aist.go.jp
//// 2004 Oct 19

 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

 int main()

{

              long i, j, k;
              char StrA[64]; // 入力文字列Ａ
              char StrB[64]; // 入力文字列Ｂ

              double ZurePenalty = 1; // １文字ずれたことへのペナルティ
              double AwazuPenalty = 5; // １文字不一致へのペナルティ
 
              double Distance = 0; // ２つの文字列の不一致度

              long LengthA; //Ａの長さ
              long LengthB; //Ｂの長さ

              int MissMatch[64][64]; //一致結果バッファ
              double Cost[64][64]; //各経路点の到達コスト
              int From[64][64]; //最短経路はどこから来たか 0:斜め、1:ｉ増え,２：ｊ増え
              double dtemp1, dtemp2, dtemp3;

              //マッチング結果

              char ResultA[128];
              char ResultB[128];
              long LenAB;

              printf("\n ============== DP Matching ================\n\n");

              printf("Input String A >> ");
              scanf("%s",StrA); 

              printf("Input String B >> ");
              scanf("%s",StrB);

              LengthA = strlen(StrA);
              LengthB = strlen(StrB);
 
             /////////////// 総当たりで一致の確認

              for(i = 0; i < LengthA; i++) {
                            for(j = 0; j < LengthB; j++) {
                                          if(StrA[i] == StrB[j]) {
                                               MissMatch[i][j] = 0;
                                          }
                                          else {
                                               MissMatch[i][j] = 1;
                                          }
                            }
              }


              //////////　コスト計算

              Cost[0][0] = MissMatch[0][0] * AwazuPenalty;
              From[0][0] = 0;

              //// i側の縁

              for(i = 1; i < LengthA; i++) {
                    Cost[i][0] = Cost[i-1][0] + ZurePenalty + MissMatch[i][0] * AwazuPenalty;
                    From[i][0] = 1;
              }

              //// ｊ側の縁

              for(j = 1; j < LengthB; j++) {

                     Cost[0][j] = Cost[0][j-1] + ZurePenalty + MissMatch[0][j] * AwazuPenalty;
                     From[0][j] = 2;

              }

 

              //// 中間部

              for(i = 1; i < LengthA; i++) {
                    for(j = 1; j < LengthB; j++) {
                          dtemp1 = Cost[i-1][j-1] + MissMatch[i][j] * AwazuPenalty; //斜めで来た
                          dtemp2 = Cost[i-1][j  ] + MissMatch[i][j] * AwazuPenalty + ZurePenalty; //i増えで来た
                          dtemp3 = Cost[i  ][j-1] + MissMatch[i][j] * AwazuPenalty + ZurePenalty; //j増えで来た

                                 if(dtemp1 <= dtemp2 && dtemp1 <= dtemp3) {
                                               Cost[i][j] = dtemp1;
                                               From[i][j] = 0;
                                          }

                                 else if(dtemp2 <= dtemp3) {
                                                Cost[i][j] = dtemp2;
                                                From[i][j] = 1;
                                          }
                                  else {
                                                 Cost[i][j] = dtemp3;
                                                 From[i][j] = 2;
                                          }
                            }
              }

 

              Distance = Cost[LengthA -1][LengthB-1];

			  for (j=0;j<LengthB;j++) {
				  for (i=0;i<LengthA;i++){
					  printf("%4.1f ", Cost[i][j]);
				  }
				  printf("\n");
			  }
				  
              //////ゴールからスタートへ逆に辿る

              LenAB = LengthA + LengthB;
              i = LengthA -1;
              j = LengthB -1;

              for(k = LenAB; i >= 0 && j >= 0; k--) {
                            ResultA[k] = StrA[i];
                            ResultB[k] = StrB[j];
 
                            //printf("%c %c  ", ResultA[k], ResultB[k]);

                            switch(From[i][j]) {
                            case 0: 
                                          i--;
                                          j--;
                                          break;

                            case 1: 
                                          i--;
                                          break;

                            case 2: 
                                          j--;
                                          break;

                            default:
                                          printf("Error\n");
                                          break;

                            }

              }

              LenAB -= k; //マッチ結果の文字列の長さ

              for(i = 0; i < LenAB; i++) {
                            ResultA[i] = ResultA[i+k+1];
                            ResultB[i] = ResultB[i+k+1];
              }

              ResultA[LenAB] = ResultB[LenAB] = '\0';

              printf("\n === Matching Result ===\n");
              printf("\nDifference = %6.1f\n",Distance);

 /*             for(i = 0; i < LengthA; i++) {

                            printf("\n%3d: ",i+1);
                            for(j = 0; j < LengthB; j++) {

                                        printf("%1d",From[i][j]);

                                          switch(From[i][j]) {
                                          case 0: printf("\\"); break;
                                          case 1: printf("|"); break;
                                          case 2: printf("-"); break;
                                          default: break;
                                          }
                            }
              }
*/
              printf("\n");
              printf("A:  %s\n",ResultA);
              printf("B:  %s\n",ResultB);
              return 0; 

}