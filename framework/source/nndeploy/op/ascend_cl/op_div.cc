#include "aclnnop/aclnn_div.h"
#include "nndeploy/op/ascend_cl/op_convert.h"
#include "nndeploy/op/ascend_cl/op_include.h"
#include "nndeploy/op/ascend_cl/op_util.h"
#include "nndeploy/op/op.h"
#include "nndeploy/op/op_binary.h"

namespace nndeploy {
namespace op {

class AscendCLOpDiv : public OpBinary {
 public:
  AscendCLOpDiv() {}
  virtual ~AscendCLOpDiv() {}

  virtual base::Status init() {
    // 流
    device::Device* device = device::getDevice(device_type_);
    inner_stream_ = (aclrtStream)device->getCommandQueue();

    return base::kStatusCodeOk;
  }
  virtual base::Status deinit() { return base::kStatusCodeOk; }
  virtual base::Status preRun() {
    // 输入输出
    inner_input_0_ =
        AscendCLOpConvert::convertFromTensor(inputs_[0], ACL_FORMAT_ND);
    inner_input_1_ =
        AscendCLOpConvert::convertFromTensor(inputs_[1], ACL_FORMAT_ND);
    inner_output_ =
        AscendCLOpConvert::convertFromTensor(outputs_[0], ACL_FORMAT_ND);

    // 创建算子
    aclnnStatus aclnn_status =
        aclnnDivGetWorkspaceSize(inner_input_0_, inner_input_1_, inner_output_,
                                 &workspace_size_, &executor_);
    NNDEPLOY_RETURN_VALUE_ON_NEQ(aclnn_status, ACL_SUCCESS,
                                 base::kStatusCodeErrorOpAscendCL,
                                 "aclnnDivGetWorkspaceSize failed.");
    return base::kStatusCodeOk;
  }
  virtual base::Status run() {
    // 输入输出
    aclnnStatus aclnn_status =
        aclnnDiv(workspace_, workspace_size_, executor_, inner_stream_);
    NNDEPLOY_RETURN_VALUE_ON_NEQ(aclnn_status, ACL_SUCCESS,
                                 base::kStatusCodeErrorOpAscendCL,
                                 "aclnnDiv failed.");

    return base::kStatusCodeOk;
  }
  virtual base::Status postRun() {
    aclDestroyTensor(inner_input_0_);
    aclDestroyTensor(inner_input_1_);
    aclDestroyTensor(inner_output_);
    return base::kStatusCodeOk;
  }

 private:
  std::string inner_op_type_ = "Div";

  aclTensor* inner_input_0_ = nullptr;
  aclTensor* inner_input_1_ = nullptr;
  aclTensor* inner_output_ = nullptr;
  aclOpExecutor* executor_;

  aclrtStream inner_stream_;
  aclopAttr* attr_{nullptr};
};

REGISTER_OP_IMPLEMENTION(base::DeviceTypeCode::kDeviceTypeCodeAscendCL,
                         ir::kOpTypeDiv, AscendCLOpDiv)

}  // namespace op
}  // namespace nndeploy
