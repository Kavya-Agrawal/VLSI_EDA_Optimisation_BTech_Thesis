// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88408301;
  double density_weight = 0.30164029;
  double prefix_weight = 0.29633829;
  double neighborhood_weight = 0.17530715;
  double late_weight = 0.09124341;
  double critical_weight = 0.36469841;
  unsigned budget = 32;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
