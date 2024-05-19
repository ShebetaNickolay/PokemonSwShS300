#pragma once
#include "Head.h"

const double PI = acos(-1.0);
const double epsilon = 1e-6;


bool equal(double first, double second) {
	return abs(first - second) < epsilon;
} 


struct Point;
class Line;
class Polygon;
class Shape;
class Rectangle;
class Square;
class Ellipse;
class Circle;

struct Point {
	double x, y;

	Point() : x(0), y(0) {}
	Point(double x1, double y1) : x(x1), y(y1) {}
	Point(const Point& A) : x(A.x), y(A.y) {}
	Point(Point first, Point second) {
		x = (first.x + second.x) / 2;
		y = (first.y + second.y) / 2;

	}

	Point operator=(const Point A) {
		x = A.x;
		y = A.y;
		return *this;
	}
	
	bool operator==(Point& other) {
		return other.x == x && y == other.y;
	}
	bool operator!=(Point& other) {
		return !(other == *this);
	}
	Point operator+(Point first) {
		Point res;
		res.x = x + first.x;
		res.y = y + first.y;
		return res;
	}
	Point operator-(Point first) {
		Point res = { x - first.x, y - first.y };
		return res;
	}

	Point operator*(double a) {
		Point res = { x * a, y * a };
		return res;
	}

	Point operator/(double a) {
		Point res;
		double k = 1.0 / a;
		res.x = x*k;
		res.y = y*k;
		return res;
	}

	void draw() {
		glPointSize(5);
		glColor3f(0, 1, 0);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
		glFlush();
	}

	void line(Point& B, double& a, double& b, double& c) {
		a = B.y - y, b = x - B.x, c = (-a) * x + (-b) * y;
	}

	double dist2() {
		return x * x + y * y;
	}

	void rotate(Point& center, double rad) {
		double x_2 = center.x + cos(rad) * (x - center.x) - sin(rad) * (y - center.y);
		double y_2 = center.y + sin(rad) * (x - center.x) + cos(rad) * (y - center.y);
		x = x_2;
		y = y_2;
	}

	void scale(Point& center, double coe) {
		x = (x - center.x) * coe + center.x;
		y = (y - center.y) * coe + center.y;
	}

	void reflect(Point& center) {
		scale(center, -1);
	}

	void reflect(const Line& line);
};

double dist2(Point A) {
	return sqrt(A.x * A.x + A.y * A.y); 
}

