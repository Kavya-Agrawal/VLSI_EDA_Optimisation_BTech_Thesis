// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89272562;
  double density_weight = 0.10471279;
  double prefix_weight = 0.44943074;
  double neighborhood_weight = 0.32879262;
  double late_weight = 0.23022137;
  double critical_weight = 0.05126100;
  unsigned budget = 4;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
