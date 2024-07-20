
#ifndef _NNDEPLOY_OP_OP_SOFTMAX_H_
#define _NNDEPLOY_OP_OP_SOFTMAX_H_

#include "nndeploy/op/ir.h"
#include "nndeploy/op/op.h"

namespace nndeploy {
namespace op {

class OpSoftmax : public Op {
 public:
  OpSoftmax() {}
  virtual ~OpSoftmax() {}

  virtual base::Status inferShape() {
    auto input_shape = inputs_[0]->getShape();
    outputs_[0]->reshape(input_shape);
    return base::kStatusCodeOk;
  }
};

}  // namespace op
}  // namespace nndeploy

#endif