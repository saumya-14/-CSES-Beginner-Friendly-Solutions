#include <bits/stdc++.h>
using namespace std;

/*
    BFS function to traverse one connected component (room)

    Parameters:
    - v   : the grid ('.' = free cell, '#' = wall)
    - vis : visited array to mark already visited cells
    - n,m : grid dimensions
    - row,col : starting cell for BFS
*/
void bfs(vector<vector<char>> &v,
         vector<vector<int>> &vis,
         int n, int m,
         int row, int col)
{
    // Mark the starting cell as visited
    vis[row][col] = 1;

    /*
        Direction array for moving in 4 directions:
        Up    -> (-1, 0)
        Left  -> (0, -1)
        Down  -> (1, 0)
        Right -> (0, 1)
    */
    int k[4][2] = {
        {-1, 0},
        {0, -1},
        {1, 0},
        {0, 1}
    };

    // Queue for BFS traversal
    queue<pair<int, int>> q;

    // Push the starting cell into the queue
    q.push({row, col});

    // Continue BFS until all reachable cells are processed
    while (!q.empty()) {

        // Get the front cell from the queue
        int a = q.front().first;
        int b = q.front().second;
        q.pop();

        // Try moving in all 4 directions
        for (int i = 0; i < 4; i++) {
            int x = a + k[i][0];
            int y = b + k[i][1];

            /*
                Conditions to move to the next cell:
                1. Cell is inside the grid
                2. Cell is a free cell ('.')
                3. Cell is not visited yet
            */
            if (x >= 0 && x < n &&
                y >= 0 && y < m &&
                v[x][y] == '.' &&
                vis[x][y] == 0)
            {
                // Mark the cell as visited
                vis[x][y] = 1;

                // Add the cell to the queue
                q.push({x, y});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read grid dimensions
    int n, m;
    cin >> n >> m;

    // Read the grid
    vector<vector<char>> v(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> v[i][j];
        }
    }

    // Visited array to track visited cells
    vector<vector<int>> vis(n, vector<int>(m, 0));

    /*
        cnt will store the number of rooms

        Idea:
        - Each unvisited '.' cell is the start of a new room
        - Run BFS from that cell to mark the entire room
    */
    int cnt = 0;

    // Traverse the entire grid
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            // If the cell is free and not visited
            if (v[i][j] == '.' && vis[i][j] == 0) {

                // We found a new room
                cnt++;

                // Traverse the entire room using BFS
                bfs(v, vis, n, m, i, j);
            }
        }
    }

    // Output the number of rooms
    cout << cnt << endl;

    return 0;
}
