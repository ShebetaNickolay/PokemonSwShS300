#pragma once
#include "Head.h"
#include "Classes.h"

class Button {
private:
    double x;
    double y;
    double width;
    double height;
    string text;
public:
    Button() : x(0), y(0), width(0), height(0), text("") {};
    Button(double x, double y, double width, double height, string text)
        : x(x), y(y), width(width), height(height), text(text) {};
    Button(const Button& other) : x(other.x), y(other.y), width(other.width), height(other.height), text(other.text) {};
    ~Button() {};

    vector <double> colors = { 0.9, 0, 0.5 };
    void setColor(double first, double second, double third) {
        colors.push_back(first);
        colors.push_back(second);
        colors.push_back(third);
    }
    void setPosition(double x_1, double y_1) {
        x = x_1;
        y = y_1;
    }
    void setSize(double w, double h) {
        width = w;
        height = h;
    }

    void setText(const string text_1) {
        text = text_1;
    }

    void drawButton() {

        //Отрисовка кнопки
        glBegin(GL_POLYGON);
        glColor3f(colors[0], colors[1], colors[2]); // Серый цвет
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f); // Серый цвет
        int textLength = text.size();
        float textX = x + width/textLength;
        float textY = y + height / 2-1;

        glRasterPos2f(textX, textY);
        for (int i = 0; i < textLength; i++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
        }
    }

    bool isButtonHovered(Point& najatie) {
        return najatie.x >= this->x && najatie.x <= this->x + this->width &&
            najatie.y >= this->y && najatie.y <= this->y + this->height;
    }

};

vector<pair<int, int>> list = { {1, 0}, {2, 0}, {3, 0}, {4,0}, {5, 0}, {6, 0}, {7, 0}, {5, 1} };

vector<Point> pointList = {};
vector<Line> lineList = { Line(Point(4, 0), Point(4, 4)), Line(5, 5) };
vector<Polygon> polygonList = { Polygon({Point(1.0, 2.0), Point(3.0, 3.0), Point(1.0, 3.0)})};
vector<Ellipse> ellipseList = { Ellipse(Point(-3, 3), Point(3, -3), 15) };
vector<Circle> circleList = { Circle(Point(1.0, 6.0), 4) };
vector<Rectangle> rectangleList = { Rectangle(Point(1, 3), Point(2, 5), 2), Rectangle(Point(4, 3), Point(5, 5), 2)};
vector<Square> squareList = {Square(Point(6, 1), Point(7,2))};
vector<Triangle> triangleList = { Triangle(Point(-10, -10), Point(-8, -8), Point(-6, -10))};

const double scale = 20;

void initGrid() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-wGrid / 2 / scale, wGrid / 2 / scale, -hGrid / 2 / scale , hGrid / 2 / scale );
    glMatrixMode(GL_MODELVIEW);
}

void initMenu() {
    glClearColor(0.0, 0.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-wMenu / 2, wMenu / 2, -hMenu / 2, hMenu / 2);
    glMatrixMode(GL_MODELVIEW);
}

Button bCreate(-40, 255, 80, 40, "Create");
Button bDelete(-40, 210, 80, 40, "Delete");
Button bEdit1(-40, 165, 80, 40, "Edit");
Button bInfo(-40, 120, 80, 40, "Info");
Button bMenu(-145, -275, 60, 30, "Menu");

void drawGrid() {
    glColor3f(0.0, 1.0, 1.0);
    glLineWidth(1);
    glBegin(GL_LINES);
    for (int i = -wGrid; i <= wGrid; i++) {
        glVertex2f(i, -hGrid);
        glVertex2f(i, hGrid);
        glVertex2f(-hGrid, i);
        glVertex2f(hGrid, i);
    }
    glEnd();
    glFlush();
}

void drawAxes() {
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(-wGrid, 0);
    glVertex2f(wGrid, 0);
    glVertex2f(0, -hGrid);
    glVertex2f(0, hGrid);
    glEnd();
}

void drawEmAll() {
    for (int i = 0; i < list.size(); i++) {
        switch (list[i].first) {
        case 0:
            pointList[list[i].second].draw();
            break;
        case 1:
            lineList[list[i].second].draw();
            break;
        case 2:
            polygonList[list[i].second].draw();
            break;
        case 3:
            ellipseList[list[i].second].draw();
            break;
        case 4:
            circleList[list[i].second].draw();
            break;
        case 5:
            rectangleList[list[i].second].draw();
            break;
        case 6:
            squareList[list[i].second].draw();
            break;
        case 7:
            triangleList[list[i].second].draw();
            break;
        default:
            break;
        }
        glFlush();   
    }
}

bool deleted = 0;
int menu_sost = 0;

void displayGrid() {
    drawGrid();
    drawAxes();
    drawEmAll();
    glFlush();
}

void Grid() {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    displayGrid();
    glutPostRedisplay();
    glFlush();
    glutSwapBuffers();
}

void drawMenu() {
    bCreate.drawButton();
    bDelete.drawButton();
    bEdit1.drawButton();
    bInfo.drawButton();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawMenu();
    glFlush();
    glutSwapBuffers();
}

struct toDel {
    Button a;
    int figure;
    int ind;
};
vector<toDel> toDelete;

