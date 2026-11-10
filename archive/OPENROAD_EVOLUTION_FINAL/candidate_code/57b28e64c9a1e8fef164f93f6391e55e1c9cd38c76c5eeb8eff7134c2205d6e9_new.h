// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20931677;
  double density_weight = 0.28457540;
  double prefix_weight = 0.04957719;
  double neighborhood_weight = 0.31115167;
  double late_weight = 0.09008828;
  double critical_weight = 0.20961173;
  unsigned budget = 18;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
