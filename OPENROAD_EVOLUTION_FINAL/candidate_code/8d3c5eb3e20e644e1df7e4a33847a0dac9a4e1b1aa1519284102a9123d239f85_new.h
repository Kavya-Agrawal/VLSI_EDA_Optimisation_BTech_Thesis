// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53733640;
  double density_weight = 0.49027781;
  double prefix_weight = 0.35631409;
  double neighborhood_weight = 0.02233739;
  double late_weight = 0.08039583;
  double critical_weight = 0.07904452;
  unsigned budget = 30;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
