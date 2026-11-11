// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10517263;
  double density_weight = 0.03748939;
  double prefix_weight = 0.49753504;
  double neighborhood_weight = 0.20259784;
  double late_weight = 0.25497249;
  double critical_weight = 0.15482401;
  unsigned budget = 9;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
