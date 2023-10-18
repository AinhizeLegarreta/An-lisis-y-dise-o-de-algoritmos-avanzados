#include <iostream>
#include <math.h>
using namespace std;

/***
Casos de prueba:

Caso de prueba 1:
Entrada:
n = 3
Puntos de la línea 1: [1,5 7,1 1,4 10,9]
Puntos de la línea 2: [10,2 1,12 3,3 0,15]
Puntos de la línea 3: [-6,-6 3,4 2,2 1,1]

Resultado:
  True
  False
  False


Caso de prueba 2:
Entrada:
n=1,
Puntos de la línea 1: [1,1 5,5 2,2 6,6]

Resultado:
True

Caso de prueba 3:
Entrada:
n = 4
Puntos de la línea 1: [0,0 2,2 4,4 6,6]
Puntos de la línea 2: [1,1 3,3 5,5 7,7]
Puntos de la línea 3: [0,1 2,3 4,5 6,7]
Puntos de la línea 4: [1,0 3,2 5,4 7,6]

Resultado:
True
True
True
True


Caso de prueba 4:
Entrada:
n = 4
Puntos de la línea 1: [1,1 2,2 3,3 4,4]
Puntos de la línea 2: [2,1 3,2 4,3 5,4]
Puntos de la línea 3: [5,5 6,6 7,7 8,8]
Puntos de la línea 4: [7,7 8,8 9,9 10,10]

Resultado:
False
False
True
True



Caso de prueba 5:
Entrada:
n = 4
Puntos de la línea 1: [1,1 2,2 3,3 4,4]
Puntos de la línea 2: [4,1 3,2 2,3 1,4]
Puntos de la línea 3: [1,1 2,2 3,3 4,4]
Puntos de la línea 4: [3,1 2,2 1,3 4,4]

Resultado:
False
True
True
True
***/

double EPSILON = 0.00005;

class Point {
private:
  double x, y;

public:
  Point();
  Point(double, double);
  Point(const Point &);
  double getX() const;
  double getY() const;
};

Point::Point() : x(0), y(0) {}

Point::Point(double xVal, double yVal) : x(xVal), y(yVal) {}

Point::Point(const Point &other) : x(other.x), y(other.y) {}

double Point::getX() const { return x; }

double Point::getY() const { return y; }

class Line {
private:
  double a, b, c;

public:
  Line();
  Line(double, double, double);
  Line(const Line &);
  double getA() const;
  double getB() const;
  double getC() const;
};

Line::Line() : a(0), b(0), c(0) {}

Line::Line(double aVal, double bVal, double cVal) : a(aVal), b(bVal), c(cVal) {}

Line::Line(const Line &other) : a(other.a), b(other.b), c(other.c) {}

double Line::getA() const { return a; }

double Line::getB() const { return b; }

double Line::getC() const { return c; }

// Complejidad computacional: O(1)
// Función para convertir dos puntos en una línea
Line pointAndSlopeToLine(const Point &p, double m) {
  return Line(-m, 1, -(-m * p.getX()) + p.getY());
}

// Complejidad computacional: O(1)
// Función para saber si dos líneas son paralelas
bool areParallel(const Line &l1, const Line &l2) {
  return ((fabs(l1.getA() - l2.getA()) <= EPSILON) &&
          (fabs(l1.getB() - l2.getB()) <= EPSILON));
}

// Complejidad computacional: O(1)
// Función para saber si dos líneas se intersectan
Point *intersectsAt(const Line &l1, const Line &l2) {
  double x, y;
  if (areParallel(l1, l2)) {
    return NULL;
  }
  x = ((l1.getB() * l1.getC()) - (l1.getB() * l2.getC())) /
      ((l2.getA() * l1.getB()) - (l1.getA() * l2.getB()));
  if (fabs(l1.getB()) < EPSILON) {
    y = -((l1.getA() * x) + l1.getC());
  } else {
    y = -((l1.getA() * x) + l2.getC());
  }
  return new Point(x, y);
}

// Complejidad computacional: O(n), dónde n es la cantidad de elementos
int main() {
  int n;

  // Entrada de datos
  cout << "Ingresa la cantidad de elementos (N): ";
  cin >> n;
  if (cin.fail()) {
    cout << "Error: Ingreso no válido. Debe ser un número entero." << endl;
    return 1; // Termina el programa con un código de error
  }

  for (int i = 0; i < n; i++) {
    double x1, y1, x2, y2, x3, y3, x4, y4;
    Point p1, p2, p3, p4;
    Line l1, l2;
    Point *result;

    cout << "Ingresa aqui los valores de los puntos de la primera linea (x1, "
            "y1, x2, y2):"
         << endl;
    cin >> x1 >> y1 >> x2 >> y2;
    p1 = Point(x1, y1);
    p2 = Point(x2, y2);
    cout << "Ingresa aqui los valores de los puntos de la primera linea (x3, "
            "y3, x4, y4):";
    cin >> x3 >> y3 >> x4 >> y4;
    p3 = Point(x3, y3);
    p4 = Point(x4, y4);

    l1 = pointAndSlopeToLine(p1,
                             p2.getY() - p1.getY() / (p2.getX() - p1.getX()));
    l2 = pointAndSlopeToLine(p3,
                             (p4.getY() - p3.getY()) / (p4.getX() - p3.getX()));
    result = intersectsAt(l1, l2);

    if (result != NULL) {
      cout << "True (" << result->getX() << ", " << result->getY() << ")"
           << endl;
    } else {
      cout << "False" << endl;
    }
  }
  return 0;
}