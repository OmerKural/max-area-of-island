#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

// Recursive depth first search function.
void search(vector<vector<int>> &grid, vector<vector<int>> &searched, int r, int c, int &area)
{
    /*
    First 4 conditions are out of bound checks, 
    5th one is if the position on grid is marked as a non-island pixel, 
    6th one is if we have searched this pixel already.
    */
    if (r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size() || grid[r][c] == 0 || searched[r][c] == 1)
    {
        return;
    }

    // Record in search grid.
    searched[r][c] = 1;

    // Calculate area (increase area by 1 every time we find a new pixel of the currently searched island).
    area++;

    // Search 4 ways
    search(grid, searched, r + 1, c, area); // Search down.
    search(grid, searched, r - 1, c, area); // Search up.
    search(grid, searched, r, c + 1, area); // Search right.
    search(grid, searched, r, c - 1, area); // Search left.
}

int maxAreaOfIsland(vector<vector<int>> &grid)
{
    int ans = 0, area;

    /* We are initiating the search grid with all zeroes (dimensions identical to the original grid) 
    in order to mark the searched areas with 1 later on.
    */
    vector<vector<int>> searched(grid.size(), vector<int>(grid[0].size(), 0));

    int r = 0, c = 0;

    // While we haven't finished searching all the grid.
    while (searched[searched.size() - 1][searched[0].size() - 1] == 0)
    {
        // If the pixel we are at haven't already been searched.
        if (searched[r][c] == 0)
        {
            // If the pixel we are on is from an island.
            if (grid[r][c] == 1)
            {
                area = 0;
                search(grid, searched, r, c, area);
                ans = max(ans, area);
            }
            // If the pixel we are on is not from an island.
            else
            {
                searched[r][c] = 1;
            }
        }

        // If the pixel we searched was from the end of the row, skip to the next row (with column 0).
        if (c + 1 == grid[0].size())
        {
            r++;
            c = 0;
        }
        // If not, just continue searching in the row.
        else
        {
            c++;
        }
    }

    return ans;
}

int main()
{
    // TEST CASE 1
    vector<vector<int>> grid = {
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}};

    cout << maxAreaOfIsland(grid) << endl; // should return 6

    return 0;
}
