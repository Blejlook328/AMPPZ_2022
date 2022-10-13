// Slow solution, reading and writing char by char.

#include <bits/stdc++.h>
using namespace std;

void makeShift(char& c) {
    c = 'a' + ((c - 'a') + 13) % 26;
}

int main() {
  int z;
  scanf("%d\n", &z);
  while (z--) {
    char c;
    for (int i = 0; ; i++) {
      scanf("%c", &c);
      if(c == '\n')
        break;
      makeShift(c);
      printf("%c", c);
    }
    printf("\n");
  }
  return 0;
}
