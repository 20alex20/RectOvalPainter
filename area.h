#ifndef AREA_H 
#define AREA_H
#include "figura.h"
#include <QtWidgets/QWidget>
#include <QContextMenuEvent>
#include <QMenu>
#include <vector>
using namespace std;

class Area : public QWidget {
    Q_OBJECT
public:
    Area(QWidget* parent = nullptr);
    ~Area() {};
    QMenu* menu1;
    QMenu* menu2;
    vector <Figura*> v;
    bool flag;
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void contextMenuEvent(QContextMenuEvent* e);
    void save_data(ofstream& out);
    void open_data(ifstream& in);
public slots:
    void add();
    void ctype();
    void dell();
    void csize();
    void ccolor();
};

#endif