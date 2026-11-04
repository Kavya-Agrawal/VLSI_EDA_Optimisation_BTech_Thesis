// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80375081;
  double density_weight = 0.20365936;
  double prefix_weight = 0.30321275;
  double neighborhood_weight = 0.17516319;
  double late_weight = 0.07938896;
  double critical_weight = 0.27663436;
  unsigned budget = 13;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
