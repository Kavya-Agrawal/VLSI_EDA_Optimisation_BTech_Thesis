// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68284092;
  double density_weight = 0.07323051;
  double prefix_weight = 0.06867077;
  double neighborhood_weight = 0.00017268;
  double late_weight = 0.25821322;
  double critical_weight = 0.07086156;
  unsigned budget = 4;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
