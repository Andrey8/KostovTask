#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <string>



class Printable
{
public:
	virtual ~Printable() {}

	virtual void PrintInfo() const = 0;	
};

class Named : public virtual Printable
{
public:
	Named( std::string const & name )
		: m_name( name ) {}

	virtual ~Named() {}

	std::string const & GetName() const { return m_name; }
	void SetName( std::string const & name ) { m_name = name; }

	virtual void PrintInfo() const override
	{
		std::cout << std::endl << "Name : " << m_name << std::endl ;
	}
private:
	std::string m_name;
};

#endif // BASE_H
