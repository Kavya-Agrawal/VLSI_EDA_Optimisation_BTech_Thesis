// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21333478;
  double density_weight = 0.28882963;
  double prefix_weight = 0.39842986;
  double neighborhood_weight = 0.38180477;
  double late_weight = 0.06263576;
  double critical_weight = 0.31478699;
  unsigned budget = 37;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
