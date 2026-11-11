// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54860980;
  double density_weight = 0.07375888;
  double prefix_weight = 0.17061294;
  double neighborhood_weight = 0.27124567;
  double late_weight = 0.06458181;
  double critical_weight = 0.36019521;
  unsigned budget = 32;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
