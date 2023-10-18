class Solution {
public:
    bool inbounds(int i, int j, int n) {
        return (0 <= i) && (i < n) && (0 <= j) && (j < n);
    }

    void printAccessibleGrid(const std::vector<std::vector<bool>>& grid) {
    int n = grid.size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << (grid[i][j] ? "1" : "0") << " ";
            }
            std::cout << std::endl;
        }
    }

    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
/*   
        // set an indicator for submerged
        vector<vector<bool>> submerged(n, vector<bool>(n, false));
        // initialize submerged cells 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    submerged[i][j] = true;
                }
            }
        }
*/
        // initialize an grid indicator for accessible cells
        vector<vector<bool>> accessible_grid(n, vector<bool>(n, false));
        
        // initialize a set indicator for accessible cells
        set<tuple<int,int>> accessible_set; // will only  increase in size

        // at the beginning, we are at (0,0) whatever the height of that cell is
        accessible_set.insert(make_tuple(0,0));
        accessible_grid[0][0] = true;

        int t = -1; // initialize time just before the beginning


        // initialize a set indicator of processed cells for every time round
        set<tuple<int,int>> processed;
        // initialize a queue to process cells adjacent from one another during one time round
        deque<tuple<int, int>> to_visit;
        
        do {
            t++;
            //std::cout << "\n===== ROUND t = " << t << " =====" << std::endl;
            // fill valleys gradually: rain pours
            // empty list of processed cells for that round
            // since every so far accessible cell may give access to a new path
            processed.clear();

            
            // fill the queue of accessible cells to be visited to process new path finding 
            for (const tuple<int,int>& cell : accessible_set) {
                to_visit.push_back(cell);
            }
                        
            
            // printAccessibleGrid(accessible_grid);

            while (!to_visit.empty()) {
                auto cell = to_visit.front();
                to_visit.pop_front();
                processed.insert(cell);
                int i = get<0>(cell);
                int j = get<1>(cell);
                
                //std::cout << "--> dépilé (" << i << ", " << j << ")" << std::endl;

                vector<tuple<int, int>> adjacent_cells = {{i, j + 1}, {i, j - 1}, {i + 1, j}, {i - 1, j}};

                for (auto& neighbouring_cell : adjacent_cells) { 
                    int u = get<0>(neighbouring_cell);
                    int v = get<1>(neighbouring_cell);
                    
                    

                    // set the adjecent cell as accessible and reinsert it to process for propagation if and only if
                    // 1) it's inbounds of the grid
                    // 2) it hasn't been processed before
                    // 3) it's submerged as well as the current cell
                    // (otherwise, not a part of a path at time t)

                    if (inbounds(u,v,n)) {
                        //std::cout << "cellule adjecente (" << u << ", " << v << ")" << ": ";
                        if (!processed.contains(neighbouring_cell)  && t >= grid[u][v] && t >= grid[i][j]) {
                        accessible_grid[u][v] = true;
                        accessible_set.insert(neighbouring_cell);
                        to_visit.push_back(neighbouring_cell);
                        //std::cout << "Ajoutée." << std::endl; 
                        }
                        else {
                            //std::cout << "Rejetée." << std::endl;  
                        }
                    }
                    
                }
            }
            
        } while (!accessible_grid.at(n-1).at(n-1));

        std::cout << "\n===== FINALE t = " << t << " =====" << std::endl;
        printAccessibleGrid(accessible_grid);

        return t;
    }
};
