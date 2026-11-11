// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57994152;
  double density_weight = 0.59686745;
  double prefix_weight = 0.08674022;
  double neighborhood_weight = 0.12740791;
  double late_weight = 0.02341888;
  double critical_weight = 0.30290593;
  unsigned budget = 8;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
