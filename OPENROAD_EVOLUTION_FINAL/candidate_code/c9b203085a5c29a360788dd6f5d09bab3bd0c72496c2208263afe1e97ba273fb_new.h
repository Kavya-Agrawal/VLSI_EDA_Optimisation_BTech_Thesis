// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71374371;
  double density_weight = 0.14060086;
  double prefix_weight = 0.45107221;
  double neighborhood_weight = 0.00942356;
  double late_weight = 0.15093259;
  double critical_weight = 0.08265694;
  unsigned budget = 24;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
