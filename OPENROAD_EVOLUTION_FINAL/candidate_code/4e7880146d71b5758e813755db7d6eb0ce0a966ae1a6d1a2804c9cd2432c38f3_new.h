// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98335834;
  double density_weight = 0.20760116;
  double prefix_weight = 0.00551533;
  double neighborhood_weight = 0.07621737;
  double late_weight = 0.27640448;
  double critical_weight = 0.12486422;
  unsigned budget = 20;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
