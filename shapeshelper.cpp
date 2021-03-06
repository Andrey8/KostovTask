#include "shapeshelper.h"
#include "shapes.h"

#include <cmath>



// class ClosedInterval :

ShapesHelper::ClosedInterval::ClosedInterval( double l, double h )
{
	if ( l > h )
	{
		throw Exception( "ShapesHelper::ClosedInterval creation : invalid values." );
	}

	m_lowValue = l;
	m_highValue = h;
}

bool ShapesHelper::ClosedInterval::Contains( double value ) const
{
	return ( m_lowValue <= value && value <= m_highValue );
}



// class Angle :

ShapesHelper::Angle::Angle( double value, AngleMeasure measure )
{
	switch ( measure )
	{
	case AngleMeasure::Radians :
	{
		m_radians = value;

		break;
	}
	case AngleMeasure::Degrees :
	{
		m_radians = value * M_PI / 180;

		break;
	}
	}
}

bool ShapesHelper::Angle::IsInClosedInterval( double a1, double a2, AngleMeasure measure ) const
{
	switch ( measure )
	{
	case AngleMeasure::Radians :
	{
		return ClosedInterval( a1, a2 ).Contains( m_radians );
	}
	case AngleMeasure::Degrees :
	{
		return ClosedInterval( a1, a2 ).Contains( GetDegrees() );
	}
	}
}

double ShapesHelper::Angle::GetDegrees() const
{
	return m_radians * 180 / M_PI;
}



// class Vector :

ShapesHelper::Vector::Vector( double x, double y )
	: m_x( x ),
	  m_y( y )
{
	if ( x == 0 && y == 0 )
	{
		throw Exception( "ShapesHelper::Vector creation : null vector is impossible." );
	}
}

ShapesHelper::Vector::Vector( Point const & p1, Point const & p2 )
	: Vector( p2.X() - p1.X(), p2.Y() - p1.Y() )
{}

double ShapesHelper::Vector::GetNorm() const
{
	return sqrt( m_x * m_x + m_y * m_y );
}

ShapesHelper::Vector ShapesHelper::Vector::GetNormal( CircleDirection direction ) const
{
	switch ( direction )
	{
	case CircleDirection::Clockwise :
	{
		return Vector( m_y, -m_x );
	}
	case CircleDirection::CounterClockwise :
	{
		return Vector( -m_y, m_x );
	}
	}
}

double ShapesHelper::Vector::operator *( Vector const & other ) const
{
	return ( m_x * other.m_x + m_y * other.m_y );
}

ShapesHelper::Angle ShapesHelper::Vector::GetRelativeAngle( Vector const & fixed, CircleDirection direction ) const
{
	switch ( direction )
	{
	case CircleDirection::Clockwise :
	{
		double const scal1 = ( *this ) * fixed;
		double const scal2 = ( *this ) * fixed.GetNormal( CircleDirection::Clockwise );

		double const x = acos( scal1 / ( GetNorm() * fixed.GetNorm() ) );
		if ( scal1 >= 0 )
		{
			if ( scal2 >= 0 )
			{
				return Angle( x );
			}
			else
			{
				return Angle( 2 * M_PI - x );
			}
		}
		else
		{
			if ( scal2 >= 0 )
			{
				return Angle( x );
			}
			else
			{
				return Angle( 2 * M_PI - x );
			}
		}
	}
	case CircleDirection::CounterClockwise :
	{
		double const scal1 = ( *this ) * fixed;
		double const scal2 = ( *this ) * fixed.GetNormal( CircleDirection::CounterClockwise );

		double const x = acos( scal1 / ( GetNorm() * fixed.GetNorm() ) );
		if ( scal1 >= 0 )
		{
			if ( scal2 >= 0 )
			{
				return Angle( x );
			}
			else
			{
				return Angle( 2 * M_PI - x );
			}
		}
		else
		{
			if ( scal2 >= 0 )
			{
				return Angle( x );
			}
			else
			{
				return Angle( 2 * M_PI - x );
			}
		}
	}
	}
}



// class LineSegment :

ShapesHelper::LineSegment::LineSegment( Point const * p1, Point const * p2 )
	: m_p1( p1 ),
	  m_p2( p2 )
{
	if ( !p1 || !p2 )
	{
		throw Exception( "ShapesHelper::LineSegment creation : invalid point." );
	}

	if ( *p1 == *p2 )
	{
		throw Exception( "ShapesHelper::LineSegment creation : equal points." );
	}
}

