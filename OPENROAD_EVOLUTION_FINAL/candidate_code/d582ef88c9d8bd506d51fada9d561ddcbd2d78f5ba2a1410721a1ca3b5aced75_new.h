// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41432682;
  double density_weight = 0.25108519;
  double prefix_weight = 0.08411402;
  double neighborhood_weight = 0.21010060;
  double late_weight = 0.19214783;
  double critical_weight = 0.23630691;
  unsigned budget = 30;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
