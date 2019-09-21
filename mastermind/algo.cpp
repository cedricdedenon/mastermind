#include "algo.hpp"

//Cette fonction retourne le nombre de caractères identiques et à la même place entre deux chaines de caractères
int Algo::egalite(string MotEntre, string MotSecret, int taille){
    int i=0, cpt=0;
    for(i=0;i<taille;i++){
        if(MotEntre[i]==MotSecret[i]){
            cpt++;
        }
    }
    return cpt;
}

//Cette fonction retourne le nombre de caractères presents dans les deux chaines de caracteres mais placé au mauvais endroit
int Algo::similarite(string MotEntre, string MotSecret, int taille){
    int i=0,j=0,cpt=0,flag=0;
    char caractere=0;
    string copieMotSecret;

    copieMotSecret=MotSecret.substr(0,taille);

    for(i=0;i<taille;i++){
        if(MotEntre[i]==copieMotSecret[i]){
            copieMotSecret[i]='X';
            MotEntre[i]='Y';
        }
    }

    for(i=0;i<taille;i++){
        flag=0;
        caractere=MotEntre[i];

        for(j=0;j<taille;j++){
            if (caractere==copieMotSecret[j] && flag==0){
                cpt++;
                flag=1;
                copieMotSecret[j]='X';
                break;
            }
        }
    }
    return cpt;
}

//Teste si deux chaines de caractères sont identiques (retourne true si oui, false sinon)
bool Algo::comparaison(string MotEntre, string MotSecret){
    if(MotEntre.compare(MotSecret)==0){
        return true;
    }
    return false;
}
