bool check(int &grid[][], int i, int j, int val)
{
    int row = i - i%3, column = j - j%3;
    for(int x=0; x<9; x++) if(grid[x][j] == val) return false;
    for(int y=0; y<9; y++) if(grid[i][y] == val) return false;
    for(int x=0; x<3; x++)
    for(int y=0; y<3; y++)
        if(grid[row+x][column+y] == val) return false;
    return true;
}
bool solveSudoku(int grid[][], int i, int j)
{
    if(i==9) return true;
    if(j==9) return solveSudoku(grid, i+1, 0);
    if(grid[i][j] != 0) return solveSudoku(grid, i, j+1);

    for(int c=1; c<=9; c++)
    {
        if(check(grid, i, j, c))
        {
            grid[i][j] = c;
            if(solveSudoku(grid, i, j+1)) return true;
            grid[i][j] = 0;
        }
    }

    return false;
}
