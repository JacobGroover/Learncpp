/*
First, we have to include the cstdarg header. This header defines va_list, va_arg, va_start, and va_end,
which are macros that we need to use to access the parameters that are part of the ellipsis.
 */

#include <iostream>
#include <string_view>
#include <cstdarg> // needed to use ellipsis


// Ellipses using a "decoder string"
// The ellipsis must be the last parameter
double findAverage(std::string_view decoder, ...)
{
	double sum{ 0 };

	// We access the ellipsis through a va_list, so let's declare one
	std::va_list list;

	// We initialize the va_list using va_start.  The first argument is
	// the list to initialize.  The second argument is the last non-ellipsis
	// parameter.
	va_start(list, decoder);

	for (auto codetype: decoder)
	{
		switch (codetype)
		{
			case 'i':
				sum += va_arg(list, int);
				break;

			case 'd':
				sum += va_arg(list, double);
				break;
		}
	}

	// Cleanup the va_list when we're done.
	va_end(list);

	return sum / std::size(decoder);
}

int main()
{
	std::cout << findAverage("iiiii", 1, 2, 3, 4, 5) << '\n';
	std::cout << findAverage("iiiiii", 1, 2, 3, 4, 5, 6) << '\n';
	std::cout << findAverage("iiddi", 1, 2, 3.5, 4.5, 5) << '\n';

	return 0;
}

/*
Recommendations for safer use of ellipsis

First, if possible, do not use ellipsis at all! Oftentimes, other reasonable solutions are available, even if they
require slightly more work. For example, in our findAverage() program, we could have passed in a dynamically sized
array of integers instead. This would have provided both strong type checking (to make sure the caller doesn’t try
to do something nonsensical) while preserving the ability to pass a variable number of integers to be averaged.

Second, if you do use ellipsis, it is better if all values passed to the ellipses parameter are the same type (e.g.
all int, or all double, not a mix of each). Intermixing different types vastly increases the possibility of the caller
inadvertently passing in data of the wrong type and va_arg() producing a garbage result.

Third, using a count parameter or decoder string parameter is generally safer than using a sentinel value. This
forces the user to pick an appropriate value for the count/decoder parameter, which ensures the ellipsis loop will
terminate after a reasonable number of iterations even if it produces a garbage value.

For advanced readers

To improve upon ellipses-like functionality, C++11 introduced parameter packs and variadic templates, which offers
functionality similar to ellipses, but with strong type checking. However, significant usability challenges impeded
adoption of this feature.

In C++17, fold expressions were added, which significantly improves the usability of parameter packs, to the point
where they are now a viable option.
 */