// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75636060;
  double density_weight = 0.13292681;
  double prefix_weight = 0.03406228;
  double neighborhood_weight = 0.22313217;
  double late_weight = 0.25898771;
  double critical_weight = 0.48961843;
  unsigned budget = 35;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
