// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59846132;
  double density_weight = 0.43865374;
  double prefix_weight = 0.22915765;
  double neighborhood_weight = 0.04995762;
  double late_weight = 0.10574869;
  double critical_weight = 0.20680370;
  unsigned budget = 18;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
