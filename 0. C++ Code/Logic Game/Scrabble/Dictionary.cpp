//
//  Dictionary.cpp


#include "Dictionary.h"

#include <fstream>
#include <string>

using namespace std;


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
