// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85217020;
  double density_weight = 0.38354831;
  double prefix_weight = 0.46178680;
  double neighborhood_weight = 0.33098997;
  double late_weight = 0.15623085;
  double critical_weight = 0.20013839;
  unsigned budget = 11;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
