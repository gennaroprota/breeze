// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2021 Gennaro Prota
//                         Copyright 1997 James Kanze
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/benchmarking/bench_harness.hpp"
#include "breeze/diagnostics/assert.hpp"
#include "breeze/time/process_timer.hpp"
#include <ostream>

namespace breeze_ns {
namespace           {

void
display_header( std::ostream &  out,
                char const *    label,
                long            loop_count )
{
    out << "Benchmarking" ;
    if ( label != nullptr ) {
        out << ' ' << label ;
    }
    out << " ("
        << loop_count
        << " iterations)..."
        << std::endl ;
}

}

long                bench_harness::s_loop_count ;
bench_harness::duration_type
                    bench_harness::s_user_overhead ;
bench_harness::duration_type
                    bench_harness::s_system_overhead ;

bench_harness::bench_harness() noexcept = default ;

bench_harness::~bench_harness() noexcept = default ;

void
bench_harness::operator()()
{
}

process_duration
bench_harness::run()
{
    BREEZE_ASSERT( s_loop_count > 0 ) ;

    ( *this )() ;           // Ensure that the code is in main memory,
                            // and not in the virtual memory, on disk.

    process_timer       timer ;
    for ( long i = 0 ; i < s_loop_count ; ++ i ) {
        ( *this )() ;
    }

    process_duration    elapsed = timer.elapsed() ;
    elapsed.user   -= s_user_overhead ;
    elapsed.system -= s_system_overhead ;

    return elapsed ;
}

void
bench_harness::run( std::ostream &      out,
                    char const *        label,
                    display_iteration    )
{
    display_header( out, label, s_loop_count ) ;
    process_duration    elapsed = run() ;
    elapsed.user   /= s_loop_count ;
    elapsed.system /= s_loop_count ;
    elapsed.wall   /= s_loop_count ;

    out << "    Times per iteration:"
        << std::endl
        << elapsed
        << std::endl ;
}

void
bench_harness::run( std::ostream &      out,
                    char const *        label,
                    display_total        )
{
    display_header( out, label, s_loop_count ) ;
    process_duration const
                        elapsed = run() ;

    out << "    Total times:"
        << std::endl
        << elapsed
        << std::endl ;
}

void
bench_harness::set_loop_count( long count )
{
    BREEZE_ASSERT( count > 0 ) ;

    s_loop_count = count ;

    //      Zero out the overheads, because run() will subtract them.
    // -----------------------------------------------------------------------
    s_user_overhead = s_system_overhead = duration_type( 0 ) ;

    process_duration const
                        overhead = bench_harness().run() ;
    s_user_overhead   = overhead.user ;
    s_system_overhead = overhead.system ;
}

}
