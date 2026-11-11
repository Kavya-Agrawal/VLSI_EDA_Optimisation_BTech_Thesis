// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11919530;
  double density_weight = 0.44870103;
  double prefix_weight = 0.06382321;
  double neighborhood_weight = 0.29607990;
  double late_weight = 0.03818104;
  double critical_weight = 0.14998934;
  unsigned budget = 12;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