Button bDel(-150, 255, 80, 40, "");

void drawMenuDelFigure(int pick, int x, int y, int i) {
    switch (pick) {
    case 0:
        bDel.setPosition(x, y);
        bDel.setText("Point");
        bDel.drawButton();
        toDelete.push_back({ bDel, pick, i });
        break;
    case 1:
        bDel.setPosition(x, y);
        bDel.setText("Line");
        bDel.drawButton();
        toDelete.push_back({ bDel, pick, i });
        break;
    case 2:
        bDel.setPosition(x, y);
        bDel.setText("Polygon");
        bDel.drawButton();
        toDelete.push_back({ bDel, pick, i });
        break;
    case 3:
        bDel.setPosition(x, y);
        bDel.setText("Ellipse");
        bDel.drawButton();
        toDelete.push_back({ bDel, pick, i });
        break;
    case 4:
        bDel.setPosition(x, y);
        bDel.setText("Circle");
        bDel.drawButton();
        toDelete.push_back({ bDel, pick, i });
        break;
    case 5:
        bDel.setPosition(x, y);
        bDel.setText("Rectangle");
        bDel.drawButton();
        toDelete.push_back({ bDel, pick, i });
        break;
    case 6:
        bDel.setPosition(x, y);
        bDel.setText("Square");
        bDel.drawButton();
        toDelete.push_back({ bDel, pick, i });
        break;
    case 7:
        bDel.setPosition(x, y);
        bDel.setText("Triangle");
        bDel.drawButton();
        toDelete.push_back({ bDel, pick, i });
        break;
    }
}

void Delete() {
    glClearColor(0.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    int x = -150, y = 255;
    for (int i = 0; i < list.size(); i++) {
        drawMenuDelFigure(list[i].first, x, y, list[i].second);
        y -= 45;
        if (y <= -255) {
            x += 85;
            y = 255;
        }
    }
    bMenu.drawButton();
    glFlush();
    glutSwapBuffers();
}

Button bPoint(-40, 255, 80, 40, "Point");
Button bLine(-40, 210, 80, 40, "Line");
Button bPolygon(-40, 165, 80, 40, "Polygon");
Button bEllipse(-40, 120, 80, 40, "Ellipse");
Button bCircle(-40, 75, 80, 40, "Circle");
Button bRectangle(-40, 30, 80, 40, "Rectangle");
Button bSquare(-40, -15, 80, 40, "Square");
Button bTriangle(-40, -60, 80, 40, "Triangle");

void drawMenuFigure() {

    bPoint.drawButton();
    bLine.drawButton();
    bPolygon.drawButton();
    bEllipse.drawButton();
    bCircle.drawButton();
    bRectangle.drawButton();
    bSquare.drawButton();
    bTriangle.drawButton();
    bMenu.drawButton();
}

void PointCreate() {
    cout << "Введите координаты точки: \n";
    double x, y;
    cin >> x >> y;
    Point a(x, y);
    pointList.push_back(a);
    list.push_back({ 0, pointList.size() - 1 });
}

void LineCreate() {
    int pick;
    cout << "Как вы хотите задать линию?\n1 - Две точки\n2 - Точка и угловой коэффициент\n3 - Угловой коэффициент и сдвиг\n";
    cin >> pick;
    if (pick == 1) {
        cout << "Введите координаты 2х точек последовательно: \n";
        double x, y, x1, y1;
        cin >> x >> y >> x1 >> y1;
        Point a(x, y);
        Point b(x1, y1);
        Line L(a, b);
        lineList.push_back(L);
        list.push_back({ 1, lineList.size() - 1 });
    }
    else if (pick == 2) {
        cout << "Введите координаты точки и угловой коэффициент последовательно: \n";
        double x2, y2, k;
        cin >> x2 >> y2 >> k;
        Point t(x2, y2);
        Line L1(k, t);
        lineList.push_back(L1);
        list.push_back({ 1, lineList.size() - 1 });
    }
    else if (pick == 3) {
        cout << "Введите угловой коэффициент и сдвиг последовательно: \n";
        double k1, d;
        cin >> k1 >> d;
        Line L2(k1, d);
        lineList.push_back(L2);
        list.push_back({ 1, lineList.size() - 1 });
    }
    else {
        cout << "Попробуй в другой раз!";
    }
}

void PolygonCreate() {
    cout << "Введите количество вершин: \n";
    int n;
    cin >> n;
    cout << "Введите точки вершин последовательно: \n";
    vector<Point> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i].x >> A[i].y;
    }
    Polygon a(A);
    polygonList.push_back(a);
    list.push_back({ 2, polygonList.size() - 1 });
}

void EllipseCreate() {
    cout << "Введите 2 точки(фокусы) и сумму расстояний от эллипса до фокусов: \n";
    Point f1, f2;
    double dist;
    cin >> f1.x >> f1.y >> f2.x >> f2.y >> dist;
    Ellipse a(f1, f2, dist);
    ellipseList.push_back(a);
    list.push_back({ 3, ellipseList.size() - 1 });
}

void CircleCreate() {
    cout << "Введите координаты центра и радиус последовательно: \n";
    Point f;
    double r;
    cin >> f.x >> f.y >> r;
    Circle a(f, r);
    circleList.push_back(a);
    list.push_back({ 4, circleList.size() - 1 });
}

