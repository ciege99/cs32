//
//  Game.hpp
//  Project1Retry
//
//  Created by Collin Prince on 1/9/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

#ifndef Game_h
#define Game_h


class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};


#endif /* Game_h */
