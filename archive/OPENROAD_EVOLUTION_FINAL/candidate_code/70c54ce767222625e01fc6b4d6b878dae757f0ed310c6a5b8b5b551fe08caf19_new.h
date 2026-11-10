// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82462688;
  double density_weight = 0.03323310;
  double prefix_weight = 0.35058679;
  double neighborhood_weight = 0.27101757;
  double late_weight = 0.04258964;
  double critical_weight = 0.26183410;
  unsigned budget = 23;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
