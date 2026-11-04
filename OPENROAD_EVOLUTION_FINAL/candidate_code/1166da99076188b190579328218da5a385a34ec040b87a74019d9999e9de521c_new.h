// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16130423;
  double density_weight = 0.54595622;
  double prefix_weight = 0.41357796;
  double neighborhood_weight = 0.35408211;
  double late_weight = 0.00717714;
  double critical_weight = 0.25375767;
  unsigned budget = 21;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
