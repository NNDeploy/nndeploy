#ifndef _NNTASK_SOURCE_COMMON_PARAMS_H_
#define _NNTASK_SOURCE_COMMON_PARAMS_H_

#include "nndeploy/source/base/basic.h"
#include "nndeploy/source/base/glic_stl_include.h"
#include "nndeploy/source/base/log.h"
#include "nndeploy/source/base/macro.h"
#include "nndeploy/source/base/object.h"
#include "nndeploy/source/base/param.h"
#include "nndeploy/source/base/status.h"
#include "nndeploy/source/base/string.h"
#include "nndeploy/source/base/type.h"
#include "nndeploy/source/base/value.h"
#include "nndeploy/source/device/buffer.h"
#include "nndeploy/source/device/buffer_pool.h"
#include "nndeploy/source/device/device.h"
#include "nndeploy/source/device/tensor.h"
#include "nndeploy/source/inference/inference.h"
#include "nndeploy/source/inference/inference_param.h"

namespace nntask {
namespace common {

/**
 * @brief
 * cvtcolor
 * resize
 * padding
 * warp_affine
 * crop
 */
class CvtclorResizeParam : public nndeploy::base::Param {
 public:
  nndeploy::base::PixelType src_pix_type_;
  nndeploy::base::PixelType dst_pix_type_;
  nndeploy::base::InterpType interp_type_;
  nndeploy::base::Size2f size_;
  std::vector<float> scale_;
  std::vector<float> bias_;
};

/**
 * @brief Classify result structure for all the image classify models
 *
 */
class NNDEPLOY_CC_API ClassifyParam : public nndeploy::base::Param {
 public:
  ClassifyParam() : Param(){};
  ClassifyParam(std::string name) : Param(name){};

  ~ClassifyParam();

  /**
   * @brief Classify param for an image
   *
   */
  std::vector<int32_t> label_ids_;
  /**
   * @brief The confidence for each classify param
   *
   */
  std::vector<float> scores_;
};

/**
 * @brief structure, used in DetectionResult for instance segmentation models
 *
 */
class NNDEPLOY_CC_API MaskParam : nndeploy::base::Param {
 public:
  MaskParam() : Param(){};
  MaskParam(std::string name) : Param(name){};

  ~MaskParam();
  /**
   * @brief Mask data buffer
   *
   */
  std::vector<uint8_t> data_;
  /**
   * @brief Shape of mask
   *
   */
  std::vector<int64_t> shape_;  // (H,W) ...
};

/**
 * @brief Detection result structure for all the object detection models and
 * instance segmentation models
 *
 */
class NNDEPLOY_CC_API DetectParam : public nndeploy::base::Param {
 public:
  DetectParam() : Param(){};
  DetectParam(std::string name) : Param(name){};

  ~DetectParam();

  /**
   * @brief All the detected object boxes for an input image, the size of
   * `boxes` is the number of detected objects, and the element of `boxes` is a
   * array of 4 float values, means [xmin, ymin, xmax, ymax]
   *
   */
  std::vector<std::array<float, 4>> boxes_;
  /**
   * @brief All the detected rotated object boxes for an input image, the size
   * of `boxes` is the number of detected objects, and the element of
   * `rotated_boxes` is an array of 8 float values, means [x1, y1, x2, y2, x3,
   * y3, x4, y4]
   */
  std::vector<std::array<float, 8>> rotated_boxes_;
  /**
   * @brief The confidence for all the detected objects
   */
  std::vector<float> scores_;
  /**
   * @brief The classify label for all the detected objects
   *
   */
  std::vector<int32_t> label_ids_;
  /**
   * @brief For instance segmentation model, `masks` is the predict mask for
   * all the deteced objects
   */
  std::vector<MaskParam> masks_;
  /**
   * @brief Shows if the DetectionResult has mask
   *
   */
  bool contain_masks_ = false;
};

/**
 * @brief Detection param structure for all the object detection models and
 * instance segmentation models
 */
class NNDEPLOY_CC_API PerceptionParam : public nndeploy::base::Param {
 public:
  PerceptionParam() : Param(){};
  PerceptionParam(std::string name) : Param(name){};