ShapesHelper::LineSegment::LineSegment( double x1, double y1, double x2, double y2 )
	: LineSegment( new Point( x1, y1 ), new Point( x2, y2 ) )
{}

bool ShapesHelper::LineSegment::Intersects( LineSegment const & other ) const
{
	if ( IntersectsLineOf( other ) && other.IntersectsLineOf( *this ) )
	{
		return true;
	}

	return false;
}

bool ShapesHelper::LineSegment::IntersectsLineOf( LineSegment const & other ) const
{
	Point const & p1 = *other.m_p1;
	Point const & p2 = *other.m_p2;
	Point const & p3 = *m_p1;
	Point const & p4 = *m_p2;

	if ( p1 == p3 || p1 == p4 || p2 == p3 || p2 == p4 )
	{
		return true;
	}

	Vector const v0( p1, p2 );
	Vector const v1( p1, p3 );
	Vector const v2( p1, p4 );

	Angle const a1 = v1.GetRelativeAngle( v0 );
	Angle const a2 = v2.GetRelativeAngle( v0 );

	if ( ( a1.IsInClosedInterval( 0, M_PI ) && a2.IsInClosedInterval( 0, M_PI ) ) ||
		 ( a1.IsInClosedInterval( M_PI, 2 * M_PI ) && a2.IsInClosedInterval( M_PI, 2 * M_PI ) ) )
	{
		return false;
	}
	else
	{
		return true;
	}
}

double ShapesHelper::LineSegment::GetLength() const
{
	return GetDistance( *m_p1, *m_p2 );
}



double ShapesHelper::GetDistance( Point const & p1, Point const & p2 )
{
	return std::sqrt( ( p1.X() - p2.X() ) * ( p1.X() - p2.X() ) +
					  ( p1.Y() - p2.Y() ) * ( p1.Y() - p2.Y() ) );
}

void ShapesHelper::MoveLastItemToBegin( Container< Point > & points )
{
	if ( points.IsEmpty() )
	{
		throw Exception( "ShapesHelper::MoveLastItemToBegin : empty container." );
	}

	points.PushFront( points.GetLast() );
	points.RemoveLast();
}

bool ShapesHelper::IsCircularShift( Container< Point > const & c1, Container< Point > const & c2 )
{
	if ( c1.GetSize() != c2.GetSize() )
	{
		return false;
	}

	Container< Point > copy1 = c1;
	for ( uint16_t i = 0; i < c1.GetSize(); ++i )
	{
		MoveLastItemToBegin( copy1 );
		if ( copy1 == c2 )
		{
			return true;
		}
	}

	return false;
}

Container< Point > ShapesHelper::GetInvertedContainer( Container< Point > const & points )
{
	Container< Point > result;

	Container< Point > copy = points;
	while ( !copy.IsEmpty() )
	{
		result.PushBack( copy.GetLast() );
		copy.RemoveLast();
	}

	return result;
}



Shape const * ShapesHelper::GetShape( ShapeType type )
{
	int const m = 100;

	switch ( type )
	{
	case ShapeType::Point :
	{
		return ( new Point( rand() % m, rand() % m ) );
	}
	case ShapeType::Circle :
	{
		Point const center( rand() & m, rand() % m );

		return ( new Circle( center, rand() % 10 ) );
	}
	case ShapeType::Rect :
	{
		Point const center( rand() & m, rand() % m );

		return ( new Rect( center, rand() % 10, rand() % 10 ) );
	}
	case ShapeType::Square :
	{
		Point const center( rand() & m, rand() % m );

		return ( new Square( center, rand() % 10 ) );
	}
	case ShapeType::Polyline :
	{
		int const vcount = rand() % 7 + 1;
		Point const begin( rand() % m, rand() % m );
		Polyline * p = new Polyline( begin );
		for ( int i = 0; i < vcount - 1; ++i )
		{
			p->AddPoint( Point( rand() % m, rand() % m ) );
		}

		return p;
	}
	case ShapeType::Polygon :
	{
		int const vcount = rand() % 5 + 3;
		Container< Point > vertices;
		for ( int i = 0; i < vcount; ++i )
		{
			vertices.PushBack( Point( rand() % m, rand() % m ) );
		}

		return ( new Polygon( vertices ) );
	}
	}
}