double distance_point(Point A, Point B) {
	return sqrt((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
}

double dot(Point A, Point B) {
	return A.x * B.x + A.y * B.y;
}

double cross(Point A, Point B) {
	return A.x * B.y - A.y * B.x;
}

class Line {
public:
	double A_l;
	double B_l;
	double C_l;
	bool par = 0;
	Line() : A_l(0), B_l(0), C_l(0) {}
	Line(double a, double b, double c) : A_l(a), B_l(b), C_l(c) {}
	Line(const Point& first,const Point& second) {
		if (equal(second.x, first.x)) {
			A_l = 0;
			B_l = -1;
			C_l = first.x;
			par = 1;
		}
		else {
			A_l = (second.y - first.y) / (second.x - first.x);
			B_l = -1;
			C_l = -first.x * ((second.y - first.y) / (second.x - first.x)) + first.y;
		}
	}
	Line(double k, Point& p) {
		A_l = k;
		B_l = -1;
		C_l = p.y - k * p.x;
	}
	Line(double k, double b) {
		A_l = -k;
		B_l = 1;
		C_l = -b;
	}

	void draw() {
		glPointSize(2.0);
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POINTS);
		if (A_l!=0) {
			for (double x = -wGrid; x <= wGrid; x += 0.01) {
				double y;
				y = (A_l * x + C_l) / -B_l * 1.0;
				glVertex2f(x, y);
			}
		}
		if (A_l==0) {
			for (double y = -hGrid; y <= hGrid; y += 0.01) {
				double x;
				x = (-C_l) / B_l * 1.0;
				glVertex2f(x, y);
			}
		}
		glEnd();
		glFlush();
	}

	void rotate(Point center, double rad) {
		// ax + by + c = 0;
		// 2x + 2y + 4 = 0
		// x = 0   y = -2
		// y = 0   x = -2

		
		Point first, second;
		if (A_l != 0.0 && B_l != 0.0) {
			double x = -C_l * 1.0 / A_l;
			double y = -C_l * 1.0 / B_l;

			first.x = x, first.y = 0;
			second.x = 0, second.y = y;
		}

		else if (A_l == 0.0) {
			// ax + c = 0
			double x = -C_l * 1.0 / B_l;

			first.x = x, first.y = -10;
			second.x = x, second.y = 10;
		}

		else if (A_l != 0.0) {
			double y = -C_l * 1.0 / A_l;

			first.x = -10, first.y = y;
			second.x = 10, second.y = y;
		}


		first.rotate(center, rad);
		second.rotate(center, rad);

		Line newL(first, second);

		A_l = newL.A_l;
		B_l = newL.B_l;
		C_l = newL.C_l;
	}

	void reflex(Line axis) {
		double d = abs(A_l * axis.A_l + B_l * axis.B_l) / (pow(A_l, 2) + pow(B_l, 2));

		double a = A_l - 2 * d * A_l;
		double b = B_l - 2 * d * B_l;
		double c = -a * axis.A_l - b * axis.B_l - axis.C_l;

		A_l = a;
		B_l = b;
		C_l = c;
	}

	void reflex(Point center) {
		if (A_l != 0)
		{
			double X = -(B_l * center.y + C_l) / A_l;
			C_l -= (center.x - X) * 2;
		}
		else
		{
			double Y = -C_l / B_l;
			C_l += (center.y - C_l) * 2;
		}
	}

	bool operator==(Line& other) {
		return (A_l == other.A_l) && (B_l == other.B_l) && (C_l == other.C_l);
	}

	bool operator!=(Line& other) {
		return !(*this == other);
	}
};

Point intersect(const Line& first, Line& second) {
	//assert(!abs((first.B_l*second.A_l-first.A_l*second.B_l) < 0.00001));
	double x = (first.B_l * second.C_l - second.B_l * first.C_l) / (first.A_l * second.B_l - second.A_l * first.B_l);
	double y = (first.C_l * second.A_l - second.C_l * first.C_l) / (first.A_l * second.B_l - second.A_l * first.B_l);
	return { x, y };
}

Line orthogonal(Line line, Point axis) {

	line.rotate(axis, PI/2);
	return line;
}

void Point::reflect(const Line& line) {
	if (line.B_l == 0)
	{
		x = (-line.C_l / line.A_l) * 2 - x;
		y = (-line.C_l / line.A_l) * 2 - y;
	}
	else
	{
		Point P;
		P.x = -(line.A_l * line.C_l + line.B_l * (line.A_l * y - line.B_l * x)) / (line.A_l * line.A_l + line.B_l * line.B_l);
		P.y = -(line.A_l * P.x + line.C_l) / line.B_l;
		x = P.x * 2 - this->x;
		y = P.y * 2 - this->y;

	}
}

class Shape {
public:
	virtual double perimeter() = 0;
	virtual double area() = 0;
	virtual bool operator==(Shape& another) = 0;
	virtual bool isCongruentTo(Shape& another) = 0;
	virtual bool isSimilarTo(Shape& another) = 0;
	virtual bool containsPoint(Point point) = 0;

	virtual void rotate(Point center, double angle) = 0;
	virtual void reflex(Point center) = 0;
	virtual void reflex(Line axis) = 0;
	virtual void scale(Point center, double coefficient) = 0;
};

class Polygon : public Shape {
protected:
	vector<Point> Vertex;
	int sz;
public:
	Polygon() : Vertex({}), sz(0) {}
	Polygon(vector<Point>& A) {
		sz = A.size();
		for (int i = 0; i < sz; i++) {
			Vertex.push_back(A[i]);
		}
	}

	template<typename... T>
	Polygon(T... points) : Vertex({ points... }) {};

	int verticesCount() { return Vertex.size(); }
	vector<Point> getVertices() { return Vertex; }
	bool isConvex() {
		int size = Vertex.size();
		if (size < 4)
			return true;
		for (int i = 0; i < size; i++)
		{
			double a, b, c;
			Vertex[(size - 1 + i) % size].line(Vertex[(i + 1) % size], a, b, c);
			bool res = (Vertex[i].x * a + Vertex[i].y * b + c) * (Vertex[(i + 2) % size].x * a + Vertex[(i + 2) % size].y * b + c) > 0;
			if (!res)
				return false;
		}
		return true;
	}

	void draw() {
		glLineWidth(3);
		glColor3f(0, 1, 0);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < Vertex.size(); i++) {
			glVertex2d(Vertex[i].x, Vertex[i].y);
		}
		glEnd();
		glFlush();
	}

	double perimeter() override {
		double per = 0;
		if (Vertex.size() <= 1) return 0;
		else {
			for (int i = 0; i < Vertex.size()-1; i++) {
				per += distance_point(Vertex[i], Vertex[i + 1]);
			}
			per += distance_point(Vertex[Vertex.size() - 1], Vertex[0]);
			return per;
		}
		
	}
	double area() override {
		double sq = 0;
		for (int i = 0; i < Vertex.size(); i++) {
			sq += Vertex[i].x * Vertex[(i + 1) % Vertex.size()].y -
				Vertex[i].y * Vertex[(i + 1) % Vertex.size()].x;
		}
		return fabsl(sq / 2);
	}
	bool operator==(Shape& other) override {
		Polygon* another = dynamic_cast<Polygon*>(&other);
		if (Vertex.size() != another->Vertex.size()) return false;
		bool good;
		for (int i = 0; i < Vertex.size(); i++) {
			good = 0;
			for (int j = 0; j < another->Vertex.size(); j++) {
				if (Vertex[i] == another->Vertex[j]) {
					good = 1;
					break;
				}
			}
			if (!good) {
				return false;
			}
		}
		return true;
	}
	bool isCongruentTo(Shape& other) override{
		Polygon* casted = dynamic_cast<Polygon*>(&other);
		if (isSimilarTo(other) && equal(area(), casted->area()))
			return true;
		return false;
	}
	bool isSimilarTo(Shape& other) override{
		Polygon* casted = dynamic_cast<Polygon*>(&other);
		if (casted == nullptr || casted->verticesCount() != verticesCount() || isConvex() != casted->isConvex())
			return false;

		int size = Vertex.size();
		vector<double> A(size), B(size);
		for (int i = 0; i < size; i++)
		{
			double a, b, c;
			a = (Vertex[i] - Vertex[(i + 1) % size]).dist2();
			b = (Vertex[(i + 1) % size] - Vertex[(i + 2) % size]).dist2();
			c = (Vertex[(i + 2) % size] - Vertex[i]).dist2();
			A[i] = (b + c - a) / (2 * sqrt(b) * sqrt(c));
		}
		for (int i = 0; i < size; i++)
		{
			double a, b, c;
			a = (casted->Vertex[i] - casted->Vertex[(i + 1) % size]).dist2();
			b = (casted->Vertex[(i + 1) % size] - casted->Vertex[(i + 2) % size]).dist2();
			c = (casted->Vertex[(i + 2) % size] - casted->Vertex[i]).dist2();
			B[i] = (b + c - a) / (2 * sqrt(b) * sqrt(c));
		}

		bool flag;
		double k;
		for (int i = 0; i < size; i++)
		{
			flag = 1;
			k = (Vertex[i] - Vertex[(i + 1) % size]).dist2() / (casted->Vertex[0] - casted->Vertex[1]).dist2();
			for (int j = 0; j < size; j++)
			{
				if (A[i] - B[j] > 0.00001 ||
					(Vertex[i] - Vertex[(i + 1) % size]).dist2() / (casted->Vertex[j] - casted->Vertex[(j + 1) % size]).dist2() - k > 0.00001)
				{
					flag = 0;
					break;
				}
			}
			if (flag)
			{
				return true;
			}
		}
		return false;
	}
	bool containsPoint(Point other) override{
		if (verticesCount() <= 2)
			return false;

		bool result = false;
		int j = Vertex.size() - 1;
		for (int i = 0; i < Vertex.size(); i++) {
			if ((Vertex[i].y < other.y && Vertex[j].y >= other.y || Vertex[j].y < other.y && Vertex[i].y >= other.y) &&
				(Vertex[i].x + (other.y - Vertex[i].y) / (Vertex[j].y - Vertex[i].y) * (Vertex[j].x - Vertex[i].x) < other.x))
				result = !result;
			j = i;
		}
		return result;
	}
	void rotate(Point center, double angle) {
		double rad = angle * PI / 180;
		for (int i = 0; i < Vertex.size(); i++)
		{
			Point c = (Vertex[i] - center);
			Vertex[i].x = c.x * cos(rad) - c.y * sin(rad) + center.x;
			Vertex[i].y = c.x * sin(rad) + c.y * cos(rad) + center.y;
		}
	}
	void reflex(Point center) {
		for (int i = 0;i < Vertex.size(); i++) {
			Vertex[i].reflect(center);
		}
	}
	void reflex(Line axis) {
		for (int i = 0;i < Vertex.size(); i++) {
			Vertex[i].reflect(axis);
		}
	}
	void scale(Point center, double coefficient) {
		for (int i = 0; i < Vertex.size(); i++)
		{
			Vertex[i].scale(center, coefficient);
		}
	}
};

