// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64379665;
  double density_weight = 0.19597306;
  double prefix_weight = 0.00564251;
  double neighborhood_weight = 0.13895224;
  double late_weight = 0.20499978;
  double critical_weight = 0.26416591;
  unsigned budget = 14;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
