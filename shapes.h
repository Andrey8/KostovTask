#ifndef SHAPES_H
#define SHAPES_H

#include "base.h"
#include "container.h"
#include "shapeshelper.h"

#include <iostream>
#include <cmath>
#include <vector>

using std::cout;
using std::endl;
using namespace ShapesHelper;
using Iter = Container< Point >::ConstIterator;

class Point;
class Rect;



class Shape : public virtual Printable
{
public:
	static uint16_t GetCount() { return sm_count; }

	static void IncrementCount() { ++sm_count; }
	static void DecrementCount() { --sm_count; }

	virtual ~Shape() {}
private:
	static uint16_t sm_count;
};



class Point : public Shape, public Named
{
public:
	void PrintInfo() const override;

	// getters
	double X() const { return m_x; }
	double Y() const { return m_y; }

	// setters
	void SetCoords( double x, double y ) { m_x = x; m_y = y; }

	// questions
	bool IsInsideRect( Rect const & ) const;
	bool operator==( Point const & other ) const;
	bool operator!=( Point const & other ) const { return !( *this == other ); }

	friend std::ostream & operator<<(
		std::ostream & os, Point const & );

	Point( double x, double y )
		: Named( "Point" ),
		  m_x( x ),
		  m_y( y )
	{
		IncrementCount();
	}
	Point( Point const & other );

	~Point() { DecrementCount(); }
private:
	double m_x;
	double m_y;
};

class Circle : public Shape, public Named
{
public:
	virtual void PrintInfo() const override;

	// getters
	Point const & GetCenter() const { return m_center; }
	double GetRadius() const { return m_radius; }
	double GetArea() const { return M_PI * m_radius * m_radius; }

	bool operator==( Circle const & other ) const;
	bool operator!=( Circle const & other ) const { return !( *this == other ); }

	friend std::ostream & operator<<(
		std::ostream & os, Circle const & );

	Circle( Point const & center, double radius );
	Circle( Circle const & other );

	~Circle() { DecrementCount(); }
private:
	Point m_center;
	double m_radius;
};

class Rect : public Shape, public Named
{
public:
	virtual void PrintInfo() const override;

	// getters
	double GetWidth() const { return m_width; }
	double GetHeight() const { return m_height; }
	Point GetBottomLeft() const;
	Point GetTopRight() const;
	Point GetBottomRight() const;
	Point GetTopLeft() const;
	Point const & GetCenter() const { return m_center; }
	double GetArea() const { return m_width * m_height; }
	double GetLeftBorder() const { return GetTopLeft().X(); }
	double GetRightBorder() const { return GetTopRight().X(); }
	double GetTopBorder() const { return GetTopLeft().Y(); }
	double GetBottomBorder() const { return GetBottomLeft().Y(); }

	// questions
	bool Contains( Point const & ) const;
	bool IsSquare() const;
	bool operator==( Rect const & other ) const;
	bool operator!=( Rect const & other ) const { return !( *this == other ); }

	friend std::ostream & operator<<(
		std::ostream & os, Rect const & );

	Rect( Point const & topLeft, Point const & bottomRight );
	Rect( Point const & center, double width, double height );
	Rect( Rect const & other );

	~Rect() { DecrementCount(); }
private:
	Point m_center;
	double m_width;
	double m_height;
};

class Square : public Rect
{
public:
	virtual void PrintInfo() const override;

	friend std::ostream & operator<<(
		std::ostream & os, Square const & );

	// getters
	double GetEdge() const { return GetWidth(); }

	Square( Point const & center, double edge )
		: Rect( center, edge, edge )
	{
		SetName( "Square" );
	}

	~Square() {}
};

class Polyline : public Shape, public Named
{
public:
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

	Polyline( Point const & begin );

	~Polyline() { DecrementCount(); }
private:
	Container< Point > m_vertices;
	bool m_isClosed;

	bool VerticesContainPoint( Point const & p ) const;
};

class Polygon : public Shape, public Named
{
public:
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

	Polygon( Container< Point > const & vertices );

	~Polygon() { DecrementCount(); }
private:
	Container< Point > m_vertices;
	Container< LineSegment > m_edges;

	static void MoveLastItemToBegin( Container< Point > & points );
	static bool CircularShift( Container< Point > const & c1, Container< Point > const & c2 );
	static uint16_t GetRemainder( int a, uint16_t b );
	static LineSegment GetLineSegment( Container< Point > const & vertices, int index );
	static Point const & GetVertex( Container< Point > const & vertices, int index );
	Point const & GetVertex( int index ) const;
	static bool VerticesContainsEqualsPoints( Container< Point > const & vertices );
	static bool VerticesAreCollinear( Point const & p1, Point const & p2, Point const & p3 );
};



#endif // SHAPES_H
