// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98377167;
  double density_weight = 0.17899316;
  double prefix_weight = 0.46579848;
  double neighborhood_weight = 0.19662242;
  double late_weight = 0.14034742;
  double critical_weight = 0.42253502;
  unsigned budget = 13;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
