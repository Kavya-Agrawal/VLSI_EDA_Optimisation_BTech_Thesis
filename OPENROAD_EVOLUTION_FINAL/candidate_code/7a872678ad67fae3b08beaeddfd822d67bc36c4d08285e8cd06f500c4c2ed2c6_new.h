// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88382896;
  double density_weight = 0.13838533;
  double prefix_weight = 0.29510635;
  double neighborhood_weight = 0.16302535;
  double late_weight = 0.15941587;
  double critical_weight = 0.41794553;
  unsigned budget = 17;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
