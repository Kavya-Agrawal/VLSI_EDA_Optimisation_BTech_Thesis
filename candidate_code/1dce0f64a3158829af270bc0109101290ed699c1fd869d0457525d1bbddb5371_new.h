// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13381740;
  double density_weight = 0.35410581;
  double prefix_weight = 0.39353637;
  double neighborhood_weight = 0.21943598;
  double late_weight = 0.09276455;
  double critical_weight = 0.17799859;
  unsigned budget = 16;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
