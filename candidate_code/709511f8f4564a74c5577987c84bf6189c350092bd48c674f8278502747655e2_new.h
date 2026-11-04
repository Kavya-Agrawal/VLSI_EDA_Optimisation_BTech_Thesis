// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79372719;
  double density_weight = 0.09138512;
  double prefix_weight = 0.47883026;
  double neighborhood_weight = 0.27425566;
  double late_weight = 0.19982921;
  double critical_weight = 0.46310972;
  unsigned budget = 14;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
