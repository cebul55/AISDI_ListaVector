#ifndef AISDI_LINEAR_VECTOR_H
#define AISDI_LINEAR_VECTOR_H

#include <iostream>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <limits>

namespace aisdi
{

template <typename Type>
class Vector
{
public:
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using value_type = Type;
  using pointer = Type*;
  using reference = Type&;
  using const_pointer = const Type*;
  using const_reference = const Type&;

  class ConstIterator;
  class Iterator;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

private:
    const size_type _default = 3;
    constexpr static size_type _limit = std::numeric_limits<size_type>::max() / sizeof(Type);
    size_type _size;
    size_type _maxSize;
    Type* _buffer;


public:
  Vector()
  {
    _size = 0;
    _maxSize = 0;
    _buffer = nullptr;
  }

  Vector(std::initializer_list<Type> l):Vector()
  {
    if(l.size() >= _limit) throw std::overflow_error("overflow");
    _size = 0;
    _maxSize = 2*l.size();
    Type *buff = new Type[_maxSize];
    _buffer = buff;

    for( auto& a : l){ append(a); }
  }

  Vector(const Vector& other)
  {
    _size = other._size;
    _maxSize = other._maxSize;
    _buffer = other._buffer;
  }

  Vector(Vector&& other)
  {
    _size = other._size;
    _maxSize = other._maxSize;
    _buffer = other._buffer;
    other._size = 0;
    other._maxSize = 0;
    other._buffer = nullptr;
  }

  ~Vector()
  {}

  Vector& operator=(const Vector& other)
  {
    if ( this == &other) return *this;
    erase(begin(), end());
    _buffer = other._buffer;
    _size = other._size;
    _maxSize = other._maxSize;
    return *this;
  }

  Vector& operator=(Vector&& other)
  {
    size_type new_size = _size;
    for(ConstIterator it = begin() ; it != end(); ++it)
    {
      (&*it)->~Type();
      --new_size;
    }
    _size = new_size;
    //erase(begin(), end());
    _size = other._size;
    _maxSize = other._maxSize;
    _buffer = other._buffer;
    other._maxSize= 0;
    other._size = 0;
    other._buffer = nullptr;
    return *this;
  }

  void build()
  {
    if(_maxSize == 0)
    {
      if (_buffer != nullptr) throw std::out_of_range("Some elements actually exist");
      _maxSize = _default;
      Type *buff = new Type[_default];
      _buffer = buff;
    }
    else /*if(_maxSize < (_limit / 3) )*/
    {
      if(_buffer == nullptr) throw std::out_of_range("Some elements actually exist");
      size_type newMaxSize = 3 * _maxSize;
      Type *newBuffer = new Type[newMaxSize];

      for(iterator it = begin(); it != end(); it++)
      {
        newBuffer[it._position] =*it._current;
        //(&*it)->~Type();

      }
      delete []_buffer;
      _maxSize = newMaxSize;
      _buffer = newBuffer;
    }
    /*else
    {
      throw std::overflow_error("overflow");
    }*/
  }

  bool isEmpty() const
  {
    if(_size == 0)return true;
    else return false;
  }

  size_type getSize() const
  {
    return _size;
  }

  void append(const Type& item)
  {
    if(_size == _maxSize)
      build();
    _buffer[_size] = item;
    ++_size;
  }

  void prepend(const Type& item)
  {
    insert(begin() , item);
  }

  void insert(const const_iterator& insertPosition, const Type& item)
  {
    if(_size >= _maxSize) build();
    ConstIterator it = insertPosition;
    for(ConstIterator it2 = end();it2 != it; it2--)
    {
      _buffer[it2._position]= _buffer[it2._position-1];
    }
    ++_size;
    _buffer[it._position] = item;
  }

  Type popFirst()
  {
      if(_size == 0 )throw std::logic_error("Vector is empty");
      Type tmp = *(begin());
      erase(begin());
      return tmp;
/*      if(_size == 0 )throw std::logic_error("Vector is empty");
      Type tmp = _buffer[0];
      erase(begin());
      return tmp;*/
  }

  Type popLast()
  {
    if(_size == 0 )throw std::logic_error("Vector is empty");
    Type tmp = *(--end());
    //Type tmp = _buffer[--(_size)];
    erase(--end());
    return tmp;  }

  void erase(const const_iterator& position)
  {
    if(position == cend())throw std::out_of_range("Out of range");
    const_iterator it = position;
    (&*it)->~Type();
    for(; it != cend() ; it++)
    {
      _buffer[it._position]= _buffer[it._position+1];
    }
    --_size;
  }

