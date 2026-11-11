// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70520558;
  double density_weight = 0.04768201;
  double prefix_weight = 0.18173512;
  double neighborhood_weight = 0.11418108;
  double late_weight = 0.09900000;
  double critical_weight = 0.17784742;
  unsigned budget = 15;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
