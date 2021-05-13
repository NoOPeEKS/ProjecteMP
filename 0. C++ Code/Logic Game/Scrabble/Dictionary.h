//
//  Dictionary.hpp
#pragma once

#include "Scrabble.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

const string englishDic = "data/Dictionaries/English.dic";
const string catalanDic = "data/Dictionaries/Catalan.dic";
const string spanishDic = "data/Dictionaries/Spanish.dic";

typedef enum {
    CATALAN = 0,
    SPANISH,
    ENGLISH,
    NO_LANGUAGE
} Language;

class Dictionary
{
public:
    Dictionary() 
    { 
        setLanguagesPath(); 
        m_currentLanguage = ENGLISH;
        string nomFitxer = m_languagePath[ENGLISH]; //COMENCEM X DEFECTE EN ANGLÈS
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

    void setLanguage(Language language) { m_currentLanguage = language; }
    Language getCurrentLanguage() const { return m_currentLanguage; }
    void setLanguagesPath() {
        m_languagePath[CATALAN] = catalanDic;
        m_languagePath[SPANISH] = spanishDic;
        m_languagePath[ENGLISH] = englishDic;
    }
    bool checkWord(const string& word);

private:
	vector<string> m_words;
    string m_languagePath[NO_LANGUAGE];
    Language m_currentLanguage;
    
};
