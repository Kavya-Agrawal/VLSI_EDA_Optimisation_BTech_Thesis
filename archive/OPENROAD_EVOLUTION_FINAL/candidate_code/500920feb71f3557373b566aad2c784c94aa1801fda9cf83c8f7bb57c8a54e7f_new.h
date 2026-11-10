// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13928017;
  double density_weight = 0.48171801;
  double prefix_weight = 0.01712680;
  double neighborhood_weight = 0.15690583;
  double late_weight = 0.04195403;
  double critical_weight = 0.04140522;
  unsigned budget = 17;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