  ~PerceptionParam();

  std::vector<float> scores_;

  std::vector<int32_t> label_ids_;
  /**
   * @brief xmin, ymin, xmax, ymax, h, w, l
   *
   */
  std::vector<std::array<float, 7>> boxes_;
  /**
   * @brief cx, cy, cz
   *
   */
  std::vector<std::array<float, 3>> center_;

  std::vector<float> observation_angle_;

  std::vector<float> yaw_angle_;
  /**
   * @brief vx, vy, vz
   *
   */
  std::vector<std::array<float, 3>> velocity_;
};

/**
 *@brief KeyPoint Detection param structure for all the keypoint detection
 * models
 */
class NNDEPLOY_CC_API KeyPointDetectionParam : public nndeploy::base::Param {
 public:
  KeyPointDetectionParam() : Param(){};
  KeyPointDetectionParam(std::string name) : Param(name){};

  ~KeyPointDetectionParam();
  /**
   * @brief All the coordinates of detected keypoints for an input image, the
   * size of `keypoints` is num_detected_objects * num_joints, and the element
   * of `keypoint` is a array of 2 float values, means [x, y]
   */
  std::vector<nndeploy::base::Point2f> keypoints_;
  /**
   * @brief The confidence for all the detected points
   *
   */
  std::vector<float> scores_;
  /**
   * @brief Number of joints for a detected object
   *
   */
  int num_joints_ = -1;
};

class NNDEPLOY_CC_API OCRParam : public nndeploy::base::Param {
 public:
  OCRParam() : Param(){};
  OCRParam(std::string name) : Param(name){};

  ~OCRParam();
  std::vector<std::array<int, 8>> boxes_;

  std::vector<std::string> text_;
  std::vector<float> rec_scores_;

  std::vector<float> cls_scores_;
  std::vector<int32_t> cls_labels_;

  std::vector<std::array<int, 8>> table_boxes_;
  std::vector<std::string> table_structure_;
  std::string table_html_;
};

/**
 * @brief MOT(Multi-Object Tracking) param structure for all the MOT models
 */
class NNDEPLOY_CC_API MOTParam : public nndeploy::base::Param {
 public:
  MOTParam() : Param(){};
  MOTParam(std::string name) : Param(name){};

  ~MOTParam();
  /**
   * @brief All the tracking object boxes for an input image, the size of
   * `boxes` is the number of tracking objects, and the element of `boxes` is a
   * array of 4 float values, means [xmin, ymin, xmax, ymax]
   */
  std::vector<std::array<int, 4>> boxes_;
  /**
   * @brief All the tracking object ids
   */
  std::vector<int> ids_;
  /**
   * @brief The confidence for all the tracking objects
   */
  std::vector<float> scores_;
  /**
   * @brief The classify label id for all the tracking object
   */
  std::vector<int> class_ids_;
};

/**
 * @brief Face detection param structure for all the face detection models
 */
class NNDEPLOY_CC_API FaceDetectionParam : public nndeploy::base::Param {
 public:
  FaceDetectionParam() : Param(){};
  FaceDetectionParam(std::string name) : Param(name){};

  ~FaceDetectionParam();
  /**
   * @brief All the detected object boxes for an input image, the size of
   * `boxes` is the number of detected objects, and the element of `boxes` is a
   * array of 4 float values, means [xmin, ymin, xmax, ymax]
   */
  std::vector<std::array<float, 4>> boxes_;
  /**
   * @brief
   * If the model detect face with landmarks, every detected object box
   * correspoing to a landmark, which is a array of 2 float values, means
   * location [x,y]
   */
  std::vector<nndeploy::base::Point2f> landmarks_;
  /**
   * @brief
   * Indicates the confidence of all targets detected from a single image, and
   * the number of elements is consistent with boxes.size()
   */
  std::vector<float> scores_;
  /**
   * @brief
   * `landmarks_per_face` indicates the number of face landmarks for each
   * detected face if the model's output contains face landmarks (such as
   * YOLOv5Face, SCRFD, ...)
   */
  int landmarks_per_face_;
};

/**
 * @brief
 * Face Alignment param structure for all the face alignment models
 */
class NNDEPLOY_CC_API FaceAlignmentParam : public nndeploy::base::Param {
 public:
  FaceAlignmentParam() : Param(){};
  FaceAlignmentParam(std::string name) : Param(name){};

