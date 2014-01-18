#include <QDesktopWidget>
#include "frm_about.h"
#include "ui_frm_about.h"

frm_about::frm_about(QWidget *parent) : QDialog(parent), ui(new Ui::frm_about) {
    ui->setupUi(this);

    QString cyb_version = "1.0.0";
    ui->label_program->setText("<span style=\"font-size:12pt; font-weight:600;\">Logikgatter " + cyb_version + "</span>");

    // Center Screen
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());

    // NoResize
    this->setFixedSize(this->width(), this->height());

    /*QPixmap Pixmap_Logo(":/images/cyb10101.de.jpg");
    ui->label_picture->setPixmap(Pixmap_Logo);*/
}

frm_about::~frm_about() {
    delete ui;
}

void frm_about::on_button_close_clicked() {
    this->hide();
}
