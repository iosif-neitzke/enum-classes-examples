#ifndef TEST_ENUM_HPP_INCLUDED
#define TEST_ENUM_HPP_INCLUDED

#include "Enum.hpp"

class Test_Enum: public Enum<Test_Enum> {
  explicit Test_Enum( int Value ) : Enum<Test_Enum>( Value ) {}

public:
  static const Test_Enum enum_11, enum_12, enum_18, enum_20, enum_21;
};

#endif

