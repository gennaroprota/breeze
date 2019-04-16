// ===========================================================================
//                     Copyright 2007-2009 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A saver/restorer for stream formatting info.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_Z4DMqDrKXOIFeJ4e9o0vyecTiAF4rmvr
#define BREATH_GUARD_Z4DMqDrKXOIFeJ4e9o0vyecTiAF4rmvr

#include "breath/idiom/declare_non_copyable.hpp"
#include <ios>

namespace breath {

//      basic_format_saver:
//      ===================
//
//!     RAII-based "guard" (saver/restorer) of a stream object's
//!     formatting info.
//!
//!     An instance of this template class saves the formatting state
//!     of a stream object in its constructor and restores it in its
//!     destructor.
//!
//!     Note: do not confuse what we call here the "formatting info"
//!     or "formatting state" (the set of all info which affect
//!     formatting), with the "state" of a stream object, which
//!     reflects the integrity of its stream buffer and is of no
//!     concern to this class.
//!
//!
//!     This facility restores everything except:
//!
//!      - integrity state ( \c rdstate() )
//!        since it represents errors; restoring would be a non-sense
//!
//!      - pointer to stream buffer ( \c rdbuf() )
//!      - stream and stream buffer locale
//!      - exception mask
//!      - synchronized output stream ( \c tie() )
//!
//!
//!     Rationale:
//!     ----------
//!
//!     We chose to have a single class to save all the relevant
//!     format information, rather than one class for each attribute
//!     (as, for instance, some Boost facilities do) for two reasons:
//!
//!     - the resulting code is significantly shorter and simpler,
//!       with obvious benefits on maintenance
//!
//!     - maintenance of client code is simplified too: if a function
//!       modifies more formatting flags than it initially did, the
//!       maintainer need not remember to correspondingly add more
//!       format savers (or use a new, more comprehensive, format
//!       saver type)
//!
//!     About locales:
//!
//!     Instances of the class \c ios_base contain a locale object.
//!     Instances of \c basic_ios (which have an \c ios_base
//!     subobject) hold a pointer the stream buffer, which has a
//!     locale too (coding conversions).
//!
//!     \c basic_ios::copyfmt copies the stream locale (member of
//!     \c ios_base), but not the stream-buffer one. Note, BTW, that
//!     it does so without triggering the \c imbue_event.
//!
//!     I meditated at length what to do about locales, because they
//!     also deal with non formatting-related stuff, such as ctype:
//!     actually, we should restore only the facets which affect
//!     formatting. In the end, there wasn't enough experience with
//!     the problem so the choice, at least for now, is to not restore
//!     any locale.
//!
//!     Credits:
//!     --------
//!
//!     This template was born as a further elaboration of a class by
//!     James Kanze, named \c IOSave. And it was a comment in his code
//!     to suggest using \c copyfmt, in order to save the additional
//!     stream info. James also gave, as usual, excellent feedback on
//!     various design issues, in particular about locales and imbue.
// -------------------------------------------------------------------------
template< typename Ch, typename Traits = std::char_traits< Ch > >
class basic_format_saver
{
public:
    BREATH_DECLARE_NON_COPYABLE( basic_format_saver )

    explicit            basic_format_saver( std::basic_ios< Ch, Traits > & ) ;
                        ~basic_format_saver() noexcept ;

private:
    typedef Ch          char_type ;
    typedef std::basic_ios< Ch, Traits >
                        ios_type ;
    typedef typename ios_type::failure
                        ios_failure_type ;

    ios_type &          m_user_stream ;
    ios_type            m_store ;
} ;

typedef basic_format_saver< char >
                    format_saver ;
typedef basic_format_saver< wchar_t >
                    wide_format_saver ;

}

#include "brt/format_saver.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
