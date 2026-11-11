// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89397311;
  double density_weight = 0.10586112;
  double prefix_weight = 0.07697370;
  double neighborhood_weight = 0.36363640;
  double late_weight = 0.12254137;
  double critical_weight = 0.37592436;
  unsigned budget = 22;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
