// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18366408;
  double density_weight = 0.37052771;
  double prefix_weight = 0.10410799;
  double neighborhood_weight = 0.21720482;
  double late_weight = 0.23936359;
  double critical_weight = 0.06693373;
  unsigned budget = 11;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
