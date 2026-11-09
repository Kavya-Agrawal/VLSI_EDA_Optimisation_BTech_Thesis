// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30274618;
  double density_weight = 0.08644971;
  double prefix_weight = 0.04874833;
  double neighborhood_weight = 0.26581164;
  double late_weight = 0.20114215;
  double critical_weight = 0.25779745;
  unsigned budget = 6;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
