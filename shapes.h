#ifndef SHAPES_H
#define SHAPES_H

#include "base.h"
#include "container.h"
#include "shapeshelper.h"

#include <iostream>
#include <cmath>
#include <vector>

using LineSegment = ShapesHelper::LineSegment;

class Point;
class Rect;



class Shape : public virtual Printable
{
public:
	Shape() { ++sm_count; }

	virtual ~Shape() { --sm_count; }

	static uint16_t GetCount() { return sm_count; }	
private:
	static uint16_t sm_count;
};



class Point : public Shape, public Named
{
public:
	Point( double x, double y )
		: Named( "Point" ),
		  m_x( x ),
		  m_y( y )
	{}
	Point( Point const & other );

	void PrintInfo() const override;

	// getters
	double X() const { return m_x; }
	double Y() const { return m_y; }

	// questions
	bool IsInsideRect( Rect const & ) const;
	bool operator==( Point const & other ) const;
	bool operator!=( Point const & other ) const { return !( *this == other ); }

	friend std::ostream & operator<<( std::ostream & os, Point const & );
private:
	double const m_x;
	double const m_y;
};

class Circle : public Shape, public Named
{
public:
	Circle( Point const & center, double radius );
	Circle( Circle const & other );

	virtual void PrintInfo() const override;

	// getters
	Point const & GetCenter() const { return m_center; }
	double GetRadius() const { return m_radius; }
	double GetArea() const { return M_PI * m_radius * m_radius; }

	bool operator==( Circle const & other ) const;
	bool operator!=( Circle const & other ) const { return !( *this == other ); }

	friend std::ostream & operator<<( std::ostream & os, Circle const & );
private:
	Point const m_center;
	double const m_radius;
};

class Rect : public Shape, public Named
{
public:
	Rect( Point const & topLeft, Point const & bottomRight );
	Rect( Point const & center, double width, double height );
	Rect( Rect const & other );

	virtual void PrintInfo() const override;

	// getters
	Point const & GetCenter() const { return m_center; }
	double GetWidth() const { return m_width; }
	double GetHeight() const { return m_height; }
	Point GetBottomLeftCorner() const;
	Point GetTopRightCorner() const;
	Point GetBottomRightCorner() const;
	Point GetTopLeftCorner() const;
	double GetArea() const { return m_width * m_height; }

	// questions
	bool Contains( Point const & ) const;
	bool IsSquare() const;
	bool operator==( Rect const & other ) const;
	bool operator!=( Rect const & other ) const { return !( *this == other ); }

	friend std::ostream & operator<<( std::ostream & os, Rect const & );
private:
	Point const m_center;
	double const m_width;
	double const m_height;
};

class Square : public Rect
{
public:
	Square( Point const & center, double edge )
		: Rect( center, edge, edge )
	{
		SetName( "Square" );
	}

	virtual void PrintInfo() const override;

	friend std::ostream & operator<<( std::ostream & os, Square const & );

	// getters
	double GetEdge() const { return GetWidth(); }
};

class Polyline : public Shape, public Named
{
public:
	Polyline( Point const & begin );

	virtual void PrintInfo() const override;

	void AddPoint( Point const & newVertice );
	void Close();

	// getters
	Container< Point > GetVertices() const;
	double GetLength() const;
	Point const & GetBegin() const;
	Point const & GetEnd() const;
	uint16_t GetVerticesCount() const;

	// questions
	bool IsClosed() const;
	bool operator==( Polyline const & other ) const;
	bool operator!=( Polyline const & other ) const { return !( *this == other ); }

	friend std::ostream & operator<<( std::ostream & os, Polyline const & );
private:
	Container< Point > m_vertices;
	bool m_isClosed;

	bool VerticesContainPoint( Point const & p ) const;
};

class Polygon : public Shape, public Named
{
public:
	Polygon( Container< Point > const & vertices );

	virtual void PrintInfo() const override;

	// getters
	uint16_t GetVerticesCount() const { return m_vertices.GetSize(); }
	Container< Point > const & GetVertices() const { return m_vertices; }
	Container< LineSegment > const & GetEdges() const { return m_edges; }
	double GetPerimeter() const;

	// questions
	bool IsConvex() const;
	bool IsTriangle() const;
	bool operator==( Polygon const & other ) const;
	bool operator!=( Polygon const & other ) const { return !( *this == other ); }

	friend std::ostream & operator<<( std::ostream & os, Polygon const & );
private:
	Container< Point > m_vertices;
	Container< LineSegment > m_edges;

	static uint16_t GetRemainder( int a, uint16_t b );
	static LineSegment GetLineSegment( Container< Point > const & vertices, int index );
	static Point const & GetVertex( Container< Point > const & vertices, int index );
	Point const & GetVertex( int index ) const;
	static bool VerticesContainsEqualsPoints( Container< Point > const & vertices );
	static bool VerticesAreCollinear( Point const & p1, Point const & p2, Point const & p3 );
};

#endif // SHAPES_H
