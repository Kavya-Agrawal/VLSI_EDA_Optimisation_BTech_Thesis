// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58982500;
  double density_weight = 0.54357025;
  double prefix_weight = 0.10758840;
  double neighborhood_weight = 0.21664069;
  double late_weight = 0.01189911;
  double critical_weight = 0.02704408;
  unsigned budget = 16;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
