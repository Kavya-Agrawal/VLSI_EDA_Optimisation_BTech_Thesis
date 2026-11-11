// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88857637;
  double density_weight = 0.30853905;
  double prefix_weight = 0.36712838;
  double neighborhood_weight = 0.20972689;
  double late_weight = 0.00334404;
  double critical_weight = 0.13927765;
  unsigned budget = 16;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
