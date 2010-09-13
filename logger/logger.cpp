/*
 * logger.cpp
 *
 *  Created on: Sep 11, 2010
 *      Author: baj
 */

#include "logger.h"

void Logger::LogLine(const Vector & begin, const Vector & end, Logger::Color color, const char* comment)
{
	AddPoint(end, comment, color);
	AddLine(begin, end, color);
}

void Logger::LogCircle(const Vector & o, const double & r, Logger::Color color)
{
	AddCircle(o, r, color);
}

void Logger::LogRectangular(const Rectangular & rect, Logger::Color color)
{
	AddLine(rect.TopLeftCorner(), rect.TopRightCorner(), color);
	AddLine(rect.TopLeftCorner(), rect.BottomLeftCorner(), color);
	AddLine(rect.BottomLeftCorner(), rect.BottomRightCorner(), color);
	AddLine(rect.BottomRightCorner(), rect.TopRightCorner(), color);
}

void Logger::Flush()
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

void Logger::Scale(double x, double y)
{
	scale_x_ = x;
	scale_y_ = y;
}

void Logger::Focus(Vector focus)
{
	focus_ = focus;
}
