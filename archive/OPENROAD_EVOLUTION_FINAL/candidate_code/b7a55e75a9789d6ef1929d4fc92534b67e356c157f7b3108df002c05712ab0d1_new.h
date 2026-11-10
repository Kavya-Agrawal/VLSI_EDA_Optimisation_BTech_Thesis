// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67952413;
  double density_weight = 0.37436299;
  double prefix_weight = 0.15556206;
  double neighborhood_weight = 0.10971257;
  double late_weight = 0.17440008;
  double critical_weight = 0.12036149;
  unsigned budget = 30;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
