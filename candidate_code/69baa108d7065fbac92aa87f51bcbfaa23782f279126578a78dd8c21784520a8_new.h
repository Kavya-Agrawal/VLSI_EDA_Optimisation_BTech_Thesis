// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29628043;
  double density_weight = 0.24649474;
  double prefix_weight = 0.37025949;
  double neighborhood_weight = 0.07337840;
  double late_weight = 0.00237682;
  double critical_weight = 0.43856173;
  unsigned budget = 11;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
