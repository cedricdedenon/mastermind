#include "mastermindfen.hpp"

vector<string> TabMotsAlea;
string mdp;

MasterMindFen::MasterMindFen()
{
    QWidget *zoneCentrale = new QWidget;
    QFont maPolice("Arial",9);

    //Déclaration des menus, sous-menus et des actions
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QMenu *menuAide = menuBar()->addMenu("&?");

    QAction *actionNvlPartie = new QAction("&Nouvelle Partie",this);
    QAction *actionOptions = new QAction("&Options",this);
    QAction *actionQuitter = new QAction("&Quitter", this);
    QAction *actionAide = new QAction("&Aide",this);
    QAction *actionAPropos = new QAction("&A Propos",this);

    menuFichier->addAction(actionNvlPartie);
    menuFichier->addAction(actionOptions);
    menuFichier->addAction(actionQuitter);
    menuAide->addAction(actionAide);
    menuAide->addAction(actionAPropos);

    //Raccourci pour les menus
    actionNvlPartie->setShortcut(QKeySequence("CTRL+N"));
    actionQuitter->setShortcut(QKeySequence("CTRL+Q"));
    actionOptions->setShortcut(QKeySequence("CTRL+O"));
    actionAide->setShortcut(QKeySequence("CTRL+F1"));
    actionAPropos->setShortcut(QKeySequence("CTRL+I"));

    //Fenetre de dialogue pour l'aide
    QDialog *fenaide = new QDialog(zoneCentrale);
    QVBoxLayout *layoutaide = new QVBoxLayout;
    QLabel *labelaide = new QLabel("Le jeu consiste à trouver le mot de passe parmis une liste de mots "
                                   "générés aléatoirement.\n\nVous devez entrer au clavier le "
                                   "mot à l'endroit indiqué puis cliquez sur le bouton OK pour "
                                   "valider le mot. Vous devez impérativement entrer un mot de la liste affichée."
                                   "\n\nSi le mot n'est pas correct, vous aurez la possibilité d'entrer un nouveau "
                                   "mot tant que le nombre d'essais ne tombe pas à 0.\nVous appercevrez alors à "
                                   "droite le nombre de lettres bien placées (cercle vert) et le nombre de lettres mal "
                                   "placées mais présent dans le mot de passe (cercle rouge).\n\nVous perdez si vous "
                                   "ne trouvez pas le bon mot et que le nombre d'essais atteint 0.\n\nPar défaut, "
                                   "vous aurez 5 essais pour rechercher un mot de taille 5 parmi 30 mots.\n"
                                   "Vous avez la possibilité de changer ces paramètres (Fichier->"
                                   "Options) à votre contenancee et appuyer sur OK "
                                   "pour prendre en compte les modifications.\nAttention toutefois, "
                                   "à ce qu'il y ait assez de mot dans le dictionnaire pour pouvoir jouer",fenaide);
    labelaide->setFont(maPolice);
    layoutaide->addWidget(labelaide);
    fenaide->setLayout(layoutaide);

    //Fenetre de dialogue pour l'"A Propos"
    QDialog *fenapropos = new QDialog(zoneCentrale);
    QVBoxLayout *layoutapropos = new QVBoxLayout;
    QLabel *labelapropos = new QLabel("Ce logiciel a été crée par Cédric D.\n\n2016\nTous droits réservés",fenaide);
    labelapropos->setFont(maPolice);
    layoutapropos->addWidget(labelapropos);
    fenapropos->setLayout(layoutapropos);

    //Création et définition des widgets utiles à l'application
    nb_essais=f.getnbEssais();
    nb_taille=f.getTaille();
    nb_mots=f.getnbMots();

    QLabel *labelintro=new QLabel("Trouver le mot de passe:",this);
    labelintro->setFont(maPolice);
    m_labelessai=new QLabel(this);
    if(nb_essais==1){
        m_labelessai->setText("Vous avez " + QString::number(nb_essais) + " essai ");
    }
    else{
        m_labelessai->setText("Vous avez " + QString::number(nb_essais) + " essais ");
    }
    m_labelessai->setFont(maPolice);
    m_boutonOK = new QPushButton("OK", this);
    m_boutonQuit = new QPushButton("Quitter",this);
    m_boutonRejouer = new QPushButton("Rejouer",this);
    m_lineedit= new QLineEdit;

    m_textMotsAlea = new QTextEdit;
    m_textMotsAlea->setFont(QFont("Arial",9));
    m_textMotsAlea->setReadOnly(true);

    m_textMotsEntres = new QTextEdit;
    m_textMotsEntres->setFont(QFont("Arial",9));
    m_textMotsEntres->setReadOnly(true);

    //Appel à la fonction d'initialisation pour la sélection des mots de la liste et du mot de passe
    init();

    //Création des layouts et organisation des widgets dans la fenêtre
    QGridLayout *layout= new QGridLayout();
    layout->addWidget(m_textMotsAlea,0,0);
    layout->addWidget(m_textMotsEntres,0,1);
    layout->addWidget(labelintro,1,0);
    layout->addWidget(m_labelessai,2,0);
    layout->addWidget(m_lineedit,3,0);
    layout->addWidget(m_boutonOK,4,0);
    layout->addWidget(m_boutonRejouer,4,1);
    layout->addWidget(m_boutonQuit,4,2);

    //Interactions avec l'utilisateur (appui sur un bouton, selections des paramètres ...)
    connect(actionNvlPartie,SIGNAL(triggered(bool)),this,SLOT(rejouer()));
    connect(actionOptions,SIGNAL(triggered(bool)),this,SLOT(options()));
    connect(actionQuitter,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(actionAide,SIGNAL(triggered(bool)),fenaide,SLOT(exec()));
    connect(actionAPropos,SIGNAL(triggered(bool)),fenapropos,SLOT(exec()));
    connect(m_boutonOK,SIGNAL(clicked(bool)),this,SLOT(algo()));
    connect(m_boutonQuit,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(m_boutonRejouer,SIGNAL(clicked(bool)),this,SLOT(rejouer()));
    connect(f.getboutonOK(),SIGNAL(clicked()),this,SLOT(rejouer()));

    zoneCentrale->setLayout(layout);
    setCentralWidget(zoneCentrale);
}

//A chaque appui sur le bouton "OK", on lance l'algorithme de l'application
void MasterMindFen::algo()
{
    Algo algo;
    int egalite=0, similarite=0, i=0;
    //On vérifie que le mot entré par l'utilisateur figure dans la liste de mots générés aléatoirement
    if(!verif(TabMotsAlea))
    {
        QMessageBox::critical(this,"MasterMind ","Veuillez entrer un mot de la liste ");
    }
    else{
        nb_essais--;
        if(nb_essais==1){
            m_labelessai->setText("Vous avez " + QString::number(nb_essais) + " essai ");
        }
        else{
            m_labelessai->setText("Vous avez " + QString::number(nb_essais) + " essais ");
        }

        //Si le mot est présent dans la liste, on affiche le résultat à droite (le mot + égalité + similarité)
        egalite = algo.egalite((m_lineedit->displayText().toStdString()), mdp, nb_taille);
        similarite = algo.similarite((m_lineedit->displayText()).toStdString(), mdp, nb_taille);

        m_textMotsEntres->insertPlainText(m_lineedit->displayText() + '\t');
        QTextDocumentFragment fragment;
        for (i= 0; i< egalite; i++){
            fragment = QTextDocumentFragment::fromHtml("<img src='vert.png'>");
            m_textMotsEntres->textCursor().insertFragment(fragment);
        }
        for (i= 0; i< similarite; i++){
            fragment = QTextDocumentFragment::fromHtml("<img src='rouge.png'>");
             m_textMotsEntres->textCursor().insertFragment(fragment);
        }
        m_textMotsEntres->setVisible(true);
        m_textMotsEntres->insertPlainText("\n");


        //Si on trouve le bon mot de passe, on gagne la partie
        if(algo.comparaison((m_lineedit->displayText()).toStdString(), mdp))
        {
            m_boutonOK->setEnabled(false);
            m_labelessai->hide();
            QMessageBox::information(this,"MasterMind ","Bien joué !!! Le mot de passe était bien " + m_lineedit->displayText());
        }
        //Sinon on teste le nombre d'essais restants, s'il atteitn zéro, la partie est perdue
        else if (nb_essais==0)
        {
            m_boutonOK->setEnabled(false);
            m_labelessai->hide();
            QMessageBox::information(this,"MasterMind ","Perdu !!! Le mot de passe était " + QString::fromStdString(mdp));
        }
    }
    m_lineedit->clear();
}

//Permet d'effacer tous les éléments de la partie en cours, puis de créer une nouvelle partie
void MasterMindFen::rejouer()
{
    while(TabMotsAlea.size()!=0)
    {
        TabMotsAlea.pop_back();
    }

    m_lineedit->clear();
    m_textMotsAlea->clear();
    m_textMotsEntres->clear();

    nb_essais=f.getnbEssais();
    nb_taille=f.getTaille();
    nb_mots=f.getnbMots();

    if(nb_essais==1){
        m_labelessai->setText("Vous avez " + QString::number(nb_essais) + " essai ");
    }
    else{
        m_labelessai->setText("Vous avez " + QString::number(nb_essais) + " essais ");
    }

    m_labelessai->show();
    m_boutonOK->setEnabled(true);
    init();
}

//Permet de modifier les paramètres génériques (taille des lettres + nb mot dans la liste + nb essais)
void MasterMindFen::options()
{
    f.setWindowModality(Qt::ApplicationModal);
    f.show();
}

//Fonction d'initialisation (utilisée pour toute nouvelle partie)
void MasterMindFen::init()
{
    Dico dico;
    //On récupére une chaine de caractère en fonction de la taille des lettres du mot pour créer un fichier .txt
    string d= dico.DestFichier(nb_taille);
    //Si ce fichier n'existe pas, il sera crée en contenant tous les mots de même taille défini précédemment
    if(!dico.fichierExistant(d))
    {
        dico.copieFichierTaille(d, "dico.txt", nb_taille);
    }

    //On vérifie qu'il y a assez de mots dans le dictionnaire (en fonction des paramètres génériques)
    if(!dico.verifdico(d, nb_mots))
    {
        QMessageBox::critical(this,"MasterMind ","Il n'y a pas assez de mots de taille " + QString::number(nb_taille) + " dans le dictionnaire");
        m_boutonOK->setEnabled(false);
        f.show();
    }
    else{
        TabMotsAlea=dico.MotsAleatoires(d, nb_mots);
        sort(TabMotsAlea.begin(),TabMotsAlea.end());

            for (int i=0; i<f.getnbMots(); i++)
            {
                m_textMotsAlea->insertPlainText(QString::fromStdString(TabMotsAlea[i]) + "\n");
            }
        mdp=dico.SelectionMotSecret(TabMotsAlea,nb_mots);
    }
}

//Teste si le mot entrée par le joueur figure dans la liste de mots (retourne true si oui, false sinon)
bool MasterMindFen::verif(vector<string> TabMotsAlea)
{
    for(int i(0);i<nb_mots;i++)
    {
        if(m_lineedit->displayText().toStdString()==TabMotsAlea[i])
        {
            return true;
        }
    }
    return false;
}

//  SLOT ré-implantant (closeEvent) lors de la fermeture de l'application (croix rouge)
void MasterMindFen::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question(this,"MasterMind",tr("Voulez-vous quitter?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        while(TabMotsAlea.size()!=0)
        {
            TabMotsAlea.pop_back();
        }
        event->accept();
    }

}
