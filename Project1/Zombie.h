//
//  Zombie.hpp
//  Project1Retry
//
//  Created by Collin Prince on 1/9/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

#ifndef Zombie_h
#define Zombie_h



class Arena;

class Zombie
{
public:
    // Constructor
    Zombie(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool getAttacked(int dir);
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
};


#endif /* Zombie_h */
