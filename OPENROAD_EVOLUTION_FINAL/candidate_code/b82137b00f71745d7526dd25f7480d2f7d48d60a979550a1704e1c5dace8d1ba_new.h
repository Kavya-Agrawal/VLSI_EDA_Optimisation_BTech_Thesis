// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47736887;
  double density_weight = 0.47497277;
  double prefix_weight = 0.38313271;
  double neighborhood_weight = 0.17715980;
  double late_weight = 0.06058659;
  double critical_weight = 0.44593004;
  unsigned budget = 33;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
