#include "figura.h"
#include <fstream>
using namespace std;

void Figura::draw(QPainter* Painter) {
    QPen pen;
    pen.setColor(color);
    QBrush brush;
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    Painter->setBrush(brush);
    Painter->setPen(pen);
    draw_obj(Painter);
    if (pressed)
        draw_pressed(Painter);
}
void Figura::check_pressed(QPoint p) {
    int dx = p.x(), dy = p.y();
    pressed = (x <= dx && dx < x + width) &&
        (y <= dy && dy < y + height);
    if (pressed) {
        cursor_x = dx;
        cursor_y = dy;
    }
}
void Figura::move(QPoint p) {
    int dx = p.x(), dy = p.y();
    x += dx - cursor_x;
    y += dy - cursor_y;
    cursor_x = dx;
    cursor_y = dy;
}
bool Figura::is_pressed() {
    return pressed;
}
void Figura::set_color(QColor c) {
    color = c;
}
void Figura::set_size(int width_new, int height_new) {
    width = width_new;
    height = height_new;
}
void Figura::draw_pressed(QPainter* Painter) {
    Painter->setBrush(Qt::NoBrush);
    Painter->setPen(QPen(Qt::darkGray, 3, Qt::DashLine));
    Painter->drawRect(x - 2, y - 2, width + 4, height + 4);
}
void Figura::save(ofstream& out) {
    out << (int)get_type() << ' ' << x << ' ' << y << ' ' <<
        width << ' ' << height << ' ' << color.name().toStdString() << endl;
}

void Rect::draw_obj(QPainter* Painter) {
    Painter->drawRect(x, y, width, height);
}
Figura* Rect::get_another_type() {
    return new Oval(x, y, width, height, color, pressed, cursor_x, cursor_y);
}

void Oval::draw_obj(QPainter* Painter) {
    Painter->drawEllipse(x, y, width, height);
}
Figura* Oval::get_another_type() {
    return new Rect(x, y, width, height, color, pressed, cursor_x, cursor_y);
}
