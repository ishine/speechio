#ifndef SIO_TYPE_H
#define SIO_TYPE_H

#include <stdint.h>
#include <stddef.h>

namespace sio {

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using f32 = float;
using f64 = double;

using index_t = ptrdiff_t;

enum class AudioFormat: int {
  kUnknown,
  kFloatMono8k,
  kFloatMono16k,
  kShortMono8k,
  kShortMono16k,
};

}; // namespace sio
#endif
