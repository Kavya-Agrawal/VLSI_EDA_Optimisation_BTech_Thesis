// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03966307;
  double density_weight = 0.10827222;
  double prefix_weight = 0.44701808;
  double neighborhood_weight = 0.04732048;
  double late_weight = 0.24354287;
  double critical_weight = 0.24841705;
  unsigned budget = 21;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
