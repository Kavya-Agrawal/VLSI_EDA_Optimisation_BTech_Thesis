// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79442845;
  double density_weight = 0.00934793;
  double prefix_weight = 0.48411006;
  double neighborhood_weight = 0.18201327;
  double late_weight = 0.06177581;
  double critical_weight = 0.39608350;
  unsigned budget = 18;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
