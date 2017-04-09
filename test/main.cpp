/***********************************************************************
*
* Copyright (c) 2017-2017 Barbara Geller
* Copyright (c) 2017-2017 Ansel Sermersheim
* All rights reserved.
*
* This file is part of libCsString
*
* libCsString is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
***********************************************************************/

#include <stdio.h>

#include <cs_string.h>

bool g_unitTest = true;

void test_1();
void test_2();
void test_3();
void test_4();
void test_5();
void test_6();
void test_7();
void test_8();
void test_9();
void test_10();
void test_11();
void test_12();
void test_13();
void test_14();
void test_15();


int main()
{
   printf("\n%s\n\n", "** CsString Library - Start of Unit Test **");

   test_1();
   test_2();
   test_3();
   test_4();
   test_5();
   test_6();
   test_7();
   test_8();
   test_9();
   test_10();
   test_11();
   test_12();
   test_13();
   test_14();
   test_15();

   printf("\n\n");

   if (! g_unitTest) {
      return 1;
   }
}

void test_1()
{
   bool ok = true;
   printf("** Unit Test 1\n");

   // default constructor & destructor

   {
      CsString::CsString str;
   }

   printf("Create and Destroy an empty string\n");

   if (ok) {
      printf("End Unit Test One - PASSED\n\n");

   } else {
      printf("End Unit Test One - Failed\n\n");
      g_unitTest = false;

   }
}

void test_2()
{
   bool ok = true;
   printf("\n** Unit Test 2\n");

   // CsChar internationalization test

   // unicode 00 42, data type char
   CsString::CsChar c0   = 'B';

   // unicode 00 BF, data type maybe char or int, compile will return the value
   CsString::CsChar c127 = '¿';
   CsString::CsChar u127 = UCHAR('¿');

   // unicode 21 B4, data type int or a compile error, not safe
   CsString::CsChar c256 = '↴';

   // unicode 21 B4, data type char32_t, guaranteed to be the proper unicode value
   CsString::CsChar u256 = UCHAR('↴');

   // unicode 01 D1 60, data type int or a compile error, not safe
   CsString::CsChar cX = '𝅘𝅥𝅮';

   // unicode 01 D1 60, data type char32_t, guaranteed to be the proper unicode value
   CsString::CsChar uX = UCHAR('𝅘𝅥𝅮');

   printf("\n");
   printf("Char B    %08x \n", c0.unicode());

   printf("Char ¿    %08x    (implementation defined, unsafe) \n", c127.unicode());
   printf("Char ¿    %08x    (unicode literal)  \n", u127.unicode());

   printf("Char ↴    %08x    (implementation defined, unsafe) \n", c256.unicode());
   printf("Char ↴    %08x    (unicode literal)  \n", u256.unicode());

   printf("Char 𝅘𝅥𝅮    %08x    (implementation defined, unsafe) \n", cX.unicode());
   printf("Char 𝅘𝅥𝅮    %08x    (unicode literal)  \n", uX.unicode());

   printf("\n");

   if (ok) {
      printf("End Unit Test Two - PASSED\n\n");

   } else {
      printf("End Unit Test Two - Failed\n\n");
      g_unitTest = false;

   }
}

void test_3()
{
   bool ok = true;
   printf("\n** Unit Test 3\n");

   {
      CsString::CsString str;
      str.append('A');
      str.append(':');
      str.append(' ');
      str.append(UCHAR('¿'));
      str.append(' ');
      str.append(' ');
      str.append(' ');
      str.append('B');
      str.append(':');
      str.append(' ');
      str.append(UCHAR('↴'));
      str.append(' ');
      str.append(' ');
      str.append(' ');
      str.append('C');
      str.append(':');
      str.append(' ');
      str.append(UCHAR('𝅘𝅥𝅮'));

      printf("\nA: (2 bytes) upside down question mark \nB: (3 bytes) rightwards arrow with corner downwards \n"
               "C: (4 bytes) musical symbol eighth note \n%s\n", str.constData());
   }

   printf("\n");

   if (ok) {
      printf("End Unit Test Three - PASSED\n\n");

   } else {
      printf("End Unit Test Three - Failed\n\n");
      g_unitTest = false;

   }
}

void test_4()
{
   bool ok = true;
   printf("\n** Unit Test 4\n");

   static_assert (std::is_move_constructible<CsString::CsString>::value, "Unable to move CsString");

   // part a
   CsString::CsString str1("A wacky fox and sizeable pig jumped halfway over a blue moon.");
   printf("\nConstructor passed a string literal: %s", str1.constData());

   CsString::CsString str2(str1);
   printf("\nCopy Construct String 1 to String 2: %s", str2.constData());

   CsString::CsString str3(std::move(str1));
   printf("\nMove Construct String 1 to String 3: %s", str3.constData());

   // part b
   const char *tmp = "This is a string literal assigned to a 'const char *'";
   CsString::CsString str4(tmp);
   printf("\n\nConstructor passed a const char *  : %s\n", str4.constData());

   printf("\n");

   if (ok) {
      printf("End Unit Test Four - PASSED\n\n");

   } else {
      printf("End Unit Test Fout - Failed\n\n");
      g_unitTest = false;

   }
}

