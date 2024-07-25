int foo(int a) {
  if (a > 10) {
    return a * 2 + 8;
  }
  else {
    return a - 10;
  }
}

int bar(int a, int b) {
  if (a > b) {
    if (a > foo(b)) {
      return (a + foo(b) * 2);
    }
    else {
      return (foo(b) - 2);
    }
  }
  else {
    return (foo(a) + foo(b) / 2);
  }
}

int main(int argc, char *argv[]) {
  int a = 123;
  int ret = 0;

  ret += foo(a);
  ret += bar(a, ret);

  return ret;
}
