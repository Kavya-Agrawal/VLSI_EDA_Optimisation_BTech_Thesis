// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99813827;
  double density_weight = 0.57614690;
  double prefix_weight = 0.06523000;
  double neighborhood_weight = 0.27712871;
  double late_weight = 0.11913507;
  double critical_weight = 0.17674272;
  unsigned budget = 25;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
