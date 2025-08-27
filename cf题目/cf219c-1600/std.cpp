#include <iostream>
using namespace std;
int n, k, ans;
string s;
char Min(int);
int main() {
    cin >> n >> k >> s;
    if (k == 2) {
        string a, b;
        for (int i = 1; i <= n; i++) a += char('A' + (i % 2));
        for (int i = 1; i <= n; i++) b += char('A' + not (i % 2));
        int ca, cb;
        ca = cb = 0;
        for (int i = 0; i < n; i++) ca += a[i] != s[i];
        for (int i = 0; i < n; i++) cb += b[i] != s[i];
        cout << min(ca, cb) << "\n" << (ca < cb ? a : b);
        return 0;
    }
    for (int i = 1; i < s.size(); i++) {
        if (s[i] == s[i - 1]) {
            ans += 1;
            s[i] = Min(i);
        }
    }
    cout << ans << "\n" << s;
    return 0;
}
char Min(int x) {
    if (x == s.size() - 1)
        return s[x - 1] == 'A' ? 'B' : 'A';
    for (int i = 1; i <= k; i++) {
        char ch = i - 1 + 'A';
        if (ch != s[x - 1] and ch != s[x + 1]) return ch;
    }
    return '@';
}
