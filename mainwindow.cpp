#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<bits/stdc++.h>
#include<string.h>

#define N 9
int mgrid[N][N] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
 };
int tgrid[N][N] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
 };

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DisplayGrid(mgrid);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::check(int grid[][9], int i, int j, int val)
{
    int row = i - i%3, column = j - j%3;
    for(int x=0; x<9; x++) if(grid[x][j] == val) return false;
    for(int y=0; y<9; y++) if(grid[i][y] == val) return false;
    for(int x=0; x<3; x++)
        for(int y=0; y<3; y++)
            if(grid[row+x][column+y] == val) return false;
    return true;
}
bool MainWindow::solveSudoku(int grid[][9], int i, int j)
{
    if(i==9) return true;
    if(j==9) return solveSudoku(grid, i+1, 0);
    if(grid[i][j] != 0) return solveSudoku(grid, i, j+1);

    for(int c=1; c<=9; c++)
    {
        if(check(grid, i, j, c))
        {
            grid[i][j] = c;
            if(solveSudoku(grid, i, j+1)) return true;
            grid[i][j] = 0;
        }
    }

    return false;
}
void MainWindow::DisplayGrid(int grid[][9])
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            ui->table->setItem(i, j, new QTableWidgetItem);
            if(tgrid[i][j]>0)ui->table->item(i,j)->setBackground(QBrush(QColor(Qt::gray)));
            if (grid[i][j]>0){
                QString str = QString::number(grid[i][j]);
                ui->table->item(i, j)->setText(str);
            }
        }
    }
    update();
}


void MainWindow::on_solve_clicked()
{
//    for(int i = 0;i<9;i++)
//        for(int j=0;j<9;j++)
//            tgrid[i][j]=mgrid[i][j];
    for(int i = 0;i<9;i++){
        for(int j = 0;j<9;j++){
            QTableWidgetItem* cell = ui->table->item(i,j);
            if(cell->text().toInt()>=10){
                ui->label->setText("Greater Than 9");
                return;
            }
            int c = cell->text().toInt();
            bool flag = cell->text().isNull();
            if(flag==false){
                if(check(mgrid,i,j,c)==false){
                ui->label->setText("There are invalid fields in existence");
                return;}
                qDebug() << "empty";
            }
            tgrid[i][j] = cell->text().toInt();
            mgrid[i][j] = cell->text().toInt();
        }
    }
    qDebug() << "Solving";
    solveSudoku(mgrid,0,0);
    DisplayGrid(mgrid);
    qDebug() << "Solved";
}


void MainWindow::on_clear_clicked()
{
    for(int i = 0;i<9;i++){
        for(int j = 0;j<9;j++){
            ui->table->item(i,j)->setText(NULL);
            ui->table->item(i,j)->setBackground(QBrush(QColor(Qt::black)));
            mgrid[i][j]=0;
        }
    }
    ui->label->setText("");
}





void MainWindow::on_undo_solve_clicked()
{
    for(int i = 0;i<9;i++){
        for(int j = 0;j<9;j++){
            ui->table->item(i,j)->setText(NULL);
            mgrid[i][j]=0;
        }
    }
    ui->label->setText("");
    DisplayGrid(tgrid);
}

