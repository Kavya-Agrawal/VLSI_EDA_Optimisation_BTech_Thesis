// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12400553;
  double density_weight = 0.07827574;
  double prefix_weight = 0.13577380;
  double neighborhood_weight = 0.13103676;
  double late_weight = 0.20832184;
  double critical_weight = 0.08440950;
  unsigned budget = 23;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
