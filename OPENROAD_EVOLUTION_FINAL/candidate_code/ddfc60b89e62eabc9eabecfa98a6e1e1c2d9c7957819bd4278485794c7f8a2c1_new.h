// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20848853;
  double density_weight = 0.53776107;
  double prefix_weight = 0.32283539;
  double neighborhood_weight = 0.02318820;
  double late_weight = 0.00395146;
  double critical_weight = 0.33626647;
  unsigned budget = 33;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
