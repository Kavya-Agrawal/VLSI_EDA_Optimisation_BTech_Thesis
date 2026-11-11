// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94311339;
  double density_weight = 0.55144072;
  double prefix_weight = 0.09405015;
  double neighborhood_weight = 0.18952460;
  double late_weight = 0.16636823;
  double critical_weight = 0.25316059;
  unsigned budget = 36;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
