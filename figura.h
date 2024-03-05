#ifndef figura_h
#define figura_h
#include <QPainter>
using namespace std;

class Figura {
protected:
    int x, y, width, height;
    bool pressed;
    int cursor_x, cursor_y;
    QColor color;
public:
    Figura(int X, int Y, int W, int H, QColor C, bool P=false, int CX=0, int CY=0) 
        : x(X), y(Y), width(W), height(H), color(C), pressed(P), cursor_x(CX), cursor_y(CY) {}
    void draw(QPainter* Painter);
    virtual void draw_obj(QPainter* Painter) = 0;
    void draw_pressed(QPainter* Painter);
    void check_pressed(QPoint p);
    bool is_pressed();
    void move(QPoint p);
    void set_color(QColor c);
    void set_size(int width_new, int height_new);
    void save(ofstream& out);
    virtual char get_type() = 0;
    virtual Figura* get_another_type() = 0;
    virtual ~Figura() {}
};

class Rect : public Figura {
protected:
    void draw_obj(QPainter* Painter);
public:
    Rect(int X, int Y, int W, int H, QColor C, bool P = false, int CX = 0, int CY = 0) 
        :Figura(X, Y, W, H, C, P, CX, CY) {}
    Figura* get_another_type();
    char get_type() {
        return 0;
    }
};

class Oval : public Figura {
protected:
    void draw_obj(QPainter* Painter);
public:
    Oval(int X, int Y, int W, int H, QColor C, bool P = false, int CX = 0, int CY = 0) 
        :Figura(X, Y, W, H, C, P, CX, CY) {}
    Figura* get_another_type();
    char get_type() {
        return 1;
    }
};

#endif
