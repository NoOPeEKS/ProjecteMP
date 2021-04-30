//
//  Dictionary.cpp


#include "Dictionary.h"

#include <fstream>
#include <string>

using namespace std;

void Dictionary::setLanguage(Language language)
{
	m_currentLanguage = language;
	string nomFitxer = m_languagesPath[language];
	ifstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		string word;
		fitxer >> word;
		while (!fitxer.eof())
		{
			m_words.push_back(word);
			fitxer >> word;
		}

		fitxer.close();
	}
}

bool Dictionary::checkWord(const string& word)
{
	int i = 0;
	bool trobat = false;
	while(i < m_words.size() && !trobat)
	{
		if (m_words[i] == word)
			trobat = true;

		else
			i++;
	}

	if (trobat)
		return true;
	else
		return false;
}
