// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73522938;
  double density_weight = 0.12585474;
  double prefix_weight = 0.47105129;
  double neighborhood_weight = 0.01897437;
  double late_weight = 0.14755880;
  double critical_weight = 0.41544331;
  unsigned budget = 11;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
