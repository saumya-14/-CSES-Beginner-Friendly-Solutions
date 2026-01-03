#include <bits/stdc++.h>
using namespace std;

const vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const vector<char> dirChar = {'U', 'D', 'L', 'R'};

/* 
   Problem link:https://cses.fi/problemset/task/1193
    BFS function to find shortest path from 'A' to 'B' in a labyrinth

    Parameters:
    - v      : the grid ('.' = free cell, '#' = wall, 'A' = start, 'B' = end)
    - n, m   : grid dimensions
    - startX, startY : starting position (where 'A' is located)

    Returns:
    - pair<int, string> : {path_length, path_string}
      - If path found: returns {length, "UDLR..."}
      - If no path: returns {-1, ""}
*/
pair<int, string> bfs(vector<vector<char>> &v, int n, int m, int startX, int startY) {
    vector<vector<int>> vis(n, vector<int>(m, 0));
    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1})); 
    queue<pair<int, int>> q; 

    vis[startX][startY] = 1;
    q.push({startX, startY});

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        // If we reached the destination 'B'
        if (v[x][y] == 'B') {
            string path = "";
            while (parent[x][y] != make_pair(-1, -1)) {
                auto [px, py] = parent[x][y];
                for (int d = 0; d < 4; ++d) {
                    if (px + directions[d].first == x && py + directions[d].second == y) {
                        path += dirChar[d];
                        break;
                    }
                }
                x = px, y = py;
            }
            reverse(path.begin(), path.end());
            return {path.size(), path};
        }

        // Try all 4 directions
        for (int d = 0; d < 4; ++d) {
            int nx = x + directions[d].first;
            int ny = y + directions[d].second;

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && vis[nx][ny] == 0 && (v[nx][ny] == '.' || v[nx][ny] == 'B')) {
                vis[nx][ny] = 1;
                parent[nx][ny] = {x, y};
                q.push({nx, ny});
            }
        }
    }

    // No path found
    return {-1, ""};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<char>> v(n, vector<char>(m));
    pair<int, int> start = {-1, -1};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> v[i][j];
            if (v[i][j] == 'A') {
                start = {i, j};
            }
        }
    }

    if (start.first == -1) {
        cout << "NO" << endl;
        return 0;
    }

    auto [length, path] = bfs(v, n, m, start.first, start.second);

    if (length != -1) {
        cout << "YES" << endl;
        cout << length << endl;
        cout << path << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}

