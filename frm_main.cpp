#include "frm_main.h"
#include "frm_about.h"
#include "ui_frm_main.h"

#include <QDesktopWidget>
#include <QMessageBox>
#include <QTime>
#include <QToolButton>
#include <QSignalMapper>
#include <QDebug>

int current_operator;
int Wert_randomA;
int Wert_randomB;

QString operator_Text;
QString trueX[2];
QString trueY[2];

frm_Main::frm_Main(QWidget *parent) : QMainWindow(parent), ui(new Ui::frm_Main) {
    ui->setupUi(this);

    // Library Check
    foreach(const QString &path, qApp->libraryPaths()) {
        qDebug() << path;
    }

    // Center Screen
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());

    // NoResize
    this->setFixedSize(this->width(), this->height());

    // Zufall zufälliger
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    trueX[0] = "False";
    trueX[1] = "True";
    trueY[0] = "0 - False";
    trueY[1] = "1 - True";

    QObject::connect(ui->Radio_A0, SIGNAL(clicked()), this, SLOT(update_view()));
    QObject::connect(ui->Radio_A1, SIGNAL(clicked()), this, SLOT(update_view()));
    QObject::connect(ui->Radio_B0, SIGNAL(clicked()), this, SLOT(update_view()));
    QObject::connect(ui->Radio_B1, SIGNAL(clicked()), this, SLOT(update_view()));

    QObject::connect(ui->button_Check_Quiz, SIGNAL(clicked()), this, SLOT(show_second()));

    // Toolbar
    QSignalMapper* sm_toolbar = new QSignalMapper(this);

    QToolButton* toolbar_buttons[6];
    for(int i = 0; i < 6; i++) {
        toolbar_buttons[i] = new QToolButton();

        switch(i + 1) {
            case 1:
                toolbar_buttons[i]->setText("AND");
                break;

            case 2:
                toolbar_buttons[i]->setText("OR");
                break;

            case 3:
                toolbar_buttons[i]->setText("XOR");
                break;

            case 4:
                toolbar_buttons[i]->setText("NAND");
                break;

            case 5:
                toolbar_buttons[i]->setText("NOR");
                break;

            case 6:
                toolbar_buttons[i]->setText("XNOR");
                break;
        }
        //toolbar_xnor->setIcon(QIcon("c://savebutton.png"));
        toolbar_buttons[i]->setCursor(Qt::OpenHandCursor);
        ui->toolbar->addWidget(toolbar_buttons[i]);

        QObject::connect(toolbar_buttons[i], SIGNAL(clicked()), sm_toolbar, SLOT(map()));
        sm_toolbar->setMapping(toolbar_buttons[i], (i + 1));
    }

    // ToolButton MapAll
    QObject::connect(sm_toolbar, SIGNAL(mapped(int)), this, SLOT(switch_operator(int)));
    switch_operator(1);

    on_button_newRandom_clicked();
    update_view();
}

frm_Main::~frm_Main() {
    delete ui;
}

/*
if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "Mein Titel", "Hier ist die Frage", QMessageBox::Yes|QMessageBox::No).exec()) {

}
*/

void frm_Main::update_view() {
    bool wertA = (ui->Radio_A1->isChecked() ? 1 : 0);
    bool wertB = (ui->Radio_B1->isChecked() ? 1 : 0);

    bool calc = this->calculate(wertA, wertB);

    ui->label_ausgabe_oben->setText("Ausgabe:\n(" + trueX[wertA] + " " + operator_Text + " " +  trueX[wertB] + ") = " + trueX[calc]);
    ui->label_ausgabe_unten->setText("");
}

void frm_Main::show_second() {
    bool wertA = Wert_randomA;
    bool wertB = Wert_randomB;
    bool wertC = (ui->Radio_C1->isChecked() ? 1 : 0);

    bool calc = this->calculate(wertA, wertB);

    QString Ergebnis_Text = "";
    if(calc == wertC) {
        Ergebnis_Text = "<span style=\"color: green;\">Richtig!</span>";
    } else {
        Ergebnis_Text = "<span style=\"color: red;\">Falsch!</span>";
    }
    ui->label_ausgabe_unten->setText(Ergebnis_Text + " - Ausgabe:<br>(" + trueX[wertA] + " " + operator_Text + " " +  trueX[wertB] + ") = " + trueX[calc]);
}

int frm_Main::randInt(int low, int high) {
    return qrand() % ((high + 1) - low) + low;
}

void frm_Main::on_button_newRandom_clicked() {
    Wert_randomA = this->randInt(0, 1);
    Wert_randomB = this->randInt(0, 1);
    ui->label_RandomA->setText(trueY[Wert_randomA]);
    ui->label_RandomB->setText(trueY[Wert_randomB]);
    ui->label_ausgabe_unten->setText("");
}

bool frm_Main::calculate(bool wertA, bool wertB) {
    bool calc = false;
    switch(current_operator) {
        case 1: calc = (wertA && wertB); break;
        case 2: calc = (wertA || wertB); break;
        case 3: calc = (wertA xor wertB); break;
        case 4: calc = !(wertA && wertB); break;
        case 5: calc = !(wertA || wertB); break;
        case 6: calc = !(wertA xor wertB); break;
    }
    return calc;
}

void frm_Main::switch_operator(int value) {
    ui->label_oben_punktC->setVisible(false);
    ui->label_unten_punktC->setVisible(false);
    switch(value) {
        case 1:
            operator_Text = "&&";
            ui->label_operator_oben->setText("<html><body>&amp;<br><br>AND</body></html>");
            ui->label_operator_unten->setText("<html><body>&amp;<br><br>AND</body></html>");
            break;

        case 2:
            operator_Text = "||";
            ui->label_operator_oben->setText("<html><body>&ge;1<br><br>OR</body></html>");
            ui->label_operator_unten->setText("<html><body>&ge;1<br><br>OR</body></html>");
            break;

        case 3:
            operator_Text = "xor";
            ui->label_operator_oben->setText("<html><body>=1<br><br>XOR</body></html>");
            ui->label_operator_unten->setText("<html><body>=1<br><br>XOR</body></html>");
            break;

        case 4:
            operator_Text = "nand";
            ui->label_operator_oben->setText("<html><body>&amp;<br><br>AND</body></html>");
            ui->label_operator_unten->setText("<html><body>&amp;<br><br>AND</body></html>");
            ui->label_oben_punktC->setVisible(true);
            ui->label_unten_punktC->setVisible(true);
            break;

        case 5:
            operator_Text = "nor";
            ui->label_operator_oben->setText("<html><body>&ge;1<br><br>OR</body></html>");
            ui->label_operator_unten->setText("<html><body>&ge;1<br><br>OR</body></html>");
            ui->label_oben_punktC->setVisible(true);
            ui->label_unten_punktC->setVisible(true);
            break;

        case 6:
            operator_Text = "xnor";
            ui->label_operator_oben->setText("<html><body>=<br><br>XOR</body></html>");
            ui->label_operator_unten->setText("<html><body>=<br><br>XOR</body></html>");
            ui->label_oben_punktC->setVisible(true);
            ui->label_unten_punktC->setVisible(true);
            break;
    }

    if(current_operator != value) {update_view();}
    current_operator = value;
}

void frm_Main::on_menu_File_Quit_triggered() {
    QApplication::quit();
}

void frm_Main::on_menu_Help_About_triggered() {
    frm_about window_about;
    window_about.show();
    window_about.exec();
}
