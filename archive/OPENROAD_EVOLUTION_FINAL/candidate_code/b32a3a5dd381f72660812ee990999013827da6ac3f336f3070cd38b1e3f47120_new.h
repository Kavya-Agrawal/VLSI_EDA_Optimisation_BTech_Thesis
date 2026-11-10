// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60430866;
  double density_weight = 0.08032058;
  double prefix_weight = 0.32865949;
  double neighborhood_weight = 0.32584251;
  double late_weight = 0.25249854;
  double critical_weight = 0.10675994;
  unsigned budget = 19;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
