#include <stdio.h>
#include <stdlib.h>
//
// Z80 HL*定数の加算展開コンパイラ
// usage: z80constmul <定数>
//
int main(int argc, char* argv[])
{
    short hl = 100; // 被乗数 
    short de = 0;
    short t;
    int ll;
    int m,r,b;

    // 引数（乗数の取得）
    if (argc != 2)
        exit(1);
    sscanf(argv[1], "%d", &ll);

    // 乗数が何ビットあるか計算（負数も可）16 bit まで
    //  (b=bit数-1となる)
    r=ll;
    b=0;
    for(m=0;m<16;m++) {
      b+=1;
      r>>=1;
      if (r==0) break;
      }

    // コンパイル（展開）
    printf("ld hl,%d\n", hl);
    printf("ld de,%d\n", de);
    printf("ex de,hl\n");
    t = de; de = hl ; hl = t;
    for (int i = b; i>=0; i--) {
      if (ll & (1 << i)) {
        printf("add hl,de\n");
        hl += de;
        }
      if ((i > 0) && (i!=b) ) {
        printf("add hl,hl\n");
        hl += hl;
        }
     }
    printf("%d\n",(int) hl);
}
