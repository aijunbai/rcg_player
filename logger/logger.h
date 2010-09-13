/*
 * logger.h
 *
 *  Created on: Sep 11, 2010
 *      Author: baj
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
#include <vector>

/**
 * RCG format logger
 */
class Logger {
public:
	enum Color {
		Red,
		Blue,
		Green,
		Navy,
		Orange,
		Cyan,
		Purple,
		White,
		Black,
		Yellow,
		Olive
	};

	struct Vector {
		double x_;
		double y_;

		Vector(const double & x, const double & y): x_(x), y_(y) {

		}

		Vector operator-() const { return Vector(-x_, -y_); }
		Vector operator+(const Vector &a) const { return Vector(x_ + a.x_, y_ + a.y_); }
		Vector operator-(const Vector &a) const { return Vector(x_ - a.x_, y_ - a.y_); }
		Vector operator*(const double & a) const { return Vector(x_ * a, y_ * a); }
		Vector operator/(double a) const { return Vector(x_ / a, y_ / a); }

		const double & X() const { return x_; }
		const double & Y() const { return y_; }
	};

	class Rectangular
	{
	public:
		Rectangular(): left_(0.0), right_(0.0), top_(0.0), bottom_(0.0) {}
		Rectangular(const double & left, const double & right, const double & top, const double & bottom): left_(left), right_(right), top_(top), bottom_(bottom) {}

		const double & Left() const { return left_; }
		const double & Right() const { return right_; }
		const double & Top() const { return top_; }
		const double & Bottom() const { return bottom_; }

		void SetLeft(const double & left) { left_ = left; }
		void SetRight(const double & right) { right_ = right; }
		void SetTop(const double & top) { top_ = top; }
		void SetBottom(const double & bottom) { bottom_ = bottom; }

		Vector TopLeftCorner() const { return Vector(left_, top_); }
		Vector TopRightCorner() const { return Vector(right_, top_); }
		Vector BottomLeftCorner() const { return Vector(left_, bottom_); }
		Vector BottomRightCorner() const { return Vector(right_, bottom_); }

	public:
		double left_; // ¾ØÐÎ×ó±ß
		double right_; // ¾ØÐÎÓÒ±ß
		double top_; // ¾ØÐÎÉÏ±ß
		double bottom_; // ¾ØÐÎÏÂ±ß
	};

private:
	struct ItemShape {
		Color line_color;

		const char *color() const {
			switch (line_color){
			case Red: return "red";
			case Blue: return "blue";
			case Green: return "green";
			case Navy: return "navy";
			case Orange: return "orange";
			case Cyan: return "cyan";
			case Purple: return "purple";
			case White: return "white";
			case Black: return "black";
			case Yellow: return "yellow";
			case Olive: return "olive";
			}
			return "black";
		}

		ItemShape (Color color){
			line_color = color;
		}
	};

	struct PointShape: public ItemShape {
		double x, y;
		std::string comment;

		PointShape (const Vector & point, Color color, const char* cmt = 0): ItemShape(color){
			x = point.X();
			y = point.Y();
			if (cmt)
			{
				comment.assign(cmt);
			}
		};

		friend std::ostream& operator<<(std::ostream &os, PointShape &point) {
			return os << "(point " << point.x << ' ' << point.y << ' ' << "\"" << point.color() << "\" "<<point.comment<<")";
		}
	};

	struct LineShape: public ItemShape {
		double x1, y1;
		double x2, y2;
		int width;

		LineShape (const Vector & from, const Vector & to, Color color): ItemShape(color){
			x1 = from.X();
			y1 = from.Y();
			x2 = to.X();
			y2 = to.Y();
		};

		friend std::ostream& operator<<(std::ostream &os, const LineShape &line) {
			return os << "(line " << line.x1 << ' ' << line.y1 << ' ' << line.x2 << ' ' << line.y2 << " \"" << line.color() << "\")";
		}
	};

	struct CircleShape: public ItemShape {
		double x, y;
		double radius;

		CircleShape (const Vector & center, const double & r, Color color): ItemShape(color){
			x = center.X();
			y = center.Y();
			radius = r;
		};

		friend std::ostream& operator<<(std::ostream &os, CircleShape &circle) {
			return os << "(circle " << circle.x << ' ' << circle.y << ' ' << circle.radius << " \"" << circle.color() << "\")";
		}
	};

public:
	void AddPoint(const Vector & point, const char* comment = 0, Color color = Red) { points_.push_back(PointShape(point, color, comment)); }
	void AddLine(const Vector & origin, const Vector & target, Color color = Yellow) { lines_.push_back(LineShape(origin, target, color)); }
	void AddCircle(const Vector & origin, const double & radius, Color color = White) { circles_.push_back(CircleShape(origin, radius, color)); }

public:
	Logger(const char *file_name): time_(0), focus_(0.0, 0.0), scale_x_(1.0), scale_y_(1.0) {
		fout.open(file_name);
	}

	~Logger() {
		fout.close();
	}

	void Flush();

	void LogLine(const Vector & begin, const Vector & end, Color color, const char* comment);
	void LogCircle(const Vector & o, const double & r, Color color);
	void LogRectangular(const Rectangular & rect, Color color);

	void Scale(double x, double y);
	void Focus(Vector focus);

private:
	std::ofstream fout;
	int time_;

	std::vector<PointShape> points_;
	std::vector<LineShape> lines_;
	std::vector<CircleShape> circles_;

	Vector focus_;
	double scale_x_;
	double scale_y_;
};

#endif /* LOGGER_H_ */
