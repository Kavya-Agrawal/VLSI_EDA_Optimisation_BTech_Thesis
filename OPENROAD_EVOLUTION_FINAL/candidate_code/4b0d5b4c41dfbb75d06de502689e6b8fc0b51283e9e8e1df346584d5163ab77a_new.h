// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16064997;
  double density_weight = 0.12166574;
  double prefix_weight = 0.44536829;
  double neighborhood_weight = 0.06620562;
  double late_weight = 0.26709485;
  double critical_weight = 0.38252047;
  unsigned budget = 7;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
