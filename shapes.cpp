#include "shapes.h"
#include "shapeshelper.h"

using Vector = ShapesHelper::Vector;
using CircleDirection = ShapesHelper::CircleDirection;



uint16_t Shape::sm_count = 0;



// class Point :

Point::Point( Point const & other )
	: Named( "Point" ),
	  m_x( other.m_x ),
	  m_y( other.m_y )
{}

std::ostream & operator<<( std::ostream & os, Point const & point )
{
	os << std::endl;

	os << point.GetName() << " :\n"
	   << "\tcoordinates : ("
	   << point.m_x << ", " << point.m_y << ")\n";

	os << std::endl;

	return os;
}

void Point::PrintInfo() const
{
	std::cout << *this ;
}

bool Point::IsInsideRect( Rect const & rect ) const
{
	return rect.Contains( *this );
}

bool Point::operator==( Point const & other ) const
{
	if ( X() == other.X() && Y() == other.Y() )
	{
		return true;
	}
	else
	{
		return false;
	}
}



// class Circle :

Circle::Circle( Point const & center, double radius )
	: Named( "Circle" ),
	  m_center( center ),
	  m_radius( radius )
{
	if ( radius <= 0 )
	{
		throw Exception( "Circle creation : radius = 0 is impossible." );
	}
}

Circle::Circle( Circle const & other )
	: Named( "Circle" ),
	  m_center( other.m_center ),
	  m_radius( other.m_radius )
{}

std::ostream & operator<<( std::ostream & os, Circle const & circle )
{
	os << std::endl;

	os << circle.GetName() << " :\n"
	   << "\tcenter : "
	   << "O(" << circle.GetCenter().X() << ", " << circle.GetCenter().Y() << ")\n"
	   << "\tradius : " << circle.GetRadius() << std::endl
	   << "\tarea : " << circle.GetArea() << std::endl;

	os << std::endl;

	return os;
}

void Circle::PrintInfo() const
{
	std::cout << *this;
}

bool Circle::operator==( Circle const & other ) const
{
	if ( m_center == other.GetCenter() && m_radius == other.GetRadius() )
	{
		return true;
	}
	else
	{
		return false;
	}
}



// class Rect :

std::ostream & operator<<( std::ostream & os, Rect const & rect )
{
	os << std::endl;

	os << rect.GetName() << " :\n"
	   << "\tvertices :\n"
	   << "\t\tA(" << rect.GetTopLeftCorner().X() << ", " << rect.GetTopLeftCorner().Y() << ")\n"
	   << "\t\tB(" << rect.GetTopRightCorner().X() << ", " << rect.GetTopRightCorner().Y() << ")\n"
	   << "\t\tC(" << rect.GetBottomRightCorner().X() << ", " << rect.GetBottomRightCorner().Y() << ")\n"
	   << "\t\tD(" << rect.GetBottomLeftCorner().X() << ", " << rect.GetBottomLeftCorner().Y() << ")\n"
	   << "\twidth : " << rect.GetWidth() << std::endl
	   << "\theight :" << rect.GetHeight() << std::endl
	   << "\tarea : " << rect.GetArea() << std::endl;
	if ( rect.IsSquare() )
	{
		std::cout << "\tIt is square.\n" ;
	}

	os << std::endl;

	return os;
}

Rect::Rect( Point const & topLeft, Point const & bottomRight )
	: Named( "Rect" ),
	  m_center( Point( ( topLeft.X() + bottomRight.X() ) / 2, ( topLeft.Y() + bottomRight.Y() ) / 2 ) ),
	  m_width( bottomRight.X() - topLeft.X() ),
	  m_height( topLeft.Y() - bottomRight.Y() )
{
	if ( topLeft.X() >= bottomRight.X() &&
		 topLeft.Y() <= bottomRight.Y() )
	{
		throw Exception( "Rect creation : no matching in top left and bottom right corners." );
	}
}

