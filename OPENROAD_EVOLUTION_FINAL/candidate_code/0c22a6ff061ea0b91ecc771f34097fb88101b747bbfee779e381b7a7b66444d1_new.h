// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99243041;
  double density_weight = 0.51231843;
  double prefix_weight = 0.41394083;
  double neighborhood_weight = 0.36638144;
  double late_weight = 0.24370547;
  double critical_weight = 0.11929082;
  unsigned budget = 24;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
