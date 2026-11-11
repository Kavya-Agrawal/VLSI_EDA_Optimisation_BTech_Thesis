// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12329178;
  double density_weight = 0.07183125;
  double prefix_weight = 0.03329079;
  double neighborhood_weight = 0.21429670;
  double late_weight = 0.12960543;
  double critical_weight = 0.41597364;
  unsigned budget = 33;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
