// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08861391;
  double density_weight = 0.35169300;
  double prefix_weight = 0.26587851;
  double neighborhood_weight = 0.33102116;
  double late_weight = 0.23862740;
  double critical_weight = 0.23056127;
  unsigned budget = 26;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
