/***********************************************************************
*
* Copyright (c) 2017-2025 Barbara Geller
* Copyright (c) 2017-2025 Ansel Sermersheim
*
* This file is part of CsString.
*
* CsString is free software which is released under the BSD 2-Clause license.
* For license details refer to the LICENSE provided with this project.
*
* CsString is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#define CATCH_CONFIG_EXPERIMENTAL_REDIRECT

#include <cs_string.h>

#include <catch2/catch.hpp>

namespace Catch {

   template <>
   struct StringMaker<CsString::CsString_utf8> {
      static std::string convert(const CsString::CsString_utf8 &value) {
         return std::string(value.storage_begin(), value.storage_end());
      }
   };

   template <>
   struct StringMaker<CsString::CsString_utf16> {
      static std::string convert(const CsString::CsString_utf16 &value) {
         const CsString::CsString_utf8 tmp(value.begin(), value.end());
         return std::string(tmp.storage_begin(), tmp.storage_end());
      }
   };
}
