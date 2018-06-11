#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <cstdint>
#include <string>

using std::cout;
using std::endl;



class Printable
{
public:
	virtual void PrintInfo() const = 0;

	virtual ~Printable() {}
};

class Named : public virtual Printable
{
public:
	std::string const & GetName() const { return m_name; }
	void SetName( std::string const & name ) { m_name = name; }

	virtual void PrintInfo() const override
	{
		cout << endl << "Name : " << m_name << endl ;
	}

	Named( std::string const & name )
		: m_name( name ) {}
	Named() {}

	virtual ~Named() {}
private:
	std::string m_name;
};



#endif // BASE_H
