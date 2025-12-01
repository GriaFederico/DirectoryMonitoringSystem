#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <vector>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushRisolvi_clicked();

    void on_pushReset_clicked();

    void on_pushSuccessivo_clicked();

    void on_pushPrecedente_clicked();

private:
    Ui::MainWindow *ui;
    struct Mossa{
        int row, col, num;
        Mossa() : row(0), col(0), num(0){};
        Mossa(int newrow, int newcol, int newnum) : row(newrow), col(newcol), num(newnum){};
    };
    QList<Mossa> mosse;
    int cont=0;    
    bool checkPrec=false, checkSucc=false;
    QLineEdit* cells[9][9];    
    bool Risolvi(int row, int col);
    bool NumeroValido(int row, int col, int num);
    bool checkGrid();
    bool MossaSuccessiva();
    bool MossaPrecedente();
};

#endif // MAINWINDOW_H
