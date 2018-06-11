#ifndef CONTAINER_H
#define CONTAINER_H

#include <cstdint>

#include "exception.h"



template < typename T > class Container
{
private:
	struct Node
	{
		Node( T const & data )
			: m_data( data ),
			  m_prev( nullptr ),
			  m_next( nullptr )
		{}

		T m_data;
		Node * m_prev;
		Node * m_next;
	};
public:
	class ConstIterator
	{
	public:
		T const & operator*() const;
		ConstIterator const & operator++();
		ConstIterator const operator+( uint16_t i ) const;
		bool operator==( ConstIterator const & other ) const;
		bool operator!=( ConstIterator const & other ) const;
		T const * GetPointer() const;

		ConstIterator( Node * node ) : m_node( node ) {}
		ConstIterator();
	private:
		Node * m_node;
	};

	void PushFront( T const & );
	void PushBack( T const & );
	void RemoveFirst();
	void RemoveLast();

	// getters
	T const & GetFirst() const;
	T const & GetLast() const;
	uint16_t GetSize() const;
	ConstIterator Begin() const;
	ConstIterator End() const;

	bool IsEmpty() const;
	bool operator==( Container< T > const & other ) const;
	bool operator!=( Container< T > const & other ) const;

	void Clear();

	Container & operator=( Container const & );

	Container( Container const & );
	Container();

	~Container();
private:
	Node * m_begin;
	Node * m_end;
	uint16_t m_size;
};



template < typename T > Container< T >::Container()
	: m_begin( nullptr ),
	  m_end( nullptr ),
	  m_size( 0 )
{}

template < typename T > Container< T >::Container( Container< T > const & other )
	: m_begin( nullptr ),
	  m_end( nullptr ),
	  m_size( 0 )
{
	bool const otherIsEmpty = ( other.m_size == 0 );

	Node * cur1 = nullptr;
	if ( !otherIsEmpty )
	{
		cur1 = new Node( other.m_begin->m_data );

		m_begin = cur1;
	}
	else
	{
		return;
	}

	Node * cur2 = other.m_begin->m_next;
	Node * prev = m_begin;
	while ( cur2 )
	{
		cur1 = new Node( cur2->m_data );

		prev->m_next = cur1;
		cur1->m_prev = prev;

		prev = cur1;
		cur2 = cur2->m_next;
	}

	if ( !otherIsEmpty )
	{
		cur1->m_next = nullptr;

		m_end = cur1;
	}

	m_size = other.m_size;
}

template < typename T > Container< T > & Container< T >::operator =( Container< T > const & other )
{
	if ( &other == this )
	{
		return *this;
	}

	Clear();

	m_begin = nullptr;
	m_end = nullptr;
	m_size = 0;
	{
		bool const otherIsEmpty = ( other.m_size == 0 );

		Node * cur1 = nullptr;
		if ( !otherIsEmpty )
		{
			cur1 = new Node( other.m_begin->m_data );

			m_begin = cur1;
		}
		else
		{
			return *this;
		}

		Node * cur2 = other.m_begin->m_next;
		Node * prev = m_begin;
		while ( cur2 )
		{
			cur1 = new Node( cur2->m_data );

			prev->m_next = cur1;
			cur1->m_prev = prev;

			prev = cur1;
			cur2 = cur2->m_next;
		}

		if ( !otherIsEmpty )
		{
			cur1->m_next = nullptr;

			m_end = cur1;
		}

		m_size = other.m_size;
	}

	return *this;
}

template < typename T > Container< T >::~Container()
{
	Clear();
}

template < typename T > void Container< T >::PushFront( T const & item )
{
	bool const isEmpty = ( m_size == 0 );

	Node * p = new Node( item );
	p->m_next = m_begin;
	if ( !isEmpty )
	{
		m_begin->m_prev = p;
	}

	m_begin = p;
	if ( isEmpty )
	{
		m_end = p;
	}
	++m_size;
}

template < typename T > void Container< T >::PushBack( T const & item )
{
	bool const isEmpty = ( m_size == 0 );

	Node * p = new Node( item );
	p->m_prev = m_end;
	if ( !isEmpty )
	{
		m_end->m_next = p;
	}

	if ( isEmpty )
	{
		m_begin = p;
	}
	m_end = p;
	++m_size;
}

