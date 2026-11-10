// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99775475;
  double density_weight = 0.54293727;
  double prefix_weight = 0.38888414;
  double neighborhood_weight = 0.08769860;
  double late_weight = 0.06222444;
  double critical_weight = 0.22291032;
  unsigned budget = 16;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
