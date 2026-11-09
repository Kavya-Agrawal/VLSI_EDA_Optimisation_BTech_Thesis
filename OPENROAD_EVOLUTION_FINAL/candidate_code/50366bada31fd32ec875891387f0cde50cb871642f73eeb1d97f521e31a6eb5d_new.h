// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40997092;
  double density_weight = 0.08633001;
  double prefix_weight = 0.10891035;
  double neighborhood_weight = 0.00947012;
  double late_weight = 0.14320119;
  double critical_weight = 0.07465547;
  unsigned budget = 33;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
