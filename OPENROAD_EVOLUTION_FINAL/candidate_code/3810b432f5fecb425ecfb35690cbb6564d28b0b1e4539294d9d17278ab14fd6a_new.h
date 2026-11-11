// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37538067;
  double density_weight = 0.37350819;
  double prefix_weight = 0.11249789;
  double neighborhood_weight = 0.13660927;
  double late_weight = 0.23336289;
  double critical_weight = 0.42032126;
  unsigned budget = 5;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
