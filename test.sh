#!/bin/bash

# <<EOFとやると、その次の行からEOFまでがcatに投入される。
CMD="cat <<EOF | gcc -xc -c -o tmp2.o -
int ret3() { return 3; }
int ret5() { return 5; }
int add(int x, int y) { return x+y; }
int sub(int x, int y) { return x-y; }

int add6(int a, int b, int c, int d, int e, int f) {
  return a+b+c+d+e+f;
}
int sumcheck(int a, int b, int c, int d, int e, int f) {
  return 32*a+16*b+8*c+4*d+2*e+f;
}
EOF"
docker run --rm --mount type=bind,src=$PWD/bind,dst=/home/user --workdir /home/user compilerbook /bin/bash -c "$CMD"

assert() {
  expected="$1"
  input="$2"

  ./target/debug/rnc "$input" > bind/tmp.s
  CMD="gcc -static -o tmp tmp.s tmp2.o; ./tmp"
  docker run --rm --mount type=bind,src=$PWD/bind,dst=/home/user --workdir /home/user compilerbook /bin/bash -c "$CMD"
  actual="$?"

  if [ "$actual" = "$expected" ]; then
    echo "$input => $expected"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

cargo build
assert 0 'int main() { return 0; }'
assert 42 'int main() { return 42; }'
assert 21 'int main() { return 5+20-4; }'
assert 41 'int main() { return  12 + 34 - 5 ; }'
assert 47 'int main() { return 5+6*7; }'
assert 15 'int main() { return 5*(9-6); }'
assert 4 'int main() { return (3+5)/2; }'
assert 10 'int main() { return -10+20; }'
assert 10 'int main() { return - -10; }'
assert 10 'int main() { return - - +10; }'

assert 0 'int main() { return 0==1; }'
assert 1 'int main() { return 42==42; }'
assert 1 'int main() { return 0!=1; }'
assert 0 'int main() { return 42!=42; }'

assert 1 'int main() { return 0<1; }'
assert 0 'int main() { return 1<1; }'
assert 0 'int main() { return 2<1; }'
assert 1 'int main() { return 0<=1; }'
assert 1 'int main() { return 1<=1; }'
assert 0 'int main() { return 2<=1; }'

assert 1 'int main() { return 1>0; }'
assert 0 'int main() { return 1>1; }'
assert 0 'int main() { return 1>2; }'
assert 1 'int main() { return 1>=0; }'
assert 1 'int main() { return 1>=1; }'
assert 0 'int main() { return 1>=2; }'

assert 3 'int main() { int a=3; return a; }'
assert 8 'int main() { int a=3; int z=5; return a+z; }'

assert 1 'int main() { return 1; 2; 3; }'
assert 2 'int main() { 1; return 2; 3; }'
assert 3 'int main() { 1; 2; return 3; }'

assert 3 'int main() { int foo=3; return foo; }'
assert 8 'int main() { int foo123=3, bar=5; return foo123+bar; }'

assert 3 'int main() { if (0) return 2; return 3; }'
assert 3 'int main() { if (1-1) return 2; return 3; }'
assert 2 'int main() { if (1) return 2; return 3; }'
assert 2 'int main() { if (2-1) return 2; return 3; }'

assert 3 'int main() { {1; {2;} return 3;} }'

assert 10 'int main() { int i=0; while(i<10) i=i+1; return i; }'
assert 55 'int main() { int i=0, j=0; while(i<=10) {j=i+j; i=i+1;} return j; }'

assert 55 'int main() { int i=0, j=0; for (i=0; i<=10; i=i+1) j=i+j; return j; }'
assert 3 'int main() { for (;;) return 3; return 5; }'

assert 55 "int main () { int a=0, b=0;while(b<10) a = a+(b = b+1); return a; }"
assert 45 "int main () { int i, a = 0;for(i=0; i<10; i = i+1) a = a + i; return a; }"
assert 55 "int main () { int a = 0; int i=0;for(;i<10;) a = a + (i=i+1); return a; }"
assert 42 "int main () { for(;;) return 42; }"
assert 89 "int main () { int i, a=1,b=1;for(i=0;i<10;i=i+1) {{int c=b;b=a+b;a=c;}} return a; }"

assert 3 'int main() { return ret3(); }'
assert 5 'int main() { return ret5(); }'
assert 8 'int main() { return add(3, 5); }'
assert 2 'int main() { return sub(5, 3); }'
assert 21 'int main() { return add6(1,2,3,4,5,6); }'
assert 63 'int main() { return add6(1,2,4,8,16,32); }'
assert 192 'int main() { return sumcheck(1,2,4,8,16,32); }'
assert 2 'int main() { int x; int a = x = 1; return a + x; }'


assert 3 'int main() { return ret32(); } int ret32() { return 3; }'
assert 5 'int main() { int x; int a = x = 1; return x + ret32(); } int ret32() { int b, a = b = 2; return a+b; }'

assert 3 'int main() { int x=3; int *y=&x, *z=&y; return **z; }'
assert 5 'int main() { int x=3; int y=5; return *(&x+1); }'
assert 3 'int main() { int x=3; int y=5; return *(&y-1); }'
assert 5 'int main() { int x=3, *y=&x; *y=5; return x; }'
assert 7 'int main() { int x=3; int y=5; *(&x+1)=7; return y; }'
assert 7 'int main() { int x=3; int y=5; *(&y-1)=7; return x; }'
assert 2 'int main() { int x=3; return (&x+2)-&x; }'

assert 7 'int main() { return 1 + _add(1, _add(2, 3)); } int _add(int a, int b) { return a+b; }'
assert 12 'int main() { return double_add(5, 2); } int double_add(int a, int b) { return 2*a+b; }'  # 引数の順番チェック
assert 1 'int main() { return is_odd(9); } int is_odd(int n) {if (n>0) return is_even(n-1); else return 0;} int is_even(int n) {if (n>0) return is_odd(n-1); else return 1;}'  # 複数関数定義チェック
assert 55 'int main() { return fib(9); } int fib(int x) { if (x<=1) return 1; return fib(x-1) + fib(x-2); }'

echo OK