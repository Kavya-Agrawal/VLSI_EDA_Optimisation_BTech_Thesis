// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57716404;
  double density_weight = 0.53886840;
  double prefix_weight = 0.13954791;
  double neighborhood_weight = 0.08148365;
  double late_weight = 0.17237340;
  double critical_weight = 0.48310794;
  unsigned budget = 18;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
