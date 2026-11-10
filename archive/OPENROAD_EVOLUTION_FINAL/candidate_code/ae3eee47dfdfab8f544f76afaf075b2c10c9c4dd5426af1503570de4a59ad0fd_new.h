// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55829752;
  double density_weight = 0.57362605;
  double prefix_weight = 0.01129136;
  double neighborhood_weight = 0.16662580;
  double late_weight = 0.27450594;
  double critical_weight = 0.34520445;
  unsigned budget = 6;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
