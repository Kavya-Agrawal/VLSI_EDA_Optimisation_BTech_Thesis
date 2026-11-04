// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57571373;
  double density_weight = 0.21254195;
  double prefix_weight = 0.30135423;
  double neighborhood_weight = 0.09815132;
  double late_weight = 0.24189638;
  double critical_weight = 0.26519219;
  unsigned budget = 4;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
