// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81962370;
  double density_weight = 0.53144987;
  double prefix_weight = 0.03408407;
  double neighborhood_weight = 0.14798854;
  double late_weight = 0.25055236;
  double critical_weight = 0.21887446;
  unsigned budget = 21;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
