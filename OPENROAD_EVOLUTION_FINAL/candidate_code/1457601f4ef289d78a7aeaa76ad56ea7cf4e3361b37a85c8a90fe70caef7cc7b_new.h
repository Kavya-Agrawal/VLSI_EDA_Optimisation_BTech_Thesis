// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40386767;
  double density_weight = 0.14919881;
  double prefix_weight = 0.48273711;
  double neighborhood_weight = 0.14917094;
  double late_weight = 0.11837133;
  double critical_weight = 0.38854033;
  unsigned budget = 38;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
