#ifndef SIO_CHECK_H
#define SIO_CHECK_H

#include "sio/base.h"
#include "sio/error.h"
#include "sio/log.h"

namespace sio {

class Voidifier {
 public:
  void operator&(const Logger &) const { }
};

#define SIO_CHECK(cond) \
  SIO_LIKELY(cond) ? (void)0 \
    : ::sio::Voidifier() & SIO_FATAL(::sio::Error::AssertionFailure) << "Check failed: {" << #cond << "}. "

#define SIO_P_COND(cond) SIO_CHECK(cond) << "Pre-condition. "
#define SIO_Q_COND(cond) SIO_CHECK(cond) << "Post-condition. "
#define SIO_INVAR(cond)  SIO_CHECK(cond) << "Invariant. "

} // namespace sio
#endif
