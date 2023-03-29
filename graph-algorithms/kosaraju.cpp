#include <iostream>
#include <vector>

using namespace std;

#define ll long long int
#define F first
#define S second
#define pb push_back
#define pf push_front
#define si set<int>
#define pii pair<int, int>
#define vi vector<int>
#define vb vector<bool>
#define vpii vector<pii>
#define vvi vector<vector<int>>
#define vvpii vector<vector<pii>>
#define mii map<int, int>
#define mpiii map<pii, int>
#define spii set<pii>
#define all(P) (P).begin(), (P).end()
#define FOR(i, j, k, in) for (int i = j; i < k; i += in)
#define RFOR(i, j, k, in) for (int i = j; i >= k; i -= in)
#define foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define que_max priority_queue<int>
#define que_min priority_queue<int, VI, greater<int>>
#define bug(...) __f(#__VA_ARGS__, __VA_ARGS__)
#define print(a)                       \
  for (auto x : (a)) cout << x << " "; \
  cout << endl;
#define printPairs(a)                                   \
  for (auto x : (a)) cout << x.F << " " << x.S << endl; \
  cout << endl;
#define printRange(a, x, y)                              \
  for (int i = (x); i < (y); i++) cout << (a)[i] << " "; \
  cout << endl;

inline int power(int a, int b) {
  int x = 1;
  while (b) {
    if (b & 1) x *= a;
    a *= a;
    b >>= 1;
  }
  return x;
}

/* Debug */
template <typename Arg1>
void __f(const char* name, Arg1&& arg1) {
  cout << name << ": " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args) {
  const char* comma = strchr(names + 1, ',');
  cout.write(names, comma - names) << ": " << arg1 << " | ";
  __f(comma + 1, args...);
}

// Kosaraju's algorithm

const int N = 1e5;

vi gr[N];
vi grr[N];  // reverse graph

int vis[N];
vi order;

int col[N];

vi components[N];

void dfs1(int cur) {
  vis[cur] = 1;
  for (auto x : gr[cur]) {
    if (!vis[x]) dfs1(x);
  }
  order.push_back(cur);
}

void dfs2(int cur, int comp) {
  vis[cur] = 1;
  col[cur] = comp;
  components[comp].pb(cur);
  for (auto x : grr[cur]) {
    if (!vis[x]) dfs2(x, comp);
  }
}

void solve() {
  // cin takes input from input.txt
  // cout outputs to output.txt

  int edges, vertices;
  cin >> edges >> vertices;

  while (edges--) {
    int x, y;
    cin >> x >> y;
    gr[x].push_back(y);
    grr[y].push_back(x);
  }

  // DFS for topological sort
  FOR(i, 1, vertices + 1, 1) {
    if (!vis[i]) dfs1(i);
  }
  reverse(all(order));
  // order has topological sort

  int comp = 1;
  memset(vis, 0, sizeof(vis));
  for (auto x : order) {
    if (!vis[x]) {
      dfs2(x, comp);
      comp++;
    }
  }

  FOR(i, 1, vertices + 1, 1) { cout << i << " " << col[i] << endl; }
  cout << endl;

  FOR(i, 1, comp, 1) {
    cout << i << ": ";
    for (auto num : components[i]) {
      cout << num << " ";
    }
    cout << endl;
  }
  cout << endl;

  cout << "Total SCC: " << comp - 1 << endl;
}

int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  clock_t z = clock();

  int t = 1;
  // cin >> t;
  while (t--) solve();

  cerr << "Run Time: " << ((double)(clock() - z) / CLOCKS_PER_SEC) << "s"
       << endl;

  return 0;
}
