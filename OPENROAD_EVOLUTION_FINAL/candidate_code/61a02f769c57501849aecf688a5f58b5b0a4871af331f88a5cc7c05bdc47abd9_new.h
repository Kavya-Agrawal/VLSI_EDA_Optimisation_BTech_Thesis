// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.69848169;
  double density_weight = 0.30797048;
  double prefix_weight = 0.26846094;
  double neighborhood_weight = 0.36019645;
  double late_weight = 0.25873383;
  double critical_weight = 0.11607890;
  unsigned budget = 26;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
