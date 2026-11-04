// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25845721;
  double density_weight = 0.39469602;
  double prefix_weight = 0.35766495;
  double neighborhood_weight = 0.31261518;
  double late_weight = 0.01483169;
  double critical_weight = 0.34740513;
  unsigned budget = 29;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
