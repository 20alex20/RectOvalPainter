#include "window.h"
#include <QtWidgets/QVBoxLayout>
#include <QFileDialog>
#include <fstream>
#include <QTextCodec> 
using namespace std;

Window::Window() {
    this->setWindowTitle("Paint");
    area = new Area(this);
    btn1 = new QPushButton("Open", this);
    btn2 = new QPushButton("Save", this);
    btn3 = new QPushButton("Close", this);
    QHBoxLayout* layout1 = new QHBoxLayout();
    layout1->addWidget(btn1);
    layout1->addWidget(btn2);
    layout1->addWidget(btn3);
    QVBoxLayout* layout2 = new QVBoxLayout(this);
    layout2->addWidget(area);
    layout2->addLayout(layout1);
    connect(btn1, &QPushButton::clicked, this, &Window::open);
    connect(btn2, &QPushButton::clicked, this, &Window::save);
    connect(btn3, SIGNAL(clicked(bool)), this, SLOT(close()));
};
void Window::save() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save data", QDir::currentPath(), "Data (*.txt)");
    if (!fileName.isEmpty()) {
        QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
        ofstream out(codec->fromUnicode(fileName).toStdString(), ios::trunc);
        area->save_data(out);
        out.close();
    }
}
void Window::open() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open data", QDir::currentPath(), "Data (*.txt)");
    if (!fileName.isEmpty()) {
        QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
        ifstream in(codec->fromUnicode(fileName).toStdString());
        area->open_data(in);
        in.close();
    }
}
