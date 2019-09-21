#ifndef MASTERMINDFEN_HPP
#define MASTERMINDFEN_HPP

#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QtWidgets>
#include <QDialog>
#include <QFile>
#include <QList>
#include "dico.hpp"
#include "algo.hpp"
#include "optionsFen.hpp"

class MasterMindFen: public QMainWindow
{
Q_OBJECT
public:
    MasterMindFen();

public slots:
    void algo();
    void rejouer();
    void options();
    void closeEvent (QCloseEvent *event);

private:
    QPushButton *m_boutonOK;
    QPushButton *m_boutonQuit;
    QPushButton *m_boutonRejouer;
    QTextEdit *m_textMotsAlea;
    QLineEdit *m_lineedit;
    QLabel *m_labelessai;
    QTextEdit *m_textMotsEntres;
    int nb_essais;
    int nb_taille;
    int nb_mots;
    OptionsFen f;

public:
    void init();
    bool verif(vector<string> TabMotsAlea);
};
#endif // MASTERMINDFEN_HPP
