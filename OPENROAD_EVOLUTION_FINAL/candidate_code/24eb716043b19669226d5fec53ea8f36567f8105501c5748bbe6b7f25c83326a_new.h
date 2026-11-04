// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32749006;
  double density_weight = 0.18639172;
  double prefix_weight = 0.00926711;
  double neighborhood_weight = 0.17701446;
  double late_weight = 0.04821224;
  double critical_weight = 0.11471197;
  unsigned budget = 11;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
