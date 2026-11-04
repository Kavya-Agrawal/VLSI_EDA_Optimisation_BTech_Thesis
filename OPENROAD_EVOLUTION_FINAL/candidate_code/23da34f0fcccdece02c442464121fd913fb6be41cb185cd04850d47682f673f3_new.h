// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15120469;
  double density_weight = 0.41771689;
  double prefix_weight = 0.08491192;
  double neighborhood_weight = 0.25736474;
  double late_weight = 0.00890959;
  double critical_weight = 0.27172225;
  unsigned budget = 19;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
