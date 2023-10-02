# --------------------------------------------------------------------
# Template custom cmake config for compiling
#
# This file is used to override the build sets in build.
# If you want to change the config, please use the following
# steps. Assume you are off the root directory. First copy the this
# file so that any local changes will be ignored by git
#
# $ mkdir build
# $ cp cmake/config_xx.cmake build
# $ cd build
# $ cmake ..
# $ make -j8
# --------------------------------------------------------------------
# common
set(ENABLE_NNDEPLOY_BUILD_SHARED ON)
set(ENABLE_NNDEPLOY_SYMBOL_HIDE ON)
set(ENABLE_NNDEPLOY_COVERAGE OFF)
set(ENABLE_NNDEPLOY_CXX11_ABI ON)
set(ENABLE_NNDEPLOY_CXX14_ABI OFF)
set(ENABLE_NNDEPLOY_CXX17_ABI OFF)
set(ENABLE_NNDEPLOY_OPENMP OFF)
set(ENABLE_NNDEPLOY_ADDRESS_SANTIZER OFF)
set(ENABLE_NNDEPLOY_DOCS OFF)
set(ENABLE_NNDEPLOY_TIME_PROFILER ON)
set(ENABLE_NNDEPLOY_OPENCV "/Users/jodio/Documents/GitHub/opencv/build/forNN") # must be ON or PATH/TO/OPENCV
set(NNDEPLOY_OPENCV_LIBS "opencv_imgproc" "opencv_core" "opencv_imgcodecs")
## base
set(ENABLE_NNDEPLOY_BASE ON)
## thread
set(ENABLE_NNDEPLOY_THREAD_POOL ON)
## cryption
set(ENABLE_NNDEPLOY_CRYPTION OFF)
## device
set(ENABLE_NNDEPLOY_DEVICE ON)
set(ENABLE_NNDEPLOY_DEVICE_CPU OFF)
set(ENABLE_NNDEPLOY_DEVICE_ARM ON)
set(ENABLE_NNDEPLOY_DEVICE_X86 OFF)
set(ENABLE_NNDEPLOY_DEVICE_CUDA OFF)
set(ENABLE_NNDEPLOY_DEVICE_CUDNN OFF)
set(ENABLE_NNDEPLOY_DEVICE_OPENCL OFF)
set(ENABLE_NNDEPLOY_DEVICE_OPENGL OFF)
set(ENABLE_NNDEPLOY_DEVICE_METAL OFF)
set(ENABLE_NNDEPLOY_DEVICE_APPLE_NPU OFF)
set(ENABLE_NNDEPLOY_DEVICE_HVX OFF)
set(ENABLE_NNDEPLOY_DEVICE_MTK_VPU OFF)
## op
set(ENABLE_NNDEPLOY_OP OFF)
set(ENABLE_NNDEPLOY_OP_NN OFF)
set(ENABLE_NNDEPLOY_OP_CV OFF)
set(ENABLE_NNDEPLOY_OP_AUDIO OFF)
## forward
set(ENABLE_NNDEPLOY_FORWARD OFF)
## inference
set(ENABLE_NNDEPLOY_INFERENCE ON)
set(ENABLE_NNDEPLOY_INFERENCE_TENSORRT OFF)
set(ENABLE_NNDEPLOY_INFERENCE_OPENVINO OFF)
set(ENABLE_NNDEPLOY_INFERENCE_COREML OFF)
set(ENABLE_NNDEPLOY_INFERENCE_TFLITE OFF)
set(ENABLE_NNDEPLOY_INFERENCE_ONNXRUNTIME OFF)
set(ENABLE_NNDEPLOY_INFERENCE_NCNN OFF)
set(ENABLE_NNDEPLOY_INFERENCE_TNN OFF)
set(ENABLE_NNDEPLOY_INFERENCE_MNN "/Users/jodio/project/mnn/MNN/build/install")
set(ENABLE_NNDEPLOY_INFERENCE_PADDLELITE OFF)
set(ENABLE_NNDEPLOY_AICOMPILER_TVM OFF)
## model
set(ENABLE_NNDEPLOY_MODEL ON)
## test
set(ENABLE_NNDEPLOY_TEST OFF)
## demo
set(ENABLE_NNDEPLOY_DEMO ON)

## model detect
set(ENABLE_NNDEPLOY_MODEL_DETECT ON)
set(ENABLE_NNDEPLOY_MODEL_DETECT_DETR OFF)
set(ENABLE_NNDEPLOY_MODEL_DETECT_YOLO ON)