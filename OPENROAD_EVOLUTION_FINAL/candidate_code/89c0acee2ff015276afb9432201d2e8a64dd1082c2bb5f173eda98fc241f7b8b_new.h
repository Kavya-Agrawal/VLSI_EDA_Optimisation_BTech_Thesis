// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10743526;
  double density_weight = 0.09907660;
  double prefix_weight = 0.45704263;
  double neighborhood_weight = 0.28972420;
  double late_weight = 0.01178553;
  double critical_weight = 0.13452514;
  unsigned budget = 26;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
