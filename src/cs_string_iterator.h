/***********************************************************************
*
* Copyright (c) 2017-2017 Barbara Geller
* Copyright (c) 2017-2017 Ansel Sermersheim
* All rights reserved.
*
* This file is part of CsString
*
* CsString is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
***********************************************************************/

#ifndef LIB_CS_STRING_ITERATOR_H
#define LIB_CS_STRING_ITERATOR_H

#include <vector>

#include <cs_char.h>

namespace CsString {

template <typename E, typename A>
class LIB_CS_STRING_EXPORT CsStringIterator
{
   using v_iter = typename std::vector<typename E::storage_unit, A>::const_iterator;

   public:
      using difference_type   = int;
      using value_type        = CsChar;
      using pointer           = CsChar *;
      using reference         = CsChar &;
      using iterator_category = std::random_access_iterator_tag;

      CsStringIterator() = default;

      CsChar operator*() const;
      CsChar operator->() const;

      CsChar operator[](int x) const;

      // comparisons
      bool operator!=(const CsStringIterator &other) const;
      bool operator==(const CsStringIterator &other) const;
      bool operator<(const CsStringIterator &other) const;
      bool operator<=(const CsStringIterator &other) const;
      bool operator>(const CsStringIterator &other) const;
      bool operator>=(const CsStringIterator &other) const;

      // math
      CsStringIterator &operator+=(int x);
      CsStringIterator &operator-=(int x);

      CsStringIterator operator+(int x) const;
      CsStringIterator &operator++();
      CsStringIterator operator++(int);

      CsStringIterator operator-(int x) const;
      int operator-(CsStringIterator iter) const;
      CsStringIterator &operator--();
      CsStringIterator operator--(int);

   private:
      explicit CsStringIterator(v_iter iter);

      typename std::pair<v_iter, v_iter> codePointRange() const;
      v_iter codePointBegin() const;
      v_iter codePointEnd() const;

      v_iter m_data;

      friend class CsBasicString<E, A>;
};

template <typename E, typename A>
CsChar CsStringIterator<E,A>::operator*() const
{
   return E::getCodePoint(m_data);
}

template <typename E, typename A>
CsChar CsStringIterator<E,A>::operator->() const
{
    return E::getCodePoint(m_data);
}

template <typename E, typename A>
CsChar CsStringIterator<E,A>:: operator[](int x) const
{
   // calls operator+()
   return *(*this + x);
}

// comparisons
template <typename E, typename A>
bool CsStringIterator <E,A>::operator!=(const CsStringIterator &other) const
{
   return m_data != other.m_data;
}

template <typename E, typename A>
bool CsStringIterator <E,A>::operator==(const CsStringIterator &other) const
{
   return m_data == other.m_data;
}

template <typename E, typename A>
bool CsStringIterator <E,A>::operator<(const CsStringIterator &other) const
{
   return m_data < other.m_data;
}

template <typename E, typename A>
bool CsStringIterator <E,A>::operator<=(const CsStringIterator &other) const
{
   return m_data <= other.m_data;
}

template <typename E, typename A>
bool CsStringIterator <E,A>::operator>(const CsStringIterator &other) const
{
   return m_data > other.m_data;
}

template <typename E, typename A>
bool CsStringIterator <E,A>::operator>=(const CsStringIterator &other) const
{
   return m_data >= other.m_data;
}

// math
template <typename E, typename A>
CsStringIterator<E,A> &CsStringIterator<E,A>::operator+=(int x)
{
   m_data += E::walk(x, m_data);

   return *this;
}
template <typename E, typename A>
CsStringIterator<E,A> &CsStringIterator<E,A>::operator-=(int x)
{
   m_data += E::walk(-x, m_data);
   return *this;
}

template <typename E, typename A>
CsStringIterator<E,A> CsStringIterator<E,A>::operator+(int x) const
{
   auto iter = m_data + E::walk(x, m_data);
   return CsStringIterator(iter);
}

template <typename E, typename A>
CsStringIterator<E,A> &CsStringIterator<E,A>::operator++()
{
   m_data += E::walk(1, m_data);
   return *this;
}

template <typename E, typename A>
CsStringIterator<E,A> CsStringIterator<E,A>::operator++(int)
{
   CsStringIterator iter = *this;
   m_data += E::walk(1, m_data);

   return iter;
}

template <typename E, typename A>
CsStringIterator<E,A> CsStringIterator<E,A>::operator-(int x) const
{
   auto iter = m_data + E::walk(-x, m_data);
   return CsStringIterator(iter);
}

template <typename E, typename A>
int CsStringIterator <E,A>::operator-(CsStringIterator iter) const
{
   // broom - add method in encoding
   int retval = m_data - iter.m_data;

   return retval;
}

template <typename E, typename A>
CsStringIterator<E,A> &CsStringIterator<E,A>::operator--()
{
   m_data += E::walk(-1, m_data);
   return *this;
}

template <typename E, typename A>
CsStringIterator<E,A> CsStringIterator<E,A>::operator--(int)
{
   CsStringIterator iter = *this;
   m_data += E::walk(-1, m_data);

   return iter;
}

// private methods
template <typename E, typename A>
CsStringIterator<E,A>::CsStringIterator(v_iter iter)
{
   m_data = iter;
}

template <typename E, typename A>
auto CsStringIterator<E,A>::codePointRange() const -> typename std::pair<v_iter, v_iter>
{
   return std::make_pair(m_data, m_data + E::walk(1, m_data));
}

template <typename E, typename A>
auto CsStringIterator<E,A>::codePointBegin() const -> v_iter
{
   return m_data;
}

template <typename E, typename A>
auto CsStringIterator<E,A>::codePointEnd() const -> v_iter
{
   return m_data + E::walk(1, m_data);
}

}

#endif