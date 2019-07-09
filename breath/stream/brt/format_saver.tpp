// ===========================================================================
//                     Copyright 2007-2009 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

//      Some notes:
//      -----------
//
//      1. We use basic_ios::copyfmt() because we also want to save and
//      restore all the iword()/pword() data, and that function is the
//      only standard way to copy them. However, despite its name,
//      copyfmt() also copies information which have nothing to do with
//      the format; for instance, the exception mask. So we "undo"
//      part of its job. (In practice, copyfmt() "does too much": I
//      think there's a need for a more elementary function in the
//      stream interface, which copies the iword()/pword() data and
//      nothing else. Note, by the way, that the latter could be
//      provided at the ios_base level.)
//
//      2. The reason for the ios_base:: qualification in the call to
//      imbue() is the following:
//
//      both basic_ios and its base ios_base have an imbue() function.
//      (Neither is virtual.) The base one deals with the stream locale
//      (and callbacks). The derived one (which hides the base version)
//      deals with both the stream locale and the stream buffer locale
//      (if rdbuf() != 0) [C++03: 27.4.2.3 and 27.4.4.2]. Since
//      copyfmt() does not copy the stream buffer locale --only the
//      stream one-- we invoke the base version.
// ---------------------------------------------------------------------------

namespace breath {

//      note: the initialization m_store( user_stream.rdbuf() )
//      ensures that our m_store will not have badbit set and thus
//      that copyfmt() won't throw due to the copy of the exception mask
//      [1] (we don't want to eat _any_ exception it might throw,
//      differently from what we do in the destructor); for the rest
//      it is really irrelevant, first because we don't do any
//      input/output on m_store, then because rdbuf() isn't copied
//      back by copyfmt(), whatever its value is.
//
//      [1] unless user_stream has both a null rdbuf() AND
//      badbit set in the exception mask.
//
//      But in that case we'd have been called on to guard a stream
//      with no buffer (thus badbit set) and corresponding exception
//      enabled. It is of course a degenerate case in which failing to
//      save (= throwing an exception from the constructor of
//      format_saver) seems quite justified. --gps
// ---------------------------------------------------------------------------
//


//      Implementation note (constructor):
//      ----------------------------------
//
//      We use
//          m_store( user_stream.rdbuf() )
//      rather than
//          m_store( nullptr )
//      just to limit needlessly throwing: when a null stream buffer
//      pointer is passed, m_store is constructed in bad state; in that
//      case copyfmt()'ing when the badbit exception is enabled in the
//      source will cause an exception to be thrown and eaten. (For
//      the rest which form we use is irrelevant, first because we
//      don't do any input/output on m_store, second because rdbuf()
//      isn't copied back by copyfmt(), whatever its value is).
//
//      Of course it may still happen that rdbuf() is null, and the
//      fact is harmless (as already said, it just causes an
//      ios_failure_type exception to be thrown and caught
//      immediately)
// ---------------------------------------------------------------------------
template< typename Ch, typename Traits >
basic_format_saver< Ch, Traits >::basic_format_saver(
                                    std::basic_ios< Ch, Traits> & user_stream )
    :   m_user_stream( user_stream ),
        m_store( user_stream.rdbuf() )
{
    //      Note that there can still be an exception, for instance
    //      because copyfmt() fails to allocate memory in which to copy
    //      the iword()/pword() elements.
    // -----------------------------------------------------------------------
    try {
        m_store.copyfmt( m_user_stream ) ;
    } catch ( ios_failure_type & ) {
    }
}

template< typename Ch, typename Traits >
basic_format_saver< Ch, Traits >::~basic_format_saver() noexcept
{
    //      We prepare m_store for the data (besides those that
    //      copyfmt() won't copy anyway) we don't want to restore: tie,
    //      locale, exception mask.

    //      [tie]
    //
    //      I'm not sure whether the intent is for copyfmt() to copy the
    //      tie pointer, too. The standard looks unclear and as a matter
    //      of fact some libraries copy it (e.g. libstdc++), some don't.
    //      So we just play safe...
    //
    //      Note: the C++11 standard is clear: tie() shall be copied.
    // -----------------------------------------------------------------------
    try {
        m_store.tie( m_user_stream.tie() ) ;
    } catch ( ... ) {
    }

    //      [locale]
    //
    //      To avoid needless invocations of callbacks I had an if here:
    //
    //        if ( m_store.ios_base::getloc() != m_user_stream.getloc() )
    //
    //      which I've removed due to what I think is a bug in VC8's
    //      Dinkum lib:
    //
    //        std::locale const & tmp( std::locale( "C" ) ) ;
    //        std::locale loc( tmp, new dummy_facet ) ;
    //
    //      constructs, contrarily to [lib.locale], a named locale loc
    //      (with name "C") and this in turn makes tmp == loc yield
    //      true, even though the locales must clearly be different.
    // -----------------------------------------------------------------------
    {
        //      So that the locale is NOT restored
        //      (but what about callbacks? -gps).
        // -------------------------------------------------------------------
        m_store.std::ios_base::imbue( m_user_stream.getloc() ) ;
    }

    //      [exception mask]
    // -----------------------------------------------------------------------
    try {
        m_store.exceptions( m_user_stream.exceptions() ) ; // ok?? and gps what can this throw?
    } catch ( ios_failure_type & ) {
    }

    //      The question arises here of what state the stream should be
    //      left in if copyfmt() exits with an exception (not due to the
    //      last assignment, which copies the exception mask).
    //
    //      The standard provides NO GUARANTEE.
    //      The standard doesn't require the strong guarantee but it is
    //      easy to provide: none of the callbacks is allowed to throw
    //      [(lib.)ios.base.callback] and the only reasonable source of
    //      such an exception is a dynamic allocation. So the
    //      implementation can attempt the allocation before anything
    //      else and do nothing if it fails. But is this the best thing
    //      to do? It could be argued that it would be better to copy
    //      the "normal" members (fmtflags, fill, etc.) anyway, leaving
    //      only the extended info uncopied.
    //
    //      An idea for C++0x --to be verified-- is using the new
    //      swap(basic_ios&& rhs) member function:
    //
    //        temp.copyfmt( m_store ) ;
    //        temp.swap( m_user_stream ) ;        // [FUTURE], [C++11]
    //
    //      This way, we could still guarantee a copy of the normal
    //      members when copyfmt() fails.
    // -----------------------------------------------------------------------
    try {
        m_user_stream.copyfmt( m_store ) ;  // what about callbacks?
    } catch ( ios_failure_type & ) {
        // OK
    } catch ( ... ) {
        //      NOT OK: an exception not due to setting the state so an
        //      allocation error or something else: we don't know in
        //      what state the stream is now :-( gps
        // -------------------------------------------------------------------
        try {
            m_user_stream.setstate( std::ios_base::badbit ) ;
        } catch ( ... ) {
        }
    }
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
