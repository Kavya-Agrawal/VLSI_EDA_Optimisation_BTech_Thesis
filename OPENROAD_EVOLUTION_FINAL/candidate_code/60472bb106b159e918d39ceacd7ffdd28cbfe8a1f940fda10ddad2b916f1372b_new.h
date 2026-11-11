// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75348084;
  double density_weight = 0.17365200;
  double prefix_weight = 0.19190202;
  double neighborhood_weight = 0.26060569;
  double late_weight = 0.10813544;
  double critical_weight = 0.15056166;
  unsigned budget = 16;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
