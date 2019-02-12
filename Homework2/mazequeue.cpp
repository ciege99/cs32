//
//  mazequeue.cpp
//  Homework2
//
//  Created by Collin Prince on 2/1/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//
#include <queue>
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

//this will simplify the discovering algorithm
void discover(int r, int c, int nRows, int nCols, string maze[], queue<Coord> &coordQueue);

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
    queue<Coord> coordQueue;    //start off by creating a coordinate stack and pushing start onto it
    Coord start(sr, sc);
    coordQueue.push(start);
    maze[sr][sc] = 'O';         //O will mark discovered positions
    while (! coordQueue.empty())
    {
        Coord current = coordQueue.front();   //set current equal to top item then pop
        coordQueue.pop();
        if (current.r() == er && current.c() == ec) //check if we've reached end
            return true;
        
        discover(current.r()+1, current.c(), nRows, nCols, maze, coordQueue);   //south
        discover(current.r(), current.c()-1, nRows, nCols, maze, coordQueue);   //west
        discover(current.r()-1, current.c(), nRows, nCols, maze, coordQueue);   //north
        discover(current.r(), current.c()+1, nRows, nCols, maze, coordQueue);   //east
    }
    return false;
}
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

void discover(int r, int c, int nRows, int nCols, string maze[], queue<Coord> &coordQueue)
{
    if ((r <= nRows-1) && (r >= 0) && (c <= nCols-1) && (c >= 0) && (maze[r][c] == '.'))
    {   //if Coord is valid and undiscovered, mark it and push it onto queue
        maze[r][c] = 'O';
        coordQueue.push(Coord(r,c));
    }
}
