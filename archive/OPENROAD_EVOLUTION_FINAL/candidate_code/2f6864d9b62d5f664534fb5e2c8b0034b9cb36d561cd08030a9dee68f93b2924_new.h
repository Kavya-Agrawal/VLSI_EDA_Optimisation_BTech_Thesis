// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79296109;
  double density_weight = 0.04901128;
  double prefix_weight = 0.13532117;
  double neighborhood_weight = 0.11764816;
  double late_weight = 0.06670471;
  double critical_weight = 0.17093524;
  unsigned budget = 15;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
