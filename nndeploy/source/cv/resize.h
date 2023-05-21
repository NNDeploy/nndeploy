
#include "nndeploy/source/base/basic.h"
#include "nndeploy/source/base/status.h"
#include "nndeploy/source/cv/common.h"
#include "nndeploy/source/device/buffer.h"
#include "nndeploy/source/device/mat.h"

CV_ARM_INCLUDE(#include "nndeploy/source/cv/arm/arm_resize.h")
CV_X86_INCLUDE(#include "nndeploy/source/cv/x86/x86_resize.h")
CV_OPENCL_INCLUDE(#include "nndeploy/source/cv/opencl/opencl_resize.h");
CV_CUDA_INCLUDE(#include "nndeploy/source/cv/cuda/cuda_resize.h");

namespace nndeploy {
namespace cv {

void resize(const device::Mat &src, device::Mat &dst, base::Size2i dsize,
            double inv_scale_x, double inv_scale_y, int interpolation) {
  CV_ARM_RUN(resize(src, dst, dsize, inv_scale_x, inv_scale_y, interpolation));
  CV_X86_RUN(resize(src, dst, dsize, inv_scale_x, inv_scale_y, interpolation));
  CV_OPENCL_RUN(
      resize(src, dst, dsize, inv_scale_x, inv_scale_y, interpolation));
  CV_CUDA_RUN(resize(src, dst, dsize, inv_scale_x, inv_scale_y, interpolation));
  return;
}

}  // namespace cv
}  // namespace nndeploy