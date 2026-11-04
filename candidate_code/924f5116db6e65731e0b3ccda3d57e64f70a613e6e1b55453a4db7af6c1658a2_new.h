// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29091789;
  double density_weight = 0.25944658;
  double prefix_weight = 0.25483502;
  double neighborhood_weight = 0.33344437;
  double late_weight = 0.12707313;
  double critical_weight = 0.02165597;
  unsigned budget = 7;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
