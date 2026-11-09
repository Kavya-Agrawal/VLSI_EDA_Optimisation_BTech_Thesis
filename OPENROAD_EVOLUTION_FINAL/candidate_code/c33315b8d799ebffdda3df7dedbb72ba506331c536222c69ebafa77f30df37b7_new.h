// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81012379;
  double density_weight = 0.13373650;
  double prefix_weight = 0.05149131;
  double neighborhood_weight = 0.35142167;
  double late_weight = 0.10302860;
  double critical_weight = 0.24659877;
  unsigned budget = 8;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
