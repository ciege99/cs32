//
//  History.h
//  Project1Retry
//
//  Created by Collin Prince on 1/9/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

#ifndef History_h
#define History_h

#include "globals.h"


class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    
private:
    int m_grid[MAXROWS][MAXCOLS];
    int m_nRows;
    int m_nCols;
};


#endif /* History_h */