void RectangleCreate() {
    cout << "Введите противоположные вершины прямоугольника и отношение смежных сторон последовательно: \n";
    Point p1, p2;
    double dist;
    cin >> p1.x >> p1.y >> p2.x >> p2.y >> dist;
    Rectangle a(p1, p2, dist);
    rectangleList.push_back(a);
    list.push_back({ 5, rectangleList.size() - 1 });
}

void SquareCreate() {
    cout << "Введите противоположные вершины квадрата последовательно: \n";
    Point p1, p2;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    Square a(p1, p2);
    squareList.push_back(a);
    list.push_back({ 6, squareList.size() - 1 });
}

void TriangleCreate() {
    cout << "Введите вершины треугольника: \n";
    Point p1, p2, p3;
    cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
    Triangle a(p1, p2, p3);
    triangleList.push_back(a);
    list.push_back({ 7, triangleList.size() - 1 });
}

void Create() {
    glClearColor(0.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawMenuFigure();
    glFlush();
    glutSwapBuffers();
}

void delFigure(int pick, int ind) {
    switch (pick) {
    case 0:
        pointList.erase(pointList.begin() + ind);
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == 0 && list[i].second == ind) list[i].second = -1;
        }
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == 0) {
                if (list[i].second > ind) {
                    list[i].second--;
                }
            }
        }
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == 0 && list[i].second == -1) list.erase(list.begin()+i);
        }
        break;
    case 1:
        lineList.erase(lineList.begin() + ind);
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick && list[i].second == ind) list[i].second = -1;
        }
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick) {
                if (list[i].second > ind) {
                    list[i].second--;
                }
            }
        }
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick && list[i].second == -1) list.erase(list.begin() + i);
        }
        break;
    case 2:
        polygonList.erase(polygonList.begin() + ind);
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick && list[i].second == ind) list[i].second = -1;
        }
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick) {
                if (list[i].second > ind) {
                    list[i].second--;
                }
            }
        }
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick && list[i].second == -1) list.erase(list.begin() + i);
        }
        break;
    case 3:
        ellipseList.erase(ellipseList.begin() + ind);
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick && list[i].second == ind) list[i].second = -1;
        }
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick) {
                if (list[i].second > ind) {
                    list[i].second--;
                }
            }
        }
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick && list[i].second == -1) list.erase(list.begin() + i);
        }
        break;
    case 4:
        circleList.erase(circleList.begin() + ind);
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick && list[i].second == ind) list[i].second = -1;
        }
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick) {
                if (list[i].second > ind) {
                    list[i].second--;
                }
            }
        }
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick && list[i].second == -1) list.erase(list.begin() + i);
        }
        break;
    case 5:
        rectangleList.erase(rectangleList.begin() + ind);
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick && list[i].second == ind) list[i].second = -1;
        }
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick) {
                if (list[i].second > ind) {
                    list[i].second--;
                }
            }
        }
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick && list[i].second == -1) list.erase(list.begin() + i);
        }
        break;
    case 6:
        squareList.erase(squareList.begin() + ind);
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick && list[i].second == ind) list[i].second = -1;
        }
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick) {
                if (list[i].second > ind) {
                    list[i].second--;
                }
            }
        }
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick && list[i].second == -1) list.erase(list.begin() + i);
        }
        break;
    case 7:
        triangleList.erase(triangleList.begin() + ind);
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick && list[i].second == ind) list[i].second = -1;
        }
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick) {
                if (list[i].second > ind) {
                    list[i].second--;
                }
            }
        }
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first == pick && list[i].second == -1) list.erase(list.begin() + i);
        }
        break;
    default:
        break;
    }
}

struct toEdit {
    Button a;
    int figure;
    int ind;
};

vector<toEdit> existFig;

Button bEdit(-150, 255, 80, 40, "");

void drawMenuEditFigure(int pick, int i, int x, int y) {
    switch (pick) {
    case 0:
        bEdit.setPosition(x, y);
        bEdit.setText("Point");
        bEdit.drawButton();
        existFig.push_back({ bEdit, pick, i });
        break;
    case 1:
        bEdit.setPosition(x, y);
        bEdit.setText("Line");
        bEdit.drawButton();
        existFig.push_back({ bEdit, pick, i });
        break;
    case 2:
        bEdit.setPosition(x, y);
        bEdit.setText("Polygon");
        bEdit.drawButton();
        existFig.push_back({ bEdit, pick, i });
        break;
    case 3:
        bEdit.setPosition(x, y);
        bEdit.setText("Ellipse");
        bEdit.drawButton();
        existFig.push_back({ bEdit, pick, i });
        break;
    case 4:
        bEdit.setPosition(x, y);
        bEdit.setText("Circle");
        bEdit.drawButton();
        existFig.push_back({ bEdit, pick, i });
        break;
    case 5:
        bEdit.setPosition(x, y);
        bEdit.setText("Rectangle");
        bEdit.drawButton();
        existFig.push_back({ bEdit, pick, i });
        break;
    case 6:
        bEdit.setPosition(x, y);
        bEdit.setText("Square");
        bEdit.drawButton();
        existFig.push_back({ bEdit, pick, i });
        break;
    case 7:
        bEdit.setPosition(x, y);
        bEdit.setText("Triangle");
        bEdit.drawButton();
        existFig.push_back({ bEdit, pick, i });
        break;
    }
}

