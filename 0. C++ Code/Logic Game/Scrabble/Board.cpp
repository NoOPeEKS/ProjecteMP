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
	ifstream fitxer;
	fitxer.open(fitxerConfig);

	if (fitxer.is_open())
	{
		int row, col;
		ScoreEffect effect;
		vector<int> fila;
		vector<int> columna;
		vector<ScoreEffect> efecte;

		fitxer >> row >> col >> effect;

		while (!fitxer.eof())
		{
			fila.push_back(row);
			columna.push_back(col);
			efecte.push_back(effect);
			fitxer >> row >> col >> effect;
		}

		for (int i = 0; i < fila.size(); i++)
		{
			cells[fila[i]][columna[i]].setScoreEffect(1);
		}

		fitxer.close();
	}

	
}



