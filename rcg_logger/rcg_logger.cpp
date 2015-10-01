/*
 * logger.cpp
 *
 *  Created on: Sep 11, 2010
 *      Author: baj
 */

#include "rcg_logger.h"

void RCGLogger::LogLine(float x1, float y1, float x2, float y2, Color color, const char* comment)
{
  AddPoint(x2, y2, color, comment);
  AddLine(x1, y1, x2, y2, color);
}

void RCGLogger::LogCircle(float x, float y, float r, Color color)
{
  AddCircle(x, y, r, color);
}

void RCGLogger::LogRectangular(const float left, const float right, const float top, const float bottom, RCGLogger::Color color)
{
  AddLine(left, top, right, top, color);
  AddLine(left, top, left, bottom, color);
  AddLine(left, bottom, right, bottom, color);
  AddLine(right, bottom, right, top, color);
}

void RCGLogger::Flush()
{
  if (!fout.good()) return;

  fout << "(scale " << time_ << ' ' << scale_x_ << ' ' << scale_y_ <<")\n";
  fout << "(focus " << time_ << ' ' << focus_.x_ << ' ' << focus_.y_ << ")\n";

  if (!points_.empty()) {
    for (std::vector<PointShape>::iterator it = points_.begin(); it != points_.end(); it++)
    {
      fout << "(draw " << time_ << ' '<< *it <<")\n";
    }
    points_.clear();
  }

  if (!lines_.empty()) {
    for (std::vector<LineShape>::iterator it = lines_.begin(); it != lines_.end(); it++)
    {
      fout << "(draw " << time_ << ' '<< *it <<")\n";
    }
    lines_.clear();
  }

  if (!circles_.empty()) {
    for (std::vector<CircleShape>::iterator it = circles_.begin(); it != circles_.end(); it++)
    {
      fout << "(draw " << time_ << ' '<< *it <<")\n";
    }
    circles_.clear();
  }

  time_ += 1;
}

void RCGLogger::Scale(float x, float y)
{
  scale_x_ = x;
  scale_y_ = y;
}

void RCGLogger::Focus(float x, float y)
{
  focus_ = Vector(x, y);
}
