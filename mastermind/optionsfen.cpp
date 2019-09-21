#include "optionsfen.hpp"

OptionsFen::OptionsFen(): QWidget()
{
    //Création et définition des widgets utiles pour les paramètres génériques
    QLabel *intro = new QLabel("Paramètres génériques:",this);
    intro->setFont(QFont("Arial",9));
    QLabel *tailleLettres = new QLabel("Taille des mots",this);
    QLabel *nbMots = new QLabel("Nombre de mots", this);
    QLabel *nbEssais = new QLabel("Nombre d'essais",this);

    m_taille = new QSpinBox(this);
    m_taille->setMinimum(3);
    m_taille->setMaximum(25);
    m_taille->setValue(5);

    m_nbMots = new QSpinBox(this);
    m_nbMots->setMinimum(5);
    m_nbMots->setValue(30);

    m_nbEssais = new QSpinBox(this);
    m_nbEssais->setMinimum(1);
    m_nbEssais->setMaximum(50);
    m_nbEssais->setValue(5);

    m_boutonOK = new QPushButton("OK", this);
    m_boutonOK->setToolTip("Teminer la configuration des paramètres génériques");   // Infobulle

    //Création du layout et organisation des widgets dans la fenêtre
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(intro,0,0);
    layout->addWidget(tailleLettres,1,0);
    layout->addWidget(m_taille,1,1);
    layout->addWidget(nbMots,2,0);
    layout->addWidget(m_nbMots,2,1);
    layout->addWidget(nbEssais,3,0);
    layout->addWidget(m_nbEssais,3,1);
    layout->addWidget(m_boutonOK,6,0,1,2);

    setLayout(layout);

    //Interactions avec l'utilisateur (appui sur un bouton)
    connect(m_boutonOK,SIGNAL(clicked()),this,SLOT(ouvrirDialogue()));
}

//La fenêtre se ferme lorsque l'utilisateur appuie sur le bouton "OK"
void OptionsFen::ouvrirDialogue()
{
    this->close();
}

//Accesseurs permettant d'obtenir les valeurs des paramètres génériques entrés par le joueur
int OptionsFen::getTaille()
{
    return m_taille->value();
}

int OptionsFen::getnbMots()
{
    return m_nbMots->value();
}

int OptionsFen::getnbEssais()
{
    return m_nbEssais->value();
}

QPushButton* OptionsFen::getboutonOK()
{
    return m_boutonOK;
}
