// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87765408;
  double density_weight = 0.52566943;
  double prefix_weight = 0.13688301;
  double neighborhood_weight = 0.13576670;
  double late_weight = 0.05508271;
  double critical_weight = 0.40932918;
  unsigned budget = 4;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
