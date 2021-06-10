// ===========================================================================
//                        Copyright 2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A thin wrapper around `std::strftime()`, plus some
//!            predefined format strings.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_wR9yYhDtICLHOJ6c2LmBkhMWoYoaeVkS
#define BREEZE_GUARD_wR9yYhDtICLHOJ6c2LmBkhMWoYoaeVkS

#include "breeze/top_level_namespace.hpp"
#include <chrono>
#include <iosfwd>
#include <string>

namespace breeze_ns {

//      Predefined format strings:
//      ==========================
//
//!     These variables allow using meaningful names in combination with
//!     `format_time()`; e.g. you can write
//!
//!     ```
//!         format_time( iso8601_extended_date, std::cout ) ;
//!     ```
//!
//!     Only a small number of format strings are provided.
//!
//!     \note
//!         These are not `std::string`s, to avoid any order of
//!         initialization issues. But this means that e.g. concatening
//!         their values may be a bit less straightforward.
// ---------------------------------------------------------------------------

//!     Gives a calendar date in the format <tt>YYYYMMDD</tt>.
// ---------------------------------------------------------------------------
extern char const   iso8601_basic_date[] ;

//!     Gives a calendar date in the format <tt>YYYY-MM-DD</tt>.
// ---------------------------------------------------------------------------
extern char const   iso8601_extended_date[] ;

//!     Gives a time of the day in the format <tt>hhmmss</tt>.
// ---------------------------------------------------------------------------
extern char const   iso8601_basic_time[] ;

//!     Gives a time of the day in the format <tt>hh:mm:ss</tt>.
// ---------------------------------------------------------------------------
extern char const   iso8601_extended_time[] ;


//      time_kind:
//      ==========
//
//!\brief
//!     The type (UTC/local) of the representation requested to
//!     `format_time()`.
// ---------------------------------------------------------------------------
enum class time_kind
{
    utc,
    local
} ;


//      format_time():
//      ==============
//
//!\brief
//!     Produces a textual representation of a
//!     `std::chrono::system_clock::time_point`.
//!
//!     This function is a wrapper around `std::put_time()`.
//!
//!     \param format
//!         A string specifying how to format the result.
//!         `format.c_str()` is passed to `std::put_time()` together
//!         with a broken-down time structure (`::tm`) which corresponds
//!         to the specified `time_point`. The `tm` structure is
//!         obtained in a thread-safe and reentrant way.
//!
//!     \param dest
//!         The stream to which the time representation is output.
//!
//!     \param kind
//!         The kind of time (UTC or local) that `time_point`
//!         represents.
//!
//!     \param time_point
//!         The `time point` to be represented.
//!
//!     \see
//!         time_kind.
//!
//!     This is a simple tool for simple and quick formatting needs. You
//!     should use a more complete solution for more complex needs.
//!
//!     \note
//!         This function is thread-safe and reentrant.
// ---------------------------------------------------------------------------
void                format_time(
    std::string const & format,
    std::ostream & dest,
    time_kind kind = time_kind::local,
    std::chrono::system_clock::time_point const & time_point =
    std::chrono::system_clock::now() ) ;

}

#endif
