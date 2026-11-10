// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76486698;
  double density_weight = 0.11281551;
  double prefix_weight = 0.25033851;
  double neighborhood_weight = 0.20904643;
  double late_weight = 0.10022077;
  double critical_weight = 0.06894297;
  unsigned budget = 36;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
