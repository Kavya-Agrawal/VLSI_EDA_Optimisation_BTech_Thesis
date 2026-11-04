// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57802485;
  double density_weight = 0.45199748;
  double prefix_weight = 0.31809057;
  double neighborhood_weight = 0.16638755;
  double late_weight = 0.24561202;
  double critical_weight = 0.16905129;
  unsigned budget = 13;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
