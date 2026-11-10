// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97534887;
  double density_weight = 0.57125019;
  double prefix_weight = 0.01367388;
  double neighborhood_weight = 0.39319609;
  double late_weight = 0.01918011;
  double critical_weight = 0.38919960;
  unsigned budget = 16;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
