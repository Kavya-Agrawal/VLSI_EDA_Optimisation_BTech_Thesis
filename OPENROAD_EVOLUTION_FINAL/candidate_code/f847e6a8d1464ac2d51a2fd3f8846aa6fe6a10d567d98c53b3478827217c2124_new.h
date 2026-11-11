// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00102767;
  double density_weight = 0.06399679;
  double prefix_weight = 0.11553335;
  double neighborhood_weight = 0.28073116;
  double late_weight = 0.15423890;
  double critical_weight = 0.45166454;
  unsigned budget = 37;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
