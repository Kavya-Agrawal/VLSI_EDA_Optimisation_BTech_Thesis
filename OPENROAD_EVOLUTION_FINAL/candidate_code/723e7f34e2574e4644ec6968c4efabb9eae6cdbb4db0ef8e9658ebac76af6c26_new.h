// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64408587;
  double density_weight = 0.14626329;
  double prefix_weight = 0.12171474;
  double neighborhood_weight = 0.17130102;
  double late_weight = 0.08112691;
  double critical_weight = 0.08411261;
  unsigned budget = 36;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
