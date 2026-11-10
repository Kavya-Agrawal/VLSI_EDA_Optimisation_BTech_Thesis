// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83406534;
  double density_weight = 0.15565904;
  double prefix_weight = 0.24078131;
  double neighborhood_weight = 0.25040002;
  double late_weight = 0.06315401;
  double critical_weight = 0.38917826;
  unsigned budget = 18;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
