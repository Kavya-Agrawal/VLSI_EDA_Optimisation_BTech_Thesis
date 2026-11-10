// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90571814;
  double density_weight = 0.26615108;
  double prefix_weight = 0.46325996;
  double neighborhood_weight = 0.38253566;
  double late_weight = 0.29754672;
  double critical_weight = 0.08817346;
  unsigned budget = 39;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
