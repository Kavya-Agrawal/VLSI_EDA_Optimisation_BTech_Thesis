// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65491605;
  double density_weight = 0.20775050;
  double prefix_weight = 0.11993080;
  double neighborhood_weight = 0.02448729;
  double late_weight = 0.23688604;
  double critical_weight = 0.29228692;
  unsigned budget = 32;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
