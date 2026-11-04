// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18440837;
  double density_weight = 0.28158206;
  double prefix_weight = 0.49443699;
  double neighborhood_weight = 0.22357160;
  double late_weight = 0.09465955;
  double critical_weight = 0.13474867;
  unsigned budget = 32;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
