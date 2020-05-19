#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;

typedef struct s_trie {
    s_trie *children[26];
    int count;
} t_trie;

t_trie *root;

void insert(string &s) {
    t_trie *cur = root;
    for (char c: s) {
        int n = c - 'A';
        if (!cur->children[n])
            cur->children[n] = new t_trie();
        cur = cur->children[n];
    }
    cur->count++;
}

int ans;

void dfs(t_trie *cur, int lvl) {
    for (int i=0; i<26; i++) {
        if (cur->children[i]) {
            dfs(cur->children[i], lvl+1);
            cur->count += cur->children[i]->count;
        }
    }
    while (cur->count>=K) {
        cur->count -= K;
        ans += lvl;
    }
}

int main() {
    int t, tc;
    cin >> tc;
    for (t=0; t<tc; t++) {
        cin >> N >> K;
        root = new t_trie();
        ans = 0;
        for (int i=0; i<N; i++) {
            string s;
            cin >> s;
            insert(s);
        }
        dfs(root, 0);
        cout << "Case #" << t+1 << ": " << ans << endl;
    }
}