class Rectangle : public Polygon {
public:
	Rectangle(Point a, Point b, double k) : Polygon({ a, Point(0, 0), b, Point(0, 0) }) {
		double angle = PI - 2 * atan(k);
		Point middle = Point(a, b);
		a.rotate(middle, angle);
		Vertex[1] = a;
		b.rotate(middle, angle);
		Vertex[3] = b;
	}

	Point center() {
		vector<Point> ver = getVertices();
		return { (ver[0].x + ver[2].x) / 2, (ver[0].y + ver[2].y) / 2 };
	}

	pair<Line, Line> diagonals() {
		vector<Point> ver = getVertices();
		return { Line(ver[0], ver[2]), Line(ver[1], ver[3]) };
	}
};

class Ellipse : public Shape {
	Point f1, f2;
	protected:
		double dist;
		vector<double> abc() {
			double a = dist / 2;
			double b = sqrt(pow(a, 2) - pow(distance_point(f1, f2) / 2, 2));
			double c = sqrt(pow(a, 2) - pow(b, 2));
			if (a < b) { swap(a, b); }
			return { a, b, c };
		}
	public:
		Ellipse(Point f1, Point f2, double dist) : f1(f1), f2(f2), dist(dist) {}
		pair<Point, Point> focuses() {
			return { f1,f2 };
		}

