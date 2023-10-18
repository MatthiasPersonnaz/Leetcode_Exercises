class Solution {
public:

    bool dfs(vector<vector<int>>& grid, int water_height, int n) {
        // std::cout << "appel à DFS" << std::endl;

        if (n == 1) {return true;}

        set<tuple<int,int>> processed;
        deque<tuple<int,int>> to_process;
        to_process.push_front(make_tuple(0,0)); // starting point always accessible
        
        while (!to_process.empty()) { // while there remain some cells to explore the neighbours of
            auto cell = to_process.front();
            to_process.pop_front();
            processed.insert(cell);
            int i = get<0>(cell);
            int j = get<1>(cell);
            vector<tuple<int, int>> adjacent_cells = {{i, j + 1}, {i, j - 1}, {i + 1, j}, {i - 1, j}};
            
            for (auto& neighbour : adjacent_cells) {  // for every possible adjecent cell
                int u = get<0>(neighbour);
                int v = get<1>(neighbour);
                if ((0 <= u) && (u < n) && (0 <= v) && (v < n) && (water_height >= grid[u][v]) && (water_height >= grid[i][j])) {
                    // if the cell exists in the grid and is accessible
                    if ((u == n - 1) && (v == n - 1)) { // check if it's the objective
                        return true; // break and return positive if so
                    }
                    else if (!processed.contains(neighbour)) {
                    to_process.push_front(neighbour); // else add to process if not already visited
                    }
                }
            }
        }
        return false; // if objective not accessible, return false
    }



    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int max_h = n*n;
        int min_h = 0;
        int ver_h = (max_h + min_h) / 2;

        int iter = 0;

        while ((min_h < max_h) && (iter < n)) {
            // std::cout << "==== ROUND " << iter << " ====" << std::endl;
            //std::cout << "min = " << min_h << " < " << ver_h << " < " << max_h << " = max" << std::endl;
            if (dfs(grid, ver_h, n)) {
                // std::cout << "access possible with h = " << ver_h << std::endl;
                max_h = ver_h;
            }
            else {
                // std::cout << "access impossible with h = " << ver_h << std::endl;
                min_h = ver_h + 1;
            }
            ver_h = (max_h + min_h) / 2;
            
            iter++;
        }
        // std::cout << "--> end loop: height found is " << ver_h << std::endl;  
        return ver_h;
    }
};
