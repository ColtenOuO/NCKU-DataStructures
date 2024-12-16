#include <stdio.h>
int slot[101][1001];
int n, s;
int main() {
    for(int i=0;i<=100;i++) for(int j=0;j<=1000;j++) slot[i][j] = -1;
    char opt[101] = {};
    while( scanf("%s", opt) ) {
        if( opt[0] == 'e' ) break;
        if( opt[0] == 'b' ) {
            scanf("%d", &n);
        }
        if( opt[0] == 'i' ) {
            int num;
            scanf("%d", &num);
            int hash = num % n;
            int ok = 0;
            for(int i=0;i<s;i++) {
                if( slot[hash][i] == -1) {
                    slot[hash][i] = num;
                    ok = 1;
                    break;
                }
            }

            if( ok == 0 ) {
                while( hash + 1 <= n && ok == 0 ) {
                    hash++;
                    for(int i=0;i<s;i++) {
                        if( slot[hash][i] == -1) {
                            slot[hash][i] = num;
                            ok = 1;
                            break;
                        }
                    }
                }
            }
        }
        if( opt[0] == 's' && opt[1] == 'l' ) {
            scanf("%d", &s);
        }
        if( opt[0] == 'd' ) {
            int num;
            scanf("%d", &num);
            int hash = num % n;
            for(int i=0;i<s;i++) {
                if( slot[hash][i] == num ) {
                    slot[hash][i] = -1;
                    break;
                }
            }
        }
        if( opt[0] == 's' && opt[1] == 'e' ) {
            int num;
            scanf("%d", &num);
            int hash = num % n;
            int ans1 = 0;
            for(int i=0;i<=n;i++) {
                for(int j=0;j<=s;j++) {
                    if( slot[i][j] == num ) {
                        printf("%d %d\n", i, j);
                    }
                }
            }
        }
    }

    return 0;
}