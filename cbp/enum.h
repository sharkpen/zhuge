/*
 File Name: enum.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-07
 Last Modified: 2023-09-07
*/
#pragma once
namespace croot {
namespace lltg {



enum FieldType {
  UNKNOWN,
  INT32,
  INT64,
  FLOAT,
  DOUBLE,
  REF,
  STATIC_ARRAY,
  DYNAMIC_ARRAY,
  STRING
};
}  // namespace lltg
}  // namespace croot

