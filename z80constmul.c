#include <stdio.h>
#include <stdlib.h>
//
// Z80 HL*定数の加算展開コンパイラ
// usage: z80constmul <定数>
// 定数乗数は2の補数を扱っているので、負数も可
//
int main(int argc, char* argv[])
{
    short hl = 100; // 被乗数 
    short de = 0;
    short b,l;

    // 引数（乗数の取得）
    {
    int ll;
    if (argc != 2)
        exit(1);
    sscanf(argv[1], "%d", &ll);
    l =  (short)ll;
    }

    // 乗数が何ビットあるか計算 (16 bit まで)
    //  (b=bit数となる)
    // 
    //乗数  b
    //     0   0
    //     1   1
    //     2   2
    //     3   2
    //     4   3
    //     5   3
    //     6   3
    //     7   3
    // ...
    // 65535   16 
    b = 0;
    for(ushort r=(ushort)l;r;r>>=1 )
      b++;

    //
    // コンパイル（展開）
    //
    printf("ld hl,%d ; ここでは、被乗数は%dとする\n", hl,hl);
    printf("ld de,%d ; de はゼロクリア\n", de);
    printf("ex de,hl\n");
    {
    short t;
    t = de; de = hl ; hl = t;
    }

    for (short i=b; i>=0 ; i--) {
      if ( l & (1 << i))  {
        printf("add hl,de\n");
        hl += de;
        }
      if ( (i != 0) && (i != b ) ) {
        printf("add hl,hl\n");
        hl += hl;
        }
     }

    printf("%d\n",(int) hl);
    exit(0);
}

