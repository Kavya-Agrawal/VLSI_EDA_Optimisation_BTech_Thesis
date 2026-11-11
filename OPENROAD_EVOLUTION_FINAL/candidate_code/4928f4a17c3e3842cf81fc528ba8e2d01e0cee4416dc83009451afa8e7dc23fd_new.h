// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19763410;
  double density_weight = 0.34756433;
  double prefix_weight = 0.49354150;
  double neighborhood_weight = 0.03733867;
  double late_weight = 0.04206275;
  double critical_weight = 0.03272638;
  unsigned budget = 15;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
