#!/usr/bin/python3
import sys
#
# Z80 HL*定数を加算命令に展開するコンパイラ Ver 2.0
# ２の補数を扱っているので、被乗数、乗数共に負数も可
# 

# 何ビットあるか計算 (b=bit数となる)
def nbit(l):
    b=0
    r=l
    while(r):
        r>>=1
        b+=1
    return b

# 2の補数表示
def print2complement(i):
    print(f"{i if i<0x8000 else i-65536}",end="")

# expand
def expand(hl,l):
    hl=hl&0xffff
    l=l&0xffff
    b=nbit(l)

    # ヘッダ
    if l==0:
        print("ld hl,0")
        hl=0
        return hl

    print("ld hl,",end='')
    print2complement(hl)
    print("; 被乗数 この行を省けばhlの値は何でもいい。");
    print("ld d,h");
    print("ld e,l");
    de=hl;

    # 展開
    for i in range(b-1,-1,-1):
        if l>>i & 1 and i!=b-1:
            print("add hl,de")
            hl = (hl+de)&0xffff
        if i:
            print("add hl,hl")
            hl = (hl+hl)&0xffff
    return hl

# main
def main(hl,l):
    hl=expand(hl,l)
    print(f";hl=",end="")
    print2complement(hl)
    print("")
    return

if __name__=="__main__":
    if len(sys.argv)!=3:
        print("Usage:z80constmul.py <被乗数> <乗数>")
        exit(1)
    main(int(sys.argv[1]),int(sys.argv[2]))
    exit(0)

