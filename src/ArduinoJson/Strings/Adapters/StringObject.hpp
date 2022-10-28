// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Strings/Adapters/RamString.hpp>
#include <ArduinoJson/Strings/StringAdapter.hpp>
#include <ArduinoJson/Strings/StringTraits.hpp>

namespace ARDUINOJSON_NAMESPACE {

template <typename T>
struct StringAdapter<
    T,
    typename enable_if<
        (string_traits<T>::has_cstr || string_traits<T>::has_data) &&
        (string_traits<T>::has_length || string_traits<T>::has_size)>::type> {
  typedef SizedRamString AdaptedString;

  static AdaptedString adapt(const T& s) {
    return AdaptedString(get_data(s), get_size(s));
  }

 private:
  template <typename U>
  static typename enable_if<string_traits<U>::has_size, size_t>::type get_size(
      const U& s) {
    return s.size();
  }

  template <typename U>
  static typename enable_if<!string_traits<U>::has_size, size_t>::type get_size(
      const U& s) {
    return s.length();
  }

  template <typename U>
  static typename enable_if<string_traits<U>::has_data, const char*>::type
  get_data(const U& s) {
    return s.data();
  }

  template <typename U>
  static typename enable_if<!string_traits<U>::has_data, const char*>::type
  get_data(const U& s) {
    return s.c_str();
  }
};

}  // namespace ARDUINOJSON_NAMESPACE
