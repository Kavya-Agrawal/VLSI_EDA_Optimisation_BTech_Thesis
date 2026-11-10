// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27222642;
  double density_weight = 0.24012663;
  double prefix_weight = 0.21364500;
  double neighborhood_weight = 0.36896003;
  double late_weight = 0.07279775;
  double critical_weight = 0.49827012;
  unsigned budget = 14;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
