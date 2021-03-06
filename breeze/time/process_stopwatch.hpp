// ===========================================================================
//                        Copyright 2021 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A process stopwatch.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_zxEwjLKMFWpcg3nLySAyPIQM4tweppgu
#define BREEZE_GUARD_zxEwjLKMFWpcg3nLySAyPIQM4tweppgu

#include "breeze/top_level_namespace.hpp"
#include <chrono>
#include <iosfwd>
#include <string>

namespace breeze_ns {

//      process_duration:
//      =================
//
//!\brief
//!     An aggregate holding the amounts of user and system time, and of
//!     wall-clock time, measured by process_stopwatch.
// ---------------------------------------------------------------------------
class process_duration
{
public:
    using               duration_type =
        std::chrono::duration< double, std::micro > ;

    duration_type       user   ;
    duration_type       system ;
    duration_type       wall   ;

    //!     \return
    //!         The percentage of `user + system` with respect to
    //!         `wall`. This is a non-negative number, but can be
    //!         greater than <tt>100</tt> if the system has multiple
    //!         CPUs or cores.
    // -----------------------------------------------------------------------
    double              percentage_to_total() const ;
    std::string         to_string() const ;
} ;

//!\brief
//!     Outputs a process_duration.
//!
//!     \relatedalso process_duration.
// ---------------------------------------------------------------------------
std::ostream &      operator <<( std::ostream & dest,
                                 process_duration const & d ) ;


//      process_stopwatch:
//      ==================
//
//!     \copybrief process_stopwatch.hpp
//!
//!     A stopwatch that allows measuring the amounts of system and user
//!     time for the current process.
//!
//!     It has an interface similar to that of `stopwatch`. The
//!     functionality of this class might be implemented via `Clock`s,
//!     using the general `stopwatch` facility. However, since we
//!     measure both system and user time, that would mean having to
//!     declare two different stopwatches in user code (with a `Clock`
//!     for system time and a `Clock` for user time), which not only is
//!     inconvenient but could introduce slight differences between the
//!     measures.
// ---------------------------------------------------------------------------
class process_stopwatch
{
public:
    //!     Deleted copy constructor.
    //!
    //!     \par Rationale
    //!
    //!     Same rationale as for `stopwatch`.
    // -----------------------------------------------------------------------
                        process_stopwatch( process_stopwatch const & )
                            = delete ;

    //!     Deleted copy assignment operator.
    //!
    //!     \par Rationale
    //!
    //!     Same rationale as for `stopwatch`.
    // -----------------------------------------------------------------------
    process_stopwatch & operator =( process_stopwatch const & ) = delete ;

    using               duration = process_duration::duration_type ;

    enum start_mode { auto_start, manual_start } ;

    //!     If `mode == auto_start`, calls start(); otherwise, it leaves
    //!     the stopwatch in an undefined state, in which the only
    //!     member functions that can be called are start() and the
    //!     destructor.
    // -----------------------------------------------------------------------
    explicit            process_stopwatch( start_mode mode = auto_start ) ;

    //!     Marks the start of a measurement.
    // -----------------------------------------------------------------------
    void                start() ;

    //!     \return
    //!         A structure with the amounts of time elapsed from the
    //!         last call to start().
    // -----------------------------------------------------------------------
    process_duration    elapsed() const ;

private:
    process_duration    m_start ;
} ;

}

#endif
