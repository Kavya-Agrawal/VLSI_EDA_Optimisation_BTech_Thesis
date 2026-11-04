// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48909362;
  double density_weight = 0.47958165;
  double prefix_weight = 0.44180850;
  double neighborhood_weight = 0.31160514;
  double late_weight = 0.12336940;
  double critical_weight = 0.19179950;
  unsigned budget = 27;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
