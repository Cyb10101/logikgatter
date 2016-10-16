#ifndef FRM_MAIN_H
#define FRM_MAIN_H

#include <QMainWindow>
#include <QToolButton>

namespace Ui {
class frm_main;
}

class frm_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit frm_main(QWidget *parent = 0);
    ~frm_main();

private slots:
    void update_view();
    void show_second();
    bool calculate(bool wertA, bool wertB);
    void switch_operator(int value);
    int randInt(int low, int high);

    void on_button_newRandom_clicked();
    void on_menu_file_quit_triggered();
    void on_menu_view_toolbar_triggered(bool checked);
    void on_menu_view_statusbar_triggered(bool checked);
    void on_menu_view_truth_table_triggered(bool checked);
    void on_menu_help_about_triggered();
    void window_resize();

private:
    Ui::frm_main *ui;
};

#endif // FRM_MAIN_H