void test_5()
{
   bool ok = true;
   printf("\n** Unit Test 5\n");

   CsString::CsString str1(5, UCHAR('↴'));
   printf("\nConstructed string with 5 copies of the same 2 byte character: %s", str1.constData());

   std::vector<CsString::CsChar> v = {'G', 'I', 'N', 'G', 'E', 'R' };
   CsString::CsString str2(v.begin(), v.begin() + 3);
   printf("\nConstructed string from vector GINGER, use iterator to copy first 3 elements: %s\n", str2.constData());

   if (str2 != "GIN") {
      ok = false;
   }

   // find
   // To dream t he impossi ble dream
   // 0123456789 0123456789 012345678

   CsString::CsString str3("To dream the impossible dream");

   int x1 = str3.find(CsString::CsString("dream"));
   int x2 = str3.find("dream", 10);
   int x3 = str3.find_first_not_of('s', 17);

   printf("\nGiven the following string              : %s", str3.constData());
   printf("\nStart at index  0, find 'dream'         : %d", x1);
   printf("\nStart at index 10, find 'dream'         : %d", x2);
   printf("\nStart at index 17, find first not of 's': %d", x3);

   printf("\n\n");

   if (x1 != 3 || x2 != 24) {
      ok = false;
   }


// more finds


   if (ok) {
      printf("End Unit Test Five - PASSED\n\n");

   } else {
      printf("End Unit Test Five - Failed\n\n");
      g_unitTest = false;

   }
}

void test_6()
{
   bool ok = true;
   printf("\n** Unit Test 6\n");

   CsString::CsString str1("Ending character is 3 bytes ");
   str1.append(UCHAR('↴'));

   CsString::CsString str2;
   str2 = str1;

   printf("\nAssign String 1 to String 2: %s", str2.constData());

   CsString::CsString str3;
   str3 = std::move(str1);

   printf("\nMove   String 1 to String 3: %s\n", str3.constData());

   if (str2 != str3) {
      ok = false;
   }

   // insert tests
   str3.insert(6, 2, UCHAR('↵'));
   printf("\nInsert  2 left arrows  at the 7th character: %s", str3.constData());

   str3.insert(6, " [string literal] ");
   printf("\nInsert  string literal at the 7th character: %s", str3.constData());


   // replace
   CsString::CsString tmp = " [string literal] xx ";
   int len = tmp.size();

   str3.replace(6, len, " { new string text } ");
   printf("\nReplace string literal at the 7th character: %s", str3.constData());


   printf("\n\n");

   if (ok) {
      printf("End Unit Test Six - PASSED\n\n");

   } else {
      printf("End Unit Test Six - Failed\n\n");
      g_unitTest = false;

   }
}

void test_7()
{
   bool ok = true;
   printf("\n** Unit Test 7\n");

   CsString::CsString str1("ABCD");
   str1.append(UCHAR('↴'));            // 3 bytes
   str1.append(UCHAR('¿'));            // 2 bytes
   str1.append('E');
   str1.append(UCHAR('𝅘𝅥𝅮'));            // 4 bytes
   str1.append('F');

   printf("\nOriginal String: %s", str1.constData());
   printf("\n");


   // 2
   CsString::CsString::const_iterator iter2 = str1.end();

   if (iter2 == str1.begin()) {
      // do nothing

   } else {
      --iter2;

      while (true) {
         const CsString::CsChar c = *iter2;

         CsString::CsString tmp(1, c);
         printf("\nWalk backwards: %s", tmp.constData() );

         if (iter2 == str1.begin()) {
            break;
         }

         --iter2;
      }
   }

   printf("\n");


   // 3
   CsString::CsString str3 = str1.substr(3, 4);
   printf("\nSubstring beginning at 3, length 4: %s", str3.constData());

   printf("\n");


   // 4
   CsString::CsString::const_iterator iter4 = str1.begin();
   int eraseCnt = 0;

   while (! str1.empty())  {
      CsString::CsString tmp(1, *iter4);

      iter4 = str1.erase(iter4);
      ++eraseCnt;

      printf("\nErase %s element: %s", tmp.constData(), str1.constData());
   }

   printf("\n\n");

   if (eraseCnt != 9) {
      ok = false;
   }

   if (ok) {
      printf("End Unit Test Seven - PASSED\n\n");

   } else {
      printf("End Unit Test Seven - Failed\n\n");
      g_unitTest = false;

   }
}

