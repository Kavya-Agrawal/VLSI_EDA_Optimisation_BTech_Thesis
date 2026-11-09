// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20011698;
  double density_weight = 0.13262444;
  double prefix_weight = 0.36071736;
  double neighborhood_weight = 0.25803148;
  double late_weight = 0.27323730;
  double critical_weight = 0.40825861;
  unsigned budget = 35;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
