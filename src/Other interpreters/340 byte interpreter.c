#include <stdio.h>
#include <stdint.h>
#define a ;break;case
#define b return 0;}
int main(){static char c[65535],d[]="";static uint16_t e=0;static uint64_t f=0,g=0;for(g;g<sizeof(d);++g){switch(d[g]){case'+':c[e]++a'-':c[e]--a'>':e++a'<':e--a'.':putchar(c[e])a',':c[e]=getchar()a'[':f=++g;while(c[e] != 0){g=f;main();}break;case']':b}b