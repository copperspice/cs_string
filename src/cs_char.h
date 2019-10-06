/***********************************************************************
*
* Copyright (c) 2017-2019 Barbara Geller
* Copyright (c) 2017-2019 Ansel Sermersheim
*
* This file is part of CsString.
*
* CsString is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#ifndef LIB_CS_CHAR_H
#define LIB_CS_CHAR_H

#include <stdint.h>

#include <functional>
#include <memory>

namespace CsString {

#ifdef _WIN32

#ifdef BUILDING_LIB_CS_STRING
# define LIB_CS_STRING_EXPORT     __declspec(dllexport)
#else
# define LIB_CS_STRING_EXPORT     __declspec(dllimport)
#endif

#else
# define LIB_CS_STRING_EXPORT

#endif

template <typename E, typename A = std::allocator<typename E::storage_unit>>
class CsBasicString;

class CsChar
{
   public:
      constexpr CsChar() noexcept
         : m_char(0)
      {

      }

      template <typename T = int>
      constexpr CsChar(char c) noexcept
         : m_char(static_cast<unsigned char>(c))
      {
#ifndef CS_STRING_ALLOW_UNSAFE
   static_assert(! std::is_same<T, T>::value, "Unsafe operations not allowed, unknown encoding for this operation");
#endif
      }

      /* UTF-8 characters - Available only with C++20 */
#ifdef __cpp_char8_t
      constexpr CsChar(char8_t c) noexcept
         : m_char(c)
      {
      }
#endif

      /* UTF-16 characters - as specified at http://eel.is/c++draft/lex.ccon#4 */
      constexpr CsChar(char16_t c) noexcept
        : m_char(c)
      {
      }

      constexpr CsChar(char32_t c) noexcept
         : m_char(c)
      {
      }

      constexpr CsChar(int c) noexcept
         : m_char(c)
      {
      }

      constexpr bool operator!=(const CsChar &other) const noexcept;
      constexpr bool operator==(const CsChar &other) const noexcept;

      constexpr bool operator<(const CsChar &other) const noexcept;
      constexpr bool operator<=(const CsChar &other) const noexcept;
      constexpr bool operator>(const CsChar &other) const noexcept;
      constexpr bool operator>=(const CsChar &other) const noexcept;

      constexpr CsChar &operator=(char c) & noexcept;
      constexpr CsChar &operator=(char32_t c) & noexcept;
      constexpr CsChar &operator=(CsChar c) & noexcept;

      constexpr uint32_t unicode() const noexcept;

   private:
      uint32_t m_char;
};

// comparisons
inline constexpr bool CsChar::operator!=(const CsChar &other) const noexcept
{
   return m_char != other.m_char;
}

inline constexpr bool CsChar::operator==(const CsChar &other) const noexcept
{
   return m_char == other.m_char;
}

inline constexpr bool CsChar::operator<(const CsChar &other) const noexcept
{
   return m_char < other.m_char;
}

inline constexpr bool CsChar::operator<=(const CsChar &other) const noexcept
{
   return m_char <= other.m_char;
}

inline constexpr bool CsChar::operator>(const CsChar &other) const noexcept
{
   return m_char > other.m_char;
}

inline constexpr bool CsChar::operator>=(const CsChar &other) const noexcept
{
   return m_char >= other.m_char;
}

inline constexpr CsChar &CsChar::operator=(char c) & noexcept
{
   m_char = c;
   return *this;
}

inline constexpr CsChar &CsChar::operator=(char32_t c) & noexcept
{
   m_char = c;
   return *this;
}

inline constexpr CsChar &CsChar::operator=(CsChar c) & noexcept
{
   m_char = c.m_char;
   return *this;
}

inline constexpr uint32_t CsChar::unicode() const noexcept
{
   return m_char;
}

} // namespace

namespace std {
   template<>
   struct hash<CsString::CsChar>
   {
      inline size_t operator()(const CsString::CsChar &key) const
      {
         return key.unicode();
      }
   };
}

#endif
