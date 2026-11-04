// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87636607;
  double density_weight = 0.49584917;
  double prefix_weight = 0.32466209;
  double neighborhood_weight = 0.21774286;
  double late_weight = 0.25328103;
  double critical_weight = 0.03466463;
  unsigned budget = 9;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