		pair<Line, Line> directrices() {
			auto params = abc();
			Line line = Line(f1, f2);
			Point d_1 = f1;
			d_1.scale(f2, (params[0] + params[0] * params[0] / params[2]) / (2 * params[0]));
			Point d_2 = f2;
			d_2.scale(f1, (params[0] + params[0] * params[0] / params[2]) / (2 * params[0]));
			return { Line(d_1, d_1 + Point(line.A_l, line.B_l)),
					Line(d_2, d_2 + Point(line.A_l, line.B_l)) };
		}

		double eccentricity() {
			auto params = abc();
			return params[2] / params[0];
		}

		Point center() {
			return { (f1.x + f2.x) / 2, (f1.y + f2.y) / 2 };
		}
		
		bool operator==(Shape& another) override {
			auto casted = dynamic_cast<Ellipse*>(&another);
			if ((casted != nullptr) &&
				((casted->f1 == f1 && casted->f2 == f2) ||
					(casted->f1 == f2 && casted->f1 == f2)) &&
				equal(casted->dist, dist)) {
				return true;
			}
			return false;
		}

		bool isCongruentTo(Shape& another) override {
			auto casted = dynamic_cast<const Ellipse*>(&another);
			if ((casted != nullptr) &&
				equal(distance_point(casted->f1, casted->f2),
					distance_point(f1, f2)) &&
				equal(casted->dist, dist)) {
				return true;
			}
			return false;
		}

		bool isSimilarTo(Shape& another)override {
			auto casted = dynamic_cast<const Ellipse*>(&another);
			if ((casted != nullptr) &&
				equal(distance_point(casted->f1, casted->f2),
					distance_point(f1, f2) * casted->dist / dist)) {
				return true;
			}
			return false;
		}

