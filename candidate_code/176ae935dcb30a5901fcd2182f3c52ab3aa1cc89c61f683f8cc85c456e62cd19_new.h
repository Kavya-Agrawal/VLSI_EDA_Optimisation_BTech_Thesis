// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52813167;
  double density_weight = 0.20425214;
  double prefix_weight = 0.02293126;
  double neighborhood_weight = 0.36227610;
  double late_weight = 0.08072121;
  double critical_weight = 0.49792140;
  unsigned budget = 40;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
