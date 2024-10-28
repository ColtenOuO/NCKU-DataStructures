#include <stdio.h>
int mp[1001][1001], visited[1001];
int queue[1001];
int idx;
int main() {
    int n;
    scanf("%d", &n);
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            scanf("%d", &mp[i][j]);
        }
    }

    queue[0] = 1;
    visited[1] = 1;
    int front = 0;
    idx = 1;
    while( front < idx ) {
        int v = queue[front++];
        printf("%d ", v);
        for(int i=1;i<=n;i++) {
            if( visited[i] == 1 || mp[v][i] == 0 ) continue;
            visited[i] = 1;
            queue[idx++] = i;
        }
    }

    return 0;
}