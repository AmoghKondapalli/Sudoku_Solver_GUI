#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_solve_clicked();
    void DisplayGrid(int grid[][9]);
    bool check(int grid[][9], int i, int j, int val);
    bool solveSudoku(int grid[][9], int i, int j);
    void on_clear_clicked();
    void on_undo_solve_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
