//
//  Dictionary.hpp
#pragma once

#include "Scrabble.h"
#include <stdio.h>
#include <iostream>


typedef enum {
    CATALAN = 0,
    SPANISH,
    ENGLISH,
    NO_LANGUAGE
} Language;

class Dictionary
{
public:
    Dictionary();
    

    void setLanguage(Language language);
    Language getCurrentLanguage() { return m_currentLanguage; }
    void setLanguagesPath(string languagesPath[3]) {
        for (int i = 0; i < 3; i++)
        {
            m_languagesPath[i] = languagesPath[i];
        }
    }
    bool checkWord(const string& word);

private:
	vector<string> m_words;
    string m_languagesPath[NO_LANGUAGE];
    Language m_currentLanguage;
    
};
