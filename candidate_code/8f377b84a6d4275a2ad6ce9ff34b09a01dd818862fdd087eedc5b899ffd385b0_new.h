// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80845605;
  double density_weight = 0.09705908;
  double prefix_weight = 0.49868458;
  double neighborhood_weight = 0.12659395;
  double late_weight = 0.21199469;
  double critical_weight = 0.30529208;
  unsigned budget = 33;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
