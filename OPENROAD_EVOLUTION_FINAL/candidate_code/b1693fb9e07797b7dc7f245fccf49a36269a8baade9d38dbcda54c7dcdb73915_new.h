// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82421286;
  double density_weight = 0.10041075;
  double prefix_weight = 0.37260437;
  double neighborhood_weight = 0.02574277;
  double late_weight = 0.11593366;
  double critical_weight = 0.44552704;
  unsigned budget = 8;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
