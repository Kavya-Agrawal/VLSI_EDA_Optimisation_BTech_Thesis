// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45817372;
  double density_weight = 0.42860634;
  double prefix_weight = 0.32780944;
  double neighborhood_weight = 0.18258587;
  double late_weight = 0.01383272;
  double critical_weight = 0.16628480;
  unsigned budget = 21;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
