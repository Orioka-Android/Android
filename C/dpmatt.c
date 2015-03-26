//// DP�}�b�`���O 
//// (C) Toru Nakata, toru-nakata@aist.go.jp
//// 2004 Oct 19

 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

 int main()

{

              long i, j, k;
              char StrA[64]; // ���͕�����`
              char StrB[64]; // ���͕�����a

              double ZurePenalty = 1; // �P�������ꂽ���Ƃւ̃y�i���e�B
              double AwazuPenalty = 5; // �P�����s��v�ւ̃y�i���e�B
 
              double Distance = 0; // �Q�̕�����̕s��v�x

              long LengthA; //�`�̒���
              long LengthB; //�a�̒���

              int MissMatch[64][64]; //��v���ʃo�b�t�@
              double Cost[64][64]; //�e�o�H�_�̓��B�R�X�g
              int From[64][64]; //�ŒZ�o�H�͂ǂ����痈���� 0:�΂߁A1:������,�Q�F������
              double dtemp1, dtemp2, dtemp3;

              //�}�b�`���O����

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
 
             /////////////// ��������ň�v�̊m�F

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


              //////////�@�R�X�g�v�Z

              Cost[0][0] = MissMatch[0][0] * AwazuPenalty;
              From[0][0] = 0;

              //// i���̉�

              for(i = 1; i < LengthA; i++) {
                    Cost[i][0] = Cost[i-1][0] + ZurePenalty + MissMatch[i][0] * AwazuPenalty;
                    From[i][0] = 1;
              }

              //// �����̉�

              for(j = 1; j < LengthB; j++) {

                     Cost[0][j] = Cost[0][j-1] + ZurePenalty + MissMatch[0][j] * AwazuPenalty;
                     From[0][j] = 2;

              }

 

              //// ���ԕ�

              for(i = 1; i < LengthA; i++) {
                    for(j = 1; j < LengthB; j++) {
                          dtemp1 = Cost[i-1][j-1] + MissMatch[i][j] * AwazuPenalty; //�΂߂ŗ���
                          dtemp2 = Cost[i-1][j  ] + MissMatch[i][j] * AwazuPenalty + ZurePenalty; //i�����ŗ���
                          dtemp3 = Cost[i  ][j-1] + MissMatch[i][j] * AwazuPenalty + ZurePenalty; //j�����ŗ���

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
				  
              //////�S�[������X�^�[�g�֋t�ɒH��

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

              LenAB -= k; //�}�b�`���ʂ̕�����̒���

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