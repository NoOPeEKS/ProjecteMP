//
//  Tile.hpp
//  Scrabble
//

#ifndef Tile_hpp
#define Tile_hpp


class Tile
{
public:
    Tile();
    Tile(char letter, int score): m_letter(letter), m_score(score) {}
    
    char getLetter() { return m_letter; }
    unsigned int getScore() { return m_score; }
    void setLetter(char letter) { m_letter = letter; }
    void setScore(unsigned int score) { m_score = score; }
    
private:
    char m_letter;
    unsigned int m_score;
};


#endif /* Tile_hpp */
