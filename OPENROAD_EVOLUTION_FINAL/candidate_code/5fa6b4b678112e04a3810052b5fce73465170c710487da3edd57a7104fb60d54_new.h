// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55211423;
  double density_weight = 0.26144290;
  double prefix_weight = 0.46166907;
  double neighborhood_weight = 0.12274422;
  double late_weight = 0.17808294;
  double critical_weight = 0.30607488;
  unsigned budget = 38;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