void Edit() {
    glClearColor(0.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    int x = -150, y = 255;
    for (int i = 0; i < list.size(); i++) {
        drawMenuEditFigure(list[i].first, list[i].second, x, y);
        y -= 45;
        if (y <= -255) {
            x += 85;
            y = 255;
        }
    }
    bMenu.drawButton();
    glFlush();
    glutSwapBuffers();
}

Button bRotate(-40, 255, 110, 40, "Rotate");
Button bReflexPoint(-40, 210, 110, 40, "Point Reflex");
Button bReflexLine(-40, 165, 110, 40, "Line Reflex");
Button bScale(-40, 120, 110, 40, "Scale");

void EdDraw() {
    glClearColor(0.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    bRotate.drawButton();
    bReflexPoint.drawButton();
    bReflexLine.drawButton();
    bScale.drawButton();
    bMenu.drawButton();

    glFlush();
    glutSwapBuffers();
}

void Editing(toEdit& a, int func) {
    if (func==0){
        cout << "Введите координаты точки, относительно которой будет производиться вращение и угол в градусах, на который будет произведен поворот: \n";
        Point p;
        cin >> p.x >> p.y;
        double rad;
        cin >> rad;
        double crad = rad * PI / 180.0;
        switch (a.figure) {
        case 0:
            pointList[a.ind].rotate(p, crad);
            break;
        case 1:
            lineList[a.ind].rotate(p, crad);
            break;
        case 2:
            polygonList[a.ind].rotate(p, rad);
            break;
        case 3:
            ellipseList[a.ind].rotate(p, rad);
            break;
        case 4:
            circleList[a.ind].rotate(p, rad);
            break;
        case 5:
            rectangleList[a.ind].rotate(p, rad);
            break;
        case 6:
            squareList[a.ind].rotate(p, rad);
            break;
        case 7:
            triangleList[a.ind].rotate(p, rad);
            break;
        default:
            break;
        }
    }
    else if (func == 1) {
        cout << "Введите координаты точка, относительно которой будет произведена симметрия: \n";
        Point p;
        cin >> p.x >> p.y;
        switch (a.figure) {
        case 0:
            pointList[a.ind].reflect(p);
            break;
        case 1:
            lineList[a.ind].reflex(p);
            break;
        case 2:
            polygonList[a.ind].reflex(p);
            break;
        case 3:
            ellipseList[a.ind].reflex(p);
            break;
        case 4:
            circleList[a.ind].reflex(p);
            break;
        case 5:
            rectangleList[a.ind].reflex(p);
            break;
        case 6:
            squareList[a.ind].reflex(p);
            break;
        case 7:
            triangleList[a.ind].reflex(p);
            break;
        default: break;
        }
    }
    else if (func == 2) {
        cout << "Введите координаты 2х точек, которыми задастся линия, через которую будет произведена симметрия: \n";
        Point p1, p2;
        cin >> p1.x >> p1.y >> p2.x >> p2.y;
        Line l1(p1, p2);
        switch (a.figure) {
        case 0:
            pointList[a.ind].reflect(l1);
            break;
        case 1:
            lineList[a.ind].reflex(l1);
            break;
        case 2:
            polygonList[a.ind].reflex(l1);
            break;
        case 3:
            ellipseList[a.ind].reflex(l1);
            break;
        case 4:
            circleList[a.ind].reflex(l1);
            break;
        case 5:
            rectangleList[a.ind].reflex(l1);
            break;
        case 6:
            squareList[a.ind].reflex(l1);
            break;
        case 7:
            triangleList[a.ind].reflex(l1);
            break;
        default: break;
        }
    }
    else if (func == 3) {
        cout << "Введиете координаты точки относительно которой будет изменять размер, и коэффициент изменения: \n";
        Point p;
        double coef;
        cin >> p.x >> p.y>>coef;
        switch (a.figure) {
        case 0:
            pointList[a.ind].scale(p, coef);
            break;
        case 1:
            //lineList[a.ind].scale(p, coef);
            break;
        case 2:
            polygonList[a.ind].scale(p, coef);
            break;
        case 3:
            ellipseList[a.ind].scale(p, coef);
            break;
        case 4:
            circleList[a.ind].scale(p, coef);
            break;
        case 5:
            rectangleList[a.ind].scale(p, coef);
            break;
        case 6:
            squareList[a.ind].scale(p, coef);
            break;
        case 7:
            triangleList[a.ind].scale(p, coef);
            break;
        default: break;
        }
    }
}

toEdit global;

toEdit globalInf;
toEdit globalInf2;

Button bArea;
Button bPerimetr;
Button bCongur;
Button bSimilar;
Button bContain;
Button bEqual;
Button bVerCnt;
Button bGetVertex;
Button bConvex;
Button bFocus;
Button bDirec;
Button bEccen;
Button bCenter;
Button bRadius;
Button bPCenter;
Button bDiag;
Button bOutCirc;
Button bInCirc;
Button bOutCircT;
Button bInCircT;
Button bCentroid;
Button bOrth;
Button bEuler;
Button bNinePtCirc;

void InfoDraw(int pick) {
    glClearColor(0.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    bEqual.setText("==");
    bEqual.setSize(150, 40);

    bArea.setText("Area");
    bArea.setSize(150, 40);

    bPerimetr.setText("Perimetr");
    bPerimetr.setSize(150, 40);

    bCongur.setText("Is congruent to?");
    bCongur.setSize(150, 40);

    bSimilar.setText("Is similar to?");
    bSimilar.setSize(150, 40);

    bContain.setText("Contain point?");
    bContain.setSize(150, 40);

    bVerCnt.setText("Vertex count");
    bVerCnt.setSize(150, 40);

    bGetVertex.setText("Get vertex");
    bGetVertex.setSize(150, 40);

    bConvex.setText("Is convex?");
    bConvex.setSize(150, 40);

    bFocus.setText("Focuses");
    bFocus.setSize(150, 40);

    bDirec.setText("Directrices");
    bDirec.setSize(150, 40);

    bEccen.setText("Eccentricity");
    bEccen.setSize(150, 40);

    bCenter.setText("Center");
    bCenter.setSize(150, 40);

    bRadius.setText("Radius");
    bRadius.setSize(150, 40);

    bPCenter.setText("Center");
    bPCenter.setSize(150, 40);

    bDiag.setText("Diagonals");
    bDiag.setSize(150, 40);

    bOutCirc.setText("Circumscribed circle");
    bOutCirc.setSize(200, 40);

    bInCirc.setText("Inscribed circle");
    bInCirc.setSize(200, 40);

    bOutCircT.setText("Circumscribed circle");
    bOutCircT.setSize(200, 40);

    bInCircT.setText("Inscribed circle");
    bInCircT.setSize(200, 40);

    bCentroid.setText("Centroid");
    bCentroid.setSize(150, 40);

    bOrth.setText("Orthocenter");
    bOrth.setSize(150, 40);

    bEuler.setText("Euler line");
    bEuler.setSize(150, 40);

    bNinePtCirc.setText("Nine points circle");
    bNinePtCirc.setSize(200, 40);

    if (pick == 0) {
        bEqual.setPosition(-75, 255);
        bEqual.drawButton();
    }
    else if (pick == 1) {
        bEqual.setPosition(-75, 255);
        bEqual.drawButton();
    }
    else if (pick >= 2) {
        bEqual.setPosition(-75, 255);
        bEqual.drawButton();
        bArea.setPosition(-75, 210);
        bArea.drawButton();
        bPerimetr.setPosition(-75, 165);
        bPerimetr.drawButton();
        bCongur.setPosition(-75, 120);
        bCongur.drawButton();
        bSimilar.setPosition(-75, 75);
        bSimilar.drawButton();
        bContain.setPosition(-75, 30);
        bContain.drawButton();
        if (pick == 2) {
            bVerCnt.setPosition(-75, -15);
            bVerCnt.drawButton();
            bGetVertex.setPosition(-75, -60);
            bGetVertex.drawButton();
            bConvex.setPosition(-75, -105);
            bConvex.drawButton();
        }
        if (pick == 3) {
            bFocus.setPosition(-75, -15);
            bFocus.drawButton();
            bDirec.setPosition(-75, -60);
            bDirec.drawButton();
            bEccen.setPosition(-75, -105);
            bEccen.drawButton();
            bCenter.setPosition(-75, -150);
            bCenter.drawButton();
        }
        if (pick == 4) {
            bRadius.setPosition(-75, -15);
            bRadius.drawButton();
        }
        if (pick == 5) {
            bPCenter.setPosition(-75, -15);
            bPCenter.drawButton();
            bDiag.setPosition(-75, -60);
            bDiag.drawButton();
        }
        if (pick == 6) {
            bOutCirc.setPosition(-100, -15);
            bOutCirc.drawButton();
            bInCirc.setPosition(-100, -60);
            bInCirc.drawButton();
        }
        if (pick == 7) {
            bOutCircT.setPosition(-100, -15);
            bOutCircT.drawButton();
            bInCircT.setPosition(-100, -60);
            bInCircT.drawButton();
            bCentroid.setPosition(-75, -105);
            bCentroid.drawButton();
            bOrth.setPosition(-75, -150);
            bOrth.drawButton();
            bEuler.setPosition(-75, -195);
            bEuler.drawButton();
            bNinePtCirc.setPosition(-100, -240);
            bNinePtCirc.drawButton();
        }
    }

    bMenu.drawButton();

    glFlush();
    glutSwapBuffers();
}

void Info() {
    glClearColor(0.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    int x = -150, y = 255;
    for (int i = 0; i < list.size(); i++) {
        drawMenuEditFigure(list[i].first, list[i].second, x, y);
        y -= 45;
        if (y <= -255) {
            x += 85;
            y = 255;
        }
    }
    bMenu.drawButton();
    glFlush();
    glutSwapBuffers();
}

bool good = 0;

bool equale(toEdit globalInf, toEdit globalInf2) {
    if (globalInf.figure != globalInf2.figure) return 0;
    else if (globalInf.figure < 2) {
        if (globalInf.figure == 0) {
            if (pointList[globalInf.ind] == pointList[globalInf2.ind]) {
                return 1;
            }
            else return 0;
        }
        else {
            if (lineList[globalInf.ind] == lineList[globalInf2.ind]) return 1;
            else return 0;
        }
    }
    else {
        if (globalInf.figure == 2) {
            if (polygonList[globalInf.ind] == polygonList[globalInf2.ind]) return 1;
            else return 0;
        }
        else if (globalInf.figure == 3) {
            if (ellipseList[globalInf.ind] == ellipseList[globalInf2.ind]) return 1;
            else return 0;
        }
        else if (globalInf.figure == 4) {
            if (circleList[globalInf.ind] == circleList[globalInf2.ind]) return 1;
            else return 0;
        }
        else if (globalInf.figure == 5) {
            if (rectangleList[globalInf.ind] == rectangleList[globalInf2.ind]) return 1;
            else return 0;
        }
        else if (globalInf.figure == 6) {
            if (squareList[globalInf.ind] == squareList[globalInf2.ind]) return 1;
            else return 0;
        }
        else if (globalInf.figure == 7) {
            if (triangleList[globalInf.ind] == triangleList[globalInf2.ind]) return 1;
            else return 0;
        }
    }
}

bool isCongr(toEdit globalInf, toEdit globalInf2) {
    if (globalInf.figure < 2) return 1;
    else {
        if (globalInf.figure == globalInf2.figure) {
            if (globalInf.figure == 2) return polygonList[globalInf.ind].isCongruentTo(polygonList[globalInf2.ind]);
            if (globalInf.figure == 3) return ellipseList[globalInf.ind].isCongruentTo(ellipseList[globalInf2.ind]);
            if (globalInf.figure == 4) return circleList[globalInf.ind].isCongruentTo(circleList[globalInf2.ind]);
            if (globalInf.figure == 5) return rectangleList[globalInf.ind].isCongruentTo(rectangleList[globalInf2.ind]);
            if (globalInf.figure == 6) return squareList[globalInf.ind].isCongruentTo(squareList[globalInf2.ind]);
            if (globalInf.figure == 7) return triangleList[globalInf.ind].isCongruentTo(triangleList[globalInf2.ind]);
        }
        else return 0;
    }
}

bool isSim(toEdit globalInf, toEdit globalInf2) {
    if (globalInf.figure < 2) return 1;
    else {
        if (globalInf.figure == globalInf2.figure) {
            if (globalInf.figure == 2) return polygonList[globalInf.ind].isSimilarTo(polygonList[globalInf2.ind]);
            if (globalInf.figure == 3) return ellipseList[globalInf.ind].isSimilarTo(ellipseList[globalInf2.ind]);
            if (globalInf.figure == 4) return circleList[globalInf.ind].isSimilarTo(circleList[globalInf2.ind]);
            if (globalInf.figure == 5) return rectangleList[globalInf.ind].isSimilarTo(rectangleList[globalInf2.ind]);
            if (globalInf.figure == 6) return squareList[globalInf.ind].isSimilarTo(squareList[globalInf2.ind]);
            if (globalInf.figure == 7) return triangleList[globalInf.ind].isSimilarTo(triangleList[globalInf2.ind]);
        }
        else return 0;
    }
}

void mouseClick(int button, int state, int x, int y) {
    setlocale(LC_ALL, "rus");
    double worldX, worldY, worldZ;
    GLint viewport[4];
    GLdouble modelview[16], projection[16];

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        glGetIntegerv(GL_VIEWPORT, viewport);
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);

        gluUnProject(x, viewport[3] - y, 0, modelview, projection, viewport, &worldX, &worldY, &worldZ);

        Point menuChoice(worldX, worldY);

        if (bCreate.isButtonHovered(menuChoice) && menu_sost==0) {
            Create();
            menu_sost = 1;
        }
        else if (bDelete.isButtonHovered(menuChoice) && menu_sost == 0) {
            Delete();
            menu_sost = 2;
        }
        else if (bEdit1.isButtonHovered(menuChoice) && menu_sost == 0) {
            Edit();
            menu_sost = 3;
        }
        else if (bMenu.isButtonHovered(menuChoice) && menu_sost != 0) {
            display();
            menu_sost = 0;
        }
        else if (bPoint.isButtonHovered(menuChoice) && menu_sost==1) {
            PointCreate();
        }
        else if (bLine.isButtonHovered(menuChoice) && menu_sost == 1) {
            LineCreate();
        }
        else if (bPolygon.isButtonHovered(menuChoice) && menu_sost == 1) {
            PolygonCreate();
        }
        else if (bEllipse.isButtonHovered(menuChoice) && menu_sost == 1) {
            EllipseCreate();
        }
        else if (bCircle.isButtonHovered(menuChoice) && menu_sost == 1) {
            CircleCreate();
        }
        else if (bRectangle.isButtonHovered(menuChoice) && menu_sost == 1) {
            RectangleCreate();
        }
        else if (bSquare.isButtonHovered(menuChoice) && menu_sost == 1) {
            SquareCreate();
        }
        else if (bTriangle.isButtonHovered(menuChoice) && menu_sost == 1) {
            TriangleCreate();
        }
        else if (bRotate.isButtonHovered(menuChoice) && menu_sost == 4) {
            Editing(global, 0);
        }
        else if (bReflexPoint.isButtonHovered(menuChoice) && menu_sost == 4) {
            Editing(global, 1);
        }
        else if (bReflexLine.isButtonHovered(menuChoice) && menu_sost == 4) {
            Editing(global, 2);
        }
        else if (bScale.isButtonHovered(menuChoice) && menu_sost == 4) {
            Editing(global, 3);
        }
        else if (bInfo.isButtonHovered(menuChoice) && menu_sost == 0) {
            Info();
            menu_sost = 5;
        }
        else if (bPerimetr.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure > 1) {
                cout << "Периметр: ";
                if (globalInf.figure == 2) cout << polygonList[globalInf.ind].perimeter() << '\n';
                if (globalInf.figure == 3) cout << ellipseList[globalInf.ind].perimeter() << '\n';
                if (globalInf.figure == 4) cout << circleList[globalInf.ind].perimeter() << '\n';
                if (globalInf.figure == 5) cout << rectangleList[globalInf.ind].perimeter() << '\n';
                if (globalInf.figure == 6) cout << squareList[globalInf.ind].perimeter() << '\n';
                if (globalInf.figure == 7) cout << triangleList[globalInf.ind].perimeter() << '\n';
            }
            else cout << "Not exist\n";
        }
        else if (bArea.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure > 1) {
                cout << "Площадь: ";
                if (globalInf.figure == 2) cout << polygonList[globalInf.ind].area() << '\n';
                if (globalInf.figure == 3) cout << ellipseList[globalInf.ind].area() << '\n';
                if (globalInf.figure == 4) cout << circleList[globalInf.ind].area() << '\n';
                if (globalInf.figure == 5) cout << rectangleList[globalInf.ind].area() << '\n';
                if (globalInf.figure == 6) cout << squareList[globalInf.ind].area() << '\n';
                if (globalInf.figure == 7) cout << triangleList[globalInf.ind].area() << '\n';
            }
            else cout << "Not exist\n";
        }
        else if (bContain.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure > 1) {
                cout << "Введите координаты точки, чтобы проверить, находится ли она внутри фигуры: \n";
                Point p;
                cin >> p.x >> p.y;
                if (globalInf.figure == 2) cout << polygonList[globalInf.ind].containsPoint(p) << '\n';
                if (globalInf.figure == 3) cout << ellipseList[globalInf.ind].containsPoint(p) << '\n';
                if (globalInf.figure == 4) cout << circleList[globalInf.ind].containsPoint(p) << '\n';
                if (globalInf.figure == 5) cout << rectangleList[globalInf.ind].containsPoint(p) << '\n';
                if (globalInf.figure == 6) cout << squareList[globalInf.ind].containsPoint(p) << '\n';
                if (globalInf.figure == 7) cout << triangleList[globalInf.ind].containsPoint(p) << '\n';
            }
            else cout << "Not exist\n";
        }
        else if (bVerCnt.isButtonHovered(menuChoice)&&menu_sost ==6) {
            if (globalInf.figure == 2) {
                cout << polygonList[globalInf.ind].verticesCount() << '\n';
            }
            else cout << "not exist\n";
        }
        else if (bGetVertex.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure == 2) {
                vector<Point> res;
                res = polygonList[globalInf.ind].getVertices();
                for (int i = 0; i < res.size(); i++) {
                    cout << res[i].x << ' ' << res[i].y << '\n';
                }
            }
            else cout << "not exist\n";
        }
        else if (bConvex.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure == 2) {
                cout << polygonList[globalInf.ind].isConvex();
            }
            else cout << "not exist\n";
        }
        else if (bFocus.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure == 3) {
                cout << ellipseList[globalInf.ind].focuses().first.x << ' ' << ellipseList[globalInf.ind].focuses().first.y << '\n';
                cout << ellipseList[globalInf.ind].focuses().second.x << ' ' << ellipseList[globalInf.ind].focuses().second.y << '\n';
            }
        }
        else if (bDirec.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure == 3) {
                Line A = ellipseList[globalInf.ind].directrices().first;
                cout << A.A_l << ' ' <<A.B_l << ' ' << A.C_l << '\n';
                A = ellipseList[globalInf.ind].directrices().second;
                cout << A.A_l << ' ' << A.B_l << ' ' << A.C_l << '\n';
            }
            else cout << "not exist\n";
        }
        else if (bEccen.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure == 3) {
                cout << ellipseList[globalInf.ind].eccentricity() << '\n';
            }
            else cout << "not exist\n";
        }
        else if (bCenter.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure == 3) {
                cout << ellipseList[globalInf.ind].center().x << ' ' << ellipseList[globalInf.ind].center().y << '\n';
            }
            else cout << "not exist\n";
        }
        else if (bRadius.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure == 4) {
                cout << circleList[globalInf.ind].radius();
            }
            else cout << "not exist\n";
        }
        else if (bPCenter.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure == 5) {
                cout << rectangleList[globalInf.ind].center().x << ' ' << rectangleList[globalInf.ind].center().y;
            }
            else cout << "no exist\n";
        }
        else if (bDiag.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure == 5) {
                Line A = rectangleList[globalInf.ind].diagonals().first;
                cout << A.A_l << ' ' << A.B_l << ' ' << A.C_l << '\n';
                A = rectangleList[globalInf.ind].diagonals().second;
                cout << A.A_l << ' ' << A.B_l << ' ' << A.C_l << '\n';
            }
            else cout << "not exist\n";
        }
        else if (bOutCirc.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure == 6) {
                double rad = squareList[globalInf.ind].circumscribedCircle().radius();
                Point cen = squareList[globalInf.ind].circumscribedCircle().center();
                cout << cen.x << ' ' <<cen.y << ' ' << rad << '\n';
            }
            else cout << "not exist\n";
        }
        else if (bInCirc.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure == 6) {
                double rad = squareList[globalInf.ind].inscribedCircle().radius();
                Point cen = squareList[globalInf.ind].inscribedCircle().center();
                cout << cen.x << ' ' << cen.y << ' ' << rad << '\n';
            }
            else cout << "not exist\n";
        }
        else if (bOutCircT.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure == 7) {
                double rad = triangleList[globalInf.ind].circumscribedCircle().radius();
                Point cen = triangleList[globalInf.ind].circumscribedCircle().center();
                cout << cen.x << ' ' << cen.y << ' ' << rad << '\n';
            }
            else cout << "not exist\n";
        }
        else if (bInCircT.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure == 7) {
                double rad = triangleList[globalInf.ind].inscribedCircle().radius();
                Point cen = triangleList[globalInf.ind].inscribedCircle().center();
                cout << cen.x << ' ' << cen.y << ' ' << rad << '\n';
            }
            else cout << "not exist\n";
        }
        else if (bCentroid.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure == 7) {
                cout << triangleList[globalInf.ind].centroid().x << ' ' << triangleList[globalInf.ind].centroid().y << '\n';
            }
            else cout << "not exist\n";
        }
        else if (bOrth.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure == 7) {
                cout << triangleList[globalInf.ind].orthocenter().x << ' ' << triangleList[globalInf.ind].orthocenter().y << '\n';
            }
            else cout << "not exist\n";
        }
        else if (bEuler.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure == 7) {
                Line A = triangleList[globalInf.ind].EulerLine();
                cout << A.A_l << ' ' << A.B_l << ' ' << A.C_l << '\n';
            }
            else cout << "not exist\n";
        }
        else if (bNinePtCirc.isButtonHovered(menuChoice) && menu_sost == 6) {
            if (globalInf.figure == 7) {
                double rad = triangleList[globalInf.ind].ninePointsCircle().radius();
                Point cen = triangleList[globalInf.ind].ninePointsCircle().center();
                cout << cen.x << ' ' << cen.y << ' ' << rad << '\n';
            }
            else cout << "not exist\n";
        }
        else if (bEqual.isButtonHovered(menuChoice) && menu_sost == 6) {

            Info();
            menu_sost = 7;
            if (good) {
                cout<<equale(globalInf, globalInf2);
                menu_sost = 5;
            }
            good = 0;
        }
        else if (bCongur.isButtonHovered(menuChoice) && menu_sost == 6) {
            menu_sost = 8;
            Info();
            if (good) {
                isCongr(globalInf, globalInf2);
                menu_sost = 5;
            }
            good = 0;
        }
        else if (bSimilar.isButtonHovered(menuChoice) && menu_sost == 6) {
            menu_sost = 9;
            Info();
            if (good) {
                cout << isSim(globalInf, globalInf2);
                menu_sost = 5;
            }
            good = 0;
        }

        for (int i = 0; i < toDelete.size(); i++) {
            if (toDelete[i].a.isButtonHovered(menuChoice) && menu_sost==2) {
                delFigure(toDelete[i].figure, toDelete[i].ind);
                toDelete.clear();
                Delete();
            }
        }
        for (int i = 0; i < existFig.size(); i++) {
            if (existFig[i].a.isButtonHovered(menuChoice)) {
                if (menu_sost == 3) {
                    EdDraw();
                    global = existFig[i];
                    menu_sost = 4;
                    
                }
                if (menu_sost == 5) {
                    InfoDraw(existFig[i].figure);
                    globalInf = existFig[i];
                    menu_sost = 6;
                }
                if (menu_sost == 7) {
                    globalInf2 = existFig[i];
                    cout << equale(globalInf, globalInf2);
                    menu_sost = 5;
                }
                if (menu_sost == 8) {
                    globalInf2 = existFig[i];
                    cout << isCongr(globalInf, globalInf2);
                    menu_sost = 5;
                }
                if (menu_sost == 9) {
                    globalInf2 = existFig[i];
                    cout << isSim(globalInf, globalInf2);
                    menu_sost = 5;
                }
                existFig.clear();
            }
        }
    }
}

void menu(int& argc, char**& argv) {
    setlocale(LC_ALL, "RUS");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    
    glutInitWindowSize(wMenu, hMenu);
    glutCreateWindow("1");
    glutPositionWindow(1000, 50);

    initMenu();

    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);

    glutInitWindowSize(wGrid, hGrid);
    glutCreateWindow("2");

    initGrid();
    glutDisplayFunc(Grid);

    glutMainLoop();
}
