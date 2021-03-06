#ifndef PYTHONIC_INCLUDE_NUMPY_ISFINITE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ISFINITE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/is_finite.hpp>

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T>
      bool isfinite(std::complex<T> const &t)
      {
        return std::isfinite(t.real()) and std::isfinite(t.imag());
      }
      template <class T>
      bool isfinite(T const &v)
      {
        return boost::simd::is_finite(v);
      }
    }

#define NUMPY_NARY_FUNC_NAME isfinite
#define NUMPY_NARY_FUNC_SYM wrapper::isfinite
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
