// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96058389;
  double density_weight = 0.21300649;
  double prefix_weight = 0.17927968;
  double neighborhood_weight = 0.21177176;
  double late_weight = 0.04707912;
  double critical_weight = 0.31810553;
  unsigned budget = 4;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
