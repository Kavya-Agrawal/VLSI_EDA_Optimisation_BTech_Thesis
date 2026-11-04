// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15748291;
  double density_weight = 0.02631329;
  double prefix_weight = 0.05688002;
  double neighborhood_weight = 0.07812489;
  double late_weight = 0.05306180;
  double critical_weight = 0.47359361;
  unsigned budget = 27;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
