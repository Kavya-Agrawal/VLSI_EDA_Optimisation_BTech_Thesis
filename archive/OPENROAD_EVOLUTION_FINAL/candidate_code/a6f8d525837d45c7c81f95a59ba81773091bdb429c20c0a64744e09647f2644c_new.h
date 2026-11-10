// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73028767;
  double density_weight = 0.20339906;
  double prefix_weight = 0.02013898;
  double neighborhood_weight = 0.32668698;
  double late_weight = 0.22615715;
  double critical_weight = 0.16915399;
  unsigned budget = 34;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