		bool containsPoint(Point point) override {
			if (distance_point(point, f1) + distance_point(point, f2) <= dist) {
				return true;
			}
			return false;
		}
		void draw()
		{
			auto params = abc();
			double a = params[0];
			double b = params[1];
			Point center((f1.x + f2.x) / 2, (f1.y + f2.y) / 2);
			Point rotat(f1.x - f2.x, f1.y - f2.y);
			double degree = atan(rotat.y / rotat.x);

			const int N = 360; 
			glLineWidth(2);
			glBegin(GL_LINE_LOOP); 
			for (int i = 0; i < N; i++)
			{
				double angle = i * PI / 180.0;
				double x = a * cos(angle) + center.x;
				double y = b * sin(angle) + center.y;
				Point rotated(x, y);
				if(f1!=f2)rotated.rotate(center, degree);
				glVertex2f(rotated.x, rotated.y);
			}
			glEnd();
		}

		double perimeter() override {
			auto params = abc();
			return PI * (3 * (params[0] + params[1]) -
				sqrtl((3 * params[0] + params[1]) * (params[0] + 3 * params[1])));
		}
		double area() override {
			auto params = abc();
			return PI * params[0] * params[1];
		}
		void rotate(Point center, double angle) override {
			double rad = angle*PI/180.0;
			f1.rotate(center, rad);
			f2.rotate(center, rad);
		}
		void reflex(Point center) override {
			f1.reflect(center);
			f2.reflect(center);
		}
		void reflex(Line axis) override {
			f1.reflect(axis);
			f2.reflect(axis);
		}
		void scale(Point center, double coefficient) override {
			f1.scale(center, coefficient);
			f2.scale(center, coefficient);
			dist *= coefficient;
		}
};

class Circle : public Ellipse {
public:
	Circle(Point p, double r) : Ellipse(p, p, r*2) {}
	double radius() const {
		return dist / 2;
	}
};

class Triangle : public Polygon {
	using Polygon::Polygon;

public:
	Circle circumscribedCircle() {
		Line first = orthogonal(Line(Vertex[0], Vertex[1]), (Vertex[0] + Vertex[1]) / 2);
		Line second = orthogonal(Line(Vertex[1], Vertex[2]), (Vertex[1] + Vertex[2]) / 2);
		Point center = intersect(first, second);
		return { center, distance_point(center, Vertex[0])};
	}

	Circle inscribedCircle() {
		double a = (Vertex[0], Vertex[1]).dist2();
		double b = (Vertex[1], Vertex[2]).dist2();
		double c = (Vertex[2], Vertex[0]).dist2();
		Point tmp;
		tmp.x = (Vertex[2].x * a + Vertex[0].x * b + Vertex[1].x * c) / (a + b + c);
		tmp.y = (Vertex[2].y * a + Vertex[0].y * b + Vertex[1].y * c) / (a + b + c);
		return { tmp, 2 * area() / (a + b + c) };
	}

	Point centroid() {
		double x = (Vertex[0].x + Vertex[1].x + Vertex[2].x) / 3;
		double y = (Vertex[0].y + Vertex[1].y + Vertex[2].y) / 3;
		return { x, y };
	}

	Point orthocenter() {
		Line first = orthogonal(Line(Vertex[0], Vertex[1]), Vertex[2]);
		Line second = orthogonal(Line(Vertex[1], Vertex[2]), Vertex[0]);
		return intersect(first, second);
	}

	Line EulerLine() {
		return { circumscribedCircle().center(), orthocenter() };
	}

	Circle ninePointsCircle() {//окружность эйлера
		Point first = circumscribedCircle().center();
		Point second = orthocenter();
		Point center = Point((first.x + second.x) / 2, (first.y + second.y) / 2);
		return { center, circumscribedCircle().radius() / 2 };
	}
};

class Square : public Rectangle {//квадрат
public:
	Square(Point a, Point b) : Rectangle(a, b, 1) {}
	
	Circle circumscribedCircle() { //вписанная окружность
		vector<Point> ver = getVertices();
		return { center(), distance_point(ver[0], ver[1]) / 2 };
	}

	Circle inscribedCircle() {//описанная окружность
		vector<Point> ver = getVertices();
		return { center(), distance_point(ver[0], ver[2]) / 2 };
	}
};