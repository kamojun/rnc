// 1行コメント

// 1行コメント
// が複数
// 並んでいる

/*
 * This is a block comment.
 */

int printf();
int exit();

int g1, g2[4];
short (*g3)[5];
typedef int MyInt, MyInt2[4];

static int static_fn() { return 3; }

// codeをactualに入れて評価して、expectedと比較する
int assert(int expected, int actual, char *code) {
  if (expected == actual) {
    printf("%s => %d\n", code, actual);
  } else {
    printf("%s => %d expected but got %d\n", code, expected, actual);
    exit(1);
  }
}

int ret3() {
  return 3;
  return 5;
}

int add2(int x, int y) { return x + y; }

int sub2(int x, int y) { return x - y; }

int add5(int a, int b, int c, int d, int e) { return a + b + c + d + e; }

int addx(int *x, int y) { return *x + y; }

int sub_char(char a, char b, char c) { return a - b - c; }

int sub_short(short a, short b, short c) {
   return a - b - c;
 }

 int sub_long(long a, long b, long c) {
   return a - b - c;
 }

int fib(int x) {
  if (x <= 1) return 1;
  return fib(x - 1) + fib(x - 2);
}
int add6(int a, int b, int c, int d, int e, int f) {
  return a + b + c + d + e + f;
}
int sumcheck(int a, int b, int c, int d, int e, int f) {
  return 32 * a + 16 * b + 8 * c + 4 * d + 2 * e + f;
}
int _add(int a, int b) { return a + 2 * b; }
_Bool bool_fn_add(_Bool x) { return x + 1; }
_Bool bool_fn_sub(_Bool x) { return x - 1; }

