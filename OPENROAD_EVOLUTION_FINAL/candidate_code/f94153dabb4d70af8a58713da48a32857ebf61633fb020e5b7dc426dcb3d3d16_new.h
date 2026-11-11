// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75337564;
  double density_weight = 0.46621120;
  double prefix_weight = 0.08219580;
  double neighborhood_weight = 0.22211938;
  double late_weight = 0.23506290;
  double critical_weight = 0.41476643;
  unsigned budget = 37;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
