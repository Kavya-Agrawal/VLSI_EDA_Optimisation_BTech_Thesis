// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52762109;
  double density_weight = 0.09756544;
  double prefix_weight = 0.29530642;
  double neighborhood_weight = 0.08969352;
  double late_weight = 0.18409567;
  double critical_weight = 0.02986329;
  unsigned budget = 31;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
