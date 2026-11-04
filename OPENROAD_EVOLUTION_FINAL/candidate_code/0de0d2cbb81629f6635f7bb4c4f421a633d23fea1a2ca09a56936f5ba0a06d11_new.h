// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44637845;
  double density_weight = 0.28345121;
  double prefix_weight = 0.04876888;
  double neighborhood_weight = 0.09111737;
  double late_weight = 0.17380182;
  double critical_weight = 0.29618807;
  unsigned budget = 31;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
