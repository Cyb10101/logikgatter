#ifndef FRM_ABOUT_H
#define FRM_ABOUT_H

#include <QDialog>

namespace Ui {
    class frm_about;
}

class frm_about : public QDialog {
    Q_OBJECT

public:
    explicit frm_about(QWidget *parent = 0);
    ~frm_about();

private slots:
    void on_button_close_clicked();

private:
    Ui::frm_about *ui;
};

#endif // FRM_ABOUT_H
