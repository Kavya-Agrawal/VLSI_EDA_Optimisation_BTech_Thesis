// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61326574;
  double density_weight = 0.29205483;
  double prefix_weight = 0.46198967;
  double neighborhood_weight = 0.27688626;
  double late_weight = 0.24477101;
  double critical_weight = 0.26493483;
  unsigned budget = 35;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
