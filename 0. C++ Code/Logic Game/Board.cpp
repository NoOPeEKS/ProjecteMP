//
//  Board.cpp
//  Scrabble
//

#include "Board.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

Board::Board(Dictionary dictionary, Cell cells[BOARD_COLS_AND_ROWS][BOARD_COLS_AND_ROWS], const string& fitxerConfig)
{
	m_nFitxesJugades = 0;
	m_torn = 0;
	ifstream fitxer;
	fitxer.open(fitxerConfig);

	if (fitxer.is_open())
	{
		int row, col;
		string effect;
		vector<int> fila;
		vector<int> columna;
		vector<string> efecte;

		fitxer >> row >> col >> effect;

		while (!fitxer.eof())
		{
			fila.push_back(row);
			columna.push_back(col);
			efecte.push_back(effect);
			fitxer >> row >> col >> effect;
		}

		ScoreEffect s;

		for (int i = 0; i < fila.size(); i++)
		{
			if (efecte[i] == "DL")
				s = DL;
			else if (efecte[i] == "TL")
				s = TL;
			else if (efecte[i] == "DW")
				s = DW;
			else if (efecte[i] == "TW")
				s = TW;
			else
				s = NO_EFFECT;

			cells[fila[i]][columna[i]].setScoreEffect(s);
		}

		fitxer.close();
	}

	
}

PositionResult Board::setTile(Tile& tile, const BoardPosition& boardPos)
{
	
	if (m_cells[boardPos.getRow()][boardPos.getCol()].getEmpty() == true)
	{
		m_cells[boardPos.getRow()][boardPos.getCol()].setEmpty(false);
		m_cells[boardPos.getRow()][boardPos.getCol()].setTile(tile);
		m_fitxesTornActual[m_nFitxesJugades] = m_cells[boardPos.getRow()][boardPos.getCol()];
		m_nFitxesJugades++;
		return VALID_POSITION;
	}
	else if (m_cells[boardPos.getRow()][boardPos.getCol()].getEmpty() == false)
	{
		return NOT_EMPTY;
	}
}

CurrentWordResult Board::checkCurrentWord(int& points)
{
        int wordColumns[7]
        int wordRows[7]
    
        //Check if vertical or horizontal positive
	for (int i = 0; i < m_nFitxesJugades; i++)
	{
                wordColumns[i] = m_fitxesTornActual[i].getCol();
                wordRows[i] = m_fitxesTornActual[i].getRow();
	}
	bool horitzontal = true, vertical = true;
	for (int i = 1; i < m_nFitxesJugades; i++)
	{
                if (wordColumns[i] != wordColumns[0])
                        vertical = false;
        }
        for (int i = 1; i < m_nFitxesJugades; i++)
	{
                if (wordRows[i] != wordRows[0])
                        horitzontal = false;
        }
        if (horitzontal == false && vertical == false)
                return INVALID_NOT_ALIGNED;
        
        
        //hem de trobar màxim i mínim fila o columa per mirar que la difereǹcia entre mínim i màxim sigui nFitxesJugades
}

