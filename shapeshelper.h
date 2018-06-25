#ifndef SHAPESHELPER_H
#define SHAPESHELPER_H

#include "container.h"

class Shape;
class Point;
class Rect;



namespace ShapesHelper
{
	enum class CircleDirection
	{
		Clockwise, CounterClockwise
	};

	enum class AngleMeasure
	{
		Degrees, Radians
	};

	enum class ShapeType
	{
		Point, Circle, Rect, Square, Polyline, Polygon
	};

	class Interval
	{
	public:
		virtual bool Contains( double value ) const = 0;

		virtual ~Interval() {}
	protected:
		double m_lowValue;
		double m_highValue;
	};

	class ClosedInterval : public Interval
	{
	public:
		bool Contains( double value ) const override;

		ClosedInterval( double l, double h );
	};

	class Angle
	{
	public:
		explicit Angle( double value, AngleMeasure m = AngleMeasure::Radians );

		bool IsInClosedInterval( double a1, double a2, AngleMeasure m = AngleMeasure::Radians ) const;

		double GetRadians() const { return m_radians; }
		double GetDegrees() const;		
	private:
		double m_radians;
	};

	class Vector
	{
	public:
		Vector( Point const & p1, Point const & p2 );
		Vector( double x, double y );

		// getters
		Angle GetRelativeAngle( Vector const & fixed, CircleDirection d = CircleDirection::CounterClockwise ) const;
		double GetNorm() const;
		Vector GetNormal( CircleDirection d ) const;

		double operator*( Vector const & other ) const;
	private:
		double m_x;
		double m_y;
	};

	class LineSegment
	{
	public:
		LineSegment( Point const * p1, Point const * p2 );
		LineSegment( double x1, double y1, double x2, double y2 );

		// question
		bool Intersects( LineSegment const & other ) const;
		bool IntersectsLineOf( LineSegment const & other ) const;

		// getters
		double GetLength() const;
	private:
		Point const * m_p1;
		Point const * m_p2;
	};

	double GetDistance( Point const &, Point const & );
	void MoveLastItemToBegin( Container< Point > & points );
	bool IsCircularShift( Container< Point > const & c1, Container< Point > const & c2 );
	Container< Point > GetInvertedContainer( Container< Point > const & points );

	Shape const * GetShape( ShapeType type );
}

#endif // SHAPESHELPER_H
