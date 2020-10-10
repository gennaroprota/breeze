// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//                         Copyright 2004 James Kanze
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A helper class for writing stream inserters that output
//!            directly through the \c streambuf.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_tEOGCROHt16yX1uloiIgGQGhjyWIPWlv
#define BREATH_GUARD_tEOGCROHt16yX1uloiIgGQGhjyWIPWlv

#include "breath/top_level_namespace.hpp"

#include <ostream>
#include <ios>     // for std::streamsize

namespace breath_ns {

//      inserter:
//      =========
//
//!\copybrief inserter.hpp
//!
//!     This class encapsulates some of the details to write an inserter
//!     for a user-defined type that uses the stream buffer layer
//!     directly.
//!
//!     The idea for such a helper class is by James Kanze. I tweaked
//!     his idea a bit, for instance by also encapsulating the <code>
//!     ostream</code>'s \c sentry.
//!
//!     For a usage example, see the stream inserter of the <code>crc
//!     </code> template.
//!
//!     The class allows reducing the high amount of duplication
//!     otherwise implied in writing such inserters, and makes your
//!     inserter definitely shorter and easier to read. But I guess
//!     duplication can be further reduced (or I hope so).
//!
//!     \warning
//!         Once an object of this class is constructed, do not call any
//!         I/O functions from the formatting layer, until the object is
//!         destroyed. Doing that might cause a deadlock.
// ---------------------------------------------------------------------------
class inserter
{
public:
    //!     Defines the behavior of the inserter with regard to whether
    //!     it resets the destination stream width or not.
    // -----------------------------------------------------------------------
    enum width_reset
    {
        reset_width,
        dont_reset_width
    } ;

    //!     \param dest
    //!         The stream to which all inserted characters will be
    //!         sent (called the <i>destination stream</i> throughout
    //!         the documentation of this class).
    //!
    //!     \param wr
    //!         See the documentation of the destructor.
    //!
    //!     \throw
    //!         This constructor might throw an exception originating
    //!         from the \c sentry constructor.
    // -----------------------------------------------------------------------
    explicit            inserter( std::ostream & dest,
                                  width_reset    wr = reset_width ) ;

    //!\{
    //!     Copy members are deleted.
    // -----------------------------------------------------------------------
                        inserter(   inserter const & ) = delete ;
    inserter &          operator =( inserter const & ) = delete ;
    //!\}

    //!     If \c sentry_is_ok() returns \c true, and \c reset_width was
    //!     passed to the constructor, sets the width of the destination
    //!     stream to <tt>0</tt>. Note that this is also done if the
    //!     inserter emits an exception, which is different from e.g.
    //!     what a typical implementation of a standard library inserter
    //!     does (it's not clear to me whether the standard requires
    //!     this or that behavior, but I consider mine easier to reason
    //!     about, as the reset is unconditional).
    // -----------------------------------------------------------------------
                        ~inserter() noexcept ;

    //!     Tells if the sentry is OK.
    // -----------------------------------------------------------------------
    bool                sentry_is_ok() const noexcept ;

    //!     \param c
    //!         The character to be output.
    //!
    //!     \pre
    //!         sentry_is_ok()
    //!
    //!     If the destination stream converts to \c true (i.e. if
    //!     <code>! fail()</code>), calls <code>sputc( c )</code> on its
    //!     underlying stream buffer, setting \c badbit (which may
    //!     throw) if \c sputc() fails.
    // -----------------------------------------------------------------------
    void                put( char c ) ;

    //!     \param source
    //!         A pointer to the characters to be output.
    //!
    //!     \param count
    //!         The number of characters.
    //!
    //!     \pre
    //!          - sentry_is_ok()
    //!          - count >= 0
    //!
    //!     If the destination stream converts to \c true (i.e. if
    //!     <code>! fail()</code>), calls <code>sputn( source, count )
    //!     </code> on its underlying stream buffer, setting \c badbit
    //!     (which may throw) if the return value is not equal to \c
    //!     count.
    // -----------------------------------------------------------------------
    void                put( char const * source, std::streamsize count ) ;

    //!     \param count
    //!         The number of characters to be output.
    //!
    //!     If the destination stream converts to \c true (i.e. if
    //!     <code>! fail()</code>), outputs \c count times the fill
    //!     character of the destination stream, using either \c sputc()
    //!     or \c sputn(), setting \c badbit (which may throw) if it is
    //!     unable to.
    //!
    //!     The number of characters may be zero, or even negative, in
    //!     which case nothing is output. (Roughly speaking, the idea is
    //!     to be able to pass something like <code>stream.width() -
    //!     generated.count</code> as an argument.)
    // -----------------------------------------------------------------------
    void                pad( std::streamsize count ) ;

private:
    std::ostream &      m_dest ;
    std::ostream::sentry const
                        m_sentry ;
    bool const          m_reset_width ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
