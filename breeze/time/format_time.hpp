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
#include "breeze/vocabulary/maybe.hpp"
#include <string>
#include <ctime>

namespace breeze_ns {

//      Predefined format strings:
//      ==========================
//
//!     These variables allow using meaningful names in combination with
//!     `format_time()`; e.g. you can write
//!
//!     ```
//!         format_time( iso8601_extended_date ) ;
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
//!     \brief
//!         The type (UTC/local) of the representation requested to
//!         `format_time()`.
// ---------------------------------------------------------------------------
enum class time_kind
{
    utc,
    local
} ;


//      format_time():
//      ==============
//
//!     \return
//!         The time corresponding to `time_stamp`, formatted according
//!         to `format`. `format` is interpreted as if passed to the
//!         `strftime()` standard function.
//!
//!     \see
//!         time_kind.
//!
//!     This is a simple tool for simple and quick formatting needs. You
//!     should use a more complete solution for more complex needs (but
//!     don't underestimate the good old `strftime()` ;-)).
//!
//!     \note
//!         This function is thread-safe and reentrant.
// ---------------------------------------------------------------------------
maybe< std::string >
                    format_time( std::string const & format,
                                 time_kind = time_kind::utc,
                               std::time_t time_stamp = std::time( nullptr ) ) ;

}

#endif
