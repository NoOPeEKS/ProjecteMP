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

const string fitxerConfig = "data/Configuration/board.txt";
Board::Board()
{
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

			m_cells[fila[i]][columna[i]].setScoreEffect(s);
		}

		fitxer.close();
	}

	
}

PositionResult Board::setTile(Tile& tile, const BoardPosition& boardPos)
{
	int row = boardPos.getRow();
	int col = boardPos.getCol();
	if (row > 15 || row < 0 || col > 15 || col < 0)
		return INVALID_POSITION;

	else if (m_cells[row][col].getEmpty() == true && m_cells[row][col].getTilePlayed() == false)
	{
		m_cells[row][col].setTile(tile);
		m_cells[row][col].setEmpty(false);
		return VALID_POSITION;
	}

	else if (m_cells[row][col].getEmpty() == false)
		return NOT_EMPTY;
}

CurrentWordResult Board::checkCurrentWord(int& points)
{
	points = 0;
	BoardPosition cellPos;
	vector<BoardPosition> board;
	bool aligned = false;

	// Guardem la vector de tipus BoardPosition board totes les fitxes que hi han col·locades
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (m_cells[i][j].getEmpty() == false)
			{
				cellPos.setCol(j);
				cellPos.setRow(i);
				board.push_back(cellPos);

			}
		}
	}

	// El primer que cal fer és mirar si la cel·la del mig, posició (7,7) està buida o no. Si està plena, farem les comprovacions pertinents.
	if (m_cells[7][7].getEmpty() == false)
	{
		// Després cal comprovar si és la primera jugada o no.
		if (m_cells[7][7].getTilePlayed() == false)
		{
			if ((m_cells[7][8].getEmpty() == false || m_cells[7][6].getEmpty() == false) && (m_cells[6][7].getEmpty() == false || m_cells[8][7].getEmpty() == false))
			{
				removeCurrentWord();
				return INVALID_NOT_ALIGNED;
			}

			else if (m_cells[7][8].getEmpty() != false && m_cells[7][6].getEmpty() != false && m_cells[6][7].getEmpty() != false && m_cells[8][7].getEmpty() != false)
			{
				removeCurrentWord();
				return INVALID_WORD_OF_ONE_LETTER;
			}

			else
				aligned = true;
		}
		else
		{
			while (0 < board.size())
			{
				cellPos = board[board.size() - 1];

				if (m_cells[cellPos.getRow()][cellPos.getCol()].getTilePlayed() == false)
				{
					// Bottom-right corner
					if (cellPos.getCol() == 14 && cellPos.getRow() == 14)
					{
						if ((m_cells[cellPos.getRow()][cellPos.getCol() - 1].getEmpty() == true) && (m_cells[cellPos.getRow() - 1][cellPos.getCol()].getEmpty() == true))
						{
							removeCurrentWord();
							return INVALID_WORD_OF_ONE_LETTER;
						}
						else if (!aligned && (m_cells[cellPos.getRow()][cellPos.getCol() - 1].getTilePlayed() == true) || (m_cells[cellPos.getRow() - 1][cellPos.getCol()].getTilePlayed() == true))
							aligned = true;

					}

					// Bottom-left corner
					else if (cellPos.getCol() == 0 && cellPos.getRow() == 14)
					{
						if ((m_cells[cellPos.getRow() - 1][cellPos.getCol()].getEmpty() == true) && (m_cells[cellPos.getRow()][cellPos.getCol() + 1].getEmpty() == true))
						{
							removeCurrentWord();
							return INVALID_WORD_OF_ONE_LETTER;
						}
						else if ((m_cells[cellPos.getRow() - 1][cellPos.getCol()].getTilePlayed() == true) || (m_cells[cellPos.getRow()][cellPos.getCol() + 1].getTilePlayed() == true) && !aligned)
							aligned = true;
					}

					// First row
					else if (cellPos.getRow() == 0 && cellPos.getCol() < 14)
					{
						if ((m_cells[cellPos.getRow() + 1][cellPos.getCol()].getEmpty() == true) && (m_cells[cellPos.getRow()][cellPos.getCol() + 1].getEmpty() == true) && (m_cells[cellPos.getRow()][cellPos.getCol() - 1].getEmpty() == true))
						{
							removeCurrentWord();
							return INVALID_WORD_OF_ONE_LETTER;
						}
						else if ((m_cells[cellPos.getRow() + 1][cellPos.getCol()].getTilePlayed() == true) || (m_cells[cellPos.getRow()][cellPos.getCol() + 1].getTilePlayed() == true) || (m_cells[cellPos.getRow()][cellPos.getCol() - 1].getTilePlayed() == true) && !aligned)
							aligned = true;
					}

					// Last row
					else if ((cellPos.getRow() == 14) && (cellPos.getCol() > 0))
					{
						if ((m_cells[cellPos.getRow() - 1][cellPos.getCol()].getEmpty() == true) && (m_cells[cellPos.getRow()][cellPos.getCol() - 1].getEmpty() == true) && (m_cells[cellPos.getRow()][cellPos.getCol() + 1].getEmpty() == true))
						{
							removeCurrentWord();
							return INVALID_WORD_OF_ONE_LETTER;
						}
						else if ((m_cells[cellPos.getRow() - 1][cellPos.getCol()].getTilePlayed() == true) || (m_cells[cellPos.getRow()][cellPos.getCol() - 1].getTilePlayed() == true) || (m_cells[cellPos.getRow()][cellPos.getCol() + 1].getTilePlayed() == true) && !aligned)
								aligned = true;
					}

					// First column
					else if (cellPos.getCol() == 0 && cellPos.getRow() > 0)
					{
						if ((m_cells[cellPos.getRow() - 1][cellPos.getCol()].getEmpty() == true) && (m_cells[cellPos.getRow()][cellPos.getCol() + 1].getEmpty() == true) && (m_cells[cellPos.getRow() + 1][cellPos.getCol()].getEmpty() == true))
						{
							removeCurrentWord();
							return INVALID_WORD_OF_ONE_LETTER;
						}
						else if ((m_cells[cellPos.getRow() - 1][cellPos.getCol()].getTilePlayed() == true) || (m_cells[cellPos.getRow()][cellPos.getCol() + 1].getTilePlayed() == true) || (m_cells[cellPos.getRow() + 1][cellPos.getCol()].getTilePlayed() == true) && !aligned)
							aligned = true;
					}

					// Last column
					else if (cellPos.getCol() == 14 && cellPos.getRow() > 0)
					{
						if ((m_cells[cellPos.getRow() + 1][cellPos.getCol()].getEmpty() == true) && (m_cells[cellPos.getRow()][cellPos.getCol() - 1].getEmpty() == true) && (m_cells[cellPos.getRow() + 1][cellPos.getCol()].getEmpty() == true))
						{
							removeCurrentWord();
							return INVALID_WORD_OF_ONE_LETTER;
						}
						else if ((m_cells[cellPos.getRow() + 1][cellPos.getCol()].getTilePlayed() == true) || (m_cells[cellPos.getRow()][cellPos.getCol() - 1].getTilePlayed() == true) || (m_cells[cellPos.getRow() + 1][cellPos.getCol()].getTilePlayed() == true) && !aligned)
							aligned = true;
					}

					// Top-right corner
					else if (cellPos.getRow() == 0 && cellPos.getCol() == 14)
					{
						if ((m_cells[cellPos.getRow() + 1][cellPos.getCol()].getEmpty() == true) && (m_cells[cellPos.getRow()][cellPos.getCol() - 1].getEmpty() == true))
						{
							removeCurrentWord();
							return INVALID_WORD_OF_ONE_LETTER;
						}
						else if ((m_cells[cellPos.getRow() + 1][cellPos.getCol()].getTilePlayed() == true) || (m_cells[cellPos.getRow()][cellPos.getCol() - 1].getTilePlayed() == true) && !aligned)
							aligned = true;
					}

					// Top-left corner
					else if (cellPos.getCol() == 0 && cellPos.getRow() == 0)
					{
						if ((m_cells[cellPos.getRow() + 1][cellPos.getCol()].getEmpty() == true) && (m_cells[cellPos.getRow()][cellPos.getCol() + 1].getEmpty() == true))
						{
							removeCurrentWord();
							return INVALID_WORD_OF_ONE_LETTER;
						}
						else if ((m_cells[cellPos.getRow() + 1][cellPos.getCol()].getTilePlayed() == true) || (m_cells[cellPos.getRow()][cellPos.getCol() + 1].getTilePlayed() == true) && !aligned)
							aligned = true;
					}

					else
					{
						if ((m_cells[cellPos.getRow() + 1][cellPos.getCol()].getEmpty() == true) && (m_cells[cellPos.getRow()][cellPos.getCol() - 1].getEmpty() == true) && (m_cells[cellPos.getRow() - 1][cellPos.getCol()].getEmpty() == true) && (m_cells[cellPos.getRow()][cellPos.getCol() + 1].getEmpty() == true))
						{
							removeCurrentWord();
							return INVALID_WORD_OF_ONE_LETTER;
						}
						else if ((m_cells[cellPos.getRow() + 1][cellPos.getCol()].getTilePlayed() == true) || (m_cells[cellPos.getRow()][cellPos.getCol() - 1].getTilePlayed() == true) || (m_cells[cellPos.getRow() - 1][cellPos.getCol()].getTilePlayed() == true || m_cells[cellPos.getRow()][cellPos.getCol() + 1].getTilePlayed() == true) && !aligned)
							aligned = true;
					}
				}
				board.pop_back();
			}
		}
	}

	// Si no està plena, simplement eliminarem la currentWord i retornarem INVALID_START_NOT_IN_CENTER
	else
	{
		removeCurrentWord();
		return INVALID_START_NOT_IN_CENTER;

	}

	// Si el bool aligned == true, significa que les lletres són consecutives i que cal comprovar si són paraules que existeixen al diccionari o no.
	if (aligned) 
	{
		bool wordExists = true;
		BoardPosition cellPos;
		vector <BoardPosition> wordPos;
		string word = "";
		vector <ScoreEffect> effect;
		ScoreEffect cellEffect;

		// Primer mirem les paraules que es poden formar horitzontalment.
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (m_cells[i][j].getEmpty() == false)
				{
					cellPos.setCol(j);
					cellPos.setRow(i);
					wordPos.push_back(cellPos);
					cellEffect = m_cells[i][j].getScoreEffect();
					word = word + m_cells[i][j].getTile().getLetter();
					effect.push_back(cellEffect);
				}

				// Si la length de wordPos és >= 2 && no hi ha cap lletra més al costat, és candidata a ser una paraula del diccionari
				if (m_cells[i][j].getEmpty() != false && wordPos.size() >= 2)  
				{
					wordExists = m_dictionary.checkWord(word);
					bool trobat = false;
					int i = 0;

					// Mirem que la paraula estigui jugada (no té cap cel·la amb tilePlayed false)
					while (i < wordPos.size() && !trobat && wordExists)
					{
						cellPos = wordPos[i];
						int fila = cellPos.getRow();
						int columna = cellPos.getCol();

						if (m_cells[fila][columna].getTilePlayed() == false)
						{
							trobat = true;
						}
						else
							i++;

					}

					// Si alguna de les lletres de la paraula estava jugada, i la paraula existeix, comptem els punts de la que es forma
					if (trobat && wordExists)
					{
						int wordPoints = 0;
						int dw = 0; // --> dw = paraula doble
						int tw = 0; // --> tw = paraula triple
						for (int i = 0; i < wordPos.size(); i++)
						{
							cellPos = wordPos[i];
							cellEffect = effect[i];

							if (cellEffect == DL && m_cells[cellPos.getRow()][cellPos.getCol()].getTilePlayed() == false)
								wordPoints = wordPoints + (m_cells[cellPos.getRow()][cellPos.getCol()].getTile().getScore() * 2);

							else if (cellEffect == TL && m_cells[cellPos.getRow()][cellPos.getCol()].getTilePlayed() == false)
								wordPoints = wordPoints + (m_cells[cellPos.getRow()][cellPos.getCol()].getTile().getScore() * 3);

							else
								wordPoints = wordPoints + m_cells[cellPos.getRow()][cellPos.getCol()].getTile().getScore();

							if (cellEffect == DW && m_cells[cellPos.getRow()][cellPos.getCol()].getTilePlayed() == false)
								dw++;

							else if (cellEffect == TW && m_cells[cellPos.getRow()][cellPos.getCol()].getTilePlayed() == false)
								tw++;
						}


						// Calculem els punts de la paraula si conté DW
						if (dw != 0)
						{
							for (int i = 0; i < dw; i++)
							{
								wordPoints = wordPoints * 2;
								dw--;
							}
						}

						// Calculem els punts de la paraula si conté TW
						if (tw != 0)
						{
							for (int i = 0; i < tw; i++)
							{

								wordPoints = wordPoints * 3;
								tw--;

							}
						}
						points = points + wordPoints; 
					}


					word = ""; //--> Resetegem la paraula actual a nul·la
					wordPos.clear(); //--> Resetegem el vector de posicions de la paraula
					effect.clear(); //--> Resetegem el vector d'scoreEffects
				}
				else if (wordPos.size() < 2 && m_cells[i][j].getEmpty() == true)
				{
					wordPos.clear();
					effect.clear();
					word = "";
				}

				// Si la paraula no existeix al diccionari corresponent, els punts tornen a zero, es borra la paraula actual i retornem INVALID_WORDS_NOT_IN_DICTIONARY
				if (!wordExists)
				{
					points = 0;
					removeCurrentWord();
					return INVALID_WORDS_NOT_IN_DICTIONARY;
				}
			}
		}

		// Repetim el mateix procediment que abans, però canviant-ho per trobar-les verticalment.
		for (int j = 0; j < 15; j++) 
		{
			for (int i = 0; i < 15; i++)
			{
				if (m_cells[i][j].getEmpty() != true)
				{

					cellPos.setRow(i);
					cellPos.setCol(j);
					wordPos.push_back(cellPos);
					cellEffect = m_cells[i][j].getScoreEffect();
					effect.push_back(cellEffect);
					word = word + m_cells[i][j].getTile().getLetter();
				}

				if (m_cells[i][j].getEmpty() == true && wordPos.size() >= 2)
				{
					wordExists = m_dictionary.checkWord(word);
					bool trobat = false;
					int i = 0;
					while (i < wordPos.size() && !trobat && wordExists)
					{
						cellPos = wordPos[i];
						int fila = cellPos.getRow();
						int columna = cellPos.getCol();

						if (m_cells[fila][columna].getTilePlayed() == false)
							trobat = true;
						else
							i++;

					}

					if (wordExists && trobat)
					{
						int wordPoints = 0;
						int dw = 0;
						int tw = 0;
						for (int i = 0; i < wordPos.size(); i++)
						{
							cellPos = wordPos[i];
							cellEffect = effect[i];


							if (m_cells[cellPos.getRow()][cellPos.getCol()].getTilePlayed() == false && cellEffect == DL)
								wordPoints = wordPoints + m_cells[cellPos.getRow()][cellPos.getCol()].getTile().getScore() * 2;

							else if (m_cells[cellPos.getRow()][cellPos.getCol()].getTilePlayed() == false && cellEffect == TL)
								wordPoints = wordPoints + m_cells[cellPos.getRow()][cellPos.getCol()].getTile().getScore() * 3;

							else
								wordPoints = wordPoints + m_cells[cellPos.getRow()][cellPos.getCol()].getTile().getScore();

							if (cellEffect == DW && m_cells[cellPos.getRow()][cellPos.getCol()].getTilePlayed() == false)
								dw++;

							else if (cellEffect == TW && m_cells[cellPos.getRow()][cellPos.getCol()].getTilePlayed() == false)
								tw++;
						}

						if (dw != 0)
						{
							for (int i = 0; i < dw; i++)
							{
								wordPoints = wordPoints * 2;
								dw--;
							}
						}

						if (tw != 0)
						{
							for (int i = 0; i < tw; i++)
							{
								wordPoints = wordPoints * 3;
								tw--;
							}
						}
						points = points + wordPoints;
					}
					word = "";
					wordPos.clear();
					effect.clear();
				}
				else if (m_cells[i][j].getEmpty() == true && wordPos.size() < 2)
				{
					word = "";
					wordPos.clear();
					effect.clear();
				}

				if (!wordExists)
				{
					points = 0;
					removeCurrentWord();
					return INVALID_WORDS_NOT_IN_DICTIONARY;
				}
			}
		}
		sendCurrentWordToBoard();
		return ALL_CORRECT;
	}
	else
	{
		removeCurrentWord();
		return INVALID_NOT_CONNECTION;
	}
}

void Board::sendCurrentWordToBoard()
{
	// Revisem cel·la per cela si està plena, i si ho és, significa que amb la funció setTile la hem posada, per tant, assignem el bool setTilePlayed a true, de la cel·la en concret.
	for (int i = 0; i < BOARD_COLS_AND_ROWS; i++)
	{
		for (int j = 0; j < BOARD_COLS_AND_ROWS; j++)
		{
			if (m_cells[i][j].getEmpty() == false)
			{
				m_cells[i][j].setTilePlayed(true);
			}
		}
	}
}

void Board::removeCurrentWord()
{
	// Per borrar la paraula actual, creem una Tile amb els valors que té el constructor per defecte, i busquem al tauler les cel·les que hagin estat plenes però no played, i les substituim per la Tile per defecte.
	Tile a;
	a.setLetter('?');
	a.setScore(-1);
	for (int i = 0; i < BOARD_COLS_AND_ROWS; i++)
	{
		for (int j = 0; j < BOARD_COLS_AND_ROWS; j++)
		{
			if (m_cells[i][j].getEmpty() == false && m_cells[i][j].getTilePlayed() == false)
			{
				m_cells[i][j].setEmpty(true);
				m_cells[i][j].setTile(a);
			}
		}
	}

}