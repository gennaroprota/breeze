The initial version of this generator was a shell script using the `od` utility
to extract 128 bits (16 octets) from `/dev/random` and output them in hex
format.

That gave, of course, 32 characters.

My friend James Kanze brought up the idea to represent each byte in base 62,
using as digits all the alphanumeric characters allowed in a C or C++
identifier, except underscore: 0-9, a-f, A-F. [footnote1]

This allows using 3 base-62 digits for each couple of bytes, thus reducing the
number of characters to 24.

I played with various implementations of this idea, using different combinations
of the Unix tools.

At a point however it occurred to me that we could just generate random numbers
in 0..61 and represent each of them with one of the alphanumeric characters
above.

And I played with several implementations of this different idea. The main
drawback was that no scripted implementations seemed reasonably fast on Cygwin
(at least at the time). So I went with C++.

This is, historically, the reason for the "24" as number of generated random
characters (later changed to more characters).

James went for a different approach (which I happened to suggest, although I
wasn't at all sure it would work until James explained it back to me:-)), using
the `tr` utility, which introduces a little bias. It's simpler, and the bias is
acceptable, but of course C++ offers a lot more versatility, and I felt that the
(short) development time that it required was in fact repaid.

But it turned out that Python offers the best solution overall: it is fast
enough on all my machines and the resulting code is very very maintainable.
Also, of course, Python allows bootstrapping on a new machine without building
anything. So, in 2021, I decided to switch to Python (as I had already done with
several other tools).

---------
[footnote1] Using underscore, too, would require more maneuvers to avoid the
appearance of consecutive underscores and other reserved combinations.
