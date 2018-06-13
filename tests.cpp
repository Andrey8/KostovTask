#include "tests.h"
#include "shapes.h"
#include "shapeshelper.h"

#include <iostream>
#include <string>
#include <ctime>

using std::cout;
using std::endl;
using namespace ShapesHelper;



void Tests::SKIP()
{
	cout << "\n\n\n" ;
}

void Tests::SHOW_ExpressionValue( bool expression )
{
	if ( expression )
	{
		cout << "True\n" ;
	}
	else
	{
		cout << "False\n" ;
	}
}

void Tests::SHOW_IntContainer( Container< int > const & c )
{
	if ( c.IsEmpty() )
	{
		cout << "Container is empty.\n" ;

		return;
	}

	for ( Container< int >::ConstIterator it = c.Begin(); it != c.End(); ++it )
	{
		cout << "\t" << *it ;
	}

	cout << endl;
}

void Tests::SHOW_PointContainer( Container< Point > const & points )
{
	if ( points.IsEmpty() )
	{
		cout << "Container is empty.\n" ;

		return;
	}

	for ( Iter it = points.Begin(); it != points.End(); ++it )
	{
		cout << "\t(" << ( *it ).X() << ", " << ( *it ).Y() << ")" ;
	}

	cout << endl ;
}



void Tests::TestContainer()
{
	cout << "CONTAINER TEST :\n" ;

	SKIP();

	// Creation
	cout << "Creation :\n" ;
	{
		Container< int > emptyCont;
		SHOW_IntContainer( emptyCont );
		SHOW_ExpressionValue( emptyCont.IsEmpty() );
		cout << "Size : " << emptyCont.GetSize() << endl ;

		cout << endl ;

		Container< int > numbers;
		numbers.PushBack( 3 );
		numbers.PushBack( 4 );
		numbers.PushBack( 5 );
		Container< int > copy = numbers;
		SHOW_IntContainer( numbers );
		SHOW_IntContainer( copy );
		SHOW_ExpressionValue( copy.IsEmpty() );
		cout << "Copy size : " << copy.GetSize() << endl ;

		Container< int > copy2 = emptyCont;
		SHOW_IntContainer( copy2 );

		cout << endl ;
	}

	SKIP();

	// operator=
	cout << "Operator= :\n" ;
	{
		Container< int > numbers1;
		numbers1.PushBack( 2 );
		numbers1.PushBack( 97 );
		numbers1.PushBack( 33 );
		Container< int > numbers2;
		numbers2.PushBack( 125 );
		numbers2.PushBack( 12 );
		SHOW_IntContainer( numbers1 );
		SHOW_IntContainer( numbers2 );
		numbers1 = numbers2;
		SHOW_IntContainer( numbers1 );
		SHOW_IntContainer( numbers2 );
	}

	SKIP();

	// PushFront
	cout << "PushFront :\n" ;
	{
		Container< int > numbers;
		numbers.PushFront( 7 );
		numbers.PushFront( 11 );
		numbers.PushFront( 105 );
		SHOW_IntContainer( numbers );
		cout << "Size : " << numbers.GetSize() << endl ;
		numbers.PushFront( 42 );
		SHOW_IntContainer( numbers );
		cout << "Size : " << numbers.GetSize() << endl ;
	}

	SKIP();

	// PushBack
	cout << "PushBack :\n" ;
	{
		Container< int > numbers;
		numbers.PushBack( 11 );
		numbers.PushBack( 24 );
		numbers.PushBack( 200 );
		SHOW_IntContainer( numbers );
		cout << "Size : " << numbers.GetSize() << endl ;
		numbers.PushBack( 0 );
		SHOW_IntContainer( numbers );
		cout << "Size : " << numbers.GetSize() << endl ;
	}

	SKIP();
	// RemoveFirst
	cout << "RemoveFirst :\n " ;
	{
		Container< int > numbers;
		numbers.PushFront( 15 );
		numbers.PushBack( 20 );
		numbers.PushFront( 10 );
		numbers.PushBack( 25 );
		numbers.PushFront( 5 );
		SHOW_IntContainer( numbers );
		cout << "Size : " << numbers.GetSize() << endl ;
		numbers.RemoveFirst();
		SHOW_IntContainer( numbers );
		cout << "Size : " << numbers.GetSize() << endl ;
		numbers.RemoveFirst();
		SHOW_IntContainer( numbers );
		cout << "Size : " << numbers.GetSize() << endl ;

		cout << endl ;

		try
		{
			Container< int > emptyCont;
			emptyCont.RemoveFirst();
		}
		catch ( Exception & exc )
		{
			exc.ShowMessage();
		}
	}

	SKIP();

	// RemoveLast
	cout << "RemoveLast :\n" ;
	{
		Container< int > numbers;
		numbers.PushFront( 50 );
		numbers.PushBack( 51 );
		numbers.PushBack( 52 );
		numbers.PushBack( 53 );
		numbers.PushFront( 49 );
		SHOW_IntContainer( numbers );
		cout << "Size : " << numbers.GetSize() << endl ;
		numbers.RemoveLast();
		SHOW_IntContainer( numbers );
		cout << "Size : " << numbers.GetSize() << endl ;
		numbers.RemoveLast();
		SHOW_IntContainer( numbers );
		cout << "Size : " << numbers.GetSize() << endl ;

		cout << endl ;

		try
		{
			Container< int > emptyCont;
			emptyCont.RemoveLast();
		}
		catch ( Exception & exc )
		{
			exc.ShowMessage();
		}
	}

	SKIP();
	// Clear
	cout << "Clear :\n" ;
	{
		Container< int > numbers;
		numbers.PushBack( 2 );
		numbers.PushBack( 4 );
		numbers.PushBack( 119 );
		numbers.PushBack( 37 );
		numbers.PushBack( 11 );
		SHOW_IntContainer( numbers );
		cout << "Size : " << numbers.GetSize() << endl ;
		numbers.Clear();
		SHOW_IntContainer( numbers );
	}

	SKIP();

	// GetFirst
	cout << "GetFirst :\n" ;
	{
		Container< int > numbers;
		numbers.PushBack( 31 );
		numbers.PushBack( 84 );
		numbers.PushFront( 1 );
		SHOW_IntContainer( numbers );
		cout << "First : " << numbers.GetFirst() << endl ;
		numbers.RemoveFirst();
		SHOW_IntContainer( numbers );
		cout << "First : " << numbers.GetFirst() << endl ;

		try
		{
			Container< int > emptyCont;
			cout << "First of empty container : " << emptyCont.GetFirst() << endl ;
		}
		catch ( Exception & exc )
		{
			exc.ShowMessage();
		}
	}

	SKIP();

	// GetLast
	cout << "GetLast :\n" ;
	{
		Container< int > numbers;
		numbers.PushBack( 17 );
		numbers.PushBack( 23 );
		numbers.PushBack( 39 );
		SHOW_IntContainer( numbers );
		cout << "Last : " << numbers.GetLast() << endl ;
		numbers.RemoveLast();
		SHOW_IntContainer( numbers );
		cout << "Last : " << numbers.GetLast() << endl ;

		try
		{
			Container< int > emptyCont;
			cout << "Last of empty container : " << emptyCont.GetLast() << endl ;
		}
		catch ( Exception & exc )
		{
			exc.ShowMessage();
		}
	}

	SKIP();

	// GetSize
	cout << "GetSize :\n" ;
	{
		Container< int > numbers;
		SHOW_IntContainer( numbers );
		cout << "Size : " << numbers.GetSize() << endl ;
		numbers.PushBack( 4 );
		numbers.PushBack( 1007 );
		SHOW_IntContainer( numbers );
		cout << "Size : " << numbers.GetSize() << endl ;
		numbers.PushBack( 92 );
		SHOW_IntContainer( numbers );
		cout << "Size : " << numbers.GetSize() << endl ;
		numbers.RemoveFirst();
		SHOW_IntContainer( numbers );
		cout << "Size : " << numbers.GetSize() << endl ;
		numbers.Clear();
		SHOW_IntContainer( numbers );
		cout << "Size : " << numbers.GetSize() << endl ;
	}

	SKIP();

	// IsEmpty
	cout << "IsEmpty :\n" ;
	{
		Container< int > numbers;
		SHOW_IntContainer( numbers );
		SHOW_ExpressionValue( numbers.IsEmpty() );
		numbers.PushBack( 3 );
		numbers.PushBack( 5 );
		numbers.PushBack( 7 );
		SHOW_IntContainer( numbers );
		SHOW_ExpressionValue( numbers.IsEmpty() );
		numbers.RemoveFirst();
		SHOW_IntContainer( numbers );
		SHOW_ExpressionValue( numbers.IsEmpty() );
	}

	SKIP();

	// operator ==
	cout << "operator == :\n" ;
	{
		Container< int > numbers1;
		numbers1.PushBack( 2 );
		numbers1.PushBack( 3 );
		numbers1.PushBack( 8 );
		numbers1.PushBack( 14 );

		Container< int > numbers2;
		numbers2.PushBack( 2 );
		numbers2.PushBack( 3 );
		numbers2.PushBack( 8 );
		numbers2.PushBack( 14 );

		Container< int > numbers3;
		numbers3.PushBack( 2 );
		numbers3.PushBack( 3 );
		numbers3.PushBack( 14 );
		numbers3.PushBack( 8 );

		SHOW_IntContainer( numbers1 );
		SHOW_IntContainer( numbers2 );
		SHOW_IntContainer( numbers3 );
		SHOW_ExpressionValue( numbers1 == numbers2 );
		SHOW_ExpressionValue( numbers1 == numbers3 );
	}

	SKIP();

	// Test with empty container
	cout << "Test with empty container :\n" ;
	{
		Container< int > empty;
		Container< int > copy = empty;
		SHOW_IntContainer( empty );
		SHOW_IntContainer( copy );
		SHOW_ExpressionValue( empty == copy );
		empty.Clear();
		SHOW_IntContainer( empty );
	}
}

