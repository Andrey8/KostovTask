#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>

using std::cout;
using std::endl;



class Exception
{
public:
	virtual void ShowMessage() const
	{
		cout << endl << m_message << endl << endl ;
	}

	Exception( std::string const & message ) { m_message = message; }
	Exception() {}
private:
	std::string m_message;
};

#endif // EXCEPTION_H
