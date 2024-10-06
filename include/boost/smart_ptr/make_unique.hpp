/*
Copyright 2012-2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_SMART_PTR_MAKE_UNIQUE_HPP
#define BOOST_SMART_PTR_MAKE_UNIQUE_HPP

#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_unbounded_array.hpp>
#include <memory>
#include <utility>
#include <type_traits>

namespace boost {

template<class T>
inline typename std::enable_if<!is_array<T>::value, std::unique_ptr<T> >::type
make_unique()
{
    return std::unique_ptr<T>(new T());
}

template<class T, class... Args>
inline typename std::enable_if<!is_array<T>::value, std::unique_ptr<T> >::type
make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<class T>
inline typename std::enable_if<!is_array<T>::value, std::unique_ptr<T> >::type
make_unique(typename std::remove_reference<T>::type&& value)
{
    return std::unique_ptr<T>(new T(std::move(value)));
}

template<class T>
inline typename std::enable_if<!is_array<T>::value, std::unique_ptr<T> >::type
make_unique_noinit()
{
    return std::unique_ptr<T>(new T);
}

template<class T>
inline typename std::enable_if<is_unbounded_array<T>::value,
    std::unique_ptr<T> >::type
make_unique(std::size_t size)
{
    return std::unique_ptr<T>(new typename std::remove_extent<T>::type[size]());
}

template<class T>
inline typename std::enable_if<is_unbounded_array<T>::value,
    std::unique_ptr<T> >::type
make_unique_noinit(std::size_t size)
{
    return std::unique_ptr<T>(new typename std::remove_extent<T>::type[size]);
}

} /* boost */

#endif
