// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32755293;
  double density_weight = 0.38019821;
  double prefix_weight = 0.16523316;
  double neighborhood_weight = 0.25799320;
  double late_weight = 0.12781666;
  double critical_weight = 0.46021188;
  unsigned budget = 17;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
