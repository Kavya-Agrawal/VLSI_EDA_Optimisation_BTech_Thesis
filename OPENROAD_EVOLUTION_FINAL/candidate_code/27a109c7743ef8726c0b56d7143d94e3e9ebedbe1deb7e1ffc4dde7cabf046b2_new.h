// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32541174;
  double density_weight = 0.55996701;
  double prefix_weight = 0.09231236;
  double neighborhood_weight = 0.13096460;
  double late_weight = 0.22168722;
  double critical_weight = 0.13852660;
  unsigned budget = 25;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
