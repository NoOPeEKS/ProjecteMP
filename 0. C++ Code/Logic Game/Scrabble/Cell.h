//
//  Cell.hpp
//  Scrabble
//


#ifndef Cell_hpp
#define Cell_hpp

#include <stdio.h>
#include "Tile.h"

typedef enum {
    DL = 0,
    TL,
    DW,
    TW,
    NO_EFFECT
} ScoreEffect;

class Cell
{
public:
    Cell();
    Cell(ScoreEffect effect, Tile tile, bool empty, bool tilePlayed)
    {
        m_scoreEffect = effect;
        m_tile = tile;
        m_empty = empty;
        m_tilePlayed = tilePlayed;
    }
    

    ScoreEffect getScoreEffect() { return m_scoreEffect; }
    Tile getTile() { return m_tile; }
    bool getEmpty() { return m_empty; }
    bool getTilePlayed() { return m_tilePlayed; }
    void setScoreEffect(ScoreEffect scoreEffect) { m_scoreEffect = scoreEffect; }
    void setTile(Tile tile) { m_tile = tile; }
    void setEmpty(bool empty) { m_empty = empty; }
    void setTilePlayed(bool tilePlayed) { m_tilePlayed; }

private:
    ScoreEffect m_scoreEffect;
    Tile m_tile;
    bool m_empty;
    bool m_tilePlayed;
};


#endif /* Cell_hpp */
