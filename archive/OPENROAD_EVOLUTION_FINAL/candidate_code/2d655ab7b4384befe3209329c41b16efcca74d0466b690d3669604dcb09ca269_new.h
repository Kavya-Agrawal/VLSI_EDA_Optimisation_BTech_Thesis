// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09007761;
  double density_weight = 0.46917717;
  double prefix_weight = 0.28093096;
  double neighborhood_weight = 0.24853287;
  double late_weight = 0.04198539;
  double critical_weight = 0.27598898;
  unsigned budget = 23;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