  ~FaceAlignmentParam();
  /**
   * @brief
   * All the coordinates of detected landmarks for an input image, and
   * the element of `landmarks` is a array of 2 float values, means [x, y]
   */
  std::vector<nndeploy::base::Point2f> landmarks_;
};

/**
 * @brief
 * Segmentation param structure for all the segmentation models
 */
class NNDEPLOY_CC_API SegmentationParam : public nndeploy::base::Param {
 public:
  SegmentationParam() : Param(){};
  SegmentationParam(std::string name) : Param(name){};

  ~SegmentationParam();
  /**
   * @brief
   * `label_map` stores the pixel-level category labels for input image. the
   * number of pixels is equal to label_map.size()
   */
  std::vector<uint8_t> label_map_;
  /**
   * @brief
   * `score_map` stores the probability of the predicted label for each pixel of
   * input image.
   */
  std::vector<float> score_map_;
  /**
   * @brief The output shape, means [H, W]
   *
   */
  std::vector<int64_t> shape_;
  /**
   * @brief SegmentationParam whether containing score_map
   *
   */
  bool contain_score_map_ = false;
};

/**
 * @brief Face recognition param structure for all the Face recognition models
 */
class NNDEPLOY_CC_API FaceRecognitionParam : public nndeploy::base::Param {
 public:
  FaceRecognitionParam() : Param(){};
  FaceRecognitionParam(std::string name) : Param(name){};

  ~FaceRecognitionParam();
  /**
   * @brief
   * The feature embedding that represents the final extraction of the
   * face recognition model can be used to calculate the feature similarity
   * between faces.
   */
  std::vector<float> embedding_;
};

/**
 * @brief Matting param structure for all the Matting models
 */
class NNDEPLOY_CC_API MattingParam : public nndeploy::base::Param {
 public:
  MattingParam() : Param(){};
  MattingParam(std::string name) : Param(name){};

  ~MattingParam();
  /**
   * @brief
   * `alpha` is a one-dimensional vector, which is the predicted alpha
   * transparency value. The range of values is [0., 1.], and the length is hxw.
   * h, w are the height and width of the input image
   */
  std::vector<float> alpha_;  // h x w
  /**
   * @brief
   * If the model can predict foreground, `foreground` save the predicted
   * foreground image, the shape is [hight,width,channel] generally.
   */
  std::vector<float> foreground_;  // h x w x c (c=3 default)
  /**
   * @brief
   * The shape of output param, when contain_foreground == false, shape only
   * contains (h, w), when contain_foreground == true, shape contains (h, w, c),
   * and c is generally 3
   */
  std::vector<int64_t> shape_;
  /**
   * @brief
   * If the model can predict alpha matte and foreground, contain_foreground =
   * true, default false
   */
  bool contain_foreground_ = false;
};

/**
 * @brief HeadPose param structure for all the headpose models
 */
class NNDEPLOY_CC_API HeadPoseParam : public nndeploy::base::Param {
 public:
  HeadPoseParam() : Param(){};
  HeadPoseParam(std::string name) : Param(name){};

  ~HeadPoseParam();
  /**
   * @brief EulerAngles for an input image, and the element of `euler_angles`
   * is a vector, contains {yaw, pitch, roll}
   */
  std::vector<float> euler_angles_;
};

}  // namespace common
}  // namespace nntask

#endif /* _NNTASK_SOURCE_COMMON_PARAMS_H_ */
