// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25377748;
  double density_weight = 0.12408958;
  double prefix_weight = 0.25015981;
  double neighborhood_weight = 0.09516584;
  double late_weight = 0.26080945;
  double critical_weight = 0.26840575;
  unsigned budget = 11;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
