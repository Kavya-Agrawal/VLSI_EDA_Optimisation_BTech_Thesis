// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64832224;
  double density_weight = 0.41644560;
  double prefix_weight = 0.29745224;
  double neighborhood_weight = 0.08743917;
  double late_weight = 0.25841922;
  double critical_weight = 0.28228043;
  unsigned budget = 38;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
