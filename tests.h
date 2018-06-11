#ifndef TESTS_H
#define TESTS_H

#include "container.h"

class Point;



namespace Tests
{
	void KostovTest();

	void TestContainer();
	void TestShapes();
	void TestShapesHelper();

	void SKIP();
	void SHOW_ExpressionValue( bool expression );
	void SHOW_IntContainer( Container< int > const & );
	void SHOW_PointContainer( Container< Point > const & );
}

#endif // TESTS_H
