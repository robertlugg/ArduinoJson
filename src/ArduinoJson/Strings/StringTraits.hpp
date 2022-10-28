// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Strings/Adapters/RamString.hpp>
#include <ArduinoJson/Strings/StringAdapter.hpp>

namespace ARDUINOJSON_NAMESPACE {

namespace string_traits_impl {

template <typename T>
class has_cstr {
 protected:
  template <typename U, const char* (U::*)() const>
  struct Check;

  template <typename U>
  static char probe(Check<U, &U::c_str>*);

  template <typename U>
  static int probe(...);

 public:
  enum { value = sizeof(probe<T>(0)) == sizeof(char) };
};

template <typename T>
class has_data {
 protected:
  template <typename U, const char* (U::*)() const>
  struct Check;

  template <typename U>
  static char probe(Check<U, &U::data>*);

  template <typename U>
  static int probe(...);

 public:
  enum { value = sizeof(probe<T>(0)) == sizeof(char) };
};

template <typename T>
class has_length {
 protected:
  template <typename U, size_t (U::*)() const>
  struct Check;

  template <typename U>
  static char probe(Check<U, &U::length>*);

  template <typename U>
  static int probe(...);

 public:
  enum { value = sizeof(probe<T>(0)) == sizeof(char) };
};

template <typename T>
class has_size {
 protected:
  template <typename U, size_t (U::*)() const>
  struct Check;

  template <typename U>
  static char probe(Check<U, &U::size>*);

  template <typename U>
  static int probe(...);

 public:
  enum { value = sizeof(probe<T>(0)) == sizeof(char) };
};
}  // namespace string_traits_impl

template <typename T>
struct string_traits {
  enum {
    has_cstr = string_traits_impl::has_cstr<T>::value,
    has_length = string_traits_impl::has_length<T>::value,
    has_data = string_traits_impl::has_data<T>::value,
    has_size = string_traits_impl::has_size<T>::value
  };
};

}  // namespace ARDUINOJSON_NAMESPACE
