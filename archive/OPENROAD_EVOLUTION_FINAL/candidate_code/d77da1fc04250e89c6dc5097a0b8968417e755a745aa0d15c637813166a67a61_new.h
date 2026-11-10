// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25560701;
  double density_weight = 0.06045635;
  double prefix_weight = 0.35422670;
  double neighborhood_weight = 0.18661494;
  double late_weight = 0.16577371;
  double critical_weight = 0.34812751;
  unsigned budget = 21;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
