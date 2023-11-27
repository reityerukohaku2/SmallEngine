#pragma once
#include "pch.h"

template <class T>
class ICollection
{
	using iterator = typename std::vector<T>::const_iterator;
public:
	virtual ~ICollection () {};
	virtual void push_back (T) = 0;
	virtual T* data () = 0;
	virtual iterator begin () = 0;
	virtual iterator end () = 0;
	virtual void clear () = 0;
	virtual size_t size () = 0;
};
