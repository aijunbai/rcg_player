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
 * RCG format logger (should be played with rcg_player)
 */
class RCGLogger {
public:
  enum Color {
    Orange,
    Cyan,
    Purple,
    Yellow,
    Olive,
    Navy,
    Green,
    Gray,
    Red,
    Blue,
    White,
    Black,

    Color_Max
  };

  struct Vector {
    float x_;
    float y_;

    Vector(const float & x, const float & y): x_(x), y_(y) {

    }

    Vector operator-() const { return Vector(-x_, -y_); }
    Vector operator+(const Vector &a) const { return Vector(x_ + a.x_, y_ + a.y_); }
    Vector operator-(const Vector &a) const { return Vector(x_ - a.x_, y_ - a.y_); }
    Vector operator*(const float & a) const { return Vector(x_ * a, y_ * a); }
    Vector operator/(float a) const { return Vector(x_ / a, y_ / a); }

    const float & X() const { return x_; }
    const float & Y() const { return y_; }
  };

  class Rectangular
  {
  public:
    Rectangular(): left_(0.0), right_(0.0), top_(0.0), bottom_(0.0) {}
    Rectangular(const float & left, const float & right, const float & top, const float & bottom): left_(left), right_(right), top_(top), bottom_(bottom) {}

    const float & Left() const { return left_; }
    const float & Right() const { return right_; }
    const float & Top() const { return top_; }
    const float & Bottom() const { return bottom_; }

    void SetLeft(const float & left) { left_ = left; }
    void SetRight(const float & right) { right_ = right; }
    void SetTop(const float & top) { top_ = top; }
    void SetBottom(const float & bottom) { bottom_ = bottom; }

    Vector TopLeftCorner() const { return Vector(left_, top_); }
    Vector TopRightCorner() const { return Vector(right_, top_); }
    Vector BottomLeftCorner() const { return Vector(left_, bottom_); }
    Vector BottomRightCorner() const { return Vector(right_, bottom_); }

  public:
    float left_;
    float right_;
    float top_;
    float bottom_;
  };

private:
  struct ItemShape {
    Color line_color;

    const char *color() const {
      switch (line_color) {
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
      case Gray: return "gray";
      default: return "black";
      }

      return "black";
    }

    ItemShape (Color color){
      line_color = color;
    }
  };

  struct PointShape: public ItemShape {
    float x, y;
    std::string comment;

    PointShape (float x_, float y_, Color color, const char* cmt = 0): ItemShape(color), x(x_), y(y_) {
      if (cmt) {
        comment.assign(std::string("@") + cmt);
      }
    };

    friend std::ostream& operator<<(std::ostream &os, PointShape &point) {
      return os << "(point " << point.x << ' ' << point.y << ' ' << "\"" << point.color() << "\" "<<point.comment<<")";
    }
  };

  struct LineShape: public ItemShape {
    float x1, y1;
    float x2, y2;

    LineShape (float x1_, float y1_, float x2_, float y2_, Color color):
       ItemShape(color), x1(x1_), y1(y1_), x2(x2_), y2(y2_)
    {
    };

    friend std::ostream& operator<<(std::ostream &os, const LineShape &line) {
      return os << "(line " << line.x1 << ' ' << line.y1 << ' ' << line.x2 << ' ' << line.y2 << " \"" << line.color() << "\")";
    }
  };

  struct CircleShape: public ItemShape {
    float x, y;
    float radius;

    CircleShape (float x_, float y_, float r, Color color): ItemShape(color), x(x_), y(y_), radius(r) {
    };

    friend std::ostream& operator<<(std::ostream &os, CircleShape &circle) {
      return os << "(circle " << circle.x << ' ' << circle.y << ' ' << circle.radius << " \"" << circle.color() << "\")";
    }
  };

public:
  void AddPoint(float x, float y, Color color = Red, const char* comment = 0) {
    points_.push_back(PointShape(x, y, color, comment));
  }

  void AddLine(float x1, float y1, float x2, float y2, Color color = Yellow) {
    lines_.push_back(LineShape(x1, y1, x2, y2, color));
  }

  void AddCircle(float x, float y, const float & radius, Color color = White) {
    circles_.push_back(CircleShape(x, y, radius, color));
  }

public:
  RCGLogger(const char *file_name): time_(0), focus_(0.0, 0.0), scale_x_(1.0), scale_y_(1.0) {
    std::string file = file_name;
    file += ".rcg";

    fout.open(file.c_str());
  }

  ~RCGLogger() {
    fout.close();
  }

  void Flush();

  void LogLine(float x1, float y1, float x2, float y2, Color color, const char* comment = 0);
  void LogCircle(float x, float y, float r, Color color);
  void LogRectangular(const float left, const float right, const float top, const float bottom, Color color);

  void Scale(float x, float y);
  void Focus(float x, float y);

private:
  std::ofstream fout;
  int time_;

  std::vector<PointShape> points_;
  std::vector<LineShape> lines_;
  std::vector<CircleShape> circles_;

  Vector focus_;
  float scale_x_;
  float scale_y_;
};

#endif /* LOGGER_H_ */
