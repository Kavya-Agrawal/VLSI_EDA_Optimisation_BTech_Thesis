// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05383762;
  double density_weight = 0.00639756;
  double prefix_weight = 0.43617268;
  double neighborhood_weight = 0.13229621;
  double late_weight = 0.22860116;
  double critical_weight = 0.06712329;
  unsigned budget = 28;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
