// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29620004;
  double density_weight = 0.02956820;
  double prefix_weight = 0.28031920;
  double neighborhood_weight = 0.16938544;
  double late_weight = 0.13977155;
  double critical_weight = 0.30708339;
  unsigned budget = 29;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
