// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17307413;
  double density_weight = 0.28978507;
  double prefix_weight = 0.48078405;
  double neighborhood_weight = 0.07215858;
  double late_weight = 0.07098849;
  double critical_weight = 0.14860815;
  unsigned budget = 27;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
