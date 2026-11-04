// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72470481;
  double density_weight = 0.23171909;
  double prefix_weight = 0.47651338;
  double neighborhood_weight = 0.08994716;
  double late_weight = 0.10467686;
  double critical_weight = 0.14199196;
  unsigned budget = 31;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
