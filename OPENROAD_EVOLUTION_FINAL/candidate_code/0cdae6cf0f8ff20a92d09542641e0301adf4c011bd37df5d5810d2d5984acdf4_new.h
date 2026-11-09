// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99284053;
  double density_weight = 0.20760498;
  double prefix_weight = 0.06125013;
  double neighborhood_weight = 0.05401786;
  double late_weight = 0.22832991;
  double critical_weight = 0.32283181;
  unsigned budget = 37;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
