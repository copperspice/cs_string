/***********************************************************************
*
* Copyright (c) 2017-2022 Barbara Geller
* Copyright (c) 2017-2022 Ansel Sermersheim
*
* This file is part of CsString.
*
* CsString is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
* CsString is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#define CS_STRING_ALLOW_UNSAFE

#include <cs_char.h>

#include <cs_catch2.h>

TEST_CASE("CsChar traits", "[cs_char]")
{
   REQUIRE(std::is_copy_constructible_v<CsString::CsChar> == true);
   REQUIRE(std::is_move_constructible_v<CsString::CsChar> == true);

   REQUIRE(std::is_copy_assignable_v<CsString::CsChar> == true);
   REQUIRE(std::is_move_assignable_v<CsString::CsChar> == true);

   REQUIRE(std::has_virtual_destructor_v<CsString::CsChar> == false);
}

TEST_CASE("CsChar u8_constructor", "[cs_char]")
{
   CsString::CsChar ch = u8'b';

   REQUIRE(ch.unicode() == char32_t(98));
   REQUIRE(ch == u8'b');
   REQUIRE(ch != u8'c');

#if defined(__cpp_char8_t)
   // c++20

   REQUIRE(u8'b' == ch);
   REQUIRE(u8'c' != ch);
#endif

}

TEST_CASE("QChar u_constructor", "[cs_char]")
{
   CsString::CsChar ch = u'b';

   REQUIRE(ch.unicode() == char32_t(98));
   REQUIRE(ch == u'b');
   REQUIRE(ch != u'c');

#if defined(__cpp_char8_t)
   // c++20

   REQUIRE(u'b' == ch);
   REQUIRE(u'c' != ch);
#endif
}

TEST_CASE("QChar U_constructor", "[cs_char]")
{
   CsString::CsChar ch = U'b';

   REQUIRE(ch.unicode() == char32_t(98));
   REQUIRE(ch == U'b');
   REQUIRE(ch != U'c');

#if defined(__cpp_char8_t)
   // c++20

   REQUIRE(U'b' == ch);
   REQUIRE(U'c' != ch);
#endif
}

TEST_CASE("QChar empty", "[cs_char]")
{
   CsString::CsChar ch;

   REQUIRE(ch.unicode() == 0);
}
