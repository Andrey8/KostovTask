#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>



class Exception
{
public:
	Exception( std::string const & message )
		: m_message( message )
	{}

	std::string const & GetMessage() const { return m_message; }
private:
	std::string const m_message;
};

#endif // EXCEPTION_H
