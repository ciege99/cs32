//
//  main.cpp
//  Homework2
//
//  Created by Collin Prince on 2/1/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

#include <stack>
#include <string>
#include <iostream>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

//this will be used to simplify pathExists algorithm
void discover(int r, int c, int nRows, int nCols, string maze[], stack<Coord> &coordStack);

//int main()
//{
//    string maze[10] = {
//        "XXXXXXXXXX",
//        "X....X...X",
//        "X.XX.XX..X",
//        "XXX....X.X",
//        "X.XXX.XXXX",
//        "X.X...X..X",
//        "X...X.X..X",
//        "XXXXX.X.XX",
//        "X........X",
//        "XXXXXXXXXX"
//    };
//    
//    if (pathExists(maze, 10,10, 3,5, 8,8))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    stack<Coord> coordStack;    //start off by creating a coordinate stack and pushing start onto it
    Coord start(sr, sc);
    coordStack.push(start);
    maze[sr][sc] = 'O';         //O will mark discovered positions
    while (! coordStack.empty())
    {
        Coord current = coordStack.top();   //set current equal to top item then pop
        coordStack.pop();
        if (current.r() == er && current.c() == ec) //check if we've reached end
            return true;
        
        discover(current.r()+1, current.c(), nRows, nCols, maze, coordStack);   //south
        discover(current.r(), current.c()-1, nRows, nCols, maze, coordStack);   //west
        discover(current.r()-1, current.c(), nRows, nCols, maze, coordStack);   //north
        discover(current.r(), current.c()+1, nRows, nCols, maze, coordStack);   //east
    }
    return false;   //false if stack is empty, end was not reached and we have no undiscoverd points left
}
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

void discover(int r, int c, int nRows, int nCols, string maze[], stack<Coord> &coordStack)
{
    if ((r <= nRows-1) && (r >= 0) && (c <= nCols-1) && (c >= 0) && (maze[r][c] == '.'))
    {
        maze[r][c] = 'O';   //if Coord is valid and undiscovered, mark and push onto stack
        coordStack.push(Coord(r,c));
    }
}
