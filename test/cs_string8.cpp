/***********************************************************************
*
* Copyright (c) 2017-2024 Barbara Geller
* Copyright (c) 2017-2024 Ansel Sermersheim
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

#include <cs_string.h>
#include <cs_char.h>

#include <cs_catch2.h>

TEST_CASE("CsString_utf8 traits", "[cs_string8]")
{
   REQUIRE(std::is_copy_constructible_v<CsString::CsString_utf8> == true);
   REQUIRE(std::is_move_constructible_v<CsString::CsString_utf8> == true);

   REQUIRE(std::is_copy_assignable_v<CsString::CsString_utf8> == true);
   REQUIRE(std::is_move_assignable_v<CsString::CsString_utf8> == true);

   REQUIRE(std::has_virtual_destructor_v<CsString::CsString_utf8> == false);
}

TEST_CASE("CsString_utf8 append", "[cs_string8]")
{
   CsString::CsString_utf8 str = "ABCD";

   str.append(UCHAR('𝅘𝅥𝅮'));

   REQUIRE(str == u8"ABCD𝅘𝅥𝅮");
}

TEST_CASE("CsString_utf8 u8_append", "[cs_string8]")
{
   CsString::CsString_utf8 str = u8"A wacky fox and sizeable pig";

   str.append(u8" went to lunch");

   REQUIRE(str == u8"A wacky fox and sizeable pig went to lunch");
}

TEST_CASE("CsString_utf8 begin_end", "[cs_string8]")
{
   CsString::CsString_utf8 str = "On a clear day you can see forever";

   {
      auto iterBegin = str.begin();
      auto iterEnd   = str.end();

      REQUIRE(*iterBegin == 'O');
      REQUIRE(*(iterEnd - 1) == 'r');
   }

   {
      auto iterBegin = str.cbegin();
      auto iterEnd   = str.cend();

      REQUIRE(*iterBegin == 'O');
      REQUIRE(*(iterEnd - 1) == 'r');
   }

   {
      auto iterBegin = str.cbegin();
      auto iterEnd   = str.cend();

      REQUIRE(*iterBegin == 'O');
      REQUIRE(*(iterEnd - 1) == 'r');
   }
}

TEST_CASE("CsString_utf8 clear", "[cs_string8]")
{
   CsString::CsString_utf8 str = "On a clear day you can see forever";

   str.clear();

   REQUIRE(str.length() == 0);
}

TEST_CASE("CsString_utf8 comparison", "[cs_string8]")
{
   CsString::CsString_utf8 str1 = "grapes";
   CsString::CsString_utf8 str2 = "apples";

   REQUIRE(str2 < str1);
   REQUIRE(! (str1 < str2));

   REQUIRE(str2 <= str1);
   REQUIRE(! (str1 <= str2));

   REQUIRE(! (str2 > str1));
   REQUIRE(str1 > str2);

   REQUIRE(! (str2 >= str1));
   REQUIRE(str1 >= str2);
}

TEST_CASE("CsString_utf8 u8_constructor", "[cs_string8]")
{
   CsString::CsString_utf8 str = u8"On a clear day you can see forever";
   REQUIRE(str == u8"On a clear day you can see forever");
}

TEST_CASE("CsString_utf8 empty", "[cs_string8]")
{
   CsString::CsString_utf8 str;

   REQUIRE(str.empty());
   REQUIRE(str.constData()[0] == '\0');

   REQUIRE(str.cbegin() == str.cend());
   REQUIRE(str.begin() == str.end());
}

TEST_CASE("CsString_utf8 find_a", "[cs_string8]")
{
   CsString::CsString_utf8 str1 = "On a clear day you can see forever";

   {
      int index = str1.find("day");
      CsString::CsString_utf8 str2 = str1.substr(index);

      REQUIRE(str2 == "day you can see forever");
   }

   {
      int index = str1.find("c", 10);
      CsString::CsString_utf8 str2 = str1.substr(index);

      REQUIRE(str2 == "can see forever");
   }

   {
      int index = str1.find_first_not_of("c", 15);
      CsString::CsString_utf8 str2 = str1.substr(index);

      REQUIRE(str2 == "you can see forever");
   }

   {
      auto iter = str1.find_fast("day");
      CsString::CsString_utf8 str2(iter, str1.end());

      REQUIRE(str2 == "day you can see forever");
   }
}

TEST_CASE("CsString_utf8 find_b", "[cs_string8]")
{
   CsString::CsString_utf8 str1 = "ABCD";

   str1.append(UCHAR('↴'));

   {
      int index = str1.find_first_not_of("DAZB");
      CsString::CsString_utf8 str2 = str1.substr(index);

      REQUIRE(str2 == u8"CD↴");
   }

   {
      int index = str1.find_first_not_of("B↴", 1);
      CsString::CsString_utf8 str2 = str1.substr(index);

      REQUIRE(str2 == u8"CD↴");
   }

   {
      int index = str1.find_last_not_of("E", 3);
      CsString::CsString_utf8 str2 = str1.substr(index);

      REQUIRE(str2 == u8"D↴");
   }

   {
      int index = str1.rfind('D');
      CsString::CsString_utf8 str2 = str1.substr(index);

      REQUIRE(str2 == u8"D↴");
   }

   {
      int index = str1.rfind('D', 3);
      CsString::CsString_utf8 str2 = str1.substr(index);

      REQUIRE(str2 == u8"D↴");
   }

   {
      int index = str1.rfind('A', 9);
      CsString::CsString_utf8 str2 = str1.substr(index);

      REQUIRE(str2 == u8"ABCD↴");
   }
}

TEST_CASE("CsString_utf8 insert_uchar", "[cs_string8]")
{
   CsString::CsString_utf8 str = "On a clear day you can see forever";

   str.insert(5, 2, UCHAR('↵'));

   REQUIRE(str == "On a ↵↵clear day you can see forever");
}

TEST_CASE("CsString_utf8 insert_str", "[cs_string8]")
{
   CsString::CsString_utf8 str1 = "Sunday Tuesday";
   CsString::CsString_utf8 str2 = "Monday ";

   SECTION ("insert_a") {
      str1.insert(7, str2);
      REQUIRE(str1 == "Sunday Monday Tuesday");
   }

   SECTION ("insert_b") {
      auto iter = str1.insert(str1.begin() + 7, str2);
      REQUIRE(str1 == "Sunday Monday Tuesday");
      REQUIRE(*iter == 'M');
   }

   SECTION ("insert_c") {
      auto iter = str1.insert(str1.begin() + 7, str2.begin(), str2.end());
      REQUIRE(str1 == "Sunday Monday Tuesday");
      REQUIRE(*iter == 'M');
   }

   SECTION ("insert_d") {
      auto iter = str1.insert(str1.begin() + 6, CsString::CsChar('!'));
      REQUIRE(str1 == "Sunday! Tuesday");
      REQUIRE(*iter == '!');
   }
}

TEST_CASE("CsString_utf8 iterator", "[cs_string8]")
{
   CsString::CsString_utf8 str("ABCD");

   str.append(UCHAR('↴'));            // 3 bytes
   str.append(UCHAR('¿'));            // 2 bytes
   str.append('E');
   str.append(UCHAR('𝅘𝅥𝅮'));            // 4 bytes, unicode 01 D1 60
   str.append('F');

   CsString::CsString::const_iterator iter = str.end();

   REQUIRE(iter != str.begin());

   --iter;

   REQUIRE(iter != str.begin());
   REQUIRE(iter->unicode() == 70);

   --iter;

   REQUIRE(iter != str.begin());
   REQUIRE(iter->unicode() == 0x01D160);

   --iter;

   REQUIRE(iter != str.begin());
   REQUIRE(iter->unicode() == 69);

   --iter;

   REQUIRE(iter != str.begin());
   REQUIRE(iter->unicode() == 0x00BF);

   --iter;

   REQUIRE(iter != str.begin());
   REQUIRE(iter->unicode() == 0x21b4);

   //
   iter = str.begin();
   int eraseCnt = 0;

   while (! str.empty())  {
      iter = str.erase(iter);
      ++eraseCnt;
   }

   REQUIRE(eraseCnt == 9);
}

TEST_CASE("CsString_utf8 u8_length", "[cs_string8]")
{
   CsString::CsString_utf8 str = u8"!ä";

   REQUIRE(str.length() ==  2);
   REQUIRE(str.size() ==  2);

   REQUIRE(str[0].unicode() == char32_t(33));
   REQUIRE(str[1].unicode() == char32_t(228));
}

TEST_CASE("CsString_utf8 replace", "[cs_string8]")
{
   CsString::CsString_utf8 str = "On a clear day you can see forever";

   str.replace(5, 2, u8"↵");

   REQUIRE(str == "On a ↵ear day you can see forever");
}

TEST_CASE("CsString_utf8 resize", "[cs_string8]")
{
   CsString::CsString_utf8 str("ABCD");

   str.append(UCHAR('↴'));               // 3 bytes
   str.resize(8, UCHAR('¿'));

   REQUIRE(str.size() == 8);
   REQUIRE(str.substr(7,1) == u8"¿");
   REQUIRE(str.substr(5,3) == u8"¿¿¿");

   str.resize(7);
   REQUIRE(str.size() == 7);

   str.resize(3);
   REQUIRE(str.size() == 3);

   REQUIRE(str == "ABC");
}

TEST_CASE("CsString_utf8 size", "[cs_string8]")
{
   CsString::CsString_utf8 str("ABCD");

   str.append(UCHAR('↴'));               // 3 storage units

   REQUIRE(str.size_storage() == 7);
   REQUIRE(str.size_codePoints() == 5);
   REQUIRE(str.size() == 5);
   REQUIRE(str.length() == 5);
}

TEST_CASE("CsString_utf8 u8_storage_iterators", "[cs_string8]")
{
   CsString::CsString_utf8 str;

   REQUIRE(str.storage_begin()  == str.storage_end());
   REQUIRE(str.storage_rbegin() == str.storage_rend());

   str = u8"grape";
   REQUIRE(*str.storage_begin()  == u8'g');
   REQUIRE(*str.storage_rbegin() == u8'e');
   REQUIRE(str.storage_end() - str.storage_begin() == 5);

   // unicode 21B4, three storage units
   CsString::CsString_utf8 arrow(1, U'↴');

   str = u8"grape" + arrow;

   REQUIRE(*(str.storage_end() - 4) == u8'e');
   REQUIRE(*(str.storage_rbegin() + 3) == u8'e');
}

TEST_CASE("CsString_utf8 swap", "[cs_string8]")
{
   CsString::CsString_utf8 str1 = "string one";
   CsString::CsString_utf8 str2 = "string two";

   swap(str1, str2);

   REQUIRE(str1 == "string two");
   REQUIRE(str2 == "string one");
}

TEST_CASE("CsString_utf8 u8_various", "[cs_string8]")
{
   {
      CsString::CsString str(5, UCHAR('↴'));

      REQUIRE(str.size() == 5);
      REQUIRE(str[0].unicode() == 0x21B4);
      REQUIRE(str == "↴↴↴↴↴");
   }

   {
      std::vector<CsString::CsChar> v = {'G', 'I', 'N', 'G', 'E', 'R' };
      CsString::CsString str(v.begin(), v.begin() + 3);

      REQUIRE(str.size() == 3);
      REQUIRE(str == "GIN");
   }
}

TEST_CASE("CsString_utf8 prefix", "[cs_string8]")
{

#if defined(__cpp_char8_t)
   // c++20

   REQUIRE(std::is_same_v<char8_t,  decltype(u8'a')> == true);
   REQUIRE(std::is_same_v<char16_t, decltype(u8'a')> == false);

   REQUIRE(std::is_same_v<const char8_t(&)[15], decltype(u8"On a clear day")> == true);

#else
   REQUIRE(std::is_same_v<char,     decltype(u8'a')> == true);
   REQUIRE(std::is_same_v<char16_t, decltype(u8'a')> == false);

   REQUIRE(std::is_same_v<const char(&)[15], decltype(u8"On a clear day")> == true);
#endif

}

// C++20 only
TEST_CASE("CsString_utf8 char8_t_constructor", "[cs_string8]")
{
#if defined(__cpp_char8_t)
   printf("\nCsString C++20 char8_t checks enabled\n");

   const char8_t *data = u8"A wacky fox and sizeable pig";

   CsString::CsString_utf8 str = data;

   REQUIRE(str == "A wacky fox and sizeable pig");

#else
   printf("\nCsString C++20 char8_t checks omitted\n");
#endif
}

// utf-32
TEST_CASE("CsString_utf8 u32_append", "[cs_string8]")
{
   CsString::CsString_utf8 str = U"A wacky fox and sizeable pig";

   str.append(U" went to lunch");

   REQUIRE(str == U"A wacky fox and sizeable pig went to lunch");
}

TEST_CASE("CsString_utf8 u32_length", "[cs_string8]")
{
   CsString::CsString_utf8 str = U"!ä";

   REQUIRE(str.length() ==  2);

   REQUIRE(str[0].unicode() == char32_t(33));
   REQUIRE(str[1].unicode() == char32_t(228));
}

TEST_CASE("CsString_utf8 u32_constructor", "[cs_string8]")
{
   {
      CsString::CsString_utf8 str = U"On a clear day you can see forever";
      REQUIRE(str == U"On a clear day you can see forever");
   }

   {
      CsString::CsString_utf8 str(U"On a clear day you can see forever", 10);

      REQUIRE(str.size() == 10);
      REQUIRE(str == U"On a clear");
   }
}


