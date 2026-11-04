// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18244500;
  double density_weight = 0.44534502;
  double prefix_weight = 0.38315335;
  double neighborhood_weight = 0.36112757;
  double late_weight = 0.16521622;
  double critical_weight = 0.46657045;
  unsigned budget = 39;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
