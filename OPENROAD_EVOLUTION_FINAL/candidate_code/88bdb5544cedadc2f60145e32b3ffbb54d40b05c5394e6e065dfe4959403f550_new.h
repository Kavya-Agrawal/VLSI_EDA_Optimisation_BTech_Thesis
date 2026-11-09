// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.69996643;
  double density_weight = 0.41274956;
  double prefix_weight = 0.27333924;
  double neighborhood_weight = 0.17927040;
  double late_weight = 0.24220740;
  double critical_weight = 0.05471752;
  unsigned budget = 27;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
