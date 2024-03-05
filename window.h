#ifndef window_h
#define window_h
#include "area.h" 
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
using namespace std;

class Window : public QWidget {
    Q_OBJECT
protected:
    Area* area;
    QPushButton* btn1, * btn2, * btn3;
public:
    Window();
public slots:
    void save();
    void open();
};

#endif