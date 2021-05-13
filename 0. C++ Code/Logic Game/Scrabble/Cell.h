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
    Cell() { m_empty = true; m_tilePlayed = false; m_scoreEffect = NO_EFFECT; m_tile.setLetter('?'); m_tile.setScore(-1); }
    ScoreEffect getScoreEffect() const { return m_scoreEffect; }
    Tile getTile() const { return m_tile; }
    bool getEmpty() const { return m_empty; }
    bool getTilePlayed() const { return m_tilePlayed; }
    void setScoreEffect(const ScoreEffect& scoreEffect) { m_scoreEffect = scoreEffect; }
    void setTile(Tile tile) { m_tile = tile; }
    void setEmpty(const bool& empty) { m_empty = empty; }
    void setTilePlayed(const bool& tilePlayed) { m_tilePlayed = tilePlayed; }

private:
    ScoreEffect m_scoreEffect;
    Tile m_tile;
    bool m_empty; // si està empty, està a true
    bool m_tilePlayed;
};


#endif /* Cell_hpp */
