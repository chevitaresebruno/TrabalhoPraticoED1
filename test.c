#include <stdio.h>

int main() {
    int a[] = {1, 2, 3, 4, 5, 999};

    register int i=0;
    int o = 0;

    while (a[i] != 999)
    {
        a[i++] = 0;
    }

    for(; o<6; o++) {
        printf("%d\n", a[o]);

    }

    return 0;
}