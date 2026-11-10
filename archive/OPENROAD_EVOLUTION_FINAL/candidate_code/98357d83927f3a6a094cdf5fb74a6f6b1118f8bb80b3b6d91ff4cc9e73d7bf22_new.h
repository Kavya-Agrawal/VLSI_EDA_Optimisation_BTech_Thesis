// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57550874;
  double density_weight = 0.45349016;
  double prefix_weight = 0.39578734;
  double neighborhood_weight = 0.10034108;
  double late_weight = 0.12612478;
  double critical_weight = 0.07081648;
  unsigned budget = 12;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
