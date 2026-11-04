// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22099389;
  double density_weight = 0.44506872;
  double prefix_weight = 0.45974104;
  double neighborhood_weight = 0.14468414;
  double late_weight = 0.18052639;
  double critical_weight = 0.22114920;
  unsigned budget = 33;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
