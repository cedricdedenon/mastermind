#ifndef DICO_HPP
#define DICO_HPP

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

class Dico{
public:
    string DestFichier(int taille);
    void copieFichierTaille(string Dest, string Source, int taille);
    bool fichierExistant(string fe);
    unsigned int nbMots(string d);
    vector<string> MotsAleatoires(string Source, int nbMotsAlea);
    bool verifdico(string Source, int nbMotsutil);
    string SelectionMotSecret(vector<string> TabMotsAleatoires, int nbMotsAlea);

};

#endif // DICO_HPP
