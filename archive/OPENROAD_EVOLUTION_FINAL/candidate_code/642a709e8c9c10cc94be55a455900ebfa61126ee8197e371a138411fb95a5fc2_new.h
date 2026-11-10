// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31605530;
  double density_weight = 0.12114384;
  double prefix_weight = 0.07229740;
  double neighborhood_weight = 0.39761982;
  double late_weight = 0.05086979;
  double critical_weight = 0.28733897;
  unsigned budget = 4;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
