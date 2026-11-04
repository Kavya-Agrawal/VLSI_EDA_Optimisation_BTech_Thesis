// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04545188;
  double density_weight = 0.27675441;
  double prefix_weight = 0.49022945;
  double neighborhood_weight = 0.20135869;
  double late_weight = 0.21829594;
  double critical_weight = 0.21341427;
  unsigned budget = 15;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
