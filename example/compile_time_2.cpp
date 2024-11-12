// Copyright 2024 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/hash2/sha2.hpp>
#include <boost/hash2/hash_append.hpp>
#include <iostream>

extern constexpr char const license[] =

"Boost Software License - Version 1.0 - August 17th, 2003\n"
"\n"
"Permission is hereby granted, free of charge, to any person or organization\n"
"obtaining a copy of the software and accompanying documentation covered by\n"
"this license (the \"Software\") to use, reproduce, display, distribute,\n"
"execute, and transmit the Software, and to prepare derivative works of the\n"
"Software, and to permit third-parties to whom the Software is furnished to\n"
"do so, all subject to the following:\n"
"\n"
"The copyright notices in the Software and this entire statement, including\n"
"the above license grant, this restriction and the following disclaimer,\n"
"must be included in all copies of the Software, in whole or in part, and\n"
"all derivative works of the Software, unless such copies or derivative\n"
"works are solely in the form of machine-executable object code generated by\n"
"a source language processor.\n"
"\n"
"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
"FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT\n"
"SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE\n"
"FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,\n"
"ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER\n"
"DEALINGS IN THE SOFTWARE.\n"

;

constexpr unsigned char secret[] = {
    0xA4, 0x80, 0x0E, 0xE8, 0x20, 0x0B, 0x7C, 0x9A,
    0xF1, 0x3E, 0x3D, 0xEC, 0x64, 0x4F, 0x64, 0xCA,
    0x33, 0xCC, 0x84, 0xC8, 0x34, 0xE3, 0x08, 0xAE,
    0x92, 0x89, 0xEB, 0xD0, 0x47, 0x39, 0x87, 0xD8,
};

template<std::size_t N> constexpr auto hmac_sha2_256( char const(&s)[ N ] )
{
    boost::hash2::hmac_sha2_256 hmac( secret, sizeof(secret) );

    // N-1, in order to not include the null terminator
    boost::hash2::hash_append_range( hmac, {}, s, s + N - 1 );

    return hmac.result();
}

constexpr auto license_mac = hmac_sha2_256( license );

int main()
{
    std::cout << "License authentication code: " << license_mac << std::endl;
}
