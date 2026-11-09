// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18078976;
  double density_weight = 0.31393247;
  double prefix_weight = 0.02818167;
  double neighborhood_weight = 0.29538996;
  double late_weight = 0.20243367;
  double critical_weight = 0.10602805;
  unsigned budget = 8;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
