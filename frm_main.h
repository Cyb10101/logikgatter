#ifndef FRM_MAIN_H
#define FRM_MAIN_H

#include <QMainWindow>
#include <QToolButton>

namespace Ui {
class frm_Main;
}

class frm_Main : public QMainWindow
{
    Q_OBJECT

public:
    explicit frm_Main(QWidget *parent = 0);
    ~frm_Main();

private slots:
    void update_view();
    void show_second();
    bool calculate(bool wertA, bool wertB);
    void switch_operator(int value);
    int randInt(int low, int high);

    void on_button_newRandom_clicked();
    void on_menu_File_Quit_triggered();
    void on_menu_Help_About_triggered();

private:
    Ui::frm_Main *ui;
};

#endif // FRM_MAIN_H
