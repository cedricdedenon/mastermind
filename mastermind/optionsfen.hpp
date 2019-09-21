#ifndef OPTIONSFEN_HPP
#define OPTIONSFEN_HPP

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QGridLayout>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QLabel>

#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

class OptionsFen: public QWidget
{
Q_OBJECT

public:
    OptionsFen();

public slots:
    void ouvrirDialogue();

private:
    QPushButton *m_boutonOK;
    QSpinBox *m_taille;
    QSpinBox *m_nbMots;
    QSpinBox *m_nbEssais;

public:
    int getTaille();
    int getnbMots();
    int getnbEssais();
    QPushButton *getboutonOK();
};

#endif // OPTIONSFEN_HPP
