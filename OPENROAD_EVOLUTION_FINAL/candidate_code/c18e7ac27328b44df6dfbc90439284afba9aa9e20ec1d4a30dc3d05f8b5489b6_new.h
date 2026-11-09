// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10952890;
  double density_weight = 0.24030316;
  double prefix_weight = 0.08590834;
  double neighborhood_weight = 0.01939094;
  double late_weight = 0.01390498;
  double critical_weight = 0.31294165;
  unsigned budget = 28;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
