// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23090086;
  double density_weight = 0.57947109;
  double prefix_weight = 0.04346508;
  double neighborhood_weight = 0.38301446;
  double late_weight = 0.23337059;
  double critical_weight = 0.39241849;
  unsigned budget = 14;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
