// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94748403;
  double density_weight = 0.15594763;
  double prefix_weight = 0.44051865;
  double neighborhood_weight = 0.35070975;
  double late_weight = 0.06421058;
  double critical_weight = 0.31175377;
  unsigned budget = 12;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
