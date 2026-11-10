// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47891478;
  double density_weight = 0.59505152;
  double prefix_weight = 0.20672245;
  double neighborhood_weight = 0.08272352;
  double late_weight = 0.28452529;
  double critical_weight = 0.41452143;
  unsigned budget = 29;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
