// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08812214;
  double density_weight = 0.06303311;
  double prefix_weight = 0.09387005;
  double neighborhood_weight = 0.26922873;
  double late_weight = 0.11592130;
  double critical_weight = 0.08442988;
  unsigned budget = 33;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