  void erase(const const_iterator& firstExcluded, const const_iterator& firstIncluded)
  {
    size_type new_size = _size;
    size_type length = firstIncluded._position - firstExcluded._position;
    for(ConstIterator it = firstExcluded ; it != firstIncluded; ++it)
    {
      (&*it)->~Type();
      --new_size;
    }
    for(ConstIterator it2 = firstExcluded ; it2 != end(); ++it2)
    {
      _buffer[it2._position] = _buffer[it2._position+length];

    }
    _size = new_size;
  }

  iterator begin()
  {
    Iterator *it = new Iterator();
    it->_size = &_size;
    it->_current = _buffer;
    it->_position = 0;
    return *it;
  }

  iterator end()
  {
    Iterator *it = new Iterator();
    it->_size = &_size;
    it->_current = _buffer;
    it->_position = _size;
    return *it;
  }

  const_iterator cbegin() const
  {
    ConstIterator *it = new ConstIterator();
    it->_size = &_size;
    it->_current = _buffer;
    it->_position = 0;
    return *it;
  }

  const_iterator cend() const
  {
    //wskazuje na pusty element za ostatnim dodanym !
    ConstIterator *it = new ConstIterator();
    it->_size = &_size;
    it->_current = _buffer;
    it->_position = _size;
    return *it;
  }

  const_iterator begin() const
  {
    return cbegin();
  }

  const_iterator end() const
  {
    return cend();
  }
};

template <typename Type>
class Vector<Type>::ConstIterator
{
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename Vector::value_type;
  using difference_type = typename Vector::difference_type;
  using pointer = typename Vector::const_pointer;
  using reference = typename Vector::const_reference;

//private:
    const size_type* _size;
    const Type* _current;
    size_type _position;
public:
  explicit ConstIterator()
  {
    _size = nullptr;
    _current = nullptr;
  }

  reference operator*() const
  {
    if(_position >= *_size)throw std::out_of_range("Out of range");
    return (_current)[_position];
  }

  ConstIterator& operator++()
  {
    if(_position >= *_size)throw std::out_of_range("Out of range");
    ++_position;
    return *this;
  }

  ConstIterator operator++(int)
  {
    ConstIterator* tmp = this;
    ++(*this);
    return *tmp;
  }

  ConstIterator& operator--()
  {
    if(_position <= 0 )throw std::out_of_range("Out of raaaaange");
    --_position;
    return *this;
  }

  ConstIterator operator--(int)
  {
    ConstIterator *tmp = this;
    --(*this);
    return *tmp;
  }

  ConstIterator operator+(difference_type d) const
  {
    ConstIterator *tmp = new ConstIterator;
    tmp->_size = this->_size;
    tmp->_position = this->_position;
    tmp->_current = this->_current;
    if(d>0)
    {
      while( d-- > 0){++(*tmp);}
    }
    else if (d<0)
    {
      while( d++ < 0){--(*tmp);}
    }
    return *tmp;
  }

  ConstIterator operator-(difference_type d) const
  {
    return operator+(-d);
  }

  bool operator==(const ConstIterator& other) const
  {
    if(_position == other._position)return true;
    else return false;
  }

  bool operator!=(const ConstIterator& other) const
  {
    if(_position != other._position)return true;
    else return false;
  }
};

template <typename Type>
class Vector<Type>::Iterator : public Vector<Type>::ConstIterator
{
public:
  using pointer = typename Vector::pointer;
  using reference = typename Vector::reference;

  explicit Iterator()
  {}

  Iterator(const ConstIterator& other)
    : ConstIterator(other)
  {}

  Iterator& operator++()
  {
    ConstIterator::operator++();
    return *this;
  }

  Iterator operator++(int)
  {
    auto result = *this;
    ConstIterator::operator++();
    return result;
  }

  Iterator& operator--()
  {
    ConstIterator::operator--();
    return *this;
  }

  Iterator operator--(int)
  {
    auto result = *this;
    ConstIterator::operator--();
    return result;
  }

  Iterator operator+(difference_type d) const
  {
    return ConstIterator::operator+(d);
  }

  Iterator operator-(difference_type d) const
  {
    return ConstIterator::operator-(d);
  }

  reference operator*() const
  {
    // ugly cast, yet reduces code duplication.
    return const_cast<reference>(ConstIterator::operator*());
  }
};

}

#endif // AISDI_LINEAR_VECTOR_H
