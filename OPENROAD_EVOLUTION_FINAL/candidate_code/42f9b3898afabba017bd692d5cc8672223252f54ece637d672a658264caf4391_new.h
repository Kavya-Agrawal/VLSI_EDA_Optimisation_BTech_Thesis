// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88389301;
  double density_weight = 0.26627061;
  double prefix_weight = 0.18588980;
  double neighborhood_weight = 0.01256209;
  double late_weight = 0.02671001;
  double critical_weight = 0.25470722;
  unsigned budget = 28;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
