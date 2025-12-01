#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QGridLayout>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QWidget *centralWidget= new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout= new QHBoxLayout(centralWidget);
    QVBoxLayout *buttonLayout=new QVBoxLayout();
    QGridLayout *sudokuLayout=new QGridLayout();
    sudokuLayout->setSpacing(0);
    mainLayout->addLayout(sudokuLayout);

    //button risolvi
    QPushButton *risolvi = new QPushButton("Risolvi", ui->pushRisolvi);
    connect(risolvi, &QPushButton::clicked,this, &MainWindow::on_pushRisolvi_clicked);
    //button reset
    QPushButton *reset = new QPushButton("Reset", ui->pushReset);
    connect(reset, &QPushButton::clicked,this, &MainWindow::on_pushReset_clicked);
    //button successivo
    QPushButton *succ = new QPushButton("Successivo", ui->pushSuccessivo);
    connect(succ, &QPushButton::clicked,this, &MainWindow::on_pushSuccessivo_clicked);
    //button precedente
    QPushButton *prec = new QPushButton("Precedente", ui->pushPrecedente);
    connect(prec, &QPushButton::clicked,this, &MainWindow::on_pushPrecedente_clicked);

    buttonLayout->addWidget(risolvi);
    buttonLayout->addWidget(reset);
    buttonLayout->addWidget(succ);
    buttonLayout->addWidget(prec);

    mainLayout->addLayout(buttonLayout);

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            cells[row][col] = new QLineEdit(this);
            cells[row][col]->setMaxLength(1);
            cells[row][col]->setValidator(new QIntValidator(1, 9, this));
            cells[row][col]->setFixedSize(50, 50);
            cells[row][col]->setAlignment(Qt::AlignCenter);
            sudokuLayout->addWidget(cells[row][col], row, col);
        }
    }

}

//destroyer
MainWindow::~MainWindow()
{
    delete ui;
}

//resolve the sudoku
bool MainWindow::Risolvi(int row, int col)
{
    if (row == 8 && col == 9)
        return true;  
    if (col == 9) {
        row++;
        col= 0; 
    }   
    if (!cells[row][col]->text().isEmpty()) //!=0
        return Risolvi(row, col + 1);

    for (int num = 1; num <= 9; ++num)
    {        
        Mossa newmossa(row, col, num);
        mosse.append(newmossa);
        cont=mosse.size()-1;

        
        if (NumeroValido(row, col, num))
        {
            cells[row][col]->clear();
            cells[row][col]->setText(QString::number(num));
            if (Risolvi(row, col + 1)) 
                return true;
            cells[row][col]->clear();
        }
    }
    return false;
}



bool MainWindow::NumeroValido(int row, int col, int num)
{
    //columns == num
    for (int x = 0; x < 9; ++x){
        if (cells[row][x]->text().toInt() == num && x!=col){            
            return false;
        }
    }

    //rows == num
    for (int x = 0; x < 9; ++x){
        if (cells[x][col]->text().toInt() == num && x!=row){
            return false;
        }
    }

    //3x3 square == num
    for (int x = 0; x < 3; ++x){
         for (int t = 0; t < 3; ++t){
            int h=row - row % 3 + x;
            int p=col - col % 3 + t;
            if (cells[h][p]->text().toInt() == num && ((h!=row)||(p!=col))){
                return false;
            }
         }
    }

    return true;
}

bool MainWindow::checkGrid(){      
    int num =0;
    
    for(int row=0; row<9; row++)
    {
        for(int col=0; col<9; col++)
        {
          
            if(!cells[row][col]->text().isEmpty()){
                num=cells[row][col]->text().toInt();
                if(!NumeroValido(row, col, num)){
                    return false;
                }
            }
        }
    }
    return true;
}

//button Risolvi
void MainWindow::on_pushRisolvi_clicked()
{        
    bool isCorrect=checkGrid();
    if(isCorrect==true){
        isCorrect = Risolvi(0,0); 
        checkPrec=true;
    }
    if (isCorrect==true)    {
        QMessageBox::information(this, "Sudoku", "Tutto corretto!");
    }    else    {
        QMessageBox::warning(this, "Sudoku", "Errore nella griglia!");
    }
}

//button Reset
void MainWindow::on_pushReset_clicked()
{   
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            cells[i][j]->clear();
        }
    }
    QMessageBox::information(this, "Sudoku", "Nuovo Sudoku!");
}



//button successivo
void MainWindow::on_pushSuccessivo_clicked() {
    bool check=MossaSuccessiva();
    if(check!=true)
        QMessageBox::warning(this, "Sudoku", "Non puoi farlo!");
}

bool MainWindow::MossaSuccessiva(){
    if(checkSucc==true && cont!=mosse.size()){
        cont++;
        if(cont!=mosse.size()){
            int n=mosse[cont].num;
            int r=mosse[cont].row;
            int c=mosse[cont].col;
            cells[r][c]->clear();
            cells[r][c]->setText(QString::number(n));
            return true;
        }
    }
    return false;

}



//button precedente
void MainWindow::on_pushPrecedente_clicked()
{ 
    bool check=MossaPrecedente();
    checkSucc=true;
    if (check!=true)
        QMessageBox::warning(this, "Sudoku", "Errore nella griglia!");
}

bool MainWindow::MossaPrecedente(){
    if(checkPrec==true){

        int r=mosse[cont].row;
        int c=mosse[cont].col;
        int n=mosse[cont].num;
        if(cells[r][c]->text().toInt()==1) {
            cells[r][c]->clear();
            return true;
        }

        cont--;
        r=mosse[cont].row;
        c=mosse[cont].col;
        n=mosse[cont].num;

        cells[r][c]->clear();
        cells[r][c]->setText(QString::number(n));
        return true;
    } else
        QMessageBox::warning(this, "Sudoku", "Non è stato risolto!");
    return false;

}
