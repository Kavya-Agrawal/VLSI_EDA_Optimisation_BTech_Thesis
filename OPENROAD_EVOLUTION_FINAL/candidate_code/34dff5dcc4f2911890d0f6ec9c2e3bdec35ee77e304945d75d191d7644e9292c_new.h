// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71706116;
  double density_weight = 0.02034671;
  double prefix_weight = 0.35607039;
  double neighborhood_weight = 0.12634731;
  double late_weight = 0.20106605;
  double critical_weight = 0.36662354;
  unsigned budget = 7;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
