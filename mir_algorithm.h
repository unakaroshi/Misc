#pragma once

#include <vector>
#include <algorithm>

namespace mir {

  // Various implementations for is_even and is_odd
  constexpr bool is_even(int value) {
    return (value % 2) == 0;
  }
  constexpr bool is_even(unsigned int value) {
    return (value % 2) == 0;
  }
  constexpr bool is_even(long value) {
    return (value % 2) == 0;
  }
  constexpr bool is_even(unsigned long value) {
    return (value % 2) == 0;
  }
  constexpr bool is_even(long long value) {
    return (value % 2) == 0;
  }
  constexpr bool is_even(unsigned long long value) {
    return (value % 2) == 0;
  }
  constexpr bool is_odd(int value) {
    return (value % 2) == 1;
  }
  constexpr bool is_odd(unsigned int value) {
    return (value % 2) == 1;
  }
  constexpr bool is_odd(long value) {
    return (value % 2) == 1;
  }
  constexpr bool is_odd(unsigned long value) {
    return (value % 2) == 1;
  }
  constexpr bool is_odd(long long value) {
    return (value % 2) == 1;
  }
  constexpr bool is_odd(unsigned long long value) {
    return (value % 2) == 1;
  }



  //
  // Slide from Cpp Seasoning
  //
  // Use case: 
  //  list of items, make continous selection and move that selection into a new 'p' position.
  //
  //  Params:
  //      f : Iterator to the first element to move
  //      l ; Iterator to the last element to move
  //      p : Iterator to the point where to move
  //
  // Returns: 
  //   two iterators - the start and the end of the new sequence (std::pair)
  //   
  // from:
  //    https://sean-parent.stlab.cc/presentations/2013-09-11-cpp-seasoning/cpp-seasoning.pdf
  //    Video: https://www.youtube.com/watch?v=W2tWOdzgXHA
  //
  //
  // Example:
  //  std::vector<int> v{ 1,2,3,4,5,6,7,8,9 };
  //
  //  auto first = std::find(v.begin(), v.end(), 3);
  //  auto last = first + 2;
  //  auto pos = std::find(v.begin(), v.end(), 8);
  //
  //  slide(first, last, pos);
  //   // v now is:  1 2 5 6 7 3 4 8 9
  template <typename I> // I models RandomAccessIterator
  auto slide(I f, I l, I p) -> std::pair<I, I> {
    if (p < f) {
      return { p, rotate(p, f, l) };
    }

    if (l < p) {
      return { rotate(f, l, p), p };
    }

    return { f, l };
  }


  //
  // Gather from Cpp Seasoning
  //
  // Use case: 
  //   list of items, select some of items (good guys) and move the to position around p.
  //   (for instance: multiple selection on a list)
  //
  // How it works:
  //   It's use case can be similar to slide: select elements - using a predicate s 
  //   so this time continuous range is not needed), then gather those elements into a 
  //   range and move this range to position around p. It returns the start and the end 
  //   of the selected range.
  //
  //   UnPred is a predicate that returns if a given element is selected or not.
  //
  // Params:
  //   f : Iterator to the start
  //   l : Iterator to the end
  //   p : Iterator to the point where to move to
  //   s : Predicate that returns if a given element is selected or not

  // Returns:
  //   two iterators - the start and the end of the new sequence (std::pair)
  //   
  // from:
  //    https://sean-parent.stlab.cc/presentations/2013-09-11-cpp-seasoning/cpp-seasoning.pdf
  //    Video: https://www.youtube.com/watch?v=W2tWOdzgXHA
  //
  // Example:
  //   // Move all even numbers to the back
  //   std::vector<int> v{ 1,2,3,4,5,6,7,8,9 };
  //   gather(v.begin(), v.end(), v.end(), [](int x) { return is_even(x); });
  //   // 1 3 5 7 9 2 4 8
  //
  template <typename I, // I models BidirectionalIterator
            typename S> // S models UnaryPredicate
  auto gather(I f, I l, I p, S s) -> std::pair < I, I >
  {
    using value_type = typename std::iterator_traits<I>::value_type;

    return { 
       std::stable_partition(f, p, [&](const value_type& x) { 
          return !s(x); 
       }),
       std::stable_partition(p, l, s) 
    };
  }



} // namespace mir






