#include "dico.hpp"

//Cette fonction retourne une chaine de caractères en fonction de la taille donnee en parametre
string Dico::DestFichier(int taille){
    string Dest;
    switch(taille){
        case 1: Dest=string("dico1.txt"); break;
        case 2: Dest=string("dico2.txt"); break;
        case 3: Dest=string("dico3.txt"); break;
        case 4: Dest=string("dico4.txt"); break;
        case 5: Dest=string("dico5.txt"); break;
        case 6: Dest=string("dico6.txt"); break;
        case 7: Dest=string("dico7.txt"); break;
        case 8: Dest=string("dico8.txt"); break;
        case 9: Dest=string("dico9.txt"); break;
        case 10: Dest=string("dico10.txt"); break;
        case 11: Dest=string("dico11.txt"); break;
        case 12: Dest=string("dico12.txt"); break;
        case 13: Dest=string("dico13.txt"); break;
        case 14: Dest=string("dico14.txt"); break;
        case 15: Dest=string("dico15.txt"); break;
        case 16: Dest=string("dico16.txt"); break;
        case 17: Dest=string("dico17.txt"); break;
        case 18: Dest=string("dico18.txt"); break;
        case 19: Dest=string("dico19.txt"); break;
        case 20: Dest=string("dico20.txt"); break;
        case 21: Dest=string("dico21.txt"); break;
        case 22: Dest=string("dico22.txt"); break;
        case 23: Dest=string("dico23.txt"); break;
        case 24: Dest=string("dico24.txt"); break;
        case 25: Dest=string("dico25.txt"); break;
        default: Dest=string("dicoN.txt"); break;
    }
    return Dest;
}

//Teste si un fichier existe déjà dans le répertoire courant
bool Dico::fichierExistant(string fe){
    ifstream flux(fe);
    //this->m_flux = ifstream(fe);
    if (flux)
    {
        flux.close();
        return true;    // Le fichier a pu etre ouvert => le fichier existe.
    }
    else
    {
         return false;   // L'ouverture du fichier a echoué => le fichier  n'existe pas.
    }
}

//Cette fonction compte le nombre de mots dans un fichier .txt, sachant qu'un seul mot se trouve sur chaque ligne
unsigned int Dico::nbMots(string d){
    ifstream flux (d);
    string mot;
    unsigned int nbMots(0);
    if(flux){
        while(getline(flux, mot)){
            nbMots++;
        }
     }
     else{
        exit(1);
     }
    flux.close();
    return nbMots;
}

//Cette fonction crée un nouveau fichier .txt contenant uniquement les mots de même taille à partir du fichier initial.
//Tous les mots contenant un ou plusieurs caractères (accents, tirets...) sont enlevés.
void Dico::copieFichierTaille(string Dest, string Source, int taille){
    ifstream fichierSource(Source);
    ofstream fichierDest(Dest);
    string mot;
    unsigned int i(0), flag(0);
    if(fichierSource || fichierDest)
    {
        while (getline(fichierSource, mot))
        {
            flag=0;
            if(mot.size()==taille)
            {
                for(i=0;i<taille;i++)
                {
                    if ((0x61 > mot[i])||( mot[i] > 0x7a))
                    {
                        flag=1;
                        break;
                    }
                }
                if (flag==0)
                {
                    fichierDest << mot << endl;
                }
            }
        }
    }
    else
    {
        exit(1);
    }
    fichierSource.close();
    fichierDest.close();
}

//Cette fonction choisi aléatoirement nbMotsAlea à partir d'un fichier Source.
vector<string> Dico::MotsAleatoires(string Source, int nbMotsAlea){
    ifstream fichier(Source);
    vector<string> TabMotsAleatoire;
    unsigned int flag=0,nbreMots=0;
    int numAlea=0,i=0,j=0,k=0;
    string buffer;
    vector<int> numAleatoire;
    srand(time(nullptr));

    //Ouverture fichier
    if(!fichier){
        exit(1);
     }
     else{
        nbreMots=nbMots(Source);
        for (i=0;i<nbMotsAlea;i++){
            numAlea=rand()%nbreMots;
            numAleatoire.push_back(numAlea);
            for (k=0;k<i;k++){
                if(numAleatoire[k]==numAlea){
                    flag=1;
                }
            }

            if(flag==1){
                flag=0;
                i--;
            }
            else{
                for(j=0;j<=numAlea;j++){
                    getline(fichier, buffer);
                }
                TabMotsAleatoire.push_back(buffer);
            }
        fichier.clear();
        fichier.seekg(0,ios::beg);
        }
    }
    fichier.close();
    return TabMotsAleatoire;
}

//Teste si un fichier contient assez de mots dans le fichier (par rapport au nombre de mots imposé par le joueur)
bool Dico::verifdico(string Source, int nbMotsutil)
{
    ifstream f(Source);
    if(!f)
    {
        exit(1);
    }
    else{
        if(nbMots(Source) >= nbMotsutil)
        {
            f.close();
            return true;
        }
    }
    f.close();
    return false;
}

//Cette fonction choisi aléatoirement un mot a partir NbMotsAlea
string Dico::SelectionMotSecret(vector<string> TabMotsAleatoires, int nbMotsAlea){
    int nb=0;
    srand(time(nullptr));
    nb=rand()%(nbMotsAlea);
    return TabMotsAleatoires[nb];
}