int main() {
  // 二項演算
  assert(0, 0, "0");
  assert(42, 42, "42");
  assert(21, 5 + 20 - 4, "5+20-4");
  assert(41, 12 + 34 - 5, " 12 + 34 - 5 ");
  assert(47, 5 + 6 * 7, "5+6*7");
  assert(15, 5 * (9 - 6), "5*(9-6)");
  assert(4, (3 + 5) / 2, "(3+5)/2");
  assert(10, -10 + 20, "-10+20");
  assert(10, - - 10, "- -10");
  assert(10, - - + 10, "- - +10");
  assert(0, 0 == 1, "0==1");
  assert(1, 42 == 42, "42==42");
  assert(1, 0 != 1, "0!=1");
  assert(0, 42 != 42, "42!=42");

  assert(1, 0 < 1, "0<1");
  assert(0, 1 < 1, "1<1");
  assert(0, 2 < 1, "2<1");
  assert(1, 0 <= 1, "0<=1");
  assert(1, 1 <= 1, "1<=1");
  assert(0, 2 <= 1, "2<=1");

  assert(1, 1 > 0, "1>0");
  assert(0, 1 > 1, "1>1");
  assert(0, 1 > 2, "1>2");
  assert(1, 1 >= 0, "1>=0");
  assert(1, 1 >= 1, "1>=1");
  assert(0, 1 >= 2, "1>=2");

  // 変数への代入、変数の計算
  assert(3, ({ int a; a = 3; a; }), "({ int a; a=3; a; })");
  assert(3, ({ int a = 3; a; }), "({ int a=3; a; })");
  assert(8, ({ int a = 3; int z = 5; a + z; }), "({ int a=3; int z=5; a+z; })");

  assert(3, ({ int a = 3; a; }), "({ int a=3; a; })");
  assert(8, ({ int a = 3; int z = 5; a + z; }), "({ int a=3; int z=5; a+z; })");
  assert(6, ({ int a; int b; a = b = 3; a + b; }), "({ int a; int b; a=b=3; a+b; })");
  assert(3, ({ int foo = 3; foo; }), "({ int foo=3; foo; })");
  assert(8, ({ int foo123 = 3; int bar = 5; foo123 + bar; }), "({ int foo123=3; int bar=5; foo123+bar; })");

  // if文
  assert(3, ({ int x; if (0) x = 2; else x = 3; x; }), "({ int x; if (0) x=2; else x=3; x; })");
  assert(3, ({ int x; if (1 - 1) x = 2; else x = 3; x; }), "({ int x; if (1-1) x=2; else x=3; x; })");
  assert(2, ({ int x; if (1) x = 2; else x = 3; x; }), "({ int x; if (1) x=2; else x=3; x; })");
  assert(2, ({ int x; if (2 - 1) x = 2; else x = 3; x; }), "({ int x; if (2-1) x=2; else x=3; x; })");
  assert(4, ({ int x; if (0) x = 2; else if (0) x = 3; else x = 4; x; }), "({ int x; if (0) x=2; else if (0) x=3; else x=4; x; })");

  // for文
  assert(55, ({ int i = 0; int j = 0; for (i = 0; i <= 10; i = i + 1) j = i + j; j; }), "({ int i=0; int j=0; for (i=0; i<=10; i=i+1) j=i+j; j; })");
  assert(385, ({ int i; int j; int x = 0; for (i = 1; i <= 10; i = i + 1) for (j = i; j <= 10; j = j + 1) x = x + j; x; }), "({ int i; int j; int x=0; for (i=1; i<=10; i=i+1) for (j=i; j<=10; j=j+1) x =x+j; x; })");

  // while文
  assert(10, ({ int i = 0; while (i < 10) i = i + 1; i; }), "({ int i=0; while(i<10) i=i+1; i; })");
  assert(3, ({ 1; { 2; } 3; }), "({ 1; {2;} 3; })");
  assert(10, ({ int i = 0; while (i < 10) i = i + 1; i; }), "({ int i=0; while(i<10) i=i+1; i; })");
  assert(55, ({ int i = 0; int j = 0; while (i <= 10) { j = i + j; i = i + 1; } j; }), "({ int i=0; int j=0; while(i<=10) {j=i+j; i=i+1;} j; })");

  // ポインタ演算
  assert(3, ({ int x = 3; *&x; }), "({ int x=3; *&x; })");
  assert(3, ({ int x = 3; int *y = &x; int **z = &y; **z; }), "({ int x=3; int *y=&x; int **z=&y; **z; })");
  assert(5, ({ int x = 3; int y = 5; *(&x + 1); }), "({ int x=3; int y=5; *(&x+1); })");
  assert(3, ({ int x = 3; int y = 5; *(&y - 1); }), "({ int x=3; int y=5; *(&y-1); })");
  assert(5, ({ int x = 3; int *y = &x; *y = 5; x; }), "({ int x=3; int *y=&x; *y=5; x; })");
  assert(7, ({ int x = 3; int y = 5; *(&x + 1) = 7; y; }), "({ int x=3; int y=5; *(&x+1)=7; y; })");
  assert(7, ({ int x = 3; int y = 5; *(&y - 1) = 7; x; }), "({ int x=3; int y=5; *(&y-1)=7; x; })");
  assert(2, ({ int x = 3; (&x + 2) - &x; }), "({ int x=3; (&x+2)-&x; })");
  assert(8, ({ int x, y; x = 3; y = 5; x + y; }), "({ int x, y; x=3; y=5; x+y; })");
  assert(8, ({ int x = 3, y = 5; x + y; }), "({ int x=3, y=5; x+y; })");

  // 関数呼び出し
  assert(3, ret3(), "ret3()");
  assert(8, add2(3, 5), "add2(3, 5)");
  assert(2, sub2(5, 3), "sub2(5, 3)");
  assert(15, add5(1, 2, 3, 4, 5), "add5(1,2,3,4,5)");
  assert(7, add2(3, 4), "add2(3,4)");
  assert(1, sub2(4, 3), "sub2(4,3)");
  assert(55, fib(9), "fib(9)");
  assert(21, add6(1, 2, 3, 4, 5, 6), "add6(1,2,3,4,5,6)");
  assert(63, add6(1, 2, 4, 8, 16, 32), "return add6(1,2,4,8,16,32)");
  assert(192, sumcheck(1, 2, 4, 8, 16, 32), "sumcheck(1,2,4,8,16,32)");
  assert(18, 1 + _add(1, _add(2, 3)), "1 + _add(1, _add(2, 3))");

  // 配列
  assert(3, ({ int x[2]; int *y = &x; *y = 3; *x; }), "({ int x[2]; int *y=&x; *y=3; *x; })");
  assert(3, ({ int x[3]; *x = 3; *(x + 1) = 4; *(x + 2) = 5; *x; }), "({ int x[3]; *x=3; *(x+1)=4; *(x+2)=5; *x; })");
  assert(4, ({ int x[3]; *x = 3; *(x + 1) = 4; *(x + 2) = 5; *(x + 1); }), "({ int x[3]; *x=3; *(x+1)=4; *(x+2)=5; *(x+1); })");
  assert(5, ({ int x[3]; *x = 3; *(x + 1) = 4; *(x + 2) = 5; *(x + 2); }), "({ int x[3]; *x=3; *(x+1)=4; *(x+2)=5; *(x+2); })");
  assert(0, ({ int x[2][3]; int *y = x; *y = 0; **x; }), "({ int x[2][3]; int *y=x; *y=0; **x; })");
  assert(1, ({ int x[2][3]; int *y = x; *(y + 1) = 1; *(*x + 1); }), "({ int x[2][3]; int *y=x; *(y+1)=1; *(*x+1); })");
  assert(2, ({ int x[2][3]; int *y = x; *(y + 2) = 2; *(*x + 2); }), "({ int x[2][3]; int *y=x; *(y+2)=2; *(*x+2); })");
  assert(3, ({ int x[2][3]; int *y = x; *(y + 3) = 3; **(x + 1); }), "({ int x[2][3]; int *y=x; *(y+3)=3; **(x+1); })");
  assert(4, ({ int x[2][3]; int *y = x; *(y + 4) = 4; *(*(x + 1) + 1); }), "({ int x[2][3]; int *y=x; *(y+4)=4; *(*(x+1)+1); })");
  assert(5, ({ int x[2][3]; int *y = x; *(y + 5) = 5; *(*(x + 1) + 2); }), "({ int x[2][3]; int *y=x; *(y+5)=5; *(*(x+1)+2); })");

  // 配列の[]演算子
  assert(3, ({ int x[3]; *x = 3; x[1] = 4; x[2] = 5; *x; }), "({ int x[3]; *x=3; x[1]=4; x[2]=5; *x; })");
  assert(4, ({ int x[3]; *x = 3; x[1] = 4; x[2] = 5; *(x + 1); }), "({ int x[3]; *x=3; x[1]=4; x[2]=5; *(x+1); })");
  assert(5, ({ int x[3]; *x = 3; x[1] = 4; x[2] = 5; *(x + 2); }), "({ int x[3]; *x=3; x[1]=4; x[2]=5; *(x+2); })");
  assert(5, ({ int x[3]; *x = 3; x[1] = 4; x[2] = 5; *(x + 2); }), "({ int x[3]; *x=3; x[1]=4; x[2]=5; *(x+2); })");
  assert(5, ({ int x[3]; *x = 3; x[1] = 4; 2 [x] = 5; *(x + 2); }), "({ int x[3]; *x=3; x[1]=4; 2[x]=5; *(x+2); })");
  assert(0, ({ int x[2][3]; int *y = x; y[0] = 0; x[0][0]; }), "({ int x[2][3]; int *y=x; y[0]=0; x[0][0]; })");
  assert(1, ({ int x[2][3]; int *y = x; y[1] = 1; x[0][1]; }), "({ int x[2][3]; int *y=x; y[1]=1; x[0][1]; })");
  assert(2, ({ int x[2][3]; int *y = x; y[2] = 2; x[0][2]; }), "({ int x[2][3]; int *y=x; y[2]=2; x[0][2]; })");
  assert(3, ({ int x[2][3]; int *y = x; y[3] = 3; x[1][0]; }), "({ int x[2][3]; int *y=x; y[3]=3; x[1][0]; })");
  assert(4, ({ int x[2][3]; int *y = x; y[4] = 4; x[1][1]; }), "({ int x[2][3]; int *y=x; y[4]=4; x[1][1]; })");
  assert(5, ({ int x[2][3]; int *y = x; y[5] = 5; x[1][2]; }), "({ int x[2][3]; int *y=x; y[5]=5; x[1][2]; })");

  // sizeof
  assert(4, ({ int x; sizeof(x); }), "({ int x; sizeof(x); })");
  assert(4, ({ int x; sizeof x; }), "({ int x; sizeof x; })");
  assert(8, ({ int *x; sizeof(x); }), "({ int *x; sizeof(x); })");
  assert(16, ({ int x[4]; sizeof(x); }), "({ int x[4]; sizeof(x); })");
  assert(48, ({ int x[3][4]; sizeof(x); }), "({ int x[3][4]; sizeof(x); })");
  assert(16, ({ int x[3][4]; sizeof(*x); }), "({ int x[3][4]; sizeof(*x); })");
  assert(4, ({ int x[3][4]; sizeof(**x); }), "({ int x[3][4]; sizeof(**x); })");
  assert(5, ({ int x[3][4]; sizeof(**x) + 1; }), "({ int x[3][4]; sizeof(**x) + 1; })");
  assert(5, ({ int x[3][4]; sizeof **x + 1; }), "({ int x[3][4]; sizeof **x + 1; })");
  assert(4, ({ int x[3][4]; sizeof(**x + 1); }), "({ int x[3][4]; sizeof(**x + 1); })");
  assert(4, ({ int x = 1; sizeof(x = 2); }), "({ int x=1; sizeof(x=2); })");
  assert(1, ({ int x = 1; sizeof(x = 2); x; }), "({ int x=1; sizeof(x=2); x; })");

  assert(0, g1, "g1");
  assert(3, ({ g1 = 3; g1; }), "({ g1=3; g1; })");
  assert(0, ({ g2[0] = 0; g2[1] = 1; g2[2] = 2; g2[3] = 3; g2[0]; }), "({ g2[0]=0; g2[1]=1; g2[2]=2; g2[3]=3; g2[0]; })");
  assert(1, ({ g2[0] = 0; g2[1] = 1; g2[2] = 2; g2[3] = 3; g2[1]; }), "({ g2[0]=0; g2[1]=1; g2[2]=2; g2[3]=3; g2[1]; })");
  assert(2, ({ g2[0] = 0; g2[1] = 1; g2[2] = 2; g2[3] = 3; g2[2]; }), "({ g2[0]=0; g2[1]=1; g2[2]=2; g2[3]=3; g2[2]; })");
  assert(3, ({ g2[0] = 0; g2[1] = 1; g2[2] = 2; g2[3] = 3; g2[3]; }), "({ g2[0]=0; g2[1]=1; g2[2]=2; g2[3]=3; g2[3]; })");

  assert(4, sizeof(g1), "sizeof(g1)");
  assert(16, sizeof(g2), "sizeof(g2)");

  assert(1, ({ char x = 1; x; }), "({ char x=1; x; })");
  assert(-56, ({ char x = 200; x; }), "({ char x=200; x; })");  // charはsigned扱い。200は-56になる。
  assert(1, ({ char x = 1; char y = 2; x; }), "({ char x=1; char y=2; x; })");
  assert(2, ({ char x = 1; char y = 2; y; }), "({ char x=1; char y=2; y; })");

  assert(1, ({ char x; sizeof(x); }), "({ char x; sizeof(x); })");
  assert(10, ({ char x[10]; sizeof(x); }), "({ char x[10]; sizeof(x); })");
  assert(1, ({ sub_char(7, 3, 3); }), "({ sub_char(7, 3, 3); })");

  assert(97, "abc"[0], "\"abc\"[0]");
  assert(98, "abc"[1], "\"abc\"[1]");
  assert(99, "abc"[2], "\"abc\"[2]");
  assert(0, "abc"[3], "\"abc\"[3]");
  assert(4, sizeof("abc"), "sizeof(\"abc\")");

  assert(7, "\a"[0], "\"\\a\"[0]");
  assert(8, "\b"[0], "\"\\b\"[0]");
  assert(9, "\t"[0], "\"\\t\"[0]");
  assert(10, "\n"[0], "\"\\n\"[0]");
  assert(11, "\v"[0], "\"\\v\"[0]");
  assert(12, "\f"[0], "\"\\f\"[0]");
  assert(13, "\r"[0], "\"\\r\"[0]");
  assert(27, "\e"[0], "\"\\e\"[0]");

  assert(106, "\j"[0], "\"\\j\"[0]");
  assert(107, "\k"[0], "\"\\k\"[0]");
  assert(108, "\l"[0], "\"\\l\"[0]");

  assert(7, "\ax\ny"[0], "\"\\ax\\ny\"[0]");
  assert(120, "\ax\ny"[1], "\"\\ax\\ny\"[1]");
  assert(10, "\ax\ny"[2], "\"\\ax\\ny\"[2]");
  assert(121, "\ax\ny"[3], "\"\\ax\\ny\"[3]");

  assert(0, "\0"[0], "\"\\0\"[0]");
  assert(16, "\20"[0], "\"\\20\"[0]");
  assert(65, "\101"[0], "\"\\101\"[0]");
  assert(104, "\1500"[0], "\"\\1500\"[0]");
  assert(0, "\x00"[0], "\"\\x00\"[0]");
  assert(119, "\x77"[0], "\"\\x77\"[0]");

  // 文式
  assert(2, ({ int x = 2; { int x = 3; } x; }), "({ int x=2; { int x=3; } x; })");
  assert(2, ({ int x = 2; { int x = 3; } int y = 4; x; }), "({ int x=2; { int x=3; } int y=4; x; })");
  assert(3, ({ int x = 2; { x = 3; } x; }), "({ int x=2; { x=3; } x; })");
  assert(2, ({ int x[5]; int *y = x + 2; y - x; }), "({ int x[5]; int *y=x+2; y-x; })");

  // カンマ演算子
  assert(3, (1, 2, 3), "(1,2,3)");
  assert(5, ({ int i = 2, j = 3; (i = 5, j) = 6; i; }), "({ int i=2, j=3; (i=5,j)=6; i; })");
  assert(6, ({ int i = 2, j = 3; (i = 5, j) = 6; j; }), "({ int i=2, j=3; (i=5,j)=6; j; })");

  // 構造体
  assert(1, ({ struct { int a; } x; x.a = 1; x.a; }), "({ struct {int a; int b;} x; x.a=1; x.b=2; x.a; })");
  assert(2, ({ struct { int a; int b; } x; x.a = 1; x.b = 2; x.b; }), "({ struct {int a; int b;} x; x.a=1; x.b=2; x.b; })");
  assert(1, ({ struct { char a; int b; char c; } x; x.a = 1; x.b = 2; x.c = 3; x.a; }), "({ struct {char a; int b; char c;} x; x.a=1; x.b=2; x.c=3; x.a; })");
  assert(2, ({ struct { char a; int b; char c; } x; x.b = 1; x.b = 2; x.c = 3; x.b; }), "({ struct {char a; int b; char c;} x; x.b=1; x.b=2; x.c=3; x.b; })");
  assert(3, ({ struct { char a; int b; char c; } x; x.a = 1; x.b = 2; x.c = 3; x.c; }), "({ struct {char a; int b; char c;} x; x.a=1; x.b=2; x.c=3; x.c; })");
  assert(0, ({ struct { int a; int b; } x[3]; int *p = x; p[0] = 0; x[0].a; }), "({ struct {int a; int b;} x[3]; int *p=x; p[0]=0; x[0].a; })");
  assert(1, ({ struct { int a; int b; } x[3]; int *p = x; p[1] = 1; x[0].b; }), "({ struct {int a; int b;} x[3]; int *p=x; p[1]=1; x[0].b; })");
  assert(2, ({ struct { int a; int b; } x[3]; int *p = x; p[2] = 2; x[1].a; }), "({ struct {int a; int b;} x[3]; int *p=x; p[2]=2; x[1].a; })");
  assert(3, ({ struct { int a; int b; } x[3]; int *p = x; p[3] = 3; x[1].b; }), "({ struct {int a; int b;} x[3]; int *p=x; p[3]=3; x[1].b; })");
  assert(6, ({ struct { int a[3]; int b[5]; } x; int *p = &x; x.a[0] = 6; p[0]; }), "({ struct {int a[3]; int b[5];} x; int *p=&x; x.a[0]=6; p[0]; })");
  assert(7, ({ struct { int a[3]; int b[5]; } x; int *p = &x; x.b[0] = 7; p[3]; }), "({ struct {int a[3]; int b[5];} x; int *p=&x; x.b[0]=7; p[3]; })");
  assert(6, ({ struct { struct { int b; } a; } x; x.a.b = 6; x.a.b; }), "({ struct { struct { int b; } a; } x; x.a.b=6; x.a.b; })");

  // 構造体のsizeof
  assert(4, ({ struct { int a; } x; sizeof(x); }), "({ struct {int a;} x; sizeof(x); })");
  assert(8, ({ struct { int a; int b; } x; sizeof(x); }), "({ struct {int a; int b;} x; sizeof(x); })");
  assert(8, ({ struct { int a, b; } x; sizeof(x); }), "({ struct {int a, b;} x; sizeof(x); })");
  assert(12, ({ struct { int a[3]; } x; sizeof(x); }), "({ struct {int a[3];} x; sizeof(x); })");
  assert(16, ({ struct { int a; } x[4]; sizeof(x); }), "({ struct {int a;} x[4]; sizeof(x); })");
  assert(24, ({ struct { int a[3]; } x[2]; sizeof(x); }), "({ struct {int a[3];} x[2]; sizeof(x); })");
  assert(2, ({ struct { char a; char b; } x; sizeof(x); }), "({ struct {char a; char b;} x; sizeof(x); })");
  assert(8, ({ struct { char a; int b; } *x; sizeof(x); }), "({ struct {char a; int b;} *x; sizeof(x); })");
  assert(8, ({ struct { char a; int b; } x; sizeof(x); }), "({ struct {char a; int b;} x; sizeof(x); })");
  assert(8, ({ struct { int a; char b; } x; sizeof(x); }), "({ struct {int a; char b;} x; sizeof(x); })");
  assert(12, ({ struct { int a; struct { char c; int b; } y; } x; sizeof(x); }), "({ struct {int a; struct {char c; int b} y;} x; sizeof(x); })");
  assert(7, ({
           int x;  // 32-35  // 0-31は非揮発性レジスタ
           int y;  // 36-39  // 48-54は空(パディング)
           char z; // 43  <- 変数のオフセットはコードの後方から順にに計算して行き、後からマイナスをつけるので、位置としては、直後の変数にくっついている
           char *a = &y;  // 44-51
           char *b = &z;  // 52-59  // この後64まで確保されている
           b - a;
         }),
         "({ int x; int y; char z; char *a=&y; char *b=&z; b-a; })");
  assert(1, ({ int x; char y; int z; char *a = &y; char *b = &z; b - a; }), "({ int x; char y; int z; char *a=&y; char *b=&z; b-a; })");
  assert(20, ({ struct t { char a[20]; }; { struct t { char a[40]; }; } struct t y; sizeof(y); }), "({ struct t {char a[20];}; { struct t {char a[40];}; } struct t y; sizeof(y); })");
  assert(3, ({ struct t { int x; }; int t = 1; struct t y; y.x = 2; t + y.x; }), "({ struct t {int x;}; int t=1; struct t y; y.x=2; t+y.x; })");
  assert(3, ({ struct t { char a; } x; struct t *y = &x; x.a = 3; y->a; }), "({ struct t {char a;} x; struct t *y = &x; x.a=3; y->a; })");
  assert(3, ({ struct t { char a; } x; struct t *y = &x; y->a = 3; x.a; }), "({ struct t {char a;} x; struct t *y = &x; y->a=3; x.a; })");
  assert(8, ({ union { int a; char b[6]; } x; sizeof(x); }), "({ union { int a; char b[6]; } x; sizeof(x); })");
  assert(3, ({ union { int a; char b[4]; } x; x.a = 515; x.b[0]; }), "({ union { int a; char b[4]; } x; x.a = 515; x.b[0]; })");
  assert(2, ({ union { int a; char b[4]; } x; x.a = 515; x.b[1]; }), "({ union { int a; char b[4]; } x; x.a = 515; x.b[1]; })");
  assert(0, ({ union { int a; char b[4]; } x; x.a = 515; x.b[2]; }), "({ union { int a; char b[4]; } x; x.a = 515; x.b[2]; })");
  assert(0, ({ union { int a; char b[4]; } x; x.a = 515; x.b[3]; }), "({ union { int a; char b[4]; } x; x.a = 515; x.b[3]; })");

  assert(3, ({ struct {int a,b;} x,y; x.a=3; y=x; y.a; }), "({ struct {int a,b;} x,y; x.a=3; y=x; y.a; })");
  assert(5, ({ struct t {int a,b;}; struct t x; x.a=5; struct t y=x; y.a; }), "({ struct t {int a,b;}; struct t x; x.a=5; struct t y=x; y.a; })");
  assert(7, ({ struct t {int a,b;}; struct t x; x.a=7; struct t y; struct t *z=&y; *z=x; y.a; }), "({ struct t {int a,b;}; struct t x; x.a=7; struct t y; struct t *z=&y; *z=x; y.a; })");
  assert(7, ({ struct t {int a,b;}; struct t x; x.a=7; struct t y, *p=&x, *q=&y; *q=*p; y.a; }), "({ struct t {int a,b;}; struct t x; x.a=7; struct t y, *p=&x, *q=&y; *q=*p; y.a; })");
  assert(5, ({ struct t {char a, b;} x, y; x.a=5; y=x; y.a; }), "({ struct t {char a, b;} x, y; x.a=5; y=x; y.a; })");

  assert(8, ({ struct t {int a; int b;} x; struct t y; sizeof(y); }), "({ struct t {int a; int b;} x; struct t y; sizeof(y); })");
  assert(8, ({ struct t {int a; int b;}; struct t y; sizeof(y); }), "({ struct t {int a; int b;}; struct t y; sizeof(y); })");

  assert(2, ({ short x; sizeof(x); }), "({ short x; sizeof(x); })");
  assert(4, ({ struct {char a; short b;} x; sizeof(x); }), "({ struct {char a; short b;} x; sizeof(x); })");

  assert(8, ({ long x; sizeof(x); }), "({ long x; sizeof(x); })");
  assert(16, ({ struct {char a; long b;} x; sizeof(x); }), "({ struct {char a; long b;} x; sizeof(x); })");

  assert(1, sub_short(7, 3, 3), "sub_short(7, 3, 3)");
  assert(1, sub_long(7, 3, 3), "sub_long(7, 3, 3)");

  assert(24, ({ int *x[3]; sizeof(x); }), "({ int *x[3]; sizeof(x); })");
  assert(8, ({ int (*x)[3]; sizeof(x); }), "({ int (*x)[3]; sizeof(x); })");
  assert(3, ({ int *x[3]; int y; x[0]=&y; y=3; x[0][0]; }), "({ int *x[3]; int y; x[0]=&y; y=3; x[0][0]; })");
  assert(4, ({ int x[3]; int (*y)[3]=x; y[0][0]=4; y[0][0]; }), "({ int x[3]; int (*y)[3]=x; y[0][0]=4; y[0][0]; })");
  assert(8, sizeof g3, "sizeof g3");
  assert(10, sizeof *g3, "sizeof *g3");
  { void *x; }

  // long int や int long
  assert(1, ({ char x; sizeof(x); }), "({ char x; sizeof(x); })");
  assert(2, ({ short int x; sizeof(x); }), "({ short int x; sizeof(x); })");
  assert(2, ({ int short x; sizeof(x); }), "({ int short x; sizeof(x); })");
  assert(4, ({ int x; sizeof(x); }), "({ int x; sizeof(x); })");
  assert(8, ({ long int x; sizeof(x); }), "({ long int x; sizeof(x); })");
  assert(8, ({ int long x; sizeof(x); }), "({ int long x; sizeof(x); })");
  assert(8, ({ long long x; sizeof(x); }), "({ long long x; sizeof(x); })");

  // typedef
  assert(1, ({ typedef int t; t x=1; x; }), "({ typedef int t; t x=1; x; })");
  assert(1, ({ typedef struct {int a;} t; t x; x.a=1; x.a; }), "({ typedef struct {int a;} t; t x; x.a=1; x.a; })");
  assert(2, ({ typedef struct {int a;} t; { typedef int t; } t x; x.a=2; x.a; }), "({ typedef struct {int a;} t; { typedef int t; } t x; x.a=2; x.a; })");
  assert(4, ({ typedef t; t x; sizeof(x); }), "({ typedef t; t x; sizeof(x); })");  // 指定のないtypedef はintにする
  assert(3, ({ MyInt x=3; x; }), "({ MyInt x=3; x; })");
  assert(16, ({ MyInt2 x; sizeof(x); }), "({ MyInt2 x; sizeof(x); })");  

  // type inside sizeof
  assert(1, sizeof(char), "sizeof(char)");
  assert(2, sizeof(short), "sizeof(short)");
  assert(2, sizeof(short int), "sizeof(short int)");
  assert(2, sizeof(int short), "sizeof(int short)");
  assert(4, sizeof(int), "sizeof(int)");
  assert(8, sizeof(long), "sizeof(long)");
  assert(8, sizeof(long int), "sizeof(long int)");
  assert(8, sizeof(long int), "sizeof(long int)");
  assert(8, sizeof(char *), "sizeof(char *)");
  assert(8, sizeof(int *), "sizeof(int *)");
  assert(8, sizeof(long *), "sizeof(long *)");
  assert(8, sizeof(int **), "sizeof(int **)");
  assert(8, sizeof(int(*)[4]), "sizeof(int(*)[4])");
  assert(32, sizeof(int*[4]), "sizeof(int*[4])");
  assert(16, sizeof(int[4]), "sizeof(int[4])");
  assert(48, sizeof(int[3][4]), "sizeof(int[3][4])");
  assert(8, sizeof(struct {int a; int b;}), "sizeof(struct {int a; int b;})");
  // type cast
  assert(131585, (int)8590066177, "(int)8590066177");
  assert(513, (short)8590066177, "(short)8590066177");
  assert(1, (char)8590066177, "(char)8590066177");
  assert(1, (long)1, "(long)1");
  assert(0, (long)&*(int *)0, "(long)&*(int *)0");
  assert(513, ({ int x=512; *(char *)&x=1; x; }), "({ int x=512; *(char *)&x=1; x; })");
  assert(5, ({ int x=5; long y=(long)&x; *(int*)y; }), "({ int x=5; long y=(long)&x; *(int*)y; })");
  (void)1;

  // ブロックスコープ
  assert(2, ({int x = 1; ({int x = 2; x;}); }),  "({int x = 1; ({int x = 2; x;}) })");

  // bool型
  assert(0, ({ _Bool x=0; x; }), "({ _Bool x=0; x; })");
  assert(1, ({ _Bool x=1; x; }), "({ _Bool x=1; x; })");
  assert(1, ({ _Bool x=2; x; }), "({ _Bool x=2; x; })");
  assert(1, (_Bool)1, "(_Bool)1");
  assert(1, (_Bool)2, "(_Bool)2");
  assert(0, (_Bool)(char)256, "(_Bool)(char)256");
  assert(1, bool_fn_add(3), "bool_fn_add(3)");
  assert(0, bool_fn_sub(3), "bool_fn_sub(3)");
  assert(1, bool_fn_add(-3), "bool_fn_add(-3)");
  assert(0, bool_fn_sub(-3), "bool_fn_sub(-3)");
  assert(1, bool_fn_add(0), "bool_fn_add(0)");
  assert(1, bool_fn_sub(0), "bool_fn_sub(0)");

  // char literal
  assert(92, '\\', "'\\\\'");
  assert(97, 'a', "'a'");
  assert(10, '\n', "'\\n'");
  assert(4, sizeof('a'), "sizeof('a')");

  // union
  assert(0, ({ enum { zero, one, two }; zero; }), "({ enum { zero, one, two }; zero; })");
  assert(1, ({ enum { zero, one, two }; one; }), "({ enum { zero, one, two }; one; })");
  assert(2, ({ enum { zero, one, two }; two; }), "({ enum { zero, one, two }; two; })");
  assert(5, ({ enum { five=5, six, seven }; five; }), "({ enum { five=5, six, seven }; five; })");
  assert(6, ({ enum { five=5, six, seven }; six; }), "({ enum { five=5, six, seven }; six; })");
  assert(0, ({ enum { zero, five=5, three=3, four }; zero; }), "({ enum { zero, five=5, three=3, four }; zero; })");
  assert(5, ({ enum { zero, five=5, three=3, four }; five; }), "({ enum { zero, five=5, three=3, four }; five; })");
  assert(3, ({ enum { zero, five=5, three=3, four }; three; }), "({ enum { zero, five=5, three=3, four }; three; })");
  assert(4, ({ enum { zero, five=5, three=3, four }; four; }), "({ enum { zero, five=5, three=3, four }; four; })");
  assert(5, ({ enum { zero, five=5, three=3, four, five2 }; five2; }), "({ enum { zero, five=5, three=3, four, five2 }; five2; })");
  assert(4, ({ enum { zero, one, two } x; sizeof(x); }), "({ enum { zero, one, two } x; sizeof(x); })");
  assert(4, ({ enum t { zero, one, two }; enum t y; sizeof(y); }), "({ enum t { zero, one, two }; enum t y; sizeof(y); })");

  // static関数
  assert(3, static_fn(), "static_fn()");
   // for文の中で変数宣言
  assert(55, ({ int j=0; for (int i=0; i<=10; i=i+1) j=j+i; j; }), "({ int j=0; for (int i=0; i<=10; i=i+1) j=j+i; j; })");
  assert(3, ({ int i=3; int j=0; for (int i=0; i<=10; i=i+1) j=j+i; i; }), "({ int i=3; int j=0; for (int i=0; i<=10; i=i+1) j=j+i; i; })");

  // +=, -=, /=, *=
  assert(7, ({ int i=2; i+=5; i; }), "({ int i=2; i+=5; i; })");
  assert(7, ({ int i=2; i+=5; }), "({ int i=2; i+=5; })");
  assert(3, ({ int i=5; i-=2; i; }), "({ int i=5; i-=2; i; })");
  assert(3, ({ int i=5; i-=2; }), "({ int i=5; i-=2; })");
  assert(6, ({ int i=3; i*=2; i; }), "({ int i=3; i*=2; i; })");
  assert(6, ({ int i=3; i*=2; }), "({ int i=3; i*=2; })");
  assert(3, ({ int i=6; i/=2; i; }), "({ int i=6; i/=2; i; })");
  assert(3, ({ int i=6; i/=2; }), "({ int i=6; i/=2; })");

  // 前置++, --
  assert(3, ({ int i=2; ++i; }), "({ int i=2; ++i; })");
  assert(11, ({ int a[3]; a[0]=0; a[1]=10; a[2]=20; int *p=a+1; ++*p; }), "({ int a[3]; a[0]=0; a[1]=10; a[2]=20; int *p=a+1; ++*p; })");
  assert(9, ({ int a[3]; a[0]=-1; a[1]=10; a[2]=2; int *p=a+1; --*p; }), "({ int a[3]; a[0]=-1; a[1]=1; a[2]=2; int *p=a+1; --*p; })");
  assert(3, ({ int x=2, y=3, z=5, *p=&x; *(++p); }), "({ int i=2; ++i; })");
  // 後置++, --  
  assert(2, ({ int i=2; i++; }), "({ int i=2; i++; })");
  assert(2, ({ int i=2; i--; }), "({ int i=2; i--; })");
  assert(3, ({ int i=2; i++; i; }), "({ int i=2; i++; i; })");
  assert(1, ({ int i=2; i--; i; }), "({ int i=2; i--; i; })");
  assert(1, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; *p++; }), "({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; *p++; })");
  assert(3, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; *p++; ++*p; }), "({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; *p++; })");
  assert(1, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; *p--; }), "({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; *p--; })");
  assert(0, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p++)--; a[0]; }), "({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p++)--; a[0]; })");
  assert(0, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*(p--))--; a[1]; }), "({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*(p--))--; a[1]; })");
  assert(2, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p)--; a[2]; }), "({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p)--; a[2]; })");
  assert(2, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p)--; p++; *p; }), "({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p)--; p++; *p; })");

  assert(0, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p++)--; a[0]; }), "({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p++)--; a[0]; })");
  assert(0, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p++)--; a[1]; }), "({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p++)--; a[1]; })");
  assert(2, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p++)--; a[2]; }), "({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p++)--; a[2]; })");
  assert(2, ({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p++)--; *p; }), "({ int a[3]; a[0]=0; a[1]=1; a[2]=2; int *p=a+1; (*p++)--; *p; })");

  // 2進、8進、16進リテラル
  assert(511, 0777, "0777");
  assert(0, 0x0, "0x0");
  assert(10, 0xa, "0xa");
  assert(10, 0XA, "0XA");
  assert(48879, 0xbeef, "0xbeef");
  assert(48879, 0xBEEF, "0xBEEF");
  assert(48879, 0XBEEF, "0XBEEF");
  assert(0, 0b0, "0b0");
  assert(1, 0b1, "0b1");
  assert(47, 0b101111, "0b101111");
  assert(47, 0B101111, "0B101111");

  // 否定演算子
  assert(0, !1, "!1");
  assert(0, !2, "!2");
  assert(1, !0, "!0");
  assert(1, !(char)0, "!(char)0");
  assert(0, !(long)3, "!(long)3");
  assert(4, sizeof(!(char)0), "sizeof(!(char)0)");
  assert(4, sizeof(!(long)0), "sizeof(!(long)0)");
  assert(-1, ~0, "~0");
  assert(0, ~-1, "~-1");
  assert(-2, ({short x=1; ~x; }), "({short x=1; ~x; })");
  assert(-1, ({enum {A, B}; ~A;}), "({enum {A, B}; ~A;})");

  // mod演算子
  assert(5, 17%6, "17%6");
  assert(5, ((long)17)%6, "((long)17)%6");
  assert(2, ({ int i=10; i%=4; i; }), "({ int i=10; i%=4; i; })");
  assert(2, ({ long i=10; i%=4; i; }), "({ long i=10; i%=4; i; })");

  // ビットand, or, xor
  assert(0, 0&1, "0&1");
  assert(1, 3&1, "3&1");
  assert(3, 7&3, "7&3");
  assert(10, -1&10, "-1&10");
  assert(1, 0|1, "0|1");
  assert(0b10011, 0b10000|0b00011, "0b10000|0b00011");
  assert(0, 0^0, "0^0");
  assert(0, 0b1111^0b1111, "0b1111^0b1111");
  assert(0b110100, 0b111000^0b001100, "0b111000^0b001100");
  assert(2, ({ int i=6; i&=3; i; }), "({ int i=6; i&=3; i; })");
  assert(7, ({ int i=6; i|=3; i; }), "({ int i=6; i|=3; i; })");
  assert(10, ({ int i=15; i^=5; i; }), "({ int i=15; i^=5; i; })");
  printf("OK\n");

  // 論理and, or
  assert(1, 0||1, "0||1");
  assert(1, 0||(2-2)||5, "0||(2-2)||5");
  assert(0, 0||0, "0||0");
  assert(0, 0||(2-2), "0||(2-2)");
  assert(0, 0&&1, "0&&1");
  assert(0, (2-2)&&5, "(2-2)&&5");
  assert(1, 1&&5, "1&&5");
  return 0;
}