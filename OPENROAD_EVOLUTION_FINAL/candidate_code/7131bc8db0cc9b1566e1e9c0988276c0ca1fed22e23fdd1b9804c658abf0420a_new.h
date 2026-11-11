// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39049732;
  double density_weight = 0.39382472;
  double prefix_weight = 0.31998678;
  double neighborhood_weight = 0.18231054;
  double late_weight = 0.05397688;
  double critical_weight = 0.05201539;
  unsigned budget = 35;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
