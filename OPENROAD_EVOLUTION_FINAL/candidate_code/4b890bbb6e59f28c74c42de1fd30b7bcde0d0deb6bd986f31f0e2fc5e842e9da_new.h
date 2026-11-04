// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45645310;
  double density_weight = 0.41308067;
  double prefix_weight = 0.28542739;
  double neighborhood_weight = 0.32744622;
  double late_weight = 0.11140123;
  double critical_weight = 0.48636881;
  unsigned budget = 26;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
