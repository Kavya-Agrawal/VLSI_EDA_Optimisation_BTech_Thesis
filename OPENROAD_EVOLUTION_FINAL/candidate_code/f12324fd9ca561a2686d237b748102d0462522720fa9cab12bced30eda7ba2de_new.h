// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48775702;
  double density_weight = 0.29836132;
  double prefix_weight = 0.32159148;
  double neighborhood_weight = 0.09929921;
  double late_weight = 0.00352238;
  double critical_weight = 0.18385022;
  unsigned budget = 27;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