void Tests::TestShapes()
{
	cout << "SHAPES TEST :\n" ;

	SKIP();

	cout << "All shapes count : " << Shape::GetCount() << endl << endl ;

	SKIP();

	// Point
	cout << "Point test :\n" ;
	{
		Point p( 2, 5 );

		SHOW_ExpressionValue( p.IsInsideRect( Rect( Point( 1, 7 ), Point( 4, 3 ) ) ) );
		SHOW_ExpressionValue( p.IsInsideRect( Rect( Point( 1, 4 ), Point( 3, 2 ) ) ) );

		cout << p;

		cout << "All shapes count : " << Shape::GetCount() << endl << endl ;
	}

	SKIP();

	// Circle
	cout << "Circle test :\n" ;
	{
		Circle c( Point( 3, 3 ), 2 );

		cout << c ;

		cout << "All shapes count : " << Shape::GetCount() << endl << endl ;
	}

	SKIP();

	// Rect
	cout << "Rect test :\n" ;
	{
		Rect r( Point( 4, 3 ), 6, 4 );
		cout << r ;
		SHOW_ExpressionValue( r.Contains( Point( 6, 4 ) ) );

		cout << "All shapes count : " << Shape::GetCount() << endl << endl ;

		Rect r2( Point( 2, 4 ), Point( 4, 1 ) );
		cout << r2 ;
		cout << "Top right corner : " << r2.GetTopRight() << endl ;

		cout << "All shapes count : " << Shape::GetCount() << endl << endl ;

		try
		{
			Rect r3( Point( 1, 1 ), Point( 5, 5 ) );
		}
		catch( Exception & exc )
		{
			exc.ShowMessage();
		}
	}

	SKIP();

	// Square
	cout << "Square test :\n" ;
	{
		Square sq( Point( 6, 5 ), 4 );
		cout << sq ;

		cout << "All shapes count : " << Shape::GetCount() << endl << endl ;
	}

	SKIP();

	// Polyline
	cout << "Polyline test :\n" ;
	{
		Polyline pol( Point( 2, 2 ) );
		pol.AddPoint( Point( 6, 5 ) );
		pol.AddPoint( Point( 18, 10 ) );
		pol.AddPoint( Point( 12, 2 ) );
		pol.AddPoint( Point( 12, 4 ) );
		cout << pol ;
		SHOW_ExpressionValue( pol.IsClosed() );
		pol.AddPoint( Point( 2, 2 ) );
		cout << pol ;
		SHOW_ExpressionValue( pol.IsClosed() );
		try
		{
			pol.AddPoint( Point( 0, 0 ) );
		}
		catch( Exception & exc )
		{
			exc.ShowMessage();
		}

		cout << "All shapes count : " << Shape::GetCount() << endl << endl ;
	}

	SKIP();

	// Polygon
	cout << "Polygon test :\n" ;
	{
		Container< Point > goodVertices1;
		goodVertices1.PushBack( Point( 1, 5 ) );
		goodVertices1.PushBack( Point( 5, 7 ) );
		goodVertices1.PushBack( Point( 10, 4 ) );
		goodVertices1.PushBack( Point( 5, 4 ) );
		goodVertices1.PushBack( Point( 4, 1 ) );
		goodVertices1.PushBack( Point( 2, 2 ) );
		try
		{
			Polygon pol1( goodVertices1 );
			cout << pol1 ;

			Container< Point > vertices;
			vertices.PushBack( Point( 5, 4 ) );
			vertices.PushBack( Point( 4, 1 ) );
			vertices.PushBack( Point( 2, 2 ) );
			vertices.PushBack( Point( 1, 5 ) );
			vertices.PushBack( Point( 5, 7 ) );
			vertices.PushBack( Point( 10, 4 ) );
			Polygon copy( vertices );
			SHOW_ExpressionValue( pol1 == copy );
		}
		catch ( Exception & exc )
		{
			exc.ShowMessage();
		}

		Container< Point > goodVertices2;
		goodVertices2.PushBack( Point( 9, 4 ) );
		goodVertices2.PushBack( Point( 6, 6 ) );
		goodVertices2.PushBack( Point( 2, 5 ) );
		goodVertices2.PushBack( Point( 1, 1 ) );
		goodVertices2.PushBack( Point( 6, 0 ) );
		try
		{
			Polygon pol2( goodVertices2 );
			cout << pol2 ;
		}
		catch ( Exception & exc )
		{
			exc.ShowMessage();
		}

		Container< Point > goodVertices3;
		goodVertices3.PushBack( Point( 0, 0 ) );
		goodVertices3.PushBack( Point( 4, 5 ) );
		goodVertices3.PushBack( Point( 7, 2 ) );
		Polygon triangle( goodVertices3 );
		cout << triangle ;

		Container< Point > badVertices1;
		badVertices1.PushBack( Point( 4, 1 ) );
		badVertices1.PushBack( Point( 1, 3 ) );
		badVertices1.PushBack( Point( 2, 4 ) );
		badVertices1.PushBack( Point( 4, 3 ) );
		badVertices1.PushBack( Point( 1, 1 ) );
		try
		{
			Polygon pol3( badVertices1 );
			cout << pol3 ;
		}
		catch ( Exception & exc )
		{
			exc.ShowMessage();
		}

		Container< Point > badVertices2;
		badVertices2.PushBack( Point( 6, 1 ) );
		badVertices2.PushBack( Point( 7, 4 ) );
		badVertices2.PushBack( Point( 11, 3 ) );
		badVertices2.PushBack( Point( 11, 0 ) );
		badVertices2.PushBack( Point( 9, 1 ) );
		badVertices2.PushBack( Point( 7, 2 ) );
		try
		{
			Polygon pol4( badVertices2 );
			cout << pol4;
		}
		catch ( Exception & exc )
		{
			exc.ShowMessage();
		}

		Container< Point > badVertices3;
		badVertices3.PushBack( Point( 1, 5 ) );
		badVertices3.PushBack( Point( 2, 7 ) );
		badVertices3.PushBack( Point( 4, 6 ) );
		badVertices3.PushBack( Point( 5, 5 ) );
		badVertices3.PushBack( Point( 2, 7 ) );
		badVertices3.PushBack( Point( 3, 4 ) );
		try
		{
			Polygon pol5( badVertices3 );
			cout << pol5 ;
		}
		catch ( Exception & exc )
		{
			exc.ShowMessage();
		}

		Container< Point > q1;
		q1.PushBack( Point( 1, 2 ) );
		q1.PushBack( Point( 4, 4 ) );
		q1.PushBack( Point( 6, 2 ) );
		q1.PushBack( Point( 3, 1 ) );
		try
		{
			Polygon quadr1( q1 );
			cout << quadr1 ;
		}
		catch ( Exception &exc )
		{
			exc.ShowMessage();
		}

		Container< Point > q2;
		q2.PushBack( Point( 3, 2 ) );
		q2.PushBack( Point( 1, 0 ) );
		q2.PushBack( Point( 4, 6 ) );
		q2.PushBack( Point( 7, 3 ) );
		try
		{
			Polygon quadr2( q2 );
			cout << quadr2 ;
		}
		catch ( Exception & exc )
		{
			exc.ShowMessage();
		}

		Container< Point > badQ1;
		badQ1.PushBack( Point( 1, 1 ) );
		badQ1.PushBack( Point( 6, 4 ) );
		badQ1.PushBack( Point( 3, 0 ) );
		badQ1.PushBack( Point( 2, 5 ) );
		try
		{
			Polygon badQuadr1( badQ1 );
			cout << badQuadr1 ;
		}
		catch ( Exception & exc )
		{
			exc.ShowMessage();
		}

		Container< Point > manyPoints;
		manyPoints.PushBack( Point( 6, 10 ) );
		manyPoints.PushBack( Point( 2, 8 ) );
		manyPoints.PushBack( Point( 1, 5 ) );
		manyPoints.PushBack( Point( 3, 1 ) );
		manyPoints.PushBack( Point( 9, 2 ) );
		//manyPoints.PushBack( Point( 11, 5 ) );
		manyPoints.PushBack( Point( 16, 4 ) );
		manyPoints.PushBack( Point( 18, 6 ) );
		manyPoints.PushBack( Point( 17, 9 ) );
		manyPoints.PushBack( Point( 12, 11 ) );
		try
		{
			Polygon pol6( manyPoints );
			cout << pol6;
		}
		catch ( Exception & exc )
		{
			exc.ShowMessage();
		}

		cout << "All shapes count : " << Shape::GetCount() << endl << endl ;
	}
}