Rect::Rect( Point const & center, double width, double height )
	: Named( "Rect" ),
	  m_center( center ),
	  m_width( width ),
	  m_height( height )
{
	if ( width <= 0 || height <= 0 )
	{
		throw Exception( "Rect creation : width = 0 or height = 0 is impossible." );
	}
}

Rect::Rect( Rect const & other )
	: Named( "Rect" ),
	  m_center( other.m_center ),
	  m_width( other.m_width ),
	  m_height( other.m_height )
{}

Point Rect::GetBottomLeftCorner() const
{
	return Point( m_center.X() - m_width / 2, m_center.Y() - m_height / 2 );
}

Point Rect::GetTopRightCorner() const
{
	return Point( m_center.X() + m_width / 2, m_center.Y() + m_height / 2 );
}

Point Rect::GetBottomRightCorner() const
{
	return Point( m_center.X() + m_width / 2, m_center.Y() - m_height / 2 );
}

Point Rect::GetTopLeftCorner() const
{
	return Point( m_center.X() - m_width / 2, m_center.Y() + m_height / 2 );
}

void Rect::PrintInfo() const
{
	std::cout << *this;
}

bool Rect::Contains( Point const & point ) const
{
	if ( point.X() >= GetTopLeftCorner().X() && point.X() <= GetTopRightCorner().X() &&
		 point.Y() >= GetBottomLeftCorner().Y() && point.Y() <= GetTopLeftCorner().Y() )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Rect::IsSquare() const
{
	return ( m_width == m_height );
}

bool Rect::operator==( Rect const & other ) const
{
	if ( m_center == other.GetCenter() && m_width == other.GetWidth() && m_height == other.GetHeight() )
	{
		return true;
	}
	else
	{
		return false;
	}
}



// class Square :

std::ostream & operator<<( std::ostream & os, Square const & square )
{
	os << std::endl ;
	os << square.GetName() << " :\n"
	   << "\tvertices :\n"
	   << "\t\tA(" << square.GetTopLeftCorner().X() << ", " << square.GetTopLeftCorner().Y() << ")\n"
	   << "\t\tB(" << square.GetTopRightCorner().X() << ", " << square.GetTopRightCorner().Y() << ")\n"
	   << "\t\tC(" << square.GetBottomRightCorner().X() << ", " << square.GetBottomRightCorner().Y() << ")\n"
	   << "\t\tD(" << square.GetBottomLeftCorner().X() << ", " << square.GetBottomLeftCorner().Y() << ")\n"
	   << "\tedge : " << square.GetEdge() << std::endl
	   << "\tarea : " << square.GetArea() << std::endl ;
	os << std::endl;

	return os;
}

void Square::PrintInfo() const
{
	std::cout << *this ;
}



// class Polyline :

Polyline::Polyline( Point const & begin )
	: Named( "Polyline" ),
	  m_isClosed( false )
{
	m_vertices.PushBack( begin );
}

bool Polyline::IsClosed() const
{
	if ( m_vertices.GetSize() >= 3 && m_isClosed )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Polyline::operator ==( Polyline const & other ) const
{
	if ( IsClosed() && other.IsClosed() )
	{
		return ( ShapesHelper::IsCircularShift( m_vertices, other.m_vertices ) || ShapesHelper::IsCircularShift( ShapesHelper::GetInvertedContainer( m_vertices ), other.m_vertices ) );
	}
	else if ( !IsClosed() && !other.IsClosed() )
	{
		return ( m_vertices == other.m_vertices || m_vertices == ShapesHelper::GetInvertedContainer( other.m_vertices ) );
	}
	else
	{
		return false;
	}
}

std::ostream & operator<<( std::ostream & os, Polyline const & pol )
{
	std::string const name = pol.GetName();

	os << std::endl;

	if ( pol.m_vertices.GetSize() == 1 )
	{
		Point const & v = pol.m_vertices.GetFirst();

		os << name << " :\n"
		   << "\tIt has only one vertex : "
		   << "(" << v.X() << ", " << v.Y() << ")" << std::endl ;

		return os;
	}

	os << name << " :\n"
	   << "\tvertices count : " << pol.GetVerticesCount() << std::endl
	   << "\tvertices :\n" ;
	for ( Container< Point >::ConstIterator it = pol.m_vertices.Begin(); it != pol.m_vertices.End(); ++it )
	{		
		os << "\t\t(" << ( *it ).X() << ", " << ( *it ).Y() << ")" ;

		if ( it == pol.m_vertices.Begin() )
		{
			os << " - Begin" ;
		}

		if ( it + 1 == pol.m_vertices.End() )
		{
			os << " - End" ;
		}

		os << std::endl ;
	}
	os << "\tlength : " << pol.GetLength() << std::endl ;
	if ( pol.IsClosed() )
	{
		std::cout << "\tPolyline is closed.\n" ;
	}
	else
	{
		std::cout << "\tPolyline is not closed.\n" ;
	}

	os << std::endl;

	return os;
}

void Polyline::AddPoint( Point const & p )
{
	if ( IsClosed() )
	{
		throw Exception( "Polyline is already closed." );
	}

	if ( VerticesContainPoint( p ) )
	{
		if ( p == m_vertices.GetFirst() )
		{
			m_isClosed = true;

			return;
		}
		else
		{
			throw Exception( "Polyline point adding : it already contains this point." );
		}
	}
	else
	{
		m_vertices.PushBack( p );
	}
}

void Polyline::Close()
{
	if ( m_vertices.GetSize() >= 3 )
	{
		m_isClosed = true;

		return;
	}
	else
	{
		throw Exception( "Polyline closing : it has too few vertices." );
	}
}

Container< Point > Polyline::GetVertices() const
{
	return m_vertices;
}

double Polyline::GetLength() const
{
	if ( m_vertices.GetSize() == 1 )
	{
		return 0;
	}

	double length = 0;
	Container< Point >::ConstIterator cur = m_vertices.Begin();
	Container< Point >::ConstIterator next = m_vertices.Begin();
	++next;
	while ( next != m_vertices.End() )
	{
		length += ShapesHelper::GetDistance( *cur, *next );

		++cur;
		++next;
	}

	return length;
}

void Polyline::PrintInfo() const
{
	std::cout << *this;
}

Point const & Polyline::GetBegin() const
{
	return m_vertices.GetFirst();
}

Point const & Polyline::GetEnd() const
{
	return m_vertices.GetLast();
}

uint16_t Polyline::GetVerticesCount() const
{
	return m_vertices.GetSize();
}

bool Polyline::VerticesContainPoint( Point const & p ) const
{
	for ( Container< Point >::ConstIterator it = m_vertices.Begin(); it != m_vertices.End(); ++it )
	{
		if ( *it == p )
		{
			return true;
		}
	}

	return false;
}



// class Polygon :

Polygon::Polygon( Container< Point > const & vertices )
	: Named( "Polygon" )
{
	uint16_t const n = vertices.GetSize();

	if ( vertices.GetSize() < 3 )
	{
		throw Exception( "Vertices are too few for polygon creation." );
	}

	if ( VerticesContainsEqualsPoints( vertices ) )
	{
		throw Exception( "Polygon creation : there are equal points in vertices." );
	}

	for ( int s = 2; s <= n / 2; ++s )
	{
		for ( int i = 0; i < n; ++i )
		{
			if ( GetLineSegment( vertices, i ).Intersects( GetLineSegment( vertices, i + s ) ) )
			{
				throw Exception( "Polygon creation : there is selfintersection." );
			}
		}
	}

	for ( uint16_t i = 0; i < vertices.GetSize(); ++i )
	{
		if ( VerticesAreCollinear( GetVertex( vertices, i - 1 ),
								   GetVertex( vertices, i ),
								   GetVertex( vertices, i + 1 ) ) )
		{
			throw Exception( "Polygon creation : three consecutive vertices are collinear." );
		}
	}

	m_vertices = vertices;
	for ( Container< Point >::ConstIterator i = m_vertices.Begin(); i + 1 != m_vertices.End(); ++i )
	{
		m_edges.PushBack( LineSegment( i.GetPointer(), ( i + 1 ).GetPointer() ) );
	}
	m_edges.PushBack( LineSegment( &m_vertices.GetFirst(), &m_vertices.GetLast() ) );
}

double Polygon::GetPerimeter() const
{
	double p = 0;
	for ( Container< LineSegment >::ConstIterator e = m_edges.Begin(); e != m_edges.End(); ++e )
	{
		p += ( *e ).GetLength();
	}

	return p;
}

bool Polygon::IsConvex() const
{
	uint16_t const n = m_vertices.GetSize();

	if ( n == 3 )
	{
		return true;
	}

	bool const b = Vector( GetVertex( 1 ), GetVertex( 2 ) ).GetNormal( CircleDirection::CounterClockwise ) *
				   Vector( GetVertex( 1 ), GetVertex( n ) ) > 0;
	for ( int i = 2; i <= n; ++i )
	{
		if ( b != ( Vector( GetVertex( i ), GetVertex( i + 1 ) ).GetNormal( CircleDirection::CounterClockwise ) *
					Vector( GetVertex( i ), GetVertex( i - 1 ) ) > 0 ) )
		{
			return false;
		}
	}

	return true;
}

bool Polygon::IsTriangle() const
{
	return ( m_vertices.GetSize() == 3 );
}

bool Polygon::operator ==( Polygon const & other ) const
{
	return ( ShapesHelper::IsCircularShift( m_vertices, other.m_vertices ) || ShapesHelper::IsCircularShift( ShapesHelper::GetInvertedContainer( m_vertices ), other.m_vertices ) );
}

uint16_t Polygon::GetRemainder( int a, uint16_t b )
{
	int r = a % b;

	if ( r < 0 )
	{
		return ( b + r );
	}

	return r;
}

LineSegment Polygon::GetLineSegment( Container< Point > const & vertices, int index )
{
	return LineSegment( &GetVertex( vertices, index ), &GetVertex( vertices, index + 1 ) );
}

Point const & Polygon::GetVertex( Container< Point > const & vertices, int index )
{
	int r = GetRemainder( index, vertices.GetSize() );

	return *( vertices.Begin() + r );
}

Point const & Polygon::GetVertex( int index ) const
{
	return GetVertex( m_vertices, index );
}

bool Polygon::VerticesContainsEqualsPoints( Container< Point > const & vertices )
{
	for ( Container< Point >::ConstIterator it1 = vertices.Begin(); it1 != vertices.End(); ++it1 )
	{
		for ( Container< Point >::ConstIterator it2 = it1 + 1; it2 != vertices.End(); ++it2 )
		{
			if ( *it1 == *it2 )
			{
				return true;
			}
		}
	}

	return false;
}

bool Polygon::VerticesAreCollinear( Point const & p1, Point const & p2, Point const & p3 )
{
	if ( Vector( p1, p2 ).GetNormal( CircleDirection::Clockwise ) * Vector( p1, p3 ) == 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Polygon::PrintInfo() const
{
	std::cout << *this;
}

std::ostream & operator<<( std::ostream & os, Polygon const & pol )
{
	os << std::endl;

	std::string const name = pol.GetName();

	os << name << " :\n"
	   << "\tvertices count : " << pol.GetVerticesCount() << std::endl
	   << "\tvertices ( in order ):\n" ;
	for ( Container< Point >::ConstIterator it = pol.m_vertices.Begin(); it != pol.m_vertices.End(); ++it )
	{
		os << "\t\t(" << ( *it ).X() << ", " << ( *it ).Y() << ")\n" ;
	}
	os << "\tperimeter : " << pol.GetPerimeter() << std::endl ;
	if ( pol.IsConvex() )
	{
		if ( pol.IsTriangle() )
		{
			std::cout << "\tPolygon is triangle.\n" ;
		}
		else
		{
			std::cout << "\tPolygon is convex.\n" ;
		}
	}
	else
	{
		std::cout << "\tPolygon is not convex.\n" ;
	}

	os << std::endl;

	return os;
}
