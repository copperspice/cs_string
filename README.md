## CsString

### Introduction

CsString is a standalone library which provides unicode aware string support.

The CsBasicString class is a templated class which provides unicode aware string support. The encoding, such
as UTF-8 or UTF-16, is passed to the CsBasicString template. The following typedefs are provided for convenience.

    using CsString       = CsBasicString<utf8>;
    using CsString_utf8  = CsBasicString<utf8>;
    using CsString_utf16 = CsBasicString<utf16>;

### System Requirements

To use CsString you will need a C++17 compiler and a C++17 standard library.

Currently uses the CMake build system for building and running the unit test suite. The library has been tested with
clang sanitizer and a major code review.

### Documentation

Class level documentation for CsString is available on the CopperSpice website:

https://www.copperspice.com/docs/cs_string/index.html


### Presentations

Our YouTube channel contains over 65 videos about C++, programming fundamentals, Unicode/Strings, multithreading,
graphics, CopperSpice, DoxyPress, and other software development topics.

https://www.youtube.com/copperspice
Links to additional videos can be found on our website.

https://www.copperspice.com/presentations.html


### Authors / Contributors

* **Ansel Sermersheim**
* **Barbara Geller**


### License

This library is released under the BSD 2-clause license. For more information refer to the LICENSE file provided with
this project.


### References

* Website:  https://www.copperspice.com
* Twitter:  https://twitter.com/copperspice_cpp
* Email:    info@copperspice.com

* Github:   https://github.com/copperspice

* Forum:    https://forum.copperspice.com
* Journal:  https://journal.copperspice.com