template < typename T > void Container< T >::RemoveFirst()
{
	if ( m_size == 0 )
	{
		throw Exception( "Removing from empty container." );
	}

	if ( m_size == 1 )
	{
		delete m_begin;
		m_begin = nullptr;
		m_end = nullptr;
		m_size = 0;

		return;
	}

	m_begin = m_begin->m_next;
	delete m_begin->m_prev;
	m_begin->m_prev = nullptr;
	--m_size;
}

template < typename T > void Container< T >::RemoveLast()
{
	if ( m_size == 0 )
	{
		throw Exception( "Removing from empty container." );
	}

	if ( m_size == 1 )
	{
		delete m_begin;
		m_begin = nullptr;
		m_end = nullptr;
		m_size = 0;

		return;
	}

	m_end = m_end->m_prev;
	delete m_end->m_next;
	m_end->m_next = nullptr;
	--m_size;

	return;
}

template < typename T > T const & Container< T >::GetFirst() const
{
	if ( m_size == 0 )
	{
		throw Exception( "Try to get element from empty container." );
	}

	return m_begin->m_data;
}

template < typename T > T const & Container< T >::GetLast() const
{
	if ( m_size == 0 )
	{
		throw Exception( "Try to get element from empty container." );
	}

	return m_end->m_data;
}

template < typename T > uint16_t Container< T >::GetSize() const
{
	return m_size;
}

template < typename T > typename Container< T >::ConstIterator Container< T >::Begin() const
{
	return ConstIterator( m_begin );
}

template < typename T > typename Container< T >::ConstIterator Container< T >::End() const
{
	return ConstIterator( nullptr );
}

template < typename T > bool Container< T >::IsEmpty() const
{
	return ( m_size == 0 );
}

template < typename T > bool Container< T >::operator ==( Container< T > const & other ) const
{
	if ( m_size != other.m_size )
	{
		return false;
	}

	Node * cur1 = m_begin;
	Node * cur2 = other.m_begin;
	while ( cur1 )
	{
		if ( cur1->m_data != cur2->m_data )
		{
			return false;
		}

		cur1 = cur1->m_next;
		cur2 = cur2->m_next;
	}

	return true;
}

template < typename T > bool Container< T >::operator !=( Container< T > const & other ) const
{
	return !( *this == other );
}

template < typename T > void Container< T >::Clear()
{
	if ( m_size == 0 )
	{
		return;
	}

	if ( m_size == 1 )
	{
		delete m_begin;

		m_begin = nullptr;
		m_end = nullptr;
		m_size = 0;

		return;
	}

	Node * cleaner = m_begin;
	Node * next = m_begin->m_next;
	while ( cleaner != m_end )
	{
		delete cleaner;
		cleaner = next;
		next = next->m_next;
	}
	delete cleaner;

	m_begin = nullptr;
	m_end = nullptr;
	m_size = 0;
}



// ConstIterator :

template < typename T > T const & Container< T >::ConstIterator::operator *() const
{
	if ( !m_node )
	{
		throw Exception( "Getting value from invalid iterator." );
	}

	return m_node->m_data;
}

template < typename T > typename Container< T >::ConstIterator const & Container< T >::ConstIterator::operator ++()
{
	if ( !m_node )
	{
		throw Exception( "Increment of invalid iterator." );
	}

	m_node = m_node->m_next;

	return *this;
}

template < typename T > typename Container< T >::ConstIterator const Container< T >::ConstIterator::operator +( uint16_t n ) const
{
	ConstIterator result( *this );

	while ( n > 0 )
	{
		if ( result.m_node )
		{
			result.m_node = result.m_node->m_next;

			--n;
		}
		else
		{
			throw Exception( "Invalid sum of iterator and number." );
		}
	}

	return result;
}

template < typename T > bool Container< T >::ConstIterator::operator ==( Container< T >::ConstIterator const & other ) const
{
	return ( m_node == other.m_node );
}

template < typename T > bool Container< T >::ConstIterator::operator !=( Container< T >::ConstIterator const & other ) const
{
	return ( m_node != other.m_node );
}

template < typename T > T const * Container< T >::ConstIterator::GetPointer() const
{
	if ( !m_node )
	{
		throw Exception( "Getting data pointer from invalid iterator." );
	}

	return &m_node->m_data;
}

#endif // CONTAINER_H
