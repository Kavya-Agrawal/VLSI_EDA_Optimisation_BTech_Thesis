// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52512268;
  double density_weight = 0.38114744;
  double prefix_weight = 0.39608876;
  double neighborhood_weight = 0.24388942;
  double late_weight = 0.11623912;
  double critical_weight = 0.36313011;
  unsigned budget = 11;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
