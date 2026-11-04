// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71601238;
  double density_weight = 0.07772977;
  double prefix_weight = 0.14711595;
  double neighborhood_weight = 0.27091621;
  double late_weight = 0.29041201;
  double critical_weight = 0.30635026;
  unsigned budget = 17;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
