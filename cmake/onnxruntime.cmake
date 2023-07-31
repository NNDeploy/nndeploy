
include(ExternalProject)
# message(STATUS "ENABLE_NNDEPLOY_INFERENCE_ONNXRUNTIME: ${ENABLE_NNDEPLOY_INFERENCE_ONNXRUNTIME}")

if (ENABLE_NNDEPLOY_INFERENCE_ONNXRUNTIME STREQUAL "OFF")
elseif (ENABLE_NNDEPLOY_INFERENCE_ONNXRUNTIME STREQUAL "ON")
else()
  include_directories(${ENABLE_NNDEPLOY_INFERENCE_ONNXRUNTIME}/include)
  set(onnxruntime "onnxruntime")
  set(tmp_name ${NNDEPLOY_LIB_PREFIX}${onnxruntime}${NNDEPLOY_LIB_SUFFIX})
  set(tmp_path ${ENABLE_NNDEPLOY_INFERENCE_ONNXRUNTIME}/lib)
  set(full_name ${tmp_path}/${tmp_name})
  set(NNDEPLOY_THIRD_PARTY_LIBRARY ${NNDEPLOY_THIRD_PARTY_LIBRARY} ${full_name})
  install(FILES ${full_name} DESTINATION ${NNDEPLOY_INSTALL_PATH})
endif()