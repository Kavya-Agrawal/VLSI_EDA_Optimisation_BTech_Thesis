// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12768164;
  double density_weight = 0.46927060;
  double prefix_weight = 0.00395510;
  double neighborhood_weight = 0.35048134;
  double late_weight = 0.14552101;
  double critical_weight = 0.23371536;
  unsigned budget = 4;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
