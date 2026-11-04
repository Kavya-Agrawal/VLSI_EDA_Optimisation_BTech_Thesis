// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89060537;
  double density_weight = 0.53281738;
  double prefix_weight = 0.45533185;
  double neighborhood_weight = 0.29716156;
  double late_weight = 0.27649429;
  double critical_weight = 0.49072851;
  unsigned budget = 27;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
