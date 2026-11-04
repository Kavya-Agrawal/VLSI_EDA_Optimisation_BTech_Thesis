// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72166491;
  double density_weight = 0.47221072;
  double prefix_weight = 0.06876579;
  double neighborhood_weight = 0.13797943;
  double late_weight = 0.02008845;
  double critical_weight = 0.45849653;
  unsigned budget = 11;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
