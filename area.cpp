#include "area.h"
#include <QMouseEvent>
#include <QColorDialog>
#include <QInputDialog>
#include <fstream>
using namespace std;

Area::Area(QWidget* parent) :QWidget(parent) {
    setMinimumSize(QSize(300, 300));
    
    menu1 = new QMenu(this);
    QAction* action = menu1->addAction("Add");
    connect(action, &QAction::triggered, this, &Area::add);
    
    menu2 = new QMenu(this);
    action = menu2->addAction("Change size");
    connect(action, &QAction::triggered, this, &Area::csize);
    action = menu2->addAction("Change type");
    connect(action, &QAction::triggered, this, &Area::ctype);
    action = menu2->addAction("Change color");
    connect(action, &QAction::triggered, this, &Area::ccolor);
    action = menu2->addAction("Delete");
    connect(action, &QAction::triggered, this, &Area::dell);
    menu2->addSeparator();
    action = menu2->addAction("Add");
    connect(action, &QAction::triggered, this, &Area::add);
}
void Area::add() {
    v.push_back(new Rect(100, 100, 100, 100, Qt::red));
    update();
}
void Area::dell() {
    int i = 0;
    while (i < v.size())
        if (v[i]->is_pressed()) {
            delete v[i];
            v.erase(v.begin() + i);
        }
        else
            i++;
    update();
}
void Area::ctype() {
    QStringList items;
    items << tr("Rectangle") << tr("Oval");
    bool ok;
    QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), 
        tr("Type of figure:"), items, 0, false, &ok);
    if (ok && !item.isEmpty()) {
        char variant = item == "Oval";
        for (int i = 0; i != v.size(); i++)
            if (v[i]->is_pressed() && v[i]->get_type() != variant) {
                Figura* obj = v[i]->get_another_type();
                delete v[i];
                v[i] = obj;
            }
        update();
    }
}
void Area::csize() {
    bool ok1, ok2;
    int num1 = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"), 
        tr("New width:"), 100, 1, 2000, 1, &ok1);
    int num2 = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"), 
        tr("New height:"), 100, 1, 2000, 1, &ok2);
    if (ok1 && ok2) {
        for (auto i = v.begin(); i != v.end(); ++i)
            if ((*i)->is_pressed())
                (*i)->set_size(num1, num2);
        update();
    }
}
void Area::ccolor() {
    QColor c = QColorDialog::getColor(Qt::red, this);
    for (auto i = v.begin(); i != v.end(); ++i)
        if ((*i)->is_pressed())
            (*i)->set_color(c);
    update();
}
void Area::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    for (auto i = v.begin(); i != v.end(); ++i)
        (*i)->draw(&painter);
}
void Area::mousePressEvent(QMouseEvent* event) {
    QPoint p = event->pos();
    int i = 0, k = 0;
    while (i < v.size() - k) {
        v[i]->check_pressed(p);
        if (v[i]->is_pressed()) {
            Figura* obj = v[i];
            v.erase(v.begin() + i);
            v.push_back(obj);
            k++;
        }
        else
            i++;
    }
    update();
}
void Area::mouseMoveEvent(QMouseEvent* event) { 
    QPoint p = event->pos();
    for (auto i = v.begin(); i != v.end(); ++i)
        if ((*i)->is_pressed())
            (*i)->move(p);
    update();
}
void Area::contextMenuEvent(QContextMenuEvent* e) {
    for (auto i = v.begin(); i != v.end(); ++i) 
        if ((*i)->is_pressed() && menu2){
            menu2->exec(e->globalPos());
            return;
        }
    if (menu1)
        menu1->exec(e->globalPos());
}
void Area::save_data(ofstream& out) {
    for (auto i = v.begin(); i != v.end(); ++i)
        (*i)->save(out);
}
void Area::open_data(ifstream& in) {
    for (auto i = v.begin(); i != v.end(); ++i)
        delete *i;
    v.clear();

    int type, x, y, width, height;
    string color;
    while (!in.eof()) {
        in >> type >> x >> y >> width >> height >> color;
        if (type == 0)
            v.push_back(new Rect(x, y, width, height, QColor(color.c_str())));
        else
            v.push_back(new Oval(x, y, width, height, QColor(color.c_str())));
    }
    update();
}