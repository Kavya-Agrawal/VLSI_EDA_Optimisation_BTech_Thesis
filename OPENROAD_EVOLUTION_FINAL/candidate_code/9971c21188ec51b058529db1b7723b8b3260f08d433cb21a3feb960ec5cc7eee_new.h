// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86911767;
  double density_weight = 0.54569760;
  double prefix_weight = 0.18770482;
  double neighborhood_weight = 0.23316194;
  double late_weight = 0.25613376;
  double critical_weight = 0.30076761;
  unsigned budget = 33;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
