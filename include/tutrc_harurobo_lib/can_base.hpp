#pragma once

#include <cstddef>
#include <cstdint>

namespace tutrc_harurobo_lib {

enum class CANIDType {
  STANDARD,
  EXTENDED,
};

struct CANMessage {
  CANIDType id_type;
  uint32_t id;
  uint8_t dlc;
  uint8_t data[8];
};

class CANBase {
public:
  virtual ~CANBase() {}
  virtual bool transmit(const CANMessage *msg) = 0;
  virtual bool receive(CANMessage *msg, uint32_t timeout) = 0;
  virtual size_t available() = 0;
};

} // namespace tutrc_harurobo_lib
