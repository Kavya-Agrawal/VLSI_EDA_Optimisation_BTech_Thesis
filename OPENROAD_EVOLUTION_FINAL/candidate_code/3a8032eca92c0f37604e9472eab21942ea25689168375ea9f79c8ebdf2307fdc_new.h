// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91878933;
  double density_weight = 0.22056688;
  double prefix_weight = 0.35706838;
  double neighborhood_weight = 0.35262498;
  double late_weight = 0.15529126;
  double critical_weight = 0.06568108;
  unsigned budget = 13;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
