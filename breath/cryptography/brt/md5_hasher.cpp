// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/cryptography/md5_hasher.hpp"

namespace breath {
namespace        {

typedef md5_engine::word_type
                        word_type ;

//
//      Note:
//          this is not a general rotate-left function: it assumes
//          (which always happens with MD5) that 0 < amount < 32.
//
template< int amount >
word_type
md5_rotate_left( word_type w )
{
    return ( w << amount ) | ( w >> ( md5_engine::word_width - amount ) ) ;
}

//      Auxiliary functions described in 3.4 Step 4
//
//      Except for the parity function there seems to be no significant
//      name we can give them. Initially these were standalone inline
//      functions (as opposed to class template members), e.g.:
//
//        inline word aux_f( word x, word y, word z )
//        {
//            return x & y | ~x & z ;
//        }
//        inline word aux_g() ...
//        inline word aux_h() ...
//
//      but few compilers seemed to be able to inline them when an array
//      was formed with their addresses, despite the inlining being
//      proven beneficial. That's why we "index" by template parameter.
// -------------------------------------------------------------------------
template< int round > struct aux_f
{
    static word_type    f( word_type, word_type, word_type ) ;
} ;

template<>
word_type
aux_f< 0 >::f( word_type x, word_type y, word_type z )
{
    return (x & y ) + (~x & z) ;
}

template<>
word_type
aux_f< 1 >::f( word_type x, word_type y, word_type z )
{
    return aux_f< 0 >::f( z, x, y ) ;
}

template<>
word_type
aux_f< 2 >::f( word_type x, word_type y, word_type z )
{
    return x ^ y ^ z ;  // aka parity( x, y, z )
}

template<>
word_type
aux_f< 3 >::f( word_type x, word_type y, word_type z )
{
    return y ^ ( x | ~z ) ;
}

template< int round, int shift >
void
core_fn( word_type & a, word_type b, word_type c, word_type d, word_type input )
{
    a = b + md5_rotate_left< shift >(
                       a + aux_f< round >::f( b, c, d ) + input ) ;
}

}

void
md5_engine::init_state( state_type & state )
{
    state[ 0 ] = 0x67452301 ;
    state[ 1 ] = 0xefcdab89 ;
    state[ 2 ] = 0x98badcfe ;
    state[ 3 ] = 0x10325476 ;
}

void md5_engine::process_block( state_type & state, block_type const & x )
{
    enum { s11 = 7, s12 = 12, s13 = 17, s14 = 22,
           s21 = 5, s22 =  9, s23 = 14, s24 = 20,
           s31 = 4, s32 = 11, s33 = 16, s34 = 23,
           s41 = 6, s42 = 10, s43 = 15, s44 = 21 } ;

    word_type           a( state[ 0 ] ) ;
    word_type           b( state[ 1 ] ) ;
    word_type           c( state[ 2 ] ) ;
    word_type           d( state[ 3 ] ) ;

    // Round 1
    core_fn< 0, s11 >( a, b, c, d, x[  0 ] + 0xd76aa478 ) ; // 1
    core_fn< 0, s12 >( d, a, b, c, x[  1 ] + 0xe8c7b756 ) ;
    core_fn< 0, s13 >( c, d, a, b, x[  2 ] + 0x242070db ) ;
    core_fn< 0, s14 >( b, c, d, a, x[  3 ] + 0xc1bdceee ) ;
    core_fn< 0, s11 >( a, b, c, d, x[  4 ] + 0xf57c0faf ) ;
    core_fn< 0, s12 >( d, a, b, c, x[  5 ] + 0x4787c62a ) ;
    core_fn< 0, s13 >( c, d, a, b, x[  6 ] + 0xa8304613 ) ;
    core_fn< 0, s14 >( b, c, d, a, x[  7 ] + 0xfd469501 ) ;
    core_fn< 0, s11 >( a, b, c, d, x[  8 ] + 0x698098d8 ) ;
    core_fn< 0, s12 >( d, a, b, c, x[  9 ] + 0x8b44f7af ) ;
    core_fn< 0, s13 >( c, d, a, b, x[ 10 ] + 0xffff5bb1 ) ;
    core_fn< 0, s14 >( b, c, d, a, x[ 11 ] + 0x895cd7be ) ;
    core_fn< 0, s11 >( a, b, c, d, x[ 12 ] + 0x6b901122 ) ;
    core_fn< 0, s12 >( d, a, b, c, x[ 13 ] + 0xfd987193 ) ;
    core_fn< 0, s13 >( c, d, a, b, x[ 14 ] + 0xa679438e ) ;
    core_fn< 0, s14 >( b, c, d, a, x[ 15 ] + 0x49b40821 ) ;

    // Round 2
    core_fn< 1, s21 >( a, b, c, d, x[  1 ] + 0xf61e2562 ) ; // 17
    core_fn< 1, s22 >( d, a, b, c, x[  6 ] + 0xc040b340 ) ;
    core_fn< 1, s23 >( c, d, a, b, x[ 11 ] + 0x265e5a51 ) ;
    core_fn< 1, s24 >( b, c, d, a, x[  0 ] + 0xe9b6c7aa ) ;
    core_fn< 1, s21 >( a, b, c, d, x[  5 ] + 0xd62f105d ) ;
    core_fn< 1, s22 >( d, a, b, c, x[ 10 ] +  0x2441453 ) ;
    core_fn< 1, s23 >( c, d, a, b, x[ 15 ] + 0xd8a1e681 ) ;
    core_fn< 1, s24 >( b, c, d, a, x[  4 ] + 0xe7d3fbc8 ) ;
    core_fn< 1, s21 >( a, b, c, d, x[  9 ] + 0x21e1cde6 ) ;
    core_fn< 1, s22 >( d, a, b, c, x[ 14 ] + 0xc33707d6 ) ;
    core_fn< 1, s23 >( c, d, a, b, x[  3 ] + 0xf4d50d87 ) ;
    core_fn< 1, s24 >( b, c, d, a, x[  8 ] + 0x455a14ed ) ;
    core_fn< 1, s21 >( a, b, c, d, x[ 13 ] + 0xa9e3e905 ) ;
    core_fn< 1, s22 >( d, a, b, c, x[  2 ] + 0xfcefa3f8 ) ;
    core_fn< 1, s23 >( c, d, a, b, x[  7 ] + 0x676f02d9 ) ;
    core_fn< 1, s24 >( b, c, d, a, x[ 12 ] + 0x8d2a4c8a ) ;

    // Round 3
    core_fn< 2, s31 >( a, b, c, d, x[  5 ] + 0xfffa3942 ) ; // 33
    core_fn< 2, s32 >( d, a, b, c, x[  8 ] + 0x8771f681 ) ;
    core_fn< 2, s33 >( c, d, a, b, x[ 11 ] + 0x6d9d6122 ) ;
    core_fn< 2, s34 >( b, c, d, a, x[ 14 ] + 0xfde5380c ) ;
    core_fn< 2, s31 >( a, b, c, d, x[  1 ] + 0xa4beea44 ) ;
    core_fn< 2, s32 >( d, a, b, c, x[  4 ] + 0x4bdecfa9 ) ;
    core_fn< 2, s33 >( c, d, a, b, x[  7 ] + 0xf6bb4b60 ) ;
    core_fn< 2, s34 >( b, c, d, a, x[ 10 ] + 0xbebfbc70 ) ;
    core_fn< 2, s31 >( a, b, c, d, x[ 13 ] + 0x289b7ec6 ) ;
    core_fn< 2, s32 >( d, a, b, c, x[  0 ] + 0xeaa127fa ) ;
    core_fn< 2, s33 >( c, d, a, b, x[  3 ] + 0xd4ef3085 ) ;
    core_fn< 2, s34 >( b, c, d, a, x[  6 ] +  0x4881d05 ) ;
    core_fn< 2, s31 >( a, b, c, d, x[  9 ] + 0xd9d4d039 ) ;
    core_fn< 2, s32 >( d, a, b, c, x[ 12 ] + 0xe6db99e5 ) ;
    core_fn< 2, s33 >( c, d, a, b, x[ 15 ] + 0x1fa27cf8 ) ;
    core_fn< 2, s34 >( b, c, d, a, x[  2 ] + 0xc4ac5665 ) ;

    // Round 4
    core_fn< 3, s41 >( a, b, c, d, x[  0 ] + 0xf4292244 ) ; // 49
    core_fn< 3, s42 >( d, a, b, c, x[  7 ] + 0x432aff97 ) ;
    core_fn< 3, s43 >( c, d, a, b, x[ 14 ] + 0xab9423a7 ) ;
    core_fn< 3, s44 >( b, c, d, a, x[  5 ] + 0xfc93a039 ) ;
    core_fn< 3, s41 >( a, b, c, d, x[ 12 ] + 0x655b59c3 ) ;
    core_fn< 3, s42 >( d, a, b, c, x[  3 ] + 0x8f0ccc92 ) ;
    core_fn< 3, s43 >( c, d, a, b, x[ 10 ] + 0xffeff47d ) ;
    core_fn< 3, s44 >( b, c, d, a, x[  1 ] + 0x85845dd1 ) ;
    core_fn< 3, s41 >( a, b, c, d, x[  8 ] + 0x6fa87e4f ) ;
    core_fn< 3, s42 >( d, a, b, c, x[ 15 ] + 0xfe2ce6e0 ) ;
    core_fn< 3, s43 >( c, d, a, b, x[  6 ] + 0xa3014314 ) ;
    core_fn< 3, s44 >( b, c, d, a, x[ 13 ] + 0x4e0811a1 ) ;
    core_fn< 3, s41 >( a, b, c, d, x[  4 ] + 0xf7537e82 ) ;
    core_fn< 3, s42 >( d, a, b, c, x[ 11 ] + 0xbd3af235 ) ;
    core_fn< 3, s43 >( c, d, a, b, x[  2 ] + 0x2ad7d2bb ) ;
    core_fn< 3, s44 >( b, c, d, a, x[  9 ] + 0xeb86d391 ) ; // 64

    state[ 0 ] += a ;
    state[ 1 ] += b ;
    state[ 2 ] += c ;
    state[ 3 ] += d ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
