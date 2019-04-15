// =========================================================================
//                       Copyright 2015 Gennaro Prota
//                        Copyright 2000 James Kanze
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief A string with non-printable chars escaped.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_03plpMI2VjgMEb2QhWRYStxFLQ2UshCk
#define BREATH_GUARD_03plpMI2VjgMEb2QhWRYStxFLQ2UshCk

#include "breath/idiom/maybe.hpp"
#include <iosfwd>
#include <string>

namespace breath {

//      printable_string:
//      =================
//
//!     Represents a string that prints to an \c ostream without
//!     non-printable characters.
//!
//!     Any character outside the range [0x20, 0x7e] is considered
//!     non-printable and is displayed either using a
//!     simple-escape-sequence or an escape sequence of the form
//!     <tt>\\x...</tt>. The goal is, for instance, to send the output
//!     to a log and then read it from another machine. The number of
//!     digits in the hexadecimal escape sequence is
//!     <code>std::ceil( CHAR_ BIT / 4.0 )</code> (they are left-padded
//!     with zeroes); note that this is different from character and
//!     string literals, where there's no limit to the number of
//!     hexadecimal digits. Thus, to read a \c %printable_string
//!     unambiguously all that is needed is to know the value of \c
//!     CHAR_BIT on the source machine.
//!
//!     A \c %printable_string can be constructed "from a non-string"
//!     (i.e. from a null pointer): this is useful for debugging purposes.
//!     In this special case, only, the \c %printable_string outputs
//!     without quotes. Otherwise, it is always enclosed in double
//!     quotes and a double quote character in the string is escaped,
////    as is usual in C++.
//!
//!     Instances of this class maintain a copy of the string, so the
//!     user does not have to worry about the lifetime of the object
//!     given to the constructor.
// ---------------------------------------------------------------------------
class printable_string
{
public:
    explicit            printable_string( char const * ) ;
    explicit            printable_string( std::string const & ) ;

private:
    friend std::ostream &
                    operator <<( std::ostream & dest,
                                 printable_string const & ) ;

    maybe< std::string >
                        m_value ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
