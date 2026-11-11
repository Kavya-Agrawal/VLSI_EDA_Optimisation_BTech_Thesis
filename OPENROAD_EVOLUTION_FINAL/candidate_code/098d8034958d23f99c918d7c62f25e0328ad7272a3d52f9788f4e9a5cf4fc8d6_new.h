// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42432780;
  double density_weight = 0.29582675;
  double prefix_weight = 0.29757217;
  double neighborhood_weight = 0.39871743;
  double late_weight = 0.18405330;
  double critical_weight = 0.43964839;
  unsigned budget = 12;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
