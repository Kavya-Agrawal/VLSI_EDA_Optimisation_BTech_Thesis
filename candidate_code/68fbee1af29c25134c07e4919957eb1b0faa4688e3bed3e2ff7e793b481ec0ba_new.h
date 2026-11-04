// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93925293;
  double density_weight = 0.11451593;
  double prefix_weight = 0.22233044;
  double neighborhood_weight = 0.29544900;
  double late_weight = 0.26431804;
  double critical_weight = 0.48481772;
  unsigned budget = 12;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
