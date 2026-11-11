// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49988689;
  double density_weight = 0.31947320;
  double prefix_weight = 0.11710271;
  double neighborhood_weight = 0.07889594;
  double late_weight = 0.00531193;
  double critical_weight = 0.07192973;
  unsigned budget = 31;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
