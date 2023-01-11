#include  <stdio.h>
#include  <stdlib.h>
#include  <stdbool.h>
//
// Z80 HL*定数を加算命令に展開するコンパイラ Ver 2.0
// 乗数,被乗数は2の補数を扱っているので、負数も可
//
int main(int argc, char* argv[])
{
    short hl,de,l;
    int b=0;

    // 引数（乗数の取得）
    if (argc!=3) fprintf(stderr,"usage:z80constmul <被乗数> <乗数>\n"),exit(1);
    hl=(short) atoi(argv[1]);
    l=(short) atoi(argv[2]);

    // 乗数が何ビットあるか計算 (b=bit数となる)
    for(ushort r=(ushort)l;r;r>>=1 ) b++;

    // コンパイル（ヘッダ）
    if (l==0) printf("ld hl,0\n"),hl=0;
    else  {
      printf("ld hl,%d ; 被乗数 この行を省けばhlの値は何でもいい。\n",(int)hl);
      printf("ld d,h\n");
      printf("ld e,l\n");
      de=hl;

      // コンパイル（展開）
      for (int i=b-1;i>=0 ; i--) {
        if ( (((l>>i) & 1)!=0 ) && (i!=b-1))
          printf("add hl,de\n"),hl += de;
        if (i!=0)
          printf("add hl,hl\n"),hl += hl;
      }
    }

    printf(";hl=%d\n",(int) hl);
    exit(0);
}