void Tests::TestShapesHelper()
{
	cout << "SHAPESHELPER TEST :\n" ;

	SKIP();

	// Vector
	cout << "Vector test :\n\n" ;
	{
		cout << "Relative angles equal : "
			 << Vector( Point( 2, 4 ), Point( 2, 2 ) ).GetRelativeAngle( Vector( Point( 3, 1 ), Point( 5, 3 ) ), CircleDirection::Clockwise ).GetDegrees()
			 << ", "
			 << Vector( Point( 4, 1 ), Point( 7, 2 ) ).GetRelativeAngle( Vector( Point( 0, 5 ), Point( 2 , -1 ) ) ).GetDegrees()
			 << endl ;
	}

	SKIP();

	// LineSegment
	cout << "LineSegment test :\n\n" ;
	{
		try
		{
			SHOW_ExpressionValue( LineSegment( 1, 1, 5, 4 ).Intersects( LineSegment( 4, 2, 2, 5 ) ) );
			SHOW_ExpressionValue( LineSegment( 2, 5, 1, 1 ).Intersects( LineSegment( 4, 2, 5, 4 ) ) );
			SHOW_ExpressionValue( LineSegment( 1, 1, 5, 4 ).Intersects( LineSegment( 5, 4, 4, 2 ) ) );
		}
		catch ( Exception & exc )
		{
			exc.ShowMessage();
		}
	}

	SKIP();

	// GetInvertedContainer
	cout << "Function GetInvertedContainer test :\n\n" ;
	{
		try
		{
			Container< Point > points;
			points.PushBack( Point( 1, 2 ) );
			points.PushBack( Point( 3, 4 ) );
			points.PushBack( Point( 5, 6 ) );
			points.PushBack( Point( 7, 8 ) );
			points.PushBack( Point( 9, 10 ) );
			SHOW_PointContainer( points );
			SHOW_PointContainer( GetInvertedContainer( points ) );
		}
		catch ( Exception & exc )
		{
			exc.ShowMessage();
		}
	}
}



void Tests::KostovTest()
{
	srand( time( 0 ) );

	cout << "KOSTOV TEST :\n\n" ;	

	int shapesCount = 20;
	Container< Shape const * > shapes;

	while ( shapes.GetSize() < shapesCount )
	{
		try
		{
			ShapeType const type = ShapeType ( rand() % 6 );

			shapes.PushBack( GetShape( type ) );
		}
		catch ( Exception & exc )
		{
			exc.ShowMessage();
		}
	}

	cout << "\nAll shapes count : " << Shape::GetCount() << endl << endl ;

	for ( Container< Shape const * >::ConstIterator it = shapes.Begin(); it != shapes.End(); ++it )
	{
		( *it )->PrintInfo();
	}

	for ( Container< Shape const * >::ConstIterator it = shapes.Begin(); it != shapes.End(); ++it )
	{
		delete ( *it );
	}

	cout << "All shapes count after destroying : " << Shape::GetCount() << endl ;
}





















