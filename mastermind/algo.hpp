#ifndef ALGO_HPP
#define ALGO_HPP

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "dico.hpp"
using namespace std;

class Algo{
public:
    int egalite(string MotEntre, string MotSecret, int taille);
    int similarite(string MotEntre, string MotSecret, int taille);
    bool comparaison(string MotEntre, string MotSecret);
};

#endif // ALGO_HPP
