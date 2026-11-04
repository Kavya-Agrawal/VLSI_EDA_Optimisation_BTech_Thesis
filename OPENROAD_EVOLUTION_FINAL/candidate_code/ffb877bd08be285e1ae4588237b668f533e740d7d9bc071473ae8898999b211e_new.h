// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51960680;
  double density_weight = 0.53479430;
  double prefix_weight = 0.47165411;
  double neighborhood_weight = 0.01881374;
  double late_weight = 0.27464632;
  double critical_weight = 0.24687857;
  unsigned budget = 20;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
