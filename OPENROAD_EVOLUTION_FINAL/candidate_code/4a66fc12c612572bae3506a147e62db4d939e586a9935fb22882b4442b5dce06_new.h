// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53258662;
  double density_weight = 0.11003822;
  double prefix_weight = 0.27092660;
  double neighborhood_weight = 0.00161051;
  double late_weight = 0.21651623;
  double critical_weight = 0.33215040;
  unsigned budget = 16;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
