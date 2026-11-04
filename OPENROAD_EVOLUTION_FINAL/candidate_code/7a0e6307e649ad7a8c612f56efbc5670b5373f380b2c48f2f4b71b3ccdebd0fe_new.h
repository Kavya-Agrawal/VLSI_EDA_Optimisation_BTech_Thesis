// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.69311344;
  double density_weight = 0.42862910;
  double prefix_weight = 0.24767170;
  double neighborhood_weight = 0.02082390;
  double late_weight = 0.29460674;
  double critical_weight = 0.21451393;
  unsigned budget = 21;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
