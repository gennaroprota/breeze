// ===========================================================================
//                        Copyright 2021 Gennaro Prota
//                         Copyright 1997 James Kanze
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A harness for running benchmarks.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_pK7uzE6NUWfbHZgK5IMlmbqchOgU9SrW
#define BREEZE_GUARD_pK7uzE6NUWfbHZgK5IMlmbqchOgU9SrW

#include "breeze/top_level_namespace.hpp"
#include "breeze/time/process_timer.hpp"
#include <iosfwd>

namespace breeze_ns {

//      bench_harness:
//      ==============
//
//!     \copybrief bench_harness.hpp
//!
//!     This class is used as a harness for measuring execution speed.
//!     Typically, the user will set the number of iterations to run by
//!     means of the static function `set_loop_count()`, then invoke one
//!     of the `run()` functions to execute the test.
//!
//!     To create a test, the user derives from the class, implementing
//!     the virtual function `operator ()()`. During the test, this
//!     function will be invoked as many times as was specified with
//!     `set_loop_count()`. According to which `run()` function is
//!     called, the elapsed times will be returned, or either the total
//!     times or the times per iteration will be displayed.
//!
//!     In `set_loop_count()`, a trial run is performed with an empty
//!     function. The user and system times (but not the wall-clock
//!     time) required by this trial will be subtracted from the
//!     respective execution times in later tests.
//!
//!     The use of a virtual function should (we hope) prevent the
//!     compiler from detecting that the results of calling the function
//!     aren't actually used, and from thus optimizing away the function
//!     completely. Supposing, of course, that each of the individual
//!     calls stores a result in either the derived object or in a
//!     global variable. In addition, each test run calls
//!     `operator ()()` once before starting any measurement, to preload
//!     the cache.
//!
//!     This class supports neither copy nor assignment.
// ---------------------------------------------------------------------------
class bench_harness
{
public:
    //!\{
    //!     \name Display parameters
    //!
    //!     The following types are used to select (by means of function
    //!     overload resolution) between the two possibilities for
    //!     display.
    // -----------------------------------------------------------------------
    //!     Displays the times used for a single iteration.
    // -----------------------------------------------------------------------
    enum display_iteration { iteration_time } ;
    //!     Displays the total times used.
    // -----------------------------------------------------------------------
    enum display_total     { total_time     } ;
    //!\}

    //!     Deleted copy constructor.
    // -----------------------------------------------------------------------
                        bench_harness( bench_harness const & ) = delete ;

    //!     Deleted copy assignment operator.
    // -----------------------------------------------------------------------
    bench_harness &     operator =( bench_harness const & ) = delete ;

    //!\brief
    //!     Destroys a `bench_harness`.
    // -----------------------------------------------------------------------
    virtual             ~bench_harness() noexcept ;

    //      run():
    //      ------
    //
    //!\brief
    //!     Executes the benchmark and returns the results.
    //!
    //!     Calls `operator ()()` a number of times equal to <tt>1</tt>
    //!     plus the argument last passed to `set_loop_count()`. The
    //!     first call has just the purpose of preloading the cache; the
    //!     remaining calls are benchmarked.
    //!
    //!     \return
    //!         A `process_duration` holding the times actually spent
    //!         executing the code under test. The overhead of looping
    //!         and of the virtual function calls, as established in
    //!         `set_loop_count()`, have been subtracted. The times are
    //!         total and not per iteration.
    // -----------------------------------------------------------------------
    process_duration    run() ;

    //      run():
    //      ------
    //
    //!\brief
    //!     Executes the benchmark and displays the average results for
    //!     a single iteration.
    //!
    //!     Calls `run()` and displays the results divided by the number
    //!     of iterations.
    //!
    //!     \param out
    //!         The destination to which the results will be displayed.
    //!
    //!     \param label
    //!         A label which will be output before the measurements
    //!         begin, so that an observer will know what is being
    //!         measured. `nullptr` if no label is wanted.
    //!
    //!     \param selector
    //!         A dummy parameter which is used to distinguish between
    //!         this function and the following one. Note that, since
    //!         this parameter is defaulted, this function, rather than
    //!         the following one, will be chosen if no selector is
    //!         given. (Otherwise, the only legal value for the argument
    //!         is `bench_harness::iteration_time`.)
    // -----------------------------------------------------------------------
    void                run( std::ostream & out,
                             char const * label = nullptr,
                             display_iteration selector = iteration_time ) ;

    //      run():
    //      ------
    //
    //!\brief
    //!     Executes the benchmark and displays the total times used.
    //!
    //!     Calls `run()` and displays the results (the calibration
    //!     times will have been subtracted).
    //!
    //!     \param out
    //!         The destination to which the results will be displayed.
    //!
    //!     \param label
    //!         A label which will be output before the measurements
    //!         begin, so that an observer will know what is being
    //!         measured. `nullptr` if no label is wanted.
    //!
    //!     \param selector
    //!         A dummy parameter which is used to distinguish between
    //!         this function and the preceding one. The argument must
    //!         be `bench_harness::total_time`.
    // -----------------------------------------------------------------------
    void                run( std::ostream & out,
                             char const * label,
                             display_total selector ) ;

    //      set_loop_count():
    //      -----------------
    //
    //!\brief
    //!     Sets the number of iterations and calibrates.
    //!
    //!     In addition to specifying the number of iterations to be
    //!     used for each call to `run()` (regardless of the object
    //!     `run()` is called on), this function calls `run()` on an
    //!     instance of this class with an empty `operator ()()`
    //!     function, and memorizes the time taken, in order to subtract
    //!     it from future measurements.
    //!
    //!     \pre
    //!         count > 0
    //!
    //!     \param count
    //!         The number of times each test should iterate.
    // -----------------------------------------------------------------------
    static void         set_loop_count( long count ) ;

protected:
    //!\brief
    //!     Default constructs a `bench_harness`.
    // -----------------------------------------------------------------------
                        bench_harness() noexcept ;

private:
    //      operator ()():
    //      --------------
    //
    //!\brief
    //!     The operation to be measured.
    //!
    //!     This function should be overridden in the derived class with
    //!     a function containing the operation to be measured. The
    //!     default version, here, does absolutely nothing, and is only
    //!     used for calibration purposes.
    // -----------------------------------------------------------------------
    virtual void        operator ()() ;

private:
    using               duration_type = process_duration::duration_type ;

    static long         s_loop_count ;
    static duration_type
                        s_user_overhead ;
    static duration_type
                        s_system_overhead ;
} ;

}

#endif
