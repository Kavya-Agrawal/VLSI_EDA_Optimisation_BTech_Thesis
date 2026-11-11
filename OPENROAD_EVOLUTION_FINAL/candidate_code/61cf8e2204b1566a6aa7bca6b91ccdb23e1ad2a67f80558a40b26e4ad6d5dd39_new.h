// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72000505;
  double density_weight = 0.51805203;
  double prefix_weight = 0.01229720;
  double neighborhood_weight = 0.36130430;
  double late_weight = 0.22224964;
  double critical_weight = 0.04563269;
  unsigned budget = 24;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
