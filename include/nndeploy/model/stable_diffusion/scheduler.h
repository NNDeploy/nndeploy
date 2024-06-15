
#ifndef _NNDEPLOY_MODEL_STABLE_DIFFUSION_SCHEDULER_H_
#define _NNDEPLOY_MODEL_STABLE_DIFFUSION_SCHEDULER_H_

#include <random>

#include "nndeploy/base/common.h"
#include "nndeploy/base/glic_stl_include.h"
#include "nndeploy/base/log.h"
#include "nndeploy/base/macro.h"
#include "nndeploy/base/object.h"
#include "nndeploy/base/opencv_include.h"
#include "nndeploy/base/param.h"
#include "nndeploy/base/status.h"
#include "nndeploy/base/string.h"
#include "nndeploy/base/value.h"
#include "nndeploy/dag/edge.h"
#include "nndeploy/dag/graph.h"
#include "nndeploy/dag/loop.h"
#include "nndeploy/dag/node.h"
#include "nndeploy/device/buffer.h"
#include "nndeploy/device/device.h"
#include "nndeploy/device/memory_pool.h"
#include "nndeploy/device/tensor.h"
#include "nndeploy/model/convert_to.h"
#include "nndeploy/model/stable_diffusion/type.h"

namespace nndeploy {
namespace model {

class NNDEPLOY_CC_API SchedulerParam : public base::Param {
 public:
  std::string version_ = "v2.1";
  int num_train_timesteps_ = 1000;  // 训练时间步数
  float beta_start_ = 0.00085;      // beta起始值
  float beta_end_ = 0.012;          // beta结束值
  bool clip_sample_ = false;        // 是否裁剪样本
  bool set_alpha_to_one_ = false;  // 是否将alpha的累积乘积的最后一个元素设置为1
  int steps_offset_ = 1;  // 时间步偏移
  /**
   * @brief
   * v_prediction or epsilon
   */
  std::string prediction_type_ = "v_prediction";  // 预测噪声的方法
  int num_inference_steps_ = 50;
  int unet_channels_ = 4;
  int image_height_ = 640;
  int image_width_ = 640;
};

/**
 * @brief
 * @note 主要是如下4个目的：
 * 1- 迭代次数
 * 2- 构建latent
 * 3- timestep
 * 4- convert_to encoder_hidden_states
 */
class NNDEPLOY_CC_API Scheduler : public dag::Loop {
 public:
  Scheduler(const std::string &name, SchedulerType scheduler_type,
            dag::Edge *input, dag::Edge *output)
      : Loop(name, input, output), scheduler_type_(scheduler_type) {}

  Scheduler(const std::string &name, SchedulerType scheduler_type,
            std::initializer_list<dag::Edge *> inputs,
            std::initializer_list<dag::Edge *> outputs)
      : Loop(name, inputs, outputs), scheduler_type_(scheduler_type) {}
  Scheduler(const std::string &name, SchedulerType scheduler_type,
            std::vector<dag::Edge *> &inputs, std::vector<dag::Edge *> &outputs)
      : Loop(name, inputs, outputs), scheduler_type_(scheduler_type) {}

  virtual ~Scheduler() {}

  /**
   * @brief Set the Timesteps object
   *
   * @param num_Scheduler_steps
   * @return base::Status
   * @note 设置推断过程中的时间步
   */
  virtual base::Status setTimesteps() = 0;

  /**
   * @brief
   *
   * @return base::Status
   * @note 配置调度器，计算推断步骤中的方差
   */
  virtual base::Status configure() = 0;

  virtual device::Tensor *scaleModelInput(device::Tensor *sample,
                                          int index) = 0;

  /**
   * @brief
   *
   * @param sample
   * @param latents
   * @param index
   * @param timestep
   * @return base::Status
   * @note
   *  生成过程中的每一步都会调用此方法，它根据当前的时间步计算并更新生成的样本。
   */
  virtual base::Status step(device::Tensor *model_output,
                            device::Tensor *sample, int idx,
                            std::vector<int64_t> &timestep, float eta,
                            bool use_clipped_model_output,
                            std::mt19937 &generator,
                            device::Tensor *variance_noise) = 0;

  /**
   * @brief
   *
   * @param init_latents 初始的潜在表示
   * @param noise 要添加的噪声
   * @param idx 当前的时间步索引
   * @param latent_timestep 潜在表示的时间步
   * @return base::Status
   * @note 此方法用于将噪声添加到初始潜在表示中，生成扩散过程中的一个步骤
   */
  virtual base::Status addNoise(device::Tensor *init_latents,
                                device::Tensor *noise, int idx,
                                int latent_timestep) = 0;

 protected:
  SchedulerType scheduler_type_ = kSchedulerTypeNotSupport;
};

void customLinspace(float start, float end, int steps,
                    std::vector<float> &values);

base::Status initializeLatents(std::mt19937 &generator, float init_noise_sigma,
                               device ::Tensor *latents);

/**
 * @brief 推理框架的创建类
 *
 */
class SchedulerCreator {
 public:
  virtual ~SchedulerCreator(){};
  virtual Scheduler *createScheduler(const std::string &name,
                                     SchedulerType type,
                                     std::vector<dag::Edge *> &input,
                                     std::vector<dag::Edge *> &output) = 0;
};

/**
 * @brief 推理框架的创建类模板
 *
 * @tparam T
 */
template <typename T>
class TypeSchedulerCreator : public SchedulerCreator {
  virtual Scheduler *createScheduler(const std::string &name,
                                     SchedulerType type,
                                     std::vector<dag::Edge *> &input,
                                     std::vector<dag::Edge *> &output) {
    return new T(name, type, input, output);
  }
};

/**
 * @brief Get the Global Scheduler Creator Map object
 *
 * @return std::map<SchedulerType, std::shared_ptr<SchedulerCreator>>&
 */
std::map<SchedulerType, std::shared_ptr<SchedulerCreator>> &
getGlobalSchedulerCreatorMap();

/**
 * @brief 推理框架的创建类的注册类模板
 *
 * @tparam T
 */
template <typename T>
class TypeSchedulerRegister {
 public:
  explicit TypeSchedulerRegister(SchedulerType type) {
    getGlobalSchedulerCreatorMap()[type] = std::shared_ptr<T>(new T());
  }
};

/**
 * @brief Create a Scheduler object
 *
 * @param type
 * @return Scheduler*
 */
extern NNDEPLOY_CC_API Scheduler *createScheduler(
    const std::string &name, SchedulerType type,
    std::vector<dag::Edge *> &input, std::vector<dag::Edge *> &output);

extern NNDEPLOY_CC_API dag::Graph *createSchedulerUNetGraph(
    const std::string &name, dag::Edge *input, dag::Edge *output,
    SchedulerType scheduler_type, base::InferenceType inference_type,
    std::vector<base::Param *> &param);

}  // namespace model
}  // namespace nndeploy

#endif