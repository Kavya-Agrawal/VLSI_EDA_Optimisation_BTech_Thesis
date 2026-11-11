// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39598920;
  double density_weight = 0.37234913;
  double prefix_weight = 0.22034846;
  double neighborhood_weight = 0.33322872;
  double late_weight = 0.11202721;
  double critical_weight = 0.26657855;
  unsigned budget = 11;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