void test_8()
{
   bool ok = true;
   printf("\n** Unit Test 8\n");

   // 1
   CsString::CsString str1("ABCD");
   str1.append(UCHAR('↴'));
   printf("\nOriginal String (↴ is 3 bytes): %s\n", str1.constData());

   // 2
   printf("\nString - size storage    : %d",   str1.size_storage());
   printf("\nString - size code points: %d",   str1.size_codePoints());
   printf("\nString - size            : %d",   str1.size());
   printf("\nString - length          : %d\n", str1.length());

   if (str1.size_codePoints() != 5 ) {
      ok = false;
   }

   // 3
   CsString::CsString::const_iterator iter = str1.begin();
   iter = iter + 2;

   CsString::CsString str2(iter, str1.end());
   printf("\nCopy original string from begin() + 2: %s\n", str2.constData());

   if (str2 != CsString::CsString("CD") + UCHAR('↴')) {
      ok = false;
   }

   // 4
   CsString::CsString str4 = str1.substr(3, 2);
   printf("\nSubstring beginning at 3, length 2: %s", str4.constData());

   printf("\n\n");


   if (ok) {
      printf("End Unit Test Eight - PASSED\n\n");

   } else {
      printf("End Unit Test Eight - Failed\n\n");
      g_unitTest = false;

   }
}

void test_9()
{
   bool ok = true;
   printf("\n** Unit Test 9\n");

   CsString::CsString str1("ABCD (");
   str1.append(UCHAR('↴'));                  // 21b4
   str1.append(UCHAR(')'));

   CsString::CsString str2("ABCD (");
   str2.append(UCHAR('↵'));                  // 21b5
   str2.append(UCHAR(')'));

   printf("\nString 1  (unicode 21b4):  %s",   str1.constData());
   printf("\nString 2  (unicode 21b5):  %s\n", str2.constData());

   // 1
   printf("\nTest if String 1 == String 2:  ");

   if (str1 == str2) {
      printf("Test == is true");
      ok = false;

   }  else  {
      printf("Test == is false");

   }

   // 2
   printf("\nTest if String 1 != String 2:  ");

   if (str1 != str2) {
      printf("Test != is true");

   } else {
      printf("Test != is false");
      ok = false;
   }

   // 3
   printf("\nTest if String 1 >  String 2:  ");

   if (str1 > str2) {
      printf("Test >  is true");
      ok = false;

   } else {
      printf("Test >  is false");

   }

   // 4
   printf("\nTest if String 1 <  String 2:  ");

   if (str1 < str2) {
      printf("Test <  is true");

   } else {
      printf("Test <  is false");
      ok = false;

   }

   printf("\n\n");

   if (ok) {
      printf("End Unit Test Nine - PASSED\n\n");

   } else {
      printf("End Unit Test Nine - Failed\n\n");
      g_unitTest = false;

   }
}

void test_10()
{
   bool ok = true;
   printf("\n** Unit Test 10\n");

   CsString::CsString_utf16 str1("ABCD");
   str1.append(UCHAR('↴'));            // 3 bytes     21 B4
   str1.append(UCHAR('¿'));            // 2 bytes        BF
   str1.append('E');
   str1.append(UCHAR('𝅘𝅥𝅮'));            // 4 bytes  01 D1 60
   str1.append('F');

   // 1
   CsString::CsString str2;
   convert(str1, str2);

   printf("\nString Constructed using UTF16 then convert() to UTF8 : %s", str2.constData());

   CsString::CsChar c = str1[7];
   printf("\nCsChar 7 (unicode 01 d1 60) : %08x", c.unicode());

   printf("\n\n");

   if (c != UCHAR('𝅘𝅥𝅮')) {
      ok = false;
   }

   if (ok) {
      printf("End Unit Test Ten - PASSED\n\n");

   } else {
      printf("End Unit Test Ten - Failed\n\n");
      g_unitTest = false;

   }
}

void test_11()
{
   bool ok = true;
   printf("\n** Unit Test 11\n");

printf("\n Open test\n");

   if (ok) {
      printf("End Unit Test Eleven - PASSED\n\n");

   } else {
      printf("End Unit Test Eleven - Failed\n\n");
      g_unitTest = false;

   }
}

void test_12()
{
   bool ok = true;
   printf("\n** Unit Test 12\n");

printf("\n Open test\n");

   if (ok) {
      printf("End Unit Test Twelve - PASSED\n\n");

   } else {
      printf("End Unit Test Twelve - Failed\n\n");
      g_unitTest = false;

   }
}

void test_13()
{
   bool ok = true;
   printf("\n** Unit Test 13\n");

printf("\n Open test\n");

   if (ok) {
      printf("End Unit Test Thirteen - PASSED\n\n");

   } else {
      printf("End Unit Test Thirteen - Failed\n\n");
      g_unitTest = false;

   }
}

void test_14()
{
   bool ok = true;
   printf("\n** Unit Test 14\n");

printf("\n Open test\n");

   if (ok) {
      printf("End Unit Test Fourteen - PASSED\n\n");

   } else {
      printf("End Unit Test Fourteen - Failed\n\n");
      g_unitTest = false;

   }
}

void test_15()
{
   bool ok = true;
   printf("\n** Unit Test 15\n");


printf("\n Open test\n");


   if (ok) {
      printf("End Unit Test Fifteen - PASSED\n\n");

   } else {
      printf("End Unit Test Fifteen - Failed\n\n");
      g_unitTest = false;

   }
}

//  CsString &operator=(const CsString &str); where S1 is utf8 and S2 is utf16 -> should be a compile error
