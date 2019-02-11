//
//  History.cpp
//  Project1Retry
//
//  Created by Collin Prince on 1/9/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

#include "History.h"
#include "globals.h"

#include <iostream>

using namespace std;

History::History(int nRows, int nCols) {
    m_nRows = nRows;
    m_nCols = nCols;
    
    //initialize all valid positions to 0
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
            m_grid[i][j] = 0;
    }
}


bool History::record(int r, int c) {
    //check that position is valid
    if (r < 0 || r > MAXROWS-1 || c < 0 || c > MAXCOLS-1)
        return false;
    //increment number of zombies at that position
    m_grid[r][c] = m_grid[r][c] + 1;
    return true;
}

void History::display() const {
    // Position (row,col) of the arena coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < m_nRows; r++)
        for (c = 0; c < m_nCols; c++)
            grid[r][c] = '.';
    
    
    // Indicate each dead zombie's position
    for (r = 0; r < m_nRows; r++)
    {
        for (c = 0; c < m_nCols; c++)
        {
            if (m_grid[r][c] > 0)
            {
                int numZombies =  m_grid[r][c];
                grid[r][c] = 'A' + (numZombies -1);
                if (numZombies >= 26)
                    grid[r][c] = 'Z';
            }
        }
    }
    
    // Draw the grid
    clearScreen();
    
    
    for (r = 0; r < m_nRows; r++)
    {
        for (c = 0; c < m_nCols; c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
}




