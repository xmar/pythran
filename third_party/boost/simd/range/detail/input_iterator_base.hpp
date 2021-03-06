//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_DETAILS_INPUT_ITERATOR_BASE_HPP_INCLUDED
#define BOOST_SIMD_RANGE_DETAILS_INPUT_ITERATOR_BASE_HPP_INCLUDED

#include <boost/simd/pack.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

namespace boost { namespace simd { namespace details
{
  template< typename Iterator
          , std::size_t C, typename Value
          , typename LoadFun
          >
  struct  input_iterator_base
        : boost::iterator_adaptor< input_iterator_base<Iterator,C,Value,LoadFun>
                                 , Iterator
                                 , pack<Value, C>
                                 , std::random_access_iterator_tag
                                 , pack<Value, C> const
                                 >
  {
    static const typename input_iterator_base::difference_type cardinal = C;
    BOOST_FORCEINLINE input_iterator_base()
                    : input_iterator_base::iterator_adaptor_()
    {}

    BOOST_FORCEINLINE explicit
    input_iterator_base ( Iterator p )
                        : input_iterator_base::iterator_adaptor_(p)
    {}

    protected:
    friend class boost::iterator_core_access;

    BOOST_FORCEINLINE
    typename input_iterator_base::reference dereference() const
    {
      dispatch::functor<LoadFun> callee;
      return callee ( &*this->base()
                    , dispatch::as_< pack<Value,C> >()
                    );
    }

    BOOST_FORCEINLINE  void increment() { this->base_reference() += C; }
    BOOST_FORCEINLINE  void decrement() { this->base_reference() -= C; }

    BOOST_FORCEINLINE
    void advance(typename input_iterator_base::difference_type n)
    {
      this->base_reference() += n*C;
    }

    BOOST_FORCEINLINE  typename input_iterator_base::difference_type
    distance_to(input_iterator_base const& other) const
    {
      return (other.base() - this->base()) / cardinal;
    }
  };
} } }

#endif
