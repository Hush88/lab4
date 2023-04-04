#include <iostream> 
#include <vector> 
#define _USE_MATH_DEFINES //M_PI
#include <cmath>

using namespace std;

// ќпредел€ем класс Point дл€ хранени€ координат точки
class Point {
private:
    double x, y;
public:
    Point(double _x, double _y) : x(_x), y(_y) {}
    double getX() const { return x; }
    double getY() const { return y; }
    void setX(double _x) { x = _x; }
    void setY(double _y) { y = _y; }
    void print() const {
        cout << "(" << x << "," << y << ")";
    }
};

// ќпредел€ем класс Segment дл€ хранени€ отрезка
class Segment {
private:
    Point p1, p2; // начальна€ и конечна€ точки отрезка
public:
    Segment(Point _p1, Point _p2) : p1(_p1), p2(_p2) {}
    Point getP1() const { return p1; } // метод дл€ получени€ начальной точки отрезка
    Point getP2() const { return p2; } // метод дл€ получени€ конечной точки отрезка
    void setP1(Point _p1) { p1 = _p1; } // метод дл€ установки начальной точки отрезка
    void setP2(Point _p2) { p2 = _p2; } // метод дл€ установки конечной точки отрезка
    double length() const { // метод дл€ получени€ длины отрезка
        double dx = p1.getX() - p2.getX();
        double dy = p1.getY() - p2.getY();
        return sqrt(dx * dx + dy * dy);
    }
};

// ќпредел€ем класс Square дл€ хранени€ квадрата
class Square {
private:
    vector<Point> vertices; // хранение вершин квадрата
    char fillChar; // символ, используемый дл€ заполнени€ квадрата
public:
    Square(Point center, double size, char _fillChar = '*') : fillChar(_fillChar) {
        // —оздаем квадрат с заданным центром и размером, и запоминаем его вершины
        Point p1(center.getX() - size / 2, center.getY() - size / 2);
        Point p2(center.getX() - size / 2, center.getY() + size / 2);
        Point p3(center.getX() + size / 2, center.getY() + size / 2);
        Point p4(center.getX() + size / 2, center.getY() - size / 2);
        vertices.push_back(p1);
        vertices.push_back(p2);
        vertices.push_back(p3);
        vertices.push_back(p4);
    }
    void draw() const {
        // –исуем квадрат
        double minX = vertices[0].getX();
        double maxX = vertices[0].getX();
        double minY = vertices[0].getY();
        double maxY = vertices[0].getY();
        for (const auto& vertex : vertices) {
            minX = min(minX, vertex.getX());
            maxX = max(maxX, vertex.getX());
            minY = min(minY, vertex.getY());
            maxY = max(maxY, vertex.getY());
        }
        for (double y = minY; y <= maxY; y++) {
            for (double x = minX; x <= maxX; x++) {
                bool inside = false;
                for (size_t i = 0, j = vertices.size() - 1; i < vertices.size(); j = i++) {
                    const Point& vi = vertices[i];
                    const Point& vj = vertices[j];
                    if ((vi.getY() > y) != (vj.getY() > y) &&
                        (x < (vj.getX() - vi.getX()) * (y - vi.getY()) / (vj.getY() - vi.getY()) + vi.getX())) {
                        inside = !inside;
                    }
                }
                if (inside) {
                    cout << fillChar;
                }
                else {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }
    void resize(double factor) {
        // ћасшдабирование квадрата
        Point center = getCenter();
        for (auto& vertex : vertices) {
            double dx = vertex.getX() - center.getX();
            double dy = vertex.getY() - center.getY();
            dx *= factor;
            dy *= factor;
            vertex.setX(center.getX() + dx);
            vertex.setY(center.getY() + dy);
        }
    }
    void rotate(double angle) {
        // ¬ычисл€ем центр квадрата
        Point center = getCenter();
        for (auto& vertex : vertices) {
            double dx = vertex.getX() - center.getX();
            double dy = vertex.getY() - center.getY();
            // ѕоворачиваем точку на заданный угол
            double newX = dx * cos(angle) - dy * sin(angle);
            double newY = dx * sin(angle) + dy * cos(angle);
            // ѕеремещаем точку обратно в положение относительно центра квадрата
            vertex.setX(center.getX() + newX);
            vertex.setY(center.getY() + newY);
        }
    }
    void setColor(char _fillChar) {
        // ”станавливаем символ заполнени€ квадрата
        fillChar = _fillChar;
    }
    Point getCenter() const {
        double sumX = 0, sumY = 0;
        // —уммируем координаты всех вершин
        for (const auto& vertex : vertices) {
            sumX += vertex.getX();
            sumY += vertex.getY();
        }
        // ¬ычисл€ем среднее арифметическое координат вершин, чтобы получить координаты центра квадрата
        double centerX = sumX / vertices.size();
        double centerY = sumY / vertices.size();
        return Point(centerX, centerY);
    }
};

int main() {
    // ќпредел€ем константу M_PI
    const double M_PI = acos(-1);
    // —оздаем квадрат и отображаем его
    Point center(10, 10);
    Square square(center, 10);
    square.draw();
    // »змен€ем символ заполнени€ и масштабируем квадрат вдвое
    square.setColor('#');
    square.resize(2);
    square.draw();
    // ѕоворачиваем квадрат на 45 градусов и отображаем его
    square.rotate(M_PI / 4);
    square.draw();
    return 0;
}
