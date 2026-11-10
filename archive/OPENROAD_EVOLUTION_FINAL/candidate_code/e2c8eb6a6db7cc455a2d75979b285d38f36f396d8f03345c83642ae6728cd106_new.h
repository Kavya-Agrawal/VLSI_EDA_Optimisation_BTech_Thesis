// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20449151;
  double density_weight = 0.27720280;
  double prefix_weight = 0.49037813;
  double neighborhood_weight = 0.05275631;
  double late_weight = 0.24688758;
  double critical_weight = 0.39474880;
  unsigned budget = 14;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
